#include <iostream>
#include <queue>

class Vozilo {
public:
    Vozilo() {
        std::cout << "Kreiram vozilo\n"; // za proveru
    }
    virtual ~Vozilo() {
        std::cout << "Unistavam vozilo\n";
    }

    virtual std::string Vrsta() const = 0;
    virtual int brojProzora() const = 0;
    virtual int brojTockova() const = 0;
    virtual int brojSedista() const = 0;
    virtual Vozilo* kopija() const = 0;
};

class Automobil : public Vozilo {
public:
    Automobil() {
        std::cout<< "Kreiram automobil\n";
    }
    ~Automobil() {
        std::cout << "Unistavam automobil\n";
    }

    virtual std::string Vrsta() const {
        return "Automobil";
    }

    int brojTockova() const {
        return 4;
    }

    virtual int brojSedista() const = 0;
    virtual Vozilo* kopija() const = 0;
};

class Kamion : public Vozilo {
public:
    Kamion() {
        std::cout << "Kreiram kamion" << std::endl;
    }

    Kamion(const Kamion& k){
        std::cout << "Kreiram kopiju kamiona" << std::endl;
    }

    ~Kamion() {
        std::cout << "Unistavam kamion" << std::endl;
    }

    std::string Vrsta() const {
        return "Kamion";
    }

    int brojProzora() const {
        return 4;
    }

    int brojTockova() const {
        return 6;
    }

    int brojSedista() const {
        return 2;
    }

    Vozilo* kopija() const {
        return new Kamion(*this);
    }
};

class Kombi: public Vozilo {
public:
    Kombi() {
        std::cout << "Kreiram kombi" << std::endl;
    }
    Kombi(const Kombi& k) {
        std::cout << "Kreiram kopiju kombija" << std::endl;
    }
    ~Kombi() {
        std::cout << "Unistavam kombi" << std::endl;
    }

    std::string Vrsta() const {
        return "Kombi";
    }
    int brojProzora() const {
        return 5;
    }
    int brojTockova() const {
        return 4;
    }
    int brojSedista() const {
        return 3;
    }

    Vozilo* kopija() const {
        return new Kombi(*this);
    }
};


class SportskiAutomobil : public Automobil {
public:
    SportskiAutomobil() {
        std::cout << "Kreiram sportski automobil" << std::endl;
    }
    SportskiAutomobil(const SportskiAutomobil& sa) {
        std::cout << "Kreiram kopiju sportskog automobila" << std::endl;
    }
    ~SportskiAutomobil() {
        std::cout << "Unistavam sportski automobil" << std::endl;
    }

    std::string Vrsta() const {
        return Automobil::Vrsta() + " -> Sportski Automobil";
    }

    int brojProzora() const {
        return 6;
    }

    int brojSedista() const {
        return 2;
    }

    int brojTockova() const {
        return 4;
    }

    Vozilo* kopija() const {
        return new SportskiAutomobil(*this);
    }
};

class Sedan: public Automobil {
public:
    Sedan() {
        std::cout <<  "Kreiram sedan" << std::endl;
    }
    Sedan(const Sedan& k) {
        std::cout << "Kreiram kopiju sedan" << std::endl;
    }
    ~Sedan() {
        std::cout << "Unistavam sedan" << std::endl;
    }

    std::string Vrsta() const {
        return Automobil::Vrsta() + " -> Karavan";
    }

    int brojProzora() const {
        return 6;
    }
    int brojTockova() const {
        return 4;
    }
    int brojSedista() const {
        return 4;
    }

    Vozilo* kopija() const {
        return new Sedan(*this);
    }
};

class Karavan: public Automobil {
public:
    Karavan() {
        std::cout <<  "Kreiram karavan" << std::endl;
    }
    Karavan(const Karavan& k) {
        std::cout << "Kreiram kopiju karavana" << std::endl;
    }
    ~Karavan() {
        std::cout << "Unistavam sedan" << std::endl;
    }

    std::string Vrsta() const {
        return Automobil::Vrsta() + " -> Karavan";
    }

    int brojProzora() const {
        return 6;
    }
    int brojTockova() const {
        return 4;
    }
    int brojSedista() const {
        return 4;
    }

    Vozilo* kopija() const {
        return new Karavan(*this);
    }
};



class Perionica {
private:
    std::deque<Vozilo*> red;

    Vozilo* prviNaRedu() {
        Vozilo* v = red.front();
        red.pop_front();
        return v;
    }

    void isprazniRed() {
        while(!red.empty())
            delete prviNaRedu();
    }      

    void popuniRed(const std::deque<Vozilo*>& red) {
        for(auto it = red.begin(); it!=red.end(); it++)
            this->red.push_back((*it)->kopija());
    }

    int odrediCenu(Vozilo* v) {
        int osnovnaCena = 800;

        /* tip vozila mozemo da proverimo pomocu operatora dynamic_cast 
         * ukoliko se ne radi o objektu klase u koju zelimo da kastujemo, 
         * dynamic_cast<> vraca nullptr.
         */
        if (dynamic_cast<Automobil*>(v) != nullptr) {
            osnovnaCena += 20*v->brojTockova() + 40*v->brojProzora() + 60*v->brojSedista();
        }
        else if (dynamic_cast<Kamion*>(v) != nullptr) {
            osnovnaCena *= 3;
        }
        else if (dynamic_cast<Kombi*>(v) != nullptr) {
            osnovnaCena*=2;
        }

        return osnovnaCena;
    }

public:
    Perionica() {
        std::deque<Vozilo*> red;
        std::cout << "Kreiram perionicu" << std::endl;
    }

    Perionica(const Perionica& p) {
        std::deque<Vozilo*> red;
        popuniRed(p.red);
    }

    ~Perionica() {
        std::cout << "Unistavam red" << std::endl;
        isprazniRed();
        std::cout << "Unisten red" << std::endl;
    }

    Perionica& operator =(const Perionica& p) {
        if (this == &p)
            return *this;
        
        isprazniRed();
        popuniRed(p.red);

        return *this;
    }

    void dodajVozilo(Vozilo* v) {
        red.push_back(v);
    }

    void operiVozilo() {
        if(!red.empty()) {
            Vozilo* v = prviNaRedu();
            std::cout << "Na redu je: " << std::endl
                      << "\tTip vozila: " << v->Vrsta()
                      << "\tBroj tockova: " << v->brojTockova()
                      << "\tBroj sedista: " << v->brojSedista()
                      << "\tBroj Prozora: " << v->brojProzora()
                      << "\tCena: " << odrediCenu(v)
                      << std::endl;
            delete v;
        } else {
            std::cout << "Perionica je prazna" << std::endl;
        }
    }

    bool nekoCeka() {
        return !red.empty();
    }
};


int main() {

    Perionica p;

    p.dodajVozilo(new Kamion());
    p.dodajVozilo(new Kombi());
    p.dodajVozilo(new SportskiAutomobil());
    p.dodajVozilo(new Karavan());
    p.dodajVozilo(new Sedan());

    while (p.nekoCeka())
        p.operiVozilo();

    return 0;
}