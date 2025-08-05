#include "SyntaxTree.hpp";

// Statement Sequence Node

StatementSequenceNode::StatementSequenceNode(){};
StatementSequenceNode::StatementSequenceNode(const StatementSequenceNode &ssn) {
  for (auto node : ssn._nodes)
    addNode(node);
}
StatementSequenceNode::~StatementSequenceNode() {
  for (auto node : _nodes)
    delete node;
}

SyntaxTreeNode *StatementSequenceNode::clone() const {
  return new StatementSequenceNode(*this);
}
std::string StatementSequenceNode::interpret(SymbolTable &st) const {
  for (auto node : _nodes)
    node->interpret(st);
}
void StatementSequenceNode::addNode(SyntaxTreeNode *stn) {
  _nodes.push_back(stn->clone());
}

// Binary operator

BinaryNode::BinaryNode(std::string &symbol, SyntaxTreeNode *left,
                       SyntaxTreeNode *right)
    : _symbol(symbol), _left(left->clone()), _right(right->clone()) {}
BinaryNode::BinaryNode(const BinaryNode &bn)
    : _symbol(bn._symbol), _left(bn._left->clone()),
      _right(bn._right->clone()) {}
BinaryNode::~BinaryNode() {
  delete _left;
  delete _right;
}

SyntaxTreeNode *BinaryNode::clone() const { return new BinaryNode(*this); }
std::string BinaryNode::interpret(SymbolTable &st) const {
  if (_symbol == "+")
    return _left->interpret(st) + _right->interpret(st);
  else if (_symbol == "*") {
    std::string s1 = _left->interpret(st);
    std::string s2 = _right->interpret(st);

    int i = 0;
    std::string res = "";

    while (s1[i] == s2[i] && i < std::min(s1.length(), s2.length()))
      res += s1[i];

    return res;

  } else if (_symbol == "==")
    return (_left->interpret(st) == _right->interpret(st)) ? "1" : "0";
  else if (_symbol == "!=")
    return (_left->interpret(st) != _right->interpret(st)) ? "1" : "0";
}

// Unary Operator

UnaryNode::UnaryNode(std::string &symbol, SyntaxTreeNode *expr)
    : _symbol(symbol), _expr(expr->clone()) {}
UnaryNode::UnaryNode(const UnaryNode &un)
    : _symbol(un._symbol), _expr(un._expr->clone()) {}
UnaryNode::~UnaryNode() { delete _expr; }

SyntaxTreeNode *UnaryNode::clone() const { return new UnaryNode(*this); }
std::string UnaryNode::interpret(SymbolTable &st) const {
  std::string tmp = _expr->interpret(st);
  std::string res = "";
  for (int i = tmp.length() - 1; i >= 0; i--)
    res += tmp[i];
  return res;
}

// Assigment Node

AssignmentNode::AssignmentNode(std::string &name, SyntaxTreeNode *expr)
    : _name(name), _expr(expr->clone()) {}
AssignmentNode::AssignmentNode(const AssignmentNode &an)
    : _name(an._name), _expr(an._expr->clone()) {}
AssignmentNode::~AssignmentNode() { delete _expr; }

SyntaxTreeNode *AssignmentNode::clone() const {
  return new AssignmentNode(*this);
}
std::string AssignmentNode::interpret(SymbolTable &st) const {
  if (st.isDefined(_name))
    st.updateValue(_name, _expr->interpret(st));
  else
    st.addValue(_name, _expr->interpret(st));
  return "";
}

// Print Node

PrintNode::PrintNode(SyntaxTreeNode *stn) : _expr(stn->clone()) {}
PrintNode::PrintNode(const PrintNode &pn) : _expr(pn._expr->clone()) {}
PrintNode::~PrintNode() { delete _expr; }

SyntaxTreeNode *PrintNode::clone() const { return new PrintNode(*this); }
std::string PrintNode::interpret(SymbolTable &st) const {
  std::cout << _expr->interpret(st);
  return _expr->interpret(st);
}

// Print All Node

SyntaxTreeNode *PrintAllNode::clone() const { return new PrintAllNode(*this); }
std::string PrintAllNode::interpret(SymbolTable &st) const {
  st.printAllVariables();
}

// STDInputNode

STDInputNode::STDInputNode(std::string &name) : _name(name) {}
STDInputNode::STDInputNode(const STDInputNode &si) : _name(si._name) {}
STDInputNode::~STDInputNode() {}

SyntaxTreeNode *STDInputNode::clone() const { return new STDInputNode(*this); }
std::string STDInputNode::interpret(SymbolTable &st) const {
  std::string tmp;
  std::cin >> tmp;
  st.addValue(_name, tmp);
}

// STDOutputNode

STDOutputNode::STDOutputNode(SyntaxTreeNode *expr) : _expr(expr->clone()) {}
STDOutputNode::STDOutputNode(const STDOutputNode &si)
    : _expr(si._expr->clone()) {}
STDOutputNode::~STDOutputNode() {}

SyntaxTreeNode *STDOutputNode::clone() const {
  return new STDOutputNode(*this);
}
std::string STDOutputNode::interpret(SymbolTable &st) const {
  std::cout << _expr->interpret(st);
  return _expr->interpret(st);
}

// STDErrorNode

STDErrorNode::STDErrorNode(SyntaxTreeNode *expr) : _expr(expr->clone()) {}
STDErrorNode::STDErrorNode(const STDErrorNode &si) : _expr(si._expr->clone()) {}
STDErrorNode::~STDErrorNode() {}

SyntaxTreeNode *STDErrorNode::clone() const { return new STDErrorNode(*this); }
std::string STDErrorNode::interpret(SymbolTable &st) const {
  std::cerr << _expr->interpret(st);
  return _expr->interpret(st);
}

// Identifier Node

IdentifierNode::IdentifierNode(std::string &name) : _name(name) {}
IdentifierNode::IdentifierNode(const IdentifierNode &in) : _name(in._name) {}
IdentifierNode::~IdentifierNode() {}

SyntaxTreeNode *IdentifierNode::clone() const {
  return new IdentifierNode(*this);
}
std::string IdentifierNode::interpret(SymbolTable &st) const {
  return st.getValue(_name);
}

// Constant Node

ConstantNode::ConstantNode(std::string &value) : _value(value) {}
ConstantNode::ConstantNode(const ConstantNode &cn) : _value(cn._value) {}
ConstantNode::~ConstantNode() {}

SyntaxTreeNode *ConstantNode::clone() const { return new ConstantNode(*this); }
std::string ConstantNode::interpret(SymbolTable &st) const { return _value; }

// If Node

IfNode::IfNode(SyntaxTreeNode *condition, SyntaxTreeNode *expr)
    : _condition(condition->clone()), _expr(expr->clone()) {}
IfNode::IfNode(const IfNode &in)
    : _condition(in._condition->clone()), _expr(in._expr->clone()) {}
IfNode::~IfNode() {
  delete _condition;
  delete _expr;
}

SyntaxTreeNode *IfNode::clone() const { return new IfNode(*this); }
std::string IfNode::interpret(SymbolTable &st) const {
  if (_condition->interpret(st) == "1")
    return _expr->interpret(st);
  return "";
}

// If-Else Node

IfElseNode::IfElseNode(SyntaxTreeNode *condition, SyntaxTreeNode *then,
                       SyntaxTreeNode *elsexpr)
    : _condition(condition->clone()), _then(then->clone()),
      _elsexpr(elsexpr->clone()) {}
IfElseNode::IfElseNode(const IfElseNode &in)
    : _condition(in._condition->clone()), _then(in._then->clone()),
      _elsexpr(in._elsexpr->clone()) {}
IfElseNode::~IfElseNode() {
  delete _condition;
  delete _then;
  delete _elsexpr;
}

SyntaxTreeNode *IfElseNode::clone() const { return new IfElseNode(*this); }
std::string IfElseNode::interpret(SymbolTable &st) const {
  if (_condition->interpret(st) == "1")
    return _then->interpret(st);
  return _elsexpr->interpret(st);
}