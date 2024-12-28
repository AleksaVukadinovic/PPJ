#include "Matrix.hpp"

Matrix::Matrix(){}

Matrix::Matrix(int m, int n, double val){
    _mat.resize(m, std::vector<double> (n, val));
}


Matrix::Matrix(Matrix* m){
    _mat.resize(m->Rows());
    for (int i = 0; i < m->Rows(); i++) {
        _mat[i].resize(m->Columns());
        for (int j = 0; j < m->Columns(); j++) 
            _mat[i][j] = (*m)[i][j];
    }
}

void Matrix::dodajRed(std::vector<double>& red){
    _mat.push_back(red);
}

void Matrix::show(std::ostream& s) const {
    for(int i=0; i<_mat.size(); i++){
        for(int j=0; j<_mat[i].size(); j++)
            s << _mat[i][j] << " ";
        s << '\n';
    }
}

int Matrix::Rows() const {
    return _mat.size();
}

int Matrix::Columns() const {
    return _mat.size()>0?_mat[0].size():0;
}

std::pair<int, int> Matrix::Size() const {
    return std::make_pair(this->Rows(), this->Columns());
}

std::vector<double>& Matrix::operator[](int i) {
    if (i < 0 || i >= _mat.size())
        throw "Index out of bounds";
    return _mat[i];
}

const std::vector<double>& Matrix::operator[](int i) const {
    if (i < 0 || i >= _mat.size())
        throw "Index out of bounds";
    return _mat[i];
}

Matrix* Matrix::operator+(const Matrix& m) const {
    Matrix* rezultat = nullptr;

    if (this->Rows() == 1 && this->Columns() == 1) {
        rezultat = new Matrix(m.Rows(), m.Columns());
        for (int i = 0; i < m.Rows(); i++) 
            for (int j = 0; j < m.Columns(); j++) 
                rezultat->_mat[i][j] = m._mat[i][j] + _mat[0][0];
    }
    else if (m.Rows() == 1 && m.Columns() == 1) {
        rezultat = new Matrix(this->Rows(), this->Columns());
        for (int i = 0; i < this->Rows(); i++) 
            for (int j = 0; j < this->Columns(); j++) 
                rezultat->_mat[i][j] = _mat[i][j] + m._mat[0][0];
    } else {
        if (this->Size() != m.Size())
            return nullptr;

        std::pair<int, int> size = this->Size();
        rezultat = new Matrix(size.first, size.second);

        for (int i = 0; i < size.first; i++) 
            for (int j = 0; j < size.second; j++) 
                (*rezultat)[i][j] = _mat[i][j] + m._mat[i][j];
    }
    return rezultat;
}

Matrix* Matrix::operator-(const Matrix& m) const {
    Matrix* rezultat = nullptr;

    if (this->Rows() == 1 && this->Columns() == 1) {
        rezultat = new Matrix(m.Rows(), m.Columns());
        for (int i = 0; i < m.Rows(); i++) 
            for (int j = 0; j < m.Columns(); j++) 
                rezultat->_mat[i][j] = m._mat[i][j] - _mat[0][0];
    }
    else if (m.Rows() == 1 && m.Columns() == 1) {
        rezultat = new Matrix(this->Rows(), this->Columns());
        for (int i = 0; i < this->Rows(); i++) 
            for (int j = 0; j < this->Columns(); j++) 
                rezultat->_mat[i][j] = _mat[i][j] - m._mat[0][0];
    } else {
        if (this->Size() != m.Size())
            return nullptr;

        std::pair<int, int> size = this->Size();
        rezultat = new Matrix(size.first, size.second);

        for (int i = 0; i < size.first; i++) 
            for (int j = 0; j < size.second; j++) 
                (*rezultat)[i][j] = _mat[i][j] - m._mat[i][j];
    }
    return rezultat;
}

Matrix* Matrix::operator *(const Matrix& m) const {
    Matrix* rezultat = nullptr;

    if (this->Rows() == 1 && this->Columns() == 1) {
        rezultat = new Matrix(m.Rows(), m.Columns());
        for (int i = 0; i < m.Rows(); i++) 
            for (int j = 0; j < m.Columns(); j++) 
                rezultat->_mat[i][j] = m._mat[i][j] * _mat[0][0];
    }
    else if (m.Rows() == 1 && m.Columns() == 1) {
        rezultat = new Matrix(this->Rows(), this->Columns());
        for (int i = 0; i < this->Rows(); i++) 
            for (int j = 0; j < this->Columns(); j++) 
                rezultat->_mat[i][j] = _mat[i][j] * m._mat[0][0];
    } else {
        if (this->Columns() != this->Rows())
            return nullptr;

        rezultat = new Matrix(this->Rows(), m.Columns());
        
        for (int i = 0; i < this->Rows(); i++) {
            for (int j = 0; j < m.Columns(); j++) {
                rezultat->_mat[i][j] = 0;
                for (int k = 0; k < this->Columns(); k++) 
                    rezultat->_mat[i][j] += _mat[i][k] * m._mat[k][j];
            }
        }
    }

    return rezultat;
}

Matrix* Matrix::operator -() const {
    Matrix* rezultat = new Matrix(this->Rows(), this->Columns());
    for (int i = 0; i < this->Rows(); i++) 
        for (int j = 0; j < this->Columns(); j++) 
            rezultat->_mat[i][j] = -_mat[i][j];
    return rezultat;
}

Matrix* Matrix::Transponuj() const {
    Matrix* rezultat = new Matrix(this->Columns(), this->Rows());
    for (int i = 0; i < _mat.size(); i++) 
        for (int j = 0; j < _mat[0].size(); j++) 
            rezultat->_mat[j][i] = _mat[i][j];
    return rezultat;
}


bool Matrix::operator ==(const Matrix& m) const {
    if (this->Size() != m.Size())
        return false;

    for (int i = 0; i < Rows(); i++) 
        for (int j = 0; j < Columns(); j++) 
            if (_mat[i][j] != m[i][j])
                return false;

    return true;
}

Matrix* Matrix::Pomnozi(const Matrix& m) const {
    Matrix* rezultat = nullptr;

    if (this->Rows() == 1 && this->Columns() == 1) {
        rezultat = new Matrix(m.Rows(), m.Columns());
        for (int i = 0; i < m.Rows(); i++) 
            for (int j = 0; j < m.Columns(); j++) 
                rezultat->_mat[i][j] = m._mat[i][j] * _mat[0][0];
    }
    else if (m.Rows() == 1 && m.Columns() == 1) {
        rezultat = new Matrix(this->Rows(), this->Columns());
        for (int i = 0; i < this->Rows(); i++) 
            for (int j = 0; j < this->Columns(); j++) 
                rezultat->_mat[i][j] = _mat[i][j] * m._mat[0][0];
    } else {
        if (this->Size() != m.Size())
            return nullptr;
        
        std::pair<int, int> size = this->Size();
        rezultat = new Matrix(size.first, size.second);

        for (int i = 0; i < size.first; i++) 
            for (int j = 0; j < size.second; j++) 
                (*rezultat)[i][j] = _mat[i][j] * m._mat[i][j];
    }

    return rezultat;
}

Matrix* Matrix::Podeli(const Matrix& m) const {
    Matrix* rezultat = nullptr;

    if (this->Rows() == 1 && this->Columns() == 1) {
        rezultat = new Matrix(m.Rows(), m.Columns());
        for (int i = 0; i < m.Rows(); i++) 
            for (int j = 0; j < m.Columns(); j++) 
                rezultat->_mat[i][j] = m._mat[i][j] * _mat[0][0];
    }
    else if (m.Rows() == 1 && m.Columns() == 1) {    
        rezultat = new Matrix(this->Rows(), this->Columns());
        for (int i = 0; i < this->Rows(); i++) 
            for (int j = 0; j < this->Columns(); j++) 
                rezultat->_mat[i][j] = _mat[i][j] * m._mat[0][0];
    } else {
        if (this->Size() != m.Size())
            return nullptr;
        
        std::pair<int, int> size = this->Size();
        rezultat = new Matrix(size.first, size.second);

        for (int i = 0; i < size.first; i++) 
            for (int j = 0; j < size.second; j++) 
                (*rezultat)[i][j] = _mat[i][j] / m._mat[i][j];
    }

    return rezultat;
}

Matrix* Matrix::SubMatrix(std::pair<int, int>& rows, std::pair<int, int>& cols) {
    int rowFrom = (rows.first == -1 ? 0 : rows.first);
    int rowTo = (rows.second == -1 ? (this->Rows() - 1) : rows.second);

    int colFrom = (cols.first == -1 ? 0 : cols.first);
    int colTo = (cols.second == -1 ? (this->Columns() - 1) : cols.second);

    if ((rowTo < rowFrom) || (rowFrom < 0 || rowFrom >= Rows()) || (rowTo < 0 || rowTo >= Rows())
        || (colTo < colFrom) || (colFrom < 0 || colFrom >= Columns()) || (colFrom < 0 || colFrom >= Columns())) 
            return nullptr;
    
    int rows1 = rowTo - rowFrom + 1;
    int cols1 = colTo - colFrom + 1;

    Matrix* rezultat = new Matrix(rows1, cols1);

    for (int i = rowFrom; i <= rowTo; i++) 
        for (int j = colFrom; j <= colTo; j++) 
            rezultat->_mat[i - rowFrom][j- colFrom] = _mat[i][j];

    return rezultat;
}

bool Matrix::operator !=(const Matrix& m) const {    
    return !(*this == m);
}

std::ostream& operator <<(std::ostream& s, const Matrix& m) {
    m.show(s);
    return s;
}