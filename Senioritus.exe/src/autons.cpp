#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/adi.h"
#include "pros/rtos.h"
#include "pros/rtos.hpp"
#include "subsystems.hpp"
#include "autons.hpp"

void right() {
    // Calibrate Odometry and Set Starting Pose
    chassis.calibrate(true);
    pros::delay(1500);
    chassis.setPose(0, 0, 0);
    Blocker.move(0);
    // Grab First 3 Balls
    Intake.move(127);
    chassis.moveToPose(-1.98, 22.5, 40, 4000, {.maxSpeed = 80});
    chassis.waitUntilDone();
    chassis.moveToPoint(6.02, 30.5, 4000, {.maxSpeed = 80});
    pros::delay(2000);
    Intake.move(0);
    chassis.waitUntilDone();
    // Score Balls into Low Goal
    chassis.moveToPose(-4.228, 41.969, -45, 4000, {.maxSpeed = 80});
    pros::delay(1500);
    Intake.move(-80);
    pros::delay(1500);
    Intake.move(127);
    // Back Out and Reposition for Next 3 Balls
    chassis.moveToPoint(0.772, 36.969, 4000, {.forwards = false, .maxSpeed = 80});
    chassis.waitUntilDone();
    chassis.moveToPose(30.347, -2.863, 180, 4000, {.maxSpeed = 80});
    pros::delay(1500);
    Scraper.set_value(true);
    // Score on High Goal
    chassis.moveToPoint(30.347, 24.13, 4000, {.forwards = false, .maxSpeed = 80});
}

void rightWP() {
    // Code here
}

void left() {
    // Code here
    chassis.calibrate(true);
    chassis.setPose(0, 0, 0);
    // HighLow.move(-127);
    Blocker.move(0);
    chassis.moveToPose(-15, 22.5, 45, 4000, {.minSpeed = 60, .earlyExitRange = 6});
    chassis.waitUntilDone();
    Intake.move(127);
    chassis.moveToPoint(25, 30, 4000, {.maxSpeed = 40});
    chassis.swingToHeading(80, lemlib::DriveSide::RIGHT, 3000, {.direction = AngularDirection::CW_CLOCKWISE, .maxSpeed = 50});
    chassis.waitUntilDone();
    chassis.swingToHeading(45, lemlib::DriveSide::RIGHT, 3000, {.direction = AngularDirection::CCW_COUNTERCLOCKWISE});
    chassis.moveToPoint(25, 30, 4000, {.forwards = false, .maxSpeed = 40});
    chassis.moveToPoint(30, 35, 4000);
    Intake.move(127);
}

void leftWP() {
    // Code here
}

void odom_test() {
    // Code here
    // set position to x:0, y:0, heading:0
    chassis.calibrate(true);
    pros::delay(1500);
    chassis.setPose(0, 0, 0);
    chassis.moveToPoint(0, 48, 40000);
}