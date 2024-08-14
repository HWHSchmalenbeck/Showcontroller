//#include <Keyboard.h>
#include <SoftwareSerial.h>
#include <Ethernet.h>
#include <AppleMIDI.h>

int plug1 = 5;
int plug2 = 6;

String ignoring = "";

byte mac[] = {
  0x42, 0x06, 0x91, 0x33, 0x75, 0x85
};

int8_t isConnected = 0;

int ethernetStatus = NULL;

unsigned long maintainMillis = 0;

APPLEMIDI_CREATE_DEFAULTSESSION_INSTANCE();

SoftwareSerial comport(11,10);

void setup() {
    Serial.begin(115200);
    digitalWrite(plug1, HIGH);
    digitalWrite(plug2, HIGH);
    comport.begin(9600);
    //Keyboard.begin(KeyboardLayout_de_DE);

    pinMode(plug1, OUTPUT);
    pinMode(plug2, OUTPUT);

    ethernetStatus = Ethernet.begin(mac);

    if (ethernetStatus != 0) {
        maintainMillis = millis();
    }

    MIDI.begin();

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

        if (state == 0 || state == 2) {
            MIDI.sendNoteOff(note, velocity, channel);
        }
    }
}

void startShow() {
    /*Keyboard.write(KEY_KP_0);
    delay(500);
    Keyboard.write(KEY_RETURN);
    delay(500);
    Keyboard.write(' ');*/
    byte note = 1;
    byte velocity = 1;
    byte channel = 1;

    sendMIDI(note, velocity, channel);
    return;
}

void stopRunning() {
    //Keyboard.write(KEY_KP_0);
    digitalWrite(plug1, HIGH);
    delay(100);
    digitalWrite(plug2, HIGH);
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

    byte note = 2;
    byte velocity = 1;
    byte channel = 1;

    sendMIDI(note, velocity, channel);
    return;
}

void sendStatus() {
    if (ethernetStatus == 0 && ignoring.indexOf('b') == -1) {
        comport.print('b');
        return;
    }

    if (ethernetStatus == 2 && ignoring.indexOf('c') == -1) {
        comport.print('c');
        return;
    }

    if (isConnected == 0 && ignoring.indexOf('d') == -1) {
        comport.print('d');
        return;
    }

    comport.print('a');
    return;
}

void ignoreError(char type) {
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
}

void loop() {
    MIDI.read();

    if (ethernetStatus != 0 && (millis() - maintainMillis) > 500) {
        int maintainStatus = Ethernet.maintain();

        if (maintainStatus == 1 || maintainStatus == 3) {
            ethernetStatus = 2;
        } else {
            maintainMillis = millis();
        }
    }

    if (comport.available()) {
        char readInst = comport.read();

        if (readInst == 'a') {
            sendStatus();
        } else if (readInst == 'i') {
            char readType = comport.read();
            ignoreError(readType);
        } else if (readInst == 's') {
            startShow();
        } else if (readInst == 'p') {
            runPanic();
        } else if (readInst == 'r') {
            stopRunning();
        }
    }

    checkIgnore();
}