#include <SoftwareSerial.h>

// Current status answer

String curStatusAnswer = "";

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

SoftwareSerial serialPortOne(51, A8);
SoftwareSerial serialPortTwo(50, A9);
SoftwareSerial serialPortThree(53, A10);
SoftwareSerial serialPortFour(52, A11);
SoftwareSerial serialPortFive(10, A12);

// Currently active serial port

SoftwareSerial curPort(22, 24);
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
int resetPin = 12;

void setup()
{
    digitalWrite(resetPin, HIGH);

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
    pinMode(resetPin, OUTPUT);

    digitalWrite(activity_led_one, HIGH);
    digitalWrite(activity_led_two, HIGH);
    digitalWrite(activity_led_three, HIGH);
    digitalWrite(activity_led_four, HIGH);
    digitalWrite(activity_led_five, HIGH);
    digitalWrite(activity_led_up, HIGH);

    delay(200);
    digitalWrite(activity_led_one, LOW);
    digitalWrite(activity_led_two, LOW);
    digitalWrite(activity_led_three, LOW);
    digitalWrite(activity_led_four, LOW);
    digitalWrite(activity_led_five, LOW);
    digitalWrite(activity_led_up, LOW);
    discoveryActive = true;
}

void toggleActivityLED(int LEDNumber)
{
    Serial.println("Change led: " + String(LEDNumber));
    switch (LEDNumber)
    {
    case 0:
        // if (activity_led_one == false) {
        activity_led_one_state = true;
        activity_led_one_millis = millis();
        digitalWrite(activity_led_one, HIGH);
        return;
        /*} else {
            activity_led_one_state = false;
            activity_led_one_millis = millis();
            digitalWrite(activity_led_one, LOW);
            return;
        }*/
        break;
    case 1:
        // if (activity_led_two == false) {
        activity_led_two_state = true;
        activity_led_two_millis = millis();
        digitalWrite(activity_led_two, HIGH);
        return;
        /*} else {
            activity_led_two_state = false;
            activity_led_two_millis = millis();
            digitalWrite(activity_led_two, LOW);
            return;
        }*/
        break;
    case 2:
        // if (activity_led_three == false) {
        activity_led_three_state = true;
        activity_led_three_millis = millis();
        digitalWrite(activity_led_three, HIGH);
        return;
        /*} else {
            activity_led_three_state = false;
            activity_led_three_millis = millis();
            digitalWrite(activity_led_three, LOW);
            return;
        }*/
        break;
    case 3:
        // if (activity_led_four == false) {
        activity_led_four_state = true;
        activity_led_four_millis = millis();
        digitalWrite(activity_led_four, HIGH);
        return;
        /*} else {
            activity_led_four_state = false;
            activity_led_four_millis = millis();
            digitalWrite(activity_led_four, LOW);
            return;
        }*/
        break;
    case 4:
        // if (activity_led_five == false) {
        activity_led_five_state = true;
        activity_led_five_millis = millis();
        digitalWrite(activity_led_five, HIGH);
        return;
        /*} else {
            activity_led_five_state = false;
            activity_led_five_millis = millis();
            digitalWrite(activity_led_five, LOW);
            return;
        }*/
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
                toggleActivityLED(curPortNumber);
                char curPortType = curPort.read();
                char curPortBId;

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
        else if (curPortNumber == 4)
        {
            curPort = serialPortFive;
        }
        else if (curPortNumber >= 5)
        {
            if (discoveryActive == true)
            {
                String allIds = "";
                for (int i = 0; i <= 4; i++)
                {
                    if (porttype[i] == 1)
                    {
                        allIds = allIds + portids[i];
                    }
                }
                Serial.println("All IDs captured: " + allIds);
                digitalWrite(activity_led_up, HIGH);
            }
            else
            {
                String allStatus = "";
                for (int i = 0; i <= 4; i++)
                {
                    if (porttype[i] == 1)
                    {
                        allStatus = allStatus + portids[i];
                        allStatus = allStatus + btnStatus[portids[i].c_str()[0] - 'A'];
                    }
                }
                Serial.println("All Status captured: " + allStatus);
                curStatusAnswer = allStatus;
            }
            discoveryActive = false;
            curPortNumber = -1;
            return;
        }

        Serial.println("curPortNumber is " + String(curPortNumber));

        curPort.begin(9600);
        if (discoveryActive == true)
        {
            curPort.print('?');
            curPort.print('_');
        }
        else
        {
            char idtosend = portids[curPortNumber].c_str()[0];
            curPort.print(idtosend);
            curPort.print('a');
        }
        waitingForAnswer = true;
        waitingForAnswerMillis = millis();
        return;
    }
}

void checkAllActivityLED()
{
    if (activity_led_one_state == true && millis() - activity_led_one_millis >= 5000)
    {
        activity_led_one_state = false;
        digitalWrite(activity_led_one, LOW);
    }
    if (activity_led_two_state == true && millis() - activity_led_two_millis >= 5000)
    {
        activity_led_two_state = false;
        digitalWrite(activity_led_two, LOW);
    }
    if (activity_led_three_state == true && millis() - activity_led_three_millis >= 5000)
    {
        activity_led_three_state = false;
        digitalWrite(activity_led_three, LOW);
    }
    if (activity_led_four_state == true && millis() - activity_led_four_millis >= 5000)
    {
        activity_led_four_state = false;
        digitalWrite(activity_led_four, LOW);
    }
    if (activity_led_five_state == true && millis() - activity_led_five_millis >= 5000)
    {
        activity_led_five_state = false;
        digitalWrite(activity_led_five, LOW);
    }
    return;
}

void checkMasterPort()
{
    if (Serial1.available())
    {
        delay(100);
        char readid = Serial1.read();
        char readinst = Serial1.read();

        String testString = String(readid);
        testString.toLowerCase();

        Serial.println("Got id: " + String(readid) + " Got inst: " + String(readinst));

        if (testString == String(readid) && readid != '?' && readid != '!')
        {
            Serial.println("FAIL");
            return;
        }

        if (readid == 'S')
        {
            if (readinst == 'a')
            {
                Serial1.print(curStatusAnswer);
            }
        }

        if (readid == '?' && readinst == '_' && discoveryActive == false)
        {
            Serial.println("CHECK");
            int numberOfIds = 0;
            String allIds = "";
            for (int i = 0; i <= 5; i++)
            {
                if (porttype[i] == 1)
                {
                    numberOfIds += 1;
                    allIds = allIds + String(portids[i]);
                }
            }
            Serial.println(String(numberOfIds));
            Serial.println(allIds);
            Serial1.print('S');
            Serial1.print(String(numberOfIds));
            Serial1.print(allIds);
        }

        if (readid == '!' && readinst == '_')
        {
            /*curPort.end();
            curPortNumber = -1;
            discoveryActive = true;
            waitingForAnswer = false;
            for (int i = 0; i <= 5; i++) {
                portids[i] = "";
                porttype[i] = 0;
            }
            curStatusAnswer = "";
            delay(100);*/
            digitalWrite(resetPin, LOW);
        }

        if (readid != '!' && readid != '?' && readid != 'S' && (readinst == 'b' || readinst == 'c' || readinst == 's' || readinst == 'r' || readinst == 'p'))
        {
            for (int i = 0; i <= 4; i++)
            {
                if (readid == 'Y')
                {
                    waitingForAnswer = false;
                    curPort.end();
                    if (i == 0)
                    {
                        curPort = serialPortOne;
                    }
                    else if (i == 1)
                    {
                        curPort = serialPortTwo;
                    }
                    else if (i == 2)
                    {
                        curPort = serialPortThree;
                    }
                    else if (i == 3)
                    {
                        curPort = serialPortFour;
                    }
                    else if (i == 4)
                    {
                        curPort = serialPortFive;
                    }

                    curPort.begin(9600);
                    curPort.print(readid);
                    curPort.print(readinst);
                }
                else
                {
                    bool done = false;
                    if (portids[i].charAt(0) == readid)
                    {
                        waitingForAnswer = false;
                        curPort.end();
                        if (i == 0)
                        {
                            curPort = serialPortOne;
                        }
                        else if (i == 1)
                        {
                            curPort = serialPortTwo;
                        }
                        else if (i == 2)
                        {
                            curPort = serialPortThree;
                        }
                        else if (i == 3)
                        {
                            curPort = serialPortFour;
                        }
                        else if (i == 4)
                        {
                            curPort = serialPortFive;
                        }

                        curPort.begin(9600);
                        curPort.print(readid);
                        curPort.print(readinst);
                        break;
                    }
                }
            }
        }
    }
}

void loop()
{
    checkMasterPort();
    checkAllActivityLED();

    if (discoveryActive == true || millis() - communication_util_millis >= 50)
    {
        communication_util_millis = millis();
        communicationUtil();
    }
}