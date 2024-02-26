#ifndef Controller_h
#define Controller_h

#include "Arduino.h"

enum ControllerStatus {
    IDLE,
    RUNNING,
    CRISIS,
    DISCOVERY,
    FAILURE
}

#endif