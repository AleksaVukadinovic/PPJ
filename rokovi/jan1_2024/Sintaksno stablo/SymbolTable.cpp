#include "SymbolTable.hpp"

bool SymbolTable::isDefined(const std::string& s) const {
    auto it = _variables.find(s);
    return it != _variables.end();
}
int SymbolTable::getValue(const std::string& s) const {
    if (!isDefined(s)) {
        throw new std::invalid_argument("Variable: " + s + " is not defined");
        exit(EXIT_FAILURE);
    }
    auto it = _variables.find(s);
    return it->second;
}
void SymbolTable::addValue(const std::string& s, const int val) {
    if (isDefined(s)) {
        throw new std::invalid_argument("Variable: " + s + " is already defined");
        exit(EXIT_FAILURE);
    }
    _variables[s] = val;
}
void SymbolTable::updateValue(const std::string& s, const int val) {
    if (!isDefined(s)) {
        throw new std::invalid_argument("Variable: " + s + " is not defined");
        exit(EXIT_FAILURE);
    }
    _variables[s] = val;
}
