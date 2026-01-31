#pragma once

#include "lemlib/api.hpp"
#include "pros/abstract_motor.hpp"

using namespace pros;

inline Controller master(E_CONTROLLER_MASTER);
inline Motor Intake(-1, MotorGears::blue);
inline Motor Blocker(15, MotorGears::blue);

inline adi::DigitalOut Descore('G');
inline adi::DigitalOut Scraper('H');