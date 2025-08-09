#include "SyntaxTree.hpp"

std::ostream &operator<<(std::ostream &s, SyntaxTreeNode *node) {
  node->print(s);
  return s;
}

// Statement Sequence Node

StatementSequenceNode::StatementSequenceNode() {}
StatementSequenceNode::StatementSequenceNode(const StatementSequenceNode &ssn) {
  int n = ssn._nodes.size();
  _nodes.resize(n);
  for (int i = 0; i < n; i++)
    _nodes[i] = ssn._nodes[i]->clone();
}
StatementSequenceNode::~StatementSequenceNode() {
  for (int i = 0; i < _nodes.size(); i++)
    delete _nodes[i];
}

void StatementSequenceNode::addNode(SyntaxTreeNode *node) {
  _nodes.push_back(node->clone());
}
SyntaxTreeNode *StatementSequenceNode::clone() const {
  return new StatementSequenceNode(*this);
}
int StatementSequenceNode::interpret(SymbolTable &st) const {
  for (int i = 0; i < _nodes.size(); i++)
    _nodes[i]->interpret(st);
  return 0;
}
void StatementSequenceNode::print(std::ostream &s) const {
  for (int i = 0; i < _nodes.size(); i++)
    _nodes[i]->print(s);
}

// Binary Node

BinaryNode::BinaryNode(std::string symbol, SyntaxTreeNode *left,
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
int BinaryNode::interpret(SymbolTable &st) const {
  if (_symbol == "+")
    return _left->interpret(st) + _right->interpret(st);
  else if (_symbol == "-")
    return _left->interpret(st) - _right->interpret(st);
  else if (_symbol == "*")
    return _left->interpret(st) * _right->interpret(st);
  else if (_symbol == "/")
    return _left->interpret(st) / _right->interpret(st);
  else if (_symbol == "%")
    return _left->interpret(st) % _right->interpret(st);
  else if (_symbol == "<<")
    return _left->interpret(st) << _right->interpret(st);
  else if (_symbol == ">>")
    return _left->interpret(st) >> _right->interpret(st);
  else if (_symbol == "^")
    return _left->interpret(st) ^ _right->interpret(st);
  else if (_symbol == "&")
    return _left->interpret(st) & _right->interpret(st);
  else if (_symbol == "|")
    return _left->interpret(st) | _right->interpret(st);
  else {
    std::cerr << "Bad operator" << std::endl;
    exit(EXIT_FAILURE);
  }
}
void BinaryNode::print(std::ostream &s) const {
  s << "Binary Node" << std::endl;
}

// Assigment Node

AssignmentNode::AssignmentNode(const std::string name, SyntaxTreeNode *expr)
    : _name(name), _expr(expr->clone()) {}
AssignmentNode::AssignmentNode(const AssignmentNode &an)
    : _name(an._name), _expr(an._expr->clone()) {}
AssignmentNode::~AssignmentNode() { delete _expr; }

SyntaxTreeNode *AssignmentNode::clone() const {
  return new AssignmentNode(*this);
}
int AssignmentNode::interpret(SymbolTable &st) const {
  st.addValue(_name, _expr->interpret(st));
  return st.getValue(_name);
}
void AssignmentNode::print(std::ostream &s) const {
  s << "Dodela" << std::endl;
}

// Update Node

UpdateNode::UpdateNode(const std::string name, SyntaxTreeNode *expr)
    : _name(name), _expr(expr->clone()) {}
UpdateNode::UpdateNode(const UpdateNode &an)
    : _name(an._name), _expr(an._expr->clone()) {}
UpdateNode::~UpdateNode() { delete _expr; }

SyntaxTreeNode *UpdateNode::clone() const { return new UpdateNode(*this); }
int UpdateNode::interpret(SymbolTable &st) const {
  st.updateValue(_name, _expr->interpret(st));
  return st.getValue(_name);
}
void UpdateNode::print(std::ostream &s) const { s << "Update" << std::endl; }

// Unary Node

UnaryNode::UnaryNode(std::string symbol, SyntaxTreeNode *expr)
    : _symbol(symbol), _expr(expr->clone()) {}
UnaryNode::UnaryNode(const UnaryNode &bn)
    : _symbol(bn._symbol), _expr(bn._expr->clone()) {}
UnaryNode::~UnaryNode() { delete _expr; }

SyntaxTreeNode *UnaryNode::clone() const { return new UnaryNode(*this); }
int UnaryNode::interpret(SymbolTable &st) const {
  if (_symbol == "~")
    return ~_expr->interpret(st);
  else if (_symbol == "-")
    return -_expr->interpret(st);
  else
    return 0;
}
void UnaryNode::print(std::ostream &s) const {
  s << _symbol << _expr << std::endl;
}

// Identifier Node

IdentifierNode::IdentifierNode(const std::string name) : _name(name) {}
IdentifierNode::IdentifierNode(const IdentifierNode &in) : _name(in._name) {}
IdentifierNode::~IdentifierNode() {}

SyntaxTreeNode *IdentifierNode::clone() const {
  return new IdentifierNode(*this);
}
int IdentifierNode::interpret(SymbolTable &st) const {
  return st.getValue(_name);
}
void IdentifierNode::print(std::ostream &s) const { s << _name << std::endl; }

// Constant Node

ConstantNode::ConstantNode(const int value) : _value(value) {}
ConstantNode::ConstantNode(const ConstantNode &cn) : _value(cn._value) {}
ConstantNode::~ConstantNode() {}

SyntaxTreeNode *ConstantNode::clone() const { return new ConstantNode(*this); }
int ConstantNode::interpret(SymbolTable &st) const { return _value; }
void ConstantNode::print(std::ostream &s) const { s << _value << std::endl; }

// Print Node

PrintNode::PrintNode(const char format, SyntaxTreeNode *expr)
    : _format(format), _expr(expr->clone()) {}
PrintNode::PrintNode(const PrintNode &pn)
    : _format(pn._format), _expr(pn._expr->clone()) {}
PrintNode::~PrintNode() { delete _expr; }

SyntaxTreeNode *PrintNode::clone() const { return new PrintNode(*this); }
int PrintNode::interpret(SymbolTable &st) const {
  if (_format == 'h') {
    std::cout << std::hex << _expr->interpret(st) << std::endl;
  } else if (_format == 'b') {
    std::bitset<sizeof(int) * 8> binaryRepresentation(_expr->interpret(st));
    std::cout << std::hex << binaryRepresentation << std::endl;
  } else if (_format == 'd') {
    std::cout << _expr->interpret(st) << std::endl;
  }
  return 0;
}
void PrintNode::print(std::ostream &s) const {
  s << "Printing..." << std::endl;
}

// Empty Node

EmptyNode::EmptyNode() {}
EmptyNode::EmptyNode(const EmptyNode &en) {}

SyntaxTreeNode *EmptyNode::clone() const { return new EmptyNode(*this); }
int EmptyNode::interpret(SymbolTable &st) const { return 0; }
void EmptyNode::print(std::ostream &s) const {}

// Logic Node

LogicNode::LogicNode(SyntaxTreeNode *left, SyntaxTreeNode *right)
    : _left(left->clone()), _right(right->clone()) {}
LogicNode::LogicNode(const LogicNode &ln)
    : _left(ln._left->clone()), _right(ln._right->clone()) {}
LogicNode::~LogicNode() {
  delete _left;
  delete _right;
}

SyntaxTreeNode *LogicNode::clone() const { return new LogicNode(*this); }
int LogicNode::interpret(SymbolTable &st) const {
  std::cout << (_left->interpret(st) == _right->interpret(st) ? "True"
                                                              : "False")
            << std::endl;
  return 0;
}
void LogicNode::print(std::ostream &s) const {
  std::cout << "Logic Node" << std::endl;
}
