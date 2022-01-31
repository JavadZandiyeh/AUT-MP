#include "pitches.h"
#include "themes.h"
#include "themes1.h"
#include "themes2.h"
#include "themes3.h"
#include "themes4.h"
#include "Ode_to_Joy.h"
#include <Keypad.h>

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

float scale = 0;

void setup() {
  keypad.addEventListener(keypadEvent);
}

void loop() {
  char c = keypad.getKey();
}

void play_music(int mel[], int durs[], int len){
  for(int thisNote = 0; thisNote < len; thisNote++){
    scale = analogRead(A0)/512.0;
    int noteDuration = 500/(durs[thisNote]);
    tone(8, (int)(mel[thisNote]*scale), noteDuration);
    delay((int)(noteDuration*1.3));
  }
}

void keypadEvent(KeypadEvent key){
  if(keypad.getState() == PRESSED){
    if(key == '0')
      play_music(melody, noteDurations, sizeof(melody)/sizeof(int));
    else if(key == '1')
      play_music(melody1, noteDurations1, sizeof(melody1)/sizeof(int));
    else if(key == '2')
      play_music(melody2, noteDurations2, sizeof(melody2)/sizeof(int));
    else if(key == '3')
      play_music(melody3, noteDurations3, sizeof(melody3)/sizeof(int));
    else if(key == '4')
      play_music(melody4, noteDurations4, sizeof(melody4)/sizeof(int));
    else if(key == '5'){
      for(int thisNote = 0; thisNote < sizeof(melody5)/sizeof(int); thisNote++){
        scale = analogRead(A0)/512.0;
        int noteDuration = 500/(noteDurations5[thisNote]);
        tone(8, (int)(melody5[thisNote]*scale), noteDuration);
        delay((int)(noteDuration*1.3));
      }
    }      
  }
}
