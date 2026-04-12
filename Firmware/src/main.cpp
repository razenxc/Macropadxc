#include <Arduino.h>

const unsigned PINS[] = { 15, 14, 13, 12, 11, 10, 9, 8, 7 };
const unsigned short BUTTON_COUNT = 9;

int lastButtonState[BUTTON_COUNT];

unsigned long lastDepressTime[BUTTON_COUNT];
const unsigned long DEPRESS_DELAY = 50;

void setup()
{
  pinMode(25, OUTPUT);
  Serial.begin(115200);
  
  digitalWrite(25, HIGH);
  unsigned long startWait = millis();
  while (!Serial && (millis() - startWait < 5000)) {
    digitalWrite(25, (millis() / 100) % 2); 
    delay(10);
  }
  digitalWrite(25, LOW);

  for (int i = 0; i < BUTTON_COUNT; i++) {
    pinMode(PINS[i], INPUT_PULLUP);
    lastButtonState[i] = HIGH; 
    lastDepressTime[i] = 0;
  }
}

void loop()
{
  if (Serial.available() > 0)
  {
    String data = Serial.readStringUntil('\n');
    data.trim();

    if (data == "WAREI_HEY")
    {
      Serial.println("WAREI_OK");
    }
  }

  for (int i = 0; i < BUTTON_COUNT; i++)
  {
    int currentState = digitalRead(PINS[i]);

    if (currentState != lastButtonState[i])
    {
      if ((millis() - lastDepressTime[i]) > DEPRESS_DELAY)
      {
        if (currentState == LOW)
        {
          Serial.print("F");
          Serial.println(i + 1);
        }

        lastDepressTime[i] = millis();
      }

      lastButtonState[i] = currentState;
    }
  }
}