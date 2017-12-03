
#define TRIGGER 4
#define ECHO 5
#define LIGHT 12
#define DOOR 14
#define BUTTON 16
#define READING_COUNT 3
#define BUTTON_SECONDARY 4000

unsigned long buttonDown = 0;

void setup() {
  Serial.begin(9600);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LIGHT, OUTPUT);
  pinMode(DOOR, OUTPUT);
  pinMode(BUTTON, INPUT);
}

void loop() {
    long distance = readDistance();

    Serial.print("Inches: ");
    Serial.println(distance);

    int button = readButton();
    if (button > 0)
    {
        Serial.print("Button: ");
        Serial.println(button);
    }

    delay(500);
}

// Just playing with button duration for a multi-function single button.
int readButton()
{
    if (buttonDown == 0 && digitalRead(BUTTON) == LOW) 
    {
        buttonDown = millis();
        Serial.print("Button down: ");
        Serial.println(buttonDown);
        return 0;
    }
    else if (digitalRead(BUTTON) == HIGH && buttonDown > 0)
    {
        unsigned long buttonUp = millis();
        unsigned long elapsed = buttonUp - buttonDown;

        Serial.print("Elapsed button time: ");
        Serial.println(elapsed);

        buttonDown = 0;
        if (elapsed > BUTTON_SECONDARY)
        {
            return 2;
        }
        else
        {
            return 1;
        }        
    }

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

  // If there isn't a big enough delay, I noticed a lot of error in the readings.
  delay(200);

  return distance;
}