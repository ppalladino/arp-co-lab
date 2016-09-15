#ifndef SELECT_BUTTON_H
#define SELECT_BUTTON_H

#include <Arduino.h>
#include "IntArray.h"

#define SELECT_BUTTON_MAX_SIZE 16

class SelectButton {
  public:

    SelectButton();
    void init(int _startRange,  int _endRange);
    void init(int _startRange,  int _endRange, const int _selectedIdx);
    int  getSelectedOption();
    void readPin(int _pinValue);
  
  private:

    IntArray<SELECT_BUTTON_MAX_SIZE> options;
    int      prevPinValue;
    int      selectedIdx;
};

#endif
