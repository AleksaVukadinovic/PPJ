#include "SyntaxTree.hpp"

// StatementSequenceNode

StatementSequenceNode::StatementSequenceNode() {}
StatementSequenceNode::StatementSequenceNode(const StatementSequenceNode &ssn) {
  for (auto node : ssn._nodes)
    _nodes.push_back(node->clone());
}
StatementSequenceNode::~StatementSequenceNode() {
  for (auto node : _nodes)
    delete node;
}

int StatementSequenceNode::interpret(SymbolTable &st) const {
  for (auto node : _nodes)
    node->interpret(st);
  return 0;
}
SyntaxTreeNode *StatementSequenceNode::clone() const {
  return new StatementSequenceNode(*this);
}
void StatementSequenceNode::addNode(SyntaxTreeNode *node) {
  _nodes.push_back(node->clone());
}

// BinaryOperatorNode

BinaryOperatorNode::BinaryOperatorNode(char symbol, SyntaxTreeNode *left,
                                       SyntaxTreeNode *right)
    : _symbol(symbol), _left(left->clone()), _right(right->clone()) {}
BinaryOperatorNode::BinaryOperatorNode(const BinaryOperatorNode &bon)
    : _symbol(bon._symbol), _left(bon._left->clone()),
      _right(bon._right->clone()) {}
BinaryOperatorNode::~BinaryOperatorNode() {
  delete _left;
  delete _right;
}

int BinaryOperatorNode::interpret(SymbolTable &st) const {
  if (_symbol == '+')
    return _left->interpret(st) + _right->interpret(st);
  else if (_symbol == '-')
    return _left->interpret(st) - _right->interpret(st);
  else if (_symbol == '<')
    return (_left->interpret(st) < _right->interpret(st)) ? 1 : 0;
  else if (_symbol == '>')
    return (_left->interpret(st) > _right->interpret(st)) ? 1 : 0;
  return 0;
}
SyntaxTreeNode *BinaryOperatorNode::clone() const {
  return new BinaryOperatorNode(*this);
}

// AssignmentNode

AssignmentNode::AssignmentNode(std::string &name, SyntaxTreeNode *expr)
    : _name(name), _expr(expr->clone()) {}
AssignmentNode::AssignmentNode(const AssignmentNode &an)
    : _name(an._name), _expr(an._expr->clone()) {}
AssignmentNode::~AssignmentNode() { delete _expr; }

int AssignmentNode::interpret(SymbolTable &st) const {
  st.addVariable(_name, _expr->interpret(st));
  return st.getValue(_name);
}
SyntaxTreeNode *AssignmentNode::clone() const {
  return new AssignmentNode(*this);
}

// PrintNode

PrintNode::PrintNode(SyntaxTreeNode *expr) : _expr(expr->clone()) {}
PrintNode::PrintNode(const PrintNode &pn) : _expr(pn._expr->clone()) {}
PrintNode::~PrintNode() { delete _expr; }

int PrintNode::interpret(SymbolTable &st) const {
  std::cout << _expr->interpret(st) << std::endl;
  return 0;
}
SyntaxTreeNode *PrintNode::clone() const { return new PrintNode(*this); }

// IfNode

IfNode::IfNode(SyntaxTreeNode *condition, SyntaxTreeNode *expr)
    : _condition(condition->clone()), _expr(expr->clone()) {}
IfNode::IfNode(const IfNode &in)
    : _condition(in._condition->clone()), _expr(in._expr->clone()) {}
IfNode::~IfNode() {
  delete _condition;
  delete _expr;
}

int IfNode::interpret(SymbolTable &st) const {
  if (_condition->interpret(st))
    return _expr->interpret(st);
  return 0;
}
SyntaxTreeNode *IfNode::clone() const { return new IfNode(*this); }

// IfElseNode

IfElseNode::IfElseNode(SyntaxTreeNode *condition, SyntaxTreeNode *expr1,
                       SyntaxTreeNode *expr2)
    : _condition(condition->clone()), _expr1(expr1->clone()),
      _expr2(expr2->clone()) {}
IfElseNode::IfElseNode(const IfElseNode &ien)
    : _condition(ien._condition->clone()), _expr1(ien._expr1->clone()),
      _expr2(ien._expr2->clone()) {}
IfElseNode::~IfElseNode() {
  delete _condition;
  delete _expr1;
  delete _expr2;
}

int IfElseNode::interpret(SymbolTable &st) const {
  if (_condition->interpret(st))
    return _expr1->interpret(st);
  else
    return _expr2->interpret(st);
}
SyntaxTreeNode *IfElseNode::clone() const { return new IfElseNode(*this); }

// WhileNode

WhileNode::WhileNode(SyntaxTreeNode *condition, SyntaxTreeNode *expr)
    : _condition(condition->clone()), _expr(expr->clone()) {}
WhileNode::WhileNode(const WhileNode &wn)
    : _condition(wn._condition->clone()), _expr(wn._expr->clone()) {}
WhileNode::~WhileNode() {
  delete _condition;
  delete _expr;
}

int WhileNode::interpret(SymbolTable &st) const {
  while (_condition->interpret(st))
    _expr->interpret(st);
  return 0;
}
SyntaxTreeNode *WhileNode::clone() const { return new WhileNode(*this); }

// IdentifierNode

IdentifierNode::IdentifierNode(std::string &name) : _name(name) {}
IdentifierNode::IdentifierNode(const IdentifierNode &in) : _name(in._name) {}
IdentifierNode::~IdentifierNode() {}

int IdentifierNode::interpret(SymbolTable &st) const {
  return st.getValue(_name);
}
SyntaxTreeNode *IdentifierNode::clone() const {
  return new IdentifierNode(*this);
}

// ConstantNode

ConstantNode::ConstantNode(int value) : _value(value) {}
ConstantNode::ConstantNode(const ConstantNode &cn) : _value(cn._value) {}
ConstantNode::~ConstantNode() {}

int ConstantNode::interpret(SymbolTable &st) const { return _value; }
SyntaxTreeNode *ConstantNode::clone() const { return new ConstantNode(*this); }
