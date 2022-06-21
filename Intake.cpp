#include "main.h"

//HELPER FUNCTIONS
void intakeVelocity(int vel){
  intake.move_velocity(vel);
}

void setBrakeIntake(int mode){
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

  intake.set_brake_mode(brakeMode);
}

void intakePower(int power){
  intake = power;
}

//OP Control
void intakeOP(int power){
  intake.set_brake_mode(MOTOR_BRAKE_HOLD);
  if (master.get_digital(DIGITAL_B)){
    intake = power;
  } else if (master.get_digital(DIGITAL_A)){
    intake = -power;
  }else{
    intake = 0;
}
}

void intakeOPVel(int vel){
  intake.set_brake_mode(MOTOR_BRAKE_HOLD);
  if (master.get_digital(DIGITAL_B)){
    intakeVelocity(vel);
  } else if (master.get_digital(DIGITAL_A)){
    intakeVelocity(vel);
  }else{
    intake = 0;
}
}

//AUTONOMOUS
