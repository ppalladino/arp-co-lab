#include <MIDI.h>
#include "Array.h"
#include "IntArray.h"
#include "SelectButton.h"
#include "TapTempo.h"
#include "Pattern.h"
#include "Scale.h"

#define MAX_ACTIVE_NOTES 4

#define TEMPO_PIN 22
#define OCTAVE_PIN 24
#define CHORD_INTERVALS_PIN 26

#define KEY_PIN 52

#define DEBUG_MAIN;

#ifdef DEBUG_MAIN
  #include <Streaming.h>
#endif

#define RUN_TESTS

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
  SelectButton keySelectButton;
  SelectButton octaveSelectButton;
  SelectButton chordIntervalsSelectButton;
  
  Pattern melodyPattern1;
  Pattern melodyPattern2;
  Array<int, MAX_PATTERN_DIRECTIONS> directionsUp;
  Array<int, MAX_PATTERN_SIZE> melodyPatternOffsets1;
  Array<int, MAX_PATTERN_SIZE> melodyPatternOffsets2;
  
  
  Array<Array<int, MAX_CHORD_SIZE>, 3> chordTypes;
  
  Scale scale;
  Array<int, MAX_CHORD_SIZE> chord;
  Array<int, MAX_ACTIVE_NOTES> activeNotes;
  
  void setup()
  {
    Serial.begin(9600);
   
    pinMode(TEMPO_PIN, OUTPUT);
    pinMode(OCTAVE_PIN, OUTPUT);
    pinMode(CHORD_INTERVALS_PIN, OUTPUT);
  
    pinMode(KEY_PIN, OUTPUT);
  
    MIDI.begin(MIDI_CHANNEL_OFF);
    
    int keys[3] = {1, 2, 3};
    keySelectButton.init(3, keys);
  
    int octaves[6] = {0, 1, 2, 3, 4, 5};
    octaveSelectButton.init(6, octaves, 2);
  
    int chordIntervals[5] = {0, 1, 2, 3, 4}; // R, R+3rd, R+5th, Triad, 7th
    chordIntervalsSelectButton.init(5, chordIntervals);
  
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
    chord = scale.getChord(0, 0);
  }
  
  void loop()
  { 
    int nowMs = millis();
  
    tapTempo.readPin(digitalRead(TEMPO_PIN), nowMs);
    octaveSelectButton.readPin(digitalRead(OCTAVE_PIN));
    chordIntervalsSelectButton.readPin(digitalRead(CHORD_INTERVALS_PIN));
    
    keySelectButton.readPin(digitalRead(KEY_PIN));
  
    if(tapTempo.isBeat(nowMs)) {
      //Serial.print("* Beat:");
      //Serial.println(tapTempo.getBpm());
  
      //
      // Clear old notes
      //
      
      for(int i = 0; i < activeNotes.getSize(); i++) {
        MIDI.sendNoteOff(activeNotes.at(i, 0), 127, 1);
      }
      activeNotes.clear();
  
  
      int octaveOffset = (octaveSelectButton.getSelectedOption() * 12);
      int melodyOffset = melodyPattern1.getCurrOffsetSum();
      chord = scale.getChord(melodyOffset, 0);
  
      activeNotes.clear();
      switch(chordIntervalsSelectButton.getSelectedOption() ) {
        case 0: // Root
          activeNotes.push(chord.at(0, 0)  + octaveOffset);
          break;
        case 1: // R+3rd
          activeNotes.push(chord.at(0, 0)  + octaveOffset);
          activeNotes.push(chord.at(1, 0)  + octaveOffset);
          break;
        case 2: // R+5th
          activeNotes.push(chord.at(0, 0)  + octaveOffset);
          activeNotes.push(chord.at(2, 0)  + octaveOffset);
          break;
        case 3: // Triad
          activeNotes.push(chord.at(0, 0)  + octaveOffset);
          activeNotes.push(chord.at(1, 0)  + octaveOffset);
          activeNotes.push(chord.at(2, 0)  + octaveOffset);
          break;
        case 4: // 7th
          activeNotes.push(chord.at(0, 0)  + octaveOffset);
          activeNotes.push(chord.at(1, 0)  + octaveOffset);
          activeNotes.push(chord.at(2, 0)  + octaveOffset);
          activeNotes.push(chord.at(3, 0)  + octaveOffset);
          break;
      }
  
      
      #ifdef DEBUG_MAIN
        Serial << "**********************" << endl;
        // Serial << "note: " << note << endl;
        Serial << "melodyOffset: " << melodyOffset << endl;
        Serial << "octave: " << octaveSelectButton.getSelectedOption() << endl;
        Serial << "octaveOffset: " << octaveOffset << endl;
        Serial << "chordInterval Mode: " << chordIntervalsSelectButton.getSelectedOption() << endl;
      #endif
  
      
      for(int i = 0; i < activeNotes.getSize(); i++) {
        MIDI.sendNoteOn(activeNotes.at(i, 0), 127, 1);
        //Serial << "!!!!!!!!!!!!!!!!!!!!!!!: " << activeNotes.at(i, 0) << endl;
      } 
  
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

