#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Wire.h>

// --------------------------------------------------------------
// keypad object initializing
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
#define INT_PIN 2
// --------------------------------------------------------------
// define lcd pins
#define RS_PIN 51
#define EN_PIN 52
#define D4_PIN 8
#define D5_PIN 9
#define D6_PIN 10
#define D7_PIN 11
// lcd object initializing
LiquidCrystal lcd(RS_PIN, EN_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);
// states of lcd
int state = 0;
// --------------------------------------------------------------
// define led pins
#define led1 4
#define led2 5
#define led3 6
#define led4 7
// --------------------------------------------------------------
// eeprom settings
#define device_addr 0b1010000
byte type;
byte time1, time2, time3, time4;
byte default_time = 10; // 10 seconds
int delay_time = 1000; // 1 second
// --------------------------------------------------------------
// functions
void update_led();
void update_screen();
void update_screen_time(byte t);
void keypadEvent(KeypadEvent key);
void eeprom_write(byte memory_addr, byte data);
byte eeprom_read(byte memory_addr);
void retrieve_var();
void save_var();

// --------------------------------------------------------------
void setup() {
  // setup lcd
  lcd.begin(16, 2);
  state = 0;
  update_screen();

  // setup keypad event listener
  keypad.addEventListener(keypadEvent); 
  
  // setup led pins
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  // begin TWI with eeprom
  Wire.begin();

  // interrupt pin
  pinMode(INT_PIN, INPUT);
}

void loop() {
  // keypad pressed button
  char c = keypad.getKey();
  
  if(digitalRead(INT_PIN) == LOW){
    lcd.clear();
    lcd.print("saving...");
    save_var();
    state = 0;
    update_screen();
  }else if(state == 1){
    if(time1 <= 0)
      state = 2;
    else{
      time1 = time1 - 1;
      update_screen_time(time1);
    }
  }else if(state == 2){
    if(time2 <= 0)
      state = 3;
    else{
      time2 = time2 - 1;
      update_screen_time(time2);     
    }
  }else if(state == 3){
    if(time3 <= 0)
      state = 4;
    else{
      time3 = time3 - 1;
      update_screen_time(time3);
    }
  }else if(state == 4){
    if(time4 <= 0){
      lcd.clear();
      lcd.print("finished");
      state = 7;
      update_led();
      delay(2*delay_time);
      state = 0;
      update_screen();
    }else{
      time4 = time4 - 1;
      update_screen_time(time4);
    }
  }
}

// --------------------------------------------------------------
void update_led(){
  if(state == 1){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
  }else if(state == 2){
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
  }else if(state == 3){
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
  }else if(state == 4){
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
  }else if(state == 7){ //finish
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
  }else{
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
  }
}

void update_screen(){
  update_led();
  lcd.clear();
  
  // state=0: time_v_type & wash
  // state=9: time1 / state=10: time2 / state=11: time3 / state=12: time4 / state=13: wash_type

  if(state == 0){
    lcd.print("settings");
    lcd.setCursor(14, 0);
    lcd.print("x");
    lcd.setCursor(0, 1);
    lcd.print("start");
    lcd.setCursor(14, 1);
    lcd.print("+");
  }else if(state == 9){
    lcd.print("time of type1");
    lcd.setCursor(0, 1);
  }else if(state == 10){
    lcd.print("time of type2");
    lcd.setCursor(0, 1);
  }else if(state == 11){
    lcd.print("time of type3");
    lcd.setCursor(0, 1);
  }else if(state == 12){
    lcd.print("time of type4");
    lcd.setCursor(0, 1);
  }else if(state == 13){
    lcd.print("wash type");
    lcd.setCursor(0, 1);
  }
}

void update_screen_time(byte t){
  update_led();
  lcd.clear();
  lcd.print("type "+String(state));
  lcd.setCursor(0, 1);
  lcd.print("time: "+String(t));
  delay(delay_time);
}

void keypadEvent(KeypadEvent key){
  if(keypad.getState() == PRESSED){
    if(state == 0){
      if(key == '*')
        state = 9;
      else if(key == '+'){
        lcd.clear();
        lcd.print("retrieving...");
        retrieve_var();
        lcd.clear();
      }
      update_screen();
    }else if(state == 9){
      time1 = (byte)(key - '0');
      lcd.print(String(time1));
      delay(delay_time);
      state = 10;
      update_screen();
    }else if(state == 10){
      time2 = (byte)(key - '0');
      lcd.print(String(time2));
      delay(delay_time);
      state = 11;
      update_screen();
    }else if(state == 11){
      time3 = (byte)(key - '0');
      lcd.print(String(time3));
      delay(delay_time);
      state = 12;
      update_screen();
    }else if(state == 12){
      time4 = (byte)(key - '0');
      lcd.print(String(time4));
      delay(delay_time);
      state = 13;
      update_screen();
    }else if(state == 13){
      if(((key >= '1') && (key <= '4'))){
        state = (key - '0');
        lcd.print(String(state));
        delay(delay_time);
        lcd.clear();
        lcd.print("saving...");
        save_var();
        state = 0;
        update_screen();
      }
    }
  }
}

// --------------------------------------------------------------
void eeprom_write(byte memory_addr, byte data){
  Wire.beginTransmission(device_addr);
  Wire.write(memory_addr);
  Wire.write(data);
  Wire.endTransmission();
}

byte eeprom_read(byte memory_addr){
  byte data = NULL;
  Wire.beginTransmission(device_addr);
  Wire.write(memory_addr);
  Wire.endTransmission();

  Wire.requestFrom(device_addr, 1);
  delay(5);
  if(Wire.available())
    data = Wire.read();
  return data;
}

// --------------------------------------------------------------
void retrieve_var(){
  type = eeprom_read(0);
  delay(delay_time);
  time1 = eeprom_read(10);
  delay(delay_time);
  time2 = eeprom_read(20);
  delay(delay_time);
  time3 = eeprom_read(30);
  delay(delay_time);
  time4 = eeprom_read(40);

  // check if times or type if zero
  if(type == 0)
    type = 1;
   
  // set state
  state = (int)type;
}

void save_var(){
  type = (byte)state;
  eeprom_write(0, type);
  delay(delay_time);
  eeprom_write(10, time1);
  delay(delay_time);
  eeprom_write(20, time2);
  delay(delay_time);
  eeprom_write(30, time3);
  delay(delay_time);
  eeprom_write(40, time4);
}
