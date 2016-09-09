#include "TapTempo.h"

const int TapTempo::THIRTY_SECOND_NOTE = 32;
const int TapTempo::SIXTEENTH_NOTE = 16;
const int TapTempo::QUARTER_NOTE = 4;
const int TapTempo::HALF_NOTE = 2;
const int TapTempo::WHOLE_NOTE = 1;

const int TapTempo::ABANDON_FIRST_TAP_MS = 2500;

TapTempo::TapTempo() {
  prevPinValue = 0;
  firstTapMs = -1;
  lastBeatMs = 0;
}

void TapTempo::init(int _tapDurationMs, const int _tapSubDivision, const int _beatSubDivision) {
  tapDurationMs = _tapDurationMs;
  tapSubDivision = _tapSubDivision;
  beatSubDivision = _beatSubDivision;
  calculateDurations();
}

int TapTempo::getTapDurationMs() {
  return tapDurationMs;
}

void TapTempo::readPin(int _value, int _nowMs) {
 if(_value != prevPinValue && _value == 1) {
  tap(_nowMs);
 }
 prevPinValue = _value;
}

void TapTempo::tap(int _nowMs) {
  // Reset firstTapMs if it was abandoned
  if(firstTapMs != -1 && _nowMs - firstTapMs > TapTempo::ABANDON_FIRST_TAP_MS) {
    firstTapMs = -1;
  }

  if(firstTapMs == -1) {
    // First Tap
    firstTapMs = _nowMs;
  } else {
    // Second Tap
    tapDurationMs = _nowMs - firstTapMs;
    calculateDurations();
    firstTapMs = -1;
  }
}

bool TapTempo::isBeat(int _nowMs) {
 if(_nowMs - lastBeatMs >= beatDurationMs) {
  lastBeatMs = _nowMs;
  return true;
 }
 return false;
}

void TapTempo::calculateDurations() {
  // Divisor protection
  if(beatSubDivision == 0) {
    beatSubDivision = 1;
  }
  measureDurationMs = tapDurationMs * tapSubDivision;
  beatDurationMs = measureDurationMs / beatSubDivision;
}

void TapTempo::setTapSubDivision(const int _tapSubDivision) {
  tapSubDivision = _tapSubDivision;
  calculateDurations();
}

void TapTempo::setBeatSubDivision(const int _beatSubDivision) {
  beatSubDivision = _beatSubDivision;
  calculateDurations();
}

int TapTempo::getBpm() {
  // Divisor protection
  if(beatDurationMs == 0) {
    return 0;
  }
  return 60000 / beatDurationMs;
}

