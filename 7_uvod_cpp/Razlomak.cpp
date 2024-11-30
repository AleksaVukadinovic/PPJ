#include "Razlomak.h"

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


Razlomak::Razlomak() : _brojilac(0), _imenilac(1) {

	std::cout << "Kreiram objekat" << std::endl;
}

Razlomak::Razlomak(int br) : _brojilac(br), _imenilac(1) {
	std::cout << "Kreiram objekat" << std::endl;
}

Razlomak::Razlomak(int br, int im) {

	_brojilac = br;
	_imenilac = im;

	if (_imenilac < 0) {
		_brojilac = -_brojilac;
		_imenilac = -_imenilac;
	}

	if (_imenilac == 0)
		throw "imenilac 0";

	int d = nzd(_brojilac, _imenilac);

	/* dovodimo razlomak u neskrativi oblik */
	_brojilac /= d;
	_imenilac /= d;

	std::cout << "Kreiram objekat" << std::endl;
}

Razlomak::Razlomak(const Razlomak& r) : _brojilac(r._brojilac), _imenilac(r._imenilac){
	std::cout << "Kopiram objekat" << std::endl;
}

Razlomak::~Razlomak() {
	std::cout << "Unistavam objekat: " << (*this) << std::endl;
}

Razlomak& Razlomak::operator =(const Razlomak& r) {
	std::cout << "Dodeljujem vrednost: " << r << " objektu " << (*this) << std::endl;

	if (this == &r)
		return *this;

	_brojilac = r._brojilac;
	_imenilac = r._imenilac;

	return *this;
}

int Razlomak::Brojilac() const {
	return _brojilac;
}

void Razlomak::Brojilac(int br) {
	_brojilac = br;
	int d = nzd(_brojilac, _imenilac);
	_brojilac /= d;
	_imenilac /= d;
}

int Razlomak::Imenilac() const {
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
	s << _brojilac << "/" << _imenilac;
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

Razlomak Razlomak::operator +(const Razlomak& r) const {
	int br = _brojilac * r._imenilac + r._brojilac * _imenilac;
	int im = _imenilac * r._imenilac;
	return Razlomak(br, im);
}

Razlomak Razlomak::operator -(const Razlomak& r) const {
	int br = _brojilac * r._imenilac - r._brojilac * _imenilac;
	int im = _imenilac * r._imenilac;
	return Razlomak(br, im);
}

Razlomak Razlomak::operator *(const Razlomak& r) const {
	int br = _brojilac * r._brojilac;
	int im = _imenilac * r._imenilac;
	return Razlomak(br, im);
}

Razlomak Razlomak::operator /(const Razlomak& r) const {
	int br = _brojilac * r._imenilac;
	int im = _imenilac * r._brojilac;
	return Razlomak(br, im);
}

Razlomak Razlomak::operator -() const {
	return Razlomak(-_brojilac, _imenilac);
}

Razlomak Razlomak::operator ~() const {
	if (_brojilac == 0)
		return Razlomak(_brojilac, _imenilac);
	return Razlomak(_imenilac, _brojilac);
}

Razlomak& Razlomak::operator ++() {
	_brojilac += _imenilac;
	return *this;
}

Razlomak& Razlomak::operator --() {
	_brojilac -= _imenilac;
	return *this;
}

Razlomak Razlomak::operator++(int) {
	Razlomak r(*this);
	_brojilac += _imenilac;
	return r;
}

Razlomak Razlomak::operator--(int) {
	Razlomak r(*this);
	_brojilac -= _imenilac;
	return r;
}

bool Razlomak::operator ==(const Razlomak& r) const {

	if (_brojilac == r._brojilac && _imenilac == r._imenilac)
		return true;
	return false;
}

bool Razlomak::operator !=(const Razlomak& r) const {
	return !(*this == r);
}

bool Razlomak::operator <=(const Razlomak& r) const {
	int br1 = _brojilac * r._imenilac;
	int br2 = _imenilac * r._brojilac;
	return br1 <= br2;
}

bool Razlomak::operator >=(const Razlomak& r) const {
	int br1 = _brojilac * r._imenilac;
	int br2 = _imenilac * r._brojilac;
	return br1 >= br2;
}

bool Razlomak::operator <(const Razlomak& r) const {
	int br1 = _brojilac * r._imenilac;
	int br2 = _imenilac * r._brojilac;
	return br1 < br2;
}

bool Razlomak::operator >(const Razlomak& r) const {
	int br1 = _brojilac * r._imenilac;
	int br2 = _imenilac * r._brojilac;
	return br1 > br2;
}

std::ostream& operator <<(std::ostream& s, const Razlomak& r) {
	r.show(s);
	return s;
}

std::istream& operator >>(std::istream& s, Razlomak& r) {
	r.read(s);
	return s;
}