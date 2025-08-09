#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include "SymbolTable.hpp"
#include <iostream>
#include <vector>

class SyntaxTreeNode {
public:
  virtual ~SyntaxTreeNode() {}

  virtual double interpret(SymbolTable &st) const = 0;
  virtual SyntaxTreeNode *clone() const = 0;
};

class StatementSequneceNode : public SyntaxTreeNode {
private:
  std::vector<SyntaxTreeNode *> _nodes;

public:
  StatementSequneceNode();
  ~StatementSequneceNode();

  void addNode(SyntaxTreeNode *node);
  double interpret(SymbolTable &st) const;
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

  double interpret(SymbolTable &st) const;
  SyntaxTreeNode *clone() const;
};

class UpdateNode : public SyntaxTreeNode {
private:
  std::string _name;
  SyntaxTreeNode *_expr;

public:
  UpdateNode(std::string &name, SyntaxTreeNode *expr);
  UpdateNode(const UpdateNode &un);
  ~UpdateNode();

  double interpret(SymbolTable &st) const;
  SyntaxTreeNode *clone() const;
};

class BinaryOperatorNode : public SyntaxTreeNode {
private:
  char _symbol;
  SyntaxTreeNode *_left, *_right;

public:
  BinaryOperatorNode(char symbol, SyntaxTreeNode *left, SyntaxTreeNode *right);
  BinaryOperatorNode(const BinaryOperatorNode *bon);
  ~BinaryOperatorNode();

  double interpret(SymbolTable &st) const;
  SyntaxTreeNode *clone() const;
};

class UnaryOperatorNode : public SyntaxTreeNode {
private:
  char _symbol;
  SyntaxTreeNode *_expr;

public:
  UnaryOperatorNode(char symbol, SyntaxTreeNode *expr);
  UnaryOperatorNode(const UnaryOperatorNode &uon);
  ~UnaryOperatorNode();

  double interpret(SymbolTable &st) const;
  SyntaxTreeNode *clone() const;
};

class IfNode : public SyntaxTreeNode {
private:
  SyntaxTreeNode *_condition, *_expr;

public:
  IfNode(SyntaxTreeNode *condition, SyntaxTreeNode *expr);
  IfNode(const IfNode &in);
  ~IfNode();

  double interpret(SymbolTable &st) const;
  SyntaxTreeNode *clone() const;
};

class IfElseNode : public SyntaxTreeNode {
private:
  SyntaxTreeNode *_condition, *_then, *_other;

public:
  IfElseNode(SyntaxTreeNode *condition, SyntaxTreeNode *then,
             SyntaxTreeNode *other);
  IfElseNode(const IfElseNode &in);
  ~IfElseNode();

  double interpret(SymbolTable &st) const;
  SyntaxTreeNode *clone() const;
};

class WhileNode : public SyntaxTreeNode {
private:
  SyntaxTreeNode *_condition, *_expr;

public:
  WhileNode(SyntaxTreeNode *condition, SyntaxTreeNode *expr);
  WhileNode(const WhileNode &in);
  ~WhileNode();

  double interpret(SymbolTable &st) const;
  SyntaxTreeNode *clone() const;
};

class PrintNode : public SyntaxTreeNode {
private:
  SyntaxTreeNode *_expr;

public:
  PrintNode(SyntaxTreeNode *expr);
  PrintNode(const PrintNode &pn);
  ~PrintNode();

  double interpret(SymbolTable &st) const;
  SyntaxTreeNode *clone() const;
};

class IdentifierNode : public SyntaxTreeNode {
private:
  std::string _name;

public:
  IdentifierNode(std::string &name);
  IdentifierNode(const IdentifierNode &in);
  ~IdentifierNode();

  double interpret(SymbolTable &st) const;
  SyntaxTreeNode *clone() const;
};

class ConstantNode : public SyntaxTreeNode {
private:
  double _value;

public:
  ConstantNode(double value);
  ConstantNode(const ConstantNode &cn);
  ~ConstantNode();

  double interpret(SymbolTable &st) const;
  SyntaxTreeNode *clone() const;
};

#endif