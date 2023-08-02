#include "TouchScreen.h"
#include <SoftwareSerial.h>

/*
    *
    *   Config
    * 
    *   btnAmount       ->  Amount of btns
    *   btns            ->  BtnIds (not more than btnAmount)
    *   debugSerialBR   ->  the baudRate of the debug Serial
    *   serialBaudRate  ->  the baudRate of the standard Serial
    *   maxWaitTime     ->  Maximum Wait Time for Btn answer (millis)
    *   timeoutTime     ->  Time until next check (millis)
    * 
    * 
*/
const int btnAmount = 3;
char btns[btnAmount] = {'A','B','C'};
int debugSerialBR = 9600;
int serialBaudRate = 9600;
int maxWaitTime = 3000;
int timeoutTime = 500;
int distanceTime = 100;

// CONFIG END

int btnChecking = 0;
bool waitingAnswer = false;
unsigned long waitMillis = 0;
unsigned long timeoutMillis = 0;
unsigned long distanceMillis = 0;
SoftwareSerial softSerial(10,11);
String curStatus = "notSetYet";
String tempStatus = "notSetYet";

void setup() {

    pinMode(10, INPUT);
    pinMode(11, OUTPUT);
    Serial.begin(debugSerialBR);
    softSerial.begin(serialBaudRate);
}

void clearSerial() {
    while (softSerial.available() > 0) {
        softSerial.read();
    }
    return;
}

void loop() {
    if (waitingAnswer == true && softSerial.available()) {
        char answer = softSerial.read();

        if (answer >= 97 && answer <= 122) {
            tempStatus = tempStatus + String(btns[btnChecking-1]) + String(answer) + "$";
        } else {
            tempStatus = tempStatus + String(btns[btnChecking-1]) + "n$";
            Serial.println("ID: " + String(btns[btnChecking-1]) + " FAULTY RESPONSE; SKIPPING");
        }

        waitingAnswer = false;
        waitMillis = 0;
        distanceMillis = millis();
        btnChecking = btnChecking + 1;
    }
    
    if (waitingAnswer == true && millis() - waitMillis >= maxWaitTime && waitMillis > 0) {
        tempStatus = tempStatus + String(btns[btnChecking-1]) + "n$";
        Serial.println("ID: " + String(btns[btnChecking-1]) + " NO RESPONSE; SKIPPING");
        waitingAnswer = false;
        waitMillis = 0;
        distanceMillis = millis();
        btnChecking = btnChecking + 1;
    }

    if (btnChecking > btnAmount) {
        btnChecking = 0;
        curStatus = tempStatus.substring(0,tempStatus.length()-1);
        Serial.println("Current Status: " + curStatus);
        tempStatus = "";
        timeoutMillis = millis();
    }

    if (btnChecking == 0 && millis() - timeoutMillis >= timeoutTime) {
        btnChecking = 1;
    } else if (btnChecking == 0 && millis() - timeoutMillis < timeoutTime && softSerial.available() > 5) {
        clearSerial();
        Serial.println("Serial cleared due to overload");
    }
    if (btnChecking > 0 && waitingAnswer == false && millis() - distanceMillis >= distanceTime) {
        softSerial.write(btns[btnChecking-1]);
        softSerial.write('a');

        waitingAnswer = true;
        waitMillis = millis();
        distanceMillis = 0;
    }
}