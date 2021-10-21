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
String op1 = "";
String op2 = "";
String operation = "";

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
    if((op1 == "") & (op2 == "") & (operation == ""))
      lcd.clear();
      
    if(key == 'C'){
      op1 = "";
      op2 = "";
      operation = "";
      lcd.clear();
    }else if((key >= '0') & (key <= '9')){
      // 0 < key < 9
      lcd.write(key);
      if(operation == "")
        op1 += key;
      else
        op2 += key;
    }else if((key != '=') & (operation == "") & (op1 != "")){
      // it means that key is one of +-/* operations in its correct place
      lcd.write(key);
      operation += key;
    }else if((key == '=') & (operation != "") & (op2 != "")){
      lcd.setCursor(0, 1);
      
      if(operation == "+")
        lcd.print(op1.toInt() + op2.toInt());
      else if(operation == "-")
        lcd.print(op1.toInt() - op2.toInt());
      else if(operation == "*")
        lcd.print(op1.toInt() * op2.toInt());
      else if(operation == "/")
        lcd.print(op1.toInt() / op2.toInt());
        
      op1 = "";
      op2 = "";
      operation = "";
    }
  }
}
