#ifndef TYPE_H
#define TYPE_H

#include <exception>
#include <iostream>

class Type {
private:
public:
  virtual int getInt() const = 0;
  virtual double getDouble() const = 0;
  virtual std::string getString() const = 0;
  virtual void show(std::ostream &s) const = 0;
  virtual Type *clone() const = 0;
  virtual std::string getType() const = 0;
};

std::ostream &operator<<(std::ostream &s, const Type *t);

class IntType : public Type {
private:
  int _value;

public:
  IntType(int value);

  int getInt() const;
  double getDouble() const;
  std::string getString() const;
  void show(std::ostream &s) const;
  Type *clone() const;
  std::string getType() const;
};

class DoubleType : public Type {
private:
  double _value;

public:
  DoubleType(double value);

  int getInt() const;
  double getDouble() const;
  std::string getString() const;
  void show(std::ostream &s) const;
  Type *clone() const;
  std::string getType() const;
};

class StringType : public Type {
private:
  std::string _value;

public:
  StringType(const std::string &value);

  int getInt() const;
  double getDouble() const;
  std::string getString() const;
  void show(std::ostream &s) const;
  Type *clone() const;
  std::string getType() const;
};

#endif