#include <Ticker.h>

#define TRIGGER 4
#define ECHO 5
#define LIGHT 12
#define DOOR 14
#define BUTTON 16
#define READING_COUNT 3
#define BUTTON_SECONDARY 4000

Ticker sensor;
unsigned long buttonDown = 0;
long currentDistance = 0;
bool printDistance = false;

void getDistance()
{
    currentDistance = readDistance();
    printDistance = true;
}

void setup() {
    Serial.begin(9600);
    pinMode(TRIGGER, OUTPUT);
    pinMode(ECHO, INPUT);
    pinMode(LIGHT, OUTPUT);
    pinMode(DOOR, OUTPUT);
    pinMode(BUTTON, INPUT);

    sensor.attach(3, getDistance);
}

void loop() {
    if (printDistance)
    {
        printDistance = false;
        Serial.print("Inches: ");
        Serial.println(currentDistance);
    }

    int button = readButton();
    if (button > 0)
    {
        Serial.print("Button: ");
        Serial.println(button);
    }
}

// Just playing with button duration for a multi-function single button.
int readButton()
{
    if (buttonDown == 0 && digitalRead(BUTTON) == LOW) 
    {
        buttonDown = millis();
    }
    else if (buttonDown > 0 && digitalRead(BUTTON) == HIGH)
    {
        if (millis() - buttonDown > BUTTON_SECONDARY)
        {
            buttonDown = 0;
            return 2;
        }
        else
        {
            buttonDown = 0;
            return 1;
        }
    }
    return 0;
}

// Grab the reading from the hc-sr04. Was playing around with the idea
// of grabbing a few readings and averaging them. A single reading seems
// accurate enough.
long readDistance()
{
  long duration, distance;
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance =  duration / 148.0;

  return distance;
}