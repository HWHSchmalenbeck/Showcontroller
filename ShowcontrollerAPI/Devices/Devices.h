#ifndef Devices_h
#define Devices_h

#include "Arduino.h"

// Enums

enum DeviceType {
    BUTTON,
    SWITCH,
    ANIMATRONIC
}

enum ButtonStatus {
    OKAY,
    ACTIVATED,
    CRISIS,
    ERRORCONST,
    ERRORNEVER
}

enum AreaType {
    SHOW_ACTIVATOR,
    SWITCHER
}

enum ActivationState {
    INACTIVE,
    ACTIVE
}

// Area Class

class Area {
    public:
        char[16] Name;
        ButtonDevice Linked_Button_Device;
        AreaType Type;
        ButtonDevice Switcher_Linked_Button_Device;
        void changeLinkedButtonDevice(ButtonDevice New_Button_Device);
}

// Device Classes

class Device {
    public:
        DeviceType Type;
        char ID;
        int Port_Number;
        char exportDeviceType();
}

class ButtonDevice : Device {
    public:
        ButtonStatus Status;
        ActivationState Bypass;
        ActivationState Manual_Activation;
        char exportButtonStatus();
        void changeBypass(ActivationState New_State);
        void changeManualActivation(ActivationState New_State);
}

class SwitchDevice : Device {
    public:
        void nothing();
}

class AnimatronicDevice : Device {
    public:
        void nothing();

}

// DeviceList Classes

class ButtonDeviceList {
    public:
        int Size;
        void addDevice(ButtonDevice device);
        void removeDevice(ButtonDevice device = NULL, char ID = NULL);
        ButtonDevice findDevice(char ID);
    
    private:
        ButtonDevice[20] Device_List;
        char[20] ID_List;
}

class SwitchDeviceList {
    public:
        int Size;
        void addDevice(SwitchDevice device);
        void removeDevice(SwitchDevice device = NULL, char ID = NULL);
        SwitchDevice findDevice(char ID);

    private:
        SwitchDevice[4] Device_List;
        char[4] ID_List;
}

class AnimatronicDeviceList {
    public:
        int Size;
        void addDevice(AnimatronicDevice device);
        void removeDevice(AnimatronicDevice device);
        AnimatronicDevice findDevice(char ID);
    
    private:
        AnimatronicDevice[20] Device_List;
        char[20] ID_List;
}


#endif