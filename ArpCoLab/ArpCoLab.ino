#include <SPI.h>
#include "ShiftRegisterButtons.h"
byte Check=1;
bool busy = false;

#define LATCH_PIN 22
#define BUTTON_PIN 2 // for mega must be one of 2, 3, 18, 19, 20, 21
#define NUM_REGISTERS 4

ShiftRegisterButtons buttons;

void setup (){
  pinMode(51, OUTPUT); // data
  pinMode(52, OUTPUT); // clock
  pinMode(LATCH_PIN, OUTPUT); // latch
  pinMode(BUTTON_PIN, INPUT);  // input from buttons
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.begin();
  buttons.init(NUM_REGISTERS, BUTTON_PIN, LATCH_PIN);
  Serial.begin(9600);
}

void loop() {
  int pre = millis();
  int key = buttons.readButtonBusPin();
  int post = millis();
  if(key > -1) {
    Serial.println(key);
    Serial.println(post - pre);
  }
}

//#include <MIDI.h>
//#include "Array.h"
//#include "IntArray.h"
//#include "SelectButton.h"
//#include "TapTempo.h"
//#include "Pattern.h"
//#include "Scale.h"
//
//#define TEMPO_PIN 22
//#define OCTAVE_PIN 24
//#define CHORD_INTERVALS_PIN 26
//#define SUSTAIN_PIN 28
//#define PATTERN_1_PRESET_PIN 30
//#define PATTERN_2_PRESET_PIN 32
//
//
//#define DEBUG_MAIN;
//#ifdef DEBUG_MAIN
//  #include <Streaming.h>
//#endif
//
//// #define RUN_TESTS
//
//#ifdef RUN_TESTS
//  #include "Tests.h"
//  void setup() {
//    Serial.begin(9600);
//    Tests tests;
//    tests.runTests();
//  }
//  void loop() {}
//#endif
//
//#ifndef RUN_TESTS
//  MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
//
//  TapTempo tapTempo;
//
//  Pattern melodyPattern1;
//  Pattern melodyPattern2;
//
//  Pattern mutePattern;
//
//  SelectButton octaveSelectButton;
//  SelectButton chordIntervalsSelectButton;
//  SelectButton sustainSelectButton;
//  SelectButton pattern1SelectButton;
//  SelectButton pattern2SelectButton;
//
//  Scale scale;
//  Array<int, MAX_CHORD_SIZE> chord;
//
//  void setup()
//  {
//    Serial.begin(9600);
//
//    pinMode(TEMPO_PIN, OUTPUT);
//    pinMode(OCTAVE_PIN, OUTPUT);
//    pinMode(CHORD_INTERVALS_PIN, OUTPUT);
//    pinMode(SUSTAIN_PIN, OUTPUT);
//
//    MIDI.begin(MIDI_CHANNEL_OFF);
//
//    octaveSelectButton.init(0, 5, 2);
//    chordIntervalsSelectButton.init(0, Scale::CHORD_INTERVALS.getLastIdx());
//    sustainSelectButton.init(0, 1); // Off, On
//
//    pattern1SelectButton.init(0, MAX_PRESET_NUM);
//    pattern2SelectButton.init(0, MAX_PRESET_NUM);
//
//    melodyPattern1.setChildPattern(&melodyPattern2);
//    melodyPattern1.applyPreset(0);
//    melodyPattern1.reset();
//    melodyPattern2.applyPreset(0);
//    melodyPattern2.reset();
//
//    mutePattern.init(16,  Pattern::BIN_PATTERN_2, 1, Pattern::DIRECTIONS_UP);
//
//    tapTempo.init(100, TapTempo::QUARTER_NOTE, TapTempo::QUARTER_NOTE);
//
//    scale.init(Scale::C_0, Scale::INTERVALS_MAJOR_SIZE,  Scale::INTERVALS_MAJOR);
//  }
//
//  void loop()
//  {
//    int nowMs = millis();
//
//    tapTempo.readPin(digitalRead(TEMPO_PIN), nowMs);
//    octaveSelectButton.readPin(digitalRead(OCTAVE_PIN));
//    chordIntervalsSelectButton.readPin(digitalRead(CHORD_INTERVALS_PIN));
//    sustainSelectButton.readPin(digitalRead(SUSTAIN_PIN));
//
//    pattern1SelectButton.readPin(digitalRead(PATTERN_1_PRESET_PIN));
//    pattern2SelectButton.readPin(digitalRead(PATTERN_2_PRESET_PIN));
//
//    if(pattern1SelectButton.getJustChanged()) {
//      Serial << "*** applyPreset 1" << endl;
//      melodyPattern1.applyPreset(pattern1SelectButton.getSelectedOption());
//    }
//
//    if(pattern2SelectButton.getJustChanged()) {
//      Serial << "*** applyPreset 2" << endl;
//      melodyPattern2.applyPreset(pattern2SelectButton.getSelectedOption());
//    }
//
//
//    if(tapTempo.isBeat(nowMs)) {
//      if(sustainSelectButton.getSelectedOption() == 0) {
//        for(int i = 0; i < chord.getSize(); i++) {
//          MIDI.sendNoteOff(chord.at(i, 0), 127, 1);
//        }
//      }
//
//
//
//      if(mutePattern.getCurrOffsetSum() == 1) {
//        int octaveOffset = (octaveSelectButton.getSelectedOption() * 12);
//        int melodyOffset = melodyPattern1.getCurrOffsetSum();
//        chord = scale.getChord(
//          octaveOffset + melodyOffset,
//          chordIntervalsSelectButton.getSelectedOption()
//        );
//
//        for(int i = 0; i < chord.getSize(); i++) {
//          if(i > 127 || i < 0) { continue; }
//          MIDI.sendNoteOn(chord.at(i, 0), 127, 1);
//        }
//      }
//
//
//      #ifdef DEBUG_MAIN
////        Serial << "**********************" << endl;
////        Serial << "note: " << note << endl;
////        Serial << "melodyOffset: " << melodyOffset << endl;
////        Serial << "octave: " << octaveSelectButton.getSelectedOption() << endl;
////        Serial << "octaveOffset: " << octaveOffset << endl;
////        Serial << "chordInterval Mode: " << chordIntervalsSelectButton.getSelectedOption() << endl;
////          Serial << "pattern1SelectButton: " <<  pattern1SelectButton.getSelectedOption() << endl;
//      #endif
//
//      //
//      // For next iteration
//      //
//
//      melodyPattern1.takeStep();
//      mutePattern.takeStep();
//    }
//  }
//
//#endif // RUN_TESTS
