#include "Tests.h"
#include "Array.h"
#include "SelectButton.h"
#include "TapTempo.h"

#define KEY_PIN 24
#define TEMPO_PIN 22

//void setup() {
//  Serial.begin(9600);
//  Tests tests;
//  tests.runTests();
//}
//void loop() {
//}

TapTempo tapTempo;
SelectButton<int, 3> keySelectButton;

void setup()
{
  Serial.begin(9600);

  pinMode(KEY_PIN, OUTPUT);
  pinMode(TEMPO_PIN, OUTPUT);

  int keyValues[3] = {1, 2, 3};
  Array<int, 3> keys(keyValues);
  keySelectButton.init(keys, 2);

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
  }
}

