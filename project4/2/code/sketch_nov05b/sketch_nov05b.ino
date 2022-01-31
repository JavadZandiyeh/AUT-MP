#include <Servo.h>
#include <Keypad.h>

#define SERVO_PIN 13


//keypad object initializing
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'7','8','9','/'},
  {'4','5','6','*'},
  {'1','2','3','-'},
  {'C','0','=','+'}
};
byte rowPins[ROWS] = {22, 23, 24, 25};
byte colPins[COLS] = {26, 27, 28, 29};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

Servo servo;

String number_string = "";

void setup() {
  servo.attach(SERVO_PIN);
  keypad.addEventListener(keypadEvent);
}

void loop() {
  // put your main code here, to run repeatedly:
  char key = keypad.getKey();
}

void keypadEvent(KeypadEvent key) {
  if(keypad.getState() == PRESSED){
    if(key == 'C'){
      number_string = "";
    } else if((key >= '0') && (key <= '9')){
      // 0 < key < 9
      number_string += key;
      if(number_string.length() > 3)
        number_string = "";
    } else if(key == '='){
      int v = number_string.toInt();
      number_string = "";
      if(v > 360)
        return;
      int d = map(v, 0, 360, 0, 180);
      servo.write(d);
    }
  }
}
