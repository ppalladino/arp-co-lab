#include "SelectButton.h"

//#define DEBUG_SELECT_BUTTON;
//
//#ifdef DEBUG_SELECT_BUTTON
//  #include <Streaming.h>
//#endif

SelectButton::SelectButton() {}
   
void SelectButton::init(int _startRange,  int _endRange) {
  init(_startRange, _endRange, 0);
}

void SelectButton::init(int _startRange,  int _endRange, const int _selectedIdx) {
  options.range(_startRange, _endRange);
  prevPinValue = 0;
  selectedIdx = _selectedIdx;
}

int SelectButton::getSelectedOption() {
  return options.at(selectedIdx, 0);
}

void SelectButton::readPin(int _pinValue) {
  bool pinValueChanged = _pinValue != prevPinValue;
  if(pinValueChanged && _pinValue == 1) {
    selectedIdx = options.getNextIdx(selectedIdx);    
    
    #ifdef DEBUG_SELECT_BUTTON
      Serial << "SelectButton: selectedIdx:" << selectedIdx << endl;
    #endif
  }
  prevPinValue = _pinValue;
}
