#include "SymbolTable.hpp"

SymbolTable::SymbolTable() : _vars() {}
SymbolTable::~SymbolTable() {}

bool SymbolTable::isDefined(const std::string &s) const {
  return _vars.find(s) != _vars.end();
}

int SymbolTable::getValue(const std::string &s) const {
  if (!isDefined(s))
    std::cerr << "Variable " << s << " is not defined\n";
  auto it = _vars.find(s);
  return it->second;
}

void SymbolTable::addVar(const std::string &s, const int val) {
  if (isDefined(s))
    std::cerr << "Variable " << s << " is already defined\n";
  _vars[s] = val;
}

void SymbolTable::updateVar(const std::string &s, const int val) {
  if (!isDefined(s))
    std::cerr << "Variable " << s << " is not defined\n";
  _vars[s] = val;
}
