#ifndef ARRAY_IMPLEMENTATION_H
#define ARRAY_IMPLEMENTATION_H

#include <Streaming.h>

template <typename T, size_t MAX_SIZE>
Array<T, MAX_SIZE>::Array()
{
  clear();
}

template <typename T, size_t MAX_SIZE>
Array<T, MAX_SIZE>::Array(const T &_value)
{
  clear();
  fill(_value);
}

template <typename T, size_t MAX_SIZE>
Array<T, MAX_SIZE>::Array(const T (&_values)[MAX_SIZE])
{
  clear();
  fill(_values);
}

template <typename T, size_t MAX_SIZE>
T& Array<T, MAX_SIZE>::operator[](const size_t _i)
{
  return values[_i];
}

template <typename T, size_t MAX_SIZE>
void Array<T, MAX_SIZE>::assign(const size_t _n, const T &_value)
{
  size_t assignSize = _n;
  if ((_n > size) && (_n <= MAX_SIZE))
  {
    size = _n;
  }
  else if (_n > MAX_SIZE)
  {
    size = MAX_SIZE;
    assignSize = MAX_SIZE;
  }
  for (size_t i = 0; i < assignSize; i++)
  {
    values[i] = _value;
  }
}

template <typename T, size_t MAX_SIZE>
void Array<T, MAX_SIZE>::assign(const size_t _n, const T _values[])
{
  size_t assignSize = _n;
  //if ((_n > size) && (_n <= MAX_SIZE))
  if (_n <= MAX_SIZE)
  {
    size = _n;
  }
  else if (_n > MAX_SIZE)
  {
    size = MAX_SIZE;
    assignSize = MAX_SIZE;
  }
  memcpy((void*) values, (void*) _values, assignSize*sizeof(T));
}

template <typename T, size_t MAX_SIZE>
T& Array<T, MAX_SIZE>::at(const size_t _i)
{
  return values[_i];
}

template <typename T, size_t MAX_SIZE>
void Array<T, MAX_SIZE>::clear()
{
  size = 0;
}

template <typename T, size_t MAX_SIZE>
void Array<T, MAX_SIZE>::fill(const T &_value)
{
  assign(MAX_SIZE, _value);
}

template <typename T, size_t MAX_SIZE>
void Array<T, MAX_SIZE>::fill(const T (&_values)[MAX_SIZE])
{
  assign(MAX_SIZE, _values);
}

template <typename T, size_t MAX_SIZE>
int Array<T, MAX_SIZE>::getIdx(const T &_value)
{  
  int idx = -1;
  for(int i = 0; i < getSize(); i++) {
    if(at(i) == _value) {
      idx = i;
      break;
    }
  }
  return idx;
}

template <typename T, size_t MAX_SIZE>
int Array<T, MAX_SIZE>::getNextIdx(int _idx)
{  
  if(_idx < 0) {
    return 0;
  }
  int nextIdx = _idx += 1;  
  if(nextIdx > getSize() - 1) {
    return 0;
  }
  return nextIdx;
}

template <typename T, size_t MAX_SIZE>
int Array<T, MAX_SIZE>::getPrevIdx(int _idx)
{  
  if(_idx > getSize() - 1) {
    return getSize() - 1;
  }
  int prevIdx = _idx -= 1;  
  if(prevIdx < 0) {
    return getSize() - 1;
  }
  return prevIdx;
}

template <typename T, size_t MAX_SIZE>
int Array<T, MAX_SIZE>::getRandomIdx()
{
  return rand() % getSize();
}

template <typename T, size_t MAX_SIZE>
int Array<T, MAX_SIZE>::getSize()
{
  return size;
}

template <typename T, size_t MAX_SIZE>
bool Array<T, MAX_SIZE>::hasIdx(int _idx)
{
  return (_idx >= 0 && _idx < getSize());
}

template <typename T, size_t MAX_SIZE>
void Array<T, MAX_SIZE>::push(const T &_value)
{
  if (size < MAX_SIZE)
  {
    values[size++] = _value;
  }
}

#endif
