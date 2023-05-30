#include "MyLED.h"
// In initialise the LED
bool MyLED::initLED(int pin)
{
  DUMP(pin);
  pinMode(pin, OUTPUT);
  pinID = pin;
  return true;
}
// Setter for pinID
void MyLED::setPinID(int pin)
{
  pinID = pin;
}
//Getter for pinID
int MyLED::getPinID()
{
  return pinID;
}
/**
 * Blink the ESP32_LED_BUILTIN blinkcount times 
 * and if forever is true then blink forever
 * 
 * @param pin The pin the LED is on (See the LED pins above, usually ESP32_LED_BUILTIN)
 * @param blinkcount The number of times to blink (If PIN_LOW the just turn the LED OFF or If PIN_HIGH the just turn the LED ON)
 * @param forever If true then halt & blink forever
 * 
 * @return  
 *          - none
 * 
 */
void MyLED::blinkLED(int blinkcount, bool forever)
{
  TRACE();
  DUMP(pinID);
  DUMP(blinkcount);
  DUMP(forever);
  
  if (blinkcount == PIN_LOW)
  {
    digitalWrite(pinID, LOW);
  }
  else if (blinkcount == PIN_HIGH)
  {
    digitalWrite(pinID, HIGH);
  }
  else
  {
    if (forever)
    {
      while (true)
      {
        for (int i = 0; i < blinkcount; i++)
        {
          digitalWrite(pinID, HIGH);
          delay(BLINK_DELAY);
          digitalWrite(pinID, LOW);
          delay(BLINK_DELAY);
        }
        delay(BLINK_REPEAT_DELAY);
      }
    }
    else
    {
      for (int i = 0; i < blinkcount; i++)
      {
        digitalWrite(pinID, HIGH);
        delay(BLINK_DELAY);
        digitalWrite(pinID, LOW);
        delay(BLINK_DELAY);
      }
      delay(BLINK_REPEAT_DELAY);
    }
  }
}