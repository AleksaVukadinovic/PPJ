#ifndef POLY_V2
#define POLY_V2

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>

/* verzija klase polinom koja koristi kolekciju vector 
 * za cuvanje niza koeficijenata polinoma 
 */
class Polinom_v2
{
private:
	/* std::vector<> je RAII tip podataka, pa mozemo da posmatramo
	 * atribut _koeficijenti kao automatsku promenljivu. Zbog toga ne 
	 * moramo da obezbedimo eksplicitne konstruktor kopije, operator
	 * dodele i destruktor, vec mozemo da se oslobodimo na podrazumevano
	 * dostupne.
	 * 
	 * Pored ovoga, std::vector<> podrzava poseduje move konstruktor i
	 * move assignment, pa mozemo da budemo sigurni da se nece desavati
	 * nepotrebna kopiranja.
	 */
	std::vector<double> _koeficijenti;
	/* pomocna funkcija koja uklanja vodece nule uz najvisi stepen */
	void normalizuj();
public:
	Polinom_v2();
	Polinom_v2(int n, double val = 0);
	Polinom_v2(const std::vector<double>& koef);

	void show(std::ostream& s) const;
	int stepen() const;
	void dodajKoef(double koef);

	// aritmeticki operatori
	Polinom_v2 operator +(const Polinom_v2& p) const;
	Polinom_v2 operator -(const Polinom_v2& p) const;
	Polinom_v2 operator *(const Polinom_v2& p) const;
	Polinom_v2 operator -() const;

	// indeksiranje
	double& operator [](int i);
	const double& operator [](int i) const;

	// izracunavanje vrednosti u tacki
	double operator[](double x);

	// uporedjivanje
	bool operator ==(const Polinom_v2& p) const;
	bool operator !=(const Polinom_v2& p) const;

	// operatori dodeljivanja
	Polinom_v2& operator +=(const Polinom_v2& p);
	Polinom_v2& operator -=(const Polinom_v2& p);
	Polinom_v2& operator *=(const Polinom_v2& p);
};

/* globalni operator za stampanje polinoma */
std::ostream& operator <<(std::ostream& s, const Polinom_v2& p);

#endif