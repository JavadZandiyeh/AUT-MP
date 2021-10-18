#include <Keypad.h>

const int LED_NUM = 9;
const int leds[LED_NUM] = {A8, A4, A5, A6, A7, A3, A2, A1, A0};

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

int LED_ON_Num = 0;

void setup(){
  keypad.addEventListener(keypadEvent);
  Serial2.begin(9600);
}

void loop(){
  char key = keypad.getKey();
  
}

void keypadEvent(KeypadEvent key) {
  if(keypad.getState() == PRESSED)
    Serial2.println(key);
}
