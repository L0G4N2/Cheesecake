#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/adi.h"
#include "pros/rtos.h"
#include "pros/rtos.hpp"
#include "subsystems.hpp"
#include "autons.hpp"

// Unclogs Intake
void unclog() {
    Intake.move(-127);
    pros::delay(500);
    Intake.move(127);
    pros::delay(500);
    Intake.move(0);
}

// Drops the Scraper When the Robot is Approaching the Match Load
void dropScraper() {
    while (chassis.isInMotion()) {
        if (chassis.getPose().y > -0.965 && chassis.getPose().y < 3.765) {
            Scraper.set_value(true);
        }
        pros::delay(10);
    }
}

void right() {
    // Calibrate Odometry and Set Starting Pose
    chassis.calibrate(true);
    pros::delay(300);
    chassis.setPose(0, 0, 0);
    Blocker.move(0);
    // Grab First 3 Balls
    Intake.move(127);
    chassis.moveToPose(-1.98, 22.5, 43, 4000, {.maxSpeed = 80});
    chassis.waitUntilDone();
    chassis.moveToPoint(6.02, 30.5, 4000, {.maxSpeed = 90});
    pros::delay(1000);
    Intake.move(0);
    // Position at Match Load
    chassis.turnToHeading(150, 3500, {.direction = AngularDirection::CW_CLOCKWISE, .minSpeed = 50});
    chassis.waitUntilDone();
    chassis.moveToPoint(18.703, 19.19, 3700, {.minSpeed = 50});
    chassis.moveToPose(30.347, -0.863, 180, 3500, {.minSpeed = 40});
    pros::delay(100);
    Scraper.set_value(true);
    pros::delay(100);
    chassis.moveToPoint(30.347, -2.363, 2500);
    Intake.move(127);
    pros::delay(1350);
    // Score on High Goal
    chassis.moveToPoint(30.347, 24.13, 2000, {.forwards = false, .minSpeed = 90});
    chassis.waitUntilDone();
    Intake.move(127);
    Blocker.move(127);
}

void rightWP() {
    // Code here
}

void left() {
    // Calibrate Odometry and Set Starting Pose
    chassis.calibrate(true);
    pros::delay(300);
    chassis.setPose(0, 0, 0);
    Blocker.move(0);
    // Grab First 3 Balls
    Intake.move(127);
    chassis.moveToPose(1.98, 22.5, -43, 4000, {.maxSpeed = 80});
    chassis.waitUntilDone();
    chassis.moveToPoint(-6.02, 30.5, 4000, {.maxSpeed = 90});
    pros::delay(1000);
    Intake.move(0);
    // Position at Match Load
    chassis.turnToHeading(-150, 3500, {.direction = AngularDirection::CCW_COUNTERCLOCKWISE, .minSpeed = 50});
    chassis.waitUntilDone();
    chassis.moveToPoint(-18.703, 19.19, 3700, {.minSpeed = 50});
    chassis.moveToPose(-30.347, -0.863, 180, 3500, {.minSpeed = 40});
    pros::delay(100);
    Scraper.set_value(true);
    pros::delay(100);
    chassis.moveToPoint(-30.347, -2.363, 2500);
    Intake.move(127);
    pros::delay(1350);
    // Score on High Goal
    chassis.moveToPoint(-30.347, 24.13, 2000, {.forwards = false, .minSpeed = 90});
    chassis.waitUntilDone();
    Intake.move(127);
    Blocker.move(127);
}

void leftWP() {
    // Code here
}

void skills() {
    // Calibrate Odometry and Set Starting Pose
    chassis.calibrate(true);
    pros::delay(300);
    chassis.setPose(0, 0, 0);
    Blocker.move(0);
    // Position at Match Load
    chassis.moveToPose(-20.435, 21.206, -105, 4000, {.maxSpeed = 90});
    chassis.moveToPose(-30.347, -0.863, 180, 3700, {.maxSpeed = 90});
    pros::delay(100);
    Scraper.set_value(true);
    pros::delay(100);
    chassis.moveToPoint(-30.347, -2.863, 2500);
    Intake.move(127);
    pros::delay(2000);
    // Score on High Goal
    chassis.moveToPoint(-30.347, 24.13, 3700, {.forwards = false, .minSpeed = 90});
    chassis.waitUntilDone();
    Blocker.move(127);
    pros::delay(2000);
    Blocker.move(0);
    // Clear Match Load & Score
    chassis.moveToPose(-30.347, -2.363, 180, 2500);
    pros::delay(1500);
    chassis.moveToPoint(-30.347, 24.13, 3700, {.forwards = false, .minSpeed = 90});
    chassis.waitUntilDone();
    Blocker.move(127);
    pros::delay(3700);
    Scraper.set_value(false);
    Blocker.move(0);

    // Move to Right Side
    chassis.moveToPoint(-30.347, 9.137, 2000);
    chassis.moveToPose(10.273, 13.327, 55, 3000, {.minSpeed = 90});
    chassis.moveToPose(48.541, 20.916, 115, 3000, {.minSpeed = 60});
    chassis.waitUntilDone();
    // Move to Next Match Load
    chassis.moveToPose(63.375, -0.863, 180, 3700);
    pros::delay(100);
    Scraper.set_value(true);
    pros::delay(100);
    chassis.moveToPoint(63.375, -2.363, 2500);
    pros::delay(2000);
    // Score on High Goal
    chassis.moveToPoint(63.375, 24.137, 2500, {.forwards = false, .minSpeed = 90});
    chassis.waitUntilDone();
    Blocker.move(127);
    pros::delay(3700);
    Blocker.move(0);
    // Clear Match Load & Score
    chassis.moveToPose(63.375, -2.363, 180, 3000, {.maxSpeed = 90});
    pros::delay(1800);
    chassis.moveToPoint(63.375, 24.137, 2500, {.forwards = false, .minSpeed = 90});
    chassis.waitUntilDone();
    Blocker.move(127);
    pros::delay(3700);
    Scraper.set_value(false);
    Blocker.move(0);
}

void odom_test() {
    // Code here
    // set position to x:0, y:0, heading:0
    // Calibrate Odometry and Set Starting Pose
    chassis.calibrate(true);
    pros::delay(300);
    chassis.setPose(0, 0, 0);
    chassis.moveToPoint(0, 2, 3700);
    Intake.move(127);
    Blocker.move(127);
    pros::delay(3700);
    Intake.move(0);
    Blocker.move(0);
}