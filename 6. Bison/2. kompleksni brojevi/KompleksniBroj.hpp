#ifndef KOMPLEKSNI_H
#define KOMPLEKSNI_H

#include <cmath>
#include <iostream>

class KompleksniBroj {
private:
  double _re, _im;

public:
  KompleksniBroj();
  KompleksniBroj(double re);
  KompleksniBroj(double re, double im);
  ~KompleksniBroj();

  double Re() const;
  void Re(double re);
  double Im() const;
  void Im(double re);

  KompleksniBroj *operator+(const KompleksniBroj &kb) const;
  KompleksniBroj *operator-(const KompleksniBroj &kb) const;
  KompleksniBroj *operator/(const KompleksniBroj &kb) const;
  KompleksniBroj *operator*(const KompleksniBroj &kb) const;
  KompleksniBroj operator-() const;
  KompleksniBroj operator~() const;
  bool operator==(const KompleksniBroj &kb) const;
  bool operator!=(const KompleksniBroj &kb) const;

  double Arg() const;
  double Moduo() const;

  void show(std::ostream &s) const;
};

std::ostream &operator>>(std::ostream &s, KompleksniBroj &kb);

#endif
