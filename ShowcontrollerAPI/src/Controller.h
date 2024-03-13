#ifndef Controller_h
#define Controller_h

#include "Arduino.h"
#include "Devices.h"
#include "Renderer.h"
#include "Communicator.h"

enum ControllerStatus {
    IDLE,
    RUNNING,
    CRISIS,
    DISCOVERY,
    FAILURE
};

class Color {
    public:
        int red;
        int green;
        int blue;
        Color(int red_value, int green_value, int blue_value);
};

class ControllerConfig {
    public:
        Area *Areas[20];

        int LCD_CS;
        int LCD_CD; 
        int LCD_WR;
        int LCD_RD;
        int LCD_RESET;

        int Start_Button_Pin;
        int Crisis_Button_Pin;
        int Page_Button_Pin;
        int Home_Button_Pin;
        int Nav_Left_Button_Pin;
        int Nav_Enter_Button_Pin;
        int Nav_Right_Button_Pin;
        int Com_Led_Disable_Button_Pin;

        int Start_Button_Blue_Pin;
        int Start_Button_Red_Pin;
        int Start_Button_Green_Pin;
        int Crisis_Button_Red_Pin;
        int Crisis_Button_Green_Pin;

        int TX_Led_Pin;
        int RX_Led_Pin;
        int Status_Led_Red_Pin;
        int Status_Led_Green_Pin;
        int Status_Led_Blue_Pin;

        ControllerConfig(
            Area *areas, int lcd_cs, int lcd_cs, int lcd_wr,
            int lcd_rd, int lcd_reset, int start_button_pin,
            int crisis_button_pin, int page_button_pin, int home_button_pin,
            int nav_left_button_pin, int nav_enter_button_pin, int nav_right_button_pin,
            int com_led_disable_button_pin, int start_button_blue_pin, int start_button_red_pin,
            int start_button_green_pin, int crisis_button_red_pin, int crisis_button_green_pin,
            int tx_led_pin, int rx_led_pin, int status_led_red_pin,
            int status_led_green_pin, int status_led_blue_pin
        );
};

class Show {
    public:
        unsigned long Show_Running_Millis;
        unsigned long getRunningMillis();
};

class ButtonHandler {
    public:
        ButtonHandler(Config config);
        void handlePageButton();
        void handleHomeButton();
        void handleNavRightButton();
        void handleNavEnterButton();
        void handleNavLeftButton();
        void handleComLedDisableButton();
        void handleStartButton();
        void handleCrisisButton();
        void checkForButtonActive();
    
    private:
        Config _Config;
};

class Controller {
    public:
        int Port_Count;
        ControllerStatus Controller_Status;
        Controller(Config config);
        void activatePartyMode();
        void lampTest(bool mode);

    private:
        const int STATUS_RED[3] = {255,0,0};
        const int STATUS_ORANGE[3] = {255,50,0};
        const int STATUS_YELLOW[3] = {255,255,0};
        const int STATUS_GREEN[3] = {0,255,0};
        const int STATUS_BLUE[3] = {0,0,255};
        const int STATUS_PINK[3] = {255,20,147};
        const int STATUS_BLACK[3] = {0,0,0};
        Config _Config;
        Show _Show;
        ButtonHandler _Button_Handler;
        Communicator _Communicator;
        DeviceList _Device_List;
        Renderer _Renderer;
};

#endif