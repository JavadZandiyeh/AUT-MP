#include <LiquidCrystal.h>
#include <Keypad.h>

//defingin pins
#define RS_PIN 50
#define EN_PIN 51
#define D4_PIN 8
#define D5_PIN 9
#define D6_PIN 10
#define D7_PIN 11

char my_char = 'Z';
int row = 0;
int col = 0;

LiquidCrystal lcd(RS_PIN, EN_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.setCursor(col, row);
  lcd.write(my_char);
  delay(1000);

  row = (row+1)%2;
  col = (col+1)%16;
}
