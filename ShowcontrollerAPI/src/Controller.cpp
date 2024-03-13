#include "Arduino.h"
#include "Controller.h"

ControllerConfig::ControllerConfig(Area *areas, int lcd_cs, int lcd_cs, int lcd_wr,
            int lcd_rd, int lcd_reset, int start_button_pin,
            int crisis_button_pin, int page_button_pin, int home_button_pin,
            int nav_left_button_pin, int nav_enter_button_pin, int nav_right_button_pin,
            int com_led_disable_button_pin, int start_button_blue_pin, int start_button_red_pin,
            int start_button_green_pin, int crisis_button_red_pin, int crisis_button_green_pin,
            int tx_led_pin, int rx_led_pin, int status_led_red_pin,
            int status_led_green_pin, int status_led_blue_pin) {
                this->Areas = areas;
                this->LCD_CS = lcd_cs;
                this->LCD_CD = lcd_cd;
                this->LCD_WR = lcd_wr;
                this->LCD_RD = lcd_rd;
                this->LCD_RESET = lcd_reset;
                this->Start_Button_Pin = start_button_pin;
                this->Crisis_Button_Pin = crisis_button_pin;
                this->Page_Button_Pin = page_button_pin;
                this->Home_Button_Pin = home_button_pin;
                this->Nav_Left_Button_Pin = nav_left_button_pin;
                this->Nav_Enter_Button_Pin = nav_enter_button_pin;
                this->Nav_Right_Button_Pin = nav_right_button_pin;
                this->Com_Led_Disable_Button_Pin = com_led_disable_button_pin;
                this->Start_Button_Blue_Pin = start_button_blue_pin;
                this->Start_Button_Red_Pin = start_button_red_pin;
                this->Start_Button_Green_Pin = start_button_green_pin;
                this->Crisis_Button_Red_Pin = crisis_button_red_pin;
                this->Crisis_Button_Green_Pin = crisis_button_green_pin;
                this->TX_Led_Pin = tx_led_pin;
                this->RX_Led_Pin = rx_led_pin;
                this->Status_Led_Red_Pin = status_led_red_pin;
                this->Status_Led_Green_Pin = status_led_green_pin;
                this->Status_Led_Blue_Pin = status_led_blue_pin;
                return;
            }

Color::Color(const int red_color, const int green_color, const int blue_color) {
    if (!(red_color != NULL && red_color >= 0 && red_color <= 255) || !(green_color != NULL && green_color >= 0 && green_color <= 255) || !(blue_color != NULL && blue_color >= 0 && blue_color <= 255)) {
        // Error
        this->red = -1;
        this->green = -1;
        this->blue = -1;
        return;   
    }
    this->red = red_color;
    this->green = green_color;
    this->blue = blue_color;
}