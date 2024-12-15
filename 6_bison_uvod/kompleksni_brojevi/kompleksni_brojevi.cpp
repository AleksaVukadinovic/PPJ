#include "kompleksni_brojevi.hpp"

KompleksniBroj::KompleksniBroj() : _re(0), _im(0) {};
KompleksniBroj::KompleksniBroj(const double re, const double im): _re(re), _im(im) {};
KompleksniBroj::KompleksniBroj(KompleksniBroj& kb): _re(kb._re), _im(kb._im) {};
KompleksniBroj::~KompleksniBroj() {}

double KompleksniBroj::RealanDeo() const {return _re;}
void KompleksniBroj::RealanDeo(const double a) {_re=a;}

double KompleksniBroj::ImaginarniDeo() const {return _im;}
void KompleksniBroj::ImaginarniDeo(const double a) {_im=a;}

KompleksniBroj* KompleksniBroj::operator +(const KompleksniBroj& kb) const {
    double a = _re+kb._re;
    double b = _im+kb._im;
    return new KompleksniBroj(a, b);
}

KompleksniBroj* KompleksniBroj::operator -(const KompleksniBroj& kb) const {
    double a = _re-kb._re;
    double b = _im-kb._im;
    return new KompleksniBroj(a, b);
}

KompleksniBroj* KompleksniBroj::operator *(const KompleksniBroj& kb) const {
    double re = _re*kb._re - _im*kb._im;
    double im = _re*kb._im + _im*kb._re;
    return new KompleksniBroj(re, im);
}

KompleksniBroj* KompleksniBroj::operator /(const KompleksniBroj& kb) const {
    double d = kb._re*kb._re + kb._im*kb._im;
    double re = _re*kb._re + _im*kb._im;
    double im = -_re*kb._im + _im*kb._re;
    return new KompleksniBroj(re/d, im/d);
}

KompleksniBroj* KompleksniBroj::operator -() const {
    return new KompleksniBroj(-_re, -_im);
}

KompleksniBroj* KompleksniBroj::operator ~() const {
    return new KompleksniBroj(_re, -_im);
}

bool KompleksniBroj::operator ==(const KompleksniBroj& kb) const {
    return (_re==kb._re && _im==kb._im);
}

bool KompleksniBroj::operator !=(const KompleksniBroj& kb) const {
    return (_re!=kb._re || _im!=kb._im);
}

double KompleksniBroj::Moduo() const {
    return sqrt(pow(_re,2)+pow(_im,2));
}

double KompleksniBroj::Arg() const {
    return atan2(_im, _re);
}

void KompleksniBroj::show(std::ostream& s) const {
    s << _re << (_im<0? '-' : '+') << fabs(_im) << "i\n";
}

std::ostream& operator <<(std::ostream& s, const KompleksniBroj& kb) {
    kb.show(s);
    return s;
}