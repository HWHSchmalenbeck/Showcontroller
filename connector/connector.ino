//#include <Keyboard.h>
#include <SoftwareSerial.h>
#include <Ethernet.h>
#include <AppleMIDI.h>

int plug1 = 5;
int plug2 = 6;

int beeper = 8;

int statusLed = 9;
int currentBrightness = 255;
int dir = 1;

int numBlink = 0;

unsigned long statusLedMillis = 0;

String ignoring = "";

byte mac[] = {
  0x42, 0x06, 0x91, 0x33, 0x75, 0x85
};

int8_t isConnected = 0;

int ethernetStatus = NULL;

unsigned long maintainMillis = 0;

int status = 0;

int wrongInst = 0;
bool sentCurWrongInst = true;
unsigned long wrongInstResetTimer = 0;
int wrongInstResetThreshold = 300000;

APPLEMIDI_CREATE_DEFAULTSESSION_INSTANCE();

SoftwareSerial comport(3, 2);

void setup() {
    Serial.begin(9600);
    digitalWrite(plug1, HIGH);
    digitalWrite(plug2, HIGH);
    comport.begin(9600);
    //Keyboard.begin(KeyboardLayout_de_DE);

    pinMode(plug1, OUTPUT);
    pinMode(plug2, OUTPUT);
    pinMode(statusLed, OUTPUT);
    pinMode(beeper, OUTPUT);

    ethernetStatus = Ethernet.begin(mac);

    if (ethernetStatus != 0) {
        maintainMillis = millis();

        MIDI.begin();
    }

    AppleMIDI
  .setHandleConnected([](const APPLEMIDI_NAMESPACE::ssrc_t & ssrc, const char* name) {
    isConnected++;
    Serial.println("Connected to session" + String(ssrc) + String(name));
  })
  .setHandleDisconnected([](const APPLEMIDI_NAMESPACE::ssrc_t & ssrc) {
    isConnected--;
    Serial.println("Disconnected" + String(ssrc));
  });
}

void sendMIDI(byte note, byte velocity, byte channel, int state = 2) {
    if (isConnected > 0) {
        if (state == 1 || state == 2) {
            MIDI.sendNoteOn(note, velocity, channel);
        }

        delay(200);

        if (state == 0 || state == 2) {
            MIDI.sendNoteOff(note, velocity, channel);
        }
    }
}

void startShow(char shownum) {
    /*Keyboard.write(KEY_KP_0);
    delay(500);
    Keyboard.write(KEY_RETURN);
    delay(500);
    Keyboard.write(' ');*/

    Serial.println("Got number:" + String(shownum));

    digitalWrite(beeper, HIGH);

    switch(shownum) {
        case '0':  
            sendMIDI(4, 127, 1);
            break;
        
        case '1':
            sendMIDI(5, 127, 1);
            break;

    }

    delay(200);
    sendMIDI(3, 127, 1);
    digitalWrite(beeper, LOW);
    return;
}

void stopRunning() {
    //Keyboard.write(KEY_KP_0);
    digitalWrite(plug1, HIGH);
    delay(100);
    digitalWrite(plug2, HIGH);

    sendMIDI(1, 127, 1);
    return;
}

void runPanic() {
    /*Keyboard.write(KEY_KP_0);
    delay(500);
    Keyboard.write('#');
    delay(500);
    Keyboard.print("1000");
    delay(500);
    Keyboard.write(KEY_RETURN);
    delay(500);
    Keyboard.write(' ');*/

    digitalWrite(plug1, LOW);
    delay(100);
    digitalWrite(plug2, LOW);

    sendMIDI(2, 127, 1);

    delay(200);

    sendMIDI(3, 127, 1);
    return;
}

void sendStatus() {
    getStatus();
    if (status == 1) {
        comport.print('b');
        return;
    }

    if (status == 2) {
        comport.print('c');
        return;
    }

    if (status == 3) {
        comport.print('d');
        return;
    }

    if (sentCurWrongInst == false || wrongInst == 5) {
        comport.print(String(wrongInst));
        sentCurWrongInst = true;
        return;
    }

    comport.print('a');
    return;
}

void getStatus() {
    if (ethernetStatus == 0) {
        status = 1;
        return;
    }

    if (ethernetStatus == 2) {
        status = 2;
        return;
    }

    if (isConnected == 0) {
        status = 3;
        numBlink = 0;
        return;
    }
    status = 0;
    return;
}

void manageLed() {
    if (status == 1) {
        analogWrite(statusLed, 0);
        return;
    } else if (status == 0) {
        if (numBlink < 6) {
            Serial.println(numBlink);
            numBlink++;
            if (numBlink % 2 == 1) {
                analogWrite(statusLed, 0);
                digitalWrite(beeper, HIGH);
            } else {
                analogWrite(statusLed, 255);
                digitalWrite(beeper, LOW);
            }
        } else {
            analogWrite(statusLed, 255);
        }
        return;
    }

    currentBrightness = currentBrightness + (dir * 5);

    if (currentBrightness >= 160) {
        dir = -1;
        currentBrightness = 160;
    } else if (currentBrightness <= 0) {
        dir = 1;
        currentBrightness = 0;
    }

    analogWrite(statusLed, currentBrightness);
    return;
}

/*void ignoreError(char type) {
    if (ignoring.indexOf(type) == -1) {
        ignoring += String(type);
    }
    return;
}

void checkIgnore() {
    if (ignoring.indexOf('b') != -1 && ethernetStatus != 0) {
        ignoring.remove(ignoring.indexOf('b'));
    }

    if (ignoring.indexOf('c') != -1 && ethernetStatus != 2) {
        ignoring.remove(ignoring.indexOf('c'));
    }

    if (ignoring.indexOf('d') != -1 && isConnected > 0) {
        ignoring.remove(ignoring.indexOf('d'));
    }
}*/

void loop() {
    if (ethernetStatus != 0) {
        MIDI.read();
    }

    getStatus();

    if ((millis() - statusLedMillis >= 10 && status == 2) || (millis() - statusLedMillis >= 30 && status == 3) || (status == 1) || (millis() - statusLedMillis >= 600 && status == 0)) {
        manageLed();

        statusLedMillis = millis();
    }

    if (ethernetStatus != 0 && (millis() - maintainMillis) > 500) {
        int maintainStatus = Ethernet.maintain();

        if (maintainStatus == 1 || maintainStatus == 3) {
            ethernetStatus = 2;
        } else {
            maintainMillis = millis();
        }
    }

    if (millis() - wrongInstResetTimer >= wrongInstResetThreshold && wrongInst != 5) {
        wrongInst = 0;
        sentCurWrongInst = true;
        wrongInstResetTimer = 0;
    }

    if (comport.available()) {
        char readInst = comport.read();

        Serial.println("Got inst: " + String(readInst));

        if (readInst == 'a') {
            sendStatus();
        } /*else if (readInst == 'i') {
            char readType = comport.read();
            ignoreError(readType);
        } */else if (readInst == 's') {
            delay(100);
            char readNum = comport.read();
            if (readNum-'0' <= 9 && readNum-'0' >= 0) {
                wrongInst++;
                if (wrongInst > 5) {
                    wrongInst = 5;
                }
                sentCurWrongInst = false;
                wrongInstResetTimer = millis();
            } else {
                startShow(readNum);
            }
        } else if (readInst == 'p') {
            runPanic();
        } else if (readInst == 'r') {
            stopRunning();
        }
    }

    if (Serial.available()) {
        String notestr = "";
        while (Serial.available() > 0) {
            notestr += String((char) Serial.read());
        }

        byte note = notestr.toInt();

        sendMIDI(note, 127, 1);
    }
}