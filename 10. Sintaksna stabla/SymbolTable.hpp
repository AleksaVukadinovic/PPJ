#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "Function.hpp"
#include <iostream>
#include <map>

class SymbolTable {
private:
  std::map<std::string, Function *> _variables;

public:
  SymbolTable();
  SymbolTable(const SymbolTable &st);
  ~SymbolTable();

  SymbolTable &operator=(const SymbolTable &st);

  bool isDefined(const std::string &s) const;
  void addVariable(const std::string &s, const Function *f);
  double getValue(const std::string &s, const double x) const;
  Function *getVariable(const std::string &s) const;
};

#endif