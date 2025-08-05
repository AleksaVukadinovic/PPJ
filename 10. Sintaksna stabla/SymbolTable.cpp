#include "SymbolTable.hpp"

SymbolTable::SymbolTable(){};
SymbolTable::SymbolTable(const SymbolTable &st) {
  for (auto pair : st._variables)
    _variables[pair.first] = pair.second->clone();
}
SymbolTable::~SymbolTable() {}

SymbolTable &SymbolTable::operator=(const SymbolTable &st) {
  if (this == &st)
    return *this;

  for (auto it = _variables.begin(); it != _variables.end(); it++)
    delete it->second;
  _variables.clear();

  for (auto it = st._variables.begin(); it != st._variables.end(); it++)
    _variables[it->first] = it->second->clone();

  return *this;
}

bool SymbolTable::isDefined(const std::string &s) const {
  auto it = _variables.find(s);
  return it != _variables.end();
}

void SymbolTable::addVariable(const std::string &s, const Function *f) {
  if (isDefined(s)) {
    std::cerr << "Promenljiva je vec definisana" << std::endl;
    exit(EXIT_FAILURE);
  }
  _variables[s] = f->clone();
}

double SymbolTable::getValue(const std::string &s, const double x) const {
  if (!isDefined(s)) {
    std::cerr << "Promenljiva nije definisana" << std::endl;
    exit(EXIT_FAILURE);
  }

  auto it = _variables.find(s);
  return it->second->value(x);
}

Function *SymbolTable::getVariable(const std::string &s) const {
  if (!isDefined(s)) {
    std::cerr << "Promenljiva nije definisana" << std::endl;
    exit(EXIT_FAILURE);
  }
  auto it = _variables.find(s);
  return it->second;
}