#include "DinamickiNiz.h"

DinamickiNiz::DinamickiNiz() {
	_size = 0;
	_capacity = DEFAULT_SIZE;
	_niz = new double[_capacity]; 
	std::cout << "Dinamicki niz: Kreiram objekat" << std::endl;
}


DinamickiNiz::DinamickiNiz(int n, double val) {
	_size = n;
	_capacity = n;
	_niz = new double[_capacity]; 
	for (int i = 0; i < _size; i++)
		_niz[i] = val;
		std::cout << "Dinamicki niz: Kreiram objekat" << std::endl;
}

DinamickiNiz::DinamickiNiz(const DinamickiNiz& dn) {

	_size = dn._size;
	_capacity = dn._capacity;
	_niz = new double[_capacity]; 
	for (int i = 0; i < _size; i++)
		_niz[i] = dn._niz[i];
	std::cout << "Dinamicki niz: Kreiram kopiju" << std::endl;
}

DinamickiNiz& DinamickiNiz::operator =(const DinamickiNiz& dn) {
	std::cout << "Dinamicki niz: Operator dodele" << std::endl;

	if (this == &dn)
		return *this;

	if (_niz != nullptr)
		delete[] _niz;

	_size = dn._size;
	_capacity = dn._capacity;

	_niz = new double[_capacity];
	for (int i = 0; i < _size; i++)
		_niz[i] = dn._niz[i];

	return *this;
}

DinamickiNiz::~DinamickiNiz() {
	delete[] _niz;
	std::cout << "Dinamicki niz: Unistavam objekat" << std::endl;
}

/* metod stampa niz na ostream */
void DinamickiNiz::show(std::ostream& s) const {
	for (int i = 0; i < _size; i++) 
		s << _niz[i] << " ";
}

int DinamickiNiz::size() const {
	return _size;
}


void DinamickiNiz::dodajNaKraj(double x) {
	if (_size == _capacity) {
		_capacity *= DEFAULT_STEP;
		double* noviNiz = new double[_capacity];
		for (int i = 0; i < _size; i++)
			noviNiz[i] = _niz[i];

		delete[] _niz;
		_niz = noviNiz;
	}

	_niz[_size++] = x;
}

void DinamickiNiz::obrisiSaKraja() {
	if (_size == 0)
		return;
	_size -= 1;
}

int DinamickiNiz::pronadji(double x) const {
	for (int i = 0; i < _size; i++) {
		if (_niz[i] == x)
			return i;
	}
	return -1;
}

double& DinamickiNiz::operator [](int i) {
	if (i < 0 || i > _size)
		throw "Index out of bounds";
	return _niz[i];
}

const double& DinamickiNiz::operator [](int i) const{
	if (i < 0 || i > _size)
		throw "Index out of bounds";
	return _niz[i];
}

std::ostream& operator <<(std::ostream& s, const DinamickiNiz& dn) {
	dn.show(s);
	return s;
}
