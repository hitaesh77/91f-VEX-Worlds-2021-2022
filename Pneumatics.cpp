#include "main.h"

//HELPER FUNCTIONS

//piston.set_value(true);//

void wingTime(int time){
  wingL.set_value(true);
  wingR.set_value(true);
  pros::delay(time);
  wingL.set_value(false);
  wingR.set_value(false);
}

void wing(bool state){
  wingL.set_value(state);
  wingR.set_value(state);
}

void clawS(bool state){
  claw.set_value(state);
}

void mogoS(bool state){
  mogo.set_value(state);
  mogoT.set_value(state);
  mogoM.set_value(state);
}

void clawTime(int time){
  claw.set_value(true);
  pros::delay(time);
  claw.set_value(false);
}

//OP Control
void clawOP(){
  if (master.get_digital(DIGITAL_L1)){
    claw.set_value(false);
  } else {
    claw.set_value(true);
  }
}

void pneumaticsOP(){
  if (master.get_digital(DIGITAL_R1)){
    claw.set_value(false);
  } else {
    claw.set_value(true);
  } if (master.get_digital(DIGITAL_R1) && master.get_digital(DIGITAL_R2)){
    wingL.set_value(false);
    wingR.set_value(false);
  } else {
    wingL.set_value(true);
    wingR.set_value(true);
  }
}

void wingOP(){
  if (master.get_digital(DIGITAL_X)){
    wingL.set_value(true);
    wingR.set_value(true);
  } else {
    wingL.set_value(false);
    wingR.set_value(false);
  }
}

void mogoOP(){
  if (master.get_digital(DIGITAL_L2)){
    mogo.set_value(false);
    mogoT.set_value(false);
    mogoM.set_value(false);
  } else {
    mogo.set_value(true);
    mogoT.set_value(true);
    mogoM.set_value(true);
  }
}

//AUTONOMOUS
