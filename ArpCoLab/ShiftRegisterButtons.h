/*
 * Helper with using a 74HC595 shift register as an serial input
 * See: https://www.youtube.com/watch?v=nXl4fb_LbcI&spfreload=1
 *      http://srv1.jpg.co.il/2/52aed8358f8e2.png
 */

#ifndef SHIFT_REGISTER_BUTTONS_H
#define SHIFT_REGISTER_BUTTONS_H

#include <SPI.h>

class ShiftRegisterButtons {
  public:
    ShiftRegisterButtons();
    void init(int _numRegisters, int _buttonBusPin, int _latchPin);
    int  readButtonBusPin();

  private:
    int prevButtonBusPinValue;
    int numRegisters; // Number of chained 74HC595
    int buttonBusPin;
    int latchPin;     // RCLK

    void resetButtons();
    void latchByte(int regIdx, byte checkRegister);
};

#endif
