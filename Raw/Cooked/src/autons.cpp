#include "main.h"
#include "autons.hpp"

void RedRight() {
    // Code here
    chassis.moveToPoint(50, 20, 4000,{true, 50, 30});
    Intake.move(127);
}

void RedLeft() {
    // Code here
    chassis.moveToPoint(20, 20, 90);
    Intake.move(127);
}

void BlueRight() {
    // Code here
    chassis.moveToPoint(20, 20, 90);
    Intake.move(127);
}

void BlueLeft() {
    // Code here
    chassis.moveToPoint(20, 20, 90);
    Intake.move(127);
}

void odom_test() {
    // Code here
    chassis.moveToPoint(20, 20, 90);
    Intake.move(127);
}