#include "SyntaxTree.hpp"

// Statement Sequence Node

StatementSequenceNode::StatementSequenceNode() {}
StatementSequenceNode::StatementSequenceNode(const StatementSequenceNode &ssn) {
  for (auto node : ssn._nodes)
    _nodes.push_back(node->clone());
}
StatementSequenceNode::~StatementSequenceNode() {
  for (int i = 0; i < _nodes.size(); i++)
    delete _nodes[i];
}

SyntaxTreeNode *StatementSequenceNode::clone() const {
  return new StatementSequenceNode(*this);
}
int StatementSequenceNode::interpret(SymbolTable &st) const {
  for (int i = 0; i < _nodes.size(); i++)
    _nodes[i]->interpret(st);
}
void StatementSequenceNode::addNode(SyntaxTreeNode *stn) {
  _nodes.push_back(stn->clone());
}

// Binary Operator

BinaryOperator::BinaryOperator(std::string symbol, SyntaxTreeNode *left,
                               SyntaxTreeNode *right)
    : _symbol(symbol), _left(left->clone()), _right(right->clone()) {}
BinaryOperator::BinaryOperator(const BinaryOperator &bo)
    : _symbol(bo._symbol), _left(bo._left->clone()),
      _right(bo._right->clone()) {}
BinaryOperator::~BinaryOperator() {
  delete _left;
  delete _right;
}

SyntaxTreeNode *BinaryOperator::clone() const {
  return new BinaryOperator(*this);
}
int BinaryOperator::interpret(SymbolTable &st) const {
  if (_symbol == "+")
    return _left->interpret(st) + _right->interpret(st);
  else if (_symbol == "-")
    return _left->interpret(st) + _right->interpret(st);
  else if (_symbol == "<")
    return (_left->interpret(st) < _right->interpret(st)) ? 1 : 0;
  else if (_symbol == ">")
    return (_left->interpret(st) > _right->interpret(st)) ? 1 : 0;
}

// Assigmnet Node

AssignmentNode::AssignmentNode(std::string name, SyntaxTreeNode *expr)
    : _name(name), _expr(expr->clone()) {}
AssignmentNode::AssignmentNode(const AssignmentNode &an)
    : _name(an._name), _expr(an._expr->clone()) {}
AssignmentNode::~AssignmentNode() { delete _expr; }

SyntaxTreeNode *AssignmentNode::clone() const {
  return new AssignmentNode(*this);
}
int AssignmentNode::interpret(SymbolTable &st) const {
  st.defineValue(_name, _expr->interpret(st));
}
