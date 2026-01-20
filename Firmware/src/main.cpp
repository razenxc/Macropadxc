#include <Arduino.h>

unsigned short currentPage = 0;

void setup()
{
  Serial.begin(115200);

  
  pinMode(13, INPUT_PULLUP); // F1
  pinMode(12, INPUT_PULLUP); // F2
  pinMode(14, INPUT_PULLUP); // F3
  pinMode(27, INPUT_PULLUP); // F4
  pinMode(26, INPUT_PULLUP); // F5
  pinMode(25, INPUT_PULLUP); // F6
  pinMode(33, INPUT_PULLUP); // F7
  pinMode(32, INPUT_PULLUP); // F8
}

void loop()
{
  if (digitalRead(13) == LOW)
  {
    Serial.printf("P%iB1", currentPage);
  }
  else if (digitalRead(12) == LOW)
  {
    Serial.printf("P%iB2", currentPage);
  }
  else if (digitalRead(14) == LOW)
  {
    Serial.printf("P%iB3", currentPage);
  }
  else if (digitalRead(27) == LOW)
  {
    Serial.printf("P%iB4", currentPage);
  }
  else if (digitalRead(26) == LOW)
  {
    Serial.printf("P%iB5", currentPage);
  }
  else if (digitalRead(25) == LOW)
  {
    Serial.printf("P%iB6", currentPage);
  }
  else if (digitalRead(33) == LOW)
  {
    Serial.printf("P%iB7", currentPage);
  }
  else if (digitalRead(32) == LOW)
  {
    Serial.printf("P%iB8", currentPage);
  }

  delay(100);
}