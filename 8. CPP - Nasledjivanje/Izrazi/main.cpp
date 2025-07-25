#include <cmath>
#include <exception>
#include <iostream>
#include <map>

class Okolina {
private:
  std::map<std::string, double> _promenljive;

public:
  Okolina() {}

  bool dodaj_promenljivu(const std::string &s, double v = 0) {
    if (promenljiva_definisana(s))
      return false;
    _promenljive[s] = v;
    return true;
  }

  bool promenljiva_definisana(const std::string &s) const {
    auto it = _promenljive.find(s);
    return it != _promenljive.end();
  }

  double vrednost_promenljive(const std::string &s) const {
    if (!promenljiva_definisana(s))
      throw std::invalid_argument("Promenljiva nije definisana!");
    auto it = _promenljive.find(s);
    return it->second;
  }

  void izmeni_vrednost_promenljive(const std::string &s, const double v) {
    if (!promenljiva_definisana(s))
      throw std::invalid_argument("Promenljiva nije definisana!");
    _promenljive[s] = v;
  }

  double &operator[](std::string &s) {
    if (!promenljiva_definisana(s))
      throw std::invalid_argument("Promenljiva nije definisana!");
    auto it = _promenljive.find(s);
    return it->second;
  }

  double operator[](std::string &s) const {
    if (!promenljiva_definisana(s))
      throw std::invalid_argument("promenljiva nije definisana");
    auto it = _promenljive.find(s);
    return it->second;
  }
};

class Izraz {
public:
  virtual ~Izraz() {}

  virtual double vrednost(const Okolina &o) const = 0;
  virtual void ispisi(std::ostream &s) const = 0;
  virtual Izraz *kopija() const = 0;
  virtual Izraz *uprosti(const Okolina &o, const std::string &s) const = 0;
  virtual Izraz *izvod(const Okolina &o, const std::string &s) const = 0;
};

std::ostream &operator<<(std::ostream &s, const Izraz &i) {
  i.ispisi(s);
  return s;
}

class Konstanta : public Izraz {
private:
  double _vrednost;

public:
  Konstanta(const double v) : _vrednost(v) {}
  Konstanta(const Konstanta &k) : _vrednost(k._vrednost) {}
  ~Konstanta() {}

  double vrednost(const Okolina &o) const { return _vrednost; }
  void ispisi(std::ostream &s) const { s << _vrednost; }
  Izraz *kopija() const { return new Konstanta(*this); }
  Izraz *uprosti(const Okolina &o, const std::string &s) const {
    return new Konstanta(*this);
  }
  Izraz *izvod(const Okolina &o, const std::string &s) const {
    return new Konstanta(0);
  }
};

class Promenljiva : public Izraz {
private:
  std::string _naziv;

public:
  Promenljiva(const std::string &s) : _naziv(s) {}
  Promenljiva(const Promenljiva &p) : _naziv(p._naziv) {}
  ~Promenljiva() {}

  double vrednost(const Okolina &o) const {
    return o.vrednost_promenljive(_naziv);
  }
  void ispisi(std::ostream &s) const { s << _naziv; }
  Izraz *kopija() const { return new Promenljiva(*this); }
  Izraz *uprosti(const Okolina &o, const std::string &s) const {
    if (s == _naziv && o.promenljiva_definisana(s))
      return new Konstanta(o.vrednost_promenljive(_naziv));
    else
      return new Promenljiva(*this);
  }
  Izraz *izvod(const Okolina &o, const std::string &s) const {
    if (s == _naziv)
      return new Konstanta(1);
    else
      return new Konstanta(0);
  }
};

class BinarniOperator : public Izraz {
protected:
  Izraz *_levi, *_desni;

public:
  BinarniOperator(Izraz *l, Izraz *d) : _levi(l), _desni(d) {}
  BinarniOperator(const BinarniOperator &b)
      : _levi(b._levi->kopija()), _desni(b._desni->kopija()) {}
  ~BinarniOperator() {
    delete _levi;
    delete _desni;
  }

  virtual double vrednost(const Okolina &o) const = 0;
  virtual void ispisi(std::ostream &s) const = 0;
  virtual Izraz *kopija() const = 0;
  virtual Izraz *uprosti(const Okolina &o, const std::string &s) const = 0;
  virtual Izraz *izvod(const Okolina &o, const std::string &s) const = 0;
};

class Zbir : public BinarniOperator {
public:
  Zbir(Izraz *l, Izraz *d) : BinarniOperator(l, d) {}
  Zbir(const Zbir &z) : BinarniOperator(z) {}
  ~Zbir() {}

  double vrednost(const Okolina &o) const {
    try {
      return _levi->vrednost(o) + _desni->vrednost(o);
    } catch (std::invalid_argument &s) {
      throw s;
    }
  }
  void ispisi(std::ostream &s) const {
    s << "( PLUS " << (*_levi) << " " << (*_desni) << ") ";
  }
  Izraz *kopija() const { return new Zbir(*this); }
  Izraz *uprosti(const Okolina &o, const std::string &s) const {
    Izraz *l = _levi->uprosti(o, s);
    Izraz *d = _desni->uprosti(o, s);

    if (dynamic_cast<Konstanta *>(l) != nullptr &&
        dynamic_cast<Konstanta *>(d) != nullptr) {
      Izraz *rez = new Konstanta(l->vrednost(o) + d->vrednost(o));
      delete l;
      delete d;
      return rez;
    } else {
      return new Zbir(l, d);
    }
  }
  Izraz *izvod(const Okolina &o, const std::string &s) const {
    Izraz *l = _levi->izvod(o, s);
    Izraz *d = _desni->izvod(o, s);

    if (dynamic_cast<Konstanta *>(l) != nullptr &&
        dynamic_cast<Konstanta *>(d) != nullptr) {
      Izraz *rez = new Konstanta(l->vrednost(o) + d->vrednost(o));
      delete l;
      delete d;
      return rez;
    } else {
      return new Zbir(l, d);
    }
  }
};

class Razlika : public BinarniOperator {
public:
  Razlika(Izraz *l, Izraz *d) : BinarniOperator(l, d) {}
  Razlika(const Razlika &z) : BinarniOperator(z) {}
  ~Razlika() {}

  double vrednost(const Okolina &o) const {
    try {
      return _levi->vrednost(o) - _desni->vrednost(o);
    } catch (std::invalid_argument &s) {
      throw s;
    }
  }
  void ispisi(std::ostream &s) const {
    s << "( MINUS " << (*_levi) << " " << (*_desni) << ") ";
  }
  Izraz *kopija() const { return new Razlika(*this); }
  Izraz *uprosti(const Okolina &o, const std::string &s) const {
    Izraz *l = _levi->uprosti(o, s);
    Izraz *d = _desni->uprosti(o, s);

    if (dynamic_cast<Konstanta *>(l) != nullptr &&
        dynamic_cast<Konstanta *>(d) != nullptr) {
      Izraz *rez = new Konstanta(l->vrednost(o) - d->vrednost(o));
      delete l;
      delete d;
      return rez;
    } else {
      return new Razlika(l, d);
    }
  }
  Izraz *izvod(const Okolina &o, const std::string &s) const {
    Izraz *l = _levi->izvod(o, s);
    Izraz *d = _desni->izvod(o, s);

    if (dynamic_cast<Konstanta *>(l) != nullptr &&
        dynamic_cast<Konstanta *>(d) != nullptr) {
      Izraz *rez = new Konstanta(l->vrednost(o) - d->vrednost(o));
      delete l;
      delete d;
      return rez;
    } else {
      return new Razlika(l, d);
    }
  }
};

class Proizvod : public BinarniOperator {
public:
  Proizvod(Izraz *l, Izraz *d) : BinarniOperator(l, d) {}
  Proizvod(const Proizvod &z) : BinarniOperator(z) {}
  ~Proizvod() {}

  double vrednost(const Okolina &o) const {
    try {
      return _levi->vrednost(o) * _desni->vrednost(o);
    } catch (std::invalid_argument &s) {
      throw s;
    }
  }
  void ispisi(std::ostream &s) const {
    s << "( PUTA " << (*_levi) << " " << (*_desni) << ") ";
  }
  Izraz *kopija() const { return new Proizvod(*this); }
  Izraz *uprosti(const Okolina &o, const std::string &s) const {
    Izraz *l = _levi->uprosti(o, s);
    Izraz *d = _desni->uprosti(o, s);

    if (dynamic_cast<Konstanta *>(l) != nullptr &&
        dynamic_cast<Konstanta *>(d) != nullptr) {
      Izraz *rez = new Konstanta(l->vrednost(o) * d->vrednost(o));
      delete l;
      delete d;
      return rez;
    } else {
      return new Proizvod(l, d);
    }
  }
  Izraz *izvod(const Okolina &o, const std::string &s) const {
    Izraz *l = _levi->izvod(o, s);
    Izraz *d = _desni->izvod(o, s);

    if (dynamic_cast<Konstanta *>(l) != nullptr &&
        dynamic_cast<Konstanta *>(d) != nullptr) {
      Izraz *rez = new Konstanta(l->vrednost(o) * d->vrednost(o));
      delete l;
      delete d;
      return rez;
    } else {
      return new Proizvod(l, d);
    }
  }
};

class Kolicnik : public BinarniOperator {
public:
  Kolicnik(Izraz *l, Izraz *d) : BinarniOperator(l, d) {}
  Kolicnik(const Kolicnik &z) : BinarniOperator(z) {}
  ~Kolicnik() {}

  double vrednost(const Okolina &o) const {
    try {
      return _levi->vrednost(o) / _desni->vrednost(o);
    } catch (std::invalid_argument &s) {
      throw s;
    }
  }
  void ispisi(std::ostream &s) const {
    s << "( PODELJENO " << (*_levi) << " " << (*_desni) << ") ";
  }
  Izraz *kopija() const { return new Kolicnik(*this); }
  Izraz *uprosti(const Okolina &o, const std::string &s) const {
    Izraz *l = _levi->uprosti(o, s);
    Izraz *d = _desni->uprosti(o, s);

    if (dynamic_cast<Konstanta *>(l) != nullptr &&
        dynamic_cast<Konstanta *>(d) != nullptr) {
      Izraz *rez = new Konstanta(l->vrednost(o) / d->vrednost(o));
      delete l;
      delete d;
      return rez;
    } else {
      return new Kolicnik(l, d);
    }
  }
  Izraz *izvod(const Okolina &o, const std::string &s) const {
    Izraz *l = _levi->izvod(o, s);
    Izraz *d = _desni->izvod(o, s);

    if (dynamic_cast<Konstanta *>(l) != nullptr &&
        dynamic_cast<Konstanta *>(d) != nullptr) {
      Izraz *rez = new Konstanta(l->vrednost(o) / d->vrednost(o));
      delete l;
      delete d;
      return rez;
    } else {
      return new Kolicnik(l, d);
    }
  }
};

class Funkcija : public Izraz {
protected:
  Izraz *izraz;

public:
  Funkcija(Izraz *i) : izraz(i) {}
  Funkcija(const Funkcija &f) { izraz = f.izraz->kopija(); }
  virtual ~Funkcija() { delete izraz; }

  virtual double vrednost(const Okolina &a) const = 0;
  virtual void ispisi(std::ostream &s) const = 0;
  virtual Izraz *kopija() const = 0;
  virtual Izraz *uprosti(const Okolina &o, const std::string &s) const = 0;
  virtual Izraz *izvod(const Okolina &o, const std::string &s) const = 0;
};

class Suprotni : public Funkcija {
public:
  Suprotni(Izraz *i) : Funkcija(i) {}
  Suprotni(const Suprotni &s) : Funkcija(s) {}
  ~Suprotni() {}

  double vrednost(const Okolina &a) const { return -izraz->vrednost(a); }
  void ispisi(std::ostream &s) const { s << "SUPROTNI ( " << (*izraz) << ") "; }
  Izraz *kopija() const { return new Suprotni(*this); }
  Izraz *uprosti(const Okolina &o, const std::string &s) const {
    Izraz *l = izraz->uprosti(o, s);
    if (dynamic_cast<Konstanta *>(l) != nullptr) {
      Izraz *rez = new Konstanta(-l->vrednost(o));
      delete l;
      return rez;
    } else
      return new Suprotni(l);
  }
  Izraz *izvod(const Okolina &o, const std::string &s) const {
    Izraz *l = izraz->izvod(o, s);
    if (dynamic_cast<Konstanta *>(l) != nullptr) {
      Izraz *rez = new Konstanta(-l->vrednost(o));
      delete l;
      return rez;
    } else
      return new Suprotni(l);
  }
};

class Sin : public Funkcija {
public:
  Sin(Izraz *i) : Funkcija(i) {}
  Sin(const Sin &s) : Funkcija(s) {}
  double vrednost(const Okolina &a) const { return sin(izraz->vrednost(a)); }
  void ispisi(std::ostream &s) const { s << "SIN ( " << (*izraz) << ") "; }
  Izraz *kopija() const { return new Sin(*this); }
  Izraz *uprosti(const Okolina &o, const std::string &s) const {
    Izraz *l = izraz->uprosti(o, s);

    if (dynamic_cast<Konstanta *>(l) != nullptr) {
      Izraz *rez = new Konstanta(sin(l->vrednost(o)));
      delete l;
      return rez;
    } else
      return new Sin(l);
  }
  Izraz *izvod(const Okolina &o, const std::string &s) const;
};

class Cos : public Funkcija {
public:
  Cos(Izraz *i) : Funkcija(i) {}
  Cos(const Cos &s) : Funkcija(s) {}
  ~Cos() {}

  double vrednost(const Okolina &a) const { return cos(izraz->vrednost(a)); }
  void ispisi(std::ostream &s) const { s << "COS ( " << (*izraz) << ") "; }
  Izraz *kopija() const { return new Cos(*this); }
  Izraz *uprosti(const Okolina &o, const std::string &s) const {
    Izraz *l = izraz->uprosti(o, s);
    if (dynamic_cast<Konstanta *>(l) != nullptr) {
      Izraz *rez = new Konstanta(cos(l->vrednost(o)));
      delete l;
      return rez;
    } else
      return new Cos(l);
  }
  Izraz *izvod(const Okolina &o, const std::string &s) const {
    Izraz *l = izraz->izvod(o, s);
    return new Suprotni(new Proizvod(new Sin(izraz->kopija()), l));
  }
};

Izraz *Sin::izvod(const Okolina &o, const std::string &s) const {
  Izraz *l = izraz->izvod(o, s);
  return new Proizvod(new Cos(izraz->kopija()), l);
}

class Tan : public Funkcija {
public:
  Tan(Izraz *i) : Funkcija(i) {}
  Tan(const Tan &s) : Funkcija(s) {}
  ~Tan() {}

  double vrednost(const Okolina &a) const { return tan(izraz->vrednost(a)); }
  void ispisi(std::ostream &s) const { s << "TAN ( " << (*izraz) << ") "; }
  Izraz *kopija() const { return new Tan(*this); }
  Izraz *uprosti(const Okolina &o, const std::string &s) const {
    Izraz *l = izraz->uprosti(o, s);
    if (dynamic_cast<Konstanta *>(l) != nullptr) {
      Izraz *rez = new Konstanta(tan(l->vrednost(o)));
      delete l;
      return rez;
    } else
      return new Tan(l);
  }

  Izraz *izvod(const Okolina &o, const std::string &s) const {
    Izraz *l = izraz->izvod(o, s);
    return new Kolicnik(
        l, new Proizvod(new Cos(izraz->kopija()), new Cos(izraz->kopija())));
  }
};

class Cot : public Funkcija {
public:
  Cot(Izraz *i) : Funkcija(i) {}
  Cot(const Cot &s) : Funkcija(s) {}
  ~Cot() {}

  double vrednost(const Okolina &a) const {
    double x = izraz->vrednost(a);
    return cos(x) / sin(x);
  }
  void ispisi(std::ostream &s) const { s << "COT ( " << (*izraz) << ") "; }
  Izraz *kopija() const { return new Cot(*this); }
  Izraz *uprosti(const Okolina &o, const std::string &s) const {
    Izraz *l = izraz->uprosti(o, s);
    if (dynamic_cast<Konstanta *>(l) != nullptr) {
      double x = l->vrednost(o);
      Izraz *rez = new Konstanta(cos(x) / sin(x));
      delete l;
      return rez;
    } else
      return new Cot(l);
  }
  Izraz *izvod(const Okolina &o, const std::string &s) const {
    Izraz *l = izraz->izvod(o, s);
    return new Kolicnik(
        new Suprotni(l),
        new Proizvod(new Sin(izraz->kopija()), new Sin(izraz->kopija())));
  }
};

class Log : public Funkcija {
public:
  Log(Izraz *i) : Funkcija(i) {}
  Log(const Log &s) : Funkcija(s) {}
  ~Log() {}

  double vrednost(const Okolina &a) const { return log(izraz->vrednost(a)); }
  void ispisi(std::ostream &s) const { s << "LOG ( " << (*izraz) << ") "; }
  Izraz *kopija() const { return new Log(*this); }
  Izraz *uprosti(const Okolina &o, const std::string &s) const {
    Izraz *l = izraz->uprosti(o, s);
    if (dynamic_cast<Konstanta *>(l) != nullptr) {
      double x = l->vrednost(o);
      Izraz *rez = new Konstanta(log(x));
      delete l;
      return rez;
    } else
      return new Log(l);
  }
  Izraz *izvod(const Okolina &o, const std::string &s) const {
    Izraz *l = izraz->izvod(o, s);
    return new Proizvod(new Kolicnik(new Konstanta(1), izraz->kopija()), l);
  }
};

class Exp : public Funkcija {
public:
  Exp(Izraz *i) : Funkcija(i) {}
  Exp(const Exp &s) : Funkcija(s) {}
  ~Exp() {}

  double vrednost(const Okolina &a) const { return exp(izraz->vrednost(a)); }
  void ispisi(std::ostream &s) const { s << "EXP ( " << (*izraz) << ") "; }
  Izraz *kopija() const { return new Exp(*this); }
  Izraz *uprosti(const Okolina &o, const std::string &s) const {
    Izraz *l = izraz->uprosti(o, s);
    if (dynamic_cast<Konstanta *>(l) != nullptr) {
      double x = l->vrednost(o);
      Izraz *rez = new Konstanta(exp(x));
      delete l;
      return rez;
    } else
      return new Exp(l);
  }
  Izraz *izvod(const Okolina &o, const std::string &s) const {
    Izraz *l = izraz->izvod(o, s);
    return new Proizvod(new Exp(izraz->kopija()), l);
  }
};

class Sqrt : public Funkcija {
public:
  Sqrt(Izraz *i) : Funkcija(i) {}
  Sqrt(const Sqrt &s) : Funkcija(s) {}
  ~Sqrt() {}

  double vrednost(const Okolina &a) const { return sqrt(izraz->vrednost(a)); }
  void ispisi(std::ostream &s) const { s << "SQRT ( " << (*izraz) << ") "; }
  Izraz *kopija() const { return new Sqrt(*this); }
  Izraz *uprosti(const Okolina &o, const std::string &s) const {
    Izraz *l = izraz->uprosti(o, s);
    if (dynamic_cast<Konstanta *>(l) != nullptr) {
      double x = l->vrednost(o);
      Izraz *rez = new Konstanta(sqrt(x));
      delete l;
      return rez;
    } else
      return new Sqrt(l);
  }
  Izraz *izvod(const Okolina &o, const std::string &s) const {
    Izraz *l = izraz->izvod(o, s);
    return new Kolicnik(
        l, new Proizvod(new Konstanta(2), new Sqrt(izraz->kopija())));
  }
};

int main() {
  Okolina o;
  o.dodaj_promenljivu("x", 5);
  o.dodaj_promenljivu("y", 10);

  Izraz *i1 = new Kolicnik(new Promenljiva("x"), new Sin(new Konstanta(2)));
  Izraz *i2 = new Proizvod(new Exp(new Sqrt(new Konstanta(3.14))),
                           new Promenljiva("x"));
  Izraz *i3 = new Razlika(new Promenljiva("y"), i2->kopija());
  Izraz *i4 = new Zbir(i1->kopija(), i3->kopija());

  std::cout << (*i4) << "=" << (i4->vrednost(o)) << std::endl;

  Izraz *izvod = i4->izvod(o, "x");
  std::cout << (*izvod) << "=" << (izvod->vrednost(o)) << std::endl;

  Izraz *i5 = i4->uprosti(o, "x");
  std::cout << (*i5) << "=" << (i5->vrednost(o)) << std::endl;

  Izraz *i6 = i5->uprosti(o, "y");
  std::cout << (*i6) << "=" << (i6->vrednost(o)) << std::endl;

  delete i5;
  delete i4;
  delete i6;
  delete izvod;
  return 0;
}
