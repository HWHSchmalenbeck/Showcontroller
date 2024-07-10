#include <Keyboard.h>
#include <SoftwareSerial.h>

int plug1 = 5;
int plug2 = 6;

SoftwareSerial comport(11,10);

void setup() {
    digitalWrite(plug1, HIGH);
    digitalWrite(plug2, HIGH);
    comport.begin(9600);
    Keyboard.begin(KeyboardLayout_de_DE);

    pinMode(plug1, OUTPUT);
    pinMode(plug2, OUTPUT);
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
    digitalWrite(plug1, HIGH);
    delay(100);
    digitalWrite(plug2, HIGH);
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

    digitalWrite(plug1, LOW);
    delay(100);
    digitalWrite(plug2, LOW);
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