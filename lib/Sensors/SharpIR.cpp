#include <Arduino.h>
#include "SharpIR.h"

#define sensorIR 15

SharpIR::SharpIR() {
}

float SharpIR::Distance() {
  float cm = 0;

  cm = 10650.08 * pow(analogRead(sensorIR),-0.935) - 10;

  return cm;
}
