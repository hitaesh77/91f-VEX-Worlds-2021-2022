#include "main.h"

//HELPER FUNCTIONS
void armVelocity(int vel){
  armL.move_velocity(vel);
//  armR.move_velocity(vel);
}

void setBrakeArm(int mode){
  pros::motor_brake_mode_e_t brakeMode;
  switch(mode){
    case 0:
      brakeMode = MOTOR_BRAKE_COAST;
      break;
    case 1:
      brakeMode = MOTOR_BRAKE_BRAKE;
      break;
    case 2:
      brakeMode = MOTOR_BRAKE_HOLD;
      break;
  }

  armL.set_brake_mode(brakeMode);
//  armR.set_brake_mode(brakeMode);
}

void arm(int power){
  armL = power;
//  armR = power;
}

//OP Control
void armOP(int power){
  setBrakeArm(2);
  armL.set_brake_mode(MOTOR_BRAKE_HOLD);
  //armR.set_brake_mode(MOTOR_BRAKE_HOLD);
  if (master.get_digital(DIGITAL_R1)){
    arm(power);
  } else if (master.get_digital(DIGITAL_R2)){
    arm(-power);
  }else{
    arm(0);
}
}
/*
void armOP2(int armPower, int mogoPower){
  setBrakeArm(2);
  armL.set_brake_mode(MOTOR_BRAKE_HOLD);
  mogo.set_brake_mode(MOTOR_BRAKE_HOLD);
  if (master.get_digital(DIGITAL_L1)){
    arm(armPower);
  } else if (master.get_digital(DIGITAL_L2)){
    arm(-armPower);
  } else if (master.get_digital(DIGITAL_L1) && master.get_digital(DIGITAL_R2)){
    mogo = mogoPower;
  } else if (master.get_digital(DIGITAL_L2) && master.get_digital(DIGITAL_R2)){
    mogo = -mogoPower;
  }else{
    arm(0);
    mogo = 0;
}
}

void mogoOP2(int power){
  mogo.set_brake_mode(MOTOR_BRAKE_HOLD);
  if (master.get_digital(DIGITAL_X)){
    mogo = power;
  } else if (master.get_digital(DIGITAL_A)){
    mogo = -power;
  }else{
    mogo = 0;
}
}
*/
//AUTONOMOUS
void armPD(float target, float kp, float kd, int max, int tol, int brakeType){
  setBrakeArm(brakeType);
  int prevError = 0;
  int sign;

  int error = target - armPot.get_value();

  while(abs(error) > tol){

    error = target - armPot.get_value();
    int derivative = error - prevError;
    prevError = error;
    int speed = error * kp + derivative * kd;

    sign = error / abs(error);

    if(speed > max)
      speed = max;
    if(speed < -max)
      speed = -max;

    arm(speed);

    pros::delay(10);
  }
  arm(0);
}
