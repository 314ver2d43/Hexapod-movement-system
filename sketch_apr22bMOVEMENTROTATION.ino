#include <Servo.h>
const int STEP_DELAY = 5; 
const int LIFT_ANGLE = 40; 
const int STRIDE_ANGLE = 35; 
const int TURN_ANGLE = 20; 
int servoPins[12] = {2, 3, 4, 5, 7, 6, 8, 9, 10, 11, 12, 13};
Servo myServos[12];
int baseAngles[12] = {100, 40, 90, 45, 90, 65, 90, 65, 90, 35, 100, 50};
int groupA[] = {4, 0, 8}; 
int groupB[] = {6, 10, 2}; 
void setup() {
  for (int i = 0; i < 12; i++) {
    myServos[i].attach(servoPins[i]);
    myServos[i].write(baseAngles[i]);
    delay(50);
  }
  delay(2000);
}
void loop() {
  MoveForward(20);
  delay(1000);
  TurnRight(35);
  delay(1000);
}
void ResetToBase() {
  int targets[12];
  for (int i = 0; i < 12; i++) {
    targets[i] = baseAngles[i];
  }
  moveMultipleSmooth(targets);
}
void MoveForward(int count) {
  for (int i = 0; i < count; i++) {
    tripodStep(groupA, groupB);
    tripodStep(groupB, groupA);
  }
  ResetToBase(); 
}
void TurnRight(int count) {
  for (int i = 0; i < count; i++) {
    tripodTurnRight(groupA, groupB);
    tripodTurnRight(groupB, groupA);
  }
  ResetToBase(); 
}
void TurnLeft(int count) {
  for (int i = 0; i < count; i++) {
    tripodTurnLeft(groupA, groupB);
    tripodTurnLeft(groupB, groupA);
  }
  ResetToBase(); 
}
void moveMultipleSmooth(int targets[]) {
  bool moving = true;
  while (moving) {
    moving = false;
    for (int i = 0; i < 12; i++) {
      int curr = myServos[i].read();
      if (curr != targets[i]) {
        myServos[i].write(curr < targets[i] ? curr + 1 : curr - 1);
        moving = true;
      }
    }
    delay(STEP_DELAY);
  }
}
void tripodStep(int hips[], int otherHips[]) {
  int targets[12];
  for(int i=0; i<12; i++) targets[i] = myServos[i].read();

  for (int i = 0; i < 3; i++) {
    targets[hips[i] + 1] = baseAngles[hips[i] + 1] + LIFT_ANGLE;
  }
  moveMultipleSmooth(targets);

  for (int i = 0; i < 3; i++) {
    int hipIdx = hips[i];
    int direction = (servoPins[hipIdx] <= 7) ? 1 : -1; 
    targets[hipIdx] = baseAngles[hipIdx] + (STRIDE_ANGLE * direction);
    targets[otherHips[i]] = baseAngles[otherHips[i]]; 
  }
  moveMultipleSmooth(targets);

  for (int i = 0; i < 3; i++) {
    targets[hips[i] + 1] = baseAngles[hips[i] + 1];
  }
  moveMultipleSmooth(targets);
}

void tripodTurnRight(int hips[], int otherHips[]) {
  int targets[12];
  for(int i=0; i<12; i++) targets[i] = myServos[i].read();
  
  for (int i = 0; i < 3; i++) {
    targets[hips[i] + 1] = baseAngles[hips[i] + 1] + LIFT_ANGLE;
  }
  moveMultipleSmooth(targets);

  for (int i = 0; i < 3; i++) {
    targets[hips[i]] = baseAngles[hips[i]] + TURN_ANGLE;
    targets[otherHips[i]] = baseAngles[otherHips[i]]; 
  }
  moveMultipleSmooth(targets);

  for (int i = 0; i < 3; i++) {
    targets[hips[i] + 1] = baseAngles[hips[i] + 1];
  }
  moveMultipleSmooth(targets);
}

void tripodTurnLeft(int hips[], int otherHips[]) {
  int targets[12];
  for(int i=0; i<12; i++) targets[i] = myServos[i].read();
  
  for (int i = 0; i < 3; i++) {
    targets[hips[i] + 1] = baseAngles[hips[i] + 1] + LIFT_ANGLE;
  }
  moveMultipleSmooth(targets);

  for (int i = 0; i < 3; i++) {
    targets[hips[i]] = baseAngles[hips[i]] - TURN_ANGLE;
    targets[otherHips[i]] = baseAngles[otherHips[i]]; 
  }
  moveMultipleSmooth(targets);

  for (int i = 0; i < 3; i++) {
    targets[hips[i] + 1] = baseAngles[hips[i] + 1];
  }
  moveMultipleSmooth(targets);
}