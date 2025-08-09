#include "SyntaxTree.hpp"

// Statement Sequence Node

StatementSequneceNode::StatementSequneceNode() {}
StatementSequneceNode::~StatementSequneceNode() {
  for (int i = 0; i < _nodes.size(); i++)
    delete _nodes[i];
}

void StatementSequneceNode::addNode(SyntaxTreeNode *node) {
  _nodes.push_back(node->clone());
}
double StatementSequneceNode::interpret(SymbolTable &st) const {
  for (int i = 0; i < _nodes.size(); i++)
    _nodes[i]->interpret(st);
  return 0;
}
SyntaxTreeNode *StatementSequneceNode::clone() const {
  return new StatementSequneceNode(*this);
}

// Assigment Node

AssignmentNode::AssignmentNode(std::string &name, SyntaxTreeNode *expr)
    : _name(name), _expr(expr->clone()) {}
AssignmentNode::AssignmentNode(const AssignmentNode &an)
    : _name(an._name), _expr(an._expr->clone()) {}
AssignmentNode::~AssignmentNode() { delete _expr; }

double AssignmentNode::interpret(SymbolTable &st) const {
  st.addVariable(_name, _expr->interpret(st));
  return st.getValue(_name);
}
SyntaxTreeNode *AssignmentNode::clone() const {
  return new AssignmentNode(*this);
}

// Update Node

UpdateNode::UpdateNode(std::string &name, SyntaxTreeNode *expr)
    : _name(name), _expr(expr->clone()) {}
UpdateNode::UpdateNode(const UpdateNode &an)
    : _name(an._name), _expr(an._expr->clone()) {}
UpdateNode::~UpdateNode() { delete _expr; }

double UpdateNode::interpret(SymbolTable &st) const {
  st.updateVariable(_name, _expr->interpret(st));
  return st.getValue(_name);
}
SyntaxTreeNode *UpdateNode::clone() const { return new UpdateNode(*this); }

// Binary Operator Node

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

double BinaryOperatorNode::interpret(SymbolTable &st) const {
  switch (_symbol) {
  case '+':
    return _left->interpret(st) + _right->interpret(st);
    break;
  case '-':
    return _left->interpret(st) - _right->interpret(st);
    break;
  case '*':
    return _left->interpret(st) * _right->interpret(st);
    break;
  case '/':
    return _left->interpret(st) / _right->interpret(st);
    break;
  case '<':
    return (_left->interpret(st) < _right->interpret(st)) ? 1 : 0;
    break;
  case '>':
    return (_left->interpret(st) > _right->interpret(st)) ? 1 : 0;
    break;
  default:
    return 0;
    break;
  }
}
SyntaxTreeNode *BinaryOperatorNode::clone() const {
  return new BinaryOperatorNode(*this);
}

// UnaryNode

UnaryOperatorNode::UnaryOperatorNode(char symbol, SyntaxTreeNode *expr)
    : _symbol(symbol), _expr(expr->clone()) {}
UnaryOperatorNode::UnaryOperatorNode(const UnaryOperatorNode &uon)
    : _symbol(uon._symbol), _expr(uon._expr->clone()) {}
UnaryOperatorNode::~UnaryOperatorNode() { delete _expr; }

double UnaryOperatorNode::interpret(SymbolTable &st) const {
  return -1 * _expr->interpret(st);
}
SyntaxTreeNode *UnaryOperatorNode::clone() const {
  return new UnaryOperatorNode(*this);
}

// If Node

IfNode::IfNode(SyntaxTreeNode *condition, SyntaxTreeNode *expr)
    : _condition(condition->clone()), _expr(expr->clone()) {}
IfNode::IfNode(const IfNode &in)
    : _condition(in._condition->clone()), _expr(in._expr->clone()) {}
IfNode::~IfNode() {
  delete _condition;
  delete _expr;
}

double IfNode::interpret(SymbolTable &st) const {
  if (_condition->interpret(st) != 0)
    return _expr->interpret(st);
  return 0;
}
SyntaxTreeNode *IfNode::clone() const { return new IfNode(*this); }

// If-Else Node

IfElseNode::IfElseNode(SyntaxTreeNode *condition, SyntaxTreeNode *then,
                       SyntaxTreeNode *other)
    : _condition(condition->clone()), _then(then->clone()),
      _other(other->clone()) {}
IfElseNode::IfElseNode(const IfElseNode &ien)
    : _condition(ien._condition->clone()), _then(ien._then->clone()),
      _other(ien._other->clone()) {}
IfElseNode::~IfElseNode() {
  delete _condition;
  delete _then;
  delete _other;
}

double IfElseNode::interpret(SymbolTable &st) const {
  if (_condition->interpret(st) != 0)
    return _then->interpret(st);
  return _other->interpret(st);
}
SyntaxTreeNode *IfElseNode::clone() const { return new IfElseNode(*this); }

// While Node

WhileNode::WhileNode(SyntaxTreeNode *condition, SyntaxTreeNode *expr)
    : _condition(condition->clone()), _expr(expr->clone()) {}
WhileNode::WhileNode(const WhileNode &wn)
    : _condition(wn._condition->clone()), _expr(wn._expr->clone()) {}
WhileNode::~WhileNode() {
  delete _condition;
  delete _expr;
}

double WhileNode::interpret(SymbolTable &st) const {
  double result = 0;
  while (_condition->interpret(st) != 0)
    result = _expr->interpret(st);
  return result;
}
SyntaxTreeNode *WhileNode::clone() const { return new WhileNode(*this); }

// Print Node

PrintNode::PrintNode(SyntaxTreeNode *expr) : _expr(expr->clone()) {}
PrintNode::PrintNode(const PrintNode &pn) : _expr(pn._expr->clone()) {}
PrintNode::~PrintNode() { delete _expr; }

double PrintNode::interpret(SymbolTable &st) const {
  double value = _expr->interpret(st);
  std::cout << value << std::endl;
  return value;
}
SyntaxTreeNode *PrintNode::clone() const { return new PrintNode(*this); }

// Identifer Node

IdentifierNode::IdentifierNode(std::string &name) : _name(name) {}
IdentifierNode::IdentifierNode(const IdentifierNode &in) : _name(in._name) {}
IdentifierNode::~IdentifierNode() {}

double IdentifierNode::interpret(SymbolTable &st) const {
  return st.getValue(_name);
}
SyntaxTreeNode *IdentifierNode::clone() const {
  return new IdentifierNode(*this);
}

// Constant Node

ConstantNode::ConstantNode(double value) : _value(value) {}
ConstantNode::ConstantNode(const ConstantNode &cn) : _value(cn._value) {}
ConstantNode::~ConstantNode() {}

double ConstantNode::interpret(SymbolTable &st) const { return _value; }
SyntaxTreeNode *ConstantNode::clone() const { return new ConstantNode(*this); }