#include "SelectButton.h"

//#define DEBUG_SELECT_BUTTON;
//
//#ifdef DEBUG_SELECT_BUTTON
//  #include <Streaming.h>
//#endif
  
SelectButton::SelectButton() {}

void SelectButton::init(const int _numOptions,  const int _options[]) {
  init(_numOptions, _options, 0);
}

void SelectButton::init(const int _numOptions,  const int _options[], const int _selectedIdx) {
  int numOptions = _numOptions > SELECT_BUTTON_MAX_SIZE ? SELECT_BUTTON_MAX_SIZE : _numOptions;
  options.assign(numOptions, _options);
  prevPinValue = 0;
  selectedIdx = _selectedIdx;
}


int SelectButton::getSelectedOption() {
  return options.at(selectedIdx, 0);;
}

void SelectButton::readPin(int _pinValue) {

  bool pinValueChanged = _pinValue != prevPinValue;
  if(pinValueChanged && _pinValue == 1) {
    selectedIdx = options.getNextIdx(selectedIdx);    
    
//    #ifdef DEBUG_SELECT_BUTTON
//      Serial << "SelectButton: selectedIdx:" << selectedIdx << endl;
//    #endif
  }
  prevPinValue = _pinValue;
}


