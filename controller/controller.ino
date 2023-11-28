#include <SoftwareSerial.h>
#include <Elegoo_GFX.h>
#include <Elegoo_TFTLCD.h>

/*
 *
 *  Config
 *
 *
 */

// LCD Pins
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

// LCD Colors

#define LCD_BLACK 0x0000
#define LCD_BLUE 0x001F
#define LCD_RED 0xF800
#define LCD_GREEN 0x07E0
#define LCD_CYAN 0x07FF
#define LCD_PINK 0xF81F
#define LCD_YELLOW 0xFFE0
#define LCD_ORANGE 0xFD40
#define LCD_WHITE 0xFFFF

// Controller button pins

int start_btn = 25;
int crisis_btn = 50;
int page_btn = 36;
int home_btn = 32;
int nav_left_btn = 42;
int nav_right_btn = 34;
int nav_enter_btn = 38;
int com_led_disable_btn = 40;

// Controller button led pins

int start_blue = 10;
int start_red = 12;
int start_green = 11;
int crisis_red = 37;   // NO PWM
int crisis_green = 35; // NO PWM

// Led pins

int tx_led = 28;
int rx_led = 30;

int status_led_red = 45;
int status_led_green = 44;
int status_led_blue = 46;

// Selection number

int curSelection = -1;

/*
 *
 *  Page Type
 *
 *  -1   ->  Home
 *  0-5  ->  Button Page
 *  -2   ->  Settings
 *  -3   ->  Credits
 *  -4   ->  Debug
 *  -100 ->  Startup screen
 *
 */

int curPage = -1;

/*
 *
 *  Area links
 *
 *  0   ->  Eingang
 *  1   ->  Hexe 1
 *  2   ->  Hexe 2
 *  3   ->  Labor
 *  4   ->  Friedhof
 *  5   ->  Ausgang
 *
 *  Value must be button id
 *
 */

String areaname[6] = {"Eingang", "Hexe 1", "Hexe 2", "Labor", "Friedhof", "Ausgang"};

char arealinking[6] = {'A', 'B', 'C', 'D', 'E', 'F'};

/*
 *
 *  SoftwareSerial Port handling
 *
 */

SoftwareSerial serialPortOne(51, A10);  // Dose Links, Links
SoftwareSerial serialPortTwo(53, A9);   // Dose Links, Rechts
SoftwareSerial serialPortThree(13, A8); // Dose Rechts, Links
SoftwareSerial serialPortFour(52, A11); // Dose Rechts, Rechts

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
int porttype[4] = {};

/*
 *
 *  Port ids
 *
 *  Contains string with id(s)
 *
 *  Buttons -> "A"
 *  Switches -> "ABCDEFG"
 *
 */

String portids[4] = {};

/*
 *
 *  Port size (only for switches)
 *
 *
 */

int portsize[4] = {};

/*
 *
 *  Button status tracking
 *
 *  Status at index of int of ID - 65
 *  e.g. A = 0, B = 1 , etc.
 *
 */

char btnStatus[10] = {};

bool btnBypass[6] = {};

bool btnManualActivation[6] = {};

/*
 *
 *  Button status colors
 *
 *  a   ->  Yellow
 *  b   ->  Green
 *  c   ->  Pink
 *  d   ->  Blue
 *  e   ->  Orange
 *  n   ->  Black
 *
 */

uint16_t statusAcolor = LCD_YELLOW;
uint16_t statusBcolor = LCD_GREEN;
uint16_t statusCcolor = LCD_PINK;
uint16_t statusDcolor = LCD_BLUE;
uint16_t statusEcolor = LCD_ORANGE;
uint16_t statusNcolor = LCD_BLACK;

/*
 *
 * Controller status
 *
 * a    ->  Waiting for activation  (LED Yellow)
 * b    ->  Show running            (LED Green)
 * c    ->  Crisis mode active      (LED Pink)
 * d    ->  Discovery running       (LED Orange)
 * f    ->  Failure                 (LED Blue)
 *
 */

char controllerStatus = 'a';

const int STATUS_RED[3] = {255, 0, 0};
const int STATUS_ORANGE[3] = {255, 50, 0};
const int STATUS_YELLOW[3] = {255, 255, 0};
const int STATUS_GREEN[3] = {0, 255, 0};
// const int STATUS_CYAN[3] = {0,255,255};
const int STATUS_BLUE[3] = {0, 0, 255};
// const int STATUS_PURPLE[3] = {128,0,128};
const int STATUS_PINK[3] = {255, 20, 147};
// const int STATUS_WHITE[3] = {255,255,255};
const int STATUS_BLACK[3] = {0, 0, 0};

// Action locks

unsigned long page_btn_millis = 0;
unsigned long home_btn_millis = 0;
unsigned long open_settings_millis = 0;
unsigned long nav_left_btn_millis = 0;
unsigned long nav_enter_btn_millis = 0;
unsigned long nav_right_btn_millis = 0;
unsigned long com_led_disable_btn_millis = 0;
unsigned long crisis_btn_millis = 0;
unsigned long start_btn_millis = 0;

unsigned long communication_util_millis = 0;
unsigned long status_led_change_millis = 0;
unsigned long status_check_millis = 0;
unsigned long crisis_led_blink_millis = 0;
unsigned long witch_status_sent_millis = 0;
unsigned long witch_wait_millis = 0;

bool sent_area_one_blink = false;
bool area_one_reconnect = false;
bool sent_area_two_blink = false;
bool area_two_reconnect = false;
bool sent_btn_pressed_blink = false;
bool btn_pressed_reconnect = false;
bool sent_vogelscheuche = false;
bool sent_stop_playing = false;

// Debug states

bool page_btn_debug = false;
bool home_btn_debug = false;
bool nav_left_btn_debug = false;
bool nav_enter_btn_debug = false;
bool nav_right_btn_debug = false;
bool com_led_disable_btn_debug = false;
bool crisis_btn_debug = false;
bool start_btn_debug = false;

// Bitmaps for logo
extern uint8_t logobody[];
extern uint8_t logoeye[];
extern uint8_t heart[];
extern uint8_t heartout[];
extern uint8_t otto_small[];
extern uint8_t eye_small[];

// Tft display
Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// Lower bar Home Screen
unsigned long showRunningMillis = 0;
char digitZero = '0';
char digitOne = '0';
char digitTwo = '0';
char digitThree = '0';
char digitFour = '0';

String oldStatusText = "";

// Values for show

bool witchEmpty = false;

// Misc values
bool discoveryActive = false;
bool comLEDDisabled = false;
bool rxLEDState = false;
bool txLEDState = false;
bool crisisLEDState = true;
unsigned long lastComLEDchange = 0;
unsigned long lastCrisisDisable = 0;
unsigned long lastBtnSentAction = 0;
unsigned long timeSinceReset = 0;
int minCrisisDisable = 2000;
int minLastBtnSentAction = 2000;
int minTimeSinceReset = 4000;

void setup()
{

    // Begin Serial
    Serial.begin(9600);

    Serial1.begin(9600);

    /*serialPortOne.begin(9600);
    serialPortTwo.begin(9600);
    serialPortOne.end();*/
    // serialPortThree.begin(9600);
    // serialPortFour.begin(9600);

    // PinModes
    pinMode(start_red, OUTPUT);
    pinMode(start_green, OUTPUT);
    pinMode(start_blue, OUTPUT);
    pinMode(crisis_red, OUTPUT);
    pinMode(crisis_green, OUTPUT);
    pinMode(rx_led, OUTPUT);
    pinMode(tx_led, OUTPUT);
    pinMode(status_led_red, OUTPUT);
    pinMode(status_led_green, OUTPUT);
    pinMode(status_led_blue, OUTPUT);

    pinMode(start_btn, INPUT);
    pinMode(crisis_btn, INPUT);
    pinMode(page_btn, INPUT);
    pinMode(home_btn, INPUT);
    pinMode(nav_left_btn, INPUT);
    pinMode(nav_right_btn, INPUT);
    pinMode(nav_enter_btn, INPUT);
    pinMode(com_led_disable_btn, INPUT);

    // Begin display
    tft.reset();
    uint16_t identifier = tft.readID();
    if (identifier == 0x0101)
    {
        identifier = 0x9341;
    }
    tft.begin(identifier);
    tft.setRotation(3);
    tft.fillScreen(LCD_BLACK);
    display_startup();
    lampTest(true);
    delay(3000);
    lampTest(false);
    // Standard set Area 5 to bypass
    btnBypass[5] = true;
    /*btnStatus[arealinking[0] - 'A'] = 'a';
    btnStatus[arealinking[1] - 'A'] = 'b';
    btnStatus[arealinking[2] - 'A'] = 'c';
    btnStatus[arealinking[3] - 'A'] = 'd';
    btnStatus[arealinking[4] - 'A'] = 'e';*/

    discoveryActive = true;
    controllerStatus = 'd';
    curPage = -100;

    // Make buttons glow

    digitalWrite(start_green, HIGH);
    digitalWrite(crisis_red, HIGH);
}

void setStatusLEDColor()
{
    // If crisis let crisis btn blink
    if (controllerStatus == 'c' && millis() - crisis_led_blink_millis >= 1000)
    {
        crisis_led_blink_millis = millis();
        if (crisisLEDState == true)
        {
            crisisLEDState = false;
            digitalWrite(crisis_red, LOW);
        }
        else
        {
            crisisLEDState = true;
            digitalWrite(crisis_red, HIGH);
        }
    }
    else if (controllerStatus != 'c' && crisisLEDState == false)
    {
        digitalWrite(crisis_red, HIGH);
    }
    int redColor = 0;
    int greenColor = 0;
    int blueColor = 0;
    switch (controllerStatus)
    {
    case 'a':
        // Waiting for activation
        redColor = STATUS_YELLOW[0];
        greenColor = STATUS_YELLOW[1];
        blueColor = STATUS_YELLOW[2];
        break;
    case 'b':
        // Show running
        redColor = STATUS_GREEN[0];
        greenColor = STATUS_GREEN[1];
        blueColor = STATUS_GREEN[2];
        break;
    case 'c':
        // Crisis mode active
        redColor = STATUS_PINK[0];
        greenColor = STATUS_PINK[1];
        blueColor = STATUS_PINK[2];
        break;
    case 'd':
        // Discovery running
        redColor = STATUS_ORANGE[0];
        greenColor = STATUS_ORANGE[1];
        blueColor = STATUS_ORANGE[2];
        break;
    case 'f':
        // Failure
        redColor = STATUS_BLUE[0];
        greenColor = STATUS_BLUE[1];
        blueColor = STATUS_BLUE[2];
        break;
    }

    analogWrite(status_led_red, redColor);
    analogWrite(status_led_green, greenColor);
    analogWrite(status_led_blue, blueColor);
    return;
}

void startShow()
{
    timeSinceReset = millis();
    showRunningMillis = millis();
    witchEmpty = true;
    sent_area_one_blink = false;
    sent_btn_pressed_blink = false;
    sent_vogelscheuche = false;
    sent_stop_playing = false;
    int i = 2;
    if (controllerStatus == 'c')
    {
        i = 0;
    }
    controllerStatus = 'a';
    for (i; i <= 5; i++)
    {
        if (btnStatus[arealinking[i] - 'A'] == 'b')
        {
            btnStatus[arealinking[i] - 'A'] = 'a';
        }
        for (int j = 0; j <= 3; j++)
        {
            delay(10);
            if (portids[j].indexOf(arealinking[i]) != -1)
            {
                curPort.end();
                waitingForAnswer = false;
                if (j == 0)
                {
                    curPort = serialPortOne;
                }
                else if (j == 1)
                {
                    curPort = serialPortTwo;
                }
                else if (j == 2)
                {
                    curPort = serialPortThree;
                }
                else if (j == 3)
                {
                    curPort = serialPortFour;
                }
                curPort.begin(9600);
                setComLED("tx");
                curPort.print(arealinking[i]);
                curPort.print('s');
                break;
            }
        }
    }
    Serial1.print('s');
    return;
}

uint16_t getLCDColor(char status)
{
    switch (status)
    {
    case 'a':
        return statusAcolor;
        break;
    case 'b':
        return statusBcolor;
        break;
    case 'c':
        return statusCcolor;
        break;
    case 'd':
        return statusDcolor;
        break;
    case 'e':
        return statusEcolor;
        break;
    default:
        return statusNcolor;
        break;
    }
}

void resetStatus()
{
    curPort.end();
    waitingForAnswer = false;
    controllerStatus = 'a';
    crisisLEDState = true;
    digitalWrite(crisis_red, HIGH);
    sent_area_one_blink = false;
    sent_area_two_blink = false;
    sent_btn_pressed_blink = false;

    for (int i = 0; i <= 3; i++)
    {
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

        setComLED("tx");
        curPort.begin(9600);
        curPort.print('Y');
        curPort.print('s');
        delay(20);
        curPort.end();
    }

    String allIds = "";

    for (int i = 0; i <= 3; i++)
    {
        allIds = allIds + String(portids[i]);
    }
    for (int i = 0; i <= (allIds.length() - 1); i++)
    {
        btnStatus[allIds.charAt(i) - 'A'] = 'a';
    }
    lastCrisisDisable = millis();
    lastBtnSentAction = millis();
    timeSinceReset = millis();
    return;
}

void enableCrisis()
{
    if (controllerStatus != 'c')
    {
        Serial1.print('p');
        showRunningMillis = 0;
        for (int i = 0; i <= 3; i++)
        {
            curPort.end();
            waitingForAnswer = false;
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

            setComLED("tx");
            curPort.begin(9600);
            curPort.print('Y');
            curPort.print('c');
        }
    }
    controllerStatus = 'c';

    return;
}

void handleSelection(char act, int dir = 0)
{
    int btnPageSelectMax = 3;
    int homePageSelectMax = 6;
    int settingsPageSelectMax = 4;

    if (act == 'u')
    {
        if (curPage == -2)
        {
            switch (curSelection)
            {
            case 1:
                curPage = -3;
                renderCreditsPage();
                return;
            case 2:
                curPage = -4;
                renderDebugPage();
                return;
            case 3:
                for (int i = 0; i <= 3; i++)
                {
                    if (porttype[i] == 2)
                    {
                        curPort.end();
                        waitingForAnswer = false;
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

                        setComLED("tx");
                        curPort.begin(9600);
                        curPort.print('!');
                        curPort.print('_');
                        delay(20);
                        curPort.end();
                    }
                    porttype[i] = 0;
                    portids[i] = "";
                }
                curPortNumber = -1;
                waitingForAnswer = false;
                discoveryActive = true;
                controllerStatus = 'd';
                display_startup();
                curPage = -100;
                delay(3000);

                return;
            case 4:
                resetStatus();
                renderHome();
                return;
            }
        }
        else if (curPage == -1)
        {
            if (curSelection == -1)
            {
                return;
            }
            curPage = curSelection - 1;
            renderButtonPage(curSelection - 1);
            return;
        }
        else if (curPage >= 0 && curPage <= 5)
        {
            // ToDo: Add Button Page actions
            switch (curSelection)
            {
            case 1:
                return;
            case 2:
                int curBypassStatus = btnBypass[curPage];

                if (curBypassStatus == false)
                {
                    btnBypass[curPage] = 1;
                    tft.fillRect(20, 187, 25, 20, LCD_GREEN);
                    return;
                }
                else
                {
                    btnBypass[curPage] = 0;
                    tft.fillRect(20, 187, 25, 20, LCD_RED);
                    return;
                }
                return;
            case 3:
                // Set button to have started
                btnManualActivation[curPage] = true;
                return;
            }
        }
    }

    if (act == 'c')
    {
        curSelection = -1;
        return;
    }
    if (dir == NULL || dir == 0)
    {
        Serial.println("ERROR (handleSelection): NO DIR OR DIR 0");
        return;
    }
    if (curSelection == -1)
    {
        curSelection = 1;
        renderSelection(1, false);
        return;
    }

    curSelection = curSelection + dir;

    int maxSelection;

    if (curPage == -2)
    {
        maxSelection = settingsPageSelectMax;
    }
    else if (curPage == -1)
    {
        maxSelection = homePageSelectMax;
    }
    else if (curPage >= 0 && curPage <= 5)
    {
        maxSelection = btnPageSelectMax;
    }

    if (curSelection <= 0)
    {
        renderSelection(1, true);
        curSelection = maxSelection;
        renderSelection(curSelection, false);
        return;
    }

    if (curSelection > maxSelection)
    {
        renderSelection(maxSelection, true);
        curSelection = 1;
        renderSelection(curSelection, false);
        return;
    }

    if (dir == 1)
    {
        renderSelection(curSelection - 1, true);
        renderSelection(curSelection, false);
        return;
    }
    else if (dir == -1)
    {
        renderSelection(curSelection + 1, true);
        renderSelection(curSelection, false);
        return;
    }
    return;
}

void activatePartyMode()
{
    for (int i = 0; i <= 3; i++)
    {
        curPort.end();
        waitingForAnswer = false;
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

        setComLED("tx");
        curPort.begin(9600);
        curPort.print('Y');
        curPort.print('p');
    }
    return;
}

void lampTest(bool mode)
{
    if (mode == true)
    {
        digitalWrite(start_red, HIGH);
        digitalWrite(start_blue, HIGH);
        digitalWrite(start_green, HIGH);

        digitalWrite(crisis_red, HIGH);

        digitalWrite(status_led_red, HIGH);
        digitalWrite(status_led_green, HIGH);
        digitalWrite(status_led_blue, HIGH);

        digitalWrite(tx_led, HIGH);
        digitalWrite(rx_led, HIGH);
        return;
    }

    digitalWrite(start_red, LOW);
    digitalWrite(start_blue, LOW);
    digitalWrite(start_green, LOW);

    digitalWrite(crisis_red, LOW);

    digitalWrite(status_led_red, LOW);
    digitalWrite(status_led_green, LOW);
    digitalWrite(status_led_blue, LOW);

    digitalWrite(tx_led, LOW);
    digitalWrite(rx_led, LOW);
    return;
}

void setComLED(String led)
{
    if (comLEDDisabled == true)
    {
        return;
    }
    if (led == "tx")
    {
        lastComLEDchange = millis();
        if (txLEDState == false)
        {
            txLEDState = true;
            digitalWrite(tx_led, HIGH);
            return;
        }
        else
        {
            txLEDState = false;
            digitalWrite(tx_led, LOW);
            return;
        }
    }
    else if (led == "rx")
    {
        lastComLEDchange = millis();
        if (rxLEDState == false)
        {
            rxLEDState = true;
            digitalWrite(rx_led, HIGH);
            return;
        }
        else
        {
            rxLEDState = false;
            digitalWrite(rx_led, LOW);
            return;
        }
    }
    return;
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
                setComLED("rx");
                char curPortCount;
                char curPortBId;
                String curPortSId;

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
                    Serial.println("curPort is Switch");
                    curPortCount = curPort.read();
                    int calcNum = curPortCount - '0';

                    for (int i = 1; i <= calcNum; i++)
                    {
                        Serial.println("i: " + String(i));
                        delay(100);
                        char readId = curPort.read();
                        curPortSId = curPortSId + String(readId);
                        Serial.println("Port read: " + String(readId));
                    }
                    portids[curPortNumber] = curPortSId;
                    porttype[curPortNumber] = 2;
                    portsize[curPortNumber] = calcNum;

                    Serial.println("All IDs got: " + String(portids[curPortNumber]));
                }
                else if (curPortType == 'V')
                {
                    Serial.println("curPort is Vogelscheuche");

                    porttype[curPortNumber] = 3;
                }

                // Serial.println("Set Porttype of " + String(curPortNumber) + " to " + String(porttype[curPortNumber]));
            }
            else
            {
                // Serial.println("Port type of" + String(curPortNumber) + " is " + String(porttype[curPortNumber]));
                if (porttype[curPortNumber] == 1)
                {
                    setComLED("rx");
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
                    setComLED("rx");
                    for (int i = 1; i <= portsize[curPortNumber]; i++)
                    {
                        char readId = curPort.read();
                        char readStatus = curPort.read();

                        btnStatus[readId - 'A'] = readStatus;

                        Serial.println("Got ID: " + String(readId) + " Got Status: " + String(readStatus));
                    }
                }
                else if (porttype[curPortNumber] == 3)
                {
                    Serial.println("Got answer from Vogelscheuche; ignoring");
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
                if (porttype[curPortNumber] == 1)
                {
                    btnStatus[portids[curPortNumber].c_str()[0] - 'A'] = 'n';
                }
                else if (porttype[curPortNumber] == 2)
                {
                    for (int i = 0; i < portsize[curPortNumber]; i++)
                    {
                        Serial.println("Cur port to change: " + portids[curPortNumber]);
                        btnStatus[portids[curPortNumber].charAt(i) - 'A'] = 'n';
                    }
                }
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
        if (discoveryActive == false && (porttype[curPortNumber] == 0 || porttype[curPortNumber] == 3))
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
        else if (curPortNumber >= 4)
        {
            if (discoveryActive == false)
            {
                if (curPage == -1)
                {
                    renderHomeStatus();
                }
                statusCheck();
            }
            else if (discoveryActive == true)
            {
                controllerStatus = 'a';
                if (curPage == -100)
                {
                    renderHome();
                }
            }
            discoveryActive = false;
            curPortNumber = -1;
            return;
        }

        Serial.println("curPortNumber is " + String(curPortNumber));

        curPort.begin(9600);
        if (discoveryActive == true)
        {
            setComLED("tx");
            curPort.print('?');
            curPort.print('_');
        }
        else
        {
            char idtosend;
            if (porttype[curPortNumber] == 2)
            {
                idtosend = 'S';
            }
            else if (porttype[curPortNumber] == 1)
            {
                idtosend = portids[curPortNumber].charAt(0);
            }
            else if (porttype[curPortNumber] == 3)
            {
                // ERROR
            }
            setComLED("tx");
            curPort.print(idtosend);
            curPort.print('a');
        }
        waitingForAnswer = true;
        waitingForAnswerMillis = millis();
        return;
    }
}

void checkTime()
{
    int timeCalc = floor((millis() - showRunningMillis) / 1000);
    int minutes = floor(timeCalc / 60);
    int seconds = timeCalc % 60;

    String minString = String(minutes);
    String secString = String(seconds);

    if (minString.charAt(1) == NULL)
    {
        minString = "0" + minString;
    }
    if (secString.charAt(1) == NULL)
    {
        secString = "0" + secString;
    }

    if (minString.charAt(2) != NULL && minString.charAt(0) != digitZero) {
        digitZero = minString.charAt(0);
        displayClock(0, minString.charAt(0));
        minString.remove(0,1);
    }

    if (minString.charAt(0) != digitOne)
    {
        digitOne = minString.charAt(0);
        displayClock(1, minString.charAt(0));
    }
    if (minString.charAt(1) != digitTwo)
    {
        digitTwo = minString.charAt(1);
        displayClock(2, minString.charAt(1));
    }
    if (secString.charAt(0) != digitThree)
    {
        digitThree = secString.charAt(0);
        displayClock(3, secString.charAt(0));
    }
    if (secString.charAt(1) != digitFour)
    {
        digitFour = secString.charAt(1);
        displayClock(4, secString.charAt(1));
    }

    if (minString == "02" && secString == "38" && sent_vogelscheuche == false)
    {
        sent_vogelscheuche = true;

        for (int i = 0; i <= 3; i++)
        {
            if (porttype[i] == 3)
            {
                curPort.end();
                waitingForAnswer = false;
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

                setComLED("tx");
                curPort.begin(9600);
                curPort.print('V');
                curPort.print('$');
            }
        }
    }

    if (minString == "30" && sent_stop_playing == false) {
        sent_stop_playing = true;

        Serial1.print('r');
        controllerStatus = 'a';
        showRunningMillis = 0;
    }

    Serial.println("Mins: " + minString + " Secs: " + secString);
}

void loop()
{
    if (showRunningMillis != 0 || (showRunningMillis == 0 && (digitZero != '0' || digitOne != '0' || digitTwo != '0' || digitThree != '0' || digitFour != '0')))
    {
        checkTime();
    }
    if (discoveryActive == true || (millis() - communication_util_millis >= 50 && (porttype[0] != 0 || porttype[1] != 0 || porttype[2] != 0 || porttype[3] != 0)))
    {
        communication_util_millis = millis();
        communicationUtil();
    }
    if (millis() - status_led_change_millis >= 1000)
    {
        setStatusLEDColor();
        if (curPage == -1)
        {
            displayStatus();
        }
    }
    checkForBtnActive();

    if (millis() - lastComLEDchange >= 5000 && (rxLEDState == true || txLEDState == true))
    {
        digitalWrite(tx_led, LOW);
        digitalWrite(rx_led, LOW);
        rxLEDState = false;
        txLEDState = false;
    }
}