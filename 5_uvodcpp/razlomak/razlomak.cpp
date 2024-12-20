#include "razlomak.h"

int Razlomak::nzd(int x, int y) {
	x = abs(x);
	y = abs(y);

	do {
		int r = x % y;
		x = y;
		y = r;
	} while (y != 0);

	return x;
}

Razlomak::Razlomak():_brojilac(0), _imenilac(1){}

Razlomak::Razlomak(const int br, const int im) {
    _brojilac = br;
	_imenilac = im;

	if (_imenilac < 0) {
		_brojilac = -_brojilac;
		_imenilac = -_imenilac;
	}

	if (_imenilac == 0)
		throw "imenilac 0";

	int d = nzd(_brojilac, _imenilac);
	_brojilac /= d;
	_imenilac /= d;
}

Razlomak::Razlomak(const Razlomak &r) {
    this->_brojilac = r._brojilac;
    this->_imenilac = r._imenilac;
}

Razlomak::~Razlomak(){}

Razlomak &Razlomak::operator=(Razlomak &r) {
    if (this == &r)
        return *this;

    _brojilac = r._brojilac;
	_imenilac = r._imenilac;

    return *this;
}

int Razlomak::Brojilac() {
    return _brojilac;
}

void Razlomak::Brojilac(int brojilac) {
    _brojilac = brojilac;
    int d = nzd(_brojilac, _imenilac);
	_brojilac /= d;
	_imenilac /= d;
}

int Razlomak::Imenilac() {
    return _imenilac;
}

void Razlomak::Imenilac(int im) {
    if (im == 0)
		throw "imenilac 0";

	_imenilac = im;
	if (_imenilac < 0) {
		_brojilac = -_brojilac;
		_imenilac = -_imenilac;
	}

	int d = nzd(_brojilac, _imenilac);
	_brojilac /= d;
	_imenilac /= d;
}

void Razlomak::show(std::ostream& s) const {
    s << _brojilac << "/" << _imenilac << '\n';
}

void Razlomak::read(std::istream& s) {
    char c;
	int br, im;
	s >> br >> c >> im;
	if (c != '/')
		throw "Neispravan format";

	if (im == 0)
		throw "imenilac 0";

	_brojilac = br;
	_imenilac = im;

	if (_imenilac < 0) {
		_brojilac = -_brojilac;
		_imenilac = -_imenilac;
	}

	int d = nzd(_brojilac, _imenilac);
	_brojilac /= d;
	_imenilac /= d;
}

Razlomak Razlomak::operator+(Razlomak &r) const {
    int br = _brojilac * r._imenilac + r._brojilac * _imenilac;
	int im = _imenilac * r._imenilac;
	return Razlomak(br, im);
}

Razlomak &Razlomak::operator+=(Razlomak &r) {
    this->_brojilac += r._brojilac;
    this->_imenilac += r._imenilac;
    return *this;
}

Razlomak Razlomak::operator-(Razlomak &r) const {
    int br = _brojilac * r._imenilac - r._brojilac * _imenilac;
	int im = _imenilac * r._imenilac;
	return Razlomak(br, im);
}

Razlomak &Razlomak::operator-=(Razlomak &r) {
    int br = _brojilac * r._imenilac - r._brojilac * _imenilac;
	int im = _imenilac * r._imenilac;
    this->_brojilac = br;
    this->_imenilac = im;
    return *this;
}

Razlomak Razlomak::operator*(Razlomak &r) const {
    int br = _brojilac * r._brojilac;
	int im = _imenilac * r._imenilac;
	return Razlomak(br, im);
}

Razlomak &Razlomak::operator*=(Razlomak &r) {
    this->_brojilac *= r._brojilac;
    this->_imenilac *= r._imenilac;
    return *this;
}

Razlomak Razlomak::operator/(Razlomak &r) const {
    int br = _brojilac * r._imenilac;
	int im = _imenilac * r._brojilac;
	return Razlomak(br, im);
}

Razlomak &Razlomak::operator/=(Razlomak &r)
{
    this->_brojilac *= r._imenilac;
	this->_imenilac *= r._imenilac;
    return *this;
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
    _brojilac+=_imenilac;
    return r;
}

Razlomak &Razlomak::operator--(int) {
    Razlomak r(*this);
    _brojilac-=_imenilac;
    return r;
}

bool Razlomak::operator<(Razlomak &r) const {
    int br1 = _brojilac * r._imenilac;
	int br2 = _imenilac * r._brojilac;
	return br1 < br2;
}

bool Razlomak::operator<=(Razlomak &r) const {
    int br1 = _brojilac * r._imenilac;
	int br2 = _imenilac * r._brojilac;
	return br1 <= br2;
}

bool Razlomak::operator>(Razlomak &r) const {
    int br1 = _brojilac * r._imenilac;
	int br2 = _imenilac * r._brojilac;
	return br1 > br2;
}

bool Razlomak::operator>=(Razlomak &r) const {
    int br1 = _brojilac * r._imenilac;
	int br2 = _imenilac * r._brojilac;
	return br1 >= br2;
}

bool Razlomak::operator==(Razlomak &r) const {
    if (_brojilac == r._brojilac && _imenilac == r._imenilac)
		return true;
	return false;
}

bool Razlomak::operator!=(Razlomak &r) const {
    return !(*this==r);
}

Razlomak Razlomak::operator-() const {
    return Razlomak(-_brojilac, _imenilac);
}

Razlomak Razlomak::operator~() const {
    if (_brojilac == 0)
		return Razlomak(_brojilac, _imenilac);

	return Razlomak(_imenilac, _brojilac);
}

std::ostream& operator <<(std::ostream& s, const Razlomak& r) {
	r.show(s);
	return s;
}

std::istream& operator>>(std::istream& s, Razlomak &r) {
    r.read(s);
	return s;
}
