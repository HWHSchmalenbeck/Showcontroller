#include <SoftwareSerial.h>

SoftwareSerial test(10, 11);

bool useful = false;

void setup()
{
    Serial.begin(9600);
    pinMode(10,INPUT);
    if (digitalRead(10) == HIGH)
    {
        useful = true;
        test.begin(9600);
        Serial.println("YES volt!");
    }
    else
    {
        Serial.println("NO volt!");
    }
}

void loop()
{
    test.print('A');
    if (useful == true)
    {
        if (test.available())
        {
            Serial.print(test.read());
        }
    }
}