#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "Type.hpp"
#include <exception>
#include <iostream>
#include <map>

class SymbolTable {
private:
  std::map<std::string, Type *> _variables;

public:
  SymbolTable();
  SymbolTable(const SymbolTable &st);
  ~SymbolTable();

  SymbolTable &operator=(const SymbolTable &st);

  bool isDefined(const std::string &name) const;
  bool defineVariable(const std::string &name, Type *value);
  bool updateVariable(const std::string &name, Type *value);
  bool deleteVariable(const std::string &name);
  Type *getValue(const std::string &name);
};

#endif