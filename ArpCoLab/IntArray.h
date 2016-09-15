#ifndef INT_ARRAY_H
#define INT_ARRAY_H

#include "Array.h"

template <size_t MAX_SIZE>
class IntArray : public Array<int, MAX_SIZE>
{
  public:
    IntArray();
    IntArray(int _startRange, int _endRange);
    void range(int _startRange, int _endRange);
  private:
};

// Dynamic templating
#include "IntArrayImplementation.h"

#endif
