#include <iostream>
#include <map>
#include <exception>
#include <cmath>

/* 
 * Hijerarhija moze biti sledeca: (ovo je sam jedno od mogucih resenja)
 * 
 * Izraz (Apstraktna) ----> Konstanta
 *                 |
 *                 -------> Promenljiva
 *                 |
 *                 -------> BinarniOperator (Apstraktna) ----> Zbir
 *                 |                                     |
 *                 |                                     ----> Razlika
 *                 |                                     |
 *                 |                                     ----> Proizvod
 *                 |                                     |
 *                 |                                     ----> Kolicnik
 *                 |
 *                 -------> Funkcija (Apstraktna) ----> Suprotni (Unarni minus)
 *                                                |
 *                                                ----> Sin
 *                                                |
 *                                                ----> Cos
 *                                                |
 *                                                ----> Tan
 *                                                |
 *                                                ----> Cot
 *                                                |
 *                                                ----> Log
 *                                                |
 *                                                ----> Exp
 *                                                |
 *                                                ----> Sqrt
 *  
 * U programu koji sledi bice ilustrovano kako mozemo da napravimo program za rad sa analitickim izrazima, bez da znamo ista
 * o prevodjenju programskih jezika. Razumevanje ovog primera je kljucno za ono sto nam sledi u nastavku kursa PPJ. Primer je
 * dugacak i kada budete analizirali resenje, uvek imajte na umu sta zelimo da postignemo i pokusajte sa time da povezete
 * resenje. 
 */

/* pomocna klasa u kojoj cuvamo promenljive i njihove vrednosti */
class Okolina {
private:
    std::map<std::string, double> _promenljive;

public:
    Okolina() {}

    bool DodajPromenljivu(const std::string& s, double v) {
        if (PromenljivaDefinisana(s))
            return false;
            
        _promenljive[s] = v;
        return true;
    }

    bool PromenljivaDefinisana(const std::string& s) const {   
        auto it = _promenljive.find(s);
        return it != _promenljive.end();
    }

    double VrednostPromenljive(const std::string& s) const {
        if (!PromenljivaDefinisana(s))
            throw std::invalid_argument("promenljiva nije definisana");
        
        auto it = _promenljive.find(s);
        return it->second;
    }

    void IzmeniVrednostPromenljive(const std::string& s, double v) {
        if (!PromenljivaDefinisana(s))
            throw std::invalid_argument("promenljiva nije definisana");
        
        _promenljive[s] = v;
    }

    double& operator [](std::string& s) {
        if (!PromenljivaDefinisana(s))
            throw std::invalid_argument("promenljiva nije definisana");
        
        auto it = _promenljive.find(s);
        return it->second;
    }

    double operator [](std::string& s) const{
        if (!PromenljivaDefinisana(s))
            throw std::invalid_argument("promenljiva nije definisana");
        
        auto it = _promenljive.find(s);
        return it->second;
    }
};

class Izraz { // interfejs
public:
    virtual ~Izraz() {}
    virtual double Vrednost(const Okolina& o) const = 0;
    virtual void Ispisi(std::ostream& s) const = 0;
    virtual Izraz* Kopija() const = 0;
    virtual Izraz* Uprosti(const Okolina& o, const std::string& s) const = 0;
    virtual Izraz* Izvod(const Okolina& o, const std::string& s) const = 0;
};

std::ostream& operator <<(std::ostream& s, const Izraz& i) {    
    i.Ispisi(s);
    return s;
}

class Konstanta : public Izraz {
private: 
    double _vrednost;

public:
    Konstanta(double v) {
        _vrednost = v;
    }

    Konstanta(const Konstanta& k) {
        _vrednost = k._vrednost;
    }

    double Vrednost(const Okolina& o) const {
        return _vrednost;
    }

    void Ispisi(std::ostream& s) const {
        s << _vrednost;
    }

    Izraz* Kopija() const {
        return new Konstanta(*this);
    }

    virtual Izraz* Uprosti(const Okolina& o, const std::string& s) const {
        return new Konstanta(*this);
    }

    virtual Izraz* Izvod(const Okolina& o, const std::string& s) const {
        return new Konstanta(0);
    }
};

class Promenljiva : public Izraz {
private:
    std::string _ime;

public:
    Promenljiva(const std::string& s) {
        _ime = s;
    }

    Promenljiva(const Promenljiva& p) {
        _ime = p._ime;
    }

    double Vrednost(const Okolina& o) const {        
        if (!o.PromenljivaDefinisana(_ime))
            throw std::invalid_argument("Promenljiva nije definisana");
        return o.VrednostPromenljive(_ime);
    }

    void Ispisi(std::ostream& s) const {
        s << _ime;
    }

    Izraz* Kopija() const {
        return new Promenljiva(*this);
    }

    virtual Izraz* Uprosti(const Okolina& o, const std::string& s) const {
        if (s == _ime && o.PromenljivaDefinisana(s)) 
            return new Konstanta(o.VrednostPromenljive(s));
        else 
            return new Promenljiva(*this);        
    }

    virtual Izraz* Izvod(const Okolina& o, const std::string& s) const {
        if (s == _ime) 
            return new Konstanta(1);
        else 
            return new Konstanta(0);
    }
};

class BinarniOperator : public Izraz {
protected:
    Izraz *levi, *desni;

public:
    BinarniOperator(Izraz* l, Izraz* d) : levi(l), desni(d) {} // plitko kopiranje

    ~BinarniOperator() {
        delete levi;
        delete desni;
    }

    BinarniOperator(const BinarniOperator& b) {
        levi = b.levi->Kopija();
        desni = b.desni->Kopija();
    }

    virtual double Vrednost(const Okolina& a) const = 0;
    virtual void Ispisi(std::ostream& s) const = 0;
    virtual Izraz* Kopija() const = 0;
    virtual Izraz* Uprosti(const Okolina& o, const std::string& s) const = 0;
    virtual Izraz* Izvod(const Okolina& o, const std::string& s) const = 0;
};

class Zbir : public BinarniOperator {
public: 

    Zbir(Izraz* l, Izraz* d) : BinarniOperator(l, d) {}
    Zbir(const Zbir& z) : BinarniOperator(z) {}

    double Vrednost(const Okolina& o) const {
        try {
            return levi->Vrednost(o) + desni->Vrednost(o);
        }
        catch (std::invalid_argument& s){
            throw s;
        }
    }

    void Ispisi(std::ostream& s) const {
        s << "( PLUS " << (*levi) << " " << (*desni) << ") ";
    }

    Izraz* Kopija() const {
        return new Zbir(*this);
    }

    Izraz* Uprosti(const Okolina& o, const std::string& s) const {
        Izraz* l = levi->Uprosti(o, s);
        Izraz* d = desni->Uprosti(o, s);

        if (dynamic_cast<Konstanta*>(l) != nullptr && dynamic_cast<Konstanta*>(d) != nullptr) {
            Izraz* rez = new Konstanta(l->Vrednost(o) + d->Vrednost(o));
            delete l; 
            delete d;
            return rez;
        }
        else {
            return new Zbir(l,d);
        }
    }

    Izraz* Izvod(const Okolina& o, const std::string& s) const {
        Izraz* l = levi->Izvod(o, s);
        Izraz* d = desni->Izvod(o, s);

        if (dynamic_cast<Konstanta*>(l) != nullptr && dynamic_cast<Konstanta*>(d) != nullptr) {
            Izraz* rez = new Konstanta(l->Vrednost(o) + d->Vrednost(o));
            delete l; 
            delete d;
            return rez;
        }
        else {
            return new Zbir(l,d);
        }
    }
};

class Razlika : public BinarniOperator {

public: 
    Razlika(Izraz* l, Izraz* d) : BinarniOperator(l, d) { }
    Razlika(const Razlika& z) : BinarniOperator(z){ }

    double Vrednost(const Okolina& o) const {
        try {
            return levi->Vrednost(o) - desni->Vrednost(o);
        }
        catch (std::invalid_argument& s){
            throw s;
        }
    }

    void Ispisi(std::ostream& s) const {
        s << "( MINUS " << (*levi) << " " << (*desni) << ") ";
    }

    Izraz* Kopija() const  {
        return new Razlika(*this);
    }


    Izraz* Uprosti(const Okolina& o, const std::string& s) const {
        Izraz* l = levi->Uprosti(o, s);
        Izraz* d = desni->Uprosti(o, s);

        if (dynamic_cast<Konstanta*>(l) != nullptr && dynamic_cast<Konstanta*>(d) != nullptr) {
            Izraz* rez = new Konstanta(l->Vrednost(o) - d->Vrednost(o));
            delete l; 
            delete d;
            return rez;
        }
        else 
            return new Razlika(l,d);
    }

    Izraz* Izvod(const Okolina& o, const std::string& s) const {
        Izraz* l = levi->Uprosti(o, s);
        Izraz* d = desni->Uprosti(o, s);

        if (dynamic_cast<Konstanta*>(l) != nullptr && dynamic_cast<Konstanta*>(d) != nullptr) {
            Izraz* rez = new Konstanta(l->Vrednost(o) - d->Vrednost(o));
            delete l; 
            delete d;
            return rez;
        }
        else 
            return new Razlika(l,d);
    }
};

class Proizvod : public BinarniOperator {
public: 
    Proizvod(Izraz* l, Izraz* d) : BinarniOperator(l, d) { }
    Proizvod(const Razlika& z) : BinarniOperator(z){ }

    double Vrednost(const Okolina& o) const {
        try {
            return levi->Vrednost(o) * desni->Vrednost(o);
        }
        catch (std::invalid_argument& s){
            throw s;
        }
    }

    void Ispisi(std::ostream& s) const {
        s << "( PUTA " << (*levi) << " " << (*desni) << ") ";
    }

    Izraz* Kopija() const  {
        return new Proizvod(*this);
    }

    Izraz* Uprosti(const Okolina& o, const std::string& s) const  {
        Izraz* l = levi->Uprosti(o, s);
        Izraz* d = desni->Uprosti(o, s);

        if (dynamic_cast<Konstanta*>(l) != nullptr && dynamic_cast<Konstanta*>(d) != nullptr) {
            Izraz* rez = new Konstanta(l->Vrednost(o) * d->Vrednost(o));
            delete l; 
            delete d;
            return rez;
        }
        else 
            return new Proizvod(l,d);
    }

    Izraz* Izvod(const Okolina& o, const std::string& s) const {
        Izraz *il = levi->Izvod(o, s);
        Izraz *id = desni->Izvod(o, s);
        Izraz* ll = new Proizvod(il, desni->Kopija());
        Izraz* dd = new Proizvod(levi->Kopija(), id);
        return new Zbir(ll, dd);
    }
};

class Kolicnik : public BinarniOperator {
public: 
    Kolicnik(Izraz* l, Izraz* d) : BinarniOperator(l, d) { }
    Kolicnik(const Razlika& z) : BinarniOperator(z){ }
  
    double Vrednost(const Okolina& o) const {
        if (desni->Vrednost(o) != 0)
            return levi->Vrednost(o) / desni->Vrednost(o);
        else 
            throw std::invalid_argument("Deljenje nulom");
    }

    void Ispisi(std::ostream& s) const {
        s << "( PODELJENO " << (*levi) << " " << (*desni) << ") ";
    }

    Izraz* Kopija() const  {
        return new Kolicnik(*this);
    }

    Izraz* Uprosti(const Okolina& o, const std::string& s) const  {
        Izraz* l = levi->Uprosti(o, s);
        Izraz* d = desni->Uprosti(o, s);

        if (dynamic_cast<Konstanta*>(l) != nullptr && dynamic_cast<Konstanta*>(d) != nullptr) {
            Izraz* rez = new Konstanta(l->Vrednost(o) / d->Vrednost(o));
            delete l; 
            delete d;
            return rez;
        }
        else 
            return new Kolicnik(l,d);
    }

    Izraz* Izvod(const Okolina& o, const std::string& s) const {
        Izraz *il = levi->Izvod(o, s);
        Izraz *id = desni->Izvod(o, s);
        Izraz* ll = new Proizvod(il, desni->Kopija());
        Izraz* dd = new Proizvod(levi->Kopija(), id);
        Izraz* gore = new Razlika(ll, dd);
        Izraz* dole = new Proizvod(desni->Kopija(), desni->Kopija());
        return new Kolicnik(gore, dole);
    }
};

class Funkcija : public Izraz {

protected:
    Izraz* izraz;
public:
    Funkcija(Izraz* i) : izraz(i) { }
    Funkcija(const Funkcija& f) {
        izraz = f.izraz->Kopija();
    }
    virtual ~Funkcija() {
        delete izraz;
    }

    virtual double Vrednost(const Okolina& a) const = 0;
    virtual void Ispisi(std::ostream& s) const = 0;
    virtual Izraz* Kopija() const = 0;
    virtual Izraz* Uprosti(const Okolina& o, const std::string& s) const = 0;
    virtual Izraz* Izvod(const Okolina& o, const std::string& s) const = 0;
};

class Suprotni : public Funkcija {
public:
    Suprotni(Izraz* i) : Funkcija(i) { }
    Suprotni(const Suprotni& s) : Funkcija(s) { }

    double Vrednost(const Okolina& a) const {
        return -izraz->Vrednost(a);
    }

    void Ispisi(std::ostream& s) const {
        s << "SUPROTNI ( " << (*izraz) << ") "; 
    }

    Izraz* Kopija() const {
        return new Suprotni(*this);
    }

    Izraz* Uprosti(const Okolina& o, const std::string& s) const {
        Izraz* l = izraz->Uprosti(o, s);
        if (dynamic_cast<Konstanta*>(l) != nullptr) {
            Izraz* rez = new Konstanta(-l->Vrednost(o));
            delete l;
            return rez;
        }
        else 
            return new Suprotni(l);
    }

    Izraz* Izvod(const Okolina& o, const std::string& s) const {
        Izraz* l = izraz->Izvod(o, s);
        if (dynamic_cast<Konstanta*>(l) != nullptr) {
            Izraz* rez = new Konstanta(-l->Vrednost(o));
            delete l;
            return rez;
        }
        else 
            return new Suprotni(l);
    }
};

class Sin : public Funkcija {

public:
    Sin(Izraz* i) : Funkcija(i) { }
    Sin(const Sin& s) : Funkcija(s) { }

    double Vrednost(const Okolina& a) const {
        return sin(-izraz->Vrednost(a));
    }

    void Ispisi(std::ostream& s) const {
        s << "SIN ( " << (*izraz) << ") "; 
    }

    Izraz* Kopija() const {
        return new Sin(*this);
    }

    Izraz* Uprosti(const Okolina& o, const std::string& s) const {
        Izraz* l = izraz->Uprosti(o, s);
        if (dynamic_cast<Konstanta*>(l) != nullptr) {
            Izraz* rez = new Konstanta(sin(l->Vrednost(o)));
            delete l;
            return rez;
        }
        else 
            return new Sin(l);
    }

    Izraz* Izvod(const Okolina& o, const std::string& s) const;
};

class Cos : public Funkcija {
public:
    Cos(Izraz* i) : Funkcija(i) { }
    Cos(const Cos& s) : Funkcija(s) { }

    double Vrednost(const Okolina& a) const {
        return cos(-izraz->Vrednost(a));
    }

    void Ispisi(std::ostream& s) const {
        s << "COS ( " << (*izraz) << ") "; 
    }

    Izraz* Kopija() const {
        
        return new Cos(*this);
    }

    Izraz* Uprosti(const Okolina& o, const std::string& s) const {
        Izraz* l = izraz->Uprosti(o, s);
        if (dynamic_cast<Konstanta*>(l) != nullptr) {
            Izraz* rez = new Konstanta(cos(l->Vrednost(o)));
            delete l;
            return rez;
        }
        else 
            return new Cos(l);
    }

    Izraz* Izvod(const Okolina& o, const std::string& s) const {
        Izraz* l = izraz->Izvod(o, s);
        return new Suprotni(new Proizvod(new Sin(izraz->Kopija()), l));
    }
};

Izraz* Sin::Izvod(const Okolina& o, const std::string& s) const {
        Izraz* l = izraz->Izvod(o, s);
        return new Proizvod(new Cos(izraz->Kopija()), l);
    }

class Tan : public Funkcija {
public:
    Tan(Izraz* i) : Funkcija(i) { }
    Tan(const Tan& s) : Funkcija(s) { }

    double Vrednost(const Okolina& a) const {
        return tan(-izraz->Vrednost(a));
    }

    void Ispisi(std::ostream& s) const {
        s << "TAN ( " << (*izraz) << ") "; 
    }

    Izraz* Kopija() const {
        return new Tan(*this);
    }

    Izraz* Uprosti(const Okolina& o, const std::string& s) const {
        Izraz* l = izraz->Uprosti(o, s);
        if (dynamic_cast<Konstanta*>(l) != nullptr) {
            Izraz* rez = new Konstanta(tan(l->Vrednost(o)));
            delete l;
            return rez;
        }
        else 
            return new Tan(l);
    }

    Izraz* Izvod(const Okolina& o, const std::string& s) const {
        Izraz* l = izraz->Izvod(o, s);
        return new Kolicnik(l, new Proizvod(new Cos(izraz->Kopija()), new Cos(izraz->Kopija())));
    }
};

class Cot : public Funkcija {
public:
    Cot(Izraz* i) : Funkcija(i) { }
    Cot(const Cot& s) : Funkcija(s) { }

    double Vrednost(const Okolina& a) const {
        double x = -izraz->Vrednost(a);
        return cos(x)/sin(x);
    }

    void Ispisi(std::ostream& s) const {
        s << "COT ( " << (*izraz) << ") "; 
    }

    Izraz* Kopija() const {
        return new Cot(*this);
    }

    Izraz* Uprosti(const Okolina& o, const std::string& s) const {
        Izraz* l = izraz->Uprosti(o, s);
        if (dynamic_cast<Konstanta*>(l) != nullptr) {
            double x = l->Vrednost(o);
            Izraz* rez = new Konstanta(cos(x)/sin(x));
            delete l;
            return rez;
        }
        else 
            return new Cot(l);
    }

    Izraz* Izvod(const Okolina& o, const std::string& s) const {
        Izraz* l = izraz->Izvod(o, s);
        return new Kolicnik(new Suprotni(l), new Proizvod(new Sin(izraz->Kopija()), new Sin(izraz->Kopija())));
    }
};

class Log : public Funkcija {
public:
    Log(Izraz* i) : Funkcija(i) { }
    Log(const Log& s) : Funkcija(s) { }

    double Vrednost(const Okolina& a) const {   
        return log(izraz->Vrednost(a));
    }

    void Ispisi(std::ostream& s) const {
        s << "LOG ( " << (*izraz) << ") "; 
    }

    Izraz* Kopija() const { 
        return new Log(*this);
    }

    Izraz* Uprosti(const Okolina& o, const std::string& s) const {
        Izraz* l = izraz->Uprosti(o, s);
        if (dynamic_cast<Konstanta*>(l) != nullptr) {
            double x = l->Vrednost(o);
            Izraz* rez = new Konstanta(log(x));
            delete l;
            return rez;
        }
        else 
            return new Log(l);
    }

    Izraz* Izvod(const Okolina& o, const std::string& s) const {
        Izraz* l = izraz->Izvod(o, s);
        return new Proizvod(new Kolicnik(new Konstanta(1), izraz->Kopija()), l);
    }
};

class Exp : public Funkcija {
public:
    Exp(Izraz* i) : Funkcija(i) { }
    Exp(const Exp& s) : Funkcija(s) { }

    double Vrednost(const Okolina& a) const {   
        return exp(izraz->Vrednost(a));
    }

    void Ispisi(std::ostream& s) const {
        s << "EXP ( " << (*izraz) << ") "; 
    }

    Izraz* Kopija() const {
        return new Exp(*this);
    }

    Izraz* Uprosti(const Okolina& o, const std::string& s) const {
        Izraz* l = izraz->Uprosti(o, s);
        if (dynamic_cast<Konstanta*>(l) != nullptr) {
            double x = l->Vrednost(o);
            Izraz* rez = new Konstanta(exp(x));
            delete l;
            return rez;
        }
        else 
            return new Log(l);
    }

    Izraz* Izvod(const Okolina& o, const std::string& s) const {
        Izraz* l = izraz->Izvod(o, s);
        return new Proizvod(new Exp(izraz->Kopija()), l);
    }
};

class Sqrt : public Funkcija {
public:
    Sqrt(Izraz* i) : Funkcija(i) { }
    Sqrt(const Sqrt& s) : Funkcija(s) { }

    double Vrednost(const Okolina& a) const {
        return sqrt(izraz->Vrednost(a));
    }

    void Ispisi(std::ostream& s) const {
        s << "SQRT ( " << (*izraz) << ") "; 
    }

    Izraz* Kopija() const {
        return new Sqrt(*this);
    }

    Izraz* Uprosti(const Okolina& o, const std::string& s) const {
        Izraz* l = izraz->Uprosti(o, s);
        if (dynamic_cast<Konstanta*>(l) != nullptr) {
            double x = l->Vrednost(o);
            Izraz* rez = new Konstanta(sqrt(x));
            delete l;
            return rez;
        }
        else 
            return new Log(l);
    }

    Izraz* Izvod(const Okolina& o, const std::string& s) const {
        Izraz* l = izraz->Izvod(o, s);
        return new Kolicnik(new Suprotni(l), new Proizvod(new Konstanta(2), new Sqrt(izraz->Kopija())));
    }
};

int main() {

    Okolina o;
    o.DodajPromenljivu("x", 5);
    o.DodajPromenljivu("y", 10);

    Izraz* i1 = new Kolicnik(new Promenljiva("x"), new Sin(new Konstanta(2)));
    Izraz* i2 = new Proizvod(new Exp(new Sqrt(new Konstanta(3.14))), new Promenljiva("x"));
    Izraz* i3 = new Razlika(new Promenljiva("y"), i2->Kopija());
    Izraz* i4 = new Zbir(i1->Kopija(), i3->Kopija());

    std::cout << (*i4) << "=" << (i4->Vrednost(o)) << std::endl;

    Izraz* izvod = i4->Izvod(o, "x'");
    std::cout << (*izvod) << "=" << (izvod->Vrednost(o)) << std::endl;

    Izraz* i5 = i4->Uprosti(o, "x");
    std::cout << (*i5) << "=" << (i5->Vrednost(o)) << std::endl;

    Izraz* i6 = i5->Uprosti(o, "y");
    std::cout << (*i6) << "=" << (i6->Vrednost(o)) << std::endl;

    delete i5;
    delete i4;
    delete i6;
    delete izvod;

    return 0;
}