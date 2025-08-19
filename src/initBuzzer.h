/*
   initBuzzer header V1.0.0
   Created by Milad Nikpendar
*/
#ifndef INITBUZZER_H
#define INITBUZZER_H

#include <Arduino.h>

class Buzzer
{
public:
  Buzzer(uint8_t pin);
  void begin();
  void write(bool status);

#ifdef ESP32
  void tone(uint16_t frequency, uint16_t duration);
  bool pulse(uint16_t freq, uint16_t duration);
  void beep(uint16_t time = 20);
#endif

private:
  uint8_t _pin;
};

#ifdef ESP32
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

struct BuzzerData
{
  uint16_t frequency;
  uint16_t duration;
};

class RtosBuzzer
{
public:
  RtosBuzzer(uint8_t pin);
  void begin();
  bool tone(uint16_t freq, uint16_t duration);
  bool tone(uint16_t duration);
  bool pulse(uint16_t freq, uint16_t duration);

private:
  uint8_t _pin;
  Buzzer buzzer;
  QueueHandle_t buzzerQueue;

  static void buzzerTask(void *pvParameters);
};
#endif // ESP32
#endif // INITBUZZER_H
