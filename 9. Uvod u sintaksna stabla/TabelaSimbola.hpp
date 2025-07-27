#ifndef TABELA_SIMBOLA_H
#define TABELA_SIMBOLA_H

#include <iostream>
#include <map>
#include <string>

class TabelaSimbola {
private:
  std::map<std::string, double> m_tabela;

public:
  void definisni_promenljivu(const std::string &s, const double v);
  void dodeli_vrednost(const std::string &s, const double v);
  double vrednost_promenljive(const std::string &s) const;
};

#endif
