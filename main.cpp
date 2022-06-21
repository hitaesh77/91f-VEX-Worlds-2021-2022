#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2,  std::to_string(distInF()));
		pros::lcd::set_text(3,  std::to_string(distInB()));
	//	pros::lcd::set_text(3,  std::to_string(RTrack.get_value()));
		pros::lcd::set_text(4,  std::to_string(imuL.get_rotation()));
		pros::lcd::set_text(5,  std::to_string(imuR.get_rotation()));
	//	pros::lcd::set_text(6,  std::to_string(armPot.get_value()));
	} else {
		pros::lcd::clear_line(0);
	}
}

int n = 0;
int auton = 0;

void debugTask(){
	while(true){
		pros::lcd::print(2, "(%f, %f)", x, posY);
		pros::lcd::print(3, "Angle: %lf", (angle/M_PI * 180.0));
		pros::lcd::print(5, "Angle: %f", test);
		pros::lcd::print(4, "Angle: %lf", imuR.get_rotation());
		pros::delay(20);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void initialize() {
	pros::lcd::initialize();

//	 x,y,angle,diff = 0;
	//pros::lcd::register_btn1_cb(on_center_button);
	armL.set_brake_mode(MOTOR_BRAKE_HOLD);
	//armR.set_brake_mode(MOTOR_BRAKE_HOLD);
//	wing(false);
	clawS(true);
	mogoS(true);
	pros::delay(500);
	imuL.reset();
	//imuR.reset();
//	RTrack.reset();
	pros::delay(2500);
	armL.set_brake_mode(MOTOR_BRAKE_HOLD);
//	armR.set_brake_mode(MOTOR_BRAKE_HOLD);
/*	int time = pros::millis();
	int iter = 0;
		while (imuL.is_calibrating()) {
			printf("IMU calibrating... %d\n", iter);
			iter += 10;
			pros::delay(10);
		}
		// should print about 2000 ms
		printf("IMU is done calibrating (took %d ms)\n", iter - time);
*/

//Tasks
//	tracking = new pros::Task(Jaytrack, TASK_PRIORITY_MAX,TASK_STACK_DEPTH_DEFAULT, "tracking");
//	pros::Task debug_task(debugTask);
//  pros::delay(200);

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
armL.set_brake_mode(MOTOR_BRAKE_HOLD);
	const int autoCount = 10;
	  const char* autoNames[autoCount] = {
	    "WP AUTON",
	    "RIGHT RUSH",
	    "LEFT RUSH",
	    "BOTH ONE",
	    "Do NOthing",
	    "160+ Prog Skills",
			"bad",
			"bad",
	    "bad",
	    "bad"
	  };

	  pros::lcd::set_text(0, "Select an Auton");
	  pros::lcd::print(2, "%s", autoNames[auton]);

	//	cleanReset();

	  while(1){
			armL.set_brake_mode(MOTOR_BRAKE_HOLD);
			//armR.set_brake_mode(MOTOR_BRAKE_HOLD);
	    if(selectLimit.get_new_press()) {
	      auton++;
	      if(auton == autoCount)
	        auton = 0;

	      pros::lcd::print(2, "%s", autoNames[auton]);
				pros::lcd::print(3, "%d", auton);
	    }

	    pros::delay(50);
	  }

}

void autonomous() {

		autonhandler(auton);
	//	leftMogoRush();

//	wpAuton();

	//	armPD(2700, 0.72, 0.0, 127, 20, 2);

	//	driveDistIME(2, 2, 0.25, 0.7, 2, 100, 20, 0, 0, 1);
	//	imuGlobal(90, 1.5, 0.4, 3, 100, 2, 1);
		//rightTwoMogoGrab();
	//	leftYellowRed();
		//leftOne();
	//	progSkills();

}

void opcontrol() {
	while (true) {

		on_center_button();
		//arcadeOP(0);
		setOP(0);
		armOP(127);
		intakeOPVel(450);
		clawOP();
	//	wingOP();
		mogoOP();
	//	clampOP();

		pros::delay(20);

	}
}
