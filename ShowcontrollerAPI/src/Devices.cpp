#include "Arduino.h"
#include "Devices.h"

Area::Area(
    int id, String name, 
    char linked_button_id, AreaType type,
    int switcher_linked_area = NULL
) {
    ID = id;
    Linked_Button_ID = linked_button_id;
    Type = type;
    Switcher_Linked_Area_ID = switcher_linked_area;
    Name = name;
    return;
}

bool Area::retrieveLinkedButtonDevice(DeviceList device_list) {
    Device new_device = device_list.findDevice(Linked_Button_ID, DeviceType::BUTTON);
    if (device_list.Size <= 0) {return false;}
    Linked_Button_Device = new_device;
    return true;
}
