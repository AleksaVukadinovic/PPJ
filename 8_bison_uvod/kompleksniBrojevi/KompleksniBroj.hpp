#ifndef KOMPLEKS_H
#define KOMPLEKS_H

#include <iostream>
#include <cmath>

class KompleksniBroj {
private:
    double _re;
    double _im;
public:
    KompleksniBroj(double re, double im = 0);

    double Re() const;
    void Re(double re);

    double Im() const;
    void Im(double im);

    KompleksniBroj* operator +(const KompleksniBroj& kb) const;
    KompleksniBroj* operator -(const KompleksniBroj& kb) const;
    KompleksniBroj* operator *(const KompleksniBroj& kb) const;
    KompleksniBroj* operator /(const KompleksniBroj& kb) const;

    KompleksniBroj operator -() const;
    KompleksniBroj operator ~() const;

    bool operator ==(const KompleksniBroj& kb) const;
    bool operator !=(const KompleksniBroj& kb) const;

    double Moduo() const;
    double Arg() const;

    void show(std::ostream& s) const;
};

std::ostream&
operator <<(std::ostream& s, const KompleksniBroj& kb);

#endif