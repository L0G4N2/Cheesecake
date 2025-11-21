#include "lemlib/chassis/chassis.hpp"
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
    chassis.moveToPose(15, 15, -45, 4000, {.minSpeed = 60, .earlyExitRange = 6});
    chassis.waitUntilDone();
    Front.move(127);
    S.move(60);
    chassis.moveToPoint(-25, 30, 6000, {.maxSpeed = 40});
    chassis.swingToHeading(-90, lemlib::DriveSide::RIGHT, 3000, {.maxSpeed = 50});
}

void left() {
    // Code here
    chassis.setPose(0, 0, 0);
    HighLow.move(-127);
    Blocker.set_value(true);
    chassis.moveToPose(-15, 18, 45, 4000, {.minSpeed = 40, .earlyExitRange = 6});
    chassis.waitUntilDone();
    chassis.moveToPoint(20, 35, 4000, {.maxSpeed = 20});

    // Intake.move(50);
    // pros::delay(500);
    // Intake.move(0);
    // chassis.turnToHeading(45-180, 4000, {.maxSpeed = 90});
    // chassis.moveToPose(-3.2, 32.2, 45-180, 4000, {false});
    // Intake.move(127);
    // pros::delay(1500);
    // chassis.moveToPose(-35.4, -7.1, 180, 4500);
}

void odom_test() {
    // Code here
    // set position to x:0, y:0, heading:0
    // chassis.setPose(0, 0, 0);

    chassis.moveToPose(0, 50, 0, 4000);
    pros::delay(2000);
    chassis.moveToPose(50, 50, 90, 4000);
}