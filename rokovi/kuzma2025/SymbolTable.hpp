#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <exception>
#include <iostream>
#include <map>

class SymbolTable {
private:
  std::map<std::string, double> _variables;

public:
  SymbolTable();

  bool isDefined(const std::string &name) const;
  double getValue(const std::string &name) const;
  void addVariable(const std::string &name, const double value);
  void updateVariable(const std::string &name, const double value);
};

#endif