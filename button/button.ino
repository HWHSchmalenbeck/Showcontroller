#include <SoftwareSerial.h>
/*
 *
 *   Config
 *
 *   btnId                  -> Id of the Button
 *   btnPin                 -> digitalPin connected to the button
 *
 *   guestMode              -> disable everything except button press
 *   nornenButton           -> enable nornenButton handling
 *
 *   ledPinR                -> digitalPin (PWR) connect to the red Anode of the LED
 *   ledPinG                -> digitalPin (PWR) connect to the green Anode of the LED
 *   ledPinB                -> digitalPin (PWR) connect to the blue Anode of the LED
 *
 *   debugSerialBR          -> baud rate of debug Serial
 *   serialBaudRate         -> baud rate of Serial
 *
 *   durBtnPress            -> duration to count normal button press (millis)
 *   durPartialCrisisPress  -> duration to count partial crisis button press (millis)
 *   durCrisisPress         -> duration to count crisis button press (millis)
 *   durCrisisStop          -> duration to stop pending crisis message (millis)
 *
 *   durPartyColor          -> duration of single color in party mode (millis)
 *   durBlinkColor          -> duration of single color in blink mode (millis)
 *
 */

char btnId = 'E';
unsigned char btnPin = 8;

bool guestMode = false;
bool nornenButton = true;

unsigned char ledPinR = 3;
unsigned char ledPinG = 5;
unsigned char ledPinB = 6;

unsigned short int debugSerialBR = 9600;
unsigned short int serialBaudRate = 9600;

unsigned short int durBtnPress = 100;
unsigned short int durPartialCrisisPress = 4000;
unsigned short int durCrisisPress = 6000;
unsigned short int durCrisisStop = 8000;

unsigned short int durPartyColor = 700;
unsigned short int durBlinkColor = 500;

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
 *   k   ->  (k)eine verbindung zum master [color = RED (blink 4)]
 *   p   ->  (p)artieller panik modus [color = BLUE (blink 6)]
 *
 */

SoftwareSerial comSerial(11, 10);

char curStatus = 'a';
unsigned char curBtnStatus = 0;

char blinkType = 0;
bool blinkState = false;
unsigned long blinkMillis = 0;

bool partyActive = false;
char partyState = 0;

unsigned long pressMillis = 0;

/*
 *
 *  disabledMode
 *
 *  0   ->  Nothing
 *  1   ->  Only cancel partial crisis
 *  2   ->  Full disable
 *
 */

unsigned char disabledMode = 0;

// Standby anim

short int fadevarr = 15;
short int fadevarg = 15;
short int fadevarb = 15;
char fadeamountr = 3;
char fadeamountg = -4;
char fadeamountb = 5;

unsigned long standbyMillis = 0;

const unsigned char RED[3] = {255, 0, 0};
const unsigned char ORANGE[3] = {255, 50, 0};
const unsigned char YELLOW[3] = {255, 255, 0};
const unsigned char GREEN[3] = {0, 255, 0};
const unsigned char CYAN[3] = {0, 255, 255};
const unsigned char BLUE[3] = {0, 0, 255};
const unsigned char PURPLE[3] = {128, 0, 128};
const unsigned char PINK[3] = {255, 20, 147};
const unsigned char WHITE[3] = {255, 255, 255};
const unsigned char BLACK[3] = {0, 0, 0};

void setup()
{

    pinMode(11, INPUT);
    pinMode(10, OUTPUT);
    Serial.begin(debugSerialBR);
    comSerial.begin(serialBaudRate);

    pinMode(btnPin, INPUT);
    pinMode(ledPinR, OUTPUT);
    pinMode(ledPinG, OUTPUT);
    pinMode(ledPinB, OUTPUT);

    if (digitalRead(btnPin) == HIGH)
    {
        curStatus = 'd';
        setBtnColor(ORANGE);
        blinkType = 2;

        // DEBUG
        Serial.println("Dauerhaft gedrueckt.");
    }
    else
    {
        curStatus = 'e';
        setBtnColor(YELLOW);
        blinkType = 3;

        // DEBUG
        Serial.println("Ewig nicht gedrueckt.");
    }

    if (nornenButton == true)
    {
        curBtnStatus = '1';
    }
}

// Set btn color

void setBtnColor(const unsigned char color[3])
{
    analogWrite(ledPinR, color[0]);
    analogWrite(ledPinG, color[1]);
    analogWrite(ledPinB, color[2]);
    return;
}

void handleStandby()
{
    fadevarr = fadevarr + fadeamountr;
    fadevarg = fadevarg + fadeamountg;
    fadevarb = fadevarb + fadeamountb;

    if (fadevarr < 10 || fadevarr > 245)
    {
        fadeamountr = -fadeamountr;
    }

    if (fadevarg <= 10 || fadevarg >= 245)
    {
        fadeamountg = -fadeamountg;
    }

    if (fadevarb <= 10 || fadevarb >= 245)
    {
        fadeamountb = -fadeamountb;
    }

    analogWrite(ledPinG, fadevarg);
    analogWrite(ledPinR, fadevarr);
    analogWrite(ledPinB, fadevarb);
    return;
}

void handlePartyMode()
{
    if (curStatus == 'c' || curStatus == 'd' || curStatus == 'e' || curStatus == 'p')
    {
        partyActive = false;
        partyState = 0;
        blinkMillis = 0;

        // DEBUG
        Serial.println("Canceling party due to status.");
        return;
    }

    // DEBUG
    Serial.println("Handling party.");

    switch (partyState)
    {
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

    if (partyState >= 8)
    {
        partyState = 0;
    }
    return;
}

void handleBlink()
{

    // DEBUG
    // Serial.println("Handle blink.");

    if (blinkState == false)
    {
        switch (blinkType)
        {
        case 1:
            setBtnColor(PINK);

            // DEBUG
            // Serial.println("Blinking Pink");
            break;
        case 2:
            setBtnColor(ORANGE);

            // DEBUG
            // Serial.println("Blinking Orange");
            break;
        case 3:
            setBtnColor(YELLOW);

            // DEBUG
            // Serial.println("Blinking Yellow");
            break;
        case 4:
            setBtnColor(RED);

            // DEBUG
            // Serial.println("Blinking Red");
            break;
        case 5:
            setBtnColor(GREEN);

            // DEBUG
            // Serial.println("Blinking Green");
            break;
        case 6:
            setBtnColor(BLUE);

            // DEBUG
            // Serial.println("Blinking Blue");
            break;
        }
        blinkState = true;
    }
    else
    {
        setBtnColor(BLACK);
        blinkState = false;

        // DEBUG
        // Serial.println("Blinking Black");
    }
    return;
}

void clearSerial()
{
    while (comSerial.available() > 0)
    {
        comSerial.read();
    }
    return;
}

void loop()
{
    if (Serial.available())
    {
        char readInst = Serial.read();

        if (readInst == 'p')
        {
            blinkMillis = millis();
            partyActive = true;
        }
        else if (readInst == 'a')
        {
            Serial.println(curStatus);
        }
        else if (readInst == 's')
        {
            partyActive = false;
            blinkType = 0;
            blinkState = false;
            blinkMillis = 0;
            curStatus = 'a';
            pressMillis = 0;
            curBtnStatus = 0;
            disabledMode = 0;
        }
    }

    // Handle blinking
    if (blinkType != 0 && millis() - blinkMillis >= durBlinkColor && partyActive == false)
    {

        // DEBUG
        // Serial.println("Running blink; Dur: " + String(millis() - blinkMillis));

        handleBlink();
        blinkMillis = millis();
    }

    // If party mode active
    if (partyActive == true && millis() - blinkMillis >= durPartyColor)
    {
        handlePartyMode();
        blinkMillis = millis();

        // DEBUG
        // Serial.println("Running party");
    }

    // Serial feedback
    if (comSerial.available())
    {
        delay(100);
        bool fault = false;
        char readid = comSerial.read();
        char readinst = comSerial.read();

        String readidtest = String(readid);
        readidtest.toLowerCase();

        // DEBUG
        Serial.println("Got id " + String(readid) + " with instruction " + String(readinst));

        if (readidtest == String(readid))
        {
            fault = true;
            clearSerial();
        }

        if ((readid == btnId || readid == 'Y') && fault == false)
        {

            // Status check

            if (readinst == 'a' && readid != 'Y')
            {
                comSerial.print(curStatus);

                // Other buttons pushed
            }
            else if (readinst == 'b')
            {
                if (curStatus != 'b')
                {
                    if (blinkType != 5)
                    {
                        // DEBUG
                        Serial.println("Blinking green due to other buttons pushed.");

                        blinkType = 5;
                        blinkMillis = 0;
                        partyActive = false;
                        curStatus = 'a';
                        setBtnColor(GREEN);
                    }
                    else
                    {
                        Serial.println("Disregarding blink green instruction because already blinking green");
                    }
                }
                else
                {
                    Serial.println("Disregarding blink green instruction because already pressed");
                }

                // Crisis mode
            }
            else if (readinst == 'c')
            {

                // DEBUG
                if (blinkType != 1)
                {
                    Serial.println("Enabling crisis due to Serial");

                    blinkType = 1;
                    blinkMillis = 0;
                    partyActive = false;
                    setBtnColor(PINK);
                    disabledMode = 2;
                }
                else
                {
                    Serial.println("Disregarding blink pink instructions because already blinking pink");
                }
            }
            else if (readinst == 'd') // Partial crisis mode
            {
                if (curStatus != 'p')
                {
                    if (blinkType != 6)
                    {
                        Serial.println("Blinking blue due to partial crisis mode of other buttons");

                        blinkType = 6;
                        blinkMillis = 0;
                        partyActive = false;
                        curStatus = 'a';
                        setBtnColor(BLUE);

                        disabledMode = 2;
                    }
                    else
                    {
                        Serial.println("Disregarding blink blue because button is already blinking blue");
                    }
                }
                else
                {
                    Serial.println("Disregarding blink blue because button initiated partial crisis");
                }
            }
            else if (readinst == 'r') // RESET
            {

                // DEBUG
                Serial.println("Resetting due to Serial");

                partyActive = false;
                blinkType = 3;
                blinkState = false;
                blinkMillis = 0;
                curStatus = 'e';
                setBtnColor(YELLOW);
                pressMillis = 0;
                curBtnStatus = 0;
                disabledMode = 0;

                // Soft Reset
            }
            else if (readinst == 's' && curStatus != 'e' && curStatus != 'd')
            {

                // DEBUG
                Serial.println("Soft Resetting due to Serial");

                partyActive = false;
                blinkType = 0;
                blinkState = false;
                blinkMillis = 0;
                curStatus = 'a';
                pressMillis = 0;
                curBtnStatus = 0;
                disabledMode = 0;

                // Party Mode
            }
            else if (readinst == 'p')
            {

                // DEBUG
                Serial.println("Enabling party due to Serial");

                partyActive = true;
                blinkMillis = millis();
            }
        }
        else if (readid == '?' && readinst == '_')
        {

            // Discovery send Stats

            // Send type Button

            comSerial.print("B");

            comSerial.print(btnId);

            partyActive = false;
            blinkType = 3;
            blinkState = false;
            blinkMillis = 0;
            curStatus = 'e';
            setBtnColor(YELLOW);
            pressMillis = 0;
            curBtnStatus = 0;
            disabledMode = 0;
        }
    }

    // If btn HIGH set start count millis
    if (disabledMode != 2)
    {
        if (digitalRead(btnPin) == HIGH && pressMillis == 0 && curStatus != 'd' && curStatus != 'e')
        {

            // DEBUG
            Serial.println("Button HIGH non e");

            pressMillis = millis();

            curBtnStatus = 0;
        }
        else if (digitalRead(btnPin) == HIGH && pressMillis > 0 && curStatus != 'd' && curStatus != 'e')
        {
            if (disabledMode == 0)
            {
                if (millis() - pressMillis >= durCrisisStop && curBtnStatus <= 3 && guestMode == false)
                {

                    curBtnStatus = 4;

                    // DEBUG
                    Serial.println("Crisis stop button press color");

                    setBtnColor(RED);
                }
                else if (millis() - pressMillis >= durCrisisPress && curBtnStatus <= 2 && guestMode == false)
                {

                    curBtnStatus = 3;
                    // DEBUG
                    Serial.println("Crisis button press color");

                    setBtnColor(PINK);
                }
                else if (millis() - pressMillis >= durPartialCrisisPress && curBtnStatus <= 1 && guestMode == false)
                {
                    curBtnStatus = 2;
                    // DEBUG
                    Serial.println("Partial Crisis button press color");

                    setBtnColor(BLUE);
                }
                else if (millis() - pressMillis >= durBtnPress && curBtnStatus == 0)
                {

                    curBtnStatus = 1;
                    // DEBUG
                    Serial.println("Normal button press color");

                    setBtnColor(GREEN);
                }
            }
            else if (disabledMode == 1)
            {
                if (millis() - pressMillis >= durPartialCrisisPress && curBtnStatus == 0)
                {

                    curBtnStatus = 1;
                    // DEBUG
                    Serial.println("Partial Crisis cancel button press color");

                    setBtnColor(RED);
                }
            }

            // If btn LOW and millis set, set status
        }
        else if (digitalRead(btnPin) == LOW && pressMillis > 0 && curStatus != 'd' && curStatus != 'e')
        {
            int dur = millis() - pressMillis;

            // DEBUG
            Serial.println("Button LOW; Dur: " + String(dur));
            if (disabledMode == 0)
            {
                if (dur >= durCrisisStop && curBtnStatus == 4 && guestMode == false)
                {

                    // DEBUG
                    Serial.println("Running crisis stop due to btnpress");

                    curStatus = 'a';
                    blinkType = 0;
                    partyActive = false;
                    setBtnColor(RED);
                }
                else if (dur >= durCrisisPress && curBtnStatus == 3 && guestMode == false)
                {

                    // DEBUG
                    Serial.println("Running crisis due to btnpress");

                    curStatus = 'c';
                    blinkType = 1;
                    partyActive = false;
                    disabledMode = 2;
                }
                else if (dur >= durPartialCrisisPress && curBtnStatus == 2 && guestMode == false)
                {

                    // DEBUG
                    Serial.println("Running partial crisis due to btnpress");

                    curStatus = 'p';
                    blinkType = 0;
                    partyActive = false;
                    setBtnColor(BLUE);
                    disabledMode = 1;
                }
                else if (dur >= durBtnPress && curBtnStatus == 1)
                {
                    if (nornenButton == false)
                    {

                        // DEBUG
                        Serial.println("Running normal button press due to btnpress");

                        curStatus = 'b';
                        blinkType = 0;
                        partyActive = false;
                        setBtnColor(GREEN);
                    }
                    else
                    {

                        if (curStatus >= '1' && curStatus <= '5')
                        {
                            curStatus += 1;

                            if (curStatus > '5')
                            {
                                curStatus = '1';
                            }
                        }
                        else
                        {
                            curStatus = '2';
                        }
                        // DEBUG
                        Serial.println("Running nornen button press status: ");
                        Serial.println(curStatus);

                        partyActive = false;

                        if (curStatus >= '2' && curStatus <= '4')
                        {
                            blinkType = 5;
                            setBtnColor(GREEN);
                        }
                        else if (curStatus == '1')
                        {
                            setBtnColor(RED);
                        }
                        else if (curStatus == '5')
                        {
                            blinkType = 0;
                            setBtnColor(GREEN);
                        }
                    }
                }
            }
            else if (disabledMode == 1)
            {
                if (dur >= durPartialCrisisPress && curBtnStatus == 1)
                {

                    // DEBUG
                    Serial.println("Running partial crisis cancel button press due to btnpress");

                    curStatus = 'a';
                    blinkType = 0;
                    partyActive = false;
                    disabledMode = 0;
                    setBtnColor(RED);
                }
            }

            curBtnStatus = 0;

            pressMillis = 0;

            // If btn HIGH and status 'e' then set status 'a'
        }
        else if (digitalRead(btnPin) == HIGH && curStatus == 'e')
        {

            // DEBUG
            Serial.println("Running first time btnpress with e");

            curStatus = 'a';
            blinkType = 0;
            pressMillis = 0;
            setBtnColor((guestMode == false ? RED : BLACK));
            delay(500);
        }
    }

    // Handle Standby
    if ((curStatus == 'a' || curStatus == '1') && blinkType == 0 && partyActive == false && millis() - standbyMillis >= 200 && digitalRead(btnPin) == LOW && pressMillis == 0)
    {
        if (guestMode == false)
        {
            handleStandby();
            standbyMillis = millis();
        }
        else
        {
            setBtnColor(BLACK);
        }
    }
}