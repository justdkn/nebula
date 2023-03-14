#include <iterator>
#include <orm/model.hxx>
#include <orm/exception.hxx>
#include <orm/field.hxx>
#include <mdb/statment.hxx>
#include <sstream>
#include <iostream>
#include <string>

Model::Model(Driver& driver, const char* table_name)
    : driver_(driver), table_name_(table_name) {
}

Model::~Model() {
}

const char* Model::table_name() const {
  return table_name_;
}

bool Model::save() {
  auto primary_key = this->primary_key();
  if (primary_key == nullptr) throw OrmException("not primary key");
  if (primary_key->is_null()) {
    // add
    const std::vector<const FieldBase*> fields = this->fields();
    if (fields.empty()) throw OrmException("fields is empty");

    // 构建SQL语句
    Statment stmt(driver_);
    std::stringstream ss;
    std::stringstream vss;
    ss << "INSERT INTO `" << table_name() << "`(";
    auto iter = fields.begin();
    if (*iter == primary_key) {
      iter++;
    }
    if (iter != fields.end()) {
      ss << "`" << (*iter)->name() << "`";
      iter++;
    }
    for (; iter != fields.end(); ++iter) {
      if (primary_key == *iter) continue;
      ss << ",`" << (*iter)->name() << "`";
      vss << ",?";
    }
    ss << ") VALUES(?" << vss.str() << ")";
    std::cout << ss.str() << std::endl;

    // 解析SQL语句和绑定参数与结果数据对象
    if (stmt.prepare(ss.str()) != 0) throw OrmException("prepare failed");
    if (stmt.param_count() != (fields.size() - 1))
      throw OrmException("param count not equal");
    std::vector<MYSQL_BIND> params(stmt.param_count());
    std::memset(params.data(), 0, sizeof(MYSQL_BIND) * params.size());
    for (auto i = 0, j = 0; i < fields.size(); ++i) {
      if (primary_key == fields[i]) continue;
      fields[i]->to_param(params[j++]);
    }
    if (stmt.bind_param(params.data()) != 0)
      throw OrmException("bind param failed");
    if (stmt.execute() != 0) {
      throw OrmException(stmt.error_str());
    }
    *const_cast<UBigIntField*>(primary_key) = stmt.insert_id();
    return true;
  } else {
    // update
    const std::vector<const FieldBase*> fields = this->fields();
    if (fields.empty()) throw OrmException("fields is empty");

    // 构建SQL语句
    Statment stmt(driver_);
    std::stringstream ss;
    ss << "UPDATE `" << table_name() << "` SET ";
    auto iter = fields.begin();
    if (*iter == primary_key) {
      iter++;
    }
    if (iter != fields.end()) {
      ss << "`" << (*iter)->name() << "`=?";
      iter++;
    }
    for (; iter != fields.end(); ++iter) {
      if (primary_key == *iter) continue;
      ss << ",`" << (*iter)->name() << "`=?";
    }
    ss << " WHERE `" << primary_key->name() << "`=" << primary_key->value();
    std::cout << ss.str() << std::endl;

    // 解析SQL语句和绑定参数与结果数据对象
    if (stmt.prepare(ss.str()) != 0) throw OrmException("prepare failed");
    if (stmt.param_count() != (fields.size() - 1))
      throw OrmException("param count not equal");
    std::vector<MYSQL_BIND> params(stmt.param_count());
    std::memset(params.data(), 0, sizeof(MYSQL_BIND) * params.size());
    for (auto i = 0, j = 0; i < fields.size(); ++i) {
      if (primary_key == fields[i]) continue;
      fields[i]->to_param(params[j++]);
    }
    if (stmt.bind_param(params.data()) != 0)
      throw OrmException("bind param failed");

    if (stmt.execute() != 0) {
      throw OrmException(stmt.error_str());
    }
    return true;
  }
  return false;
}

bool Model::remove() {
  auto primary_key = this->primary_key();
  if (primary_key == nullptr) throw OrmException("not primary key");
  if (primary_key->is_null()) return false;
  // 构建SQL语句
  Statment stmt(driver_);
  std::stringstream ss;
  ss << "DELETE FROM `" << table_name() << "` WHERE `" << primary_key->name()
     << "`=" << primary_key->value();
  std::cout << ss.str() << std::endl;

  // 解析SQL语句和绑定参数与结果数据对象
  if (stmt.prepare(ss.str()) != 0) throw OrmException("prepare failed");
  if (stmt.execute() != 0) {
    throw OrmException(stmt.error_str());
  }
  return true;
}

bool Model::update(std::vector<std::string_view> names) {
  auto primary_key = this->primary_key();
  if (primary_key == nullptr) throw OrmException("not primary key");
  if (primary_key->is_null()) return false;

  // update
  const std::vector<const FieldBase*> fields = this->fields();
  if (fields.empty()) throw OrmException("fields is empty");
  if (names.empty()) {
    for (const auto& field : fields) {
      names.push_back(field->name());
    }
  }

  // 构建SQL语句
  Statment stmt(driver_);
  std::stringstream ss;
  ss << "UPDATE `" << table_name() << "` SET `" << names[0] << "`=?";
  for (auto i = 1; i < names.size(); ++i) {
    ss << ",`" << names[i] << "`=?";
  }
  ss << " WHERE `" << primary_key->name() << "`=" << primary_key->value();
  std::cout << ss.str() << std::endl;

  // 解析SQL语句和绑定参数与结果数据对象
  if (stmt.prepare(ss.str()) != 0) throw OrmException("prepare failed");
  if (stmt.param_count() > fields.size())
    throw OrmException("param count error");
  std::vector<MYSQL_BIND> params(stmt.param_count());
  std::memset(params.data(), 0, sizeof(MYSQL_BIND) * params.size());
  for (auto i = 0; i < fields.size(); ++i) {
    auto iter = std::find_if(begin(names), end(names),
                             [&](const std::string_view& name) {
                               return name.compare(fields[i]->name()) == 0;
                             });
    if (iter != end(names)) {
      fields[i]->to_result(params[std::distance(begin(names), iter)]);
    }
  }
  if (stmt.bind_param(params.data()) != 0)
    throw OrmException("bind param failed");

  if (stmt.execute() != 0) {
    throw OrmException(stmt.error_str());
  }
  return true;
}

std::ostream& Model::operator>>(std::ostream& out) const {
  out << table_name() << std::endl;
  for (auto field : fields()) {
    const FieldBase& field_base = *field;
    out << "[" << field->name() << "]: " << field_base << std::endl;
  }
  return out;
}

std::ostream& operator<<(std::ostream& out, const Model& model) {
  model >> out;
  return out;
}
