#include "1_razlomak.h"

int Razlomak::nzd(int x, int y) {
  x = abs(x);
  y = abs(y);

  do {
    int r = x % y;
    x = y;
    y = r;
  } while (y);
  return x;
}

Razlomak::Razlomak() : _brojilac(0), _imenilac(1) {}
Razlomak::Razlomak(int br) : _brojilac(br), _imenilac(1) {}
Razlomak::Razlomak(int br, int im) {
  _brojilac = im < 0 ? -br : br;
  _imenilac = im < 0 ? -im : im;

  if (im == 0)
    throw "Imenilac ne sme biti 0!";

  int d = nzd(_brojilac, _imenilac);
  _brojilac /= d;
  _imenilac /= d;
}
Razlomak::Razlomak(const Razlomak &r)
    : _brojilac(r._brojilac), _imenilac(r._imenilac) {}
Razlomak::~Razlomak() {}

int Razlomak::Brojilac() const { return _brojilac; }

void Razlomak::Brojilac(int br) { _brojilac = br; }

int Razlomak::Imenilac() const { return _imenilac; }

void Razlomak::Imenilac(int im) { _imenilac = im; }

void Razlomak::show(std::ostream &s) const {
  s << _brojilac << '/' << _imenilac;
}

void Razlomak::read(std::istream &s) {
  char c;
  int br, im;
  s >> br >> c >> im;
  if (c != '/')
    throw "Neispravan format!";

  if (im == 0)
    throw "Imenilac ne sme biti 0!";

  _brojilac = im < 0 ? -br : br;
  _imenilac = im < 0 ? -im : im;

  int d = nzd(_brojilac, _imenilac);
  _brojilac /= d;
  _imenilac /= d;
}

Razlomak &Razlomak::operator=(const Razlomak &r) {
  if (this == &r) // self-assigment check. Ovo obavezno svuda
    return *this;

  _brojilac = r._brojilac;
  _imenilac = r._imenilac;

  return *this;
}

Razlomak Razlomak::operator+(const Razlomak &r) const {
  int br = _brojilac * r._imenilac + r._brojilac * _imenilac;
  int im = r._imenilac * _imenilac;
  return Razlomak(br, im);
}

Razlomak Razlomak::operator-(const Razlomak &r) const {
  int br = _brojilac * r._imenilac - r._brojilac * _imenilac;
  int im = r._imenilac * _imenilac;
  return Razlomak(br, im);
}

Razlomak Razlomak::operator*(const Razlomak &r) const {
  int br = _brojilac * r._brojilac;
  int im = _imenilac * r._imenilac;
  return Razlomak(br, im);
}

Razlomak Razlomak::operator/(const Razlomak &r) const {
  int br = _brojilac * r._imenilac;
  int im = _imenilac * r._brojilac;
  return Razlomak(br, im);
}

Razlomak Razlomak::operator-() const { return Razlomak(-_brojilac, _imenilac); }

Razlomak Razlomak::operator~() const {
  if (_brojilac == 0)
    return Razlomak(_brojilac, _imenilac);
  return Razlomak(_imenilac, _brojilac);
}

Razlomak &Razlomak::operator++() {
  _brojilac += _imenilac;
  return *this;
}

Razlomak &Razlomak::operator--() {
  _brojilac -= _imenilac;
  return *this;
}

Razlomak &Razlomak::operator++(int) {
  Razlomak r(*this);
  _brojilac += _imenilac;
  return r;
}

Razlomak &Razlomak::operator--(int) {
  Razlomak r(*this);
  _brojilac -= _imenilac;
  return r;
}

bool Razlomak::operator==(const Razlomak &r) const {
  return _brojilac == r._brojilac && _imenilac == r._imenilac;
}
bool Razlomak::operator!=(const Razlomak &r) const { return !(*this == r); }
bool Razlomak::operator>=(const Razlomak &r) const {
  int br1 = _brojilac * r._imenilac;
  int br2 = _imenilac * r._brojilac;
  return br1 >= br2;
}
bool Razlomak::operator<=(const Razlomak &r) const {
  int br1 = _brojilac * r._imenilac;
  int br2 = _imenilac * r._brojilac;
  return br1 <= br2;
}
bool Razlomak::operator>(const Razlomak &r) const {
  int br1 = _brojilac * r._imenilac;
  int br2 = _imenilac * r._brojilac;
  return br1 > br2;
}
bool Razlomak::operator<(const Razlomak &r) const {
  int br1 = _brojilac * r._imenilac;
  int br2 = _imenilac * r._brojilac;
  return br1 < br2;
}

std::ostream &operator<<(std::ostream &s, const Razlomak &r) {
  r.show(s);
  return s;
}

std::istream &operator>>(std::istream &s, Razlomak &r) {
  r.read(s);
  return s;
}