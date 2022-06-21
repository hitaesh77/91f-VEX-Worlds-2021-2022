#include "main.h"
#include <math.h>

float degToRad(float degrees){
  return degrees * 3.14159265 / 180;
}

float radToDeg(float radians){
  return radians * 180 / PI;
}
/*
float heading(){
  return ((LTrack.get_value() * L_SPIN_IN) - (RTrack.get_value() * R_SPIN_IN)) / (L_DISTANCE + R_DISTANCE);
}

float headingDeg(){
  return radToDeg(((LTrack.get_value() * L_SPIN_IN) - (RTrack.get_value() * R_SPIN_IN)) / (L_DISTANCE + R_DISTANCE));
}

int avgTrack(){
  return (LTrack.get_value() + RTrack.get_value()) / 2;
}
*/
int updateStrafe(){
  int deltaL = ( driveLF.get_position() - driveLB.get_position() ) / 2;
  int deltaR = ( driveRF.get_position() - driveRB.get_position() ) / 2;

  return (deltaL + deltaR) / 2;
}

float angle360( float angleDeg ) { //Takes an input angle in degrees and converts it to a positive angle value below 360.
  while(!(angleDeg >= 0 && angleDeg < 360)) {
    if( angleDeg < 0 ) { angleDeg += 360; }
    if(angleDeg >= 360) { angleDeg -= 360; }
  }
  return(angleDeg);
}

float angle180( float angleDeg ) { //Takes an input angle in degrees and converts it to an angle between -180 and 180.
  while(!(angleDeg >= -180 && angleDeg < 180)) {
    if( angleDeg < -180 ) { angleDeg += 360; }
    if(angleDeg >= 180) { angleDeg -= 360; }
  }
  return(angleDeg);
}

float mmtoIn(float mm){
  return (mm/25.4);
}

float distInB(){
  return mmtoIn(distB.get());
}

float distInF(){
  return mmtoIn(distF.get());
}

double imuFilter(const double& currentVal, const double& lastVal){
  double filteredVal = currentVal - lastVal;
  if(fabs(filteredVal) < 0.01){
    filteredVal = 0;
  }
  return filteredVal;
}
