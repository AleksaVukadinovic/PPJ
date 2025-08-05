#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include "SymbolTable.hpp"
#include <iostream>
#include <string>
#include <vector>

class SyntaxTreeNode {
public:
  virtual ~SyntaxTreeNode() {}

  virtual SyntaxTreeNode *clone() const = 0;
  virtual std::string interpret(SymbolTable &st) const = 0;
};

class StatementSequenceNode : public SyntaxTreeNode {
private:
  std::vector<SyntaxTreeNode *> _nodes;

public:
  StatementSequenceNode();
  StatementSequenceNode(const StatementSequenceNode &ssn);
  ~StatementSequenceNode();

  SyntaxTreeNode *clone() const;
  std::string interpret(SymbolTable &st) const;
  void addNode(SyntaxTreeNode *stn);
};

class BinaryNode : public SyntaxTreeNode {
private:
  std::string _symbol;
  SyntaxTreeNode *_left, *_right;

public:
  BinaryNode(std::string &symbol, SyntaxTreeNode *left, SyntaxTreeNode *right);
  BinaryNode(const BinaryNode &bn);
  ~BinaryNode();

  SyntaxTreeNode *clone() const;
  std::string interpret(SymbolTable &st) const;
};

class UnaryNode : public SyntaxTreeNode {
private:
  std::string _symbol;
  SyntaxTreeNode *_expr;

public:
  UnaryNode(std::string &symbol, SyntaxTreeNode *expr);
  UnaryNode(const UnaryNode &un);
  ~UnaryNode();

  SyntaxTreeNode *clone() const;
  std::string interpret(SymbolTable &st) const;
};

class AssignmentNode : public SyntaxTreeNode {
private:
  std::string _name;
  SyntaxTreeNode *_expr;

public:
  AssignmentNode(std::string &name, SyntaxTreeNode *expr);
  AssignmentNode(const AssignmentNode *an);
  ~AssignmentNode();

  SyntaxTreeNode *clone() const;
  std::string interpret(SymbolTable &st) const;
};

class PrintNode : public SyntaxTreeNode {
private:
  SyntaxTreeNode *_expr;

public:
  PrintNode(SyntaxTreeNode *expr);
  PrintNode(const PrintNode &pn);
  ~PrintNode();

  SyntaxTreeNode *clone() const;
  std::string interpret(SymbolTable &st) const;
};

class PrintAllNode : public SyntaxTreeNode {
public:
  PrintAllNode() {}
  PrintAllNode(const PrintAllNode &pan) {}

  SyntaxTreeNode *clone() const;
  std::string interpret(SymbolTable &st) const;
};

class STDInputNode : public SyntaxTreeNode {
private:
  std::string _name;

public:
  STDInputNode(std::string &name);
  STDInputNode(const STDInputNode &si);
  ~STDInputNode();

  SyntaxTreeNode *clone() const;
  std::string interpret(SymbolTable &st) const;
};

class STDOutputNode : public SyntaxTreeNode {
private:
  SyntaxTreeNode *_expr;

public:
  STDOutputNode(SyntaxTreeNode *expr);
  STDOutputNode(const STDOutputNode &si);
  ~STDOutputNode();

  SyntaxTreeNode *clone() const;
  std::string interpret(SymbolTable &st) const;
};

class STDErrorNode : public SyntaxTreeNode {
private:
  SyntaxTreeNode *_expr;

public:
  STDErrorNode(SyntaxTreeNode *expr);
  STDErrorNode(const STDErrorNode &si);
  ~STDErrorNode();

  SyntaxTreeNode *clone() const;
  std::string interpret(SymbolTable &st) const;
};

class IdentifierNode : public SyntaxTreeNode {
private:
  std::string _name;

public:
  IdentifierNode(std::string &name);
  IdentifierNode(const IdentifierNode &in);
  ~IdentifierNode();

  SyntaxTreeNode *clone() const;
  std::string interpret(SymbolTable &st) const;
};

class ConstantNode : public SyntaxTreeNode {
private:
  std::string _value;

public:
  ConstantNode(std::string &value);
  ConstantNode(const ConstantNode &cn);
  ~ConstantNode();

  SyntaxTreeNode *clone() const;
  std::string interpret(SymbolTable &st) const;
};

class IfNode : public SyntaxTreeNode {
private:
  SyntaxTreeNode *_condition, *_expr;

public:
  IfNode(SyntaxTreeNode *condition, SyntaxTreeNode *expr);
  IfNode(const IfNode &in);
  ~IfNode();

  SyntaxTreeNode *clone() const;
  std::string interpret(SymbolTable &st) const;
};

class IfElseNode : public SyntaxTreeNode {
private:
  SyntaxTreeNode *_condition, *_then, *_elsexpr;

public:
  IfElseNode(SyntaxTreeNode *condition, SyntaxTreeNode *then,
             SyntaxTreeNode *elsexpr);
  IfElseNode(const IfElseNode &in);
  ~IfElseNode();

  SyntaxTreeNode *clone() const;
  std::string interpret(SymbolTable &st) const;
};

#endif
