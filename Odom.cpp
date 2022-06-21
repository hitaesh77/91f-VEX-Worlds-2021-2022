#include "main.h"
float spinToInLR = (rWheelDiam * 3.14159265) / tpr;
//Jay Odom Pog
float x,y,angle,diff = 0;
bool trackenabled = true;

double filter(const double& currentVal, const double& lastVal){
  double filteredVal = currentVal - lastVal;
  if(fabs(filteredVal) < 0.01){
    filteredVal = 0;
  }
  return filteredVal;
}

void Jaytrack(){
  //Reset Sensors
//  MTrack.reset();
  RTrack.reset();

  //Robot Constants
  float Sr = -7.00, // distance from tracking center to middle of right wheel
        Ss = -4.125, // distance from tracking center to middle of the tracking wheel
        wheelDiameter = 2.75, // diameter of the side wheels being used for tracking
        trackingDiameter = 2.75, // diameter of the sideways tracking wheel
        scaleFactor = 1.0, // gear ratio, slop, etc. adjustment for right wheel
        scaleFactorS = 1.0, // gear ratio, slop, etc. adjustment for side wheel

  //Theta Values
        deltaTheta = 0, // change in angle between refresh cycles
        alpha = 0, // average angle robot took over interval (deltaTheta/2)
        theta = 0, // average angle between average angle and final
        radius = 0, // radius of the arc traveled by bot
        thetaFiltered = 0, // theta value that has been filtered
        thetaNew = 0, // current angle after filter
        thetaAvg = 0, // average theta of refresh
        curRotation = 0, // current raw angle
        lastRotation = 0, // previous interval raw angle

  //Encoder Values
        curRight = 0, // current rotations of right wheel
        curSide = 0, // current rotations of side wheel
        lastRight = 0, // previous interval rotations of right wheel
        lastSide = 0, // previous interval rotations of side wheel
        deltaRight = 0, // distance traveled by right wheel over interval in inches
        deltaSide = 0, // distance traveled by side wheel over interval in inches
        rightRadius = 0, // supporting value in calculation of rightCord
        rightCord = 0, // translation of right wheel
        sideRadius = 0, // supporting value in calculation of sideCord
        sideCord = 0, // translation of side wheel

        iL, iR, iB,
        lL, lR, lB,
        cL = 1, cR =1, cB = 1,
        Li = imuL.get_rotation(),
        Ri = imuR.get_rotation();
      //  Li = 0,
      //  Ri = 0;

  while(trackenabled){

    //Robot angle calculations
    iL = (imuL.get_rotation() - Li - diff) * cL;
    iR = (imuR.get_rotation() - Ri - diff) * cR;

    curRotation = iR;
    //if(iL > iR){
    //  curRotation = iL;
    //}

  //  thetaFiltered += filter(curRotation, lastRotation);
    thetaFiltered += curRotation - lastRotation;
    lastRotation = curRotation;
    //thetaNew = degToRad(thetaFiltered);
    deltaTheta = degToRad(thetaFiltered);
  //  deltaTheta = thetaNew - angle;

    //Encoder position calculations
    curRight = RTrack.get_value() * 3.14159265/360 * scaleFactor;
  //  curSide = MTrack.get_value() * M_PI/360 * scaleFactorS;
    deltaRight = (curRight - lastRight)*(wheelDiameter);
  //  deltaSide = (curSide - lastSide)*(trackingDiameter);
    lastRight = curRight;
  //  lastSide = curSide;

    //Calculating wheel translations
    if(deltaTheta != 0){
    //  sideCord = (2*sin(deltaTheta/2))*(deltaSide/deltaTheta + Ss); //step 8
      rightCord = (2*sin(deltaTheta/2))*(deltaRight/deltaTheta + Sr);
    }
    else{
       rightCord = deltaRight;
      // sideCord = deltaSide;
    }

    //Calculating average angle over interval
    thetaAvg = angle + deltaTheta/2;

    //Adding change in each polar axis to cartesian plane
    x += rightCord * sin(thetaAvg);
    y += rightCord * cos(thetaAvg);
  //  x += sideCord * -cos(thetaAvg);
  //  y += sideCord *  sin(thetaAvg);

    //Calculating values in this inverval
    angle += deltaTheta;

    test += 1;

    pros::delay(20);
  }
}

void Jaytrack1(){
  //Reset Sensors
//  MTrack.reset();
  RTrack.reset();

  //Robot Constants
  float Sr = -7.00, // distance from tracking center to middle of right wheel
        Ss = -4.125, // distance from tracking center to middle of the tracking wheel
        wheelDiameter = 2.75, // diameter of the side wheels being used for tracking
        trackingDiameter = 2.75, // diameter of the sideways tracking wheel
        scaleFactor = 1.0, // gear ratio, slop, etc. adjustment for right wheel
        scaleFactorS = 1.0, // gear ratio, slop, etc. adjustment for side wheel

  //Theta Values
        deltaTheta = 0, // change in angle between refresh cycles
        alpha = 0, // average angle robot took over interval (deltaTheta/2)
        theta = 0, // average angle between average angle and final
        radius = 0, // radius of the arc traveled by bot
        thetaFiltered = 0, // theta value that has been filtered
        thetaNew = 0, // current angle after filter
        thetaAvg = 0, // average theta of refresh
        curRotation = 0, // current raw angle
        lastRotation = 0, // previous interval raw angle

  //Encoder Values
        curRight = 0, // current rotations of right wheel
        curSide = 0, // current rotations of side wheel
        lastRight = 0, // previous interval rotations of right wheel
        lastSide = 0, // previous interval rotations of side wheel
        deltaRight = 0, // distance traveled by right wheel over interval in inches
        deltaSide = 0, // distance traveled by side wheel over interval in inches
        rightRadius = 0, // supporting value in calculation of rightCord
        rightCord = 0, // translation of right wheel
        sideRadius = 0, // supporting value in calculation of sideCord
        sideCord = 0, // translation of side wheel

        iL, iR, iB,
        lL, lR, lB,
        cL = 1, cR =1, cB = 1,
        Li = imuL.get_rotation(),
        Ri = imuR.get_rotation();

  while(trackenabled){

    int left = driveLF.get_position();
    int right = RTrack.get_value();
    float L = (left - lastDeltaL) * spinToInLR; // The amount the left side of the robot moved
  	float R = (right - lastDeltaR) * spinToInLR; // The amount the right side of the robot moved

  	// Update the last values
  	lastDeltaL = left;
  	lastDeltaR = right;

  	float h; // The hypotenuse of the triangle formed by the middle of the robot on the starting position and ending position and the middle of the circle it travels around
  	float i; // Half on the angle that I've traveled
  	float a = (L - R) / (lWidth + rWidth); // The angle that I've traveled
    float a2 = degToRad(imuL.get_rotation()) - lastA;
  	if (a2)
  	{
  		float r = R / a2; // The radius of the circle the robot travel's around with the right side of the robot
  		i = a2 / 2.0;
  		float sinI = sin(i);
  		h = ((r + rWidth) * sinI) * 2.0;

  	}
  	else
  	{
  		h = R;
  		i = 0;

  	}
  	float p = i + posA; // The global ending angle of the robot
  	float cosP = cos(p);
  	float sinP = sin(p);

  	// Update the global position
  	posY += h * cosP;
  	posX += h * sinP;

  	posA += a2;
    while (a2 > 2 * 3.14159265)
        a2 -= 2 * 3.14159265;
    while (a2 < -2 * 3.14159265)
        a2 += 2 * 3.14159265;

    lastA = degToRad(imuL.get_rotation());
    thetaDeg = radToDeg(a2);
    thetaRad = a2;

    pros::delay(10);
  }
}

void stopTracking(){
  if(tracking != nullptr){
    tracking->remove();
    delete tracking;
    tracking = nullptr;
  }
}

//Old Odom
//Physical Distances on the Bot, measured in inches from the center
float rWidth = 4.5;
float lWidth = 4.5;

//Diameter of Odom Wheels, in Inches/Degrees
float rWheelDiam = 3.25;
float lWheelDiam = 3.25;

//Ticks per rotation
float tpr = 540.0;

//float spinToInLR = (rWheelDiam * 3.14159265) / tpr;

//variables
float offset = 0;
float inert = 0;
float thetaRad = 0;
float thetaDeg = 0;
float currentL = 0;
float currentR = 0;
float deltaL = 0;
float deltaR = 0;
float lastDeltaL = 0;
float lastDeltaR = 0;
float lastA = 0;
float posX = 0;
float posY = 0;
float posA = 0;
bool isRunning = false;

void trackPositionENC(int left, int right){
  float L = (left - lastDeltaL) * spinToInLR; // The amount the left side of the robot moved
	float R = (right - lastDeltaR) * spinToInLR; // The amount the right side of the robot moved

	// Update the last values
	lastDeltaL = left;
	lastDeltaR = right;

	float h; // The hypotenuse of the triangle formed by the middle of the robot on the starting position and ending position and the middle of the circle it travels around
	float i; // Half on the angle that I've traveled
	float a = (L - R) / (lWidth + rWidth); // The angle that I've traveled
  float a2 = degToRad(imuL.get_rotation());
	if (a)
	{
		float r = R / a; // The radius of the circle the robot travel's around with the right side of the robot
		i = a / 2.0;
		float sinI = sin(i);
		h = ((r + rWidth) * sinI) * 2.0;

	}
	else
	{
		h = R;
		i = 0;

	}
	float p = i + posA; // The global ending angle of the robot
	float cosP = cos(p);
	float sinP = sin(p);

	// Update the global position
	posY += h * cosP;
	posX += h * sinP;

	posA += a;
}

void trackPositionIMU(){
  while(trackenabled){
  int left = driveLF.get_position();
  int right = RTrack.get_value();
  float L = (left - lastDeltaL) * spinToInLR; // The amount the left side of the robot moved
	float R = (right - lastDeltaR) * spinToInLR; // The amount the right side of the robot moved

	// Update the last values
	lastDeltaL = left;
	lastDeltaR = right;

	float h; // The hypotenuse of the triangle formed by the middle of the robot on the starting position and ending position and the middle of the circle it travels around
	float i; // Half on the angle that I've traveled
	float a = (L - R) / (lWidth + rWidth); // The angle that I've traveled
  float a2 = degToRad(imuL.get_rotation()) - lastA;
	if (a)
	{
		float r = R / a2; // The radius of the circle the robot travel's around with the right side of the robot
		i = a2 / 2.0;
		float sinI = sin(i);
		h = ((r + rWidth) * sinI) * 2.0;

	}
	else
	{
		h = R;
		i = 0;

	}
	float p = i + posA; // The global ending angle of the robot
	float cosP = cos(p);
	float sinP = sin(p);

	// Update the global position
	posY += h * cosP;
	posX += h * sinP;

	posA += a2;
  while (a2 > 2 * 3.14159265)
      a2 -= 2 * 3.14159265;
  while (a2 < -2 * 3.14159265)
      a2 += 2 * 3.14159265;

  lastA = degToRad(imuL.get_rotation());
  thetaDeg = radToDeg(a2);
  thetaRad = a2;

  pros::delay(10);
  }
}
