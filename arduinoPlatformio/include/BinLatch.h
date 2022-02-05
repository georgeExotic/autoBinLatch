/*
  BinLatch.h - Library for colabLab 
  Created by Jorge Roa, Feb 02 2022.
  Released into the public domain.
*/

#include <Arduino.h>
#include <Servo.h>
#ifndef BinLatch_h
#define BinLatch_h

class BinLatch
{
public:
    BinLatch(byte servoPin, byte switchPin);
    void lockLatch();
    void releaseLatch();
    boolean getBinStatus();
private:
    byte _servoPin;
    byte _switchPin;
    boolean _binStatus;
    Servo _myservo;
};

#endif