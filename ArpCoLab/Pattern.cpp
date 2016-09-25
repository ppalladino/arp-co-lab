#include "Pattern.h"


#define DEBUG_PATTERN;
#ifdef DEBUG_PATTERN
  #include <Streaming.h>
#endif

const int Pattern::DIRECTION_UP = 0;
const int Pattern::DIRECTION_DOWN = 1;
const int Pattern::DIRECTION_RANDOM = 2;

const int Pattern::DIRECTIONS_UP[] = {Pattern::DIRECTION_UP};
const int Pattern::DIRECTIONS_DOWN[] = {DIRECTION_DOWN};
const int Pattern::DIRECTIONS_UP_DOWN[] = {Pattern::DIRECTION_UP, Pattern::DIRECTION_DOWN};
const int Pattern::DIRECTIONS_DOWN_UP[] = {Pattern::DIRECTION_DOWN, Pattern::DIRECTION_UP};

const int Pattern::PEDAL_OFFSETS[]    = {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 };
const int Pattern::INC_OFFSETS[]      = {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15 };
const int Pattern::ALT_BIN_OFFSETS[]  = {  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1 };

const int Pattern::BIN_PATTERN_1[]      = {  1,  1,  1,  0,  1,  1,  1,  0,  1,  1,  1,  0,  1,  1,  1,  0 };
const int Pattern::BIN_PATTERN_2[]      = {  1,  0,  1,  0,  1,  1,  1,  1,  1,  0,  1,  0,  1,  1,  1,  1 };

Pattern::Pattern() {}

void Pattern::init(const int _numOffsets,  const int _offsets[], const int _numDirections,  const int _directions[]) {
  set(_numOffsets,  _offsets, _numDirections, _directions);
  hasChildPattern = false;
  reset();
}

void Pattern::reset() {
  restart();
  setStepsLimit(numSteps);
  multiplier = 1;

  if(hasChildPattern) {
    childPattern->reset();
  }
}

void Pattern::restart() {
  currOffsetIdx = 0;
  currDirectionIdx = 0;
  currOffset = 0;
  currStep = 0;
  numSteps = offsets.getSize();
  setStepsLimit(stepsLimit); // make sure steps limit is in bounds

  if(hasChildPattern) {
    childPattern->restart();
  }
}

void Pattern::setChildPattern(Pattern* _childPattern) {
  childPattern = _childPattern;
  hasChildPattern = true;
}

Pattern* Pattern::getChildPattern() {
  return childPattern;
}

void Pattern::removeChildPattern() {
  hasChildPattern = false;
}

void Pattern::takeStep()
{
  bool moveToNextStep = true;
  
  if(hasChildPattern) {
    moveToNextStep = childPattern->isLastStep();
    childPattern->takeStep();
  }

  if(moveToNextStep) {

    if(isLastStep()) {
      currDirectionIdx = directions.getNextIdx(currDirectionIdx);
    }
 
    const int currDirection = getDirection(currDirectionIdx);
    
    switch(currDirection) {
      case Pattern::DIRECTION_UP:
        if(isLastStep()) {
          currOffsetIdx = 0;
        } else {
          currOffsetIdx = offsets.getNextIdx(currOffsetIdx);
        }
        break;
      case Pattern::DIRECTION_DOWN:
        if(isLastStep()) {
          currOffsetIdx = numSteps - 1;
        } else {
          currOffsetIdx = offsets.getPrevIdx(currOffsetIdx);
        }
        break;
      case Pattern::DIRECTION_RANDOM:
        currOffsetIdx = offsets.getRandomIdx();
        break;
    } 

    currStep++;
    if(currStep >= stepsLimit) {
      currStep = 0;
    }
  }
}

int Pattern::getCurrOffset() {
  return getOffset(currOffsetIdx);
}

int Pattern::getCurrOffsetIdx() {
  return currOffsetIdx;
}

int Pattern::getCurrOffsetSum() {
  int sum = 0;
  if(hasChildPattern) {
    sum += childPattern->getCurrOffsetSum();
  }
  sum += multiplier * getOffset(currOffsetIdx);

//  #ifdef DEBUG_PATTERN
//    Serial << "-----------------------------" << endl;
//    Serial << "Pattern - #getCurrOffsetSum: currOffsetIdx:" <<  currOffsetIdx << endl;
//    Serial << "Pattern - #getCurrOffsetSum: sum " <<  sum << endl;
//    Serial << "Pattern - #getCurrOffsetSum: isLastStep " <<  isLastStep() << endl;
//    Serial << "Pattern - #getCurrOffsetSum: numSteps " <<  numSteps << endl;
//    Serial << "Pattern - #getCurrOffsetSum: offsets.getSize() " <<  offsets.getSize() << endl;
//    Serial << "Pattern - #getCurrOffsetSum: stepsLimit " <<  stepsLimit << endl;
//  #endif
  
  return sum;
}

bool Pattern::isLastStep() {
  return (currStep >= stepsLimit - 1);
}

int Pattern::getOffset(int _idx) {
  return offsets.at(_idx, 0);
}

int Pattern::getDirection(int _idx) {
  return directions.at(_idx, Pattern::DIRECTION_UP);
}
    
int Pattern::getCurrStep() {
  return currStep;
}

int Pattern::getNumSteps() {
  return numSteps;
}

void Pattern::setStepsLimit(int _stepsLimit) {
  if(_stepsLimit > numSteps) {
    stepsLimit = numSteps;
    return;
  }

  if(_stepsLimit < 0) {
    stepsLimit = 0;
    return;
  }
  stepsLimit = _stepsLimit;
}

void Pattern::setOffsets(const int _numOffsets,  const int _offsets[]) {
  offsets.assign(_numOffsets, _offsets);
  restart();
}


void Pattern::setDirections(const int _numDirections,  const int _directions[]) {
  directions.assign(_numDirections, _directions);
  restart();
}

void Pattern::set(const int _numOffsets,  const int _offsets[], const int _numDirections,  const int _directions[]) {
  offsets.assign(_numOffsets, _offsets);
  directions.assign(_numDirections, _directions);
  restart();
}

void Pattern::setMultiplier(int _multiplier) {
  multiplier = _multiplier;
}

void Pattern::applyPreset(const int _preset) {
  #ifdef DEBUG_PATTERN
    Serial << "Pattern - #applyPreset: " <<  _preset << endl;
  #endif
  
  switch(_preset) {
    case 0:
      // OFF
      set(16, Pattern::PEDAL_OFFSETS, 1,  Pattern::DIRECTIONS_UP);
      setStepsLimit(0);
      setMultiplier(1);
      break;
    case 1:
      // PEDAL
      set(16, Pattern::PEDAL_OFFSETS, 1,  Pattern::DIRECTIONS_UP);
      setStepsLimit(8);
      setMultiplier(1);
      break;
    case 2:
      // Up
      set(16, Pattern::INC_OFFSETS, 1,  Pattern::DIRECTIONS_UP);
      setStepsLimit(16);
      setMultiplier(1);
      break;
    case 3:
      // Down
      set(16, Pattern::INC_OFFSETS, 1,  Pattern::DIRECTIONS_DOWN);  
      setStepsLimit(16);
      setMultiplier(1);  
      break;
    case 4:
      // Up - Triad Chord
      set(16, Pattern::INC_OFFSETS, 1,  Pattern::DIRECTIONS_UP);  
      setStepsLimit(3); 
      setMultiplier(2);
      break;
    case 5:
      // Down - Triad Chord
      set(16, Pattern::INC_OFFSETS, 1,  Pattern::DIRECTIONS_DOWN);  
      setStepsLimit(3); 
      setMultiplier(2);
      break;
    case 6:
      // Up - 7th Chord
      set(16, Pattern::INC_OFFSETS, 1,  Pattern::DIRECTIONS_UP);  
      setStepsLimit(4); 
      setMultiplier(2);
      break;
    case 7:
      // Down - 7th Chord
      set(16, Pattern::INC_OFFSETS, 1,  Pattern::DIRECTIONS_DOWN);  
      setStepsLimit(4); 
      setMultiplier(2);
      break;
    case 8:
      // Alt Bin 3 - Up
      set(16, Pattern::ALT_BIN_OFFSETS, 1,  Pattern::DIRECTIONS_UP);  
      setStepsLimit(3); 
      setMultiplier(2);
      break;
    case 9:
      // Alt Bin 3 - Down
      set(16, Pattern::ALT_BIN_OFFSETS, 1,  Pattern::DIRECTIONS_DOWN);  
      setStepsLimit(3); 
      setMultiplier(2);
      break;
    default:
      set(16,  Pattern::INC_OFFSETS, 1,  Pattern::DIRECTIONS_UP);
      setStepsLimit(8);  
      setMultiplier(1);
  }
}

