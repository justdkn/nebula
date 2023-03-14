#include <orm/field_base.hxx>

FieldBase::FieldBase(const char* name) : name_(name) {
}

FieldBase::~FieldBase() {
}

const char* FieldBase::name() const {
  return name_;
}

std::ostream& operator<<(std::ostream& out, const FieldBase& field) {
  field >> out;
  return out;
}