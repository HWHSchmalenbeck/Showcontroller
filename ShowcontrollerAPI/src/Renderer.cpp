#include "Arduino.h"
#include "Renderer.h"

Renderer::Renderer(int LCD_CS, int LCD_CD, int LCD_WR, int LCD_RD, int LCD_RESET, Clock clock) {
    _LCD_CS = LCD_CS;
    _LCD_CD = LCD_CD;
    _LCD_WR = LCD_WR;
    _LCD_RD = LCD_RD;
    _LCD_RESET = LCD_RESET;
    _clock = clock;
    return;
}

void Renderer::begin() {
    Elegoo_TFTLCD tft(_LCD_CS,_LCD_CD,_LCD_WR,_LCD_RD,_LCD_RESET);

    tft.reset();
    if (tft.readID() == 0x0101) {
        tft.begin(0x9341);
    } else {
        tft.begin(tft.readID());
    }
    tft.setRotation(3);
    tft.fillScreen(LCD_BLACK);
}