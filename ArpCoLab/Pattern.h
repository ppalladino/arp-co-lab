#ifndef PATTERN_H
#define PATTERN_H

#include <Arduino.h>
#include "IntArray.h"

#define MAX_PATTERN_SIZE 16
#define MAX_PATTERN_DIRECTIONS 16

#define MAX_PRESET_NUM 16

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
    void restart();

    Pattern* getChildPattern();
    void     set(const int _numOffsets,  const int _offsets[], const int _numDirections,  const int _directions[]);
    void     setChildPattern(Pattern* _childPattern);
    void     setStepsLimit(int _stepsLimit);
    void     setOffsets(const int _numOffsets,  const int _offsets[]);
    void     setDirections(const int _numDirections,  const int _directions[]);
    void     setMultiplier(int _multiplier);
    void     removeChildPattern();
    void     applyPreset(int _preset);

    static const int DIRECTION_UP;
    static const int DIRECTION_DOWN;
    static const int DIRECTION_RANDOM;

    static const int DIRECTIONS_UP[];
    static const int DIRECTIONS_DOWN[];
    static const int DIRECTIONS_UP_DOWN[];
    static const int DIRECTIONS_DOWN_UP[];

    static const int PEDAL_OFFSETS[];
    static const int INC_OFFSETS[];
    static const int ALT_BIN_OFFSETS[];

    static const int Pattern::BIN_PATTERN_1[];
    static const int Pattern::BIN_PATTERN_2[];

    // static void applyPreset(Pattern* _childPattern, int _preset);
 
  private:

    IntArray<MAX_PATTERN_DIRECTIONS>  directions;
    IntArray<MAX_PATTERN_SIZE>        offsets;
    
    Pattern* childPattern;
    int      currOffset;
    int      currOffsetIdx;
    int      currDirectionIdx;
    bool     hasChildPattern;
    int      currStep;
    int      numSteps;         
    int      stepsLimit;        // limit number of steps taken
    int      multiplier;        // multiplies offsets

    int  getDirection(int _idx);
    int  getOffset(int _idx);
};

#endif
