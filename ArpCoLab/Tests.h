#ifndef TESTS_H
#define TESTS_H

#include <Arduino.h>
#include <Streaming.h>
#include <assert.h>
#include "Array.h"
#include "IntArray.h"
#include "TapTempo.h"
#include "Pattern.h"
#include "Scale.h"

class Tests
{
  public:
    Tests();
    void runTests();
    void runArrayTests();
    void runIntArrayTests();
    void runTapTempoTests();
    void runPatternTests();
    void runScaleTests();

  private:
    int numErrors;
    int numTests;
    void test(int line, bool condition, char message[]);
};

#endif
