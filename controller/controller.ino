#include <SoftwareSerial.h>
#include <Elegoo_GFX.h>
#include <Elegoo_TFTLCD.h>

// LCD Pins
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

// LCD Colors

#define	LCD_BLACK   0x0000
#define	LCD_BLUE    0x001F
#define	LCD_RED     0xF800
#define	LCD_GREEN   0x07E0
#define LCD_CYAN    0x07FF
#define LCD_MAGENTA 0xF81F
#define LCD_YELLOW  0xFFE0
#define LCD_WHITE   0xFFFF

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
int crisis_red = 37; // NO PWM
int crisis_green = 35; // NO PWM

// Led pins

int rx_led = 28;
int tx_led = 30;

int status_led_red = 45;
int status_led_green = 44;
int status_led_blue = 46;

/*
 *  
 *  SoftwareSerial Port handling
 *
 *  Values must be under the same index
 * 
*/

SoftwareSerial serialports[] = {
    SoftwareSerial(A10,51), // Dose Links, Links
    SoftwareSerial(A9,53),  // Dose Links, Rechts
    SoftwareSerial(A8,13),  // Dose Rechts, Links
    SoftwareSerial(A11,52)  // Dose Rechts, Rechts
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

String portids[] = {};



/*
 *
 *  Button status tracking
 * 
 *  Status at index of int of ID - 65
 *  e.g. A = 0, B = 1 , etc.
 * 
*/

char btnStatus[] = {};



// Bitmaps for logo
extern uint8_t logobody[];
extern uint8_t logoeye[];

// Tft display
Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

void setup() {
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
    tft.begin(identifier);
    tft.setRotation(1);

    display_startup();
}

void display_startup() {

    // Fill screen with Black
    tft.fillScreen(LCD_BLACK);

    // Draw Logo body
    tft.drawBitmap(110,10,logobody,110,159,LCD_WHITE);

    // Draw Left eye
    tft.drawBitmap(149,53,logoeye,6,6,LCD_BLUE);

    // Draw Right eye
    tft.drawBitmap(179,53,logoeye,6,6,LCD_MAGENTA);

    // Text
    tft.setCursor(100,180);
    tft.setTextSize(5);
    tft.setTextColor(LCD_WHITE);
    tft.print("HWHS Showcontroller");

    return;
}

void loop() {

}