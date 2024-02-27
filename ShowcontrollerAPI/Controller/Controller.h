#ifndef Controller_h
#define Controller_h

#include "Arduino.h"
#include "Devices.h"

enum ControllerStatus {
    IDLE,
    RUNNING,
    CRISIS,
    DISCOVERY,
    FAILURE
}

struct Color {
    int red;
    int green;
    int blue;
};

struct Config {
    Area[20] Areas,

    int Start_Button_Pin,
    int Crisis_Button_Pin,
    int Page_Button_Pin,
    int Home_Button_Pin,
    int Nav_Left_Button_Pin,
    int Nav_Enter_Button_Pin,
    int Nav_Right_Button_Pin,
    int Com_Led_Disable_Button_Pin,

    int Start_Button_Blue_Pin,
    int Start_Button_Red_Pin,
    int Start_Button_Green_Pin,
    int Crisis_Button_Red_Pin,
    int Crisis_Button_Green_Pin,

    int TX_Led_Pin,
    int RX_Led_Pin,
    int Status_Led_Red_Pin,
    int Status_Led_Green_Pin,
    int Status_Led_Blue_Pin
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
        Config _config; 
}

class Show {
    public:
        unsigned long Show_Running_Millis;
        unsigned long getRunningMillis();
}

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
        Config _config;
}

#endif