#ifndef POLINOM_H
#define POLINOM_H

#include <cmath>
#include <iostream>
#include <vector>

class Polinom {
private:
  std::vector<double> _koef;
  void normalizuj();

public:
  Polinom();
  Polinom(int n);
  Polinom(Polinom *p);

  void dodajKoef(double val);
  int stepen() const;
  void show(std::ostream &s) const;

  double operator[](double x);

  Polinom *operator+(const Polinom &p) const;
  Polinom *operator-(const Polinom &p) const;
  Polinom *operator*(const Polinom &p) const;

  Polinom *operator-() const;

  Polinom *izvod() const;
  Polinom *integral(double c) const;

  bool operator==(const Polinom &p) const;
  bool operator!=(const Polinom &p) const;
};

std::ostream &operator<<(std::ostream &s, const Polinom &p);

#endif