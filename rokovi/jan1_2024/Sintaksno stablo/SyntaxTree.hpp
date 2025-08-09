#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include "SymbolTable.hpp"
#include <bitset>
#include <iostream>
#include <vector>

class SyntaxTreeNode {
public:
  ~SyntaxTreeNode() {}

  virtual SyntaxTreeNode *clone() const = 0;
  virtual int interpret(SymbolTable &st) const = 0;
  virtual void print(std::ostream &s) const = 0;
};

std::ostream &operator<<(std::ostream &s, const SyntaxTreeNode &node);

class StatementSequenceNode : public SyntaxTreeNode {
private:
  std::vector<SyntaxTreeNode *> _nodes;

public:
  StatementSequenceNode();
  StatementSequenceNode(const StatementSequenceNode &node);
  ~StatementSequenceNode();

  void addNode(SyntaxTreeNode *stn);
  SyntaxTreeNode *clone() const;
  int interpret(SymbolTable &st) const;
  void print(std::ostream &s) const;
};

class BinaryNode : public SyntaxTreeNode {
private:
  std::string _symbol;
  SyntaxTreeNode *_left, *_right;

public:
  BinaryNode(std::string symbol, SyntaxTreeNode *left, SyntaxTreeNode *right);
  BinaryNode(const BinaryNode &bn);
  ~BinaryNode();

  SyntaxTreeNode *clone() const;
  int interpret(SymbolTable &st) const;
  void print(std::ostream &s) const;
};

class AssignmentNode : public SyntaxTreeNode {
private:
  std::string _name;
  SyntaxTreeNode *_expr;

public:
  AssignmentNode(const std::string name, SyntaxTreeNode *expr);
  AssignmentNode(const AssignmentNode &an);
  ~AssignmentNode();

  SyntaxTreeNode *clone() const;
  int interpret(SymbolTable &st) const;
  void print(std::ostream &s) const;
};

class UpdateNode : public SyntaxTreeNode {
private:
  std::string _name;
  SyntaxTreeNode *_expr;

public:
  UpdateNode(const std::string name, SyntaxTreeNode *expr);
  UpdateNode(const UpdateNode &an);
  ~UpdateNode();

  SyntaxTreeNode *clone() const;
  int interpret(SymbolTable &st) const;
  void print(std::ostream &s) const;
};

class UnaryNode : public SyntaxTreeNode {
private:
  std::string _symbol;
  SyntaxTreeNode *_expr;

public:
  UnaryNode(std::string symbol, SyntaxTreeNode *expr);
  UnaryNode(const UnaryNode &bn);
  ~UnaryNode();

  SyntaxTreeNode *clone() const;
  int interpret(SymbolTable &st) const;
  void print(std::ostream &s) const;
};

class IdentifierNode : public SyntaxTreeNode {
private:
  std::string _name;

public:
  IdentifierNode(const std::string name);
  IdentifierNode(const IdentifierNode &in);
  ~IdentifierNode();

  SyntaxTreeNode *clone() const;
  int interpret(SymbolTable &st) const;
  void print(std::ostream &s) const;
};

class ConstantNode : public SyntaxTreeNode {
private:
  int _value;

public:
  ConstantNode(const int value);
  ConstantNode(const ConstantNode &cn);
  ~ConstantNode();

  SyntaxTreeNode *clone() const;
  int interpret(SymbolTable &st) const;
  void print(std::ostream &s) const;
};

class PrintNode : public SyntaxTreeNode {
private:
  char _format;
  SyntaxTreeNode *_expr;

public:
  PrintNode(const char format, SyntaxTreeNode *expr);
  PrintNode(const PrintNode &pn);
  ~PrintNode();

  SyntaxTreeNode *clone() const;
  int interpret(SymbolTable &st) const;
  void print(std::ostream &s) const;
};

class EmptyNode : public SyntaxTreeNode {
public:
  EmptyNode();
  EmptyNode(const EmptyNode &en);

  SyntaxTreeNode *clone() const;
  int interpret(SymbolTable &st) const;
  void print(std::ostream &s) const;
};

class LogicNode : public SyntaxTreeNode {
private:
  SyntaxTreeNode *_left, *_right;

public:
  LogicNode(SyntaxTreeNode *left, SyntaxTreeNode *right);
  LogicNode(const LogicNode &ln);
  ~LogicNode();

  SyntaxTreeNode *clone() const;
  int interpret(SymbolTable &st) const;
  void print(std::ostream &s) const;
};

#endif
