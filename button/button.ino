#include <SoftwareSerial.h>
/*
    *
    *   Config
    *   
    *   btnId           -> Id of the Button
    *   btnPin          -> digitalPin connected to the button
    *   ledPinR         -> digitalPin (PWR) connect to the red Anode of the LED
    *   ledPinG         -> digitalPin (PWR) connect to the green Anode of the LED
    *   ledPinB         -> digitalPin (PWR) connect to the blue Anode of the LED
    *   debugSerialBR   -> baud rate of debug Serial
    *   serialBaudRate  -> baud rate of Serial
    *   durBtnPress     -> duration to count normal button press (millis)
    *   durCrisisPress  -> duration to count crisis button press (millis)
    *   durCrisisStop   -> duration to stop pending crisis message (millis)
    *   durPartyColor   -> duration of single color in party mode (millis)
    *   durBlinkColor   -> duration of single color in blink mode (millis)
    * 
*/

char btnId = 'D';
int btnPin = 8;

int ledPinR = 3;
int ledPinG = 5;
int ledPinB = 6;

int debugSerialBR = 9600;
int serialBaudRate = 9600;
int durBtnPress = 500;
int durCrisisPress = 5000;
int durCrisisStop = 7000;
int durPartyColor = 700;
int durBlinkColor = 500;

// Config end

/*
    *
    *   Status
    * 
    *   a   ->  (a)lles okay [color = RED]
    *   b   ->  (b)utton gedrückt [color = GREEN]
    *   c   ->  (c)risis [color = PINK (blink 1)]
    *   d   ->  (d)auerhaft gedrückt (falls bei Start HIGH) [color = ORANGE (blink 2)]
    *   e   ->  (e)wig nicht gedrückt (sobald gestartet und noch net gedrückt) [color = YELLOW (blink 3)]
    * 
*/

SoftwareSerial comSerial(11,10);

char curStatus = 'a';
int curBtnStatus = 0;

int blinkType = 0;
bool blinkState = false;
unsigned long blinkMillis = 0;

bool partyActive = false;
int partyState = 0;
unsigned long partyMillis = 0;

unsigned long pressMillis = 0;

// Standby anim

int fadevarr = 15;
int fadevarg = 15;
int fadevarb = 15;
int fadeamountr = 3;
int fadeamountg = 4;
int fadeamountb = 5;

unsigned long standbyMillis = 0;

const int RED[3] = {255,0,0};
const int ORANGE[3] = {255,50,0};
const int YELLOW[3] = {255,255,0};
const int GREEN[3] = {0,255,0};
const int CYAN[3] = {0,255,255};
const int BLUE[3] = {0,0,255};
const int PURPLE[3] = {128,0,128};
const int PINK[3] = {255,20,147};
const int WHITE[3] = {255,255,255};
const int BLACK[3] = {0,0,0};

void setup() {

    pinMode(11, INPUT);
    pinMode(10, OUTPUT);
    Serial.begin(debugSerialBR);
    comSerial.begin(serialBaudRate);

    pinMode(btnPin, INPUT);
    pinMode(ledPinR, OUTPUT);
    pinMode(ledPinG, OUTPUT);
    pinMode(ledPinB, OUTPUT);

    if (digitalRead(btnPin) == HIGH) {
        curStatus = 'd';
        setBtnColor(ORANGE);
        blinkType = 2;

        // DEBUG
        Serial.println("Dauerhaft gedrueckt.");
    } else {
        curStatus = 'e';
        setBtnColor(YELLOW);
        blinkType = 3;

        // DEBUG
        Serial.println("Ewig nicht gedrueckt.");
    }
}

// Set btn color

void setBtnColor(const int color[3]) {
    analogWrite(ledPinR, color[0]);
    analogWrite(ledPinG, color[1]);
    analogWrite(ledPinB, color[2]);
    return;
}

void handleStandby() {
    fadevarr = fadevarr + fadeamountr;
      fadevarg = fadevarg + fadeamountg;
      fadevarb = fadevarb + fadeamountb;

      if (fadevarr < 10 || fadevarr > 145) {
        fadeamountr = -fadeamountr;
      }

      if (fadevarg <= 10 || fadevarg >= 145) {
        fadeamountg = -fadeamountg;
      }

      if (fadevarb <= 10 || fadevarb >= 145) {
        fadeamountb = -fadeamountb;
      }

      analogWrite(ledPinG, fadevarg);
      analogWrite(ledPinR, fadevarr);
      analogWrite(ledPinB, fadevarb);
      return;
}

void handlePartyMode() {
    if (curStatus == 'c' || curStatus == 'd' || curStatus == 'e') {
        partyActive = false;
        partyState = 0;
        partyMillis = 0;
        
        // DEBUG
        Serial.println("Canceling party due to status.");
        return;
    }

    // DEBUG
    Serial.println("Handling party.");

    switch (partyState) {
        case 0:
            setBtnColor(RED);
            break;
        case 1:
            setBtnColor(ORANGE);
            break;
        case 2:
            setBtnColor(YELLOW);
            break;
        case 3:
            setBtnColor(GREEN);
            break;
        case 4:
            setBtnColor(CYAN);
            break;
        case 5:
            setBtnColor(BLUE);
            break;
        case 6:
            setBtnColor(PURPLE);
            break;
        case 7:
            setBtnColor(PINK);
            break;
    }

    partyState = partyState + 1;

    if (partyState >= 8) {
        partyState = 0;
    }
    return;
}

void handleBlink() {

    // DEBUG
    //Serial.println("Handle blink.");

    if (blinkState == false) {
        switch (blinkType) {
            case 1:
                setBtnColor(PINK);

                // DEBUG
                //Serial.println("Blinking Pink");
                break;
            case 2:
                setBtnColor(ORANGE);

                // DEBUG
                //Serial.println("Blinking Orange");
                break;
            case 3:
                setBtnColor(YELLOW);

                // DEBUG
                //Serial.println("Blinking Yellow");
                break;
            case 4:
                setBtnColor(RED);

                // DEBUG
                //Serial.println("Blinking Red");
                break;
            case 5:
                setBtnColor(GREEN);

                // DEBUG
                //Serial.println("Blinking Green");
                break;
        }
        blinkState = true;
    } else {
        setBtnColor(BLACK);
        blinkState = false;

        // DEBUG
        //Serial.println("Blinking Black");
    }
    return;
}

void clearSerial() {
    while (comSerial.available() > 0) {
        comSerial.read();
    } 
    return;
}

void loop() {

    // Handle blinking
    if (blinkType != 0 && millis() - blinkMillis >= durBlinkColor && partyActive == false) {

        // DEBUG
        //Serial.println("Running blink; Dur: " + String(millis() - blinkMillis));

        handleBlink();
        blinkMillis = millis();
    }

    // If party mode active
    if (partyActive == true && millis() - partyMillis >= durPartyColor) {
        handlePartyMode();
        partyMillis = millis();

        // DEBUG
        //Serial.println("Running party");
    }

    // Serial feedback
    if (comSerial.available()) {
        delay(100);
        bool fault = false;
        char readid = comSerial.read();
        char readinst = comSerial.read();

        String readidtest = String(readid);
        readidtest.toLowerCase();

        // DEBUG
        Serial.println("Got id " + String(readid) + " with instruction " + String(readinst));

        if (readidtest == String(readid)) {
            fault = true;
            clearSerial();
        }

        if ((readid == btnId || readid == 'Y') && fault == false) {

            // Status check

            if (readinst == 'a' && readid != 'Y') {
                comSerial.print(curStatus);
            
            // Other buttons pushed

            } else if (readinst == 'b') {

                // DEBUG
                Serial.println("Blinking green due to other buttons pushed.");

                blinkType = 5;
                blinkMillis = 0;
                partyActive = false;
                setBtnColor(GREEN);

            // Crisis mode

            } else if (readinst == 'c') {

                // DEBUG
                Serial.println("Enabling crisis due to Serial");

                blinkType = 1;
                blinkMillis = 0;
                partyActive = false;
                setBtnColor(PINK);

            // RESET

            } else if (readinst == 'r') {

                // DEBUG
                Serial.println("Resetting due to Serial");

                partyActive = false;
                partyMillis = 0;
                blinkType = 3;
                blinkState = false;
                blinkMillis = 0;
                curStatus = 'e';
                setBtnColor(YELLOW);
                pressMillis = 0;
                curBtnStatus = 0;

            // Soft Reset

             } else if (readinst == 's') {

                // DEBUG
                Serial.println("Soft Resetting due to Serial");

                partyActive = false;
                partyMillis = 0;
                blinkType = 0;
                blinkState = false;
                blinkMillis = 0;
                curStatus = 'a';
                pressMillis = 0;
                curBtnStatus = 0;
            
            // Party Mode

            } else if (readinst == 'p') {

                // DEBUG
                Serial.println("Enabling party due to Serial");

                partyActive = true;
                partyMillis = millis();
            }
        } else if (readid == '?' && readinst == '_') {
            
            // Discovery send Stats

            // Send type Button

            comSerial.print("B");

            comSerial.print(btnId);
        }
    }

    // If btn HIGH set start count millis

    if (digitalRead(btnPin) == HIGH && pressMillis == 0 && curStatus != 'd' && curStatus != 'e') {
        
        // DEBUG
        Serial.println("Button HIGH non e");

        pressMillis = millis();

        curBtnStatus = 0;

    } else if (digitalRead(btnPin) == HIGH && pressMillis > 0 && curStatus != 'd' && curStatus != 'e') {
        if (millis() - pressMillis >= durCrisisStop && curBtnStatus <= 2) {

            curBtnStatus = 3;

            // DEBUG
            Serial.println("Crisis stop button press color");

            setBtnColor(RED);
        } else if (millis() - pressMillis >= durCrisisPress && curBtnStatus <= 1) {

            curBtnStatus = 2;
            // DEBUG
            Serial.println("Crisis button press color");

            setBtnColor(PINK);
        } else if (millis() - pressMillis >= durBtnPress && curBtnStatus == 0) {

            curBtnStatus = 1;
            // DEBUG
            Serial.println("Normal button press color");

            setBtnColor(GREEN);
        }
    
    // If btn LOW and millis set, set status

    } else if (digitalRead(btnPin) == LOW && pressMillis > 0 && curStatus != 'd' && curStatus != 'e') {
        int dur = millis() - pressMillis;

        // DEBUG
        Serial.println("Button LOW; Dur: " + String(dur));

        if (dur >= durCrisisStop && curBtnStatus == 3) {

            // DEBUG
            Serial.println("Running crisis stop due to btnpress");

            curStatus = 'a';
            blinkType = 0;
            setBtnColor(RED);
        } else if (dur >= durCrisisPress && curBtnStatus == 2) {

            // DEBUG
            Serial.println("Running crisis due to btnpress");

            curStatus = 'c';
            blinkType = 1;
            partyActive = false;
        } else if (dur >= durBtnPress && curBtnStatus == 1) {

            // DEBUG
            Serial.println("Running normal button press due to btnpress");

            curStatus = 'b';
        }

        curBtnStatus = 0;

        pressMillis = 0;

    // If btn HIGH and status 'e' then set status 'a'

    } else if (digitalRead(btnPin) == HIGH && curStatus == 'e') {

        // DEBUG
        Serial.println("Running first time btnpress with e");
        
        curStatus = 'a';
        blinkType = 0;
        pressMillis = 0;
        setBtnColor(RED);
        delay(500);
    }

    // Handle Standby
    if (curStatus == 'a' && blinkType == 0 && partyActive == false && millis() - standbyMillis >= 200 && digitalRead(btnPin) == LOW && pressMillis == 0) {
        handleStandby();
        standbyMillis = millis();
    }
}