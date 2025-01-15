#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include <iostream>
#include <cstdlib>
#include <map>
#include <exception>
#include <vector>

class Expression {
public:
    // virtual - mora da se nasledi
    // const - nece menjati polja objekta
    // = 0 ne moze da se instancira objekat te klase
    virtual double value() const = 0;
    virtual Expression* clone() const = 0;
    virtual ~Expression() {}
};

class Constant : public Expression {
private:
    double _val;

public:
    Constant(double val) : _val(val) {}
    Constant(const Constant& c) : _val(c._val) {}

    double value() const;
    Expression* clone() const;
};

class Variable : public Expression {
private:
    std::string _name;
public:
    Variable(std::string name) : _name(name) {}
    Variable(const Variable& c) : _name(c._name) {}

    double value() const;
    Expression* clone() const;
};

class BinaryOperator : public Expression {
protected:
    Expression* _levi;
    Expression* _desni;

public:
    BinaryOperator(Expression* levi, Expression* desni) : _levi(levi->clone()), _desni(desni->clone()) {}
    ~BinaryOperator();

    virtual double value() const = 0;
    virtual Expression* clone() const = 0;
};

class Addition : public BinaryOperator {
public:
    Addition(Expression* levi, Expression* desni) : BinaryOperator(levi, desni) {}
    Addition(const Addition& add) : BinaryOperator(add._levi, add._desni) {}

    double value() const;
    Expression* clone() const;
};

class Subtraction : public BinaryOperator {
public:
    Subtraction(Expression* levi, Expression* desni) : BinaryOperator(levi, desni) {}
    Subtraction(const Subtraction& sub) : BinaryOperator(sub._levi, sub._desni) {}

    double value() const;
    Expression* clone() const;
};

class Multiplication : public BinaryOperator {
public:
    Multiplication(Expression* levi, Expression* desni) : BinaryOperator(levi, desni) {}
    Multiplication(const Multiplication& mul) : BinaryOperator(mul._levi, mul._desni) {}

    double value() const;
    Expression* clone() const;
};

class Division : public BinaryOperator {
public:
    Division(Expression* levi, Expression* desni) : BinaryOperator(levi, desni) {}
    Division(const Division& div) : BinaryOperator(div._levi, div._desni) {}

    double value() const;
    Expression* clone() const;
};

class Command {
public:
    virtual ~Command() {}
    virtual void execute() const = 0;
};

class PrintCommand : public Command {
private:
    Expression* _exp;

public:
    PrintCommand(Expression* exp) : _exp(exp->clone()) {}
    ~PrintCommand();

    void execute() const;
};

class DefCommand : public Command {
private:
    std::string _name;
    Expression* _exp;

public:
    DefCommand(std::string name, Expression* exp) : _name(name), _exp(exp->clone()) {}
    DefCommand(std::string name) : _name(name), _exp(new Constant(0)) {}
    ~DefCommand();

    void execute() const;
};

class RedefCommand : public Command {
private:
    std::string _name;
    Expression* _exp;

public:
    RedefCommand(std::string name, Expression* exp) : _name(name), _exp(exp->clone()) {}
    ~RedefCommand();

    void execute() const;
};

class Blok : public Command {
private:
    std::vector<Command*> _coms;

public:
    Blok(std::vector<Command*> coms) : _coms(coms) {}
    ~Blok();

    void execute() const;
};

#endif

