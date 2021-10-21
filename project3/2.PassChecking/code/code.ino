#include <LiquidCrystal.h>
#include <Keypad.h>

//defingin pins
#define RS_PIN 50
#define EN_PIN 51
#define D4_PIN 8
#define D5_PIN 9
#define D6_PIN 10
#define D7_PIN 11

//global variables
String my_pass = "9831032";
String cur_input = "";


//lcd object initializing
LiquidCrystal lcd(RS_PIN, EN_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);

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


void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.clear();
  
  keypad.addEventListener(keypadEvent);
}

void loop() {
  // put your main code here, to run repeatedly:
  char key = keypad.getKey();
}


void keypadEvent(KeypadEvent key) {
  if(keypad.getState() == PRESSED){
    if((key >= '0') & (key <= '9')){
      lcd.write(key);
      cur_input += key;
    }
    else if(key == '*'){
      lcd.setCursor(0, 1);
      if(cur_input == "9831032")
        lcd.print("correct password");
      else
        lcd.print(" wrong password ");
      delay(1000);
      cur_input = "";
      lcd.clear();
    }
  }
}
