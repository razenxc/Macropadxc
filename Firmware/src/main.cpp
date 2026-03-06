#include <Arduino.h>
#include <FastLED.h>

unsigned short currentPage = 1;
unsigned short lastRenderedPage = 0;

const unsigned PINS[] = { 13, 12, 14, 27, 26, 25, 33, 32 };
const unsigned short BUTTON_COUNT = 8;

int lastButtonState[BUTTON_COUNT];

unsigned long lastDepressTime[BUTTON_COUNT];
const unsigned long DEPRESS_DELAY = 50;

#define NUM_LEDS 8
uint8_t hue = 160;
CRGB leds[NUM_LEDS];
const uint8_t pageHues[NUM_LEDS] = { 0, 32, 64, 96, 128, 160, 192, 224 };

void setup()
{
  Serial.begin(115200);

  for (int i = 0; i < BUTTON_COUNT; i++) {
    pinMode(PINS[i], INPUT_PULLUP);
    lastButtonState[i] = HIGH; 
    lastDepressTime[i] = 0;
  }

  delay(1000);

  FastLED.addLeds<WS2812B, 4, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(10);
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
          bool isDoubleTriggered = false;
          // Issue: when two buttons are pressed serial write lines of these two buttons
          if ((i == 0 && digitalRead(PINS[4]) == LOW) || (i == 4 && digitalRead(PINS[0]) == LOW)) 
          {
            if (currentPage > 1) {
              currentPage--; 
            }
            isDoubleTriggered = true;
          }
          else if ((i == 3 && digitalRead(PINS[7]) == LOW) || (i == 7 && digitalRead(PINS[3]) == LOW)) 
          {
            if (currentPage < 8) 
            {
              currentPage++; 
            }
            isDoubleTriggered = true;
          }

          if (!isDoubleTriggered) 
          {
            Serial.printf("P%iF%i\n", currentPage, i+1);
          }
        }

        lastDepressTime[i] = millis();
      }

      lastButtonState[i] = currentState;
    }
  }

  if (currentPage != lastRenderedPage)
  {
    FastLED.clear();

    int ledIndex = currentPage - 1; 
    uint8_t currentHue = pageHues[ledIndex];
    leds[ledIndex] = CHSV(currentHue, 255, 255);
    
    FastLED.show();
    lastRenderedPage = currentPage; 
  }
}