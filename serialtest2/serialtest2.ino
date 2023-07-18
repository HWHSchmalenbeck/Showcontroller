#include <SoftwareSerial.h>

SoftwareSerial test(10,11);

void setup() {
    Serial.begin(9600);
    test.begin(9600);
}

void loop() {
    if (test.available()) {
        char read = test.read();
        if (read == 'A') {
            test.print('B');
        }
    }
}