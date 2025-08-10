#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include "SymbolTable.hpp"
#include "Type.hpp"
#include <cstdlib>
#include <exception>
#include <iostream>
#include <vector>

class SyntaxTreeNode {
public:
  virtual ~SyntaxTreeNode() {}

  virtual Type *interpret(SymbolTable &st) const = 0;
  virtual void show(std::ostream &s) const = 0;
  virtual SyntaxTreeNode *clone() const = 0;
};

std::ostream &operator<<(std::ostream &s, const SyntaxTreeNode *node);

class ConstantNode : public SyntaxTreeNode {
public:
  virtual Type *interpret(SymbolTable &st) const = 0;
  virtual void show(std::ostream &s) const = 0;
  virtual SyntaxTreeNode *clone() const = 0;
};

class IntegerConstantNode : public ConstantNode {
private:
  int _value;

public:
  IntegerConstantNode(int value);

  Type *interpret(SymbolTable &st) const;
  void show(std::ostream &s) const;
  SyntaxTreeNode *clone() const;
};

class DoubleConstantNode : public ConstantNode {
private:
  double _value;

public:
  DoubleConstantNode(double value);

  Type *interpret(SymbolTable &st) const;
  void show(std::ostream &s) const;
  SyntaxTreeNode *clone() const;
};

class StringConstantNode : public ConstantNode {
private:
  std::string _value;

public:
  StringConstantNode(const std::string &value);

  Type *interpret(SymbolTable &st) const;
  void show(std::ostream &s) const;
  SyntaxTreeNode *clone() const;
};

class IdentifierNode : public SyntaxTreeNode {
private:
  std::string _name;

public:
  IdentifierNode(const std::string &name);

  Type *interpret(SymbolTable &st) const;
  void show(std::ostream &s) const;
  SyntaxTreeNode *clone() const;
};

class GroupNode : public SyntaxTreeNode {
private:
  SyntaxTreeNode *_node;

public:
  GroupNode(SyntaxTreeNode *node);
  GroupNode(const GroupNode &gn);
  ~GroupNode();

  Type *interpret(SymbolTable &st) const;
  void show(std::ostream &s) const;
  SyntaxTreeNode *clone() const;
};

class UnaryNode : public SyntaxTreeNode {
private:
  SyntaxTreeNode *_node;

public:
  UnaryNode(SyntaxTreeNode *node);
  UnaryNode(const UnaryNode &un);
  ~UnaryNode();

  Type *interpret(SymbolTable &st) const;
  void show(std::ostream &s) const;
  SyntaxTreeNode *clone() const;
};

class BlockNode : public SyntaxTreeNode {
private:
  SyntaxTreeNode *_node;

public:
  BlockNode(SyntaxTreeNode *node);
  BlockNode(const BlockNode &gn);
  ~BlockNode();

  Type *interpret(SymbolTable &st) const;
  void show(std::ostream &s) const;
  SyntaxTreeNode *clone() const;
};

class PrintNode : public SyntaxTreeNode {
private:
  SyntaxTreeNode *_node;

public:
  PrintNode(SyntaxTreeNode *node);
  PrintNode(const PrintNode &gn);
  ~PrintNode();

  Type *interpret(SymbolTable &st) const;
  void show(std::ostream &s) const;
  SyntaxTreeNode *clone() const;
};

class IfNode : public SyntaxTreeNode {
private:
  SyntaxTreeNode *_condition, *_ifExpr, *_elseExpr;

public:
  IfNode(SyntaxTreeNode *condition, SyntaxTreeNode *ifExpr,
         SyntaxTreeNode *elseExpr);
  IfNode(const IfNode &in);
  ~IfNode();

  Type *interpret(SymbolTable &st) const;
  void show(std::ostream &s) const;
  SyntaxTreeNode *clone() const;
};

class WhileNode : public SyntaxTreeNode {
private:
  SyntaxTreeNode *_condition, *_expr;

public:
  WhileNode(SyntaxTreeNode *condition, SyntaxTreeNode *expr);
  WhileNode(const WhileNode &wn);
  ~WhileNode();

  Type *interpret(SymbolTable &st) const;
  void show(std::ostream &s) const;
  SyntaxTreeNode *clone() const;
};

// TODO

#endif