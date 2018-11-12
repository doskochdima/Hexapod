#include <Arduino.h>
#include "Communication.h"

Communication::Communication() {
  Serial.begin(9600);
}

int Communication::ReadWrite(int output) {
  int input = 0;

  if (Serial.available() > 0) {
    input = (int)(Serial.read());
  }

  Serial.write(output);

  return input;
}
