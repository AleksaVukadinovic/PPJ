#include "TabelaSimbola.hpp"

void TabelaSimbola::definisni_promenljivu(const std::string &s,
                                          const double v) {
  if (m_tabela.find(s) != m_tabela.end()) {
    std::cerr << "Promenljiva " << s << " je vec definisana" << std::endl;
    exit(EXIT_FAILURE);
  }
  m_tabela[s] = v;
}

void TabelaSimbola::dodeli_vrednost(const std::string &s, const double v) {
  if (m_tabela.find(s) == m_tabela.end()) {
    std::cerr << "Promenljiva " << s << " nije definisana" << std::endl;
    exit(EXIT_FAILURE);
  }
  m_tabela[s] = v;
}

double TabelaSimbola::vrednost_promenljive(const std::string &s) const {
  if (m_tabela.find(s) == m_tabela.end()) {
    std::cerr << "Promenljiva " << s << " nije definisana" << std::endl;
    exit(EXIT_FAILURE);
  }
  auto it = m_tabela.find(s);
  return it->second;
}