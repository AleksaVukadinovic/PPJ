#include "Function.hpp"

std::ostream &operator<<(std::ostream &s, const Function &f) {
  f.print(s);
  return s;
}

// Constant function

ConstantFunction::ConstantFunction(double val) { _value = val; }
ConstantFunction::ConstantFunction(const ConstantFunction &kf) {
  _value = kf._value;
}

void ConstantFunction::print(std::ostream &s) const { s << _value; }
Function *ConstantFunction::clone() const {
  return new ConstantFunction(*this);
}
double ConstantFunction::value(double x) const { return _value; }
Function *ConstantFunction::diff() const { return new ConstantFunction(0); }
Function *ConstantFunction::compose(Function *f) const { return clone(); }

// Identity function

void IdentityFunction::print(std::ostream &s) const { s << "x"; }
Function *IdentityFunction::clone() const {
  return new IdentityFunction(*this);
}
double IdentityFunction::value(double x) const { return x; }
Function *IdentityFunction::diff() const { return new ConstantFunction(1); }
Function *IdentityFunction::compose(Function *f) const { return f->clone(); }

// Binary function

BinaryFunction::BinaryFunction(const std::string &s, Function *l, Function *r)
    : _symbol(s), _left(l), _right(r) {}
BinaryFunction::~BinaryFunction() {
  delete _left;
  delete _right;
}

void BinaryFunction::print(std::ostream &s) const {
  s << (*_left) << " " << _symbol << " " << (*_right);
}

// Addition function

AdditionFunction::AdditionFunction(Function *l, Function *d)
    : BinaryFunction("+", l, d) {}
AdditionFunction::AdditionFunction(const AdditionFunction &pf)
    : BinaryFunction("+", pf._left->clone(), pf._right->clone()) {}

Function *AdditionFunction::clone() const {
  return new AdditionFunction(*this);
}
double AdditionFunction::value(double x) const {
  return _left->value(x) + _right->value(x);
}
Function *AdditionFunction::diff() const {
  return new AdditionFunction(_left->diff(), _right->diff());
}
Function *AdditionFunction::compose(Function *f) const {
  return new AdditionFunction(_left->compose(f), _right->compose(f));
}

// Subtraction function

SubtractionFunction::SubtractionFunction(Function *l, Function *d)
    : BinaryFunction("-", l, d) {}
SubtractionFunction::SubtractionFunction(const SubtractionFunction &pf)
    : BinaryFunction("-", pf._left->clone(), pf._right->clone()) {}

Function *SubtractionFunction::clone() const {
  return new SubtractionFunction(*this);
}
double SubtractionFunction::value(double x) const {
  return _left->value(x) - _right->value(x);
}
Function *SubtractionFunction::diff() const {
  return new SubtractionFunction(_left->diff(), _right->diff());
}
Function *SubtractionFunction::compose(Function *f) const {
  return new SubtractionFunction(_left->compose(f), _right->compose(f));
}

// MultiplicationFunction

MultiplicationFunction::MultiplicationFunction(Function *l, Function *d)
    : BinaryFunction("*", l, d) {}
MultiplicationFunction::MultiplicationFunction(const MultiplicationFunction &pf)
    : BinaryFunction("*", pf._left->clone(), pf._right->clone()) {}

Function *MultiplicationFunction::clone() const {
  return new MultiplicationFunction(*this);
}
double MultiplicationFunction::value(double x) const {
  return _left->value(x) * _right->value(x);
}
Function *MultiplicationFunction::diff() const {
  return new AdditionFunction(
      new MultiplicationFunction(_left->diff(), _right->clone()),
      new MultiplicationFunction(_left->clone(), _right->diff()));
}
Function *MultiplicationFunction::compose(Function *f) const {
  return new MultiplicationFunction(_left->compose(f), _right->compose(f));
}

// Division function

DivisionFunction::DivisionFunction(Function *l, Function *d)
    : BinaryFunction("/", l, d) {}
DivisionFunction::DivisionFunction(const DivisionFunction &pf)
    : BinaryFunction("/", pf._left->clone(), pf._right->clone()) {}

Function *DivisionFunction::clone() const {
  return new DivisionFunction(*this);
}
double DivisionFunction::value(double x) const {
  return _left->value(x) / _right->value(x);
}
Function *DivisionFunction::diff() const {
  return new DivisionFunction(
      new SubtractionFunction(
          new MultiplicationFunction(_left->diff(), _right->clone()),
          new MultiplicationFunction(_left->clone(), _right->diff())),
      new MultiplicationFunction(_right->clone(), _right->clone()));
}
Function *DivisionFunction::compose(Function *f) const {
  return new DivisionFunction(_left->compose(f), _right->compose(f));
}

// Unary function

UnaryFunction::UnaryFunction(const std::string &s, Function *f)
    : _name(s), _expr(f) {}
UnaryFunction::~UnaryFunction() { delete _expr; }

void UnaryFunction::print(std::ostream &s) const {
  s << _name << "(" << (*_expr) << ")";
}
ReverseFunction::ReverseFunction(Function *expr) : UnaryFunction("-", expr) {}
ReverseFunction::ReverseFunction(const ReverseFunction &sf)
    : UnaryFunction("-", sf._expr->clone()) {}

// Reverse function

Function *ReverseFunction::clone() const { return new ReverseFunction(*this); }
double ReverseFunction::value(double x) const { return -_expr->value(x); }
Function *ReverseFunction::diff() const {
  return new ReverseFunction(_expr->diff());
}
Function *ReverseFunction::compose(Function *f) const {
  return new ReverseFunction(_expr->compose(f));
}

// Sin function

SinFunction::SinFunction(Function *expr) : UnaryFunction("sin", expr) {}
SinFunction::SinFunction(const SinFunction &sf)
    : UnaryFunction("sin", sf._expr->clone()) {}

Function *SinFunction::clone() const { return new SinFunction(*this); }
double SinFunction::value(double x) const { return sin(_expr->value(x)); }
Function *SinFunction::diff() const {
  return new MultiplicationFunction(_expr->diff(),
                                    new CosFunction(_expr->clone()));
}
Function *SinFunction::compose(Function *f) const {
  return new SinFunction(_expr->compose(f));
}

// Cos function

CosFunction::CosFunction(Function *expr) : UnaryFunction("cos", expr) {}
CosFunction::CosFunction(const CosFunction &sf)
    : UnaryFunction("cos", sf._expr->clone()) {}

Function *CosFunction::clone() const { return new CosFunction(*this); }
double CosFunction::value(double x) const { return cos(_expr->value(x)); }
Function *CosFunction::diff() const {
  return new MultiplicationFunction(
      new ConstantFunction(-1),
      new MultiplicationFunction(_expr->diff(),
                                 new SinFunction(_expr->clone())));
}
Function *CosFunction::compose(Function *f) const {
  return new CosFunction(_expr->compose(f));
}

// Tan function

TanFunction::TanFunction(Function *expr) : UnaryFunction("tan", expr) {}
TanFunction::TanFunction(const TanFunction &sf)
    : UnaryFunction("tan", sf._expr->clone()) {}

Function *TanFunction::clone() const { return new TanFunction(*this); }
double TanFunction::value(double x) const { return tan(_expr->value(x)); }
Function *TanFunction::diff() const {
  return new DivisionFunction(
      new ConstantFunction(1),
      new MultiplicationFunction(new CosFunction(_expr->clone()),
                                 new CosFunction(_expr->clone())));
}
Function *TanFunction::compose(Function *f) const {
  return new TanFunction(_expr->compose(f));
}

// Cot function

CotFunction::CotFunction(Function *expr) : UnaryFunction("cot", expr) {}
CotFunction::CotFunction(const CotFunction &sf)
    : UnaryFunction("cot", sf._expr->clone()) {}

Function *CotFunction::clone() const { return new CotFunction(*this); }
double CotFunction::value(double x) const { return 1 / tan(_expr->value(x)); }
Function *CotFunction::diff() const {
  return new DivisionFunction(
      new ConstantFunction(-1),
      new MultiplicationFunction(new SinFunction(_expr->clone()),
                                 new SinFunction(_expr->clone())));
}
Function *CotFunction::compose(Function *f) const {
  return new CotFunction(_expr->compose(f));
}

// Exp function

ExpFunction::ExpFunction(Function *expr) : UnaryFunction("exp", expr) {}
ExpFunction::ExpFunction(const ExpFunction &sf)
    : UnaryFunction("exp", sf._expr->clone()) {}

Function *ExpFunction::clone() const { return new ExpFunction(*this); }
double ExpFunction::value(double x) const { return exp(_expr->value(x)); }
Function *ExpFunction::diff() const {
  return new MultiplicationFunction(_expr->diff(),
                                    new ExpFunction(_expr->clone()));
}
Function *ExpFunction::compose(Function *f) const {
  return new ExpFunction(_expr->compose(f));
}

// Log function

LogFunction::LogFunction(Function *expr) : UnaryFunction("log", expr) {}
LogFunction::LogFunction(const LogFunction &sf)
    : UnaryFunction("log", sf._expr->clone()) {}

Function *LogFunction::clone() const { return new LogFunction(*this); }
double LogFunction::value(double x) const { return log(_expr->value(x)); }
Function *LogFunction::diff() const {
  return new DivisionFunction(_expr->diff(), new LogFunction(_expr->clone()));
}
Function *LogFunction::compose(Function *f) const {

  return new LogFunction(_expr->compose(f));
}

// Pow function

PowFunction::PowFunction(Function *expr, double step)
    : UnaryFunction("pow", expr) {
  _pow = step;
}
PowFunction::PowFunction(const PowFunction &sf)
    : UnaryFunction("pow", sf._expr->clone()) {
  _pow = sf._pow;
}

Function *PowFunction::clone() const { return new PowFunction(*this); }
double PowFunction::value(double x) const { return pow(_expr->value(x), _pow); }
Function *PowFunction::diff() const {
  return new MultiplicationFunction(
      new MultiplicationFunction(new ConstantFunction(_pow), _expr->diff()),
      new PowFunction(_expr->clone(), _pow - 1));
}
Function *PowFunction::compose(Function *f) const {

  return new PowFunction(_expr->compose(f), _pow);
}

// Sqrt function

SqrtFunction::SqrtFunction(Function *expr) : UnaryFunction("sqrt", expr) {}
SqrtFunction::SqrtFunction(const SqrtFunction &sf)
    : UnaryFunction("sqrt", sf._expr->clone()) {}

Function *SqrtFunction::clone() const { return new SqrtFunction(*this); }
double SqrtFunction::value(double x) const { return sqrt(_expr->value(x)); }
Function *SqrtFunction::diff() const {
  return new DivisionFunction(
      _expr->diff(),
      new MultiplicationFunction(new ConstantFunction(2),
                                 new SqrtFunction(_expr->clone())));
}
Function *SqrtFunction::compose(Function *f) const {
  return new SqrtFunction(_expr->compose(f));
}