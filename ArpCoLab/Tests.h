#ifndef TESTS_H
#define TESTS_H

#include <Arduino.h>
#include <Streaming.h>
#include <assert.h>
#include "Array.h"
#include "TapTempo.h"
#include "Pattern.h"

class Tests
{
  public:
    Tests();
    void runTests();
    void runArrayTests();
    void runTapTempoTests();
    void runPatternTests();

  private:
    int numErrors;
    int numTests;
    void test(int line, bool condition, char message[]);
};

#endif
