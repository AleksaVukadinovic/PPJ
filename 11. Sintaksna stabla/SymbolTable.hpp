#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <iostream>
#include <map>
#include <string>

class SymbolTable {
private:
    std::map<std::string, int> _variables;

public:
    int getValue(const std::string& s) const;
    void defineValue(const std::string& s, const int x);
};

#endif
