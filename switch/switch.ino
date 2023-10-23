#include <SoftwareSerial.h>

// Activity LEDs

int activity_led_up = 47;
int activity_led_one = 46;
int activity_led_two = 45;
int activity_led_three = 44;
int activity_led_four = 43;
int activity_led_five = 4;

// Activity LED millis

unsigned long activity_led_one_millis = 0;
unsigned long activity_led_two_millis = 0;
unsigned long activity_led_three_millis = 0;
unsigned long activity_led_four_millis = 0;
unsigned long activity_led_five_millis = 0;

// Activity LED states

bool activity_led_one_state = false;
bool activity_led_two_state = false;
bool activity_led_three_state = false;
bool activity_led_four_state = false;
bool activity_led_five_state = false;

// SoftwareSerial Ports

SoftwareSerial serialPortOne(A8, 51);
SoftwareSerial serialPortTwo(A9, 50);
SoftwareSerial serialPortThree(A10, 53);
SoftwareSerial serialPortFour(A11, 52);
SoftwareSerial serialPortFive(A12, 10);

// Currently active serial port

SoftwareSerial curPort(22,24);
int curPortNumber = -1;

bool waitingForAnswer = false;
unsigned long waitingForAnswerMillis = 0;
int maxWaitingForAnswerMillis = 1000;

/*
 *
 *  Port type
 *
 *  1 B -> Button (One id)
 *  2 S -> Switch (String of ids)
 *
 */
int porttype[5] = {};

/*
 *
 *  Port ids
 *
 *  Contains string with id(s)
 *
 *  Buttons -> "A"
 *
 */

String portids[5] = {};

/*
 *
 *  Button status tracking
 *
 *  Status at index of int of ID - 65
 *  e.g. A = 0, B = 1 , etc.
 *
 */

char btnStatus[5] = {};

// Misc values
bool discoveryActive = false;
unsigned long communication_util_millis = 0;

void setup() {

    // Begin Serial
    Serial.begin(9600);
    
    Serial1.begin(9600);


    // PinModes
    pinMode(activity_led_one, OUTPUT);
    pinMode(activity_led_two, OUTPUT);
    pinMode(activity_led_three, OUTPUT);
    pinMode(activity_led_four, OUTPUT);
    pinMode(activity_led_five, OUTPUT);
    pinMode(activity_led_up, OUTPUT);

    delay(200);
    discoveryActive = true;
}

void toggleActivityLED(int LEDNumber) {
    switch (LEDNumber) {
        case 0:
            if (activity_led_two == false) {
                activity_led_two_state = true;
                activity_led_two_millis = millis();
                digitalWrite(activity_led_two, HIGH);
                return;
            } else {
                activity_led_two_state = false;
                activity_led_two_millis = millis();
                digitalWrite(activity_led_two, LOW);
                return;
            }
            break;
        case 1:
            if (activity_led_two == false) {
                activity_led_two_state = true;
                activity_led_two_millis = millis();
                digitalWrite(activity_led_two, HIGH);
                return;
            } else {
                activity_led_two_state = false;
                activity_led_two_millis = millis();
                digitalWrite(activity_led_two, LOW);
                return;
            }
            break;
        case 2:
            if (activity_led_three == false) {
                activity_led_three_state = true;
                activity_led_three_millis = millis();
                digitalWrite(activity_led_three, HIGH);
                return;
            } else {
                activity_led_three_state = false;
                activity_led_three_millis = millis();
                digitalWrite(activity_led_three, LOW);
                return;
            }
            break;
        case 3:
            if (activity_led_four == false) {
                activity_led_four_state = true;
                activity_led_four_millis = millis();
                digitalWrite(activity_led_four, HIGH);
                return;
            } else {
                activity_led_four_state = false;
                activity_led_four_millis = millis();
                digitalWrite(activity_led_four, LOW);
                return;
            }
            break;
        case 4:
            if (activity_led_five == false) {
                activity_led_five_state = true;
                activity_led_five_millis = millis();
                digitalWrite(activity_led_five, HIGH);
                return;
            } else {
                activity_led_five_state = false;
                activity_led_five_millis = millis();
                digitalWrite(activity_led_five, LOW);
                return;
            }
            break;
    }
}

void communicationUtil()
{
    if (waitingForAnswer == true)
    {
        if (curPort.available() && millis() - waitingForAnswerMillis >= 200)
        {
            Serial.println("Got answer from curPort");

            if (discoveryActive == true)
            {

                char curPortType = curPort.read();
                toggleActivityLED(curPortNumber);
                char curPortCount;
                char curPortBId;
                String curPortSId;

                delay(10);

                if (curPortType == 'B')
                {
                    Serial.println("curPort is Button");
                    curPortBId = curPort.read();
                    portids[curPortNumber] = String(curPortBId);
                    Serial.println("curPortId is " + String(curPortBId));
                    porttype[curPortNumber] = 1;
                }
                else if (curPortType == 'S')
                {
                    // ToDo: Error
                }

                // Serial.println("Set Porttype of " + String(curPortNumber) + " to " + String(porttype[curPortNumber]));
            }
            else
            {
                // Serial.println("Port type of" + String(curPortNumber) + " is " + String(porttype[curPortNumber]));
                if (porttype[curPortNumber] == 1)
                {
                    toggleActivityLED(curPortNumber);
                    char readstatus = curPort.read();
                    String readstatustest = String(readstatus);
                    readstatustest.toLowerCase();

                    Serial.println("Got status " + String(readstatus));

                    if (String(readstatus) == readstatustest)
                    {
                        Serial.println("Read status: " + String(readstatus));

                        btnStatus[portids[curPortNumber].c_str()[0] - 'A'] = readstatus;
                    }
                    else
                    {
                        btnStatus[portids[curPortNumber].c_str()[0] - 'A'] = 'n';
                    }
                }
                else if (porttype[curPortNumber] == 2)
                {
                    // Error
                }
            }

            waitingForAnswer = false;
        }

        if (waitingForAnswer == true && millis() - waitingForAnswerMillis >= maxWaitingForAnswerMillis)
        {
            Serial.println("Got no answer from curPort");
            if (discoveryActive == true)
            {
                porttype[curPortNumber] = 0;
            }
            else
            {
                btnStatus[portids[curPortNumber].c_str()[0] - 'A'] = 'n';
            }
            waitingForAnswer = false;
        }
        delay(20);
    }
    else
    {
        curPort.end();
        delay(10);
        curPortNumber += 1;

        // Serial.println("Port type of " + String(curPortNumber) + " is " + String(porttype[curPortNumber]));
        if (discoveryActive == false && porttype[curPortNumber] == 0)
        {
            return;
        }

        if (curPortNumber == 0)
        {
            curPort = serialPortOne;
        }
        else if (curPortNumber == 1)
        {
            curPort = serialPortTwo;
        }
        else if (curPortNumber == 2)
        {
            curPort = serialPortThree;
        }
        else if (curPortNumber == 3)
        {
            curPort = serialPortFour;
        }
        else if (curPortNumber == 3)
        {
            curPort = serialPortFour;
        }
        else if (curPortNumber == 4)
        {
            curPort = serialPortFive;
        }
        else if (curPortNumber >= 5)
        {
            if (discoveryActive == true) {
                String allIds = "";
                for (int i = 0; i <= 4; i++) {
                    allIds = allIds + portids[i];
                }
                Serial.println("All IDs captured: " + allIds);
            } else {
                String allStatus = "";
                for (int i = 0; i <= 4; i++) {
                    allStatus = allStatus + portids[i];
                    allStatus = allStatus + btnStatus[portids[i].c_str()[0] - 'A'];
                }
                Serial.println("All Status captured: " + allStatus);
            }
            discoveryActive = false;
            curPortNumber = -1;
            return;
        }

        Serial.println("curPortNumber is " + String(curPortNumber));

        curPort.begin(9600);
        if (discoveryActive == true)
        {
            toggleActivityLED(curPortNumber);
            curPort.print('?');
            curPort.print('_');
        }
        else
        {
            char idtosend = portids[curPortNumber].c_str()[0];
            toggleActivityLED(curPortNumber);
            curPort.print(idtosend);
            curPort.print('a');
        }
        waitingForAnswer = true;
        waitingForAnswerMillis = millis();
        return;
    }
}

void checkAllActivityLED() {
    if (activity_led_one_state == true && millis() - activity_led_one_millis >= 5000) {
        activity_led_one_state = false;
        digitalWrite(activity_led_one, LOW);
    }
    if (activity_led_two_state == true && millis() - activity_led_two_millis >= 5000) {
        activity_led_two_state = false;
        digitalWrite(activity_led_two, LOW);
    }
    if (activity_led_three_state == true && millis() - activity_led_three_millis >= 5000) {
        activity_led_three_state = false;
        digitalWrite(activity_led_three, LOW);
    }
    if (activity_led_four_state == true && millis() - activity_led_four_millis >= 5000) {
        activity_led_four_state = false;
        digitalWrite(activity_led_four, LOW);
    }
    if (activity_led_five_state == true && millis() - activity_led_five_millis >= 5000) {
        activity_led_five_state = false;
        digitalWrite(activity_led_five, LOW);
    }
    return;
}

void checkMasterPort() {
    // ToDo: Check Master port for actions to do
}


void loop() {
    checkMasterPort();

    if (discoveryActive == true || millis() - communication_util_millis >= 100) {
        communication_util_millis = millis();
        communicationUtil();
    }
}