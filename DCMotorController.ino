#define RIGHT_FRONT_ENGINE_IN1 3
#define RIGHT_FRONT_ENGINE_IN2 4
#define FRONT_LEFT_ENGINE_IN3 5
#define FRONT_LEFT_ENGINE_IN4 6
#define RIGHT_FRONT_ENGINE_ENA 2
#define FRONT_LEFT_ENGINE_ENB 7

#define RIGHT_REAR_ENGINE_IN1 9
#define RIGHT_REAR_ENGINE_IN2 10
#define LEFT_REAR_ENGINE_IN3 11
#define LEFT_REAR_ENGINE_IN4 12
#define RIGHT_REAR_ENGINE_ENA 8
#define LEFT_REAR_ENGINE_ENB 13



// Orientation
String command = "";
String FORWARD = "f";
String BACK = "b";
String LEFT = "l";
String RIGHT = "r";
String STOP = "s";


// Sets the output pins
void setPinModeOut(int engine)
{
  pinMode(engine, OUTPUT);
}

// Active at high logic level, the pins responsible for DC motor rotation
void active5V(int engine)
{
  digitalWrite(engine, HIGH);
}

// Active at low logic level, the pins responsible for the rotation of the DC motor
void activeGND(int engine)
{
  digitalWrite(engine, LOW);
}

// Sets the delay time between received commands
void runtime(int timeDelay)
{
  delay(timeDelay);
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

  analogWrite(RIGHT_FRONT_ENGINE_ENA, 255);
  analogWrite(FRONT_LEFT_ENGINE_ENB, 255);
  analogWrite(RIGHT_REAR_ENGINE_ENA, 255);
  analogWrite(LEFT_REAR_ENGINE_ENB, 255);
  delay(1000);
}

// Engine movement clockwise
void engineMovementClockwise(int pinIn1, int pinIn2)
{
  active5V(pinIn1);
  activeGND(pinIn2);
}

// Engine movement counterclockwise
void engineMovementCounterclockwise(int pinIn1, int pinIn2)
{
  activeGND(pinIn1);
  active5V(pinIn2);
}

// Dead-spot
void deadSpot(int pinIn1, int pinIn2)
{
  activeGND(pinIn1);
  activeGND(pinIn2);
}

// Braked engine
void braked(int pinIn1, int pinIn2)
{
  active5V(pinIn1);
  active5V(pinIn2);
}

// Move the robot forward
void moveTheRobotForward()
{
  engineMovementClockwise(RIGHT_FRONT_ENGINE_IN1, RIGHT_FRONT_ENGINE_IN2);
  engineMovementCounterclockwise(FRONT_LEFT_ENGINE_IN3, FRONT_LEFT_ENGINE_IN4);
  engineMovementClockwise(LEFT_REAR_ENGINE_IN3, LEFT_REAR_ENGINE_IN4);
  engineMovementCounterclockwise(RIGHT_REAR_ENGINE_IN1, RIGHT_REAR_ENGINE_IN2);
}

// Move the robot back
void moveTheRobotBack()
{
  engineMovementCounterclockwise(RIGHT_FRONT_ENGINE_IN1, RIGHT_FRONT_ENGINE_IN2);
  engineMovementClockwise(FRONT_LEFT_ENGINE_IN3, FRONT_LEFT_ENGINE_IN4);
  engineMovementCounterclockwise(LEFT_REAR_ENGINE_IN3, LEFT_REAR_ENGINE_IN4);
  engineMovementClockwise(RIGHT_REAR_ENGINE_IN1, RIGHT_REAR_ENGINE_IN2);
}

// Stop the robot
void stopTheRobot()
{
  braked(RIGHT_FRONT_ENGINE_IN1, RIGHT_FRONT_ENGINE_IN2);
  braked(FRONT_LEFT_ENGINE_IN3, FRONT_LEFT_ENGINE_IN4);
  braked(RIGHT_REAR_ENGINE_IN1, RIGHT_REAR_ENGINE_IN2);
  braked(LEFT_REAR_ENGINE_IN3, LEFT_REAR_ENGINE_IN4);
}

// Rotate the robot right
void rotateTheRobotRight()
{
  engineMovementCounterclockwise(FRONT_LEFT_ENGINE_IN3, FRONT_LEFT_ENGINE_IN4);
  engineMovementCounterclockwise(RIGHT_REAR_ENGINE_IN1, RIGHT_REAR_ENGINE_IN2);
  braked(RIGHT_FRONT_ENGINE_IN1, RIGHT_FRONT_ENGINE_IN2);
  braked(LEFT_REAR_ENGINE_IN3, LEFT_REAR_ENGINE_IN4);
}

// Rotate the robot left
void rotateTheRobotLeft()
{
  engineMovementClockwise(RIGHT_FRONT_ENGINE_IN1, RIGHT_FRONT_ENGINE_IN2);
  engineMovementClockwise(LEFT_REAR_ENGINE_IN3, LEFT_REAR_ENGINE_IN4);
  braked(FRONT_LEFT_ENGINE_IN3, FRONT_LEFT_ENGINE_IN4);
  braked(RIGHT_REAR_ENGINE_IN1, RIGHT_REAR_ENGINE_IN2);
}


void loop()
{

  auto timeDelay = 2000;

  if (Serial.available()) {
    while (Serial.available()) {
      delay(3);
      command += (char)Serial.read();
    }
  }
  Serial.println(command);

  if (command == FORWARD) {
    moveTheRobotForward();
    runtime(timeDelay);
  }
  if (command == BACK) {
    moveTheRobotBack();
    runtime(timeDelay);
  }
  if (command == LEFT) {
    rotateTheRobotLeft();
    runtime(timeDelay);
  }
  if (command == RIGHT) {
    rotateTheRobotRight();
    runtime(timeDelay);
  }
}
