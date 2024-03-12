#ifndef Renderer_h
#define Renderer_h

#include "Arduino.h"
#include "Devices.h"
#include <Elegoo_GFX.h>
#include <Elegoo_TFTLCD.h>

// Bitmaps for logo
extern uint8_t logobody[];
extern uint8_t logoeye[];
extern uint8_t heart[];
extern uint8_t heartout[];
extern uint8_t otto_small[];
extern uint8_t eye_small[];

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

uint16_t Status_A_Color = LCD_YELLOW;
uint16_t Status_B_Color = LCD_GREEN;
uint16_t Status_C_Color = LCD_PINK;
uint16_t Status_D_Color = LCD_BLUE;
uint16_t Status_E_Color = LCD_ORANGE;
uint16_t Status_N_Color = LCD_BLACK;

class Clock {
    public:
        char Digits[5];
        char getDigit(int digit);
};

class Renderer {
    public:
        int Current_Selection;
        int Current_Page;
        Elegoo_TFTLCD tft;
        Renderer(int LCD_CS, int LCD_CD, 
            int LCD_WR, int LCD_RD, 
            int LCD_RESET, Clock clock);
        void begin();
        void displayStartup();
        void renderSelection(int id, bool negative = false);
        void displayClock(int digit);
        void displayStatus();
        void renderHomeStatus();
        void renderHome();
        void renderButtonPage();
        void renderSettingsPage();
        void renderCreditsPage();
        void renderDebugPage();
        void handleDebugPage();     

    private:
        int _LCD_CS;
        int _LCD_CD;
        int _LCD_WR;
        int _LCD_RD;
        int _LCD_RESET;
        Clock _clock;
        uint16_t _getLCDColor(char status);
};

#endif