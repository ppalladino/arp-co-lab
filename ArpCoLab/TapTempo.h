#ifndef TAP_TEMPO_HPP
#define TAP_TEMPO_HPP

#include <Arduino.h>

class TapTempo {
  private:

    int firstTapMs;             // Timestamp of first tap
    int prevPinValue;           // Last value of tap tempo pin
    int tapDurationMs;          // Time between last first tap and second tap

    int tapSubDivision;         // What sub-division a tap duration represents (quarter note, half note, etc.)
    int beatSubDivision;        // What sub-divisions should a beat fall on (quarter note, half note, etc.)

    int lastBeatMs;             // Timestamp of last beat

    int measureDurationMs;      // Calculated value for duration of a measure
    int beatDurationMs;         // Calculated value for duration of a beat
    
    void calculateDurations();  // When a sub-division or duration changes calculate expensive duration values
    
  public:

    static const int THIRTY_SECOND_NOTE;
    static const int SIXTEENTH_NOTE;
    static const int QUARTER_NOTE;
    static const int HALF_NOTE;
    static const int WHOLE_NOTE;
    static const int ABANDON_FIRST_TAP_MS;
    
    TapTempo();

    void init(int _tapDurationMs, const int _tapSubDivision, const int _beatSubDivision);
    int  getTapDurationMs();
    void readPin(int _value, int _nowMs);
    void tap(int _nowMs);
    bool isBeat(int _nowMs);
    void setTapSubDivision(const int _tapSubDivision);
    void setBeatSubDivision(const int _beatSubDivision);
    int  getBpm();
};

#endif
