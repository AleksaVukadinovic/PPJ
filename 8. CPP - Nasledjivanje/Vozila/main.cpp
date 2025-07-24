#include <deque>
#include <iostream>

class Vozilo {
public:
  Vozilo() { std::cout << "Kreiram vozilo" << std::endl; }
  virtual ~Vozilo() { std::cout << "Unistavam vozilo" << std::endl; }

  virtual std::string Vrsta() const = 0;
  virtual int BrojProzora() const = 0;
  virtual int BrojTockova() const = 0;
  virtual int BrojSedista() const = 0;
  virtual Vozilo *kopija() const = 0;
};

class Automobil : public Vozilo {
public:
  Automobil() { std::cout << "Kreiram automobil" << std::endl; }
  ~Automobil() { std::cout << "Unistavam automobil" << std::endl; }

  virtual std::string Vrsta() const { return "Automobil"; }

  virtual int BrojProzora() const = 0;
  int BrojTockova() const { return 4; }
  virtual int BrojSedista() const = 0;
  virtual Vozilo *kopija() const = 0;
};

class Kamion : public Vozilo {
public:
  Kamion() { std::cout << "Kreiram kamion" << std::endl; }
  ~Kamion() { std::cout << "Unistavam kamion" << std::endl; }
  Kamion(const Kamion &k) {
    std::cout << "Kreiram kopiju kamiona" << std::endl;
  }

  std::string Vrsta() const { return "Kamion"; }
  int BrojProzora() const { return 4; }
  int BrojTockova() const { return 6; }
  int BrojSedista() const { return 2; }
  Vozilo *kopija() const { return new Kamion(*this); }
};

class Kombi : public Vozilo {
public:
  Kombi() { std::cout << "Kreiram kombi" << std::endl; }
  ~Kombi() { std::cout << "Unistavam kombi" << std::endl; }
  Kombi(const Kombi &k) { std::cout << "Kreiram kopiju kombija" << std::endl; }

  std::string Vrsta() const { return "Kombi"; }
  int BrojProzora() const { return 5; }
  int BrojTockova() const { return 4; }
  int BrojSedista() const { return 3; }
  Vozilo *kopija() const { return new Kombi(*this); }
};

class SportskiAutomobil : public Automobil {
public:
  SportskiAutomobil() {
    std::cout << "Kreiram sportski automobil" << std::endl;
  }
  ~SportskiAutomobil() {
    std::cout << "Unistavam sportski automobil" << std::endl;
  }
  SportskiAutomobil(const SportskiAutomobil &k) {
    std::cout << "Kreiram kopiju sportskog automobila" << std::endl;
  }

  std::string Vrsta() const {
    return Automobil::Vrsta() + " -> Sportski Automobil";
  }
  int BrojProzora() const { return 6; }
  int BrojTockova() const { return 4; }
  int BrojSedista() const { return 2; }
  Vozilo *kopija() const { return new SportskiAutomobil(*this); }
};

class Sedan : public Automobil {
public:
  Sedan() { std::cout << "Kreiram sedan" << std::endl; }
  ~Sedan() { std::cout << "Unistavam sedan" << std::endl; }
  Sedan(const Sedan &k) { std::cout << "Kreiram kopiju sedan" << std::endl; }

  std::string Vrsta() const { return Automobil::Vrsta() + " -> Sedan"; }
  int BrojProzora() const { return 6; }
  int BrojTockova() const { return 4; }
  int BrojSedista() const { return 4; }
  Vozilo *kopija() const { return new Sedan(*this); }
};

class Karavan : public Automobil {
public:
  Karavan() { std::cout << "Kreiram karavan" << std::endl; }
  ~Karavan() { std::cout << "Unistavam karavan" << std::endl; }
  Karavan(const Karavan &k) {
    std::cout << "Kreiram kopiju karavana" << std::endl;
  }

  std::string Vrsta() const { return Automobil::Vrsta() + " -> Karavan"; }
  int BrojProzora() const { return 8; }
  int BrojTockova() const { return 4; }
  int BrojSedista() const { return 4; }
  Vozilo *kopija() const { return new Karavan(*this); }
};

class Perionica {
private:
  std::deque<Vozilo *> _red;
  Vozilo *prviNaRedu() {
    Vozilo *v = _red.front();
    _red.pop_front();
    return v;
  }

  void isprazniRed() {
    while (!_red.empty())
      delete prviNaRedu();
  }

  void popuniRed(const std::deque<Vozilo *> &red) {
    for (auto it = red.begin(); it != red.end(); it++)
      _red.push_back((*it)->kopija());
  }

  int odrediCenu(Vozilo *v) {
    int osnovnaCena = 800;
    if (dynamic_cast<Automobil *>(v) != nullptr)
      osnovnaCena +=
          20 * v->BrojTockova() + 40 * v->BrojProzora() + 60 * v->BrojSedista();
    else if (dynamic_cast<Kamion *>(v) != nullptr)
      osnovnaCena *= 3;
    else if (dynamic_cast<Kombi *>(v) != nullptr)
      osnovnaCena *= 2;

    return osnovnaCena;
  }

public:
  Perionica() : _red() { std::cout << "Kreiram perionicu" << std::endl; }
  ~Perionica() {
    std::cout << "Unistavam red" << std::endl;
    isprazniRed();
    std::cout << "Unisten red" << std::endl;
  }

  Perionica(const Perionica &p) : _red() { popuniRed(p._red); }
  Perionica &operator=(const Perionica &p) {
    if (this == &p)
      return *this;
    isprazniRed();
    popuniRed(p._red);
    return *this;
  }

  void DodajVozilo(Vozilo *v) { _red.push_back(v); }

  void OperiVozilo() {
    if (!_red.empty()) {
      Vozilo *v = prviNaRedu();
      std::cout << "Na redu je: " << std::endl
                << "\tTip vozila: " << v->Vrsta()
                << "\tBroj tockova: " << v->BrojTockova()
                << "\tBroj sedista: " << v->BrojSedista()
                << "\tBroj Prozora: " << v->BrojProzora()
                << "\tCena: " << odrediCenu(v) << std::endl;
      delete v;
    } else
      std::cout << "Perionica je prazna" << std::endl;
  }

  bool NekoCeka() { return !_red.empty(); }
};

int main() {
  Kamion *k = new Kamion();
  delete k;

  Perionica p;
  p.DodajVozilo(new Kamion());
  p.DodajVozilo(new Kombi());
  p.DodajVozilo(new SportskiAutomobil());
  p.DodajVozilo(new Karavan());
  p.DodajVozilo(new Sedan());

  while (p.NekoCeka())
    p.OperiVozilo();

  return 0;
}