#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include "SymbolTable.hpp"
#include <vector>

class SyntaxTreeNode {
public:
  virtual ~SyntaxTreeNode() {}

  virtual SyntaxTreeNode *clone() const = 0;
  virtual int interpret(SymbolTable &st) const = 0;
};

class StatementSequenceNode : public SyntaxTreeNode {
private:
  std::vector<SyntaxTreeNode *> _nodes;

public:
  StatementSequenceNode() {}
  StatementSequenceNode(const StatementSequenceNode &ssn);
  ~StatementSequenceNode();

  SyntaxTreeNode *clone() const;
  int interpret(SymbolTable &st) const;
  void addNode(SyntaxTreeNode *stn);
};

class BinaryOperator : public SyntaxTreeNode {
private:
  std::string _symbol;
  SyntaxTreeNode *_left, *_right;

public:
  BinaryOperator(std::string symbol, SyntaxTreeNode *left,
                 SyntaxTreeNode *right);
  BinaryOperator(const BinaryOperator &bo);
  ~BinaryOperator();

  SyntaxTreeNode *clone() const;
  int interpret(SymbolTable &st) const;
};

class AssignmentNode : public SyntaxTreeNode {
private:
  std::string _name;
  SyntaxTreeNode *_expr;

public:
  AssignmentNode(std::string name, SyntaxTreeNode *expr);
  AssignmentNode(const AssignmentNode &an);
  ~AssignmentNode();

  SyntaxTreeNode *clone() const;
  int interpret(SymbolTable &st) const;
};

class PrintNode : public SyntaxTreeNode {
private:
  SyntaxTreeNode *_expr;

public:
  PrintNode(SyntaxTreeNode *expr);
  PrintNode(const PrintNode &pn);
  ~PrintNode();

  SyntaxTreeNode *clone() const;
  int interpret(SymbolTable &st) const;
};

class WhileNode : public SyntaxTreeNode {
private:
  SyntaxTreeNode *_condition;
  SyntaxTreeNode *_body;

public:
  WhileNode(SyntaxTreeNode *condition, SyntaxTreeNode *body);
  WhileNode(const WhileNode &wn);
  ~WhileNode();

  SyntaxTreeNode *clone() const;
  int interpret(SymbolTable &st) const;
};

class IfNode : public SyntaxTreeNode {
private:
  SyntaxTreeNode *_condition;
  SyntaxTreeNode *_body;

public:
  IfNode(SyntaxTreeNode *condition, SyntaxTreeNode *body);
  IfNode(const IfNode &in);
  ~IfNode();

  SyntaxTreeNode *clone() const;
  int interpret(SymbolTable &st) const;
};

class IfElseNode : public SyntaxTreeNode {
private:
  SyntaxTreeNode *_condition;
  SyntaxTreeNode *_then;
  SyntaxTreeNode *_elsexpr;

public:
  IfElseNode(SyntaxTreeNode *condition, SyntaxTreeNode *then,
             SyntaxTreeNode *elseexpr);
  IfElseNode(const IfElseNode &ien);
  ~IfElseNode();

  SyntaxTreeNode *clone() const;
  int interpret(SymbolTable &st) const;
};

#endif
