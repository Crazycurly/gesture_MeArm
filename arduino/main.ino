#include <Servo.h>

Servo servo[4];
int default_angle[4] = {75, 90, 90, 60};

void setup()
{
    Serial.begin(115200);
    servo[0].attach(5);
    servo[1].attach(6);
    servo[2].attach(7);
    servo[3].attach(8);

    for (size_t i = 0; i < 4; i++)
    {
        servo[i].write(default_angle[i]);
    }
}

byte angle[4];
byte pre_angle[4];
long t = millis();

void loop()
{
    if (Serial.available())
    {
        Serial.readBytes(angle, 4);
        for (size_t i = 0; i < 4; i++)
        {
            if (angle[i] != pre_angle[i])
            {
                servo[i].write(angle[i]);
                pre_angle[i] = angle[i];
            }
        }
        t = millis();
    }

    if (millis() - t > 1000)
    {
        for (size_t i = 0; i < 4; i++)
        {
            servo[i].write(default_angle[i]);
            pre_angle[i] = default_angle[i];
        }
    }
}
