#include <Arduino.h>
#include "..\Array.h"
#include <Streaming.h>
#include <assert.h>

const int BAUDRATE = 9600;
const int ELEMENT_COUNT = 5;
const int RESIZE_ELEMENT_COUNT = 3; // Must be less than original size

void printArray(Array<int, ELEMENT_COUNT> array)
{
  Serial << "[";
  for (int i=0; i < ELEMENT_COUNT; i++)
  {
    if (i != 0)
    {
      Serial << ",";
    }
    Serial << array[i];
  }
  Serial << "]" << endl;
}

void test(bool condition, char message[], int line) 
{
  if(condition == true) 
  {
    return;
  }
  
  Serial << "ERROR!! Test failed: " << message << "\n";
  Serial << " on line " << line  << "\n";
  Serial << " in file " << __FILE__ << "\n"; 
  assert(false);
}

void setup()
{
  Serial.begin(BAUDRATE);
  delay(1000);

  Serial << "#Array(int [])" << endl;
  const int intArray[ELEMENT_COUNT] = {15,14,13,12,11};
  Serial << "intArray:" << endl;
  Array<int, ELEMENT_COUNT> intArrayConstructor(intArray);
  Serial << "intArrayConstructor:" << endl;
  printArray(intArrayConstructor);
    Serial << "ELEMENT_COUNT = " << ELEMENT_COUNT << endl;
  Serial << "size is: " << intArrayConstructor.getSize() << endl;
  test(
    (intArrayConstructor.getSize() == 5), 
    "Constructor passed int[] with 5 elements", 
    __LINE__
  );


  Serial << "#push" << endl;
  Array<int, ELEMENT_COUNT> pushArray;
  pushArray.push(4);
  test(
    (pushArray.getSize() == 1), 
    "Pushed 1 element", 
    __LINE__
  );
  pushArray.push(3);
  pushArray.push(2);
  pushArray.push(1);
  pushArray.push(0);
  printArray(pushArray);
  test(
    (pushArray.getSize() == 5), 
    "Pushed 5 elements", 
    __LINE__
  );

  Serial << "#Array(size)" << endl;
  Array<int, ELEMENT_COUNT> arraySized(0);
  printArray(arraySized);
  Serial << "size is: " << arraySized.getSize() << endl;
  test(
    (arraySized.getSize() == 5), 
    "Array initialized with 5 elements", 
    __LINE__
  );
   test(
    (arraySized.at(0) == 0), 
    "Array initialized all values = 0", 
    __LINE__
  );

  Serial << "* Initialize an array" << endl;
  Array<int, ELEMENT_COUNT> arrayInitialized(0);
  Serial << "arrayInitialized:" << endl;
  printArray(arrayInitialized);

  Serial << "#fill" << endl;
  Serial << "size before fill: " << arrayInitialized.getSize() << endl;
  arrayInitialized.fill(37);
  Serial << "arrayInitialized.fill(37):" << endl;
  printArray(arrayInitialized);
  Serial << "size after fill: " << arrayInitialized.getSize() << endl;
  test(
    (arrayInitialized.getSize() == 5), 
    "arrayInitialized.getSize() == 5", 
    __LINE__
  );
  test(
    (arrayInitialized.at(3) == 37), 
    "filled with 37's", 
    __LINE__
  );

  Serial << "#assign" << endl;
  const int resizedArray2[3] = {0, 1, 2};
  arrayInitialized.assign(3, resizedArray2);
  printArray(arrayInitialized);
  test(
    (arrayInitialized.getSize() == 3), 
    "arrayInitialized.getSize() == 3", 
    __LINE__
  );

  Serial << "#fill" << endl;
  arrayInitialized.fill(37);
  Serial << "arrayInitialized.fill(37):" << endl;
  printArray(arrayInitialized);
  test(
    (arrayInitialized.getSize() == 5), 
    "arrayInitialized.getSize() == 5", 
    __LINE__
  );
  test(
    (arrayInitialized.at(3) == 37), 
    "filled with 37's", 
    __LINE__
  );

  Serial << "#idxOf" << endl;
  Serial << "ELEMENT_COUNT = " << ELEMENT_COUNT << endl;
  const int getIdxElements[ELEMENT_COUNT] = {1, 2, 3, 4, 5};
  Array<int, ELEMENT_COUNT> getIdxArray(getIdxElements);
  printArray(getIdxArray);
  test(
    (getIdxArray.getIdx(2) == 1), 
    "getIdxArray.getIdx(2) == 1", 
    __LINE__
  );
}

void loop() 
{
}
