#include "main.h"
// #include "autons.cpp"
// #include "subsystems.hpp"

// using namespace lemlib;

// Global auton selector state
int current_auton_selection = 0;
bool auto_started = false;

void on_center_button() {
	/**
	 * A callback function for LLEMU's center button.
	 *
	 * When this callback is fired, it will toggle line 2 of the LCD text between
	 * "I was pressed!" and nothing.
	 */

	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

void initialize() {
	/**
	 * Runs initialization code. This occurs as soon as the program is started.
	 *
	 * All other competition modes are blocked by initialize; it is recommended
	 * to keep execution time for this mode under a few seconds.
	 */

	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

void disabled() {
	/**
	 * Runs while the robot is in the disabled state of Field Management System or
	 * the VEX Competition Switch, following either autonomous or opcontrol. When
	 * the robot is enabled, this task will exit.
	 */
}


void competition_initialize() {
	/**
	 * Runs after initialize(), and before autonomous when connected to the Field
	 * Management System or the VEX Competition Switch. This is intended for
	 * competition-specific initialization routines, such as an autonomous selector
	 * on the LCD.
	 *
	 * This task will exit when the robot is enabled and autonomous or opcontrol
	 * starts.
	 */

	while (!auto_started) {
		pros::screen::erase(); // clear the brain screen

		// Show the currently selected auton
		switch (current_auton_selection) {
			case 0:
				pros::screen::print(pros::E_TEXT_MEDIUM, 50, 50, "Red_Right");
				break;
			case 1:
				pros::screen::print(pros::E_TEXT_MEDIUM, 50, 50, "Red_Left");
				break;
			case 2:
				pros::screen::print(pros::E_TEXT_MEDIUM, 50, 50, "Blue_Right");
				break;
			case 3:
				pros::screen::print(pros::E_TEXT_MEDIUM, 50, 50, "Blue_Left");
				break;
			case 4:
				pros::screen::print(pros::E_TEXT_MEDIUM, 50, 50, "Tank_Odom_Test");
				break;
		}

		// Tap screen to cycle auton selection
		if (pros::screen::touch_status().touch_status == pros::E_TOUCH_PRESSED) {
			// Wait until finger lifted (prevents double-count)
			while (pros::screen::touch_status().touch_status == pros::E_TOUCH_PRESSED) {
				pros::delay(10);
			}
			current_auton_selection++;
		}

		// Loop back to 0 after last option
		if (current_auton_selection >= 5) {
			current_auton_selection = 0;
		}

		pros::delay(20); // Small delay to prevent wasted resources
	}
}
void autonomous() {
	/**
	 * Runs the user autonomous code. This function will be started in its own task
	 * with the default priority and stack size whenever the robot is enabled via
	 * the Field Management System or the VEX Competition Switch in the autonomous
	 * mode. Alternatively, this function may be called in initialize or opcontrol
	 * for non-competition testing purposes.
	 *
	 * If the robot is disabled or communications is lost, the autonomous task
	 * will be stopped. Re-enabling the robot will restart the task, not re-start it
	 * from where it left off.
	 */

	auto_started = true; // Flag to tell competition_initialize to stop
	switch (current_auton_selection) {
		case 0: // Red Right
			RedRight();
			break;
		case 1: // Red Left
			RedLeft();
			break;
		case 2: // Blue Right
			BlueRight();
			break;
		case 3: // Blue Left
			BlueLeft();
			break;
		case 4: // Tank Odom Test
			TankOdomTest();
			break;
	}
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	// Create a controller object for the master controller
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	// Creates a motor group with forwards ports 3, 2 and 1
	pros::MotorGroup left_mg({3, 2, 1});
	// Creates a motor group with reversed ports 11, 12 and 13
	pros::MotorGroup right_mg({-11, -12, -13});


	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);  // Prints status of the emulated screen LCDs

		// Tank Control Scheme
		left_mg.move(master.get_analog(ANALOG_LEFT_Y));   // Sets left motor voltage to left joystick vertical axis
		right_mg.move(master.get_analog(ANALOG_RIGHT_Y)); // Sets right motor voltage to right joystick vertical axis

		// // Arcade control scheme
		// int dir = master.get_analog(ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
		// int turn = master.get_analog(ANALOG_RIGHT_X);  // Gets the turn left/right from right joystick
		// left_mg.move(dir - turn);                      // Sets left motor voltage
		// right_mg.move(dir + turn);                     // Sets right motor voltage

		pros::delay(20);                               // Run for 20 ms then update
	}
}