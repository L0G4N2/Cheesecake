#pragma once

#include "lemlib/api.hpp"
#include "pros/abstract_motor.hpp"

using namespace pros;

inline Controller master(E_CONTROLLER_MASTER);
inline Motor Front(-1, MotorGears::blue);
inline Motor S(-10, MotorGears::green);
inline MotorGroup Intake({-1, -10});
// inline Motor HighLow(10);
inline adi::DigitalOut HighLow('A');
inline adi::DigitalOut Blocker('B');
inline adi::DigitalOut Scraper('C');