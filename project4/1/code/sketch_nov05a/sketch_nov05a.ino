#include <Servo.h>

#define SERVO_PIN 13

Servo servo;

void setup() {
  // put your setup code here, to run once:
  servo.attach(SERVO_PIN);
}

int val(int x) {
  //return map(x, 0, 90, 93, 144);
  return map(x, -90, 90, 0, 180);
}

void loop() {
  
  //servo.write(val(45));
  
  for(int i=0;i<=90;i++) {
    servo.write(val(i));
    delay(20);
  }
  for(int i=89;i>0;i--) {
    servo.write(val(i));
    delay(20);
  }
}
