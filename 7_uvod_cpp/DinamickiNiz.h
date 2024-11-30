#ifndef DINAMICKI_NIZ_H
#define DINAMICKI_NIZ_H

#include <iostream>
#include <exception>

#define DEFAULT_SIZE (32)
#define DEFAULT_STEP (2)

class DinamickiNiz
{
private:
	double* _niz;
	int _capacity;
	int _size;
public:
	DinamickiNiz();
	DinamickiNiz(int n, double val = 0);
	DinamickiNiz(const DinamickiNiz& dn);
	DinamickiNiz& operator =(const DinamickiNiz& dn);
	~DinamickiNiz();

	void show(std::ostream& s) const;

	int size() const;

	void dodajNaKraj(double x);
	void obrisiSaKraja();
	int pronadji(double x) const;

	double& operator [](int i);
	const double& operator [](int i) const;
};

std::ostream& operator <<(std::ostream& s, const DinamickiNiz& dn);

#endif