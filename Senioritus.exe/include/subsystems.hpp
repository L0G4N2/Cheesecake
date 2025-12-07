#pragma once

#include "lemlib/api.hpp"
#include "pros/abstract_motor.hpp"

using namespace pros;

inline Controller master(E_CONTROLLER_MASTER);
inline Motor Intake(-1, MotorGears::blue);
inline Motor Blocker(15, MotorGears::blue);
// inline Motor HighLow(10);
inline adi::DigitalOut HighLow('G');
inline adi::DigitalOut Scraper('H');
inline adi::DigitalOut Descore('C');