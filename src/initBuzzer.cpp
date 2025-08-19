#include "initBuzzer.h"

Buzzer::Buzzer(uint8_t pin) : _pin(pin) {}

void Buzzer::begin()
{
  pinMode(_pin, OUTPUT);
}

void Buzzer::write(bool status)
{
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, status);
}

#ifdef ESP32
void Buzzer::tone(uint16_t frequency, uint16_t duration)
{
  uint32_t startTime = millis();
  uint32_t halfPeriod = 1000000L / frequency / 2;
  pinMode(_pin, OUTPUT);
  while (millis() - startTime < duration)
  {
    digitalWrite(_pin, HIGH);
    delayMicroseconds(halfPeriod);
    yield();                             // Yield to allow other tasks to run
    digitalWrite(_pin, LOW);
    delayMicroseconds(halfPeriod);
    yield();                             // Yield to allow other tasks to run
  }
}

bool Buzzer::pulse(uint16_t freq, uint16_t duration)
{
  if (freq == 0 || duration == 0)
  {
    write(false);
    return true;
  }
  tone(freq, duration);
  return true;
}

void Buzzer::beep(uint16_t time)
{
  tone(1000, time);
}
#endif // ESP32

#ifdef ESP32
RtosBuzzer::RtosBuzzer(uint8_t pin)
    : _pin(pin), buzzer(pin), buzzerQueue(nullptr) {}

void RtosBuzzer::begin()
{
  buzzer.begin();
  buzzerQueue = xQueueCreate(20, sizeof(BuzzerData));
  if (buzzerQueue != nullptr)
  {
    xTaskCreatePinnedToCore(buzzerTask, "BuzzerTask", 1024, this, 1, nullptr, 1);
  }
}

bool RtosBuzzer::tone(uint16_t freq, uint16_t duration)
{
  BuzzerData data = {freq, duration};
  if (freq == 0)
  {
    vTaskDelay(pdMS_TO_TICKS(duration)); // If frequency is 0, just delay for the duration
    yield();                             // Yield to allow other tasks to run
    return true;                         // Return true to indicate success
  }
  return xQueueSend(buzzerQueue, &data, 0) == pdTRUE;
}

bool RtosBuzzer::tone(uint16_t duration)
{
  return tone(3000, duration);
}

bool RtosBuzzer::pulse(uint16_t freq, uint16_t duration)
{
  return tone(freq, duration);
}

void RtosBuzzer::buzzerTask(void *pvParameters)
{
  RtosBuzzer *self = static_cast<RtosBuzzer *>(pvParameters);
  BuzzerData data;

  while (true)
  {
    if (xQueueReceive(self->buzzerQueue, &data, portMAX_DELAY) == pdTRUE)
    {
      self->buzzer.pulse(data.frequency, data.duration);
    }
    vTaskDelay(pdMS_TO_TICKS(10)); // Delay to prevent task starvation
    yield();                       // Yield to allow other tasks to run
  }
}
#endif // ESP32
