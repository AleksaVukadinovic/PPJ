#ifndef _KOMPLEKSNI_H_
#define _KOMPLEKSNI_H_

#include <iostream>
#include <cmath>

class KompleksniBroj {
private:
    double _re, _im;
public:
    KompleksniBroj();
    KompleksniBroj(const double re, const double im);
    KompleksniBroj(KompleksniBroj& kb);
    ~KompleksniBroj();

    double RealanDeo() const;
    void RealanDeo(const double a);

    double ImaginarniDeo() const;
    void ImaginarniDeo(const double a);

    KompleksniBroj* operator +(const KompleksniBroj& kb) const;
    KompleksniBroj* operator -(const KompleksniBroj& kb) const;
    KompleksniBroj* operator *(const KompleksniBroj& kb) const;
    KompleksniBroj* operator /(const KompleksniBroj& kb) const;

    KompleksniBroj* operator -() const;
    KompleksniBroj* operator ~() const;

    bool operator == (const KompleksniBroj& kb) const;
    bool operator != (const KompleksniBroj& kb) const;

    double Moduo() const;
    double Arg() const;

    void show(std::ostream& s) const;
};

std::ostream& operator <<(std::ostream& s, const KompleksniBroj* kb);

#endif