#include "where_utils.hxx"
#include "transform.hxx"

template <typename T>
QueryWhere new_query_where(std::string name, Op op, const T& v) {
  MYSQL_BIND bind;
  type_to_param(v, bind);
  const char* ops = nullptr;
  switch (op) {
    case Op::eq:
      ops = bind.buffer_type == MYSQL_TYPE_NULL ? "is" : "=";
      break;
    case Op::ne:
      ops = bind.buffer_type == MYSQL_TYPE_NULL ? "is not" : "!=";
      break;
    case Op::gt:
      ops = ">";
      break;
    case Op::ge:
      ops = ">=";
      break;
    case Op::lt:
      ops = "<";
      break;
    case Op::le:
      ops = "<=";
      break;
    default:
      throw std::runtime_error("op not supported");
  }
  if ((int)op > 1 && bind.buffer_type == MYSQL_TYPE_NULL)
    throw std::runtime_error("op not supported null");
  if (bind.buffer_type == MYSQL_TYPE_NULL) {
    return QueryWhere("`" + name + "` " + ops + " null", {});
  } else {
    return QueryWhere("`" + name + "` " + ops + " ?", {bind});
  }
}
