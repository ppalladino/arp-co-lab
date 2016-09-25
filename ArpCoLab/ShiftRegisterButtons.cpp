#include "ShiftRegisterButtons.h"

ShiftRegisterButtons::ShiftRegisterButtons() {}

void ShiftRegisterButtons::init(int _numRegisters,  int _buttonBusPin,  int _latchPin) {
  numRegisters = _numRegisters;
  buttonBusPin = _buttonBusPin;
  latchPin = _latchPin;
  prevButtonBusPinValue = LOW;
  resetButtons();
}

int ShiftRegisterButtons::readButtonBusPin() {
  int buttonBusPinValue = digitalRead(buttonBusPin);
  bool pinValueChanged = buttonBusPinValue != prevButtonBusPinValue;
  byte checkBit = 1;
  int regIdx, bitIdx;
  int pressedButtonIdx = -1;

  if(pinValueChanged && buttonBusPinValue == HIGH) {
    for(regIdx = 0; regIdx < numRegisters; regIdx++) {
      if(pressedButtonIdx > 0) {
        break;
      }
      checkBit = 1;
      for(bitIdx = 0; bitIdx < 8; bitIdx++) {
        latchByte(regIdx, checkBit);
        if(digitalRead(buttonBusPin) == HIGH) {
          pressedButtonIdx = bitIdx + (regIdx * 8);
          break;
        }
        checkBit = checkBit << 1; // Next bit
      }
    }
    resetButtons(); // Ready buttons for next press
  }

  prevButtonBusPinValue = buttonBusPinValue;
  return pressedButtonIdx;
}

void ShiftRegisterButtons::latchByte(int regIdx, byte value) {
  for(int r = 0; r < numRegisters; r++) {
    if(r == numRegisters - 1 - regIdx) {
      SPI.transfer(value);
    } else {
      SPI.transfer(0);
    }
  }
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin, LOW);
}

void ShiftRegisterButtons::resetButtons() {
  for(int r = 0; r < numRegisters; r++) {
    SPI.transfer(255); // All
  }
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin, LOW);
}
