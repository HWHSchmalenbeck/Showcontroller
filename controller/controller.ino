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

int rx_led = 28;
int tx_led = 30;

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

String areaname[] = {"Eingang", "Hexe 1", "Hexe 2", "Labor", "Friedhof", "Ausgang"};

char arealinking[] = {'A', 'B', 'C', 'D', 'E', 'F'};

/*
 *
 *  SoftwareSerial Port handling
 *
 *  Values must be under the same index
 *
 */

SoftwareSerial serialports[] = {
    SoftwareSerial(A10, 51), // Dose Links, Links
    SoftwareSerial(A9, 53),  // Dose Links, Rechts
    SoftwareSerial(A8, 13),  // Dose Rechts, Links
    SoftwareSerial(A11, 52)  // Dose Rechts, Rechts
};

/*
 *
 *  Port type
 *
 *  B -> Button (One id)
 *  S -> Switch (String of ids)
 *
 */
char porttype[] = {};

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

char portids[] = {};

/*
 *
 *  Button status tracking
 *
 *  Status at index of int of ID - 65
 *  e.g. A = 0, B = 1 , etc.
 *
 */

char btnStatus[] = {};

bool btnBypass[] = {};

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

// Tft display
Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

void setup()
{
    // Begin Serial
    Serial.begin(9600);

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
    delay(500);
    btnStatus[arealinking[0]] = 'a';
    btnStatus[arealinking[1]] = 'b';
    btnStatus[arealinking[2]] = 'c';
    btnStatus[arealinking[3]] = 'd';
    btnStatus[arealinking[4]] = 'e';

    // Make buttons glow

    //digitalWrite(start_green, HIGH);
    //digitalWrite(crisis_red, HIGH);

    renderHome();
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

uint16_t getcolor(char status)
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
            tft.drawRect(59, 69, 202, 42, selectionColor);
            return;
        case 2:
            tft.drawRect(59, 119, 202, 42, selectionColor);
            return;
        case 3:
            tft.drawRect(59, 169, 202, 42, selectionColor);
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

void handleSelection(char act, int dir = 0)
{
    int btnPageSelectMax = 3;
    int homePageSelectMax = 6;
    int settingsPageSelectMax = 3;

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
                // ToDo: Add Rediscover
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

void renderHome()
{
    handleSelection('c');
    curPage = -1;
    // Fill screen with White
    tft.fillScreen(LCD_WHITE);

    uint16_t areacolor;
    // Top Left Status
    areacolor = getcolor(btnStatus[arealinking[0]]);
    tft.fillRect(15, 20, 26, 26, areacolor);
    tft.setCursor(52, 26);
    tft.setTextSize(2);
    tft.setTextColor(LCD_BLACK);
    tft.print(areaname[0]);

    // Middle Left Status
    areacolor = getcolor(btnStatus[arealinking[2]]);
    tft.fillRect(15, 76, 26, 26, areacolor);
    tft.setCursor(52, 82);
    tft.setTextSize(2);
    tft.setTextColor(LCD_BLACK);
    tft.print(areaname[2]);

    // Bottom Left Status
    areacolor = getcolor(btnStatus[arealinking[4]]);
    tft.fillRect(15, 132, 26, 26, areacolor);
    tft.setCursor(52, 138);
    tft.setTextSize(2);
    tft.setTextColor(LCD_BLACK);
    tft.print(areaname[4]);

    // Top Right Status
    areacolor = getcolor(btnStatus[arealinking[1]]);
    tft.fillRect(170, 20, 26, 26, areacolor);
    tft.setCursor(207, 26);
    tft.setTextSize(2);
    tft.setTextColor(LCD_BLACK);
    tft.print(areaname[1]);

    // Middle Right Status
    areacolor = getcolor(btnStatus[arealinking[3]]);
    tft.fillRect(170, 76, 26, 26, areacolor);
    tft.setCursor(207, 82);
    tft.setTextSize(2);
    tft.setTextColor(LCD_BLACK);
    tft.print(areaname[3]);

    // Bottom Right Status
    areacolor = getcolor(btnStatus[arealinking[5]]);
    tft.fillRect(170, 132, 26, 26, areacolor);
    tft.setCursor(207, 138);
    tft.setTextSize(2);
    tft.setTextColor(LCD_BLACK);
    tft.print(areaname[5]);

    // Show Info Line
    tft.drawFastHLine(0, 190, 360, LCD_BLACK);
    tft.drawFastHLine(0, 191, 360, LCD_BLACK);
    tft.drawFastHLine(0, 192, 360, LCD_BLACK);

    // Show Status
    tft.setCursor(15, 210);
    tft.print("Show active");

    // Show Run Duration
    tft.setCursor(240, 210);
    tft.print("03:37");

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
    tft.print(btnStatus[arealinking[number]]);

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

    tft.drawRect(60, 70, 200, 40, LCD_BLACK);
    tft.setCursor(118, 82);
    tft.print("Credits");

    tft.drawRect(60, 120, 200, 40, LCD_BLACK);
    tft.setCursor(131, 132);
    tft.print("Debug");

    tft.drawRect(60, 170, 200, 40, LCD_BLACK);
    tft.setCursor(97, 182);
    tft.print("Re-Discover");
    return;
}

void renderCreditsPage()
{
    handleSelection('c');
    tft.fillScreen(LCD_WHITE);
    tft.drawRect(5, 5, 50, 50, LCD_BLACK);

    tft.setCursor(75, 14);
    tft.setTextColor(LCD_BLACK);
    tft.setTextSize(2);
    tft.print("HWHS Showcontroller");
    tft.setCursor(145, 34);
    tft.print("Credits");

    tft.setCursor(10, 70);
    tft.print("Coding:");

    tft.setCursor(170, 70);
    tft.print("Lois");

    tft.setCursor(10, 110);
    tft.print("Konstruktion:");

    tft.setCursor(170, 110);
    tft.print("Valentin");

    tft.setCursor(170, 130);
    tft.print("Lois");

    tft.setCursor(170, 150);
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
    tft.setCursor(105, 10);
    tft.setTextSize(2);
    tft.setTextColor(LCD_BLACK);
    tft.print("Debug Page");

    tft.setCursor(60, 30);
    tft.setTextSize(1);
    tft.print("Zum Verlassen: Left + Right + Enter");
    tft.setCursor(104, 40);
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
            //digitalWrite(start_green, HIGH);
            //digitalWrite(crisis_red, HIGH);
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
    // Disable the com leds
    return;
}

void handleStartBtn()
{
    if (curPage == -4)
    {
        if (start_btn_debug == true)
        {
            return;
        }
        start_btn_debug = true;
        tft.fillRect(270, 188, 20, 20, LCD_GREEN);
        return;
    }

    // Start btn function
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

    // Panic button function
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

void loop()
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

    if (digitalRead(start_btn) == HIGH && (start_btn_millis == 0 || millis() - start_btn_millis >= 500))
    {
        start_btn_millis = millis();
        handleStartBtn();
    }

    if (digitalRead(crisis_btn) == HIGH && (crisis_btn_millis == 0 || millis() - crisis_btn_millis >= 500))
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
}