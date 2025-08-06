#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <exception>
#include <iostream>
#include <map>

class SymbolTable {
private:
  std::map<std::string, int> _variables;

public:
  void addVariable(const std::string &name, const int value);
  int getValue(const std::string &name) const;
};

#endif
