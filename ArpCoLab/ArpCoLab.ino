#include <MIDI.h>
#include "Array.h"
#include "SelectButton.h"
#include "TapTempo.h"
#include "Pattern.h"
#include "Scale.h"

#define KEY_PIN 24
#define TEMPO_PIN 22

#define DEBUG_MAIN;

#ifdef DEBUG_MAIN
  #include <Streaming.h>
#endif

// Uncomment to run tests
//#include "Tests.h"
//void setup() {
//  Serial.begin(9600);
//  Tests tests;
//  tests.runTests();
//}
//void loop() {}

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

TapTempo tapTempo;
SelectButton<int, 3> keySelectButton;
Pattern melodyPattern1;
Pattern melodyPattern2;
Array<int, MAX_PATTERN_DIRECTIONS> directionsUp;
Array<int, MAX_PATTERN_SIZE> melodyPatternOffsets1;
Array<int, MAX_PATTERN_SIZE> melodyPatternOffsets2;

Scale scale;
Array<int, MAX_CHORD_SIZE> chord;

void setup()
{
  Serial.begin(9600);

  pinMode(KEY_PIN, OUTPUT);
  pinMode(TEMPO_PIN, OUTPUT);

  MIDI.begin(MIDI_CHANNEL_OFF);
  
  int keyValues[3] = {1, 2, 3};
  Array<int, 3> keys(keyValues);
  keySelectButton.init(keys, 2);

  const int directionsUp[1] = {Pattern::DIRECTION_UP};
  const int melody1[8] = {0, 1, 2, 3, 4, 5, 6, 7};
  const int melody2[3] = {1, 0, 1};

  melodyPattern1.init(8, melody1, 1, directionsUp);
  melodyPattern2.init(3, melody2, 1, directionsUp);
  melodyPattern1.setChildPattern(&melodyPattern2);

  tapTempo.init(250, TapTempo::QUARTER_NOTE, TapTempo::QUARTER_NOTE);

  scale.init(Scale::C_0 + 5*12, Scale::INTERVALS_MINOR_P_SIZE,  Scale::INTERVALS_MINOR_P);
  chord = scale.getChord(0);
}

void loop()
{ 
  int nowMs = millis();
  keySelectButton.readPin(digitalRead(KEY_PIN));
  tapTempo.readPin(digitalRead(TEMPO_PIN), nowMs);

  if(tapTempo.isBeat(nowMs)) {
    //Serial.print("* Beat:");
    //Serial.println(tapTempo.getBpm());

    
    MIDI.sendNoteOff(chord.at(0), 127, 1);
    MIDI.sendNoteOff(chord.at(1), 127, 1);

    chord = scale.getChord(melodyPattern1.getCurrOffsetSum());
    

    #ifdef DEBUG_MAIN
      Serial << "Main - chord: " << chord.at(0) << endl;
    #endif
    
    MIDI.sendNoteOn(chord.at(0), 127, 1);
    MIDI.sendNoteOn(chord.at(1), 127, 1);
    
    melodyPattern1.takeStep();
  }
}

