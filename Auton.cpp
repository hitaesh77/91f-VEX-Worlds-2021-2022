#include "main.h"

//HOW TO TUNE DRIVE FUNCTIONS

//driveDistIME(float LTarget, float RTarget, float kp, float kd, int acc, int max, int tol, int lBruh, int rBruh, int brakeType);
//driveDistIME(target for left side of bot, target for right side of bot, p value of pid, d value of pid, slew rate acceleration, max voltage of bot, tolerance, dwai, dwai, base braketype);

//imuGlobal(float degrees, float kP, float kD, int acc, int max, float tol, int brakeType);
//imuGlobal(target degreees to turn, p value of pid, d value of pid, slew rate acceleration, max voltage, tolerance, base braketype);

//NOTES
//call me before u change anything
//dont just change the tolerance by some crazy amount, only change it by 1 or 2 at a time
//Seriously, call or text or ft me before u change anything
//Everything u need to change stuph in is this file and globals if u need to change ports
//Dont go to any other files unless I tell u too cuz u dont need to
//start the program at least 5 second sbefoe the match starts
//Save and build until the laptop says "nothing to be done" before downloading

//auton handler
void autonhandler(int auton) { //check global integer auton
   switch(auton) {
      case 0:
        wpAuton();
      case 1:
        leftYellowRed();
      case 2:
        leftMogoRush();;
      case 3:
        leftOne();
      case 4:
        doNothing();
      case 5:
        progSkills();
      case 6:
        progSkills();
      case 7:
        leftOne();
      case 8:
        leftOne();
      case 9:
        leftOne();

   }
}

//auton programs

//RIGHT THREE MOBILE GOALS
void rightTwoMogoGrab(){

  armL.set_brake_mode(MOTOR_BRAKE_HOLD);
//  armR.set_brake_mode(MOTOR_BRAKE_HOLD);

  //armPD(2590, 0.72, 0.8, 127, 50, 2);
  //wings up
  clawS(false);
  arm(-10);
  //wing(false);

  //Ditsance robot travels to the 2 yellow goals
  float errorTemp = 53 - distInB();

  driveDistIME(errorTemp/12, errorTemp/12, 0.6, 0.6, 50, 127, 50, 0, 0, 1);
  pros::Task armlol{[=] {
              pros::delay(500);
              clawS(true);
  }};

  clawS(true);

  //uncomment this later

  //arm(60);

  //How far robot move back
  float errorTemp1 = distInB() - 16;

  driveDistIME(-errorTemp1/12, -errorTemp1/12, 0.6, 0.6, 50, 127, 50, 0, 0, 1);

  clawS(false);

  pros::delay(700);

  driveDistIME(-1, -1, 0.7, 0.6, 50, 100, 50, 0, 0, 1);

  //turn to red mobile goal
  imuGlobal(-125, 1.9, 0.3, 2, 100, 5, 1);

  mogoS(false);

  pros::delay(1000);

  //time commands to get mobile goal and take it out
  drive(-60, -60);

  pros::delay(750);

  drive(0, 0);

//  mogoS(true);

  arm(100);
  pros::delay(500);
  arm(0);
/*
  drive(60, 60);
  pros::delay(500);
  drive(0, 0);
*/
  intake = 127;
  pros::delay(500);
  intake = 0;

  drive(80, -80);

  pros::delay(750);

  drive(0, 0);

  pros::delay(15000);

}

//AUTON PROGRAM TO GET leFT SIDE YELLOW AND RED MOGOs
void leftYellowRed(){

    armL.set_brake_mode(MOTOR_BRAKE_HOLD);
  //  armR.set_brake_mode(MOTOR_BRAKE_HOLD);

    //armPD(2590, 0.72, 0.8, 127, 50, 2);
    //wings up
    clawS(false);
    arm(-20);
    //wing(false);

    //Ditsance robot travels to the 2 yellow goals
    float errorTemp = 53 - distInB();

    driveDistIME(errorTemp/12, errorTemp/12, 0.6, 0.6, 50, 127, 50, 0, 0, 1);
    pros::Task armlol{[=] {
                pros::delay(500);
                clawS(true);
    }};

    clawS(true);

    pros::Task armhehe{[=] {
                armPD(1700, 0.72, 0.0, 127, 20, 2);
    }};


    while(distInB() > 15){
      drive(-127, -127);
    }

    drive(0, 0);

    pros::delay(500);

    //How far robot move back
    float errorTemp1 = distInB() - 26;

    driveDistIME(-errorTemp1/12, -errorTemp1/12, 0.6, 0.6, 2, 80, 50, 0, 0, 1);

    //clawS(false);

    pros::delay(500);

    //driveDistIME(-1, -1, 0.7, 0.6, 50, 100, 50, 0, 0, 1);

    //turn to red mobile goal
    imuGlobal(-90, 1.1, 0.8, 2, 60, 4, 1);

    pros::delay(300);

    driveDistIME(0.5, 0.5, 0.7, 0.6, 50, 100, 50, 0, 0, 1);

    mogoS(false);

    pros::delay(300);

    driveDistIME(-1.9, -1.9, 0.6, 0.7, 1, 40, 60, 0, 0, 1);

    mogoS(true);

    pros::delay(300);

    armPD(1800, 0.85, 0.0, 127, 70, 2);

    intakeVelocity(500);

    drive(50, 30);

    pros::delay(1400);

    drive(20, 55);

    pros::delay(1100);

    driveDistIME(2.5, 2.5, 0.6, 0.6, 2, 40, 50, 0, 2, 1);

    drive(-70, -90);

    pros::delay(1500);

    drive(0, 0);

    //driveDistIME(-1.5, -1.5, 0.6, 0.6, 2, 40, 50, 0, 2, 1);

    pros::delay(15000);
}

void leftMogoRush(){

    armL.set_brake_mode(MOTOR_BRAKE_HOLD);
  //  armR.set_brake_mode(MOTOR_BRAKE_HOLD);

    //armPD(2590, 0.72, 0.8, 127, 50, 2);
    //wings up
    clawS(false);
    arm(-20);
    //wing(false);

    //Ditsance robot travels to the 2 yellow goals
    float errorTemp = 53 - distInB();

    driveDistIME(errorTemp/12, errorTemp/12, 0.6, 0.6, 50, 127, 50, 0, 0, 1);
    pros::Task armlol{[=] {
                pros::delay(500);
                clawS(true);
    }};

    clawS(true);

    pros::Task armhehe{[=] {
                armPD(2500, 0.72, 0.0, 127, 20, 2);
    }};


    while(distInB() > 25){
      drive(-127, -127);
    }

    drive(0, 0);

    pros::delay(500);

    //How far robot move back
    float errorTemp1 = distInB() - 10;

    driveDistIME(-errorTemp1/12, -errorTemp1/12, 0.6, 0.6, 2, 80, 50, 0, 0, 1);

    //clawS(false);

    pros::delay(500);

    //driveDistIME(-1, -1, 0.7, 0.6, 50, 100, 50, 0, 0, 1);

    //turn to red mobile goal
    imuGlobal(-90, 1.3, 0.7, 2, 70, 4, 1);

    pros::delay(300);

    driveDistIME(1, 1, 0.7, 0.6, 50, 100, 50, 0, 0, 1);

/*
    mogoS(false);

    pros::delay(300);

    driveDistIME(-1.25, -1.25, 0.6, 0.7, 1, 40, 50, 0, 0, 1);

    mogoS(true);

    pros::delay(300);

    armPD(2200, 0.85, 0.0, 127, 70, 2);

    intakeVelocity(500);

    drive(50, 50);

    pros::delay(700);

    drive(0, 0);
*/
    pros::delay(15000);
}

//AUTON PROGRAM TO GET JUST ONE GOAL
void leftOne(){

  //wing(true);
  clawS(true);

  armPD(1700, 0.72, 0.0, 127, 20, 2);

  drive(40, 40);

  pros::delay(700);

  drive(0, 0);

  clawS(false);

  drive(-40, -40);

  pros::delay(500);

  drive(0, 0);

  clawS(false);

  //drive(-90, -90);

  //pros::delay(500);

  //drive(0, 0);

  pros::delay(15000);

}

//80 POINT PROG SKILLS PROGRAM
void progSkills(){

  armL.set_brake_mode(MOTOR_BRAKE_HOLD);

  //claw up
  clawS(false);
  mogoS(false);

  pros::delay(500);
  //arm(-5);
  //wing(false);

  //Ditsance robot travels to the 2 yellow goals
  float errorTemp = distInF() - 28;

  driveDistIME(errorTemp/12, errorTemp/12, 0.3, 0.6, 3, 70, 50, 0, 0, 1);

  mogoS(true);

  pros::delay(750);

  drive(60, 30);

  pros::delay(750);

  drive(0,0);

  imuGlobal(90, 1.4, 0.6, 2, 90, 3, 1);

  driveDistIME(1, 1, 0.3, 0.6, 3, 70, 50, 0, 0, 1);

  imuGlobal(0, 1.3, 0.8, 2, 80, 2, 1);

  float errorTemp3 = distInF() - 26;

  driveDistIME(errorTemp3/12, errorTemp3/12, 0.3, 0.6, 3, 70, 50, 0, 0, 1);

  imuGlobal(90, 1.2, 0.9, 2, 65, 2, 1);

  float errorTemp1 = 58 - distInB();

  driveDistIME(errorTemp1/12, errorTemp1/12, 0.3, 0.6, 3, 70, 50, 0, 0, 1);

  clawS(true);

  pros::delay(500);

  armPD(2000, 0.72, 0.0, 127, 80, 2);

  float errorTemp2 = distInF() - 44;

  driveDistIME(errorTemp2/12, errorTemp2/12, 0.3, 0.6, 3, 70, 50, 0, 0, 1);

  imuGlobal(180, 1.1, 1.1, 1, 50, 2, 1);

  intakeVelocity(600);

  driveDistIME(6, 6, 0.3, 0.6, 2, 60, 50, 0, 0, 1);

  driveDistIME(-2.8, -2.8, 0.3, 0.6, 2, 80, 50, 0, 0, 1);

  armPD(3000, 0.72, 0.0, 127, 80, 2);

  imuGlobal(90, 1.1, 1.1, 1, 50, 2, 1);

  driveDistIME(1.45, 1.45, 0.3, 0.6, 2, 60, 50, 0, 0, 1);

  arm(-90);
  pros::delay(900);
  arm(0);

  clawS(false);

  pros::delay(500);

  intakeVelocity(0);

  armPD(3000, 0.72, 0.0, 127, 80, 2);

  driveDistIME(-1.2, -1.2, 0.3, 0.6, 2, 60, 50, 0, 0, 1);

  pros::Task armlol{[=] {
              armPD(500, 0.72, 0.0, 70, 100, 2);
  }};

  mogoS(false);

  pros::delay(750);

  driveDistIME(0.7, 0.7, 0.3, 0.6, 2, 60, 50, 0, 0, 1);

  mogoS(true);

  imuGlobal(-90, 1.2, 1.0, 2, 70, 2, 1);

  driveDistIME(1, 1, 0.3, 0.6, 2, 60, 50, 0, 0, 1);

  clawS(true);

  pros::delay(500);

  pros::Task armhehe{[=] {
              armPD(2900, 0.72, 0.0, 127, 80, 2);
  }};

  driveDistIME(-0.2, -0.2, 0.5, 0.5, 2, 80, 70, 0, 0, 1);

  imuGlobal(90, 1.1, 1.1, 1, 50, 3, 1);

  driveDistIME(1.8, 1.8, 0.3, 0.6, 2, 60, 50, 0, 0, 1);

  //armPD(2600, 0.72, 0.0, 127, 80, 2);
  arm(-90);
  pros::delay(500);
  arm(0);

  clawS(false);

  driveDistIME(-1, -1, 0.3, 0.6, 2, 60, 50, 0, 0, 1);

  pros::Task armhehee{[=] {
              armPD(500, 0.72, 0.0, 110, 130, 2);
  }};

  imuGlobal(-90, 1.3, 1.0, 2, 60, 3, 1);

  driveDistIME(1.7, 1.7, 0.3, 0.6, 2, 60, 50, 0, 0, 1);

  clawS(true);

  pros::delay(500);

  armPD(1500, 0.72, 0.0, 127, 100, 2);

  driveDistIME(-2.6, -2.6, 0.3, 0.6, 2, 60, 50, 0, 0, 1);

  imuGlobal(180, 1.1, 1.1, 1, 50, 3, 1);

  arm(-90);
  pros::delay(700);
  arm(0);

  clawS(false);

  pros::delay(500);

  pros::Task armheheee{[=] {
              armPD(500, 0.72, 0.0, 110, 100, 2);
  }};

  driveDistIME(-2.5, -2.5, 0.3, 0.6, 2, 60, 50, 0, 0, 1);

  imuGlobal(0, 1.3, 1.0, 2, 70, 3, 1);

  driveDistIME(1.0, 1.0, 0.3, 0.6, 2, 60, 50, 0, 0, 1);

  clawS(true);

  pros::delay(500);

  driveDistIME(-0.5, -0.5, 0.4, 0.5, 3, 90, 50, 0, 0, 1);

  armPD(2800, 0.72, 0.0, 120, 100, 2);


  float errorTemp4 = distInF() - 30;
  driveDistIME(errorTemp4/12, errorTemp4/12, 0.3, 0.6, 3, 70, 50, 0, 0, 1);

  imuGlobal(-90, 1.3, 1.0, 2, 70, 3, 1);

  intakePower(127);

  driveDistIME(6, 6, 0.3, 0.6, 2, 60, 50, 0, 0, 1);

  float errorTemp5 = distInF() - 43;
  driveDistIME(errorTemp5/12, errorTemp5/12, 0.3, 0.6, 3, 70, 50, 0, 0, 1);

  imuGlobal(180, 1.3, 1.0, 2, 70, 3, 1);

  float errorTemp6 = 68 - distInB();
  driveDistIME(errorTemp6/12, errorTemp6/12, 0.3, 0.6, 3, 70, 50, 0, 0, 1);

  pros::Task armheheeee{[=] {
              armPD(3000, 0.72, 0.0, 110, 100, 2);
  }};

  imuGlobal(-90, 1.1, 1.2, 1, 60, 4, 1);

  intakePower(0);

  driveDistIME(1.5, 1.5, 0.3, 0.6, 2, 60, 50, 0, 0, 1);

  arm(-90);
  pros::delay(1000);
  arm(0);

  clawS(false);

  armPD(3000, 0.72, 0.0, 110, 100, 2);

  driveDistIME(-0.2, -0.2, 0.3, 0.6, 2, 60, 50, 0, 0, 1);

  imuGlobal(-55, 1.6, 0.9, 3, 90, 6, 1);

  drive(-100, -100);
  pros::delay(3000);
  drive(0,0);

  pros::delay(15000);

}

//160 POINT PROG SKILLS PROGRAM
void progSkills1(){

armL.set_brake_mode(MOTOR_BRAKE_HOLD);

  wing(false);
  clawS(true);

  //Distance to get goal from platform
  float errorTemp = 23 - distInB();

  driveDistIME(errorTemp/12, errorTemp/12, 0.32, 0.95, 3, 110, 40, 0, 0, 1);

  //clamp onto goal
  clawS(false);

  pros::delay(500);

  //raise arm
  armPD(400, 0.72, 0.8, 127, 50, 2);

  //Move distance
  float errorTemp1 = 26 - distInB();

  driveDistIME(errorTemp1/12, errorTemp1/12, 0.32, 0.95, 2, 90, 40, 0, 0, 1);

  //Turn to yellow goal in middle
  imuGlobal(90, 1.4, 0.95, 2, 110, 4, 1);

  //YOLO Move yellow goal distance LETS TRY SOMETHING HOPEFULLY HITAESH DOESNT KILL ME HEHE (CHANGED THE *-10* (ORIGINALLY FROM *-5) ALSO CHANGED *110* TO *60*))
  driveDistIME(-8.75, -8.75, 0.32, 0.95, 2, 60, 20, 0, 0, 1);

  //Move forward to get in front of platform
  driveDistIME(1.5, 1.5, 0.32, 0.95, 2, 110, 20, 0, 0, 1);

  //turn to move in front of the goal
  imuGlobal(0, 1.5, 0.8, 2, 90, 2, 1);

  //raise arm
  armPD(400, 0.72, 0.8, 127, 50, 2);

  //Move to center of goal
  float errorTemp3 = 65 - distInB();

  driveDistIME(errorTemp3/12, errorTemp3/12, 0.32, 0.95, 2, 90, 40, 0, 0, 1);

  pros::delay(250);

  //Move back to get rings out of the way
  float errorTemp4 = 61 - distInB();

  driveDistIME(errorTemp4/12, errorTemp4/12, 0.32, 0.95, 2, 90, 40, 0, 0, 1);

  //Move to face platform
  imuGlobal(-90, 1.5, 0.8, 2, 90, 2, 1);

  //raise arm
  armPD(400, 0.72, 0.8, 127, 50, 2);

  //Move to goal
  //driveDistIME(1.5, 1.5, 0.32, 0.95, 2, 110, 20, 0, 0, 1);

  drive(90, 90);
  pros::delay(1200);
  drive(60, 60);

  //Let go of blue mogo
  clawS(true);

//  driveDistIME(-1, -1, 0.32, 0.95, 2, 110, 20, 0, 0, 1);

  //raise arm
  armPD(400, 0.72, 0.8, 127, 50, 2);

  drive(60, 60);
  pros::delay(500);
  drive(0, 0);

  pros::delay(250);

  //Move backward
  driveDistIME(-1, -1, 0.32, 0.95, 2, 110, 20, 0, 0, 1);

  //Turn to face red mogo
  imuGlobal(180, 1.5, 0.8, 2, 90, 2, 1);

  //arm down
  armPD(1950, 0.72, 0.8, 127, 50, 2);

  drive(70, 70);
  pros::delay(1500);
  drive(0, 0);

//  float errorTemp5 = distInF() - 18;

//  driveDistIME(errorTemp5/12, errorTemp5/12, 0.32, 0.95, 2, 90, 40, 0, 0, 1);

  //grab red mogo
  clawS(false);

  pros::delay(500);

  driveDistIME(-2, -2, 0.32, 0.95, 2, 110, 20, 0, 0, 1);

  armPD(400, 0.72, 0.8, 127, 50, 2);

  imuGlobal(90, 1.5, 0.8, 2, 90, 2, 1);

  driveDistIME(5, 5, 0.32, 0.95, 2, 110, 20, 0, 0, 1);

  float errorTemp6 = distInF() - 36;

  driveDistIME(errorTemp6/12, errorTemp6/12, 0.32, 0.95, 2, 90, 40, 0, 0, 1);

  armPD(400, 0.72, 0.8, 127, 50, 2);

  imuGlobal(0, 1.5, 0.8, 2, 90, 2, 1);

  float errorTemp7 = 61 - distInB();

  driveDistIME(errorTemp7/12, errorTemp7/12, 0.32, 0.95, 2, 90, 40, 0, 0, 1);

  armPD(400, 0.72, 0.8, 127, 50, 2);

  imuGlobal(90, 1.6, 0.75, 2, 90, 4, 1);

  //driveDistIME(1.5, 1.5, 0.32, 0.95, 2, 110, 20, 0, 0, 1);

  armPD(400, 0.72, 0.8, 127, 50, 2);

  drive(60, 60);
  pros::delay(500);
  drive(0, 0);

  clawS(false);

  armPD(400, 0.72, 0.8, 127, 50, 2);

  driveDistIME(-1, -1, 0.32, 0.95, 2, 110, 20, 0, 0, 1);

  imuGlobal(0, 1.7, 0.7, 2, 90, 4, 1);

  armPD(400, 0.72, 0.8, 127, 50, 2);

  driveDistIME(2.5, 2.5, 0.32, 0.95, 2, 110, 20, 0, 0, 1);

  imuGlobal(90, 1.6, 0.7, 2, 90, 4, 1);

  armPD(400, 0.72, 0.8, 127, 50, 2);

  driveDistIME(1, 1, 0.32, 0.95, 2, 110, 20, 0, 0, 1);

  pros::delay(250);

  driveDistIME(-0.925, -0.925, 0.32, 0.95, 2, 110, 20, 0, 0, 1);

  imuGlobal(0, 1.5, 0.8, 2, 90, 2, 1);

  armPD(1950, 0.72, 0.8, 127, 50, 2);

  drive(70, 70);
  pros::delay(1000);
  drive(0, 0);

  clawS(true);

  float errorTemp8 = distInF() - 33.5;

  driveDistIME(errorTemp8/12, errorTemp8/12, 0.32, 0.95, 2, 90, 40, 0, 0, 1);

  imuGlobal(-90, 1.7, 0.7, 2, 90, 6, 1);

  armPD(400, 0.72, 0.8, 127, 50, 2);

  driveDistIME(7, 7, 0.32, 0.95, 2, 90, 40, 0, 0, 1);

  clawS(false);

  driveDistIME(-0.5, -0.5, 0.32, 0.95, 2, 110, 20, 0, 0, 1);

  imuGlobal(-45, 2.0, 0.5, 2, 100, 7, 1);

  driveDistIME(-9, -9, 0.32, 0.95, 2, 110, 20, 0, 0, 1);

  pros::delay(15000);

}

void wpAuton(){
  armL.set_brake_mode(MOTOR_BRAKE_HOLD);

  clawS(true);
  arm(-5);
  //wing(false);

  //Ditsance robot travels to the 2 yellow goals
  float errorTemp = distInF() - 28;

  driveDistIME(errorTemp/12, errorTemp/12, 0.6, 0.6, 2, 90, 50, 0, 0, 1);

  pros::delay(200);

  imuGlobal(90, 1.5, 0.6, 2, 70, 4, 1);

  pros::delay(200);

  mogoS(false);

  pros::delay(300);

  driveDistIME(-1.47, -1.47, 0.6, 0.6, 2, 60, 50, 0, 0, 1);

  mogoS(true);

  pros::delay(300);

  armPD(1400, 0.72, 0.0, 127, 20, 2);

  intakeVelocity(500);

  driveDistIME(8, 8, 0.6, 0.6, 2, 60, 50, 1, 0, 1);

  //How far robot move back
//  float errorTemp1 = distInF() - 27;

//  driveDistIME(errorTemp1/12, errorTemp1/12, 0.6, 0.6, 2, 60, 50, 0, 0, 1);

  intakeVelocity(0);

  imuGlobal(-11, 1.5, 0.5, 2, 90, 2, 1);

  driveDistIME(1.4, 1.4, 0.6, 0.6, 2, 60, 120, 0, 0, 1);

  clawS(false);

  mogoS(false);

  pros::delay(15000);
}

void doNothing(){
  pros::delay(15000);
}
