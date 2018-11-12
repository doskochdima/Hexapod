#include <Arduino.h>
#include <Locomotion.h>
//#include "SharpIR.h"
//#include "Communication.h"

//SharpIR Sensor;
Locomotion HexaPod;
//Communication Raspberry;


void setup() {
  Serial.begin(9600);
}

void loop() {
  HexaPod.Test(0, 45);
  delay(1000);

  HexaPod.Test(0, 90);
  delay(1000);

  HexaPod.Test(0, 135);
  delay(1000);

  //Serial.println("Leg: ");
  //int leg = Serial.read();

  //Serial.println("Part: ");
  //int part = Serial.read();

  //Serial.println("Angle: ");
  //float angle = Serial.read();
  //delay(250);
  //HexaPod.Test(leg, part, angle);
  //Serial.println(Sensor.Distance());
  //Serial.println(Raspberry.ReadWrite(data));
  //Movement.Idle();
}
