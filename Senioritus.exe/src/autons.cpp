#include "main.h"
#include "subsystems.hpp"
#include "autons.hpp"

void right() {
    // Code here
    chassis.setPose(0, 0, 0);
    HighLow.move(127);
    chassis.moveToPose(11.2, 29, 45, 4000);
    Intake.move(80);
    pros::delay(500);
    Intake.move(0);
    chassis.moveToPose(36, 0, 180, 4000);
    chassis.moveToPose(36, 17, 180, 4000, {false});
    Intake.move(127);
    pros::delay(1000);
    chassis.moveToPose(36, -10, 180, 4000);
    pros::delay(1000);
    chassis.moveToPose(36, 17, 180, 4000, {false});
    Intake.move(0);
    HighLow.move(0);
}

void left() {
    // Code here
    chassis.setPose(0, 0, 0);
    HighLow.move(127);
    chassis.moveToPose(-11.2, 29, -45, 4000);
    Intake.move(80);
    pros::delay(500);
    Intake.move(0);
    chassis.moveToPose(-36, 0, 180, 4000);
    chassis.moveToPose(-36, 17, 180, 4000, {false});
    Intake.move(127);
    pros::delay(1000);
    chassis.moveToPose(-36, -10, 180, 4000);
    pros::delay(1000);
    chassis.moveToPose(-36, 17, 180, 4000, {false});
    Intake.move(0);
    HighLow.move(0);
}

void odom_test() {
    // Code here
    // set position to x:0, y:0, heading:0
    chassis.setPose(-50, 0, 0);
    // move to point (0, 20) with a very long timeout
    chassis.moveToPose(0, 0, 0, 100000);
}