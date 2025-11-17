#include "main.h"
#include "pros/adi.h"
#include "pros/rtos.h"
#include "pros/rtos.hpp"
#include "subsystems.hpp"
#include "autons.hpp"

void right() {
    // Code here
    chassis.setPose(0, 0, 0);
    HighLow.move(-127);
    Blocker.set_value(true);
    chassis.moveToPose(13.8, 25.6, -45, 4000, {.maxSpeed = 110, .minSpeed = 80});
    Intake.move(50);
    pros::delay(500);
    Intake.move(0);
    chassis.turnToHeading(45-180, 3000, {.maxSpeed = 70});
    chassis.moveToPose(-3.2, 36.2, -45-180, 4000, {false});
    Intake.move(127);
    pros::delay(500);
    chassis.moveToPose(35.4, -7.1, 180, 4500);
}

void left() {
    // Code here
    // chassis.setPose(0, 0, 0);
    // HighLow.move(-127);
    // Blocker.set_value(true);
    // chassis.moveToPose(-13.8, 25.6, 45, 4000, {.maxSpeed = 80, .minSpeed = 50});
    // Intake.move(50);
    // pros::delay(500);
    // Intake.move(0);
    // chassis.turnToHeading(45-180, 4000, {.maxSpeed = 90});
    // chassis.moveToPose(-3.2, 32.2, 45-180, 4000, {false});
    // Intake.move(127);
    // pros::delay(1500);
    // chassis.moveToPose(-35.4, -7.1, 180, 4500);

    chassis.setPose(0, 0, 0);
    pros::delay(2000);
    HighLow.move(127);
    pros::delay(2000);
    chassis.moveToPose(-30, 0, -90, 4000);
    pros::delay(2000);
    chassis.turnToHeading(-180, 4000);
    pros::delay(2000);
    chassis.moveToPose(-30, 20, -180, 4000, {false});
    pros::delay(2000);
    Intake.move(127);
}

void odom_test() {
    // Code here
    // set position to x:0, y:0, heading:0
    // chassis.setPose(0, 0, 0);

    chassis.moveToPose(0, 50, 0, 4000);
    pros::delay(2000);
    chassis.moveToPose(50, 50, 90, 4000);
}