#ifndef POLY_V1
#define POLY_V1

/* Klasa Polinom ce interno da koristi dinamicki niz za 
 * za cuvanje liste koeficijenata 
 */
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "DinamickiNiz.h"

class Polinom_v1
{
private:
	DinamickiNiz _koeficijenti;
	/* pomocna funkcija koja uklanja vodece nule uz najvisi stepen */
	void normalizuj();
public:
	Polinom_v1();			// podrazumevani kostruktor
	Polinom_v1(int n);		// polinom stepena n inicijalizovan nulama
	
	int stepen() const;		// stepen polinom

	void show(std::ostream& s) const;

	void dodajKoef(double koef);
	
	// aritmeticki operatori
	Polinom_v1 operator +(const Polinom_v1& p) const;
	Polinom_v1 operator -(const Polinom_v1& p) const;
	Polinom_v1 operator *(const Polinom_v1& p) const;
	Polinom_v1 operator -() const;

	// indeksiranje
	double& operator [](int i);
	const double& operator [](int i) const;

	// izracunavanje vrednosti u tacki
	double operator[](double x);

	// uporedjivanje
	bool operator ==(const Polinom_v1& p) const;
	bool operator !=(const Polinom_v1& p) const;

	// operatori dodeljivanja
	Polinom_v1& operator +=(const Polinom_v1& p);
	Polinom_v1& operator -=(const Polinom_v1& p);
	Polinom_v1& operator *=(const Polinom_v1& p);
};

std::ostream& operator <<(std::ostream& s, const Polinom_v1& p);

#endif