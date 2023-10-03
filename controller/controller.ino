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

// Bitmaps for logo
extern uint8_t logobody[];
extern uint8_t logoeye[];

// Tft display
Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

void setup()
{
    // Begin Serial
    Serial.begin(9600);

    // DEBUG
    btnStatus['A'] = 'a';
    btnStatus['B'] = 'b';
    btnStatus['C'] = 'c';
    btnStatus['D'] = 'd';
    btnStatus['E'] = 'e';

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
    if (identifier == 0x0101) {
        identifier = 0x9341;
    }
    tft.begin(identifier);
    tft.setRotation(3);
    tft.fillScreen(LCD_BLACK);
    display_startup();
    delay(500);
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

void renderHome()
{
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
    if (btnBypass[arealinking[number]] == true) {
        tft.fillRect(20, 187, 25, 20, LCD_GREEN);
    } else {
        tft.fillRect(20, 187, 25, 20, LCD_RED);
    }
    tft.setCursor(55, 190);
    tft.print("Bypass");

    tft.drawRect(165, 160, 150, 75, LCD_BLACK);
    tft.setCursor(192, 190);
    tft.print("Freigabe");

    return;
}

void loop()
{

}