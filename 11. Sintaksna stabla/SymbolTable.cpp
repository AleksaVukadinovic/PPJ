#include "SymbolTable.hpp"

int SymbolTable::getValue(const std::string& s) const {
    auto it = _variables.find(s);

    if (it == _variables.end())
        throw std::invalid_argument("Promenljiva nije definisana");

    return it->second;
}
void SymbolTable::defineValue(const std::string& s, int val) {
    _variables[s] = val;
}
