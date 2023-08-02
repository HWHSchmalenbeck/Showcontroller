int startgreen = 11;
int crisisred = 37;
int txled = 30;
int rxled = 28;
int statusred = 45;
int statusgreen = 44;
int statusblue = 46;

int btn1 = 34;
int btn2 = 36;
int btn3 = 38;
int btn4 = 40;
int btn5 = 42;
int btn6 = 50;
int btn7 = 25;

void setup() {
    pinMode(startgreen, OUTPUT);
    pinMode(crisisred, OUTPUT);
    pinMode(txled, OUTPUT);
    pinMode(rxled, OUTPUT);
    pinMode(statusred, OUTPUT);
    pinMode(statusgreen, OUTPUT);
    pinMode(statusblue, OUTPUT);

    pinMode(btn1, INPUT);
    pinMode(btn2, INPUT);
    pinMode(btn3, INPUT);
    pinMode(btn4, INPUT);
    pinMode(btn5, INPUT);
    pinMode(btn6, INPUT);
    pinMode(btn7, INPUT);
}

void loop() {
    if (digitalRead(btn1) == HIGH) {
        digitalWrite(startgreen, HIGH);
    } else {
        digitalWrite(startgreen, LOW);
    }
    if (digitalRead(btn2) == HIGH) {
        digitalWrite(crisisred, HIGH);
    } else {
        digitalWrite(crisisred, LOW);
    }
    if (digitalRead(btn3) == HIGH) {
        digitalWrite(txled, HIGH);
    } else {
        digitalWrite(txled, LOW);
    }
    if (digitalRead(btn4) == HIGH) {
        digitalWrite(rxled, HIGH);
    } else {
        digitalWrite(rxled, LOW);
    }
    if (digitalRead(btn5) == HIGH) {
        digitalWrite(statusred, HIGH);
    } else {
        digitalWrite(statusred, LOW);
    }
    if (digitalRead(btn6) == HIGH) {
        digitalWrite(statusgreen, HIGH);
    } else {
        digitalWrite(statusgreen, LOW);
    }
    if (digitalRead(btn7) == HIGH) {
        digitalWrite(statusblue, HIGH);
    } else {
        digitalWrite(statusblue, LOW);
    }
    /*
        digitalWrite(startgreen, HIGH);
    digitalWrite(crisisred, HIGH);

    digitalWrite(txled, HIGH);
    digitalWrite(rxled, HIGH);


    digitalWrite(statusred, HIGH);
delay(500);
 digitalWrite(statusred, LOW);

    digitalWrite(statusgreen, HIGH);
    delay(500);
      digitalWrite(statusgreen, LOW);


    digitalWrite(statusblue, HIGH);
    delay(500);
      digitalWrite(statusblue, LOW);
    */
}