#ifndef INT_ARRAY_IMPLEMENTATION_H
#define INT_ARRAY_IMPLEMENTATION_H

// #define DEBUG_INT_ARRAY;

#ifdef DEBUG_INT_ARRAY
  #include <Streaming.h>
#endif

template <size_t MAX_SIZE>   
IntArray<MAX_SIZE>::IntArray(int _startRange, int _endRange) {
  // clear(); called in range method
  range(_startRange, _endRange);
}

template <size_t MAX_SIZE>
void IntArray<MAX_SIZE>::range(int _startRange, int _endRange) {
  clear();
  
  if(_endRange < _startRange) {
    return;
  }
  
  for(int i = _startRange; i <= _endRange; i++) {
    
    #ifdef DEBUG_INT_ARRAY
      Serial << "IntArray #range - pushing:" << i << endl;
    #endif
    
    push(i);
  }
}

#endif
