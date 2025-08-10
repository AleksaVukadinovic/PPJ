#include "SyntaxTree.hpp"

std::ostream &operator<<(std::ostream &s, const SyntaxTreeNode *node) {
  node->show(s);
  return s;
}

// Integer Constant Node

IntegerConstantNode::IntegerConstantNode(int value) : _value(value) {}

Type *IntegerConstantNode::interpret(SymbolTable &st) const {
  return new IntType(_value);
}
void IntegerConstantNode::show(std::ostream &s) const { s << _value; }
SyntaxTreeNode *IntegerConstantNode::clone() const {
  return new IntegerConstantNode(*this);
}

// Double Constant Node

DoubleConstantNode::DoubleConstantNode(double value) : _value(value) {}

Type *DoubleConstantNode::interpret(SymbolTable &st) const {
  return new DoubleType(_value);
}
void DoubleConstantNode::show(std::ostream &s) const { s << _value; }
SyntaxTreeNode *DoubleConstantNode::clone() const {
  return new DoubleConstantNode(*this);
}

// String Constant Node

StringConstantNode::StringConstantNode(const std::string &value)
    : _value(value) {}

Type *StringConstantNode::interpret(SymbolTable &st) const {
  return new StringType(_value);
}
void StringConstantNode::show(std::ostream &s) const {
  s << "\"" << _value << "\"";
}
SyntaxTreeNode *StringConstantNode::clone() const {
  return new StringConstantNode(_value);
}

// Identifier Node

IdentifierNode::IdentifierNode(const std::string &name) : _name(name) {}

Type *IdentifierNode::interpret(SymbolTable &st) const {
  Type *result = st.getValue(_name);
  if (result == nullptr)
    throw std::invalid_argument("Variable is not defined");
  return result->clone();
}
void IdentifierNode::show(std::ostream &s) const { s << _name; }
SyntaxTreeNode *IdentifierNode::clone() const {
  return new IdentifierNode(*this);
}

// Group Node

GroupNode::GroupNode(SyntaxTreeNode *node) : _node(node->clone()) {}
GroupNode::GroupNode(const GroupNode &gn) : _node(gn._node->clone()) {}
GroupNode::~GroupNode() { delete _node; }

Type *GroupNode::interpret(SymbolTable &st) const {
  return _node->interpret(st);
}
void GroupNode::show(std::ostream &s) const {
  s << "(";
  _node->show(s);
  s << ")";
}
SyntaxTreeNode *GroupNode::clone() const { return new GroupNode(*this); }

// Unary Node

UnaryNode::UnaryNode(SyntaxTreeNode *node) : _node(node->clone()) {}
UnaryNode::UnaryNode(const UnaryNode &un) : _node(un._node->clone()) {}
UnaryNode::~UnaryNode() { delete _node; }

Type *UnaryNode::interpret(SymbolTable &st) const {
  Type *result = _node->interpret(st);
  std::string rtype = result->getType();
  if (rtype == "int") {
    int x = result->getInt();
    delete result;
    return new IntType(-x);
  } else if (rtype == "double") {
    int x = result->getInt();
    delete result;
    return new DoubleType(-x);
  } else {
    throw std::invalid_argument("Unary - is not applicable to string type");
  }
}
void UnaryNode::show(std::ostream &s) const {
  s << '-';
  _node->show(s);
}
SyntaxTreeNode *UnaryNode::clone() const { return new UnaryNode(*this); }

// Block Node

BlockNode::BlockNode(SyntaxTreeNode *node) : _node(node->clone()) {}
BlockNode::BlockNode(const BlockNode &gn) : _node(gn._node->clone()) {}
BlockNode::~BlockNode() { delete _node; }

Type *BlockNode::interpret(SymbolTable &st) const {
  Type *result = _node->interpret(st);
  if (result != nullptr)
    delete result;

  return nullptr;
}
void BlockNode::show(std::ostream &s) const {
  s << "{\n";
  _node->show(s);
  s << "\n}\n";
}
SyntaxTreeNode *BlockNode::clone() const { return new BlockNode(*this); }

// Print Node

PrintNode::PrintNode(SyntaxTreeNode *node) : _node(node->clone()) {}
PrintNode::PrintNode(const PrintNode &gn) : _node(gn._node->clone()) {}
PrintNode::~PrintNode() { delete _node; }

Type *PrintNode::interpret(SymbolTable &st) const {
  Type *result = _node->interpret(st);
  std::cout << result;
  delete result;
  return nullptr;
}
void PrintNode::show(std::ostream &s) const {
  s << "print(";
  _node->show(s);
  s << ")\n";
}
SyntaxTreeNode *PrintNode::clone() const { return new PrintNode(*this); }

// If (Else) Node

IfNode::IfNode(SyntaxTreeNode *condition, SyntaxTreeNode *ifExpr,
               SyntaxTreeNode *elseExpr)
    : _condition(condition->clone()), _ifExpr(ifExpr->clone()),
      _elseExpr(elseExpr->clone()) {}
IfNode::IfNode(const IfNode &in)
    : _condition(in._condition->clone()), _ifExpr(in._ifExpr->clone()),
      _elseExpr(nullptr) {
  if (in._elseExpr != nullptr)
    _elseExpr = in._elseExpr->clone();
}
IfNode::~IfNode() {
  delete _condition;
  delete _ifExpr;
  delete _elseExpr;
}

Type *IfNode::interpret(SymbolTable &st) const {
  Type *uslov = _condition->interpret(st);
  Type *result = nullptr;

  if (uslov->getInt()) {
    _ifExpr->interpret(st);
  } else if (_elseExpr != nullptr) {
    result = _elseExpr->interpret(st);
  }

  if (result != nullptr)
    delete result;
  delete uslov;

  return nullptr;
}
void IfNode::show(std::ostream &s) const {
  s << "if (";
  _condition->show(s);
  s << ")" << std::endl;
  _ifExpr->show(s);
  s << std::endl;
  if (_elseExpr != nullptr) {
    s << "else";
    _elseExpr->show(s);
    s << std::endl;
  }
}
SyntaxTreeNode *IfNode::clone() const { return new IfNode(*this); }

// While Node

WhileNode::WhileNode(SyntaxTreeNode *condition, SyntaxTreeNode *expr)
    : _condition(condition->clone()), _expr(expr->clone()) {}
WhileNode::WhileNode(const WhileNode &wn)
    : _condition(wn._condition->clone()), _expr(wn._expr->clone()) {}
WhileNode::~WhileNode() {
  delete _condition;
  delete _expr;
}

Type *WhileNode::interpret(SymbolTable &st) const {
  while (_condition->interpret(st)) {
    Type *uslov = _condition->interpret(st);
    if (uslov->getInt() == 0) {
      delete uslov;
      return nullptr;
    }
    uslov = _expr->interpret(st);
    delete uslov;
  }
  return nullptr;
}
void WhileNode::show(std::ostream &s) const {
  s << "Mrzi me while" << std::endl;
}
SyntaxTreeNode *WhileNode::clone() const { return new WhileNode(*this); }

// TODO