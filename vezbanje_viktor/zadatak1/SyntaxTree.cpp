#include "SyntaxTree.hpp"

extern std::map<std::string, double> promenljive;

double Constant::value() const {
    return _val;
}

Expression* Constant::clone() const {
    return new Constant(*this);
}

double Variable::value() const {
    if (promenljive.find(_name) == promenljive.end())
        throw new std::invalid_argument("Promenljiva nije definisana");
    return promenljive[_name];
}

Expression* Variable::clone() const {
    return new Variable(*this);
}

BinaryOperator::~BinaryOperator() {
    delete _levi;
    delete _desni;
}

double Addition::value() const {
    return _levi->value() + _desni->value();
}

Expression* Addition::clone() const {
    return new Addition(*this);
}

double Subtraction::value() const {
    return _levi->value() - _desni->value();
}

Expression* Subtraction::clone() const {
    return new Subtraction(*this);
}

double Multiplication::value() const {
    return _levi->value() * _desni->value();
}

Expression* Multiplication::clone() const {
    return new Multiplication(*this);
}

double Division::value() const {
    return _levi->value() / _desni->value();
}

Expression* Division::clone() const {
    return new Division(*this);
}

PrintCommand::~PrintCommand() {
    delete _exp;
}

void PrintCommand::execute() const {
    std::cout << _exp->value() << std::endl;
}

DefCommand::~DefCommand() {
    delete _exp;
}

void DefCommand::execute() const {
    if(promenljive.find(_name) == promenljive.end())
        promenljive[_name] = _exp->value();
    else throw std::invalid_argument("Promenljiva je vec definisan");
}

RedefCommand::~RedefCommand() {
    delete _exp;
}

void RedefCommand::execute() const {
    if(promenljive.find(_name) != promenljive.end())
        promenljive[_name] = _exp->value();
    else throw std::invalid_argument("Promenljiva nije definisana");
}

Blok::~Blok() {
    for(int i=0; i<_coms.size(); i++)
        delete _coms[i];
}

void Blok::execute() const {
    for(int i=0; i<_coms.size(); i++)
        _coms[i]->execute();
}
