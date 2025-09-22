#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;

// Your motors, sensors, etc. should go here.  Below are examples

// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');

inline pros::MotorGroup Intake(14, 15);
inline pros::adi::DigitalOut Descore('A');
inline pros::Motor HighLow(6);