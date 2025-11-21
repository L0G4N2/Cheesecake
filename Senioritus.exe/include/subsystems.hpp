#pragma once

#include "lemlib/api.hpp"
#include "pros/abstract_motor.hpp"

using namespace pros;

inline Controller master(E_CONTROLLER_MASTER);
inline Motor S(2);
inline Motor Front(-1, pros::MotorGears::blue);
inline MotorGroup Intake({2, -1}); // Creates a motor group for the Intake
inline Motor HighLow(10);
inline adi::DigitalOut Blocker('A');