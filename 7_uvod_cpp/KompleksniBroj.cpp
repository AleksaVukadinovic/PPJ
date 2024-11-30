#include "KompleksniBroj.h"

KompleksniBroj::KompleksniBroj() {
	_re = 0;
	_im = 0;
}

KompleksniBroj::KompleksniBroj(double re, double im) :
	_re(re), _im (im){
}

double KompleksniBroj::Re() const {
	return _re;
}

void KompleksniBroj::Re(double re) {
	_re = re;
}

double KompleksniBroj::Im() const {
	return _im;
}

void KompleksniBroj::Im(double im) {
	_im = im;
}

void KompleksniBroj::show(std::ostream& s) const {
	s << _re << (_im < 0 ? " - " : " + ") << fabs(_im) << "*i";
}

void KompleksniBroj::read(std::istream& s) {
	double x, y;
	char c;
	s >> x >> c >> y;
	_re = x;
	_im = y;
}

KompleksniBroj KompleksniBroj::operator +(const KompleksniBroj& kb) const {
	return KompleksniBroj(_re + kb._re, _im + kb._im);
}

KompleksniBroj& KompleksniBroj::operator +=(const KompleksniBroj& kb) {
	_re += kb._re;
	_im += kb._im;
	return *this;
}

KompleksniBroj KompleksniBroj::operator -(const KompleksniBroj& kb) const {
	return KompleksniBroj(_re - kb._re, _im - kb._im);
}

KompleksniBroj& KompleksniBroj::operator -=(const KompleksniBroj& kb) {
	_re -= kb._re;
	_im -= kb._im;
	return *this;
}
KompleksniBroj KompleksniBroj::operator *(const KompleksniBroj& kb) const {
	double x = _re*kb._re - _im*kb._im;
	double y = _re*kb._im + _im*kb._re;
	return KompleksniBroj(x, y);
}

KompleksniBroj& KompleksniBroj::operator *=(const KompleksniBroj& kb) {
	double x = _re * kb._re - _im * kb._im;
	double y = _re * kb._im + _im * kb._re;
	_re = x;
	_im = y;
	return *this;
}

KompleksniBroj KompleksniBroj::operator /(const KompleksniBroj& kb) const {
	double del = kb._re * kb._re + kb._im * kb._im;
	double x = _re * kb._re + _im * kb._im;
	double y = -_re * kb._im + _im * kb._re;
	return KompleksniBroj(x/del, y/del);
}

KompleksniBroj& KompleksniBroj::operator /=(const KompleksniBroj& kb) {
	double del = kb._re * kb._re + kb._im * kb._im;
	double x = _re * kb._re + _im * kb._im;
	double y = -_re * kb._im + _im * kb._re;
	_re = x/del;
	_im = y/del;
	return *this;
}

KompleksniBroj KompleksniBroj::operator -() const {
	return KompleksniBroj(-_re, -_im);
}

KompleksniBroj KompleksniBroj::operator ~() const {
	return KompleksniBroj(_re, -_im);
}

double KompleksniBroj::Moduo() const {
	return sqrt(_re * _re + _im * _im);
}

double KompleksniBroj::Arg() const {
	return atan2(_im, _re);
}

bool KompleksniBroj::operator ==(const KompleksniBroj& kb) const {
	if (_re == kb._re && _im == kb._im)
		return true;
	return false;
}

bool KompleksniBroj::operator !=(const KompleksniBroj& kb) const {
	return !(*this == kb);
}

std::ostream& operator <<(std::ostream& s, const KompleksniBroj& kb) {
	kb.show(s);
	return s;
}

std::istream& operator >>(std::istream& s, KompleksniBroj& kb) {
	kb.read(s);
	return s;
}