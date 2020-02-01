#include <OutputControl.h>

OutputControl::OutputControl(int pin, bool startLow , bool isReverePolarity ){
    _myPin.pin = pin;
    _myPin.isRevPolarity = isReverePolarity;
    _myPin.isHigh = false;

    if (startLow){
        if (isReverePolarity) digitalWrite(pin , HIGH);
        else digitalWrite(pin , LOW);
    
    }else{
        if (isReverePolarity) digitalWrite(pin , LOW);
        else digitalWrite(pin , HIGH);
    }
    pinMode(pin, OUTPUT);
}


void OutputControl::switchState(){
    Serial.print(F("[OutputControl] Switching State ..."));

    if (_myPin.isHigh){ //--> switch to LOW
        Serial.println(F("to LOW"));        
        if (_myPin.isRevPolarity) digitalWrite(_myPin.pin, HIGH);
        else digitalWrite(_myPin.pin, LOW);

        _myPin.isHigh = false;

    } else {  //--> switch to HIGH
        Serial.println(F("to HIGH"));
        if (_myPin.isRevPolarity) digitalWrite(_myPin.pin, LOW);
        else digitalWrite(_myPin.pin, HIGH);

        _myPin.isHigh = true;
    }
}


bool OutputControl::turnHigh(unsigned long delayToLow){
    if (_myPin.isHigh) return false;
    Serial.println(F("[OutputControl] Turning HIGH"));
    if (_myPin.isRevPolarity) digitalWrite(_myPin.pin,LOW);
    else digitalWrite(_myPin.pin,HIGH);

    _myPin.isHigh = true;

    if (delayToLow > 0){
        _delayToSwitch = delayToLow;
        _lastSwitchingTime = millis();
    }

    return true;
}


bool OutputControl::turnLow(unsigned long delayToHigh){
    if (!_myPin.isHigh) return false;
    Serial.println(F("[OutputControl] Turning LOW"));
    if (_myPin.isRevPolarity) digitalWrite(_myPin.pin,HIGH);
    else digitalWrite(_myPin.pin,LOW);

    _myPin.isHigh = false;

    if (delayToHigh > 0){
        _delayToSwitch = delayToHigh;
        _lastSwitchingTime = millis();
    }

    return true;
}


bool OutputControl::poll() {
    if (_delayToSwitch == 0) return false;
    if ( millis() - _lastSwitchingTime >= _delayToSwitch ){
        Serial.println(F("[OutputControl] Polled!!"));
        switchState();
        _delayToSwitch = 0;
    } 
    return true;
}

bool OutputControl::isHigh(){
    return _myPin.isHigh;
}