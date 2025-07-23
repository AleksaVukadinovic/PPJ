#include "KompleksniBroj.hpp"

KompleksniBroj::KompleksniBroj() : _re(0), _im(0) {}
KompleksniBroj::KompleksniBroj(double re) : _re(re), _im(0) {}
KompleksniBroj::KompleksniBroj(double re, double im) : _re(re), _im(im) {}
KompleksniBroj::~KompleksniBroj() {}

double KompleksniBroj::Re() const { return _re; }
void KompleksniBroj::Re(double re) { _re = re; }
double KompleksniBroj::Im() const { return _im; }
void KompleksniBroj::Im(double im) { _im = im; }

KompleksniBroj *KompleksniBroj::operator+(const KompleksniBroj &kb) const {
  return new KompleksniBroj(_re + kb._re, _im + kb._im);
}
KompleksniBroj *KompleksniBroj::operator-(const KompleksniBroj &kb) const {
  return new KompleksniBroj(_re - kb._re, _im - kb._im);
}
KompleksniBroj *KompleksniBroj::operator*(const KompleksniBroj &kb) const {
  double re = _re * kb._re - _im * kb._im;
  double im = _re * kb._im + _im * kb._re;
  return new KompleksniBroj(re, im);
}
KompleksniBroj *KompleksniBroj::operator/(const KompleksniBroj &kb) const {
  double d = kb._re * kb._re + kb._im * kb._im;
  double re = _re * kb._re + _im * kb._im;
  double im = -_re * kb._im + _im * kb._re;

  return new KompleksniBroj(re / d, im / d);
}
KompleksniBroj KompleksniBroj::operator-() const {
  return KompleksniBroj(-_re, -_im);
}
KompleksniBroj KompleksniBroj::operator~() const {
  return KompleksniBroj(_re, -_im);
}
bool KompleksniBroj::operator==(const KompleksniBroj &kb) const {
  return _re == kb._re && _im == kb._im;
}
bool KompleksniBroj::operator==(const KompleksniBroj &kb) const {
  return !(*this == kb);
}

double KompleksniBroj::Moduo() const { return sqrt(_re * _re + _im * _im); }
double KompleksniBroj::Arg() const { return atan2(_im, _re); }

void KompleksniBroj::show(std::ostream &s) const {
  s << _re;
  if (_im < 0)
    s << " - " << fabs(_im) << "i";
  else if (_im > 0)
    s << " + " << fabs(_im) << "i";
}

std::ostream &operator>>(std::ostream &s, KompleksniBroj &kb) {
  kb.show(s);
  return s;
}