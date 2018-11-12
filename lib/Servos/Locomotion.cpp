#include <Arduino.h>
#include <Servo.h>
#include <Locomotion.h>
#include <HexabotCfg.h>

Locomotion::Locomotion() {
  AttachLeg(0);
}

//Attaching current leg
void Locomotion::AttachLeg(int i) {
  Leg[i].Coxa.attach(Coxa_pin[i]);
  Leg[i].Femur.attach(Femur_pin[i]);
  Leg[i].Tibia.attach(Tibia_pin[i]);
}

//Detaching current leg
void Locomotion::DetachLeg(int i) {
  delay(Servo_Life);
  Leg[i].Coxa.detach();
  Leg[i].Femur.detach();
  Leg[i].Tibia.detach();
}

//Attaching legs
void AttachAll() {
  for (int i = 0; i < 6; i++) {
    Leg[i].Coxa.attach(Coxa_pin[i]);
    Leg[i].Femur.attach(Femur_pin[i]);
    Leg[i].Tibia.attach(Tibia_pin[i]);
  }
}

//Detaching legs
void DetachAll() {
  delay(Servo_Life);
  for (int i = 0; i < 6; i++) {
    Leg[i].Coxa.detach();
    Leg[i].Femur.detach();
    Leg[i].Tibia.detach();
  }
}

//Calculating IK
void LegIK(float _lHeight, float _lLength, float _hStep, float _lStep, float& Out1, float& Out2) {
  float L1 = sqrt(pow(_lHeight - _hStep, 2.0) + pow(_lLength - _lCoxa - _lStep, 2.0));
  float a1 = atan((_lLength - _lCoxa - _lStep) / (_lHeight - _hStep)) * Rad;
  float a2 = (acos((pow(_lFemur, 2.0) + pow(L1, 2.0) - pow(_lTibia, 2.0)) / (2 * _lFemur * L1))) * Rad;
  Out1 = a2 + a1 - 90;

  float b2 = (acos((pow(_lTibia, 2.0) + pow(L1, 2.0) - pow(_lFemur, 2.0)) / (2 * _lTibia * L1))) * Rad;
  float y2 = 180 - (a2 + b2);
  Out2 = 90 - y2;
}

void Locomotion::Idle() {
  //Setting middle position
  for (int i = 0; i < 6; i++) {
    AttachLeg(i);

    if (i < 3) {
      Leg[i].Coxa.write(90);
      Leg[i].Coxa_State = -90;

      Leg[i].Femur.write(90);
      Leg[i].Femur_State = -90;

      Leg[i].Tibia.write(90);
      Leg[i].Tibia_State = -90;
    }

    else {
      Leg[i].Coxa.write(90);
      Leg[i].Coxa_State = 90;

      Leg[i].Femur.write(90);
      Leg[i].Femur_State = 90;

      Leg[i].Tibia.write(90);
      Leg[i].Tibia_State = 90;
    }
  }
}

//Step Forward
void Locomotion::Forward() {
  float Out1;
  float Out2;

  for (int i = 0; i <= 4; i+=2) {   //Leg 0 2 4 cycle
    //Backward -> Forward
    Coxa_Range = 30.0;
    Coxa_Height = 80.0;
    Step_Length = 120.0;
    Tibia_OffsetH = 0.0;
    Tibia_OffsetL = 0.0;

    Leg[i].Coxa_State = Leg[i].Coxa_State + Coxa_Range;   //Depends on side write in Setup
    Leg[i].Coxa.write( abs(Leg[i].Coxa_State));  //Need correct param
    delay(Servo_Life);    //Need delay for sync
    LegIK(Coxa_Height, Step_Length, Tibia_OffsetH, Tibia_OffsetL, Out1, Out2);
    Leg[i].Femur.write( abs(Leg[i].Femur_State + Out1));
    Leg[i].Tibia.write( abs(Leg[i].Tibia_State + Out2));

    //Forward -> Backward
    Tibia_OffsetH = 20.0;
    Tibia_OffsetL = 20.0;

    Leg[i].Coxa_State = Leg[i].Coxa_State - Coxa_Range;   //Depends on side write in Setup
    Leg[i].Coxa.write(Leg[i].Coxa_State);  //Need correct param
    delay(Servo_Life);    //Need delay for sync
    LegIK(Coxa_Height, Step_Length, Tibia_OffsetH, Tibia_OffsetL, Out1, Out2);
    Leg[i].Femur.write( abs(Leg[i].Femur_State + Out1));
    Leg[i].Tibia.write( abs(Leg[i].Tibia_State + Out2));
  }
}

void Locomotion::Test(int _leg, int _angle) {

  Leg[_leg].Coxa.write(_angle);
  Leg[_leg].Femur.write(90);
  Leg[_leg].Tibia.write(90);
  /*
  switch (_part) {
    case 1:
      Leg[_leg].Coxa.write(_angle);
    case 2:
      Leg[_leg].Femur.write(_angle);
    case 3:
      Leg[_leg].Tibia.write(_angle);
  }
  */
}
