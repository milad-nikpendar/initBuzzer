#include "initBuzzer.h"

RtosBuzzer buzzer(12); // Replace with your actual GPIO pin

void setup() {
  buzzer.begin();
}

void loop() {
  buzzer.tone(3000,200);    // Beep for 200 milliseconds
  delay(1000);              // Wait 1 second before next beep
}
