#include "SymbolTable.hpp"

SymbolTable::SymbolTable() {}

bool SymbolTable::isDefined(const std::string &name) const {
  auto it = _variables.find(name);
  return it != _variables.end();
}
double SymbolTable::getValue(const std::string &name) const {
  if (!isDefined(name)) {
    throw std::invalid_argument("Variable is not defined");
    exit(EXIT_FAILURE);
  }
  auto it = _variables.find(name);
  return it->second;
}
void SymbolTable::addVariable(const std::string &name, const double value) {
  if (isDefined(name)) {
    throw std::invalid_argument("Variable is already defined");
    exit(EXIT_FAILURE);
  }
  _variables[name] = value;
}
void SymbolTable::updateVariable(const std::string &name, const double value) {
  if (!isDefined(name)) {
    throw std::invalid_argument("Variable is not defined");
    exit(EXIT_FAILURE);
  }
  _variables[name] = value;
}