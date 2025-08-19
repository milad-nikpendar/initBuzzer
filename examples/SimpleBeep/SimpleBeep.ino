#include "initBuzzer.h"

Buzzer buzzer(12); // Replace with your actual GPIO pin

void setup() {
  buzzer.begin();
}

void loop() {
  buzzer.beep(200);     // Beep for 200 milliseconds
  delay(1000);          // Wait 1 second before next beep
}
