#include "Arduino.h"
#include "Devices.h"

Area::Area(
    int id, char[16] name, 
    char linked_button_id, AreaType type,
    int switcher_linked_area = NULL
) {
    static_assert(type == SWITCHER && switcher_linked_area == NULL, "ERROR: Switcher Area must have linked_area defined.");
    ID = id;
    Name = name;
    Linked_Button_ID = linked_button_id;
    Type = type;
    Switcher_Linked_Area_ID = switcher_linked_area;
    return;
}

bool Area::retrieveLinkedButtonDevice(DeviceList device_list) {
    Device new_device = device_list.findDevice(Linked_Button_ID, DeviceType::BUTTON);
    if (new_device == NULL) {return false;}
    Linked_Button_Device = new_device;
    return true;
}
