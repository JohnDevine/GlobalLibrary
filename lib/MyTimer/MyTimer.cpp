#include "MyTimer.h"

void MyTimer::hang() {
  while (true) {
    // do nothing
  }
}
// Delay for a number of milliseconds
/* NOTE
The delay() function does not disable interrupts1. 
Serial communication that appears at the RX pin is recorded, 
PWM (analogWrite) values and pin states are maintained, 
and interrupts will work as they should.
*/
void MyTimer::delay_ms(int ms) {
  delay(ms);
}

