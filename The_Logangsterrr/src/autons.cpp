#include "main.h"

ASSET(RedRight_1_txt);

void RedRight() {
	// Your code for the Red Right autonomous goes here
	
	// chassis.moveToPoint(20, 50, 90); // Move to (20, 50) facing 90 degrees
	chassis.setPose(0, 0, 90);
	Intake.move(127);
	chassis.follow(RedRight_1_txt, 15, 2000);
}

void RedLeft() {
	// Your code for the Red Left autonomous goes here
}

void BlueRight() {
	// Your code for the Blue Right autonomous goes here
}

void BlueLeft() {
	// Your code for the Blue Left autonomous goes here
}

void TankOdomTest() {
	// Your code for the Tank Odom Test autonomous goes here
}