#include "main.h"
#include "autons.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "liblvgl/llemu.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rotation.hpp"
#include "pros/rtos.hpp"
#include "subsystems.hpp"

int autonSelector = 0;
bool autonStarted = false;

// left motor group
pros::MotorGroup left_mg({-11, -12, -13}, pros::MotorGears::blue);
// right motor group
pros::MotorGroup right_mg({18, 17, 20}, pros::MotorGears::blue);

// drivetrain settings
lemlib::Drivetrain drivetrain(&left_mg, // left motor group
                              &right_mg, // right motor group
                              11, // 11 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
                              450, // drivetrain rpm is 450
                              2 // horizontal drift is 2 (for now)
);

// imu
pros::Imu imu(16);
// horizontal tracking wheel encoder
pros::Rotation horizontal_tracker(6);
// vertical tracking wheel encoder
pros::Rotation vertical_tracker(-10);
// horizontal tracking wheel
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_tracker, lemlib::Omniwheel::NEW_325, -14);
// vertical tracking wheel
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_tracker, lemlib::Omniwheel::NEW_325, -5.5, 48.0/60.0);

// odometry settings
lemlib::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr /*&horizontal_tracking_wheel*/, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// lateral PID controller
lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
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
lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
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
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors
	chassis.setPose(0, 0, 0); // reset odometry position to 0, 0, 0
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	while (autonStarted == false) {
		switch (autonSelector) {
			case 0:
				pros::lcd::set_text(1, "Auton -> Right");
				break;
			case 1:
				pros::lcd::set_text(1, "Auton -> Right: Win Point");
				break;
			case 2:
				pros::lcd::set_text(1, "Auton -> Left");
				break;
			case 3:
				pros::lcd::set_text(1, "Auton -> Left: Win Point");
				break;
			case 4:
				pros::lcd::set_text(1, "Auton -> Skills");
				break;
			case 5:
				pros::lcd::set_text(1, "Auton -> Odom Test");
				break;
		}

		if (pros::lcd::read_buttons() & LCD_BTN_LEFT) {
			autonSelector--;
			if (autonSelector < 0) {
				autonSelector = 5;
			}
			pros::delay(300);
		}
		else if (pros::lcd::read_buttons() & LCD_BTN_RIGHT) {
			autonSelector++;
			if (autonSelector > 5) {
				autonSelector = 0;
			}
			pros::delay(300);
		}
		
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP) && master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
			autonomous();
		}
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A) && master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
			opcontrol();
		}

		pros::delay(20); // small delay to prevent wasted resources
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
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
	autonStarted = true;

	switch (autonSelector) {
		case 0:
			right();
			break;
		case 1:
			rightWP();
			break;
		case 2:
			left();
			break;
		case 3:
			leftWP();
			break;
		case 4:
			odom_test();
			break;
	}

	while (true) {
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A) && master.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
			autonStarted = false;
			competition_initialize();
		}

		pros::delay(200);
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
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);

	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);  // Prints status of the emulated screen LCDs

		// Tank control scheme
		int left = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
		int right = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);  // Gets amount forward/backward from right joystick
		left_mg.move(left);
		right_mg.move(right);

		// // Arcade control scheme
		// int dir = master.get_analog(ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
		// int turn = master.get_analog(ANALOG_RIGHT_X);  // Gets the turn left/right from right joystick
		// left_mg.move(dir - turn);                      // Sets left motor voltage
		// right_mg.move(dir + turn);                     // Sets right motor voltage

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			Intake.move(127);
		}
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			Intake.move(-127);
		}
		else {
			Intake.move(0);
		}

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			Blocker.move(127);
		}
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			Blocker.move(-127);
		}
		else {
			Blocker.move(0);
		}

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
			HighLow.set_value(false);
		}
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
			HighLow.set_value(true);
		}

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
			Descore.set_value(true);
		}
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
			Descore.set_value(false);
		}
		
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
			Scraper.set_value(true);
		}
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
			Scraper.set_value(false);
		}

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) && master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
			autonStarted = false;
			competition_initialize();
		}

		pros::delay(20);                               // Run for 20 ms then update
	}
}