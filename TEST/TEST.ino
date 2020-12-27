#define DIR_PIN 11
#define PUL_PIN 10
#define FWBW_INT_PIN 2 
#define LIMIT_PIN 3 
#define forward 4
#define backward 5
#define FRONT_LIMIT 6 
#define BACK_LIMIT 7 
#define testPinButton 4
void setup() {
  // put your setup code here, to run once: 
  Serial.begin(9600); 
  pinMode(forward, INPUT); 
  pinMode(backward, INPUT); 
  pinMode(FRONT_LIMIT, INPUT);
  pinMode(BACK_LIMIT, INPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(PUL_PIN, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(LIMIT_PIN), limitTest, RISING); //add a flag to prevent wierd errors
  attachInterrupt(digitalPinToInterrupt(FWBW_INT_PIN), dirTest, RISING);
}

void loop() {
  // put your main code here, to run repeatedly: 

} 
void limitTest(){
  Serial.print("Limit interrupt Fired : ");
  if(digitalRead(FRONT_LIMIT) == HIGH){
     Serial.println("Front Limit Pressed");
    } 
   else if(digitalRead(BACK_LIMIT) == HIGH){
     Serial.println("Back Limit Pressed");
    }
    else{
      Serial.println("No limit Pressed");
    }
  
  }

  void dirTest(){
  Serial.print("Limit interrupt Fired : ");
  if(digitalRead(forward) == HIGH){
     Serial.println("Front button Pressed");
    } 
   else if(digitalRead(backward) == HIGH){
     Serial.println("Back button Pressed");
    }
    else{
      Serial.println("No button Pressed");
    }

  }
