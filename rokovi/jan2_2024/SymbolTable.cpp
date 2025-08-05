#include "SymbolTable.hpp"

bool SymbolTable::isDefined(const std::string &name) const {
  return _variables.find(name) != _variables.end();
}

void SymbolTable::addValue(const std::string &name, const std::string &val) {
  if (isDefined(name))
    throw std::invalid_argument("Variable is already defined");
  _variables[name] = val;
}

void SymbolTable::updateValue(const std::string &name, const std::string &val) {
  if (!isDefined(name))
    throw std::invalid_argument("Variable is not defined");
  _variables[name] = val;
}

std::string SymbolTable::getValue(const std::string &name) const {
  if (!isDefined(name))
    throw std::invalid_argument("Variable is not defined");
  auto it = _variables.find(name);
  return it->second;
}

void SymbolTable::printAllVariables() const {
  for (auto p : _variables)
    std::cout << p.first << ": " << p.second << '\n';
  std::cout << std::endl;
}