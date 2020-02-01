/* 
Simple library for controlling an Output without blocking the code execution.
Possibility to handle Reverse Polarity Pin (eg. to use with PNP transistor)


João Costa - São João da Azenha, 1 Feb 2020
*/

#ifndef OUTPUT_CONTROL_H
#define OUTPUT_CONTROL_H
#include <Arduino.h>
#include <functional>

typedef std::function<void(void)> GeneralVoidFunction;

typedef struct{
        int pin;
        int isRevPolarity;
        int isHigh;
    }GeneralPin_t;

class OutputControl
{
public:
    //constructor
    OutputControl (int pin, bool startLow = true, bool isReverePolarity = false);
    //switches current state of GPIO
    void switchState();
    //turns output HIGH. Possibility to pass a timeout to switch back to LOW
    bool turnHigh(unsigned long delayToLow = 0);
    //turns output LOW. Possibility to pass a timeout to switch back to HIGH
    bool turnLow(unsigned long delayToHigh = 0);

    //to call on each loop
    bool poll();

    bool isHigh();

    


private:
    GeneralPin_t _myPin;

    unsigned long _delayToSwitch = 0;

    unsigned long _lastSwitchingTime = 0;





    

};




#endif

