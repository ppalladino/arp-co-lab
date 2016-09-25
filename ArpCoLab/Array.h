#ifndef ARRAY_H
#define ARRAY_H

#include <Arduino.h>

template <typename T, size_t MAX_SIZE>
class Array
{
  public:
    Array();
    Array(const T &_value);
    Array(const T (&_values)[MAX_SIZE]);
    T&   operator[](const size_t _i);
    void assign(const size_t _n, const T &_value);
    void assign(const size_t _n, const T _values[]);
    T&   at(const size_t i, T _default);               
    T&   _at(const size_t i);
    void clear();
    void fill(const T &_value);
    void fill(const T (&_values)[MAX_SIZE]);
    int  getIdx(const T &_value);
    int  getLastIdx();
    int  getNextIdx(int _idx);
    int  getPrevIdx(int _idx);
    int  getRandomIdx();
    int  getSize();
    bool hasIdx(int _idx);
    void push(const T &_value);
    void set(int _idx, const T &_value);
    void setSize();
  private:
    T values[MAX_SIZE];
    size_t size;
};

// Dynamic templating
#include "ArrayImplementation.h"

#endif
