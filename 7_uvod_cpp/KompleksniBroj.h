#ifndef KOMPLEKSNI_BROJ_H
#define KOMPLEKSNI_BROJ_H

#include <iostream>
#include <cmath>

class KompleksniBroj
{
private:
	double _re;
	double _im;
public:
	KompleksniBroj();
	KompleksniBroj(double re, double im = 0);

	double Re() const;
	void Re(double re);

	double Im() const;
	void Im(double im);

	void show(std::ostream& s) const;
	void read(std::istream& s);

	KompleksniBroj operator +(const KompleksniBroj& kb) const;
	KompleksniBroj& operator +=(const KompleksniBroj& kb);
	KompleksniBroj operator -(const KompleksniBroj& kb) const;
	KompleksniBroj& operator -=(const KompleksniBroj& kb);
	KompleksniBroj operator *(const KompleksniBroj& kb) const;
	KompleksniBroj& operator *=(const KompleksniBroj& kb);
	KompleksniBroj operator /(const KompleksniBroj& kb) const;
	KompleksniBroj& operator /=(const KompleksniBroj& kb);

	KompleksniBroj operator -() const;
	KompleksniBroj operator ~() const;

	double Moduo() const;
	double Arg() const;

	bool operator ==(const KompleksniBroj& kb) const;
	bool operator !=(const KompleksniBroj& kb) const;

};

std::ostream& operator <<(std::ostream& s, const KompleksniBroj& kb);
std::istream& operator >>(std::istream& s, KompleksniBroj& kb);

#endif

