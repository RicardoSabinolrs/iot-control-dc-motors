#define ENGINE_COUNT 8  
  
const int enginePins[ENGINE_COUNT] = {  
  52, 50, 48, 46, 31, 33, 35, 37  
};  
  
enum Direction {  
  FORWARD = 'f',  
  BACK = 'b',  
  LEFT = 'l',  
  RIGHT = 'r',  
  STOP = 's'  
};  
  
// Set all engine pins to output mode  
void setPinModeOut() {  
  for (int i = 0; i < ENGINE_COUNT; i++) {  
    pinMode(enginePins[i], OUTPUT);  
  }  
}  
  
// Activate pin with 5V logic level  
void active5V(int engine) {  
  digitalWrite(engine, HIGH);  
}  
  
// Activate pin with GND logic level  
void activeGND(int engine) {  
  digitalWrite(engine, LOW);  
}  
  
// Move engine clockwise  
void engineMovementClockwise(int pinIn1, int pinIn2) {  
  active5V(pinIn1);  
  activeGND(pinIn2);  
}  
  
// Move engine counterclockwise  
void engineMovementCounterclockwise(int pinIn1, int pinIn2) {  
  activeGND(pinIn1);  
  active5V(pinIn2);  
}  
  
// Brake the engine  
void braked(int pinIn1, int pinIn2) {  
  active5V(pinIn1);  
  active5V(pinIn2);  
}  
  
// Move the robot forward  
void moveTheRobotForward() {  
  engineMovementClockwise(enginePins[0], enginePins[1]);  
  engineMovementCounterclockwise(enginePins[2], enginePins[3]);  
  engineMovementClockwise(enginePins[4], enginePins[5]);  
  engineMovementCounterclockwise(enginePins[6], enginePins[7]);  
}  
  
// Move the robot backward  
void moveTheRobotBack() {  
  engineMovementCounterclockwise(enginePins[0], enginePins[1]);  
  engineMovementClockwise(enginePins[2], enginePins[3]);  
  engineMovementCounterclockwise(enginePins[4], enginePins[5]);  
  engineMovementClockwise(enginePins[6], enginePins[7]);  
}  
  
// Stop all engines  
void stopTheRobot() {  
  for (int i = 0; i < ENGINE_COUNT; i += 2) {  
    braked(enginePins[i], enginePins[i + 1]);  
  }  
}  
  
// Rotate the robot to the right  
void rotateTheRobotRight() {  
  engineMovementCounterclockwise(enginePins[2], enginePins[3]);  
  engineMovementCounterclockwise(enginePins[6], enginePins[7]);  
  braked(enginePins[0], enginePins[1]);  
  braked(enginePins[4], enginePins[5]);  
}  
  
// Rotate the robot to the left  
void rotateTheRobotLeft() {  
  engineMovementClockwise(enginePins[0], enginePins[1]);  
  engineMovementClockwise(enginePins[4], enginePins[5]);  
  braked(enginePins[2], enginePins[3]);  
  braked(enginePins[6], enginePins[7]);  
}  
  
// Delay and then stop the robot  
void runtime(int timeDelay) {  
  delay(timeDelay);  
  stopTheRobot();  
}  
  
void setup() {  
  Serial.begin(9600);  
  setPinModeOut();  
}  
  
void loop() {  
  int timeDelay = 2000;  
  if (Serial.available()) {  
    char commandRead = Serial.read();  
    switch (commandRead) {  
      case FORWARD:  
        moveTheRobotForward();  
        runtime(timeDelay);  
        break;  
      case BACK:  
        moveTheRobotBack();  
        runtime(timeDelay);  
        break;  
      case LEFT:  
        rotateTheRobotLeft();  
        runtime(timeDelay);  
        break;  
      case RIGHT:  
        rotateTheRobotRight();  
        runtime(timeDelay);  
        break;  
      case STOP:  
        stopTheRobot();  
        break;  
    }  
  }  
}  
