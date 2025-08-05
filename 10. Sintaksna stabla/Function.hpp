#ifndef FUNKCIJE_H
#define FUNKCIJE_H

#include <cmath>
#include <iostream>

class Function {
public:
  virtual ~Function() {}

  virtual void print(std::ostream &s) const = 0;
  virtual Function *clone() const = 0;
  virtual double value(double x) const = 0;
  virtual Function *diff() const = 0;
  virtual Function *compose(Function *f) const = 0;
};

std::ostream &operator<<(std::ostream &s, const Function &f);

class ConstantFunction : public Function {
private:
  double _value;

public:
  ConstantFunction(double val);
  ConstantFunction(const ConstantFunction &kf);

  virtual void print(std::ostream &s) const;
  virtual Function *clone() const;
  virtual double value(double x) const;
  virtual Function *diff() const;
  virtual Function *compose(Function *f) const;
};

class IdentityFunction : public Function {
public:
  virtual void print(std::ostream &s) const;
  virtual Function *clone() const;
  virtual double value(double x) const;
  virtual Function *diff() const;
  virtual Function *compose(Function *f) const;
};

class BinaryFunction : public Function {
protected:
  std::string _symbol;
  Function *_left;
  Function *_right;

public:
  BinaryFunction(const std::string &s, Function *l, Function *r);
  ~BinaryFunction();

  virtual void print(std::ostream &s) const;
  virtual Function *clone() const = 0;
  virtual double value(double x) const = 0;
  virtual Function *diff() const = 0;
  virtual Function *compose(Function *f) const = 0;
};

class AdditionFunction : public BinaryFunction {
public:
  AdditionFunction(Function *l, Function *d);
  AdditionFunction(const AdditionFunction &pf);

  virtual Function *clone() const;
  virtual double value(double x) const;
  virtual Function *diff() const;
  virtual Function *compose(Function *f) const;
};

class SubtractionFunction : public BinaryFunction {
public:
  SubtractionFunction(Function *l, Function *d);
  SubtractionFunction(const SubtractionFunction &pf);

  virtual Function *clone() const;
  virtual double value(double x) const;
  virtual Function *diff() const;
  virtual Function *compose(Function *f) const;
};

class MultiplicationFunction : public BinaryFunction {
public:
  MultiplicationFunction(Function *l, Function *d);
  MultiplicationFunction(const MultiplicationFunction &pf);

  virtual Function *clone() const;
  virtual double value(double x) const;
  virtual Function *diff() const;
  virtual Function *compose(Function *f) const;
};

class DivisionFunction : public BinaryFunction {
public:
  DivisionFunction(Function *l, Function *d);
  DivisionFunction(const DivisionFunction &pf);

  virtual Function *clone() const;
  virtual double value(double x) const;
  virtual Function *diff() const;
  virtual Function *compose(Function *f) const;
};

class UnaryFunction : public Function {
protected:
  std::string _name;
  Function *_expr;

public:
  UnaryFunction(const std::string &s, Function *f);
  ~UnaryFunction();

  virtual void print(std::ostream &s) const;
  virtual Function *clone() const = 0;
  virtual double value(double x) const = 0;
  virtual Function *diff() const = 0;
  virtual Function *compose(Function *f) const = 0;
};

class ReverseFunction : public UnaryFunction {
public:
  ReverseFunction(Function *expr);
  ReverseFunction(const ReverseFunction &sf);

  virtual Function *clone() const;
  virtual double value(double x) const;
  virtual Function *diff() const;
  virtual Function *compose(Function *f) const;
};

class SinFunction : public UnaryFunction {
public:
  SinFunction(Function *expr);
  SinFunction(const SinFunction &sf);

  virtual Function *clone() const;
  virtual double value(double x) const;
  virtual Function *diff() const;
  virtual Function *compose(Function *f) const;
};

class CosFunction : public UnaryFunction {
public:
  CosFunction(Function *expr);
  CosFunction(const CosFunction &sf);

  virtual Function *clone() const;
  virtual double value(double x) const;
  virtual Function *diff() const;
  virtual Function *compose(Function *f) const;
};

class TanFunction : public UnaryFunction {
public:
  TanFunction(Function *expr);
  TanFunction(const TanFunction &sf);

  virtual Function *clone() const;
  virtual double value(double x) const;
  virtual Function *diff() const;
  virtual Function *compose(Function *f) const;
};

class CotFunction : public UnaryFunction {
public:
  CotFunction(Function *expr);
  CotFunction(const CotFunction &sf);

  virtual Function *clone() const;
  virtual double value(double x) const;
  virtual Function *diff() const;
  virtual Function *compose(Function *f) const;
};

class ExpFunction : public UnaryFunction {
public:
  ExpFunction(Function *expr);
  ExpFunction(const ExpFunction &sf);

  virtual Function *clone() const;
  virtual double value(double x) const;
  virtual Function *diff() const;
  virtual Function *compose(Function *f) const;
};

class LogFunction : public UnaryFunction {
public:
  LogFunction(Function *expr);
  LogFunction(const LogFunction &sf);

  virtual Function *clone() const;
  virtual double value(double x) const;
  virtual Function *diff() const;
  virtual Function *compose(Function *f) const;
};

class PowFunction : public UnaryFunction {
private:
  double _pow;

public:
  PowFunction(Function *expr, double step);
  PowFunction(const PowFunction &sf);

  virtual Function *clone() const;
  virtual double value(double x) const;
  virtual Function *diff() const;
  virtual Function *compose(Function *f) const;
};

class SqrtFunction : public UnaryFunction {
public:
  SqrtFunction(Function *expr);
  SqrtFunction(const SqrtFunction &sf);

  virtual Function *clone() const;
  virtual double value(double x) const;
  virtual Function *diff() const;
  virtual Function *compose(Function *f) const;
};

#endif