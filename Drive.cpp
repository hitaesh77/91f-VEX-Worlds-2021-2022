#include "main.h"
#include <math.h>

//BASIC
void brake(){
	driveLF.move_velocity(0);
	driveRB.move_velocity(0);
	driveLB.move_velocity(0);
	driveRF.move_velocity(0);
	driveLM.move_velocity(0);
	driveRM.move_velocity(0);
}

void drive(int left, int right){
  if (left == 0 && right == 0){
		brake();
	}
  driveLF = left;
  driveRB = right;
  driveLB = left;
  driveRF = right;
	driveLM = left;
	driveRM = right;
}

void driveVel(int left, int right){
  if (left == 0 && right == 0){
		brake();
	}
  driveLF.move_velocity(left);
  driveRB.move_velocity(right);
  driveLB.move_velocity(left);
  driveRF.move_velocity(right);
	driveLM.move_velocity(left);
  driveRM.move_velocity(right);
}

void driveMove(int left, int right){
  if (left == 0 && right == 0){
		brake();
	}
  driveLF.move(left);
  driveRB.move(right);
  driveLB.move(left);
  driveRF.move(right);
	driveLM.move(left);
  driveRM.move(right);
}

void driveMV(int left, int right){
  if (left == 0 && right == 0){
		brake();
	}
  driveLF.move_voltage(left);
  driveRB.move_voltage(right);
  driveLB.move_voltage(left);
  driveRF.move_voltage(right);
}

float lVelocity = 0, maxChange = 600.0;
float slew(float velocity){
  float vOut;
  float deriv = velocity - lVelocity;
  if(deriv > maxChange){
    vOut = lVelocity + maxChange;
  }
  else{
    vOut = velocity;
  }
  lVelocity = vOut;
  return vOut;
}

void setBrake(int mode){
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

  driveLF.set_brake_mode(brakeMode);
  driveRF.set_brake_mode(brakeMode);
  driveLB.set_brake_mode(brakeMode);
  driveRB.set_brake_mode(brakeMode);
	driveLM.set_brake_mode(brakeMode);
  driveRM.set_brake_mode(brakeMode);
}

//OPCONTROL
void setOP(int brake){

  setBrake(brake);
  //get joystic values
  int left = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int right = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

  //set contorlle deadzone
  if(abs(left) < 10)
    left = 0;
  if(abs(right) < 10)
    right = 0;

  //drive base motors
  drive(left, right);
}

void arcadeOP(int brake){

  setBrake(brake);

  int power = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    //set controller deadzone
    if(abs(power) < 10)
      power = 0;
    if(abs(turn) < 10)
      turn = 0;

    //VELOCITY
    driveLF = (power + turn);
	  driveLB = (power + turn);
	  driveRF = (power - turn);
	  driveRB = (power - turn);
		driveLM = (power + turn);
	  driveRM = (power - turn);

}

//AUTON

//DRIVING

void driveDistIME(float LTarget, float RTarget, float kp, float kd, int acc, int max, int tol, int lBruh, int rBruh, int brakeType){
  setBrake(brakeType);
  int prevErrorL = 0;
  int prevErrorR = 0;
  int velCap = 0;
  int signLeft;
  int signRight;

  //ft to tick conversion
  float circum = 3.25 * PI;
  float circumft = circum / 12;
  float LTargetTick = ((LTarget / circumft) * 300 * 1.6666);
  float RTargetTick = ((RTarget / circumft) * 300 * 1.6666);

  driveLF.tare_position();
  driveRF.tare_position();

  int errorL = LTargetTick;
  int errorR = RTargetTick;

  while(abs(errorL) > tol){

    errorL = LTargetTick - driveLF.get_position();
    errorR = RTargetTick - driveRF.get_position();
    int derivativeL = errorL - prevErrorL;
    prevErrorL = errorL;
    int derivativeR = errorR - prevErrorR;
    prevErrorR = errorR;
    int speedL = errorL * kp + derivativeL * kd;
    int speedR = errorR * kp + derivativeR * kd;

    signLeft = errorL / abs(errorL);
    signRight = errorR / abs(errorR);

    if(speedL > max)
      speedL = max;
    if(speedL < -max)
      speedL = -max;

    if(speedR > max)
      speedR = max;
    if(speedR < -max)
      speedR = -max;

    //SLEW RATE
    velCap = velCap + acc;  //slew rate
    if(velCap > max)
      velCap = max; //velCap cannot exceed max

    if(abs(speedL) > velCap) //limit the voltage
      speedL = velCap * signLeft;

    if(abs(speedR) > velCap) //ditto
      speedR = velCap * signRight;

    drive(speedL - lBruh, speedR - rBruh);

    pros::delay(10);
  }
  drive(0,0);
}

//TURNING
void imuGlobal(float degrees, float kP, float kD, int acc, int max, float tol, int brakeType){
  setBrake(brakeType);
  float prevError = 0;
  int direction = abs(degrees) / degrees;
  int sign;
  int velCap = 0;

  float degreesG = angle360(degrees);

  float orientation = angle360(imuL.get_yaw());

  float error = angle180((degreesG - orientation));

  //float error = degrees;

  //drive(-voltage * direction, voltage * direction);
  while(abs(error) > tol){

    pros::lcd::set_text(4, std::to_string(direction));
		pros::lcd::set_text(5, std::to_string(imuL.get_yaw()));
    pros::lcd::set_text(6, std::to_string(degrees));

    orientation = angle360(imuL.get_yaw());

    error = angle180(degreesG - orientation);
    //error = degrees - imu.get_yaw();
    float derivative = error - prevError;
    prevError = error;
    float speed = error * kP + derivative * kD;

    sign = error / abs(error);

    if(speed > 127)
      speed = 127;
    if(speed < -127)
      speed = -127;

      velCap = velCap + acc;  //slew rate
      if(velCap > max)
        velCap = max; //velCap cannot exceed max

      if(abs(speed) > velCap) //limit the voltage
        speed = velCap * sign;

    drive(speed, -speed);

    pros::delay(10);
  }

  drive(0, 0);

}
