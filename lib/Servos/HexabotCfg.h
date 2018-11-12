#include <Servo.h>

#define Servo_Life 200   //Set Max servo life time
#define Rad (180 / 3.14159265358979323846)

//Setting phisycal parameters
#define _lCoxa 47
#define _lFemur 65
#define _lTibia 72

//Setting pins
int Coxa_pin [6] = {31, 37, 43, 30, 36, 42};     //setting pins for Coxa
int Femur_pin [6] = {33, 39, 45, 32, 38, 44};     //setting pins for Femur
int Tibia_pin [6] = {35, 41, 47, 34, 40, 46};   //setting pins for Tibia


float Coxa_Range = 30;
float Coxa_Height = 80;  //Hight per leg
float Step_Length = 120;
float Tibia_OffsetH = 20;
float Tibia_OffsetL = 20;

//Setting legs structure
struct Legs {
  Servo Coxa;
  float Coxa_State;
  Servo Femur;
  float Femur_State;
  Servo Tibia;
  float Tibia_State;
} Leg[6];
