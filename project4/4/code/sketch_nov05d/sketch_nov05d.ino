#include <Servo.h>

#define SERVO_PIN 13
#define POT_PIN A0

Servo servo;

int tmp;

void setup() {
  servo.attach(SERVO_PIN);
  pinMode(POT_PIN, INPUT);
}

void loop(){
  tmp = analogRead(POT_PIN);
  servo.write(map(tmp, 0, 1023, 0, 180));
}
