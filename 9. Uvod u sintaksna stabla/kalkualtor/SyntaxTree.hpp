#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include "SymbolTable.hpp"
#include <bitset>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

class SyntaxTreeNode {
public:
  virtual ~SyntaxTreeNode();

  virtual int interpret(SymbolTable &st) const = 0;
  virtual SyntaxTreeNode *clone() const = 0;
};

class StatementSequenceNode : public SyntaxTreeNode {
private:
  std::vector<SyntaxTreeNode *> _nodes;

public:
  StatementSequenceNode(std::vector<SyntaxTreeNode *> nodes);
  StatementSequenceNode(const StatementSequenceNode &ssn);
  ~StatementSequenceNode();

  int interpret(SymbolTable &st) const;
  SyntaxTreeNode *clone() const;
};

class AssignmentNode : public SyntaxTreeNode {
private:
  std::string _name;
  SyntaxTreeNode *_value;

public:
  AssignmentNode(std::string name);
  AssignmentNode(std::string name, SyntaxTreeNode *value);
  AssignmentNode(const AssignmentNode &an);
  ~AssignmentNode();

  int interpret(SymbolTable &st) const;
  SyntaxTreeNode *clone() const;
};

class PrintNode : public SyntaxTreeNode {
private:
  char _format;
  SyntaxTreeNode *_value;

public:
  PrintNode(char format, SyntaxTreeNode *value);
  PrintNode(const PrintNode &pn);
  ~PrintNode();

  int interpret(SymbolTable &st) const;
  SyntaxTreeNode *clone() const;
};

class LogicNode : public SyntaxTreeNode {
protected:
  SyntaxTreeNode *_value_left, *_value_right;

public:
  LogicNode(SyntaxTreeNode *value_left, SyntaxTreeNode *value_right);
  LogicNode(const LogicNode &ln);
  ~LogicNode();

  virtual int interpret(SymbolTable &st) const = 0;
  virtual SyntaxTreeNode *clone() const = 0;
};

class EqualityNode : public LogicNode {
  EqualityNode(SyntaxTreeNode *value_left, SyntaxTreeNode *value_right);
  EqualityNode(const EqualityNode &en);

  int interpret(SymbolTable &st) const;
  SyntaxTreeNode *clone() const;
};

class InequalityNode : public LogicNode {
  InequalityNode(SyntaxTreeNode *value_left, SyntaxTreeNode *value_right);
  InequalityNode(const InequalityNode &in);
  ~InequalityNode();

  int interpret(SymbolTable &st) const;
  SyntaxTreeNode *clone() const;
};

class BinaryOperatorNode : public SyntaxTreeNode {
protected:
  char _symbol;
  SyntaxTreeNode *_left, *_right;

public:
  BinaryOperatorNode(char symbol, SyntaxTreeNode *left, SyntaxTreeNode *right);
  BinaryOperatorNode(const BinaryOperatorNode &bon);
  ~BinaryOperatorNode();

  int interpret(SymbolTable &st) const;
  SyntaxTreeNode *clone() const;
};

class UnaryOperatorNode : public SyntaxTreeNode {
protected:
  char _symbol;
  SyntaxTreeNode *_val;

public:
  UnaryOperatorNode(char symbol, SyntaxTreeNode *val);
  UnaryOperatorNode(const UnaryOperatorNode &uon);
  ~UnaryOperatorNode();

  int interpret(SymbolTable &st) const;
  SyntaxTreeNode *clone() const;
};

class ConstantNode : public SyntaxTreeNode {
private:
  int _val;

public:
  ConstantNode(int val);
  ConstantNode(const ConstantNode &cn);
  ~ConstantNode();

  int interpret(SymbolTable &st) const;
  SyntaxTreeNode *clone() const;
};

class VariableNode : public SyntaxTreeNode {
private:
  std::string _name;

public:
  VariableNode(std::string name);
  VariableNode(const VariableNode &cn);
  ~VariableNode();

  int interpret(SymbolTable &st) const;
  SyntaxTreeNode *clone() const;
};

#endif
