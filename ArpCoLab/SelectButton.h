#ifndef SELECT_BUTTON_H
#define SELECT_BUTTON_H

#include <Arduino.h>
#include "Array.h"

#define SELECT_BUTTON_MAX_SIZE 16

class SelectButton {
  public:

    SelectButton();
    void init(const int _numOptions,  const int _options[]);
    void init(const int _numOptions,  const int _options[], const int _selectedIdx);
    int  getSelectedOption();
    void readPin(int _pinValue);
  
  private:

    Array<int, SELECT_BUTTON_MAX_SIZE>  options;
    int      prevPinValue;
    int      selectedIdx;
};

#endif
