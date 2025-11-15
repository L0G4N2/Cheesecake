#pragma once

#include "lemlib/api.hpp"

using namespace pros;

inline Controller master(E_CONTROLLER_MASTER);
inline MotorGroup Intake({2, -1}); // Creates a motor group for the Intake
inline Motor HighLow(10);
inline adi::DigitalOut Blocker('D');