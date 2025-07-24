#ifndef KOMPLEKSNI_H
#define KOMPLEKSNI_H

#include <cmath>
#include <iostream>

class KompleksniBroj {
private:
  double _re;
  double _im;

public:
  KompleksniBroj();
  KompleksniBroj(double re);
  KompleksniBroj(double re, double im);
  KompleksniBroj(const KompleksniBroj &k);
  ~KompleksniBroj();

  double Re() const;
  void Re(const double re);

  double Im() const;
  void Im(const double im);

  void show(std::ostream &s) const;
  void read(std::istream &s);

  KompleksniBroj operator+(const KompleksniBroj &k) const;
  KompleksniBroj operator+=(const KompleksniBroj &k);
  KompleksniBroj operator-(const KompleksniBroj &k) const;
  KompleksniBroj operator-=(const KompleksniBroj &k);
  KompleksniBroj operator*(const KompleksniBroj &k) const;
  KompleksniBroj operator*=(const KompleksniBroj &k);
  KompleksniBroj operator/(const KompleksniBroj &k) const;
  KompleksniBroj operator/=(const KompleksniBroj &k);

  KompleksniBroj operator-() const;
  KompleksniBroj operator~() const;

  double Moduo() const;
  double Arg() const;

  bool operator==(const KompleksniBroj &k) const;
  bool operator!=(const KompleksniBroj &k) const;
};

std::ostream &operator<<(std::ostream &s, const KompleksniBroj &k);
std::istream &operator>>(std::istream &s, KompleksniBroj &k);

#endif