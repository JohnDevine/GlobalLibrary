#include "MyTiming.h"

void MyTiming::MyTimingDelay(int delayInMs)
{
    _previousMillis = millis(); // Set the start time for the delay
    while (millis() - _previousMillis < delayInMs) {} // Wait until enough time has passed
}

void MyTiming::MyTimingHang()
{
    while(true) {} // Loop indefinitely, effectively hanging the program
}
