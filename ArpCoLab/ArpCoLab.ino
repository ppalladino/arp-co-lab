#include <MIDI.h>
#include "Array.h"
#include "IntArray.h"
#include "SelectButton.h"
#include "TapTempo.h"
#include "Pattern.h"
#include "Scale.h"

#define TEMPO_PIN 22
#define OCTAVE_PIN 24
#define CHORD_INTERVALS_PIN 26

#define DEBUG_MAIN;

#ifdef DEBUG_MAIN
  #include <Streaming.h>
#endif

// #define RUN_TESTS

#ifdef RUN_TESTS
  #include "Tests.h"
  void setup() {
    Serial.begin(9600);
    Tests tests;
    tests.runTests();
  }
  void loop() {}
#endif

#ifndef RUN_TESTS
  MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
  
  TapTempo tapTempo;
  
  SelectButton octaveSelectButton;
  SelectButton chordIntervalsSelectButton;
  
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
   
    pinMode(TEMPO_PIN, OUTPUT);
    pinMode(OCTAVE_PIN, OUTPUT);
    pinMode(CHORD_INTERVALS_PIN, OUTPUT);
  
    MIDI.begin(MIDI_CHANNEL_OFF);
    
    octaveSelectButton.init(0, 5, 2); 
    chordIntervalsSelectButton.init(0, Scale::CHORD_INTERVALS.getLastIdx());
  
    const int directionsUp[1] = {Pattern::DIRECTION_UP};
    const int directionsUpDown[2] = {Pattern::DIRECTION_UP, Pattern::DIRECTION_DOWN};
    
    const int melody1[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    melodyPattern1.init(8, melody1, 2, directionsUpDown);
    
  //  const int melody1[8] = {0, 1, 2, 3, 4, 5, 6, 7};
  //  const int melody2[3] = {1, 0, 1};
  //  melodyPattern1.init(8, melody1, 1, directionsUp);
  //  melodyPattern2.init(3, melody2, 1, directionsUp);
  //  melodyPattern1.setChildPattern(&melodyPattern2);
  
    tapTempo.init(1000, TapTempo::QUARTER_NOTE, TapTempo::QUARTER_NOTE);
  
    scale.init(Scale::C_0, Scale::INTERVALS_MAJOR_SIZE,  Scale::INTERVALS_MAJOR);
  }
  
  void loop()
  { 
    int nowMs = millis();
  
    tapTempo.readPin(digitalRead(TEMPO_PIN), nowMs);
    octaveSelectButton.readPin(digitalRead(OCTAVE_PIN));
    chordIntervalsSelectButton.readPin(digitalRead(CHORD_INTERVALS_PIN));
      
    if(tapTempo.isBeat(nowMs)) {
      //Serial.print("* Beat:");
      //Serial.println(tapTempo.getBpm());
  
      //
      // Clear old notes
      //
      
      for(int i = 0; i < chord.getSize(); i++) {
        MIDI.sendNoteOff(chord.at(i, 0), 127, 1);
      }
  
  
      int octaveOffset = (octaveSelectButton.getSelectedOption() * 12);
      int melodyOffset = melodyPattern1.getCurrOffsetSum();
      chord = scale.getChord(
        octaveOffset + melodyOffset, 
        chordIntervalsSelectButton.getSelectedOption()
      );
  
      for(int i = 0; i < chord.getSize(); i++) {
        MIDI.sendNoteOn(chord.at(i, 0), 127, 1);
      }
  
      
      #ifdef DEBUG_MAIN
        Serial << "**********************" << endl;
        // Serial << "note: " << note << endl;
        Serial << "melodyOffset: " << melodyOffset << endl;
        Serial << "octave: " << octaveSelectButton.getSelectedOption() << endl;
        Serial << "octaveOffset: " << octaveOffset << endl;
        Serial << "chordInterval Mode: " << chordIntervalsSelectButton.getSelectedOption() << endl;
      #endif
  
      
  //    note = chord.at(0, 0) + octaveOffset;
  //    note = note > 127 ? 127 : note;
  //    note = note < 0 ? 0 : note;
  
      
  //    MIDI.sendNoteOn(chord.at(1, 0), 127, 1);
  
      //
      // For next iteration
      //
      
      melodyPattern1.takeStep();
    }
  }
  
#endif // RUN_TESTS

