#ifndef _RAZLOMAK_H_
#define _RAZLOMAK_H_

#include <iostream>
#include <cmath>

class Razlomak {
private:
    int _brojilac, _imenilac;
    int nzd(int x, int y);
public:
    Razlomak();
    Razlomak(const int brojilac, const int imenilac);
    Razlomak(const Razlomak& r);
    ~Razlomak();
    Razlomak& operator =(Razlomak& r);

    int Brojilac();
    void Brojilac(int brojilac);

    int Imenilac();
    void Imenilac(int imenilac);

    void show(std::ostream& s) const;
    void read(std::istream& s);

    Razlomak operator +(Razlomak& r) const;
    Razlomak& operator +=(Razlomak& r);
    Razlomak operator -(Razlomak& r) const;
    Razlomak& operator -=(Razlomak& r);
    Razlomak operator *(Razlomak& r) const;
    Razlomak& operator *=(Razlomak& r);
    Razlomak operator /(Razlomak& r) const;
    Razlomak& operator /=(Razlomak& r);

    // prefiksni
    Razlomak& operator ++();
    Razlomak& operator --();

    // postfiksni
    Razlomak& operator ++(int);
    Razlomak& operator --(int);

    bool operator <(Razlomak& r) const;
    bool operator <=(Razlomak& r) const;
    bool operator >(Razlomak& r) const;
    bool operator >=(Razlomak& r) const;
    bool operator ==(Razlomak& r) const;
    bool operator !=(Razlomak& r) const;

    Razlomak operator -() const;
    Razlomak operator ~() const;

};

std::ostream& operator << (std::ostream& s, const Razlomak& r);
std::istream& operator >> (std::istream& s, Razlomak& r);

#endif