#ifndef _kompleksni_broh_h_
#define _kompleksni_broj_h_

#include <iostream>
#include <cmath>

class KompleksniBroj {

private:
    double _re, _im;

public:
    KompleksniBroj();
    KompleksniBroj(double re, double im = 0);

    double Re();
    double Im();

    void Re(double re);
    void Im(double im);

    // const znaci da nece menjati polja klase 
    double Moduo() const;
    double Arg() const;

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

    bool operator ==(const KompleksniBroj& kb) const;
    bool operator !=(const KompleksniBroj& kb) const;
};

std::ostream& operator <<(std::ostream& s, const KompleksniBroj& kb);
std::istream& operator >>(std::ostream& s,  KompleksniBroj& kb);

#endif