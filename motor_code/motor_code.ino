//curent (A) at 1.5A
#define DIR_PIN 11
#define PUL_PIN 10
int button1 = LOW;
int button2 = LOW;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(PUL_PIN, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  //low = clockwise when pointed up
  //high = counterclockwise when pointed up
  digitalWrite(DIR_PIN, HIGH);
   Serial.print("start");
}

void loop() {
  // current rn set at 800 pulse/rev
  int sensorVal1 = digitalRead(2);
  int sensorVal2 = digitalRead(3);
  int sensorValue = analogRead(A0);
  //Serial.println(sensorValue);
  if(sensorVal1 == LOW && button1){
    digitalWrite(DIR_PIN, HIGH);
    //Serial.print("press1");
    button1 = LOW;
  }else{
    button1 = HIGH;
  }
   if(sensorVal2 == LOW && button2){
    digitalWrite(DIR_PIN, LOW);
    //Serial.print("press2");
    button2 = LOW;
  }else{
    button2 = HIGH;
  }
  
  digitalWrite(PUL_PIN, HIGH);
  delayMicroseconds(sensorValue);
  digitalWrite(PUL_PIN, LOW);
  delayMicroseconds(sensorValue);
}
