#include <Arduino.h>
#include "BinLatch.h"


BinLatch::BinLatch(byte servoPin,byte switchPin){
    _servoPin = servoPin;
    _switchPin = switchPin;
    _binStatus = false;
    _myservo.attach(_servoPin);
    releaseLatch();
    pinMode(_switchPin, INPUT_PULLDOWN);
}

void BinLatch::lockLatch(){
    _myservo.write(180);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
}

void BinLatch::releaseLatch(){
    _myservo.write(45);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
}

boolean BinLatch::getBinStatus(){
    if (digitalRead(_switchPin)){
    _binStatus = true ;}
    else  {_binStatus = false;}
    return _binStatus;
}