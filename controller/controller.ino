#define SC_CONTROLLER
/*#include <SoftwareSerial.h>
#include <Elegoo_GFX.h>
#include <Elegoo_TFTLCD.h>*/
#include <ShowcontrollerAPI.h>
/*
 *
 *  Config
 *
 *
 */

Area AreaList[20] = {
    Area(1,"Test",'A', SHOW_ACTIVATOR),
};

Config config {
};

// LCD Pins
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

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

void display_startup()
{

    // Fill screen with Black
    tft.fillScreen(LCD_BLACK);

    // Draw Logo body
    tft.drawBitmap(110, 10, logobody, 110, 159, LCD_WHITE);

    // Draw Left eye
    tft.drawBitmap(149, 53, logoeye, 6, 6, LCD_BLUE);

    // Draw Right eye
    tft.drawBitmap(179, 53, logoeye, 6, 6, LCD_PINK);

    // Text
    tft.setCursor(127, 180);
    tft.setTextSize(3);
    tft.setTextColor(LCD_WHITE);
    tft.print("HWHS");
    tft.setCursor(40, 210);
    tft.print("Showcontroller");

    return;
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

/*
 *
 *  Handle Selection Function
 *
 *  act:
 *
 *  c   =>  Clear (Clear selection on new page reload) [Sets selection to -1]
 *  m   =>  Move (Move the current selection) [Increases or decreases the selection according to dir value]
 *  u   =>  Use (Run the current selections action)
 *
 */

void renderSelection(int id, bool negative = false)
{
    uint16_t selectionColor = LCD_RED;
    if (negative == true)
    {
        selectionColor = LCD_WHITE;
    }

    // Settings page

    if (curPage == -2)
    {
        switch (id)
        {
        case 1:
            tft.drawRect(59, 59, 202, 42, selectionColor);
            return;
        case 2:
            tft.drawRect(59, 109, 202, 42, selectionColor);
            return;
        case 3:
            tft.drawRect(59, 159, 202, 42, selectionColor);
            return;
        case 4:
            tft.drawRect(109, 209, 102, 22, selectionColor);
            return;
        }
    }
    else if (curPage == -1)
    {
        switch (id)
        {
        case 1:
            tft.drawRect(14, 19, 140, 28, selectionColor);
            return;
        case 2:
            tft.drawRect(169, 19, 140, 28, selectionColor);
            return;
        case 3:
            tft.drawRect(14, 75, 140, 28, selectionColor);
            return;
        case 4:
            tft.drawRect(169, 75, 140, 28, selectionColor);
            return;
        case 5:
            tft.drawRect(14, 131, 140, 28, selectionColor);
            return;
        case 6:
            tft.drawRect(169, 131, 140, 28, selectionColor);
            return;
        }
    }
    else if (curPage >= 0 && curPage <= 5)
    {
        switch (id)
        {
        case 1:
            tft.drawRect(4, 74, 152, 77, selectionColor);
            return;
        case 2:
            tft.drawRect(4, 159, 152, 77, selectionColor);
            return;
        case 3:
            tft.drawRect(164, 159, 152, 77, selectionColor);
            return;
        }
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

void displayClock(int digit, char number)
{
    if (curPage != -1)
    {
        return;
    }
    tft.setTextSize(2);
    switch (digit)
    {
    case 0:
        tft.fillRect(228, 210, 10, 15, LCD_WHITE);
        tft.setCursor(228, 210);
        tft.print(String(number));
        break;
    case 1:
        tft.fillRect(240, 210, 10, 15, LCD_WHITE);
        tft.setCursor(240, 210);
        tft.print(String(number));
        // Change digit one
        break;
    case 2:
        tft.fillRect(252, 210, 10, 15, LCD_WHITE);
        tft.setCursor(252, 210);
        tft.print(String(number));
        // Change digit two
        break;
    case 3:
        tft.fillRect(272, 210, 10, 15, LCD_WHITE);
        tft.setCursor(272, 210);
        tft.print(String(number));
        // Change digit three
        break;
    case 4:
        tft.fillRect(284, 210, 10, 15, LCD_WHITE);
        tft.setCursor(284, 210);
        tft.print(String(number));
        // Change digit four
        break;
    }
    return;
}

void displayStatus()
{
    String statusText = "";

    if (showRunningMillis == 0)
    {
        statusText = "Idle";
    }

    if (controllerStatus == 'f')
    {
        statusText = "Fault";
    }

    if (showRunningMillis != 0)
    {
        statusText = "Show running";
    }

    if (controllerStatus == 'c')
    {
        statusText = "Panik";
    }

    if (statusText != oldStatusText)
    {
        oldStatusText = statusText;
        // Clear current Status
        tft.fillRect(15, 210, 215, 25, LCD_WHITE);

        // Print new Status
        tft.setCursor(15, 210);
        tft.print(statusText);
    }

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

void renderHomeStatus()
{
    uint16_t areacolor;

    if (curPage != -1)
    {
        return;
    }

    // Top Left Status
    areacolor = getLCDColor(btnStatus[arealinking[0] - 'A']);
    tft.fillRect(15, 20, 26, 26, areacolor);

    if (curPage != -1)
    {
        return;
    }

    // Middle Left Status
    areacolor = getLCDColor(btnStatus[arealinking[2] - 'A']);
    tft.fillRect(15, 76, 26, 26, areacolor);

    if (curPage != -1)
    {
        return;
    }

    // Bottom Left Status
    areacolor = getLCDColor(btnStatus[arealinking[4] - 'A']);
    tft.fillRect(15, 132, 26, 26, areacolor);

    if (curPage != -1)
    {
        return;
    }

    // Top Right Status
    areacolor = getLCDColor(btnStatus[arealinking[1] - 'A']);
    tft.fillRect(170, 20, 26, 26, areacolor);

    if (curPage != -1)
    {
        return;
    }

    // Middle Right Status
    areacolor = getLCDColor(btnStatus[arealinking[3] - 'A']);
    tft.fillRect(170, 76, 26, 26, areacolor);

    if (curPage != -1)
    {
        return;
    }

    // Bottom Right Status
    areacolor = getLCDColor(btnStatus[arealinking[5] - 'A']);
    tft.fillRect(170, 132, 26, 26, areacolor);

    return;
}

void renderHome()
{
    handleSelection('c');
    curPage = -1;
    // Fill screen with White
    tft.fillScreen(LCD_WHITE);

    // uint16_t areacolor;
    //  Top Left Status
    // areacolor = getcolor(btnStatus[arealinking[0] - 'A']);
    // tft.fillRect(15, 20, 26, 26, areacolor);
    tft.setCursor(52, 26);
    tft.setTextSize(2);
    tft.setTextColor(LCD_BLACK);
    tft.print(areaname[0]);

    // Middle Left Status
    // areacolor = getcolor(btnStatus[arealinking[2] - 'A']);
    // tft.fillRect(15, 76, 26, 26, areacolor);
    tft.setCursor(52, 82);
    tft.setTextSize(2);
    tft.setTextColor(LCD_BLACK);
    tft.print(areaname[2]);

    // Bottom Left Status
    // areacolor = getcolor(btnStatus[arealinking[4] - 'A']);
    // tft.fillRect(15, 132, 26, 26, areacolor);
    tft.setCursor(52, 138);
    tft.setTextSize(2);
    tft.setTextColor(LCD_BLACK);
    tft.print(areaname[4]);

    // Top Right Status
    // areacolor = getcolor(btnStatus[arealinking[1] - 'A']);
    // tft.fillRect(170, 20, 26, 26, areacolor);
    tft.setCursor(207, 26);
    tft.setTextSize(2);
    tft.setTextColor(LCD_BLACK);
    tft.print(areaname[1]);

    // Middle Right Status
    // areacolor = getcolor(btnStatus[arealinking[3] - 'A']);
    // tft.fillRect(170, 76, 26, 26, areacolor);
    tft.setCursor(207, 82);
    tft.setTextSize(2);
    tft.setTextColor(LCD_BLACK);
    tft.print(areaname[3]);

    // Bottom Right Status
    // areacolor = getcolor(btnStatus[arealinking[5] - 'A']);
    // tft.fillRect(170, 132, 26, 26, areacolor);
    tft.setCursor(207, 138);
    tft.setTextSize(2);
    tft.setTextColor(LCD_BLACK);
    tft.print(areaname[5]);

    renderHomeStatus();

    // Show Info Line
    tft.drawFastHLine(0, 190, 360, LCD_BLACK);
    tft.drawFastHLine(0, 191, 360, LCD_BLACK);
    tft.drawFastHLine(0, 192, 360, LCD_BLACK);

    // Show Status
    oldStatusText = "";
    displayStatus();

    // Show Run Duration
    displayClock(1, '0');
    displayClock(2, '0');
    tft.setCursor(262, 210);
    tft.print(":");
    displayClock(3, '0');
    displayClock(4, '0');

    return;
}

void renderButtonPage(int number)
{
    handleSelection('c');
    curPage = number;

    tft.fillScreen(LCD_WHITE);
    tft.setCursor(8, 8);
    tft.setTextSize(2);
    tft.setTextColor(LCD_BLACK);
    tft.print(areaname[number]);

    tft.drawRect(5, 75, 150, 75, LCD_BLACK);
    tft.setCursor(40, 105);
    tft.print("ID");
    tft.drawRect(78, 95, 32, 32, LCD_BLACK);
    tft.drawRect(79, 96, 30, 30, LCD_BLACK);
    tft.setCursor(89, 104);
    tft.setTextSize(2);
    tft.print(arealinking[number]);

    tft.drawRect(165, 75, 150, 75, LCD_BLACK);
    tft.setCursor(175, 105);
    tft.print("Status");
    tft.drawRect(258, 95, 32, 32, LCD_BLACK);
    tft.drawRect(259, 96, 30, 30, LCD_BLACK);
    tft.setCursor(269, 104);
    tft.setTextSize(2);
    tft.print(btnStatus[arealinking[number] - 'A']);

    tft.drawRect(5, 160, 150, 75, LCD_BLACK);
    tft.drawRect(19, 186, 27, 22, LCD_BLACK);
    if (btnBypass[number] == 1)
    {
        tft.fillRect(20, 187, 25, 20, LCD_GREEN);
    }
    else
    {
        tft.fillRect(20, 187, 25, 20, LCD_RED);
    }
    tft.setCursor(55, 190);
    tft.print("Bypass");

    tft.drawRect(165, 160, 150, 75, LCD_BLACK);
    tft.setCursor(192, 190);
    tft.print("Freigabe");

    return;
}

void renderSettingsPage()
{
    handleSelection('c');
    tft.fillScreen(LCD_WHITE);
    tft.setCursor(90, 20);
    tft.setTextSize(3);
    tft.setTextColor(LCD_BLACK);
    tft.print("Settings");

    tft.setTextSize(2);

    tft.drawRect(60, 60, 200, 40, LCD_BLACK);
    tft.setCursor(118, 72);
    tft.print("Credits");

    tft.drawRect(60, 110, 200, 40, LCD_BLACK);
    tft.setCursor(131, 122);
    tft.print("Debug");

    tft.drawRect(60, 160, 200, 40, LCD_BLACK);
    tft.setCursor(97, 172);
    tft.print("Re-Discover");

    tft.drawRect(110, 210, 100, 20, LCD_BLACK);
    tft.setTextSize(1);
    tft.setCursor(125, 217);
    tft.print("Reset Status");
    return;
}

void renderCreditsPage()
{
    handleSelection('c');
    tft.fillScreen(LCD_WHITE);
    tft.drawBitmap(5, 5, otto_small, 51, 50, LCD_BLACK);
    tft.drawBitmap(25, 19, eye_small, 3, 2, LCD_BLUE);
    tft.drawBitmap(34, 19, eye_small, 3, 2, LCD_PINK);
    /*
    tft.drawBitmap(5, 5, heart, 53, 53, LCD_RED);
    tft.drawBitmap(5, 5, heartout, 53, 53, LCD_BLACK);
    */

    tft.setCursor(75, 14);
    tft.setTextColor(LCD_ORANGE);
    tft.setTextSize(2);
    tft.print("HW");
    tft.setTextColor(LCD_BLACK);
    tft.print("HS Showcontroller");
    tft.setCursor(145, 34);
    tft.print("Credits");

    tft.setCursor(10, 70);
    tft.print("Coding:");

    tft.setCursor(170, 70);
    tft.setTextColor(LCD_BLUE);
    tft.print("Lo");
    tft.setTextColor(LCD_PINK);
    tft.print("is");

    tft.setCursor(10, 110);
    tft.setTextColor(LCD_BLACK);
    tft.print("Konstruktion:");

    tft.setCursor(170, 110);
    tft.setTextColor(LCD_GREEN);
    tft.print("Valentin");

    tft.setCursor(170, 130);
    tft.setTextColor(LCD_BLUE);
    tft.print("Lo");
    tft.setTextColor(LCD_PINK);
    tft.print("is");

    tft.setCursor(170, 150);
    tft.setTextColor(LCD_BLACK);
    tft.print("Timo");

    tft.setCursor(170, 170);
    tft.print("Christof");

    tft.setCursor(170, 190);
    tft.print("Steffen");

    tft.setTextSize(1);
    tft.setCursor(63, 226);
    tft.print("Holz gesponsert von Holzland Wulf");
    return;
}

void renderDebugPage()
{
    handleSelection('c');

    page_btn_debug = false;
    home_btn_debug = false;
    nav_left_btn_debug = false;
    nav_enter_btn_debug = false;
    nav_right_btn_debug = false;
    com_led_disable_btn_debug = false;
    crisis_btn_debug = false;
    start_btn_debug = false;

    tft.fillScreen(LCD_WHITE);
    tft.setCursor(105, 5);
    tft.setTextSize(2);
    tft.setTextColor(LCD_BLUE);
    tft.print("Debug ");
    tft.setTextColor(LCD_PINK);
    tft.print("Page");

    tft.setCursor(60, 25);
    tft.setTextSize(1);
    tft.setTextColor(LCD_BLACK);
    tft.print("Zum ");
    tft.setTextColor(LCD_RED);
    tft.print("Verlassen");
    tft.setTextColor(LCD_BLACK);
    tft.print(": Left + Enter + Right");
    tft.setCursor(69, 35);
    tft.print("Activate ");
    tft.setTextColor(LCD_RED);
    tft.print("p");
    tft.setTextColor(LCD_YELLOW);
    tft.print("a");
    tft.setTextColor(LCD_GREEN);
    tft.print("r");
    tft.setTextColor(LCD_BLUE);
    tft.print("t");
    tft.setTextColor(LCD_PINK);
    tft.print("y");
    tft.setTextColor(LCD_BLACK);
    tft.print(" mode: Page + Home");
    tft.setCursor(4, 45);
    tft.print("WitchEmpty ");
    tft.setTextColor(LCD_RED);
    tft.print("false");
    tft.setTextColor(LCD_BLACK);
    tft.print(": Panik + Start / ");
    tft.setTextColor(LCD_GREEN);
    tft.print("true");
    tft.setTextColor(LCD_BLACK);
    tft.print(": Left + Start");
    tft.setCursor(104, 55);
    tft.print("Lamptest: Comdisable");

    tft.setCursor(10, 70);
    tft.setTextSize(2);
    tft.print("Buttons:");

    tft.setCursor(140, 70);
    tft.print("Home");
    tft.fillRect(270, 68, 20, 20, LCD_RED);

    tft.setCursor(140, 90);
    tft.print("Page");
    tft.fillRect(270, 88, 20, 20, LCD_RED);

    tft.setCursor(140, 110);
    tft.print("Left");
    tft.fillRect(270, 108, 20, 20, LCD_RED);

    tft.setCursor(140, 130);
    tft.print("Enter");
    tft.fillRect(270, 128, 20, 20, LCD_RED);

    tft.setCursor(140, 150);
    tft.print("Right");
    tft.fillRect(270, 148, 20, 20, LCD_RED);

    tft.setCursor(140, 170);
    tft.print("Panic");
    tft.fillRect(270, 168, 20, 20, LCD_RED);

    tft.setCursor(140, 190);
    tft.print("Start");
    tft.fillRect(270, 188, 20, 20, LCD_RED);

    tft.setCursor(140, 210);
    tft.print("Comdisable");
    tft.fillRect(270, 208, 20, 20, LCD_RED);
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

void handlePageBtn()
{
    if (curPage == -4)
    {
        if (page_btn_debug == true)
        {
            return;
        }
        page_btn_debug = true;
        tft.fillRect(270, 88, 20, 20, LCD_GREEN);
        return;
    }
    if (curPage < -1 || curPage == 5)
    {
        curPage = -1;
        renderHome();
        return;
    }
    curPage += 1;
    renderButtonPage(curPage);
    return;
}

void handleHomeBtn()
{
    if (curPage == -4)
    {
        if (digitalRead(page_btn) == HIGH)
        {
            activatePartyMode();
        }
        if (home_btn_debug == true)
        {
            return;
        }
        home_btn_debug = true;
        tft.fillRect(270, 68, 20, 20, LCD_GREEN);
        return;
    }
    if (curPage == -1)
    {
        curPage = -2;
        renderSettingsPage();
        return;
    }
    curPage = -1;
    renderHome();
    return;
}

void handleNavRightBtn()
{
    if (curPage == -4)
    {
        if (digitalRead(nav_enter_btn) == HIGH && digitalRead(nav_left_btn) == HIGH)
        {
            // Make buttons glow again
            digitalWrite(start_green, HIGH);
            digitalWrite(crisis_red, HIGH);
            rxLEDState = false;
            txLEDState = false;
            curPage = -1;
            renderHome();
            return;
        }
        if (nav_left_btn_debug == true)
        {
            return;
        }
        nav_right_btn_debug = true;
        tft.fillRect(270, 148, 20, 20, LCD_GREEN);
        return;
    }
    handleSelection('m', 1);
    return;
}

void handleNavEnterBtn()
{
    if (curPage == -4)
    {
        if (nav_enter_btn_debug == true)
        {
            return;
        }
        nav_enter_btn_debug = true;
        tft.fillRect(270, 128, 20, 20, LCD_GREEN);
        return;
    }
    handleSelection('u');
    return;
}

void handleNavLeftBtn()
{
    if (curPage == -4)
    {
        if (nav_left_btn_debug == true)
        {
            return;
        }
        nav_left_btn_debug = true;
        tft.fillRect(270, 108, 20, 20, LCD_GREEN);
        return;
    }
    handleSelection('m', -1);
    return;
}

void handleComLedDisableBtn()
{
    if (curPage == -4)
    {
        if (com_led_disable_btn_debug == true)
        {
            return;
        }
        lampTest(true);
        com_led_disable_btn_debug = true;
        tft.fillRect(270, 208, 20, 20, LCD_GREEN);
        return;
    }
    if (comLEDDisabled == true)
    {
        comLEDDisabled = false;
    }
    else
    {
        comLEDDisabled = true;
    }
    return;
}

void handleStartBtn()
{
    if (curPage == -4)
    {
        if (digitalRead(crisis_btn) == HIGH)
        {
            witchEmpty = false;
            for (int i = 0; i <= 1; i++)
            {
                btnStatus[arealinking[i] - 'A'] = 'a';
                for (int j = 0; j <= 3; j++)
                {
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

                        setComLED("tx");
                        curPort.begin(9600);
                        curPort.print(arealinking[i]);
                        curPort.print('s');
                        break;
                    }
                }
            }
        }
        if (digitalRead(nav_left_btn) == HIGH)
        {
            witchEmpty = true;
            sent_area_one_blink = false;
            sent_area_two_blink = false;
        }
        if (start_btn_debug == true)
        {
            return;
        }
        start_btn_debug = true;
        tft.fillRect(270, 188, 20, 20, LCD_GREEN);
        return;
    }

    startShow();
}

void handleCrisisBtn()
{
    if (curPage == -4)
    {
        if (crisis_btn_debug == true)
        {
            return;
        }
        crisis_btn_debug = true;
        tft.fillRect(270, 168, 20, 20, LCD_GREEN);
        return;
    }

    if (controllerStatus == 'c')
    {
        resetStatus();
    }
    else
    {
        enableCrisis();
        ;
    }
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

void checkForBtnActive()
{
    if (digitalRead(page_btn) == HIGH && (page_btn_millis == 0 || millis() - page_btn_millis >= 500))
    {
        page_btn_millis = millis();
        handlePageBtn();
    }

    if (digitalRead(home_btn) == HIGH && (home_btn_millis == 0 || millis() - home_btn_millis >= 500))
    {
        home_btn_millis = millis();
        handleHomeBtn();
    }

    if (digitalRead(nav_right_btn) == HIGH && (nav_right_btn_millis == 0 || millis() - nav_right_btn_millis >= 500))
    {
        nav_right_btn_millis = millis();
        handleNavRightBtn();
    }

    if (digitalRead(nav_enter_btn) == HIGH && (nav_enter_btn_millis == 0 || millis() - nav_enter_btn_millis >= 500))
    {
        nav_enter_btn_millis = millis();
        handleNavEnterBtn();
    }

    if (digitalRead(nav_left_btn) == HIGH && (nav_left_btn_millis == 0 || millis() - nav_left_btn_millis >= 500))
    {
        nav_left_btn_millis = millis();
        handleNavLeftBtn();
    }

    if (digitalRead(com_led_disable_btn) == HIGH && (com_led_disable_btn_millis == 0 || millis() - com_led_disable_btn_millis >= 500))
    {
        com_led_disable_btn_millis = millis();
        handleComLedDisableBtn();
    }

    if (digitalRead(start_btn) == HIGH && (start_btn_millis == 0 || millis() - start_btn_millis >= 1000))
    {
        start_btn_millis = millis();
        handleStartBtn();
    }

    if (digitalRead(crisis_btn) == HIGH && (crisis_btn_millis == 0 || millis() - crisis_btn_millis >= 1000))
    {
        crisis_btn_millis = millis();
        handleCrisisBtn();
    }

    // Debug page handling

    if (curPage == -4)
    {
        if (digitalRead(page_btn) == LOW)
        {
            if (page_btn_debug == true)
            {
                page_btn_debug = false;
                tft.fillRect(270, 88, 20, 20, LCD_RED);
            }
        }

        if (digitalRead(home_btn) == LOW)
        {
            if (home_btn_debug == true)
            {
                home_btn_debug = false;
                tft.fillRect(270, 68, 20, 20, LCD_RED);
            }
        }

        if (digitalRead(nav_right_btn) == LOW)
        {
            if (nav_right_btn_debug == true)
            {
                nav_right_btn_debug = false;
                tft.fillRect(270, 148, 20, 20, LCD_RED);
            }
        }

        if (digitalRead(nav_enter_btn) == LOW)
        {
            if (nav_enter_btn_debug == true)
            {
                nav_enter_btn_debug = false;
                tft.fillRect(270, 128, 20, 20, LCD_RED);
            }
        }

        if (digitalRead(nav_left_btn) == LOW)
        {
            if (nav_left_btn_debug == true)
            {
                nav_left_btn_debug = false;
                tft.fillRect(270, 108, 20, 20, LCD_RED);
            }
        }

        if (digitalRead(com_led_disable_btn) == LOW)
        {
            if (com_led_disable_btn_debug == true)
            {
                com_led_disable_btn_debug = false;
                tft.fillRect(270, 208, 20, 20, LCD_RED);
                lampTest(false);
            }
        }

        if (digitalRead(start_btn) == LOW)
        {
            if (start_btn_debug == true)
            {
                start_btn_debug = false;
                tft.fillRect(270, 188, 20, 20, LCD_RED);
            }
        }

        if (digitalRead(crisis_btn) == LOW)
        {
            if (crisis_btn_debug == true)
            {
                crisis_btn_debug = false;
                tft.fillRect(270, 168, 20, 20, LCD_RED);
            }
        }
    }
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

void statusCheck()
{
    if (millis() - timeSinceReset <= minTimeSinceReset)
    {
        return;
    }
    String allIds = "";
    bool hasFailure = false;
    bool hasCrisis = false;
    int areaTwoBtns = 0;
    int areaTwoBypassBtns = 0;
    for (int i = 0; i <= 3; i++)
    {
        allIds = allIds + String(portids[i]);
    }
    for (int i = 0; i <= (allIds.length() - 1); i++)
    {
        char gotStatus = btnStatus[allIds.charAt(i) - 'A'];
        if (gotStatus == 'c' && millis() - lastCrisisDisable >= minCrisisDisable)
        {
            hasCrisis = true;
            break;
        }
        else if (gotStatus == 'd' || gotStatus == 'e')
        {
            hasFailure = true;
        }
    }

    if (btnStatus[arealinking[0] - 'A'] == 'n')
    {
        area_one_reconnect = true;
    }
    else if (btnStatus[arealinking[0] - 'A'] != 'n' && area_one_reconnect == true)
    {
        sent_area_one_blink = false;
    }
    if (btnStatus[arealinking[1] - 'A'] == 'n')
    {
        area_two_reconnect = true;
    }
    else if (btnStatus[arealinking[1] - 'A'] != 'n' && area_two_reconnect == true)
    {
        sent_area_two_blink = false;
    }

    if ((btnStatus[arealinking[2] - 'A'] == 'n' && btnBypass[2] == false) ||
        (btnStatus[arealinking[3] - 'A'] == 'n' && btnBypass[3] == false) ||
        (btnStatus[arealinking[4] - 'A'] == 'n' && btnBypass[4] == false))
    {
        btn_pressed_reconnect = true;
    }
    else if ((btnStatus[arealinking[2] - 'A'] != 'n' || btnBypass[2] == true) &&
             (btnStatus[arealinking[3] - 'A'] != 'n' || btnBypass[2] == true) &&
             (btnStatus[arealinking[4] - 'A'] != 'n' || btnBypass[2] == true) &&
             btn_pressed_reconnect == true)
    {
        sent_btn_pressed_blink = false;
    }

    if (btnStatus[arealinking[2] - 'A'] == 'b')
    {
        areaTwoBtns += 1;
    }
    if (btnBypass[2] == true)
    {
        areaTwoBypassBtns += 1;
    }

    if (btnStatus[arealinking[3] - 'A'] == 'b')
    {
        areaTwoBtns += 1;
    }
    if (btnBypass[3] == true)
    {
        areaTwoBypassBtns += 1;
    }

    if (btnStatus[arealinking[4] - 'A'] == 'b')
    {
        areaTwoBtns += 1;
    }
    if (btnBypass[4] == true)
    {
        areaTwoBypassBtns += 1;
    }

    if (btnStatus[arealinking[5] - 'A'] == 'b')
    {
        areaTwoBtns += 1;
    }
    if (btnBypass[5] == true)
    {
        areaTwoBypassBtns += 1;
    }

    if (hasCrisis == false && controllerStatus != 'c')
    {
        // Area 1

        if (btnStatus[arealinking[0] - 'A'] == 'b' && witchEmpty == true && millis() - witch_status_sent_millis >= 2000 && btnStatus[arealinking[1] - 'A'] != 'b' && sent_area_two_blink == false)
        {
            sent_area_two_blink = true;
            witch_status_sent_millis = millis();
            for (int i = 0; i <= 3; i++)
            {
                if (portids[i].indexOf(arealinking[1]) != -1)
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
                    curPort.print(arealinking[1]);
                    curPort.print('b');
                    break;
                }
            }
        }
        else if (btnStatus[arealinking[0] - 'A'] != 'b' && witchEmpty == true && millis() - witch_status_sent_millis >= 2000 && btnStatus[arealinking[1] - 'A'] != 'b' && sent_area_one_blink == false)
        {
            witch_status_sent_millis = millis();
            sent_area_one_blink = true;
            sent_area_two_blink = false;
            for (int i = 0; i <= 3; i++)
            {
                if (portids[i].indexOf(arealinking[0]) != -1)
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
                    curPort.print(arealinking[0]);
                    curPort.print('b');
                    break;
                }
            }
        }

        if (btnStatus[arealinking[0] - 'A'] == 'b' && btnStatus[arealinking[1] - 'A'] == 'b' && witchEmpty == true)
        {
            if (witch_wait_millis == 0)
            {
                witch_wait_millis = millis();
            }

            if (millis() - witch_wait_millis >= 10000)
            {
                witch_wait_millis = 0;
                witchEmpty = false;
                sent_area_one_blink = false;
                sent_area_two_blink = false;
                for (int i = 0; i <= 1; i++)
                {
                    btnStatus[arealinking[i] - 'A'] = 'a';
                    for (int j = 0; j <= 3; j++)
                    {
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

                            setComLED("tx");
                            curPort.begin(9600);
                            curPort.print(arealinking[i]);
                            curPort.print('s');
                            break;
                        }
                    }
                }
            }
        }

        // Area 2

        if ((areaTwoBtns + areaTwoBypassBtns) == 4)
        {
            startShow();
        }
        else if (areaTwoBtns >= 1 && areaTwoBtns <= 3 && millis() - lastBtnSentAction >= minLastBtnSentAction && sent_btn_pressed_blink == false)
        {
            sent_btn_pressed_blink = true;
            lastBtnSentAction = millis();
            controllerStatus = 'b';
            for (int i = 2; i <= 5; i++)
            {
                for (int j = 0; j <= 3; j++)
                {
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

                        setComLED("tx");
                        curPort.begin(9600);
                        curPort.print(arealinking[i]);
                        curPort.print('b');
                        break;
                    }
                }
            }
        }
    }

    if (hasFailure == true && controllerStatus != 'c')
    {
        controllerStatus = 'f';
    }
    else if (hasFailure == false && controllerStatus == 'f')
    {
        controllerStatus = 'a';
    }

    if (hasCrisis == true)
    {
        enableCrisis();
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

    if (minString.charAt(2) != NULL && minString.charAt(0) != digitZero)
    {
        digitZero = minString.charAt(0);
        displayClock(0, minString.charAt(0));
        minString.remove(0, 1);
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

    if (minString == "30" && sent_stop_playing == false)
    {
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