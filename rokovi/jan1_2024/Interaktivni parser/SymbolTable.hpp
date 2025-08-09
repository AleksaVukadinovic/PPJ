#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <iostream>
#include <string>
#include <map>
#include <exception>

class SymbolTable {
private:
    std::map<std::string, int> _variables;

public:
    SymbolTable() {}

    bool isDefined(const std::string& s) const;
    int getValue(const std::string& s) const;
    void addValue(const std::string& s, const int val = 0);
    void updateValue(const std::string& s, const int val);
};

#endif
