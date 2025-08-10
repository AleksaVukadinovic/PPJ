#include "Type.hpp"

std::ostream &operator<<(std::ostream &s, const Type *t) {
  t->show(s);
  return s;
}

IntType::IntType(int value) : _value(value) {}

int IntType::getInt() const { return _value; }
double IntType::getDouble() const { return _value; }
std::string IntType::getString() const { return std::to_string(_value); }
void IntType::show(std::ostream &s) const { s << _value; }
Type *IntType::clone() const { return new IntType(*this); }
std::string IntType::getType() const { return "int"; }

DoubleType::DoubleType(double value) : _value(value) {}

int DoubleType::getInt() const { return (int)_value; }
double DoubleType::getDouble() const { return _value; }
std::string DoubleType::getString() const { return std::to_string(_value); }
void DoubleType::show(std::ostream &s) const { s << _value; }
Type *DoubleType::clone() const { return new DoubleType(*this); }
std::string DoubleType::getType() const { return "double"; }

StringType::StringType(const std::string &value) : _value(value) {}

int StringType::getInt() const { return std::stoi(_value); }
double StringType::getDouble() const { return std::stod(_value); }
std::string StringType::getString() const { return _value; }
void StringType::show(std::ostream &s) const { s << "\"" << _value << "\""; }
Type *StringType::clone() const { return new StringType(*this); }
std::string StringType::getType() const { return "string"; }
