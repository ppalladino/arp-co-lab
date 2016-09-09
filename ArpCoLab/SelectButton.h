#ifndef SELECT_BUTTON_H
#define SELECT_BUTTON_H

#include <Arduino.h>
#include "Array.h"

template <typename T, size_t MAX_SIZE>
class SelectButton {
  public:

  SelectButton();

  void init(Array<T, MAX_SIZE>_options, const T &_value);
  T&   getValue();
  void readPin(int _pinValue);
  
  private:

  Array<T, MAX_SIZE>  options;
  int      prevPinValue;
  int      value;
  
};

// Dynamic templating
#include "SelectButtonImplementation.h"

#endif
