const int LED_NUM = 9;
const int leds[LED_NUM] = {A8, A4, A5, A6, A7, A3, A2, A1, A0};

int LED_ON_Num = 0;

void setup(){
  for(int i=0;i<LED_NUM;i++)
    pinMode(leds[i], OUTPUT);
  Serial2.begin(9600);
}

void loop(){
  for(int i=0;i<LED_NUM;i++)
    digitalWrite(leds[i], (i < LED_ON_Num ? HIGH : LOW));
  if(Serial2.available() > 0) {
    int num = Serial2.parseInt();
    Serial2.println(num);
    if(num < 0 || num > 9)
      Serial2.println("Invalid number");
    else
      LED_ON_Num = num;
  }
}
