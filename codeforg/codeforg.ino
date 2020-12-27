#define DIR_PIN 11
#define PUL_PIN 10
#define FWBW_INT_PIN 2 
#define LIMIT_PIN 3 
#define forward 4 
#define backward 5
#define FRONT_LIMIT 6 
#define BACK_LIMIT 7 

bool dir = HIGH;
bool motorRun = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(DIR_PIN, OUTPUT);
  pinMode(PUL_PIN, OUTPUT);
  pinMode(BACK_LIMIT, INPUT); //OUTPUT ONLY DURING TESTING  
  pinMode(FRONT_LIMIT, INPUT); 
  pinMode(forward, INPUT); 
  pinMode(backward, INPUT);

  attachInterrupt(digitalPinToInterrupt(LIMIT_PIN), limit, RISING); //add a flag to prevent wierd errors
  attachInterrupt(digitalPinToInterrupt(FWBW_INT_PIN), dir2, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(motorRun){
  digitalWrite(PUL_PIN, HIGH);
  delayMicroseconds(200); 
  digitalWrite(PUL_PIN, LOW);
  delayMicroseconds(200);
  }
}

void limit(){
  motorRun = false;
}

void dir2(){
  motorRun = true;
  if(digitalRead(forward) == HIGH){
    dir= HIGH;
  }else if(digitalRead(backward) == HIGH){
    dir = LOW;
  }else{
    motorRun = false;
  }
  digitalWrite(DIR_PIN,dir);
}
