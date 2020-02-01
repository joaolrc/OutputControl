#include <Arduino.h>
#include <OutputControl.h>

#define RELAYPIN D2  
#define RELAY_ACTIVATIONINTERVAL 10000


unsigned long lastMeasurementTime = 0;
unsigned long lastRelayActivation = 0;
unsigned long relayActivationInterval = 10000;
unsigned long on_Counter = 0;


OutputControl myRelay(RELAYPIN,false,true);



void setup(){
    Serial.begin(115200);
    Serial.println(F("Starting OutputControl Example"));
    delay(2000);

    Serial.println("Turning HIGH");
    myRelay.turnHigh();
    delay(5000);

    Serial.println("Turning LOW");
    myRelay.turnLow();
    delay(5000);

    Serial.println("Switching State");
    myRelay.switchState();
    delay(5000);

    Serial.println("Switching State Again");
    myRelay.switchState();
    delay(5000);

}



void loop(){
    //call this every loop
    myRelay.poll();

    if (millis()- lastRelayActivation > RELAY_ACTIVATIONINTERVAL ){
        on_Counter++;
        Serial.printf("Turning Relay ON for the %lu time\n", on_Counter);
        lastRelayActivation = millis();
        myRelay.turnHigh(3000);
    }

}

