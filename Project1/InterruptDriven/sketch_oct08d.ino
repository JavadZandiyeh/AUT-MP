//set pin numbers
const int led1 = 6;
const int led2 = 5;
const int led3 = 4;
const int led4 = 3;
const int led5 = 2;
const int led6 = 1;
const int led7 = 0;

const int switch1 = 18;
const int switch2 = 19;
const int switch3 = 20;

int switch1_state = 0;
int switch2_state = 0;
int switch3_state = 0;

unsigned long prevMillis = 0;
const long interval = 500;

void setup() {
  // put your setup code here, to run once:
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  
  pinMode(switch1, INPUT);
  pinMode(switch2, INPUT);
  pinMode(switch3, INPUT);

  attachInterrupt(digitalPinToInterrupt(switch1), switch1_pressed, LOW);
  attachInterrupt(digitalPinToInterrupt(switch2), switch2_pressed, LOW);
  attachInterrupt(digitalPinToInterrupt(switch3), switch3_pressed, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
    if(switch1_state == 1){
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    digitalWrite(led7, LOW);
    delay(500);
      
    digitalWrite(led1, HIGH);
    delay(500);
    digitalWrite(led2, HIGH);
    delay(500);
    digitalWrite(led3, HIGH);
    delay(500);
    digitalWrite(led4, HIGH);
    delay(500);
    digitalWrite(led5, HIGH);
    delay(500);
    digitalWrite(led6, HIGH);
    delay(500);
    digitalWrite(led7, HIGH);
    switch1_pressed();
    delay(500);
  }
  
  if(switch2_state == 1){
    for(int i = 0; i < strlen("MohammadJavad"); i++){
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      digitalWrite(led7, LOW);
      delay(500);
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
      digitalWrite(led6, HIGH);
      digitalWrite(led7, HIGH);
      switch2_pressed();
      delay(500);
    }
  }
  
  if(switch3_state == 1){
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    digitalWrite(led7, LOW);
    switch3_pressed();
  }
}

void switch1_pressed(){
  switch1_state = !switch1_state;
}

void switch2_pressed(){
  switch2_state = !switch2_state;
}

void switch3_pressed(){
  switch3_state = !switch3_state;
}
