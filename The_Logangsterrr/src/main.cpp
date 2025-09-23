#include "main.h"
#include "lemlib/api.hpp"

// using namespace lemlib;

// Global auton selector state
int current_auton_selection = 0;
bool auto_started = false;

// Create a controller object for the master controller
pros::Controller master(pros::E_CONTROLLER_MASTER);

// Creates a motor group with forwards ports 3, 2 and 1
pros::MotorGroup left_mg({3, 2, 1});
// left_mg.set_gearing(pros::v5::MotorGears::blue);
// Creates a motor group with reversed ports 11, 12 and 13
pros::MotorGroup right_mg({-11, -12, -13});
// right_mg.set_gearing(pros::v5::MotorGears::blue);
// Intake
pros::MotorGroup Intake({14, 15});
// Intake.set_gearing(pros::v5::MotorGears::blue);
// HighLow Motor
pros::Motor HighLow(16);
// HighLow.set_gearing(pros::v5::MotorGears::green);
// Descrore Pneumatics
pros::adi::DigitalOut Descore('A');
// Drivetrain settings
lemlib::Drivetrain drivetrain(left_mg, // Left motor group
                              right_mg, // Right motor group
                              10.0f, // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
                              360.0f, // drivetrain rpm is 360
                              2.0f // horizontal drift is 2 (for now)
);

// Create an imu on port 10
pros::Imu imu(10);

// Horizontal tracking wheel encoder
pros::Rotation horizontalTracker(20);
// Vertical tracking wheel encoder
pros::Rotation verticalTracker(19);
// Horizontal tracking wheel
lemlib::TrackingWheel horizontalTrackingWheel(&horizontalTracker, lemlib::Omniwheel::NEW_275, -5.75);
// Vertical tracking wheel
lemlib::TrackingWheel verticalTrackingWheel(&verticalTracker, lemlib::Omniwheel::NEW_275, -2.5);

// odometry settings
lemlib::OdomSensors sensors(&verticalTrackingWheel, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &horizontalTrackingWheel, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// lateral PID controller
lemlib::ControllerSettings lateralController(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angularController(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// create the chassis
lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateralController, // lateral PID settings
                        angularController, // angular PID settings
                        sensors // odometry sensors
);

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
	while (true) { // infinite loop
        // print measurements from the vertical tracker
        pros::lcd::print(0, "Vertical Tracker: %d", verticalTracker.get_value());
        // print measurements from the horizontal tracker
        pros::lcd::print(1, "Horizontal Tracker: %d", horizontalTracker.get_position());
        pros::delay(10); // delay to save resources. DO NOT REMOVE
    }
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

	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		(pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		(pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);  // Prints status of the emulated screen LCDs
		
		// Tank Control Scheme
		// Get left y and right y positions
		int leftY = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
		int rightY = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);

		// move the robot
		chassis.tank(leftY, rightY); // Sets right motor voltage to right joystick vertical axis
		
		if (master.get_digital(DIGITAL_R1)) {
			Intake.move(127);
		}
		else if (master.get_digital(DIGITAL_R2)) {
			Intake.move(-127);
		}
		else {
			Intake.move(0);
		}

		if (master.get_digital(DIGITAL_X)) {
			HighLow.move(127);
		}
		else if (master.get_digital(DIGITAL_B)) {
			HighLow.move(-127);
		}
		else {
			HighLow.move(0);
		}

		if (master.get_digital(DIGITAL_L1)) {
			Descore.set_value(true);
		}
		else if (master.get_digital(DIGITAL_L2)) {
			Descore.set_value(false);
		}
					

		pros::delay(20);  // Run for 20 ms then update
	}
}