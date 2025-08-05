#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <exception>
#include <iostream>
#include <map>

class SymbolTable {
private:
  std::map<std::string, std::string> _variables;

public:
  bool isDefined(const std::string &name) const;
  void addValue(const std::string &name, const std::string &val);
  void updateValue(const std::string &name, const std::string &val);
  std::string getValue(const std::string &name) const;
  void printAllVariables() const;
};

#endif