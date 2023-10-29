#include <Keyboard.h>
#include <SoftwareSerial.h>

SoftwareSerial comport(11,10);

void setup() {
    comport.begin(9600);
    Keyboard.begin(KeyboardLayout_de_DE);
}

void startShow() {
    Keyboard.write(KEY_KP_0);
    delay(500);
    Keyboard.write(KEY_RETURN);
    delay(500);
    Keyboard.write(' ');
    return;
}

void stopRunning() {
    Keyboard.write(KEY_KP_0);
    return;
}

void runPanic() {
    Keyboard.write(KEY_KP_0);
    delay(500);
    Keyboard.write('#');
    delay(500);
    Keyboard.print("1000");
    delay(500);
    Keyboard.write(KEY_RETURN);
    delay(500);
    Keyboard.write(' ');
    return;
}

void loop() {
    if (comport.available()) {
        char readInst = comport.read();

        if (readInst == 's') {
            startShow();
        } else if (readInst == 'p') {
            runPanic();
        } else if (readInst == 'r') {
            stopRunning();
        }
    }
}