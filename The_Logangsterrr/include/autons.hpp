#pragma once
#include "lemlib/api.hpp"

// Declare the chassis object defined in main.cpp so other files can use it
extern lemlib::Chassis chassis;

// Declare your autonomous functions here
void RedRight();
void RedLeft();
void BlueRight();
void BlueLeft();
void TankOdomTest();