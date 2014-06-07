#include <NewPing.h>
#include <Servo.h>

#define TRIGGER_PIN  14
#define ECHO_PIN     15
#define MAX_DISTANCE 100

int pwm_a = 3;  //PWM control for motor outputs 1 and 2 is on digital pin 3
int pwm_b = 11;  //PWM control for motor outputs 3 and 4 is on digital pin 11
int dir_a = 12;  //dir control for motor outputs 1 and 2 is on digital pin 12
int dir_b = 13;  //dir control for motor outputs 3 and 4 is on digital pin 13

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); //Set up the sonar
Servo neck;

int i;
int distance;

int Distance_f;
int Distance_l;
int Distance_r;
int obsDistance = 30;

int pos_start = 90;
int pos_left = 25;
int pos_forw = 100;
int pos_right = 180;

void setup() {
  Serial.begin(115200);

  pinMode(pwm_a, OUTPUT);  //Set control pins to be outputs
  pinMode(pwm_b, OUTPUT);
  pinMode(dir_a, OUTPUT);
  pinMode(dir_b, OUTPUT);

  analogWrite(pwm_a, 150); 
  analogWrite(pwm_b, 150);

  neck.attach(2);
  neck.write(pos_start);
}

void loop() {
  delay(75);
  START:scanFront();
  if (Distance_f < obsDistance) {
    moveBackward();
    delay(250);
    moveStop();
    delay(750);
    scanLeft();
    delay(50);
    scanRight();
    if (Distance_l > Distance_r) {
      turnLeft();
      delay(450);
      goto START;
    } 
    else if (Distance_r > Distance_l) {
      turnRight();
      delay(450);
      goto START;
    } 
    else {
      moveBackward();
      delay(750);
      turnLeft();
      delay(500);
      goto START;
    }
  } 
  else {
    moveForward();
    goto START;
  }
}

//Scan commands - scan base, look left and right

int scan() {
  delay(50);
  distance = sonar.ping_cm();
  Serial.write(distance);
  if(distance == 0){
    distance = 100;
  }
  return distance;
}

int scanFront() {
  neck.write(pos_forw);
  delay(15);
  Distance_f = 0;
  scan();
  Distance_f = distance;
  return Distance_f;
}

int scanLeft() {
  Distance_l = 0;
  for(i = pos_forw; i > pos_left; i--) {
    neck.write(pos_left);
    delay(15);
  }
  scan();
  Distance_l = distance - 14;
  return Distance_l;
}

int scanRight() {
  Distance_r = 0;
  for(i = pos_forw; i < pos_right; i++) {
    neck.write(pos_right);
    delay(15);
  }
  scan();
  Distance_r = distance;
  return Distance_r;
}

//Movement commands

void moveForward() {
  analogWrite(pwm_a, 150);
  analogWrite(pwm_b, 150);
  digitalWrite(dir_a, HIGH);
  digitalWrite(dir_b, HIGH);
}

void moveBackward() {
  analogWrite(pwm_a, 100);
  analogWrite(pwm_b, 100);
  digitalWrite(dir_a, LOW);
  digitalWrite(dir_b, LOW);
}

void turnLeft() {
  analogWrite(pwm_a, 100);
  analogWrite(pwm_b, 100);
  digitalWrite(dir_a, HIGH);
  digitalWrite(dir_b, LOW);
}

void turnRight() {
  analogWrite(pwm_a, 100);
  analogWrite(pwm_b, 100);
  digitalWrite(dir_a, LOW);
  digitalWrite(dir_b, HIGH);
}

void moveStop() {
  digitalWrite(dir_a, LOW);
  digitalWrite(dir_b, LOW);
  analogWrite(pwm_a, 100);
  analogWrite(pwm_b, 100);
  delay(250);
  analogWrite(pwm_a, 80);
  analogWrite(pwm_b, 80);
  delay(250);
  analogWrite(pwm_a, 40);
  analogWrite(pwm_b, 40);
  delay(250);
  analogWrite(pwm_a, 0);
  analogWrite(pwm_b, 0);
}

