// Timing related functions
#ifndef MYTIMING_H
#define MYTIMING_H

#include "MyGlobal.h"

class MyTiming {
  private:
    int _previousMillis; // Variable to hold the previous time for use in timing calculations

  public:
    void MyTimingDelay(int delayInMs); // Function to set up a delay
    void MyTimingHang(); // Function to hang the program indefinitely
};


#endif // MYTIMING_H
