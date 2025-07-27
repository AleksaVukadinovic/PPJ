#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <iostream>
#include <map>
#include <string>

class SymbolTable {
private:
  std::map<std::string, int> _vars;

public:
  SymbolTable();
  ~SymbolTable();

  bool isDefined(const std::string &s) const;
  int getValue(const std::string &s) const;
  void addVar(const std::string &s, const int val = 0);
  void updateVar(const std::string &s, const int val);
};

#endif
