#include <Arduino.h>

#define led 13

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop()
{
  for (int i = 0; i < 15; i++)
  {
    digitalWrite(led, 1);
    delay(500);
    Serial.println("Counter: " + String(i));
    //Serial.println(i);
    digitalWrite(led, 0);
    delay(400);
  }
}