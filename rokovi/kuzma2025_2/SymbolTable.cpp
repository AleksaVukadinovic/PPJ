#include "SymbolTable.hpp"

SymbolTable::SymbolTable() : _variables() {}
SymbolTable::SymbolTable(const SymbolTable &st) : _variables() {
  for (auto p : st._variables)
    _variables[p.first] = p.second->clone();
}
SymbolTable::~SymbolTable() {
  for (auto p : _variables)
    delete p.second;
}

SymbolTable &SymbolTable::operator=(const SymbolTable &st) {
  if (this == &st)
    return *this;

  _variables.clear();

  for (auto p : st._variables)
    _variables[p.first] = p.second->clone();

  return *this;
}

bool SymbolTable::isDefined(const std::string &name) const {
  return _variables.find(name) != _variables.end();
}
bool SymbolTable::defineVariable(const std::string &name, Type *value) {
  if (isDefined(name))
    return false;

  _variables[name] = value;
  return true;
}
bool SymbolTable::updateVariable(const std::string &name, Type *value) {
  auto it = _variables.find(name);
  if (it == _variables.end())
    return false;

  delete it->second;
  it->second = value;

  return true;
}
bool SymbolTable::deleteVariable(const std::string &name) {
  auto it = _variables.find(name);
  if (it == _variables.end())
    return false;

  delete it->second;
  _variables.erase(it);

  return true;
}
Type *SymbolTable::getValue(const std::string &name) {
  auto it = _variables.find(name);
  if (it == _variables.end())
    return nullptr;
  return it->second;
}