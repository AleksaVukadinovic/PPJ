#include "Polinom_v1.h"

Polinom_v1::Polinom_v1() : _koeficijenti() {
	std::cout << "Polinom_v1: Kreiram objekat " << std::endl;
}

Polinom_v1::Polinom_v1(int n) : _koeficijenti(n+1) {
	std::cout << "Polinom_v1: Kreiram objekat " << std::endl;
}

int Polinom_v1::stepen() const {
	return _koeficijenti.size() - 1;
}

void Polinom_v1::show(std::ostream& s) const {
	for (int i = 0; i < _koeficijenti.size(); i++) {
		if (_koeficijenti[i] == 0)
			continue;
		if (_koeficijenti[i] < 0) 
			s << " - ";
		else if (i > 0)
			s << " + ";

		s << fabs(_koeficijenti[i]);

		if (i > 0) 
			s << "*x^" << i;
	}

	if (_koeficijenti.size() == 1 && _koeficijenti[0] == 0) 
		s << 0;
}

void Polinom_v1::dodajKoef(double koef) {
	_koeficijenti.dodajNaKraj(koef);
}

void Polinom_v1::normalizuj() {
	while (_koeficijenti.size() > 1 && _koeficijenti[_koeficijenti.size() - 1] == 0) 
		_koeficijenti.obrisiSaKraja();
}

Polinom_v1 Polinom_v1::operator +(const Polinom_v1& p) const {
	Polinom_v1 result(std::max(_koeficijenti.size(), p._koeficijenti.size()));
	int i = 0;
	for (i = 0; i < std::min(_koeficijenti.size(), p._koeficijenti.size()); i++) 
		result[i] = _koeficijenti[i] + p._koeficijenti[i];
	
	while (i < _koeficijenti.size()) {
		result[i] = _koeficijenti[i];
		i++;
	}

	while (i < p._koeficijenti.size()) {
		result[i] = p._koeficijenti[i];
		i++;
	}

	result.normalizuj();
	return result;
}

Polinom_v1 Polinom_v1::operator -(const Polinom_v1& p) const {
	Polinom_v1 result(std::max(_koeficijenti.size(), p._koeficijenti.size()));
	int i = 0;
	for (i = 0; i < std::min(_koeficijenti.size(), p._koeficijenti.size()); i++) 
		result[i] = _koeficijenti[i] - p._koeficijenti[i];
	
	while (i < _koeficijenti.size()) {
		result[i] = _koeficijenti[i];
		i++;
	}

	while (i < p._koeficijenti.size()) {
		result[i] = -p._koeficijenti[i];
		i++;
	}

	result.normalizuj();
	return result;
}

Polinom_v1 Polinom_v1::operator *(const Polinom_v1& p) const {
	Polinom_v1 result(stepen() + p.stepen() + 1);
	for (int i = 0; i < _koeficijenti.size(); i++) 
		for (int j = 0; j < p._koeficijenti.size(); j++) 
				result._koeficijenti[i+j] += _koeficijenti[i] * p._koeficijenti[j];
		
	result.normalizuj();
	return result;
}

Polinom_v1 Polinom_v1::operator -() const {
	Polinom_v1 result(_koeficijenti.size());
	for (int i = 0; i < _koeficijenti.size(); i++) 
		result[i] = -_koeficijenti[i];
	
	return result;
}

double& Polinom_v1::operator [](int i) {
	return _koeficijenti[i];
}

const double& Polinom_v1::operator [](int i) const {
		return _koeficijenti[i];
}

double Polinom_v1::operator[](double x) {
	double result = _koeficijenti[_koeficijenti.size() - 1];
	for (int i = _koeficijenti.size() - 2; i >= 0; i--) 
		result = _koeficijenti[i] + result * x;
	return result;
}

bool Polinom_v1::operator ==(const Polinom_v1& p) const {
	if (this->stepen() != p.stepen())
		return false;

	for (int i = 0; i < stepen(); i++) {
		if (_koeficijenti[i] != p._koeficijenti[i])
			return false;
	}

	return true;
}

bool Polinom_v1::operator !=(const Polinom_v1& p) const {
		return !(*this == p);
}

Polinom_v1& Polinom_v1::operator +=(const Polinom_v1& p) {
	int i = 0;
	for (i = 0; i < std::min(_koeficijenti.size(), p._koeficijenti.size()); i++) 
		_koeficijenti[i] += p._koeficijenti[i];
	
	while (i < p._koeficijenti.size()) {
		_koeficijenti.dodajNaKraj(p._koeficijenti[i]);
		i++;
	}
	normalizuj();
	return *this;
}

Polinom_v1& Polinom_v1::operator -=(const Polinom_v1& p) {
	int i = 0;
	for (i = 0; i < std::min(_koeficijenti.size(), p._koeficijenti.size()); i++) 
		_koeficijenti[i] -= p._koeficijenti[i];
	
	while (i < p._koeficijenti.size()) {
		_koeficijenti.dodajNaKraj(-p._koeficijenti[i]);
		i++;
	}
	normalizuj();
	return *this;
}

Polinom_v1& Polinom_v1::operator *=(const Polinom_v1& p) {
	DinamickiNiz result(stepen() + p.stepen() + 1);
	for (int i = 0; i < _koeficijenti.size(); i++) 
		for (int j = 0; j < p._koeficijenti.size(); j++) 
			result[i + j] += _koeficijenti[i] * p._koeficijenti[j];
		
	_koeficijenti = result;
	normalizuj();
	return *this;
}

std::ostream& operator <<(std::ostream& s, const Polinom_v1& p) {
	p.show(s);
	return s;
}