/*
DCMotorController it is responsible for the control of 4 DC motors,

receives commands through TX / RX serial ports, and performs the appropriate behavior for each received command,

thus moving theft in all directions.

Created by Ricardo Sabino, November, 2016.

Released into the public domain.
*/

//Sets the pins of the front engines
#define RIGHT_FRONT_ENGINE_IN1 52
#define RIGHT_FRONT_ENGINE_IN2 50
#define FRONT_LEFT_ENGINE_IN3 48
#define FRONT_LEFT_ENGINE_IN4 46

//Defines the pins of the rear engines
#define RIGHT_REAR_ENGINE_IN1 31
#define RIGHT_REAR_ENGINE_IN2 33
#define LEFT_REAR_ENGINE_IN3 35
#define LEFT_REAR_ENGINE_IN4 37

//Orientation
#define FORWARD "f"
#define BACK "r"
#define LEFT "e"
#define RIGHT "d"

//Sets the output pins
void setPinModeOut(int engine)
{
	pinMode(engine, OUTPUT);
}

//Active at high logic level, the pins responsible for DC motor rotation
void active5V(int engine)
{
	digitalWrite(engine, HIGH);
}

//Active at low logic level, the pins responsible for the rotation of the DC motor
void activeGND(int engine)
{
	digitalWrite(engine, LOW);
}

//Sets the delay time between received commands
void runtime(int timeDelay) {
	delay(timeDelay);
	stopTheRobot();
}

void setup()
{
	Serial.begin(9600);

	setPinModeOut(RIGHT_FRONT_ENGINE_IN1);
	setPinModeOut(RIGHT_FRONT_ENGINE_IN2);
	setPinModeOut(FRONT_LEFT_ENGINE_IN3);
	setPinModeOut(FRONT_LEFT_ENGINE_IN4);

	setPinModeOut(RIGHT_REAR_ENGINE_IN1);
	setPinModeOut(RIGHT_REAR_ENGINE_IN2);
	setPinModeOut(LEFT_REAR_ENGINE_IN3);
	setPinModeOut(LEFT_REAR_ENGINE_IN4);
}

//Engine movement clockwise
void engineMovementClockwise(int pinIn1, int pinIn2) {
	active5V(pinIn1);
	activeGND(pinIn2);
}

//Engine movement counterclockwise
void engineMovementCounterclockwise(int pinIn1, int pinIn2) {
	activeGND(pinIn1);
	active5V(pinIn2);
}

//Dead-spot
void deadSpot(int pinIn1, int pinIn2) {
	activeGND(pinIn1);
	activeGND(pinIn2);
}

//Braked engine
void braked(int pinIn1, int pinIn2) {
	active5V(pinIn1);
	active5V(pinIn2);
}

//Move the robot forward
void moveTheRobotForward()
{
	engineMovementClockwise(RIGHT_FRONT_ENGINE_IN1, RIGHT_FRONT_ENGINE_IN2);
	engineMovementCounterclockwise(FRONT_LEFT_ENGINE_IN3, FRONT_LEFT_ENGINE_IN4);
	engineMovementClockwise(LEFT_REAR_ENGINE_IN3, LEFT_REAR_ENGINE_IN4);
	engineMovementCounterclockwise(RIGHT_REAR_ENGINE_IN1, RIGHT_REAR_ENGINE_IN2);
}

//Move the robot back
void moveTheRobotBack()
{
	engineMovementCounterclockwise(RIGHT_FRONT_ENGINE_IN1, RIGHT_FRONT_ENGINE_IN2);
	engineMovementClockwise(FRONT_LEFT_ENGINE_IN3, FRONT_LEFT_ENGINE_IN4);
	engineMovementCounterclockwise(LEFT_REAR_ENGINE_IN3, LEFT_REAR_ENGINE_IN4);
	engineMovementClockwise(RIGHT_REAR_ENGINE_IN1, RIGHT_REAR_ENGINE_IN2);
}

//Stop the robot
void stopTheRobot()
{
	braked(RIGHT_FRONT_ENGINE_IN1, RIGHT_FRONT_ENGINE_IN2);
	braked(FRONT_LEFT_ENGINE_IN3, FRONT_LEFT_ENGINE_IN4);
	braked(RIGHT_REAR_ENGINE_IN1, RIGHT_REAR_ENGINE_IN2);
	braked(LEFT_REAR_ENGINE_IN3, LEFT_REAR_ENGINE_IN4);
}

//Rotate the robot right
void rotateTheRobotRight()
{
	engineMovementCounterclockwise(FRONT_LEFT_ENGINE_IN3, FRONT_LEFT_ENGINE_IN4);
	engineMovementCounterclockwise(RIGHT_REAR_ENGINE_IN1, RIGHT_REAR_ENGINE_IN2);
	braked(RIGHT_FRONT_ENGINE_IN1, RIGHT_FRONT_ENGINE_IN2);
	braked(LEFT_REAR_ENGINE_IN3, LEFT_REAR_ENGINE_IN4);
}

//Rotate the robot left
void rotateTheRobotLeft()
{
	engineMovementClockwise(RIGHT_FRONT_ENGINE_IN1, RIGHT_FRONT_ENGINE_IN2);
	engineMovementClockwise(LEFT_REAR_ENGINE_IN3, LEFT_REAR_ENGINE_IN4);
	braked(FRONT_LEFT_ENGINE_IN3, FRONT_LEFT_ENGINE_IN4);
	braked(RIGHT_REAR_ENGINE_IN1, RIGHT_REAR_ENGINE_IN2);
}

void loop() {
	if (Serial.available() > 0) {
		auto timeDelay = 2000;
		auto commandRead = Serial.readString();
		if (commandRead.equals(FORWARD)) {
			moveTheRobotForward();
			runtime(3000);
		}
		if (commandRead.equals(BACK)) {
			moveTheRobotBack();
			runtime(timeDelay);
		}
		if (commandRead.equals(LEFT)) {
			rotateTheRobotLeft();
			runtime(timeDelay);
		}
		if (commandRead.equals(RIGHT)) {
			rotateTheRobotRight();
			runtime(timeDelay);
		}
	}
}
