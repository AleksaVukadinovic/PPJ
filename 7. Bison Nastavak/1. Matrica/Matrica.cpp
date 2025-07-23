#include "Matrica.hpp"

Matrica::Matrica() : _mat() {}
Matrica::Matrica(int m, int n, double val = 0)
    : _mat(m, std::vector<double>(n, val)) {}
Matrica::Matrica(Matrica *m) {
  if (this == m)
    return;
  _mat.resize(m->Rows());
  for (int i = 0; i < m->Rows(); i++) {
    _mat[i].resize(m->Columns());
    for (int j = 0; j < m->Columns(); j++)
      _mat[i][j] = (*m)[i][j];
  }
}

void Matrica::dodajRed(std::vector<double> &red) { _mat.push_back(red); }
void Matrica::show(std::ostream &s) const {
  for (int i = 0; i < _mat.size(); i++) {
    for (int j = 0; j < _mat[0].size(); j++)
      std::cout << std::setw(6) << _mat[i][j] << " ";
    std::cout << std::endl;
  }
}

int Matrica::Rows() const { return std::max((int)_mat.size(), 0); }
int Matrica::Columns() const { return std::max((int)_mat[0].size(), 0); }
std::pair<int, int> Matrica::Size() const {
  return std::make_pair(_mat.size(), _mat[0].size());
}

std::vector<double> &Matrica::operator[](int i) {
  if (i < 0 || i >= _mat.size())
    throw "Index out of bounds";

  return _mat[i];
}
const std::vector<double> &Matrica::operator[](int i) const {
  if (i < 0 || i >= _mat.size())
    throw "Index out of bounds";

  return _mat[i];
}

Matrica *Matrica::operator+(const Matrica &m) const {
  Matrica *rezultat = nullptr;

  if (this->Rows() == 1 && this->Columns() == 1) {
    rezultat = new Matrica(m.Rows(), m.Columns());
    for (int i = 0; i < m.Rows(); i++)
      for (int j = 0; j < m.Columns(); j++)
        rezultat->_mat[i][j] = m._mat[i][j] + _mat[0][0];
  }

  else if (m.Rows() == 1 && m.Columns() == 1) {
    rezultat = new Matrica(this->Rows(), this->Columns());
    for (int i = 0; i < this->Rows(); i++)
      for (int j = 0; j < this->Columns(); j++)
        rezultat->_mat[i][j] = _mat[i][j] + m._mat[0][0];
  }

  else {
    if (this->Size() != m.Size())
      return nullptr;
    std::pair<int, int> size = this->Size();
    rezultat = new Matrica(size.first, size.second);

    for (int i = 0; i < size.first; i++)
      for (int j = 0; j < size.second; j++)
        (*rezultat)[i][j] = _mat[i][j] + m._mat[i][j];
  }

  return rezultat;
}

Matrica *Matrica::operator-(const Matrica &m) const {
  Matrica *rezultat = nullptr;
  if (this->Rows() == 1 && this->Columns() == 1) {
    rezultat = new Matrica(m.Rows(), m.Columns());
    for (int i = 0; i < m.Rows(); i++)
      for (int j = 0; j < m.Columns(); j++)
        rezultat->_mat[i][j] = m._mat[i][j] - _mat[0][0];
  } else if (m.Rows() == 1 && m.Columns() == 1) {
    rezultat = new Matrica(this->Rows(), this->Columns());
    for (int i = 0; i < this->Rows(); i++)
      for (int j = 0; j < this->Columns(); j++)
        rezultat->_mat[i][j] = _mat[i][j] - m._mat[0][0];
  } else {
    if (this->Size() != m.Size())
      return nullptr;
    std::pair<int, int> size = this->Size();
    rezultat = new Matrica(size.first, size.second);
    for (int i = 0; i < size.first; i++)
      for (int j = 0; j < size.second; j++)
        (*rezultat)[i][j] = _mat[i][j] + m._mat[i][j];
  }

  return rezultat;
}

Matrica *Matrica::operator*(const Matrica &m) const {

  Matrica *rezultat = nullptr;

  if (this->Rows() == 1 && this->Columns() == 1) {
    rezultat = new Matrica(m.Rows(), m.Columns());

    for (int i = 0; i < m.Rows(); i++) {
      for (int j = 0; j < m.Columns(); j++) {
        rezultat->_mat[i][j] = m._mat[i][j] * _mat[0][0];
      }
    }
  } else if (m.Rows() == 1 && m.Columns() == 1) {

    rezultat = new Matrica(this->Rows(), this->Columns());

    for (int i = 0; i < this->Rows(); i++) {
      for (int j = 0; j < this->Columns(); j++) {
        rezultat->_mat[i][j] = _mat[i][j] * m._mat[0][0];
      }
    }
  } else {
    if (this->Columns() != this->Rows())
      return nullptr;

    rezultat = new Matrica(this->Rows(), m.Columns());

    for (int i = 0; i < this->Rows(); i++) {
      for (int j = 0; j < m.Columns(); j++) {
        rezultat->_mat[i][j] = 0;
        for (int k = 0; k < this->Columns(); k++) {
          rezultat->_mat[i][j] += _mat[i][k] * m._mat[k][j];
        }
      }
    }
  }

  return rezultat;
}

Matrica *Matrica::operator-() const {
  Matrica *rezultat = new Matrica(this->Rows(), this->Columns());
  for (int i = 0; i < this->Rows(); i++)
    for (int j = 0; j < this->Columns(); j++)
      rezultat->_mat[i][j] = -_mat[i][j];
  return rezultat;
}

Matrica *Matrica::Transponuj() const {
  Matrica *rezultat = new Matrica(this->Columns(), this->Rows());
  for (int i = 0; i < _mat.size(); i++)
    for (int j = 0; j < _mat[0].size(); j++)
      rezultat->_mat[j][i] = _mat[i][j];
  return rezultat;
}

Matrica *Matrica::Pomnozi(const Matrica &m) const {
  Matrica *rezultat = nullptr;
  if (this->Rows() == 1 && this->Columns() == 1) {
    rezultat = new Matrica(m.Rows(), m.Columns());
    for (int i = 0; i < m.Rows(); i++)
      for (int j = 0; j < m.Columns(); j++)
        rezultat->_mat[i][j] = m._mat[i][j] * _mat[0][0];
  } else if (m.Rows() == 1 && m.Columns() == 1) {
    rezultat = new Matrica(this->Rows(), this->Columns());
    for (int i = 0; i < this->Rows(); i++)
      for (int j = 0; j < this->Columns(); j++)
        rezultat->_mat[i][j] = _mat[i][j] * m._mat[0][0];
  } else {
    if (this->Size() != m.Size())
      return nullptr;
    std::pair<int, int> size = this->Size();
    rezultat = new Matrica(size.first, size.second);
    for (int i = 0; i < size.first; i++)
      for (int j = 0; j < size.second; j++)
        (*rezultat)[i][j] = _mat[i][j] * m._mat[i][j];
  }

  return rezultat;
}

Matrica *Matrica::Podeli(const Matrica &m) const {

  Matrica *rezultat = nullptr;

  if (this->Rows() == 1 && this->Columns() == 1) {
    rezultat = new Matrica(m.Rows(), m.Columns());

    for (int i = 0; i < m.Rows(); i++) {
      for (int j = 0; j < m.Columns(); j++) {
        rezultat->_mat[i][j] = m._mat[i][j] * _mat[0][0];
      }
    }
  } else if (m.Rows() == 1 && m.Columns() == 1) {

    rezultat = new Matrica(this->Rows(), this->Columns());

    for (int i = 0; i < this->Rows(); i++) {
      for (int j = 0; j < this->Columns(); j++) {
        rezultat->_mat[i][j] = _mat[i][j] * m._mat[0][0];
      }
    }
  } else {
    if (this->Size() != m.Size())
      return nullptr;

    std::pair<int, int> size = this->Size();
    rezultat = new Matrica(size.first, size.second);

    for (int i = 0; i < size.first; i++) {
      for (int j = 0; j < size.second; j++) {
        (*rezultat)[i][j] = _mat[i][j] / m._mat[i][j];
      }
    }
  }

  return rezultat;
}

Matrica *Matrica::SubMatrix(std::pair<int, int> &rows,
                            std::pair<int, int> &cols) {
  int rowFrom = (rows.first == -1 ? 0 : rows.first);
  int rowTo = (rows.second == -1 ? (this->Rows() - 1) : rows.second);
  int colFrom = (cols.first == -1 ? 0 : cols.first);
  int colTo = (cols.second == -1 ? (this->Columns() - 1) : cols.second);
  if ((rowTo < rowFrom) || (rowFrom < 0 || rowFrom >= Rows()) ||
      (rowTo < 0 || rowTo >= Rows()) || (colTo < colFrom) ||
      (colFrom < 0 || colFrom >= Columns()) ||
      (colFrom < 0 || colFrom >= Columns())) {
    return nullptr;
  }
  int rows1 = rowTo - rowFrom + 1;
  int cols1 = colTo - colFrom + 1;
  Matrica *rezultat = new Matrica(rows1, cols1);
  for (int i = rowFrom; i <= rowTo; i++)
    for (int j = colFrom; j <= colTo; j++)
      rezultat->_mat[i - rowFrom][j - colFrom] = _mat[i][j];
  return rezultat;
}

bool Matrica::operator==(const Matrica &m) const {
  if (this->Size() != m.Size())
    return false;
  for (int i = 0; i < Rows(); i++)
    for (int j = 0; j < Columns(); j++)
      if (_mat[i][j] != m[i][j])
        return false;
  return true;
}

bool Matrica::operator!=(const Matrica &m) const { return !(*this == m); }

std::ostream &operator<<(std::ostream &s, const Matrica &m) {

  m.show(s);
  return s;
}