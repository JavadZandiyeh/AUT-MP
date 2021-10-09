//set pin numbers
const int led1 = 6;
const int led2 = 5;
const int led3 = 4;
const int led4 = 3;
const int led5 = 2;
const int led6 = 1;
const int led7 = 0;

const int switch1 = 12;
const int switch2 = 11;
const int switch3 = 10;

//set state of switches
int switch1_state = 0;
int switch2_state = 0;
int switch3_state = 0;

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
}

void loop() {
  // put your main code here, to run repeatedly:
  switch1_state = digitalRead(switch1);
  switch2_state = digitalRead(switch2);
  switch3_state = digitalRead(switch3);

  if(switch1_state == LOW){
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
    delay(500);
  }
  
  if(switch2_state == LOW){
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
      delay(500);
    }
  }

  if(switch3_state == LOW){
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    digitalWrite(led7, LOW);
  }
  
}
