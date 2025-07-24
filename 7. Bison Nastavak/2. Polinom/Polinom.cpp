#include "Polinom.hpp"

void Polinom::normalizuj() {
  while (_koef.size() > 0 && _koef[_koef.size() - 1] == 0)
    _koef.pop_back();
}

Polinom::Polinom() : _koef() {}
Polinom::Polinom(int n) : _koef(n + 1, 0) { _koef[_koef.size() - 1] = 1; }
Polinom::Polinom(Polinom *p) : _koef() {
  for (int i = 0; i < p->_koef.size(); i++)
    _koef.push_back(p->_koef[i]);
}

void Polinom::dodajKoef(double val) { _koef.push_back(val); }
int Polinom::stepen() const { return _koef.size() > 0 ? _koef.size() - 1 : 0; }
void Polinom::show(std::ostream &s) const {
  for (int i = 0; i < _koef.size(); i++) {
    if (_koef[i] == 0)
      continue;

    if (_koef[i] < 0)
      s << " - ";
    else if (i > 0)
      s << " + ";

    s << fabs(_koef[i]);

    if (i > 0)
      s << "*x^" << i;
  }

  if (_koef.size() == 0)
    s << "0";
}

double Polinom::operator[](double x) {
  double P = _koef[_koef.size() - 1];
  for (int i = _koef.size() - 2; i >= 0; i--)
    P = _koef[i] + P * x;
  return P;
}

Polinom *Polinom::operator+(const Polinom &p) const {
  Polinom *rezultat = new Polinom();
  int i = 0;

  for (i = 0; i < std::min(_koef.size(), p._koef.size()); i++)
    rezultat->dodajKoef(_koef[i] + p._koef[i]);

  while (i < _koef.size()) {
    rezultat->dodajKoef(_koef[i]);
    i++;
  }

  while (i < p._koef.size()) {
    rezultat->dodajKoef(p._koef[i]);
    i++;
  }

  rezultat->normalizuj();
  return rezultat;
}

Polinom *Polinom::operator-(const Polinom &p) const {
  Polinom *rezultat = new Polinom();
  int i = 0;

  for (i = 0; i < std::min(_koef.size(), p._koef.size()); i++)
    rezultat->dodajKoef(_koef[i] - p._koef[i]);

  while (i < _koef.size()) {
    rezultat->dodajKoef(_koef[i]);
    i++;
  }

  while (i < p._koef.size()) {
    rezultat->dodajKoef(-p._koef[i]);
    i++;
  }

  rezultat->normalizuj();

  return rezultat;
}

Polinom *Polinom::operator*(const Polinom &p) const {
  Polinom *rezultat = new Polinom(this->stepen() + p.stepen() + 1);
  rezultat->_koef[rezultat->_koef.size() - 1] = 0;

  for (int i = 0; i < _koef.size(); i++)
    for (int j = 0; j < p._koef.size(); j++)
      rezultat->_koef[i + j] += _koef[i] * p._koef[j];

  return rezultat;
}

Polinom *Polinom::operator-() const {
  Polinom *rezultat = new Polinom();

  for (int i = 0; i < _koef.size(); i++)
    rezultat->dodajKoef(-_koef[i]);

  return rezultat;
}

Polinom *Polinom::izvod() const {
  Polinom *rezultat = new Polinom();

  for (int i = 1; i < _koef.size(); i++)
    rezultat->dodajKoef(i * _koef[i]);

  return rezultat;
}
Polinom *Polinom::integral(double c) const {
  Polinom *rezultat = new Polinom();
  rezultat->dodajKoef(c);

  for (int i = 0; i < _koef.size(); i++)
    rezultat->dodajKoef(_koef[i] / (i + 1));

  return rezultat;
}

bool Polinom::operator==(const Polinom &p) const {
  if (this->stepen() != p.stepen())
    return false;

  for (int i = 0; i < _koef.size(); i++)
    if (_koef[i] != p._koef[i])
      return false;

  return true;
}

bool Polinom::operator!=(const Polinom &p) const { return !(*this == p); }

std::ostream &operator<<(std::ostream &s, const Polinom &p) {
  p.show(s);
  return s;
}