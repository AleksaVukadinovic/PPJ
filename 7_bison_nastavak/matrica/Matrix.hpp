#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

class Matrix {
private:
    std::vector<std::vector<double>> _mat;
public:
    Matrix();
    Matrix(int m, int n, double val = 0);
    Matrix(Matrix* m);

    void dodajRed(std::vector<double>& red);
    void show(std::ostream& s) const;

    int Rows() const;
    int Columns() const;
    std::pair<int, int> Size() const;

    std::vector<double>& operator[](int i);
    const std::vector<double>& operator[](int i) const;

    Matrix* operator +(const Matrix& m) const;
    Matrix* operator -(const Matrix& m) const;
    Matrix* operator *(const Matrix& m) const;

    Matrix* operator -() const;

    Matrix* Transponuj() const;
    Matrix* Pomnozi(const Matrix& m) const;
    Matrix* Podeli(const Matrix& m) const;

    Matrix* SubMatrix(std::pair<int, int>& rows, std::pair<int, int>& cols);

    bool operator ==(const Matrix& m) const;
    bool operator !=(const Matrix& m) const;
};

std::ostream& operator <<(std::ostream& s, const Matrix& m);

#endif