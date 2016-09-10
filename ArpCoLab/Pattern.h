#ifndef PATTERN_H
#define PATTERN_H

#include <Arduino.h>
#include "Array.h"

#define MAX_PATTERN_SIZE 16
#define MAX_PATTERN_DIRECTIONS 16

class Pattern {
  public:
  
    Pattern();

    void init(const int _numOffsets,  const int _offsets[], const int _numDirections,  const int _directions[]);

    int  getCurrOffset();    // Returns only this pattern's offset. Not it's child's
    int  getCurrOffsetIdx(); // Returns only this pattern's offsetIdx. Not it's child's
    int  getCurrOffsetSum(); // Calculates and returns current offset plus children's offsets
    
    int  getNumSteps();
    int  getCurrStep();   
    bool isLastStep();
    void takeStep();            // Takes next step in the pattern
    void reset();
    
    void     setChildPattern(Pattern* _childPattern);
    Pattern* getChildPattern();
    void     removeChildPattern();

    static const int DIRECTION_UP;
    static const int DIRECTION_DOWN;
    static const int DIRECTION_RANDOM;
 
  private:

    Array<int, MAX_PATTERN_DIRECTIONS>  directions;
    Array<int, MAX_PATTERN_SIZE>        offsets;
    
    Pattern* childPattern;
    int      currOffset;
    int      currOffsetIdx;
    int      currDirectionIdx;
    bool     hasChildPattern;
    int      currStep;
    int      numSteps;

    int  getDirection(int _idx);
    int  getOffset(int _idx);
};

#endif
