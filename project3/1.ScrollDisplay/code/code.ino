#include <LiquidCrystal.h>

#define RS_PIN 50
#define EN_PIN 51
#define D4_PIN 8
#define D5_PIN 9
#define D6_PIN 10
#define D7_PIN 11

LiquidCrystal lcd(RS_PIN, EN_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);
char *my_name = "JAVAD";
int my_name_len = strlen(my_name);
int row = 0;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.setCursor(0, row);
  lcd.print(my_name);
  delay(1000);
  for(int i = 0; i < (16 - my_name_len); i++){
    lcd.scrollDisplayRight();
    delay(1000);
  }
  row = (row + 1) % 2;
}
