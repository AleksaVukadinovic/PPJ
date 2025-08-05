#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include <cstdlib>
#include <exception>
#include <iostream>
#include <vector>

#include "Function.hpp"
#include "SymbolTable.hpp"

std::ostream &operator<<(std::ostream &s, const SyntaxTreeNode &st);

class SyntaxTreeNode {
public:
  virtual ~SyntaxTreeNode() {}

  virtual void print(std::ostream &s) const = 0;
  virtual Function *interpret(SymbolTable &st) const = 0;
  virtual double calculate(SymbolTable &st, double x) const = 0;
  virtual SyntaxTreeNode *clone() const = 0;
};

class SequenceNode : public SyntaxTreeNode {
private:
  std::vector<SyntaxTreeNode *> _statements;

public:
  SequenceNode() {}
  SequenceNode(const SequenceNode &sn);
  ~SequenceNode();

  void Add(SyntaxTreeNode *stn);
  virtual void print(std::ostream &s) const;
  virtual Function *interpret(SymbolTable &st) const;
  virtual double calculate(SymbolTable &st, double x) const;
  virtual SyntaxTreeNode *clone() const;
};

class ConstantNode : public SyntaxTreeNode {
private:
  double _value;

public:
  ConstantNode(double val);
  ConstantNode(const ConstantNode &cn);

  virtual void print(std::ostream &s) const;
  virtual Function *interpret(SymbolTable &st) const;
  virtual double calculate(SymbolTable &st, double x) const;
  virtual SyntaxTreeNode *clone() const;
};

class ConstantFunctionNode : public SyntaxTreeNode {
private:
  double _value;

public:
  ConstantFunctionNode(double val);
  ConstantFunctionNode(const ConstantFunctionNode &cn);

  virtual void print(std::ostream &s) const;
  virtual Function *interpret(SymbolTable &st) const;
  virtual double calculate(SymbolTable &st, double x) const;
  virtual SyntaxTreeNode *clone() const;
};

class IdentifierNode : public SyntaxTreeNode {
private:
  std::string _name;

public:
  IdentifierNode(const std::string &s);
  IdentifierNode(const IdentifierNode &cn);

  virtual void print(std::ostream &s) const;
  virtual Function *interpret(SymbolTable &st) const;
  virtual double calculate(SymbolTable &st, double x) const;
  virtual SyntaxTreeNode *clone() const;
};

class IdentityFunctionNode : public SyntaxTreeNode {
public:
  virtual void print(std::ostream &s) const;
  virtual Function *interpret(SymbolTable &st) const;
  virtual double calculate(SymbolTable &st, double x) const;
  virtual SyntaxTreeNode *clone() const;
};

class AssignmentNode : public SyntaxTreeNode {
private:
  std::string _name;
  SyntaxTreeNode *_expr;

public:
  AssignmentNode(const std::string &s, SyntaxTreeNode *expr);
  AssignmentNode(const AssignmentNode &an);
  ~AssignmentNode();

  virtual void print(std::ostream &s) const;
  virtual Function *interpret(SymbolTable &st) const;
  virtual double calculate(SymbolTable &st, double x) const;
  virtual SyntaxTreeNode *clone() const;
};

class PrintNode : public SyntaxTreeNode {
private:
  SyntaxTreeNode *_expr;

public:
  PrintNode(SyntaxTreeNode *expr);
  PrintNode(const PrintNode &an);
  ~PrintNode();

  virtual void print(std::ostream &s) const;
  virtual Function *interpret(SymbolTable &st) const;
  virtual double calculate(SymbolTable &st, double x) const;
  virtual SyntaxTreeNode *clone() const;
};

class EmptyNode : public SyntaxTreeNode {
public:
  virtual void print(std::ostream &s) const;
  virtual Function *interpret(SymbolTable &st) const;
  virtual double calculate(SymbolTable &st, double x) const;
  virtual SyntaxTreeNode *clone() const;
};

class BinaryNode : public SyntaxTreeNode {
private:
  SyntaxTreeNode *_left;
  SyntaxTreeNode *_right;
  std::string _symbol;

public:
  BinaryNode(const std::string _s, SyntaxTreeNode *l, SyntaxTreeNode *r);
  BinaryNode(const BinaryNode &bo);
  ~BinaryNode();

  virtual void print(std::ostream &s) const;
  virtual Function *interpret(SymbolTable &st) const;
  virtual double calculate(SymbolTable &st, double x) const;
  virtual SyntaxTreeNode *clone() const;
};

class FunctionNode : public SyntaxTreeNode {
protected:
  SyntaxTreeNode *_expr;

public:
  FunctionNode(SyntaxTreeNode *expr);
  ~FunctionNode();

  virtual void print(std::ostream &s) const = 0;
  virtual Function *interpret(SymbolTable &st) const = 0;
  virtual double calculate(SymbolTable &st, double x) const = 0;
  virtual SyntaxTreeNode *clone() const = 0;
};

class CompositionNode : public FunctionNode {
private:
  std::string _name;

public:
  CompositionNode(const std::string &s, SyntaxTreeNode *expr);
  CompositionNode(const CompositionNode &cn);

  virtual void print(std::ostream &s) const;
  virtual Function *interpret(SymbolTable &st) const;
  virtual double calculate(SymbolTable &st, double x) const;
  virtual SyntaxTreeNode *clone() const;
};

class PowNode : public FunctionNode {
private:
  SyntaxTreeNode *_stepen;

public:
  PowNode(SyntaxTreeNode *expr, SyntaxTreeNode *step);
  PowNode(const PowNode &cn);
  ~PowNode();

  virtual void print(std::ostream &s) const;
  virtual Function *interpret(SymbolTable &st) const;
  virtual double calculate(SymbolTable &st, double x) const;
  virtual SyntaxTreeNode *clone() const;
};

class SinNode : public FunctionNode {
public:
  SinNode(SyntaxTreeNode *expr);
  SinNode(const SinNode &cn);

  virtual void print(std::ostream &s) const;
  virtual Function *interpret(SymbolTable &st) const;
  virtual double calculate(SymbolTable &st, double x) const;
  virtual SyntaxTreeNode *clone() const;
};

class CosNode : public FunctionNode {
public:
  CosNode(SyntaxTreeNode *expr);
  CosNode(const CosNode &cn);

  virtual void print(std::ostream &s) const;
  virtual Function *interpret(SymbolTable &st) const;
  virtual double calculate(SymbolTable &st, double x) const;
  virtual SyntaxTreeNode *clone() const;
};

class TanNode : public FunctionNode {
public:
  TanNode(SyntaxTreeNode *expr);
  TanNode(const TanNode &cn);

  virtual void print(std::ostream &s) const;
  virtual Function *interpret(SymbolTable &st) const;
  virtual double calculate(SymbolTable &st, double x) const;
  virtual SyntaxTreeNode *clone() const;
};

class CotNode : public FunctionNode {
public:
  CotNode(SyntaxTreeNode *expr);
  CotNode(const CotNode &cn);

  virtual void print(std::ostream &s) const;
  virtual Function *interpret(SymbolTable &st) const;
  virtual double calculate(SymbolTable &st, double x) const;
  virtual SyntaxTreeNode *clone() const;
};

class LogNode : public FunctionNode {
public:
  LogNode(SyntaxTreeNode *expr);
  LogNode(const LogNode &cn);

  virtual void print(std::ostream &s) const;
  virtual Function *interpret(SymbolTable &st) const;
  virtual double calculate(SymbolTable &st, double x) const;
  virtual SyntaxTreeNode *clone() const;
};

class ExpNode : public FunctionNode {
public:
  ExpNode(SyntaxTreeNode *expr);
  ExpNode(const ExpNode &cn);

  virtual void print(std::ostream &s) const;
  virtual Function *interpret(SymbolTable &st) const;
  virtual double calculate(SymbolTable &st, double x) const;
  virtual SyntaxTreeNode *clone() const;
};

class SqrtNode : public FunctionNode {
public:
  SqrtNode(SyntaxTreeNode *expr);
  SqrtNode(const SqrtNode &cn);

  virtual void print(std::ostream &s) const;
  virtual Function *interpret(SymbolTable &st) const;
  virtual double calculate(SymbolTable &st, double x) const;
  virtual SyntaxTreeNode *clone() const;
};

class ReverseNode : public FunctionNode {
public:
  ReverseNode(SyntaxTreeNode *expr);
  ReverseNode(const ReverseNode &cn);

  virtual void print(std::ostream &s) const;
  virtual Function *interpret(SymbolTable &st) const;
  virtual double calculate(SymbolTable &st, double x) const;
  virtual SyntaxTreeNode *clone() const;
};

class DiffNode : public FunctionNode {
public:
  DiffNode(SyntaxTreeNode *expr);
  DiffNode(const DiffNode &cn);

  virtual void print(std::ostream &s) const;
  virtual Function *interpret(SymbolTable &st) const;
  virtual double calculate(SymbolTable &st, double x) const;
  virtual SyntaxTreeNode *clone() const;
};

class ValueNode : public FunctionNode {
private:
  SyntaxTreeNode *_x;

public:
  ValueNode(SyntaxTreeNode *expr, SyntaxTreeNode *x);
  ValueNode(const ValueNode &cn);
  ~ValueNode();

  virtual void print(std::ostream &s) const;
  virtual Function *interpret(SymbolTable &st) const;
  virtual double calculate(SymbolTable &st, double x) const;
  virtual SyntaxTreeNode *clone() const;
};

#endif
