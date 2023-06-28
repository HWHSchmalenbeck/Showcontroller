/*
    *
    *   Config
    *   
    *   btnId           -> Id of the Button
    *   btnPin          -> digitalPin connected to the button
    *   ledPinR         -> digitalPin (PWR) connect to the red Anode of the LED
    *   ledPinG         -> digitalPin (PWR) connect to the green Anode of the LED
    *   ledPinB         -> digitalPin (PWR) connect to the blue Anode of the LED
    *   serialBaudRate  -> baud rate of Serial
    *   durBtnPress     -> duration to count normal button press (millis)
    *   durCrisisPress  -> duration to count crisis button press (millis)
    *   durPartyColor   -> duration of single color in party mode (millis)
    *   durBlinkColor   -> duration of single color in blink mode (millis)
    * 
*/

char btnId = 'A';
int btnPin = 5;

int ledPinR = 1;
int ledPinG = 2;
int ledPinB = 3;

int serialBaudRate = 9600;
int durBtnPress = 100;
int durCrisisPress = 5000;
int durPartyColor = 400;
int durBlinkColor = 400;

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

char curStatus = 'a';

int blinkType = 0;
bool blinkState = false;
int blinkMillis = 0;

bool partyActive = false;
int partyState = 0;
int partyMillis = 0;

int pressMillis = 0;

const int RED[3] = {255,0,0};
const int ORANGE[3] = {255,165,0};
const int YELLOW[3] = {255,255,0};
const int GREEN[3] = {0,255,0};
const int CYAN[3] = {0,255,255};
const int BLUE[3] = {0,0,255};
const int PURPLE[3] = {128,0,128};
const int PINK[3] = {255,20,147};
const int WHITE[3] = {255,255,255};
const int BLACK[3] = {0,0,0};

void setup() {
    Serial.begin(serialBaudRate);

    pinMode(btnPin, INPUT);
    pinMode(ledPinR, OUTPUT);
    pinMode(ledPinG, OUTPUT);
    pinMode(ledPinB, OUTPUT);

    if (digitalRead(btnPin) == HIGH) {
        curStatus = 'd';
        setBtnColor(ORANGE);
        blinkType = 2;
    } else {
        curStatus = 'e';
        setBtnColor(YELLOW);
        blinkType = 3;
    }
}

// Set btn color

void setBtnColor(const int color[3]) {
    analogWrite(ledPinR, color[0]);
    analogWrite(ledPinG, color[1]);
    analogWrite(ledPinB, color[2]);
    return;
}

void handlePartyMode() {
    if (curStatus == 'c' || curStatus == 'd' || curStatus == 'e') {
        partyActive = false;
        partyState = 0;
        partyMillis = 0;
        return;
    }

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
    if (blinkState == false) {
        switch (blinkType) {
            case 1:
                setBtnColor(PINK);
                break;
            case 2:
                setBtnColor(ORANGE);
                break;
            case 3:
                setBtnColor(YELLOW);
                break;
        }
        blinkState = true;
    } else {
        setBtnColor(BLACK);
        blinkState = false;
    }
    return;
}

void loop() {

    // Handle blinking
    if (blinkType != 0 && millis() - blinkMillis >= durBlinkColor && partyActive == false) {
        handleBlink();
        blinkMillis = millis();
    }

    // If party mode active
    if (partyActive == true && millis() - partyMillis >= durPartyColor) {
        handlePartyMode();
        partyMillis = millis();
    }

    // Serial feedback
    if (Serial.available()) {
        char readid = Serial.read();
        char readinst = Serial.read();

        if (readid == btnId || readid == 'Y') {

            // Status check

            if (readinst == 'a' && readid != 'Y') {
                Serial.print(curStatus);

            // Crisis mode

            } else if (readinst == 'c') {
                blinkType = 1;
                blinkMillis = 0;
                partyActive = false;
                setBtnColor(PINK);

            // RESET

            } else if (readinst == 'r') {
                partyActive = false;
                partyMillis = 0;
                blinkType = 3;
                blinkState = false;
                blinkMillis = 0;
                curStatus = 'e';
                setBtnColor(YELLOW);
                pressMillis = 0;
            
            // Party Mode

            } else if (readinst == 'p') {
                partyActive = true;
                partyMillis = millis();
            }
        }
    }

    // If btn HIGH set start count millis

    if (digitalRead(btnPin) == HIGH && pressMillis == 0 && curStatus != 'd' && curStatus != 'e') {
        pressMillis = millis();
        setBtnColor(GREEN);

    } else if (digitalRead(btnPin) == HIGH && pressMillis > 0 && curStatus != 'd' && curStatus != 'e') {
        if (millis() - pressMillis >= durCrisisPress) {
            setBtnColor(PINK);
        }
    
    // If btn LOW and millis set, set status

    } else if (digitalRead(btnPin) == LOW && pressMillis > 0 && curStatus != 'd' && curStatus != 'e') {
        int dur = millis() - pressMillis;

        if (dur >= durCrisisPress) {
            curStatus = 'c';
            blinkType = 1;
            partyActive = false;
        } else if (dur >= durBtnPress) {
            curStatus = 'b';
        }

    // If btn HIGH and status 'e' then set status 'a'

    } else if (digitalRead(btnPin) == HIGH && curStatus == 'e') {
        curStatus = 'a';
        blinkType = 0;
        setBtnColor(RED);
        delay(200);
    }
}