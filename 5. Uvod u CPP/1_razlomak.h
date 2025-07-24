#ifndef RAZLOMAK_H
#define RAZLOMAK_H

#include <cmath>
#include <iostream>

class Razlomak {
private:
  int _brojilac;
  int _imenilac;
  int nzd(int x, int y);

public:
  Razlomak();
  Razlomak(int br);
  Razlomak(int br, int im);
  Razlomak(const Razlomak &r);
  ~Razlomak();

  int Brojilac() const;
  void Brojilac(int br);

  int Imenilac() const;
  void Imenilac(int br);

  void show(std::ostream &s) const;
  void read(std::istream &s);

  Razlomak &operator=(const Razlomak &r);
  Razlomak operator+(const Razlomak &r) const;
  Razlomak operator-(const Razlomak &r) const;
  Razlomak operator/(const Razlomak &r) const;
  Razlomak operator*(const Razlomak &r) const;

  Razlomak operator-() const;
  Razlomak operator~() const;

  Razlomak &operator++();
  Razlomak &operator--();

  Razlomak &operator++(int);
  Razlomak &operator--(int);

  bool operator==(const Razlomak &r) const;
  bool operator!=(const Razlomak &r) const;
  bool operator>=(const Razlomak &r) const;
  bool operator<=(const Razlomak &r) const;
  bool operator>(const Razlomak &r) const;
  bool operator<(const Razlomak &r) const;
};

std::ostream &operator<<(std::ostream &s, const Razlomak &r);
std::istream &operator>>(std::istream &s, Razlomak &r);

#endif