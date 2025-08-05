#include "SyntaxTree.hpp"

std::ostream &operator<<(std::ostream &s, const SyntaxTreeNode &st) {
  st.print(s);
  return s;
}

// Constant Node

ConstantNode::ConstantNode(double val) { _value = val; }
ConstantNode::ConstantNode(const ConstantNode &cn) { _value = cn._value; }

void ConstantNode::print(std::ostream &s) const { s << _value; }
Function *ConstantNode::interpret(SymbolTable &fs) const {
  return new ConstantFunction(_value);
}
double ConstantNode::calculate(SymbolTable &fs, double x) const {
  return _value;
}
SyntaxTreeNode *ConstantNode::clone() const { return new ConstantNode(*this); }

// Constant Function Node

ConstantFunctionNode::ConstantFunctionNode(double val) { _value = val; }
ConstantFunctionNode::ConstantFunctionNode(const ConstantFunctionNode &cn) {
  _value = cn._value;
}

void ConstantFunctionNode::print(std::ostream &s) const { s << _value; }
Function *ConstantFunctionNode::interpret(SymbolTable &fs) const {
  return new ConstantFunction(_value);
}
double ConstantFunctionNode::calculate(SymbolTable &fs, double x) const {
  return _value;
}
SyntaxTreeNode *ConstantFunctionNode::clone() const {
  return new ConstantFunctionNode(*this);
}

// Identifier Node

IdentifierNode::IdentifierNode(const std::string &s) { _name = s; }
IdentifierNode::IdentifierNode(const IdentifierNode &cn) { _name = cn._name; }

void IdentifierNode::print(std::ostream &s) const { s << _name; }
Function *IdentifierNode::interpret(SymbolTable &fs) const {
  Function *f = fs.getVariable(_name);
  if (f == nullptr)
    throw std::invalid_argument("Variable not defined");
  return f;
}
double IdentifierNode::calculate(SymbolTable &fs, double x) const {
  Function *f = fs.getVariable(_name);
  if (f == nullptr)
    throw std::invalid_argument("Variable not defined");
  double rez = f->value(x);
  delete f;
  return rez;
}
SyntaxTreeNode *IdentifierNode::clone() const {
  return new IdentifierNode(*this);
}

// Identifer Function Node

void IdentityFunctionNode::print(std::ostream &s) const { s << "x"; }
Function *IdentityFunctionNode::interpret(SymbolTable &fs) const {
  return new IdentityFunction();
}
double IdentityFunctionNode::calculate(SymbolTable &fs, double x) const {

  return x;
}
SyntaxTreeNode *IdentityFunctionNode::clone() const {
  return new IdentityFunctionNode(*this);
}

// Function Node

FunctionNode::FunctionNode(SyntaxTreeNode *expr) { _expr = expr; }
FunctionNode::~FunctionNode() { delete _expr; }

// Composition Node

CompositionNode::CompositionNode(const std::string &s, SyntaxTreeNode *expr)
    : FunctionNode(expr) {
  _name = s;
}
CompositionNode::CompositionNode(const CompositionNode &cn)
    : FunctionNode(cn._expr->clone()) {
  _name = cn._name;
}

void CompositionNode::print(std::ostream &s) const {
  s << _name << "(" << (*_expr) << ")";
}
Function *CompositionNode::interpret(SymbolTable &fs) const {
  Function *f = fs.getVariable(_name);
  if (f == nullptr)
    throw std::invalid_argument("Variable not defined");
  Function *rez = f->compose(_expr->interpret(fs));
  delete f;
  return rez;
}
double CompositionNode::calculate(SymbolTable &fs, double x) const {
  Function *f = fs.getVariable(_name);
  if (f == nullptr)
    throw std::invalid_argument("Variable not defined");
  double rez = f->value(_expr->interpret(fs)->value(x));
  delete f;
  return rez;
}
SyntaxTreeNode *CompositionNode::clone() const {
  return new CompositionNode(*this);
}

// Pow Node

PowNode::PowNode(SyntaxTreeNode *expr, SyntaxTreeNode *step)
    : FunctionNode(expr) {
  _stepen = step;
}
PowNode::PowNode(const PowNode &cn) : FunctionNode(cn._expr->clone()) {
  _stepen = cn._stepen->clone();
}
PowNode::~PowNode() { delete _stepen; }

void PowNode::print(std::ostream &s) const {
  s << "pow(" << (*_expr) << "," << (*_stepen) << ")";
}
Function *PowNode::interpret(SymbolTable &fs) const {
  return new PowFunction(_expr->interpret(fs),
                         _stepen->interpret(fs)->value(0));
}
double PowNode::calculate(SymbolTable &fs, double x) const {
  return pow(_expr->interpret(fs)->value(x), _stepen->interpret(fs)->value(x));
}
SyntaxTreeNode *PowNode::clone() const { return new PowNode(*this); }

// Sin Node

SinNode::SinNode(SyntaxTreeNode *expr) : FunctionNode(expr) {}
SinNode::SinNode(const SinNode &cn) : FunctionNode(cn._expr->clone()) {}

void SinNode::print(std::ostream &s) const { s << "sin(" << (*_expr) << ")"; }
Function *SinNode::interpret(SymbolTable &fs) const {
  return new SinFunction(_expr->interpret(fs));
}
double SinNode::calculate(SymbolTable &fs, double x) const {
  return sin(_expr->interpret(fs)->value(x));
}
SyntaxTreeNode *SinNode::clone() const { return new SinNode(*this); }

// Cos Node

CosNode::CosNode(SyntaxTreeNode *expr) : FunctionNode(expr) {}
CosNode::CosNode(const CosNode &cn) : FunctionNode(cn._expr->clone()) {}

void CosNode::print(std::ostream &s) const { s << "cos(" << (*_expr) << ")"; }
Function *CosNode::interpret(SymbolTable &fs) const {
  return new CosFunction(_expr->interpret(fs));
}
double CosNode::calculate(SymbolTable &fs, double x) const {
  return cos(_expr->interpret(fs)->value(x));
}
SyntaxTreeNode *CosNode::clone() const { return new CosNode(*this); }

// Tan Node

TanNode::TanNode(SyntaxTreeNode *expr) : FunctionNode(expr) {}
TanNode::TanNode(const TanNode &cn) : FunctionNode(cn._expr->clone()) {}

void TanNode::print(std::ostream &s) const { s << "tan(" << (*_expr) << ")"; }
Function *TanNode::interpret(SymbolTable &fs) const {
  return new TanFunction(_expr->interpret(fs));
}
double TanNode::calculate(SymbolTable &fs, double x) const {
  return tan(_expr->interpret(fs)->value(x));
}
SyntaxTreeNode *TanNode::clone() const { return new TanNode(*this); }

// Cot Node

CotNode::CotNode(SyntaxTreeNode *expr) : FunctionNode(expr) {}
CotNode::CotNode(const CotNode &cn) : FunctionNode(cn._expr->clone()) {}

void CotNode::print(std::ostream &s) const { s << "cot(" << (*_expr) << ")"; }
Function *CotNode::interpret(SymbolTable &fs) const {
  return new CotFunction(_expr->interpret(fs));
}
double CotNode::calculate(SymbolTable &fs, double x) const {
  return 1 / tan(_expr->interpret(fs)->value(x));
}
SyntaxTreeNode *CotNode::clone() const { return new CotNode(*this); }

// Log Node

LogNode::LogNode(SyntaxTreeNode *expr) : FunctionNode(expr) {}
LogNode::LogNode(const LogNode &cn) : FunctionNode(cn._expr->clone()) {}

void LogNode::print(std::ostream &s) const { s << "log(" << (*_expr) << ")"; }
Function *LogNode::interpret(SymbolTable &fs) const {
  return new LogFunction(_expr->interpret(fs));
}
double LogNode::calculate(SymbolTable &fs, double x) const {
  return log(_expr->interpret(fs)->value(x));
}
SyntaxTreeNode *LogNode::clone() const { return new LogNode(*this); }

// Exp Node

ExpNode::ExpNode(SyntaxTreeNode *expr) : FunctionNode(expr) {}
ExpNode::ExpNode(const ExpNode &cn) : FunctionNode(cn._expr->clone()) {}

void ExpNode::print(std::ostream &s) const { s << "exp(" << (*_expr) << ")"; }
Function *ExpNode::interpret(SymbolTable &fs) const {
  return new ExpFunction(_expr->interpret(fs));
}
double ExpNode::calculate(SymbolTable &fs, double x) const {
  return log(_expr->interpret(fs)->value(x));
}
SyntaxTreeNode *ExpNode::clone() const { return new ExpNode(*this); }

// Sqrt Node

SqrtNode::SqrtNode(SyntaxTreeNode *expr) : FunctionNode(expr) {}
SqrtNode::SqrtNode(const SqrtNode &cn) : FunctionNode(cn._expr->clone()) {}

void SqrtNode::print(std::ostream &s) const { s << "sqrt(" << (*_expr) << ")"; }
Function *SqrtNode::interpret(SymbolTable &fs) const {
  return new SqrtFunction(_expr->interpret(fs));
}
double SqrtNode::calculate(SymbolTable &fs, double x) const {
  return sqrt(_expr->interpret(fs)->value(x));
}
SyntaxTreeNode *SqrtNode::clone() const { return new SqrtNode(*this); }

// Reverse Node

ReverseNode::ReverseNode(SyntaxTreeNode *expr) : FunctionNode(expr) {}
ReverseNode::ReverseNode(const ReverseNode &cn)
    : FunctionNode(cn._expr->clone()) {}

void ReverseNode::print(std::ostream &s) const { s << "-(" << (*_expr) << ")"; }
Function *ReverseNode::interpret(SymbolTable &fs) const {
  return new ReverseFunction(_expr->interpret(fs));
}
double ReverseNode::calculate(SymbolTable &fs, double x) const {
  return -(_expr->interpret(fs)->value(x));
}
SyntaxTreeNode *ReverseNode::clone() const { return new ReverseNode(*this); }

// Diff Node

DiffNode::DiffNode(SyntaxTreeNode *expr) : FunctionNode(expr) {}
DiffNode::DiffNode(const DiffNode &cn) : FunctionNode(cn._expr->clone()) {}

void DiffNode::print(std::ostream &s) const { s << "(" << (*_expr) << ")'"; }
Function *DiffNode::interpret(SymbolTable &fs) const {
  return _expr->interpret(fs)->diff();
}
double DiffNode::calculate(SymbolTable &fs, double x) const {
  Function *f = _expr->interpret(fs)->diff();
  double rez = f->value(x);
  delete f;
  return rez;
}
SyntaxTreeNode *DiffNode::clone() const { return new DiffNode(*this); }

// Value Node

ValueNode::ValueNode(SyntaxTreeNode *expr, SyntaxTreeNode *x)
    : FunctionNode(expr) {
  _x = x;
}
ValueNode::ValueNode(const ValueNode &cn) : FunctionNode(cn._expr->clone()) {
  _x = cn._x->clone();
}
ValueNode::~ValueNode() { delete _x; }

void ValueNode::print(std::ostream &s) const {
  s << (*_expr) << "[" << (*_x) << "]";
}
Function *ValueNode::interpret(SymbolTable &fs) const {

  return new ConstantFunction(
      _expr->interpret(fs)->value(_x->interpret(fs)->value(0)));
}
double ValueNode::calculate(SymbolTable &fs, double x) const {

  return _expr->interpret(fs)->value(_x->interpret(fs)->value(x));
}
SyntaxTreeNode *ValueNode::clone() const { return new ValueNode(*this); }

// Binary Node

BinaryNode::BinaryNode(const std::string _s, SyntaxTreeNode *l,
                       SyntaxTreeNode *r) {
  _left = l;
  _right = r;
  _symbol = _s;
}
BinaryNode::BinaryNode(const BinaryNode &bo) {
  _left = bo._left->clone();
  _right = bo._right->clone();
  _symbol = bo._symbol;
}
BinaryNode::~BinaryNode() {
  delete _left;
  delete _right;
}

void BinaryNode::print(std::ostream &s) const {

  s << (*_left) << _symbol << (*_right);
}
Function *BinaryNode::interpret(SymbolTable &fs) const {

  if (_symbol == "+") {
    return new AdditionFunction(_left->interpret(fs), _right->interpret(fs));
  } else if (_symbol == "-") {
    return new SubtractionFunction(_left->interpret(fs), _right->interpret(fs));
  } else if (_symbol == "*") {
    return new MultiplicationFunction(_left->interpret(fs),
                                      _right->interpret(fs));
  } else if (_symbol == "/") {
    return new DivisionFunction(_left->interpret(fs), _right->interpret(fs));
  }
  return nullptr;
}
double BinaryNode::calculate(SymbolTable &fs, double x) const {

  if (_symbol == "+") {
    return _left->interpret(fs)->value(x) + _right->interpret(fs)->value(x);
  } else if (_symbol == "-") {
    return _left->interpret(fs)->value(x) - _right->interpret(fs)->value(x);
  } else if (_symbol == "*") {
    return _left->interpret(fs)->value(x) * _right->interpret(fs)->value(x);
  } else if (_symbol == "/") {
    return _left->interpret(fs)->value(x) / _right->interpret(fs)->value(x);
  }
  return 0;
}
SyntaxTreeNode *BinaryNode::clone() const { return new BinaryNode(*this); }
AssignmentNode::AssignmentNode(const std::string &s, SyntaxTreeNode *expr) {
  _name = s;
  _expr = expr;
}

// Assignment Node

AssignmentNode::AssignmentNode(const AssignmentNode &an) {
  _name = an._name;
  _expr = an._expr->clone();
}
AssignmentNode::~AssignmentNode() { delete _expr; }

void AssignmentNode::print(std::ostream &s) const {
  s << _name << " = " << (*_expr) << std::endl;
}
Function *AssignmentNode::interpret(SymbolTable &fs) const {

  Function *f = _expr->interpret(fs);
  fs.addVariable(_name, f);

  return f;
}
double AssignmentNode::calculate(SymbolTable &fs, double x) const {

  Function *f = _expr->interpret(fs);
  fs.addVariable(_name, f);

  return f->value(x);
}
SyntaxTreeNode *AssignmentNode::clone() const {

  return new AssignmentNode(*this);
}

// Print Node

PrintNode::PrintNode(SyntaxTreeNode *expr) { _expr = expr; }
PrintNode::PrintNode(const PrintNode &an) { _expr = an._expr->clone(); }
PrintNode::~PrintNode() { delete _expr; }

void PrintNode::print(std::ostream &s) const {
  s << "print(" << (*_expr) << ")";
}
Function *PrintNode::interpret(SymbolTable &fs) const {
  Function *f = _expr->interpret(fs);
  std::cout << (*f) << std::endl;
  return f;
}
double PrintNode::calculate(SymbolTable &fs, double x) const {
  Function *f = _expr->interpret(fs);
  std::cout << f->value(x) << std::endl;
  return f->value(x);
}
SyntaxTreeNode *PrintNode::clone() const { return new PrintNode(*this); }
SequenceNode::SequenceNode(const SequenceNode &sn) {

  for (auto it = sn._statements.begin(); it != sn._statements.end(); it++)
    _statements.push_back((*it)->clone());
}

// Sequnce Node

SequenceNode::~SequenceNode() {
  for (auto it = _statements.begin(); it != _statements.end(); it++)
    delete *it;
}
void SequenceNode::Add(SyntaxTreeNode *stn) { _statements.push_back(stn); }

void SequenceNode::print(std::ostream &s) const {
  for (auto it = _statements.begin(); it != _statements.end(); it++) {
    (*it)->print(s);
    s << std::endl;
  }
}
Function *SequenceNode::interpret(SymbolTable &fs) const {
  for (auto it = _statements.begin(); it != _statements.end(); it++)
    (*it)->interpret(fs);
  return nullptr;
}
double SequenceNode::calculate(SymbolTable &fs, double x) const {
  for (auto it = _statements.begin(); it != _statements.end(); it++)
    (*it)->interpret(fs)->value(x);
  return 0;
}
SyntaxTreeNode *SequenceNode::clone() const { return new SequenceNode(*this); }

// Empty Node

void EmptyNode::print(std::ostream &s) const { s << std::endl; }
Function *EmptyNode::interpret(SymbolTable &fs) const { return nullptr; }
double EmptyNode::calculate(SymbolTable &fs, double x) const { return 0; }
SyntaxTreeNode *EmptyNode::clone() const { return new EmptyNode(*this); }