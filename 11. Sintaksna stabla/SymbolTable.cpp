#include "SymbolTable.hpp"

void SymbolTable::addVariable(const std::string &name, const int value) {
  _variables[name] = value;
}

int SymbolTable::getValue(const std::string &name) const {
  auto it = _variables.find(name);

  if (it == _variables.end())
    throw new std::invalid_argument("Variable" + name + "is not defined");

  return it->second;
}
