#include "SintaksnoStablo.hpp"

ASTCvor::~ASTCvor() {}
ASTCvor *NizNaredbi::kloniraj() const { return new NizNaredbi(*this); }

std::ostream &operator<<(std::ostream &s, const ASTCvor &ast_cvor) {
  ast_cvor.ispisi(s);
  return s;
}

// NIZ NAREDBI

NizNaredbi::NizNaredbi() {}
NizNaredbi::NizNaredbi(const NizNaredbi &nn) {
  m_naredbe.resize(nn.m_naredbe.size());
  for (int i = 0; i < nn.m_naredbe.size(); i++)
    m_naredbe[i] = nn.m_naredbe[i]->kloniraj();
}
NizNaredbi::~NizNaredbi() {
  for (ASTCvor *cvor : m_naredbe)
    delete cvor;
}

void NizNaredbi::ispisi(std::ostream &s) const {
  for (auto naredba : m_naredbe)
    s << naredba << ";\n";
}
double NizNaredbi::interpretiraj(TabelaSimbola &ts) const {
  for (auto cvor : m_naredbe)
    cvor->interpretiraj(ts);
  return 0;
}

// DEFINICIJA

Definicija::Definicija(const std::string id, ASTCvor *izraz)
    : m_id(id), m_izraz(izraz) {}
Definicija::Definicija(const Definicija &drugi) {
  m_id = drugi.m_id;
  m_izraz - drugi.m_izraz->kloniraj();
}
Definicija::~Definicija() { delete m_izraz; };

void Definicija::ispisi(std::ostream &s) const {
  s << "def " << m_id << " = " << m_izraz << ";\n";
}
double Definicija::interpretiraj(TabelaSimbola &ts) const {
  double vrednost = m_izraz->interpretiraj(ts);
  ts.definisni_promenljivu(m_id, vrednost);
  return 0;
}
ASTCvor *Definicija::kloniraj() const { return new Definicija(*this); }

// DODELA

Dodela::Dodela(const std::string id, ASTCvor *izraz)
    : m_id(id), m_izraz(izraz) {}
Dodela::Dodela(const Dodela &drugi) {
  m_id = drugi.m_id;
  m_izraz - drugi.m_izraz->kloniraj();
}
Dodela::~Dodela() { delete m_izraz; };

void Dodela::ispisi(std::ostream &s) const {
  s << "def " << m_id << " = " << m_izraz << ";\n";
}
double Dodela::interpretiraj(TabelaSimbola &ts) const {
  double vrednost = m_izraz->interpretiraj(ts);
  ts.dodeli_vrednost(m_id, vrednost);
  return 0;
}
ASTCvor *Dodela::kloniraj() const { return new Dodela(*this); }

// PROMENLJIVA

Promenljiva::Promenljiva(const std::string &id) : m_id(id) {}
void Promenljiva::ispisi(std::ostream &s) const { s << m_id; }
double Promenljiva::interpretiraj(TabelaSimbola &ts) const {
  return ts.vrednost_promenljive(m_id);
}
ASTCvor *Promenljiva::kloniraj() const { return new Promenljiva(*this); }

// KONSTANTA

Konstanta::Konstanta(double vrednost) : m_vrednost(vrednost) {}
void Konstanta::ispisi(std::ostream &s) const { s << m_vrednost; }
double Konstanta::interpretiraj(TabelaSimbola &ts) const { return m_vrednost; }
ASTCvor *Konstanta::kloniraj() const { return new Konstanta(*this); }

// UNARNI CVOR

UnarniCvor::UnarniCvor(ASTCvor *cvor) : m_cvor(cvor) {}
UnarniCvor::UnarniCvor(const UnarniCvor &cvor) {
  m_cvor = cvor.m_cvor->kloniraj();
}
UnarniCvor::~UnarniCvor() { delete m_cvor; }

// NEGACIJA

Negacija::Negacija(ASTCvor *cvor) : UnarniCvor(cvor) {}
void Negacija::ispisi(std::ostream &s) const { s << "- (" << *m_cvor << ")"; }
double Negacija::interpretiraj(TabelaSimbola &ts) const {
  return -m_cvor->interpretiraj(ts);
}
ASTCvor *Negacija::kloniraj() const { return new Negacija(*this); }

// ISPIS

Ispis::Ispis(ASTCvor *cvor) : UnarniCvor(cvor) {}
void Ispis::ispisi(std::ostream &s) const { s << "- (" << *m_cvor << ")"; }
double Ispis::interpretiraj(TabelaSimbola &ts) const {
  std::cout << m_cvor->interpretiraj(ts);
  return 0;
}
ASTCvor *Ispis::kloniraj() const { return new Ispis(*this); }

// BINARNI CVOR

BinarniCvor::BinarniCvor(ASTCvor *levi, ASTCvor *desni)
    : m_levi(levi), m_desni(desni) {}
BinarniCvor::BinarniCvor(const BinarniCvor &cvor) {
  m_levi = cvor.m_levi->kloniraj();
  m_desni = cvor.m_desni->kloniraj();
}
BinarniCvor::~BinarniCvor() {
  delete m_levi;
  delete m_desni;
}

// SABIRANJE

Sabiranje::Sabiranje(ASTCvor *levi, ASTCvor *desni)
    : BinarniCvor(levi, desni) {}

void Sabiranje::ispisi(std::ostream &s) const {
  s << "(" << m_levi << ") + (" << m_desni << ")";
}
double Sabiranje::interpretiraj(TabelaSimbola &ts) const {
  return m_levi->interpretiraj(ts) + m_desni->interpretiraj(ts);
};

// ODUZIMANJE

// MNOZENJE