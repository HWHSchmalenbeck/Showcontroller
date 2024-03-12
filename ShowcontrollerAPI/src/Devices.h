#ifndef Devices_h
#define Devices_h

#include "Arduino.h"

// Enums

enum DeviceType {
    BUTTON,
    SWITCH,
    ANIMATRONIC
};

enum ButtonStatus {
    OKAY,
    ACTIVATED,
    RUNCRISIS,
    ERRORCONST,
    ERRORNEVER
};

enum AreaType {
    SHOW_ACTIVATOR,
    SWITCHER
};

enum ActivationState {
    INACTIVE,
    ACTIVE
};

// Device Classes

class Device {
    public:
        DeviceType Type;
        char ID;
        int Port_Number;
        ButtonStatus Status;
        ActivationState Bypass;
        ActivationState Manual_Activation;
        char exportButtonStatus();
        void changeBypass(ActivationState new_state);
        void changeManualActivation(ActivationState new_state);
        char exportDeviceType();
};

// DeviceList Classes

class DeviceList {
    public:
        int Size;
        void addDevice(Device device);
        void removeDevice(Device device, char id = NULL);
        Device findDevice(char id, DeviceType type);
    
    private:
        Device *_Device_List[20];
        char _ID_List[20];
};

// Area Class

class Area {
    public:
        int ID;
        String Name;
        char Linked_Button_ID;
        Device Linked_Button_Device;
        AreaType Type;
        int Switcher_Linked_Area_ID;
        void changeLinkedButtonDevice(Device new_button_device);
        Area() {};
        Area(
            int id, String name, 
            char linked_button_id, AreaType type,
            int switcher_linked_area = NULL
        );
        bool retrieveLinkedButtonDevice(DeviceList device_list);
};

#endif