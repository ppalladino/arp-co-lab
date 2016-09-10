#include "Tests.h"

#define DEBUG;

Tests::Tests() {
  numErrors = 0;
  numTests = 0;
}

void Tests::runTests() {
  runArrayTests();
  runTapTempoTests();
  runPatternTests();
  runScaleTests();
  
  Serial << "//////////////////////////////////////////////////////////////////////" << endl;
  Serial << "Ran " << numTests << " tests" << endl;
  if(numErrors == 0) {
    Serial << "ALL PASSED!" << endl;
  } else {
    Serial << "ERRORS!! There were " << numErrors << " errors." << endl;
  }
}

void Tests::test(int line, bool condition, char message[]) {
  numTests += 1;
  
  if(condition == true) 
  {   
    // Serial << message << endl;
    return;
  }

  numErrors += 1;

  Serial << "ERROR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
  Serial << message << endl;
  Serial << " on line " << line  << endl;
}

//////////////////////////////////////////////////////////////////////
//
// Array Tests
//
//////////////////////////////////////////////////////////////////////

void Tests::runArrayTests() {

  // Used in various tests, do not mutate!!
  const int intValuesSize = 5;
  const int intValues[intValuesSize] = {1, 2, 3, 4, 5};
  Array<int, intValuesSize> intArray(intValues);

  //
  // Array: Initialization
  //
  
  Serial << "#Array: initialize with array of integers" << endl;
  test(
    __LINE__,
    (intArray.getSize() == 5), 
    "- size should be 5"
  );
  test(
    __LINE__,
    (intArray.at(0) == 1), 
    "- at(0) should return 0"
  );
  test(
    __LINE__,
    (intArray.at(4) == 5), 
    "- at(0) should return 0"
  );

  //
  // Array: Push values
  //

  Serial << "#Array: push values" << endl;
  Array<int, 5> pushedValuesArray;
  test(
    __LINE__,
    (pushedValuesArray.getSize() == 0), 
    "- initial size should be 0"
  );
  pushedValuesArray.push(1);
  test(
    __LINE__,
    (pushedValuesArray.getSize() == 1), 
    "- size should now be 1"
  );
  test(
    __LINE__,
    (pushedValuesArray.at(0) == 1), 
    "- first value should be 1"
  );
  pushedValuesArray.push(66);
  test(
    __LINE__,
    (pushedValuesArray.getSize() == 2), 
    "- size should now be 2"
  );
  test(
    __LINE__,
    (pushedValuesArray.at(1) == 66), 
    "- first value should be 66"
  );

  //
  // Array: Initialize with fill values
  //
  
  Serial << "#Array: initialize with fill values" << endl;
  Array<int, 5> arrayFilled(0);
  test(
    __LINE__,
    (arrayFilled.getSize() == 5), 
    "- size should be 5"
  );
  test(
    __LINE__,
    (arrayFilled.at(0) == 0), 
    "- first value should be 0"
  );
  test(
    __LINE__,
    (arrayFilled.at(4) == 0), 
    "- last value should be 0"
  );
  arrayFilled.fill(33);
   test(
    __LINE__,
    (arrayFilled.getSize() == 5), 
    "- size should still be 5"
  );
  test(
    __LINE__,
    (arrayFilled.at(0) == 33), 
    "- first value should be 33"
  );
  test(
    __LINE__,
    (arrayFilled.at(4) == 33), 
    "- last value should be 33"
  );

  //
  // Array: Assign values
  //

  Serial << "#Array: assign values" << endl;
  Array<int, 5> assignArray(0);
  test(
    __LINE__,
    (assignArray.getSize() == 5), 
    "- initial size should be 5"
  );
  const int assignValues[3] = {0, 1, 2};
  assignArray.assign(3, assignValues);
  test(
    __LINE__,
    (assignArray.getSize() == 3), 
    "- assigned size should be 3"
  );

  //
  // Array: Get Index
  //

  Serial << "#Array: get index of" << endl;
  test(
    __LINE__,
    (intArray.getIdx(3) == 2), 
    "- 3 should be at idx 2"
  );
   test(
    __LINE__,
    (intArray.getIdx(99) == -1), 
    "- 99 will not be found so should be -1"
  );

  //
  // Array: Get Next Index
  //

  Serial << "#Array: get next index" << endl;
  test(
    __LINE__,
    (intArray.getNextIdx(0) == 1), 
    "- the index after idx 0 should be index 1"
  );
  test(
    __LINE__,
    (intArray.getNextIdx(4) == 0), 
    "- the index after idx 4 so should wrap and return 0"
  );

  //
  // Array: Get Prev Index
  //

  Serial << "#Array: get prev index" << endl;
  test(
    __LINE__,
    (intArray.getPrevIdx(0) == 4), 
    "- the index prev idx 0 should wrap and return 4"
  );
  test(
    __LINE__,
    (intArray.getPrevIdx(4) == 3), 
    "- the prev after idx 4 so should return 3"
  );
  test(
    __LINE__,
    (intArray.getPrevIdx(14) == 4), 
    "- the prev after idx 14 is OOB so should return last idx = 4"
  );
}

//////////////////////////////////////////////////////////////////////
//
// Tap Tempo Tests
//
//////////////////////////////////////////////////////////////////////

void Tests::runTapTempoTests() {

  // Used in various tests, do not mutate!!
  TapTempo tapTempo; 
  int currTapDuration = 1000;
  int currTapSubDivision = TapTempo::QUARTER_NOTE;
  int currBeatSubDivision = TapTempo::QUARTER_NOTE;
  int currMs = 123;
  
  //
  // TapTempo: Initialization
  //
  
  Serial << "#TapTempo: initialize" << endl;
  tapTempo.init(currTapDuration, currTapSubDivision, currBeatSubDivision);
  test(
    __LINE__,
    (tapTempo.getTapDurationMs() == currTapDuration), 
    "- tap duration should be 1000"
  );
  test(
    __LINE__,
    (tapTempo.isBeat(currMs) == false), 
    "- not a beat yet"
  );

  Serial << "#TapTempo: beat it" << endl;
  currMs = 1001;
  test(
    __LINE__,
    (tapTempo.isBeat(currMs) == true), 
    "- just after a beat"
  );

  Serial << "#TapTempo: tap in new duration" << endl;
  currMs = 2000;
  tapTempo.readPin(1, currMs); // Tap 1
  currMs = 2500;
  tapTempo.readPin(0, currMs); // Rest
  currMs = 2500;
  tapTempo.readPin(1, currMs); // Tap 2
  // Serial << "#debug: tap duration: " << tapTempo.getTapDurationMs() << endl;
  test(
    __LINE__,
    (tapTempo.getTapDurationMs() == 500), 
    "- tap duration should have updated"
  );
  test(
    __LINE__,
    (tapTempo.isBeat(currMs) == true), 
    "- its been a while since last last check"
  );
  currMs = 2750;
  test(
    __LINE__,
    (tapTempo.isBeat(currMs) == false), 
    "- in the middle of a beat"
  );
  currMs = 3000;
  test(
    __LINE__,
    (tapTempo.isBeat(currMs) == true), 
    "- on the beat"
  );

  Serial << "#TapTempo: setTapSubDivision" << endl;
  currMs = 4000;
  tapTempo.isBeat(currMs); // set lastBeatMs
  tapTempo.setTapSubDivision(TapTempo::WHOLE_NOTE);
  currMs = 4100;
  test(
    __LINE__,
    (tapTempo.isBeat(currMs) == false), 
    "- before the beat"
  );
  currMs = 4126;
  test(
    __LINE__,
    (tapTempo.isBeat(currMs) == true), 
    "- just after the beat"
  );

  Serial << "#TapTempo: setBeatSubDivision" << endl;
  currMs = 5000;
  tapTempo.isBeat(currMs); // set lastBeatMs
  tapTempo.setBeatSubDivision(TapTempo::SIXTEENTH_NOTE);
  currMs = 5025;
  test(
    __LINE__,
    (tapTempo.isBeat(5025) == false), 
    "- before the beat"
  );
  currMs = 5033;
  test(
    __LINE__,
    (tapTempo.isBeat(currMs) == true), 
    "- just after the beat"
  );
}

//////////////////////////////////////////////////////////////////////
//
// Pattern Tests
//
//////////////////////////////////////////////////////////////////////

void Tests::runPatternTests() {

  // Used in various tests, do not mutate!!
  const int offsets012[3] = {0, 1, 2};
  const int offset01[2] = {0, 1};
  const int directionsUp[1] = {Pattern::DIRECTION_UP};
  const int directionsUpDown[2] = {Pattern::DIRECTION_UP, Pattern::DIRECTION_DOWN};
  
  //
  // Pattern: Initialization
  //
  
  Serial << "#Pattern: initialize" << endl;
  Pattern pattern; 
  Pattern childPattern; 
  childPattern.init(2, offset01, 1, directionsUp);
  
  pattern.init(3, offsets012, 2, directionsUpDown);
  pattern.setChildPattern(&childPattern);
  
  test(
    __LINE__,
    (pattern.getNumSteps() == 3), 
    "- numSteps should be 3"
  );
  test(
    __LINE__,
    (pattern.getChildPattern()->getNumSteps() == 2), 
    "- child numSteps should be 2"
  );  
  test(
    __LINE__,
    (pattern.getCurrStep() == 0), 
    "- curr step should be 0"
  );
  test(
    __LINE__,
    (pattern.getChildPattern()->getCurrStep() == 0), 
    "- child curr step should be 0"
  );  
  test(
    __LINE__,
    (pattern.getCurrOffsetSum() == 0), 
    "- offset should be 0"
  );
  
  Serial << "#Pattern: step 1" << endl;
  pattern.takeStep();
  test(__LINE__, (pattern.getCurrStep()      == 0)                    , "- parent currStep");
  test(__LINE__, (pattern.getCurrOffsetIdx() == 0)                    , "- parent offset idx");
  test(__LINE__, (pattern.getCurrOffset()    == 0)                    , "- parent offset");
  
  test(__LINE__, (pattern.getChildPattern()->getCurrStep()      == 1) , "- child currStep");
  test(__LINE__, (pattern.getChildPattern()->getCurrOffsetIdx() == 1) , "- child offset idx");
  test(__LINE__, (pattern.getChildPattern()->getCurrOffset()    == 1) , "- child offset");

  test(__LINE__, (pattern.getCurrOffsetSum() == 1)                    , "- offset sum");

  Serial << "#Pattern: step 2" << endl;
  pattern.takeStep();
  test(__LINE__, (pattern.getCurrStep()                         == 1) , "- parent currStep");
  test(__LINE__, (pattern.getCurrOffset()                       == 1) , "- parent offset");
  test(__LINE__, (pattern.getChildPattern()->getCurrStep()      == 0) , "- child currStep");
  test(__LINE__, (pattern.getChildPattern()->getCurrOffset()    == 0) , "- child offset");
  test(__LINE__, (pattern.getCurrOffsetSum()                    == 1) , "- offset sum");

  Serial << "#Pattern: step 3" << endl;
  pattern.takeStep();
  test(__LINE__, (pattern.getCurrStep()                         == 1) , "- parent currStep");
  test(__LINE__, (pattern.getCurrOffset()                       == 1) , "- parent offset");
  test(__LINE__, (pattern.getChildPattern()->getCurrStep()      == 1) , "- child currStep");
  test(__LINE__, (pattern.getChildPattern()->getCurrOffset()    == 1) , "- child offset");
  test(__LINE__, (pattern.getCurrOffsetSum()                    == 2) , "- offset sum");

  Serial << "#Pattern: step 4" << endl;
  pattern.takeStep();
  test(__LINE__, (pattern.getCurrStep()                         == 2) , "- parent currStep");
  test(__LINE__, (pattern.getCurrOffset()                       == 2) , "- parent offset");
  test(__LINE__, (pattern.getChildPattern()->getCurrStep()      == 0) , "- child currStep");
  test(__LINE__, (pattern.getChildPattern()->getCurrOffset()    == 0) , "- child offset");
  test(__LINE__, (pattern.getCurrOffsetSum()                    == 2) , "- offset sum");

  Serial << "#Pattern: step 5" << endl;
  pattern.takeStep();
  test(__LINE__, (pattern.getCurrStep()                         == 2) , "- parent currStep");
  test(__LINE__, (pattern.getCurrOffset()                       == 2) , "- parent offset");
  test(__LINE__, (pattern.getChildPattern()->getCurrStep()      == 1) , "- child currStep");
  test(__LINE__, (pattern.getChildPattern()->getCurrOffset()    == 1) , "- child offset");
  test(__LINE__, (pattern.getCurrOffsetSum()                    == 3) , "- offset sum");

  Serial << "#Pattern: step 6" << endl;
  pattern.takeStep();
  test(__LINE__, (pattern.getCurrStep()                         == 0) , "- parent currStep");  
  test(__LINE__, (pattern.getCurrOffset()                       == 2) , "- parent offset");    
  test(__LINE__, (pattern.getChildPattern()->getCurrStep()      == 0) , "- child currStep");
  test(__LINE__, (pattern.getChildPattern()->getCurrOffset()    == 0) , "- child offset");
  test(__LINE__, (pattern.getCurrOffsetSum()                    == 2) , "- offset sum");

  Serial << "#Pattern: step 7" << endl;
  pattern.takeStep();
  test(__LINE__, (pattern.getCurrStep()                         == 0) , "- parent currStep");
  test(__LINE__, (pattern.getCurrOffset()                       == 2) , "- parent offset");
  test(__LINE__, (pattern.getChildPattern()->getCurrStep()      == 1) , "- child currStep");
  test(__LINE__, (pattern.getChildPattern()->getCurrOffset()    == 1) , "- child offset");
  test(__LINE__, (pattern.getCurrOffsetSum()                    == 3) , "- offset sum");

  Serial << "#Pattern: step 8" << endl;
  pattern.takeStep();
  test(__LINE__, (pattern.getCurrStep()                         == 1) , "- parent currStep");
  test(__LINE__, (pattern.getCurrOffset()                       == 1) , "- parent offset");
  test(__LINE__, (pattern.getChildPattern()->getCurrStep()      == 0) , "- child currStep");
  test(__LINE__, (pattern.getChildPattern()->getCurrOffset()    == 0) , "- child offset");
  test(__LINE__, (pattern.getCurrOffsetSum()                    == 1) , "- offset sum");

  Serial << "#Pattern: step 9" << endl;
  pattern.takeStep();
  test(__LINE__, (pattern.getCurrStep()                         == 1) , "- parent currStep");
  test(__LINE__, (pattern.getCurrOffset()                       == 1) , "- parent offset");
  test(__LINE__, (pattern.getChildPattern()->getCurrStep()      == 1) , "- child currStep");
  test(__LINE__, (pattern.getChildPattern()->getCurrOffset()    == 1) , "- child offset");
  test(__LINE__, (pattern.getCurrOffsetSum()                    == 2) , "- offset sum");

  Serial << "#Pattern: step 10" << endl;
  pattern.takeStep();
  test(__LINE__, (pattern.getCurrStep()                         == 2) , "- parent currStep");
  test(__LINE__, (pattern.getCurrOffset()                       == 0) , "- parent offset");
  test(__LINE__, (pattern.getChildPattern()->getCurrStep()      == 0) , "- child currStep");
  test(__LINE__, (pattern.getChildPattern()->getCurrOffset()    == 0) , "- child offset");
  test(__LINE__, (pattern.getCurrOffsetSum()                    == 0) , "- offset sum");

  Serial << "#Pattern: step 11" << endl;
  pattern.takeStep();
  test(__LINE__, (pattern.getCurrStep()                         == 2) , "- parent currStep");
  test(__LINE__, (pattern.getCurrOffset()                       == 0) , "- parent offset");
  test(__LINE__, (pattern.getChildPattern()->getCurrStep()      == 1) , "- child currStep");
  test(__LINE__, (pattern.getChildPattern()->getCurrOffset()    == 1) , "- child offset");
  test(__LINE__, (pattern.getCurrOffsetSum()                    == 1) , "- offset sum");

  Serial << "#Pattern: step 12 (back to beginning)" << endl;
  pattern.takeStep();
  test(__LINE__, (pattern.getCurrStep()                         == 0) , "- parent currStep");
  test(__LINE__, (pattern.getCurrOffset()                       == 0) , "- parent offset");
  test(__LINE__, (pattern.getChildPattern()->getCurrStep()      == 0) , "- child currStep");
  test(__LINE__, (pattern.getChildPattern()->getCurrOffset()    == 0) , "- child offset");
  test(__LINE__, (pattern.getCurrOffsetSum()                    == 0) , "- offset sum");
}

//////////////////////////////////////////////////////////////////////
//
// Scale Tests
//
//////////////////////////////////////////////////////////////////////

void Tests::runScaleTests() {
  
  Serial << "#Scale: initialize" << endl;
  Scale scale;
  scale.init(Scale::C_0, Scale::INTERVALS_MAJOR_SIZE,  Scale::INTERVALS_MAJOR);
  Array<int, MAX_CHORD_SIZE> chord;

  //
  // Scale: Chord values
  //
  
  Serial << "#Chord: #getNote" << endl;
  test(__LINE__, (scale.getNote(0) == Scale::C_0),          "- 0 note should be C");
  test(__LINE__, (scale.getNote(1) == Scale::D_0),          "- 1 note should be D");
  test(__LINE__, (scale.getNote(2) == Scale::E_0),          "- 2 note should be E");
  test(__LINE__, (scale.getNote(3) == Scale::F_0),          "- 3 note should be F");
  test(__LINE__, (scale.getNote(4) == Scale::G_0),          "- 4 note should be G");
  test(__LINE__, (scale.getNote(5) == Scale::A_0),          "- 5 note should be A");
  test(__LINE__, (scale.getNote(6) == Scale::B_0),          "- 6 note should be B");
  test(__LINE__, (scale.getNote(7) == (Scale::C_0 + 12)),   "- 7 note should be C1");
  test(__LINE__, (scale.getNote(8) == (Scale::D_0 + 12)),   "- 8 note should be D1");
  
  //
  // Scale: Chord values
  //
  
  Serial << "#Chord: I chord" << endl;
  chord = scale.getChord(0);
  test(__LINE__, (chord.getSize() == 5),       "- 5 notes to chord");
  test(__LINE__, (chord.at(0) == Scale::C_0),  "- root of I");
  test(__LINE__, (chord.at(1) == Scale::E_0),  "- third of I");
  test(__LINE__, (chord.at(2) == Scale::G_0),  "- fifth of I");
  test(__LINE__, (chord.at(3) == Scale::B_0),  "- seventh of I");

  Serial << "#Chord: ii chord" << endl;
  chord = scale.getChord(1);
  test(__LINE__, (chord.getSize() == 5),            "- 5 notes to chord");
  test(__LINE__, (chord.at(0) == Scale::D_0),       "- root of ii");
  test(__LINE__, (chord.at(1) == Scale::F_0),       "- third of ii");
  test(__LINE__, (chord.at(2) == Scale::A_0),       "- fifth of ii");
  test(__LINE__, (chord.at(3) == Scale::C_0 + 12),  "- seventh of ii");

  Serial << "#Chord: iii chord" << endl;
  chord = scale.getChord(2);
  test(__LINE__, (chord.getSize() == 5),            "- 5 notes to chord");
  test(__LINE__, (chord.at(0) == Scale::E_0),       "- root of iii");
  test(__LINE__, (chord.at(1) == Scale::G_0),       "- third of iii");
  test(__LINE__, (chord.at(2) == Scale::B_0),       "- fifth of iii");
  test(__LINE__, (chord.at(3) == Scale::D_0 + 12),  "- seventh of iii");

  Serial << "#Chord: IV chord" << endl;
  chord = scale.getChord(3);
  test(__LINE__, (chord.getSize() == 5),            "- 5 notes to chord");
  test(__LINE__, (chord.at(0) == Scale::F_0),       "- root of IV");
  test(__LINE__, (chord.at(1) == Scale::A_0),       "- third of IV");
  test(__LINE__, (chord.at(2) == Scale::C_0 + 12),  "- fifth of IV");
  test(__LINE__, (chord.at(3) == Scale::E_0 + 12),  "- seventh of IV");
  //Serial << "#DEBUG: " << chord.at(3) << endl;
}


    

