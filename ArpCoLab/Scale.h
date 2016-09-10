#ifndef SCALE_HPP
#define SCALE_HPP

#include "Array.h"

#define MAX_CHORD_SIZE 5
#define MAX_SCALE_SIZE 12

class Scale {
  public:
    Scale();

    static const int C_0;
    static const int Db_0;
    static const int D_0;
    static const int Eb_0;
    static const int E_0;
    static const int F_0;
    static const int Gb_0;
    static const int G_0;
    static const int Ab_0;
    static const int A_0;
    static const int Bb_0;
    static const int B_0;

    static const int INTERVALS_MAJOR_SIZE;
    static const int INTERVALS_MAJOR[];

    static const int INTERVALS_MINOR_SIZE;
    static const int INTERVALS_MINOR[];

    static const int INTERVALS_MINOR_P_SIZE;
    static const int INTERVALS_MINOR_P[];
    
    void                       init(int _tonic, const int _numIntervals,  const int _intervals[]);
    Array<int, MAX_CHORD_SIZE> getChord(int _offset);
    int                        getNote(int _offset);
      
  private:

    Array<int, MAX_SCALE_SIZE> tonicOffsets;
    int            tonic;
    
    void setTonicOffsets(const int _numIntervals,  const int _intervals[]);
};

#endif
