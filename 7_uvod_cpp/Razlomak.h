#ifndef RAZLOMAK_H
#define RAZLOMA_H

#include <iostream>
#include <cmath>

class Razlomak
{
private: 
	int _brojilac;
	int _imenilac;
	int nzd(int x, int y);
public: 
	Razlomak();							// podrazumevani konstruktor
	Razlomak(int br);					// parametrizovani konstruktor
	Razlomak(int br, int im);			// parametrizovani konstruktor
	Razlomak(const Razlomak& r);		// konstruktor kopije
	Razlomak& operator =(const Razlomak& r); // operator dodele (copy - assignment)
	~Razlomak();						// destruktor

	// get i set metode
	int Brojilac() const;
	void Brojilac(int br);

	int Imenilac() const;
	void Imenilac(int im);

	// pomocne metode za stampanje i ucitavanje razlomka
	void show(std::ostream& s) const;
	void read(std::istream& s);

	// binarni operatori
	Razlomak operator +(const Razlomak& r) const;
	Razlomak operator -(const Razlomak& r) const;
	Razlomak operator *(const Razlomak& r) const;
	Razlomak operator /(const Razlomak& r) const;

	// unarni operatori
	Razlomak operator -() const;
	Razlomak operator ~() const;
	Razlomak& operator ++();
	Razlomak& operator --();
	Razlomak operator++(int);
	Razlomak operator--(int);

	// operatori uporedjivanja
	bool operator ==(const Razlomak& r) const;
	bool operator !=(const Razlomak& r) const;
	bool operator <=(const Razlomak& r) const;
	bool operator >=(const Razlomak& r) const;
	bool operator <(const Razlomak& r) const;
	bool operator >(const Razlomak& r) const;
};

// globalno definisani operatori za ispis i ucitavanje razlomaka
std::ostream& operator <<(std::ostream& s, const Razlomak& r);
std::istream& operator >>(std::istream& s, Razlomak& r);

#endif