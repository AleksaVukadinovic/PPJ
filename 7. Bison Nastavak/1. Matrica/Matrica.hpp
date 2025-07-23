#ifndef MATRIX_H
#define MATRIX_H

#include <iomanip>
#include <iostream>
#include <vector>

class Matrica {
private:
  std::vector<std::vector<double>> _mat;

public:
  Matrica();
  Matrica(int m, int n, double val = 0);
  Matrica(Matrica *m);

  void dodajRed(std::vector<double> &red);
  void show(std::ostream &s) const;

  int Rows() const;
  int Columns() const;
  std::pair<int, int> Size() const;

  std::vector<double> &operator[](int i);
  const std::vector<double> &operator[](int i) const;

  Matrica *operator+(const Matrica &m) const;
  Matrica *operator-(const Matrica &m) const;
  Matrica *operator*(const Matrica &m) const;
  Matrica *operator-() const;

  Matrica *Transponuj() const;
  Matrica *Pomnozi(const Matrica &m) const;
  Matrica *Podeli(const Matrica &m) const;
  Matrica *SubMatrix(std::pair<int, int> &rows, std::pair<int, int> &cols);

  bool operator==(const Matrica &m) const;
  bool operator!=(const Matrica &m) const;
};
std::ostream &operator<<(std::ostream &s, const Matrica &m);

#endif
