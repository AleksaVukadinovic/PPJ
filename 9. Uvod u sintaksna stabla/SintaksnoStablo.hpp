#ifndef SINTAKSNO_STABLO_H
#define SINTAKSNO_STABLO_H

#include "TabelaSimbola.hpp"
#include <iostream>
#include <vector>

class ASTCvor {
public:
  virtual ~ASTCvor();

  virtual void ispisi(std::ostream &s) const = 0;
  virtual double interpretiraj(TabelaSimbola &ts) const = 0;
  virtual ASTCvor *kloniraj() const = 0;
};

std::ostream &operator<<(std::ostream &s, const ASTCvor &ast_cvor);

class NizNaredbi : public ASTCvor {
private:
  std::vector<ASTCvor *> m_naredbe;

public:
  NizNaredbi();
  NizNaredbi(const NizNaredbi &nn);
  ~NizNaredbi();

  void ispisi(std::ostream &s) const override;
  double interpretiraj(TabelaSimbola &ts) const override;
  virtual ASTCvor *kloniraj() const override;
};

class Definicija : public ASTCvor {
private:
  std::string m_id;
  ASTCvor *m_izraz;

public:
  Definicija(const std::string id, ASTCvor *izraz);
  Definicija(const Definicija &drugi);
  ~Definicija();

  void ispisi(std::ostream &s) const override;
  double interpretiraj(TabelaSimbola &ts) const override;
  virtual ASTCvor *kloniraj() const override;
};

class Dodela : public ASTCvor {
private:
  std::string m_id;
  ASTCvor *m_izraz;

public:
  Dodela(const std::string id, ASTCvor *izraz);
  Dodela(const Dodela &drugi);
  ~Dodela();

  void ispisi(std::ostream &s) const override;
  double interpretiraj(TabelaSimbola &ts) const override;
  virtual ASTCvor *kloniraj() const override;
};

class Promenljiva : public ASTCvor {
private:
  std::string m_id;

public:
  Promenljiva(const std::string &id);

  void ispisi(std::ostream &s) const override;
  double interpretiraj(TabelaSimbola &ts) const override;
  virtual ASTCvor *kloniraj() const override;
};

class Konstanta : public ASTCvor {
private:
  double m_vrednost;

public:
  Konstanta(double vrednost);
  void ispisi(std::ostream &s) const override;
  double interpretiraj(TabelaSimbola &ts) const override;
  virtual ASTCvor *kloniraj() const override;
};

class UnarniCvor : public ASTCvor {
protected:
  ASTCvor *m_cvor;

public:
  UnarniCvor(ASTCvor *cvor);
  UnarniCvor(const UnarniCvor &cvor);
  ~UnarniCvor();

  virtual void ispisi(std::ostream &s) const override;
  virtual double interpretiraj(TabelaSimbola &ts) const override;
  virtual ASTCvor *kloniraj() const override;
};

class Negacija : public UnarniCvor {
public:
  Negacija(ASTCvor *cvor);

  void ispisi(std::ostream &s) const override;
  double interpretiraj(TabelaSimbola &ts) const override;
  virtual ASTCvor *kloniraj() const override;
};

class Ispis : public UnarniCvor {
public:
  Ispis(ASTCvor *cvor);

  void ispisi(std::ostream &s) const override;
  double interpretiraj(TabelaSimbola &ts) const override;
  virtual ASTCvor *kloniraj() const override;
};

class BinarniCvor : public ASTCvor {
protected:
  ASTCvor *m_levi, *m_desni;

public:
  BinarniCvor(ASTCvor *levi, ASTCvor *desni);
  BinarniCvor(const BinarniCvor &cvor);
  ~BinarniCvor();

  virtual void ispisi(std::ostream &s) const override;
  virtual double interpretiraj(TabelaSimbola &ts) const override;
  virtual ASTCvor *kloniraj() const override;
};

class Sabiranje : public BinarniCvor {
public:
  Sabiranje(ASTCvor *levi, ASTCvor *desni);

  void ispisi(std::ostream &s) const override;
  double interpretiraj(TabelaSimbola &ts) const override;
  virtual ASTCvor *kloniraj() const override;
};

#endif
