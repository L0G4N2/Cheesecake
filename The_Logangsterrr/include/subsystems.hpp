#pragma once

#include "lemlib/api.hpp"

// Drivetrain settings
// Create a controller object for the master controller
inline pros::Controller master(pros::E_CONTROLLER_MASTER);

// Intake
inline pros::MotorGroup Intake({2, -1}, pros::MotorGearset::blue);
// HighLow Motor
inline pros::Motor HighLow(10, pros::MotorGearset::green);
// Descrore Pneumatics
inline pros::adi::DigitalOut Descore('A');