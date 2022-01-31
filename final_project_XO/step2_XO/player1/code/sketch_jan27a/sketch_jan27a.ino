// player 1

#include <LiquidCrystal.h>
#include <Keypad.h>

// lcd object initializing
#define RS_PIN 50
#define EN_PIN 51
#define D4_PIN 8
#define D5_PIN 9
#define D6_PIN 10
#define D7_PIN 11
LiquidCrystal lcd(RS_PIN, EN_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);

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

// point
char player1_point = 'X';
char player2_point = 'O';

// grid fill places
int fill[10];

// 1: player1 turn
// 2: player2 turn
int turn = 1;

void setup() {
  Serial2.begin(9600);
  keypad.addEventListener(keypadEvent);
  lcd.begin(16, 4);
  lcd.clear();

  for(int i=0; i<10; i++)
    fill[i] = 0;
}

void loop() {
  // keypad pressed button
  char c = keypad.getKey();
  
  if(Serial2.available()){
    char data = Serial2.read();
    int num = data - '0';
    update_screen(num, 2); // show what player 2 done
  }
}

void keypadEvent(KeypadEvent key){
  if(keypad.getState() == PRESSED){
    if((key >= '1') & (key <= '9')){
      int num = key - '0';
      if((fill[num] == 0) & (turn == 1)){
        Serial2.print(key);
        update_screen(num, 1); // show what player 1 done
      }
    }
  }
}

void update_screen(int num, int player){
  switch(num){
    case 1:
    lcd.setCursor(0, 2);
    break;
    case 2:
    lcd.setCursor(2, 2);
    break;
    case 3:
    lcd.setCursor(4, 2);
    break;
    case 4:
    lcd.setCursor(0, 1);
    break;
    case 5:
    lcd.setCursor(2, 1);
    break;
    case 6:
    lcd.setCursor(4, 1);
    break;
    case 7:
    lcd.setCursor(0, 0);
    break;
    case 8:
    lcd.setCursor(2, 0);
    break;
    case 9:
    lcd.setCursor(4, 0);
    break;
  }
  
  if(player == 1){
    fill[num] = 1;
    turn = 2;
    lcd.print(player1_point);
  }
  else if(player == 2){
    fill[num] = 2;
    turn = 1;
    lcd.print(player2_point);
  }

  check_win();
}

void check_win(){
  int winner = 0;
  
  if( (fill[1]*fill[2]*fill[3] == 1) ||
      (fill[4]*fill[5]*fill[6] == 1) ||
      (fill[7]*fill[8]*fill[9] == 1) ||
      (fill[1]*fill[4]*fill[7] == 1) ||
      (fill[2]*fill[5]*fill[8] == 1) ||
      (fill[3]*fill[6]*fill[9] == 1) ||
      (fill[1]*fill[5]*fill[9] == 1) ||
      (fill[3]*fill[5]*fill[7] == 1)){
        winner = 1;
      }
  else if( (fill[1]*fill[2]*fill[3] == 8) ||
           (fill[4]*fill[5]*fill[6] == 8) ||
           (fill[7]*fill[8]*fill[9] == 8) ||
           (fill[1]*fill[4]*fill[7] == 8) ||
           (fill[2]*fill[5]*fill[8] == 8) ||
           (fill[3]*fill[6]*fill[9] == 8) ||
           (fill[1]*fill[5]*fill[9] == 8) ||
           (fill[3]*fill[5]*fill[7] == 8)){
             winner = 2;
           }
  if(winner != 0){
    delay(10);
    lcd.clear();
    
    if(winner == 1)
      lcd.print("you win");
    else
      lcd.print("you lose");

    delay(2000);
    reset_game(winner);
  }else{
    int mul = 1;
    for(int i=1; i<10; i++)
      mul *= fill[i];
    if(mul != 0){
      lcd.clear();
      lcd.print("no winner");
      delay(2000);
      reset_game(1);
    }
  }
}

void reset_game(int winner){
  lcd.clear();
  for(int i=0; i<10; i++)
    fill[i] = 0;
  turn = winner;
}
