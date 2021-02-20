#include <Arduino.h>
#include "TM1637Display.h"

#define CLK 0
#define DIO 2
#define BUZZER 4

unsigned long millis_prev = 0;
unsigned long loop_length = 1; // ms.
unsigned long second_counter = 0;
unsigned long prep_time = 30;
int round_time = 180; // Round length (s)

uint8_t round_counter = 0;
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

void loop()
{
  if (millis() >= (millis_prev + loop_length))
  {
    millis_prev = millis();
    
    if (second_counter < prep_time){
      Serial.printf("Prep:\t");
      DisplayTime(&second_counter);
    }
    else{
      Serial.printf("Main:\t");
      if (round_counter < round_max){
        
      }
    }

    second_counter++;
  }
}

/*
void old_loop()
{
  if (millis() >= (millis_prev + loop_length))
  {
    millis_prev = millis();

    // prepare time
    if (prep_flag)
    {
    }

    // down time
    if (dn_flag)
    {
      Serial.printf("Down: \t");

      if (second_counter == dn_seconds)
      {
        second_counter = 0;
        dn_flag = false;
        Serial.printf("Down time is over!\n");
      }
      else
      {
        DisplayTime(&minute_counter, &second_counter);
      }
      second_counter++;
    }
    // up time
    else
    {
      Serial.printf("Up.\t Round %i.\t", (round_counter + 1));

      if (second_counter == 60) // todo: work only with seconds. Get minuts from dividing
      {
        minute_counter++;
        second_counter = 0;
      }

      if (round_counter < round_count_max)
      {
        if (minute_counter == round_minutes)
        {
          dn_flag = true;
          Serial.printf("Round -=\"%i\"=- time is over!\n", round_counter);
          round_counter++;
          minute_counter = 0;
          second_counter = 0;
        }
        else
        {
          DisplayTime(&minute_counter, &second_counter);
          second_counter++;
        }
      }
      else
      {
        Serial.printf("\n -end!\n");
        ESP.deepSleepMax();
        loop_length = 86400000;
        Serial.printf("Loop length increased to %lu", loop_length);
      }
    }
  }
}
*/