#include <Arduino.h>

unsigned short currentPage = 0;

const unsigned PINS[] = { 13, 12, 14, 27, 26, 25, 33, 32 };
const unsigned short BUTTON_COUNT = 8;

int lastButtonState[BUTTON_COUNT];

unsigned long lastDepressTime[BUTTON_COUNT];
const unsigned long DEPRESS_DELAY = 50;

void setup()
{
  Serial.begin(115200);

  for (int i = 0; i < BUTTON_COUNT; i++) {
    pinMode(PINS[i], INPUT_PULLUP);
    lastButtonState[i] = HIGH; 
    lastDepressTime[i] = 0;
  }
}

void loop()
{
  for (int i = 0; i < BUTTON_COUNT; i++)
  {
    int currentState = digitalRead(PINS[i]);

    if (currentState != lastButtonState[i])
    {
      if ((millis() - lastDepressTime[i]) > DEPRESS_DELAY)
      {
        if (currentState == LOW)
        {
          Serial.printf("P%iF%i\n", currentPage, i+1);
        }

        lastDepressTime[i] = millis();
      }

      lastButtonState[i] = currentState;
    }
  }
}