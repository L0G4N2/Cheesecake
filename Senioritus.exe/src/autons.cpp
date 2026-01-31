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
        if (chassis.getPose().y > -0.765 && chassis.getPose().y < 1.765) {
            Scraper.set_value(true);
        }
        pros::delay(10);
    }
}

void right() {
    // Calibrate Odometry and Set Starting Pose
    chassis.calibrate(true);
    pros::delay(1500);
    chassis.setPose(0, 0, 0);
    Blocker.move(0);
    // Grab First 3 Balls
    Intake.move(127);
    chassis.moveToPose(-1.98, 22.5, 43, 4000, {.maxSpeed = 80});
    chassis.waitUntilDone();
    chassis.moveToPoint(6.02, 30.5, 4000, {.maxSpeed = 90});
    pros::delay(2000);
    Intake.move(0);
    chassis.waitUntilDone();
    // Position at Match Load
    chassis.turnToHeading(150, 4000, {.direction = AngularDirection::CW_CLOCKWISE});
    chassis.moveToPoint(18.703, 19.19, 4000, {.maxSpeed = 100});
    chassis.moveToPose(30.347, -0.863, 180, 4000, {.maxSpeed = 100});
    dropScraper();
    chassis.moveToPoint(30.347, -5.863, 4000);
    // Score on High Goal
    chassis.moveToPoint(30.347, 24.13, 4000, {.forwards = false, .maxSpeed = 90});
    chassis.waitUntilDone();
    Intake.move(127);
    Blocker.move(127);
    pros::delay(2000);
    Blocker.move(0);
    // Clear Match Load & Score
    chassis.moveToPoint(30.347, -5.863, 4000);
    pros::delay(1300);
    chassis.moveToPoint(30.347, 24.13, 4000, {.forwards = false, .maxSpeed = 90});
    chassis.waitUntilDone();
    Blocker.move(127);
    pros::delay(2000);
    Intake.move(0);
    Blocker.move(0);
}

void rightWP() {
    // Code here
}

void left() {
    // Calibrate Odometry and Set Starting Pose
    chassis.calibrate(true);
    pros::delay(1500);
    chassis.setPose(0, 0, 0);
    Blocker.move(0);
    // Grab First 3 Balls
    Intake.move(127);
    chassis.moveToPose(1.98, 22.5, -43, 4000, {.maxSpeed = 80});
    chassis.waitUntilDone();
    chassis.moveToPoint(-6.02, 30.5, 4000, {.maxSpeed = 90});
    pros::delay(2000);
    Intake.move(0);
    chassis.waitUntilDone();
    // Position at Match Load
    chassis.moveToPose(-30.347, -0.863, 180, 4000, {.maxSpeed = 100});
    dropScraper();
    chassis.moveToPoint(-30.347, -5.863, 4000);
    // Score on High Goal
    chassis.moveToPoint(-30.347, 24.13, 4000, {.forwards = false, .maxSpeed = 90});
    chassis.waitUntilDone();
    Intake.move(127);
    Blocker.move(127);
    pros::delay(2000);
    Blocker.move(0);
    // Clear Match Load & Score
    chassis.moveToPoint(-30.347, -5.863, 4000);
    pros::delay(1300);
    chassis.moveToPoint(-30.347, 24.13, 4000, {.forwards = false, .maxSpeed = 90});
    chassis.waitUntilDone();
    Blocker.move(127);
    pros::delay(2000);
    Intake.move(0);
    Blocker.move(0);
}

void leftWP() {
    // Code here
}

void skills() {
    // Calibrate Odometry and Set Starting Pose
    chassis.calibrate(true);
    pros::delay(1500);
    chassis.setPose(0, 0, 0);
    Blocker.move(0);
    // Grab First 3 Balls
    Intake.move(127);
    chassis.moveToPose(1.98, 22.5, -43, 4000, {.maxSpeed = 80});
    chassis.waitUntilDone();
    chassis.moveToPoint(-6.02, 30.5, 4000, {.maxSpeed = 90});
    pros::delay(2000);
    Intake.move(0);
    chassis.waitUntilDone();
    // Position at Match Load
    chassis.moveToPose(-30.347, -0.863, 180, 4000, {.maxSpeed = 100});
    dropScraper();
    chassis.moveToPoint(-30.347, -5.863, 4000);
    // Score on High Goal
    chassis.moveToPoint(-30.347, 24.13, 4000, {.forwards = false, .maxSpeed = 90});
    chassis.waitUntilDone();
    Intake.move(127);
    Blocker.move(127);
    pros::delay(2000);
    Blocker.move(0);
    // Clear Match Load & Score
    chassis.moveToPoint(-30.347, -5.863, 4000);
    pros::delay(1800);
    chassis.moveToPoint(-30.347, 24.13, 4000, {.forwards = false, .maxSpeed = 90});
    chassis.waitUntilDone();
    Blocker.move(127);
    pros::delay(2000);
    Scraper.set_value(false);
    Blocker.move(0);

    // Grab Next Balls
    chassis.moveToPoint(-30.347, 9.137, 4000);
    chassis.moveToPose(32.016, 23.056, 48, 4000);
    chassis.waitUntilDone();
    chassis.moveToPoint(42.016, 33.056, 4000);
    pros::delay(2000);
    Intake.move(0);
    chassis.waitUntilDone();
    // Move to Next Match Load
    chassis.moveToPose(50.571, 16.484, 125, 4000);
    chassis.moveToPose(63.375, -0.863, 180, 4000);
    dropScraper();
    chassis.moveToPoint(63.375, -5.863, 4000);
    // Score on High Goal
    chassis.moveToPoint(63.375, 24.137, 4000, {.forwards = false, .maxSpeed = 90});
    chassis.waitUntilDone();
    Intake.move(127);
    Blocker.move(127);
    pros::delay(2000);
    Blocker.move(0);
    // Clear Match Load & Score
    chassis.moveToPoint(63.375, -5.863, 4000);
    pros::delay(1800);
    chassis.moveToPoint(63.375, 24.137, 4000, {.forwards = false, .maxSpeed = 90});
    chassis.waitUntilDone();
    Blocker.move(127);
    pros::delay(2000);
    Scraper.set_value(false);
    Intake.move(0);
    Blocker.move(0);
}

void odom_test() {
    // Code here
    // set position to x:0, y:0, heading:0
    chassis.calibrate(true);
    pros::delay(1500);
    chassis.setPose(0, 0, 0);
    chassis.moveToPoint(0, 48, 40000);
}