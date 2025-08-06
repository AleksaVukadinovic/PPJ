#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include "SymbolTable.hpp"
#include <iostream>
#include <string>
#include <vector>

class SyntaxTreeNode {
public:
  virtual ~SyntaxTreeNode() {}

  virtual int interpret(SymbolTable &st) const = 0;
  virtual SyntaxTreeNode *clone() const = 0;
};

class StatementSequenceNode : public SyntaxTreeNode {
private:
  std::vector<SyntaxTreeNode *> _nodes;

public:
  StatementSequenceNode();
  StatementSequenceNode(const StatementSequenceNode &ssn);
  ~StatementSequenceNode();

  int interpret(SymbolTable &st) const;
  SyntaxTreeNode *clone() const;
  void addNode(SyntaxTreeNode *node);
};

class BinaryOperatorNode : public SyntaxTreeNode {
private:
  char _symbol;
  SyntaxTreeNode *_left, *_right;

public:
  BinaryOperatorNode(char symbol, SyntaxTreeNode *left, SyntaxTreeNode *right);
  BinaryOperatorNode(const BinaryOperatorNode &bon);
  ~BinaryOperatorNode();

  int interpret(SymbolTable &st) const;
  SyntaxTreeNode *clone() const;
};

class AssignmentNode : public SyntaxTreeNode {
private:
  std::string _name;
  SyntaxTreeNode *_expr;

public:
  AssignmentNode(std::string &name, SyntaxTreeNode *expr);
  AssignmentNode(const AssignmentNode &an);
  ~AssignmentNode();

  int interpret(SymbolTable &st) const;
  SyntaxTreeNode *clone() const;
};

class PrintNode : public SyntaxTreeNode {
private:
  SyntaxTreeNode *_expr;

public:
  PrintNode(SyntaxTreeNode *expr);
  PrintNode(const PrintNode &pn);
  ~PrintNode();

  int interpret(SymbolTable &st) const;
  SyntaxTreeNode *clone() const;
};

class IfNode : public SyntaxTreeNode {
private:
  SyntaxTreeNode *_condition;
  SyntaxTreeNode *_expr;

public:
  IfNode(SyntaxTreeNode *condition, SyntaxTreeNode *expr);
  IfNode(const IfNode &in);
  ~IfNode();

  int interpret(SymbolTable &st) const;
  SyntaxTreeNode *clone() const;
};

class IfElseNode : public SyntaxTreeNode {
private:
  SyntaxTreeNode *_condition;
  SyntaxTreeNode *_expr1;
  SyntaxTreeNode *_expr2;

public:
  IfElseNode(SyntaxTreeNode *condition, SyntaxTreeNode *expr1,
             SyntaxTreeNode *expr2);
  IfElseNode(const IfElseNode &ien);
  ~IfElseNode();

  int interpret(SymbolTable &st) const;
  SyntaxTreeNode *clone() const;
};

class WhileNode : public SyntaxTreeNode {
private:
  SyntaxTreeNode *_condition;
  SyntaxTreeNode *_expr;

public:
  WhileNode(SyntaxTreeNode *condition, SyntaxTreeNode *expr);
  WhileNode(const WhileNode &wn);
  ~WhileNode();

  int interpret(SymbolTable &st) const;
  SyntaxTreeNode *clone() const;
};

class IdentifierNode : public SyntaxTreeNode {
private:
  std::string _name;

public:
  IdentifierNode(std::string &name);
  IdentifierNode(const IdentifierNode &in);
  ~IdentifierNode();

  int interpret(SymbolTable &st) const;
  SyntaxTreeNode *clone() const;
};

class ConstantNode : public SyntaxTreeNode {
private:
  int _value;

public:
  ConstantNode(int value);
  ConstantNode(const ConstantNode &cn);
  ~ConstantNode();

  int interpret(SymbolTable &st) const;
  SyntaxTreeNode *clone() const;
};

#endif
