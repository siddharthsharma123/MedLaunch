#define BUT_ONE 11
#define BUT_TWO 10
#define BUT_OR 3

void setup() {
  // put your setup code here, to run once: 
  Serial.begin(9600); 
  pinMode(BUT_ONE, INPUT); 
  pinMode(BUT_TWO, INPUT); 
  pinMode(BUT_OR, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUT_OR), OR, RISING); //add a flag to prevent wierd errors
}

void loop() {
  // put your main code here, to run repeatedly: 

} 

void OR(){
  if(BUT_ONE == HIGH){
     Serial.print(" BUTor: ");
    } 
   if(BUT_TWO == HIGH){
     Serial.println("butor");
    }
  
  }
