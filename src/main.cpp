#include <Arduino.h>
#include "TM1637Display.h"

#define CLK 0
#define DIO 2
#define BUZZER 4

unsigned long millis_prev = 0;
unsigned long loop_length = 1; // ms.
unsigned long loop_counter = 0;
unsigned long prep_time = 15;
unsigned long round_time = 180; // Round length (s)
unsigned long dn_time = 60;     // Down time
bool dn_flag = false;           // Down time flag
uint8_t round_counter = 1;
uint8_t round_max = 3; // Maximum rounds

TM1637Display display(CLK, DIO);

void setup()
{
  Serial.begin(9600);
  display.setBrightness(0x00);
  display.clear();
}

void DisplayTime(unsigned long *seconds)
{
  uint8_t min = *seconds / 60;
  uint8_t sec = *seconds % 60;
  Serial.printf("Minutes: %i\tSeconds: %i\n", min, sec);
}

void BeepRun(){
  tone(BUZZER, 1000, 1000);
}

void loop()
{
  if (millis() >= (millis_prev + loop_length))
  {
    millis_prev = millis();

    // prepare time
    if (prep_time > 0)
    {
      Serial.printf("Prep:\t");
      prep_time--;
      DisplayTime(&loop_counter);
    }
    // main time
    //// down time
    else if (dn_flag)
    {
      if (loop_counter < dn_time)
      {
        Serial.printf("Down time!\t");
        DisplayTime(&loop_counter);
        loop_counter++;
      }
      else
      {
        dn_flag = false;
        loop_counter = 0;
      }
    }
    //// up time
    else
    {
      if (round_counter < round_max)
      {
        if (loop_counter < round_time)
        {
          Serial.printf("Round: %i\t", round_counter);
          DisplayTime(&loop_counter);
        }
        else
        {
          round_counter++;
          loop_counter = 0;
          dn_flag = true;
        }
      }
      else
      {
        Serial.printf("Done!\n");
        //BeepRun();
        delay(60000);
      }
    }

    loop_counter++;
  }
}
