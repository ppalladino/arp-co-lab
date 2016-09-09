#ifndef SELECT_BUTTON_IMPLEMENTATION_H
#define SELECT_BUTTON_IMPLEMENTATION_H

template <typename T, size_t MAX_SIZE>
SelectButton<T, MAX_SIZE>::SelectButton() {
  
}

template <typename T, size_t MAX_SIZE>
void SelectButton<T, MAX_SIZE>::init(Array<T, MAX_SIZE> _options, const T &_value) {
  prevPinValue = 0;
  options = _options;
  value = _value;
}

template <typename T, size_t MAX_SIZE>
T& SelectButton<T, MAX_SIZE>::getValue() {
  return value;
}

template <typename T, size_t MAX_SIZE>
void SelectButton<T, MAX_SIZE>::readPin(int _pinValue) {
  bool pinValueChanged = _pinValue != prevPinValue;
  if(pinValueChanged && _pinValue == 1) {
    int nextIdx = options.getNextIdx(value);  
    value = options.at(nextIdx);   
  }
  prevPinValue = _pinValue;
}

#endif
