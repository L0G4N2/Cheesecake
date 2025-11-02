#pragma once

#include "lemlib/api.hpp"

inline pros::Controller master(pros::E_CONTROLLER_MASTER);
inline pros::MotorGroup Intake({2, -1}); // Creates a motor group for the Intake
inline pros::Motor HighLow(10);
inline pros::adi::DigitalOut Descore('A');