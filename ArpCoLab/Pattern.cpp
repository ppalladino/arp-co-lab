#include "Pattern.h"

const int Pattern::DIRECTION_UP = 0;
const int Pattern::DIRECTION_DOWN = 1;
const int Pattern::DIRECTION_RANDOM = 2;
    
Pattern::Pattern() {
   //Pattern childPattern;
}

void Pattern::init(const int _numOffsets,  const int _offsets[], const int _numDirections,  const int _directions[]) {
  offsets.assign(_numOffsets, _offsets);
  directions.assign(_numDirections, _directions);
  hasChildPattern = false;
  reset();
}

void Pattern::reset() {
  currOffsetIdx = 0;
  currDirectionIdx = 0;
  currOffset = 0;
  currStep = 0;
  numSteps = offsets.getSize(); // expose this parameter later

  if(hasChildPattern) {
    childPattern->reset();
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
    if(currStep >= numSteps) {
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
  sum += getOffset(currOffsetIdx);
  return sum;
}

bool Pattern::isLastStep() {
  return (currStep >= numSteps - 1);
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

    

