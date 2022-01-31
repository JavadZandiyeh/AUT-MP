#include <Servo.h>

#define SERVO_PIN 13

Servo servo;

int deg = 180;

void setup() {
  servo.attach(SERVO_PIN);
  Serial2.begin(9600);
}

void loop(){
  if(Serial2.available() > 0) {
    int num = Serial2.parseInt();
    Serial2.println(num);
    num = (-num + 360) % 360;
    deg = (deg + num) % 360;
  }
  int t = map(deg, 0, 360, 0, 180);
  servo.write(t);
}
