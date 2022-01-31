#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

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


//defingin pins
#define RS_PIN 50
#define EN_PIN 51
#define D4_PIN 8
#define D5_PIN 9
#define D6_PIN 10
#define D7_PIN 11

//lcd object initializing
LiquidCrystal lcd(RS_PIN, EN_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);

#define SERVO_PIN 13

Servo servo;


// Motor Speed Control Pins
#define MSC0_PIN 3
#define MSC1_PIN 4
#define MSC2_PIN 5
#define MSC3_PIN 6
#define MSC4_PIN 7

const byte SpeedInPin = 18, SpeedDePin = 19, AngleInPin = 20, AngleDePin = 21;

int speed = 0;
int angle = 0;
int state = 0;
String pad_input = "";

void setup() {
  pinMode(SpeedInPin, INPUT_PULLUP);
  pinMode(SpeedDePin, INPUT_PULLUP);
  pinMode(AngleInPin, INPUT_PULLUP);
  pinMode(AngleDePin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SpeedInPin), speedIn, FALLING);
  attachInterrupt(digitalPinToInterrupt(SpeedDePin), speedDe, FALLING);
  attachInterrupt(digitalPinToInterrupt(AngleInPin), angleIn, FALLING);
  attachInterrupt(digitalPinToInterrupt(AngleDePin), angleDe, FALLING);
  
  lcd.begin(16, 2);
  lcd.clear();
  
  servo.attach(SERVO_PIN, 1000, 2000);

  
  pinMode(MSC0_PIN, OUTPUT);
  pinMode(MSC1_PIN, OUTPUT);
  pinMode(MSC2_PIN, OUTPUT);
  pinMode(MSC3_PIN, OUTPUT);
  pinMode(MSC4_PIN, OUTPUT);
  
  keypad.addEventListener(keypadEvent);
  setMotorSpeed(speed);
  setAngle(angle);
  update_screen();
}



void speedIn() {
  speed = setMotorSpeed(speed+1);
  update_screen();
}
void speedDe() {
  speed = setMotorSpeed(speed-1);
  update_screen();
}
void angleIn() {
  angle = setAngle(angle+10);
  update_screen();
}
void angleDe() {
  angle = setAngle(angle-10);
  update_screen();
}


int setMotorSpeed(int s) {
  if(s > 31) s = 31;
  if(s < 0) s = 0;
  int res = s;
  digitalWrite(MSC0_PIN, (s&1) ? HIGH : LOW); s >>= 1;
  digitalWrite(MSC1_PIN, (s&1) ? HIGH : LOW); s >>= 1;
  digitalWrite(MSC2_PIN, (s&1) ? HIGH : LOW); s >>= 1;
  digitalWrite(MSC3_PIN, (s&1) ? HIGH : LOW); s >>= 1;
  digitalWrite(MSC4_PIN, (s&1) ? HIGH : LOW); s >>= 1;
  return res;
}

int setAngle(int a) {
  float b = round(a / 10.0f);
  if(b < -1) b = -1;
  if(b > 4) b = 4;
  a = round(b * 10);
  int d = map(a, -10, 40, 0, 180);
  servo.write(d);
  return a;
}

void update_screen() {
  if(state == 0) {
    lcd.clear();
    lcd.print("Speed: "+String(speed));
    lcd.setCursor(11, 0);
    lcd.print("set x");
    lcd.setCursor(0, 1);
    lcd.print("Angle: "+String(angle));
    lcd.setCursor(11, 1);
    lcd.print("set +");
  } else if(state == 1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Speed:");
    lcd.setCursor(0, 1);
    lcd.print(pad_input);
    lcd.setCursor(7, 1);
    lcd.print("(0 to 31)");
  } else if(state == 2) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Angle:");
    lcd.setCursor(0, 1);
    lcd.print(pad_input);
    lcd.setCursor(5, 1);
    lcd.print("(-10 to 40)");
  }
}

void loop() {
  char c = keypad.getKey();
}


void keypadEvent(KeypadEvent key) {
  if(keypad.getState() == PRESSED){
    if(state) {
      if(key == 'C'){
        pad_input = "";
      } else if(((key >= '0') && (key <= '9')) || (key == '-' && pad_input.length() == 0)){
        // 0 < key < 9
        if(pad_input.length() < 3)
          pad_input += key;
      } else if(key == '='){
        int v = pad_input.toInt();
        if(state == 1)
          speed = setMotorSpeed(v);
        else if(state == 2)
          angle = setAngle(v);
        state = 0;
      }
    }
    if(key == '*') {
      state = 1;
      pad_input = "";
    }
    if(key == '+') {
      state = 2;
      pad_input = "";
    }
    if(key == '/') {
      state = 0;
    }
    update_screen();
  }
}
