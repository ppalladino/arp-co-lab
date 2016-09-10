//#include "Tests.h"

#include <MIDI.h>
#include "Array.h"
#include "SelectButton.h"
#include "TapTempo.h"
#include "Pattern.h"

#define KEY_PIN 24
#define TEMPO_PIN 22

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

//void setup() {
//  Serial.begin(9600);
//  Tests tests;
//  tests.runTests();
//}
//void loop() {
//}

TapTempo tapTempo;
SelectButton<int, 3> keySelectButton;
Pattern melodyPattern1;
Pattern melodyPattern2;
Array<int, MAX_PATTERN_DIRECTIONS> directionsUp;
Array<int, MAX_PATTERN_SIZE> melodyPatternOffsets1;
Array<int, MAX_PATTERN_SIZE> melodyPatternOffsets2;

int note = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(KEY_PIN, OUTPUT);
  pinMode(TEMPO_PIN, OUTPUT);

  MIDI.begin(MIDI_CHANNEL_OFF);
  
  int keyValues[3] = {1, 2, 3};
  Array<int, 3> keys(keyValues);
  keySelectButton.init(keys, 2);

  const int directionValuesUp[1] = {Pattern::DIRECTION_UP};
  directionsUp.assign(1, directionValuesUp);
  const int melodyPatternOffsetsValues1[4] = {0, 1, 2, 3};
  melodyPatternOffsets1.assign(4, melodyPatternOffsetsValues1);
  const int melodyPatternOffsetsValues2[3] = {1, 0, 1};
  melodyPatternOffsets2.assign(3, melodyPatternOffsetsValues2);

  melodyPattern1.init(melodyPatternOffsets1, directionsUp);
  melodyPattern2.init(melodyPatternOffsets2, directionsUp);
  melodyPattern1.setChildPattern(&melodyPattern2);

  tapTempo.init(1000, TapTempo::QUARTER_NOTE, TapTempo::QUARTER_NOTE);
}

void loop()
{ 
  int nowMs = millis();
  keySelectButton.readPin(digitalRead(KEY_PIN));
  tapTempo.readPin(digitalRead(TEMPO_PIN), nowMs);

  if(tapTempo.isBeat(nowMs)) {
    Serial.print("* Beat:");
    Serial.println(tapTempo.getBpm());

    
    MIDI.sendNoteOff(note, 127, 1);

    note = 40 + melodyPattern1.getCurrOffsetSum();

    MIDI.sendNoteOn(note, 127, 1);
    
    melodyPattern1.takeStep();
  }
}

