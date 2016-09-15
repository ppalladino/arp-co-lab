#include "Scale.h"

// #define DEBUG_SCALE;

#ifdef DEBUG_SCALE
  #include <Streaming.h>
#endif

Scale::Scale() {}

  const int Scale::C_0  = 0;
  const int Scale::Db_0 = 1;
  const int Scale::D_0  = 2;
  const int Scale::Eb_0 = 3;
  const int Scale::E_0  = 4;
  const int Scale::F_0  = 5;
  const int Scale::Gb_0 = 6;
  const int Scale::G_0  = 7;
  const int Scale::Ab_0 = 8;
  const int Scale::A_0  = 9;
  const int Scale::Bb_0 = 10;
  const int Scale::B_0  = 11;

  const int Scale::CHORD_ROOT = 0;
  const int Scale::CHORD_ROOT_OCTAVE = 1;
  const int Scale::CHORD_ROOT_THIRD = 2;
  const int Scale::CHORD_ROOT_FIFTH = 3;
  const int Scale::CHORD_TRIAD = 4;
  const int Scale::CHORD_SEVENTH = 5;
  const IntArray<6> Scale::CHORD_INTERVALS(0, 5);

  const int Scale::INTERVALS_MAJOR_SIZE = 7;
  const int Scale::INTERVALS_MAJOR[] = {2,2,1,2,2,2,1};

  const int Scale::INTERVALS_MINOR_SIZE = 7;
  const int Scale::INTERVALS_MINOR[]  = {2,1,2,2,2,2,1};

  const int Scale::INTERVALS_MINOR_P_SIZE = 5;
  const int Scale::INTERVALS_MINOR_P[]  = {3,2,2,3,2};
    
void Scale::init(int _tonic, const int _numIntervals,  const int _intervals[]) {
  tonic = _tonic;
  setTonicOffsets(_numIntervals, _intervals);
}

void Scale::setTonicOffsets(const int _numIntervals,  const int _intervals[]) {
  tonicOffsets.assign(_numIntervals, 0);

  for(int i = 0; i < tonicOffsets.getSize(); i++) {
    int val = (i == 0) ? 0 : (tonicOffsets.at(i - 1, 0) + _intervals[i - 1]);

    #ifdef DEBUG_SCALE
      Serial << "Scale:tonicOffsets; i:" << i << "; val:" << val << endl;
    #endif
    tonicOffsets.set(i, val);
  }
}



Array<int, MAX_CHORD_SIZE> Scale::getChord(int _tonicOffset, const int _chordType) {
  Array<int, MAX_CHORD_SIZE> chord;
  // Every chord has a root note
  chord.push(getNote(_tonicOffset));
  switch(_chordType) {
    case Scale::CHORD_ROOT_OCTAVE:
      chord.push(getNote(_tonicOffset));
      chord.push(getNote(_tonicOffset + 1));
      break;
    case Scale::CHORD_ROOT_THIRD:
      chord.push(getNote(_tonicOffset + 2));
      break;
    case Scale::CHORD_ROOT_FIFTH:
      chord.push(getNote(_tonicOffset + 4));
      break;
    case Scale::CHORD_TRIAD:
      chord.push(getNote(_tonicOffset + 2));
      chord.push(getNote(_tonicOffset + 4));
      break;
    case Scale::CHORD_SEVENTH: 
      chord.push(getNote(_tonicOffset + 2));
      chord.push(getNote(_tonicOffset + 4));
      chord.push(getNote(_tonicOffset + 6));
      break;
  }
  return chord;
}

int Scale::getNote(int _tonicOffset) {  
  int numOffsets = tonicOffsets.getSize();

  // Protect divisor
  if(numOffsets == 0) {
    return 0;
  }
  
  int octave = _tonicOffset / numOffsets;
  int offsetIdx = _tonicOffset % numOffsets;
  int note;
  
  if(!tonicOffsets.hasIdx(offsetIdx)) {
    note = 0;
    #ifdef DEBUG_SCALE
      Serial << "Scale::getNote; Can't find offsetIdx: " << offsetIdx << " returning 0 instead." << endl;
    #endif
  } else {
    note = tonic + tonicOffsets.at(offsetIdx, 0) + (octave * 12);
  }
  
  #ifdef DEBUG_SCALE
    Serial << "Scale::getNote; _tonicOffset:" << _tonicOffset << "; numOffsets:" << numOffsets << "; octave:" << octave << "; offsetIdx:" << offsetIdx << "; note:" << note << endl;
  #endif

  return note;
}
