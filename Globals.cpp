#include "main.h"

pros::Motor driveLM(9, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRM(2, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor armL(1, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor armR(11, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor mogoNo(18, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor intake(10, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveLF(6, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRF(5, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveLB(7, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRB(3, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);


//CONTROLLER
pros::Controller master(pros::E_CONTROLLER_MASTER);

//SENSORS
//pros::ADIEncoder MTrack ('C', 'D', true);
pros::ADIEncoder RTrack ('A', 'B', false);

pros::ADIDigitalIn selectLimit('C');

pros::Imu imuL(4);
pros::Imu imuR(8);

pros::Distance distB(21);
pros::Distance distF(13);

pros::ADIDigitalOut wingL ('A');
pros::ADIDigitalOut wingR ('A');
pros::ADIDigitalOut claw ('H');
pros::ADIDigitalOut mogo ('F');
pros::ADIDigitalOut mogoT ('G');
pros::ADIDigitalOut mogoM ('E');

pros::ADIAnalogIn armPot ('D');

//VARIABLES
float PI = 3.14159265;

bool clawState = 0;

int test = 0;
//TASKS
//pros::Task *tracking = nullptr;
