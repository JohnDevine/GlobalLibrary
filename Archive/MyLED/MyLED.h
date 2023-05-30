#ifndef MYLED_H
#define MYLED_H
#include "MyGlobal.h"

#define BLINK_DELAY 300         // Delay between flashes in milliseconds
#define BLINK_REPEAT_DELAY 5000 // Delay between repeats in milliseconds

#define PIN_LOW 0  // Pin LOW
#define PIN_HIGH 1 // Pin HIGH

class MyLED
{
    /**
     * Initialise the LED pin
     *
     * @param pin  The pin the LED is on (See the LED pins above, usually ESP32_LED_BUILTIN)
     *
     * @return
     *          - true
     *
     */
public:
    bool initLED(int pin);
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
    void blinkLED(int blinkcount, bool forever);
    void setPinID(int pin);
    int getPinID();


private:
    int pinID;
};
#endif // MYLED_H
