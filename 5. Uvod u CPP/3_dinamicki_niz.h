#ifndef DINAMICKI_NIZ_H
#define DINAMICKI_NIZ_H

#include <exception>
#include <iostream>

#define DEFAULT_SIZE (32)
#define DEFAULT_STEP (2)

class DynamicArray {
private:
  double *_arr;
  int _capacity;
  int _size;

public:
  DynamicArray();
  DynamicArray(int n, double val = 0);
  DynamicArray(const DynamicArray &arr);
  ~DynamicArray();

  DynamicArray &operator=(const DynamicArray &arr);
  double &operator[](int i);
  const double &operator[](int i) const;

  int size() const;
  void push(double x);
  void pop();
  int find(double x) const;

  void show(std::ostream &s) const;
};

std::ostream &operator<<(std::ostream &s, const DynamicArray &arr);

#endif
