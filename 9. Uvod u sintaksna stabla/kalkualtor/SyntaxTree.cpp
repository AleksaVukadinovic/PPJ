#include "SyntaxTree.hpp"

// Statement Sequence Node

StatementSequenceNode::StatementSequenceNode(
    std::vector<SyntaxTreeNode *> nodes) {
  int n = nodes.size();
  _nodes.resize(n);
  for (int i = 0; i < n; i++)
    _nodes[i] = nodes[i]->clone();
}
StatementSequenceNode::StatementSequenceNode(const StatementSequenceNode &ssn) {
  int n = ssn._nodes.size();
  _nodes.resize(n);
  for (int i = 0; i < n; i++)
    _nodes[i] = ssn._nodes[i]->clone();
}
StatementSequenceNode::~StatementSequenceNode() {
  int n = _nodes.size();
  for (int i = 0; i < n; i++)
    delete _nodes[i];
}

int StatementSequenceNode::interpret(SymbolTable &st) const {
  int n = _nodes.size();
  for (int i = 0; i < n; i++)
    _nodes[i]->interpret(st);
  return 0;
}

SyntaxTreeNode *StatementSequenceNode::clone() const {
  return new StatementSequenceNode(*this);
}

// Assignemnt Node

AssignmentNode::AssignmentNode(std::string name)
    : _name(name), _value(new ConstantNode(0)) {}
AssignmentNode::AssignmentNode(std::string name, SyntaxTreeNode *value)
    : _name(name), _value(value->clone()) {}
AssignmentNode::AssignmentNode(const AssignmentNode &an)
    : _name(an._name), _value(an._value->clone()) {}
AssignmentNode::~AssignmentNode() { delete _value; }

int AssignmentNode::interpret(SymbolTable &st) const {
  if (st.isDefined(_name))
    st.updateVar(_name, _value->interpret(st));
  else
    st.addVar(_name, _value->interpret(st));
  return 0;
}

// Print Node

PrintNode::PrintNode(char format, SyntaxTreeNode *value)
    : _format(format), _value(value->clone()) {}
PrintNode::PrintNode(const PrintNode &pn)
    : _format(pn._format), _value(pn._value->clone()) {}
PrintNode::~PrintNode() { delete _value; }

int PrintNode::interpret(SymbolTable &st) const {
  switch (_format) {
  case 'h':
    std::cout << std::hex << _value->interpret(st) << std::dec;
    break;
  case 'b':
    std::cout << std::bitset<8 * sizeof(int)>(_value->interpret(st))
              << std::dec;
    break;
  case 'd':
    std::cout << _value->interpret(st);
    break;
  default:
    break;
  }
  return 0;
}
SyntaxTreeNode *PrintNode::clone() const { return new PrintNode(*this); }

// Logic Node

LogicNode::LogicNode(SyntaxTreeNode *value_left, SyntaxTreeNode *value_right)
    : _value_left(value_left->clone()), _value_right(value_right->clone()) {}
LogicNode::LogicNode(const LogicNode &ln)
    : _value_left(ln._value_left->clone()),
      _value_right(ln._value_right->clone()) {}
LogicNode::~LogicNode() {
  delete _value_left;
  delete _value_right;
}

// Equality Node

EqualityNode::EqualityNode(SyntaxTreeNode *value_left,
                           SyntaxTreeNode *value_right)
    : LogicNode(value_left, value_right) {}
EqualityNode::EqualityNode(const EqualityNode &en) : LogicNode(en) {}

int EqualityNode::interpret(SymbolTable &st) const {
  std::cout << (_value_left->interpret(st) == _value_right->interpret(st)
                    ? "True"
                    : "False")
            << std::endl;
  return 0;
}
SyntaxTreeNode *EqualityNode::clone() const { return new EqualityNode(*this); }

// Inequality Node

InequalityNode::InequalityNode(SyntaxTreeNode *value_left,
                               SyntaxTreeNode *value_right)
    : LogicNode(value_left, value_right) {}
InequalityNode::InequalityNode(const InequalityNode &en) : LogicNode(en) {}

int InequalityNode::interpret(SymbolTable &st) const {
  std::cout << (_value_left->interpret(st) != _value_right->interpret(st)
                    ? "True"
                    : "False")
            << std::endl;
  return 0;
}
SyntaxTreeNode *InequalityNode::clone() const {
  return new InequalityNode(*this);
}

// Binary Operator

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
  case '%':
    return _left->interpret(st) % _right->interpret(st);
    break;
  case '&':
    return _left->interpret(st) & _right->interpret(st);
    break;
  case '|':
    return _left->interpret(st) | _right->interpret(st);
    break;
  case '^':
    return _left->interpret(st) ^ _right->interpret(st);
    break;
  case 'l':
    return _left->interpret(st) << _right->interpret(st);
    break;
  case 'r':
    return _left->interpret(st) >> _right->interpret(st);
    break;
  default:
    return 0;
    break;
  }
}
SyntaxTreeNode *BinaryOperatorNode::clone() const {
  return new BinaryOperatorNode(*this);
}

// Unary operator

UnaryOperatorNode::UnaryOperatorNode(char symbol, SyntaxTreeNode *val)
    : _symbol(symbol), _val(val->clone()) {}
UnaryOperatorNode::UnaryOperatorNode(const UnaryOperatorNode &uon)
    : _symbol(uon._symbol), _val(uon._val->clone()) {}
UnaryOperatorNode::~UnaryOperatorNode() { delete _val; }

int UnaryOperatorNode::interpret(SymbolTable &st) const {
  switch (_symbol) {
  case '-':
    return -_val->interpret(st);
    break;
  case '~':
    return ~_val->interpret(st);
    break;
  default:
    return 0;
    break;
  }
}

// Constant Node

ConstantNode::ConstantNode(int val) : _val(val) {}
ConstantNode::ConstantNode(const ConstantNode &cn) : _val(cn._val) {}
ConstantNode::~ConstantNode() {}

int ConstantNode::interpret(SymbolTable &st) const { return _val; }
SyntaxTreeNode *ConstantNode::clone() const { return new ConstantNode(*this); }

// VariableNode

VariableNode::VariableNode(std::string name) : _name(name) {}
VariableNode::VariableNode(const VariableNode &vn) : _name(vn._name) {}
VariableNode::~VariableNode() {}

int VariableNode::interpret(SymbolTable &st) const {
  return st.getValue(_name);
}
SyntaxTreeNode *VariableNode::clone() const { return new VariableNode(*this); }
