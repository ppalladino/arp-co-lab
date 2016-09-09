#include "Tests.h"

Tests::Tests() {
  numErrors = 0;
  numTests = 0;
}

void Tests::runTests() {
  runArrayTests();
  runTapTempoTests();
  
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
    (intArray.getNextIdx(3) == 3), 
    "- the index after value 3 should be index 3"
  );
  test(
    __LINE__,
    (intArray.getNextIdx(5) == 0), 
    "- the index after value 5 DNE so should wrap and return 0"
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


    

