#include "3_dinamicki_niz.h"

DynamicArray::DynamicArray() {
  _size = 0;
  _capacity = DEFAULT_SIZE;
  _arr = new double[_capacity];
}

DynamicArray::DynamicArray(int n, double val) {
  _size = n;
  _capacity = n;
  _arr = new double[_capacity];

  for (int i = 0; i < _size; i++)
    _arr[i] = val;
}

DynamicArray::DynamicArray(const DynamicArray &arr) {
  _size = arr._size;
  _capacity = arr._capacity;
  _arr = new double[_capacity];

  for (int i = 0; i < _size; i++)
    _arr[i] = arr._arr[i];
}

DynamicArray::~DynamicArray() { delete[] _arr; }

DynamicArray &DynamicArray::operator=(const DynamicArray &arr) {
  if (this == &arr)
    return *this;

  if (_arr != nullptr)
    delete[] _arr;

  _size = arr._size;
  _capacity = arr._capacity;
  _arr = new double[_capacity];

  for (int i = 0; i < _size; i++)
    _arr[i] = arr._arr[i];
  return *this;
}

double &DynamicArray::operator[](int i) {
  if (i < 0 || i > _size)
    throw "Index out of bounds!";
  return _arr[i];
}

const double &DynamicArray::operator[](int i) const {
  if (i < 0 || i > _size)
    throw "Index out of bounds!";
  return _arr[i];
}

int DynamicArray::size() const { return _size; }
void DynamicArray::push(double x) {
  if (_size == _capacity) {
    _capacity *= DEFAULT_STEP;
    double *newArr = new double[_capacity];
    for (int i = 0; i < _size; i++)
      newArr[i] = _arr[i];
    delete[] _arr;
    _arr = newArr;
  }
  _arr[_size++] = x;
}
void DynamicArray::pop() {
  if (_size == 0)
    return;
  --_size;
}
int DynamicArray::find(double x) const {
  for (int i = 0; i < _size; i++)
    if (_arr[i] == x)
      return i;
  return -1;
}

void DynamicArray::show(std::ostream &s) const {

  for (int i = 0; i < _size; i++) {
    s << _arr[i] << " ";
  }
}

std::ostream &operator<<(std::ostream &s, const DynamicArray &arr) {
  arr.show(s);
  return s;
}