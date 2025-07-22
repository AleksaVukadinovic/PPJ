#include "2_kompleksniBroj.h"

KompleksniBroj::KompleksniBroj() : _re(0), _im(0) {}
KompleksniBroj::KompleksniBroj(double re) : _re(re), _im(0) {}
KompleksniBroj::KompleksniBroj(double re, double im) : _re(re), _im(im) {}
KompleksniBroj::KompleksniBroj(const KompleksniBroj &k)
    : _re(k._re), _im(k._im) {}
KompleksniBroj::~KompleksniBroj() {}

double KompleksniBroj::Re() const { return _re; }
void KompleksniBroj::Re(double re) { _re = re; }
double KompleksniBroj::Im() const { return _im; }
void KompleksniBroj::Re(double im) { _im = im; }

void KompleksniBroj::show(std::ostream &s) const {
  s << _re << (_im < 0 ? " - " : " + ") << abs(_im) << "i";
}
void KompleksniBroj::read(std::istream &s) {
  double x, y;
  s >> x >> y;
  _re = x;
  _im = y;
}

KompleksniBroj KompleksniBroj::operator+(const KompleksniBroj &k) const {
  return KompleksniBroj(_re + k._re, _im + k._im);
}
KompleksniBroj KompleksniBroj::operator+=(const KompleksniBroj &k) {
  _re += k._re;
  _im += k._im;
  return *this;
}
KompleksniBroj KompleksniBroj::operator-(const KompleksniBroj &k) const {
  return KompleksniBroj(_re - k._re, _im - k._im);
}
KompleksniBroj KompleksniBroj::operator-=(const KompleksniBroj &k) {
  _re -= k._re;
  _im -= k._im;
  return *this;
}
KompleksniBroj KompleksniBroj::operator*(const KompleksniBroj &k) const {
  double x = _re * k._re - _im * k._im;
  double y = _re * k._im + _im * k._re;
}
KompleksniBroj KompleksniBroj::operator*=(const KompleksniBroj &k) {
  _re = _re * k._re - _im * k._im;
  _im = _re * k._im + _im * k._re;
  return *this;
}
KompleksniBroj KompleksniBroj::operator/(const KompleksniBroj &k) const {
  double del = k._re * k._re + k._im * k._im;
  double x = _re * k._re - _im * k._im;
  double y = _re * k._im + _im * k._re;
  return KompleksniBroj(x / del, y / del);
}
KompleksniBroj KompleksniBroj::operator/=(const KompleksniBroj &k) {
  double del = k._re * k._re + k._im * k._im;
  double x = _re * k._re - _im * k._im;
  double y = _re * k._im + _im * k._re;
  _re = x / del;
  _im = y / del;
  return *this;
}

KompleksniBroj KompleksniBroj::operator-() const {
  return KompleksniBroj(-_re, -_im);
}
KompleksniBroj KompleksniBroj::operator~() const {
  return KompleksniBroj(_re, -_im);
}

double KompleksniBroj::Moduo() const { return sqrt(_re * _re + _im * _im); }
double KompleksniBroj::Arg() const { return atan2(_im, _re); }

bool KompleksniBroj::operator==(const KompleksniBroj &k) const {
  return _re == k._re && _im == k._im;
}
bool KompleksniBroj::operator!=(const KompleksniBroj &k) const {
  return !(*this == k);
}

std::ostream &operator<<(std::ostream &s, const KompleksniBroj &k) {
  k.show(s);
  return s;
}
std::istream &operator>>(std::istream &s, KompleksniBroj &k) {
  k.read(s);
  return s;
}