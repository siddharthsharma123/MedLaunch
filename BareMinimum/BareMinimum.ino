const byte forward = 4; 
const byte backward = 5; 


  bool dir = true;  
  float vel = 1000;    
  float accel = 20;

//curent (A) at 1.5A
#define DIR_PIN 11
#define PUL_PIN 10


void setup() {  

  Serial.begin(9600); 
  pinMode(DIR_PIN, OUTPUT);
  pinMode(PUL_PIN, OUTPUT);
  

  //initialize some variables

  //int len =  100; 
  //float wheel = 12.6;   

  
  
  // put your setup code here, to run once: 
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0 

   // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A); 

  //SETTING LIMIT SWITCHES  
  pinMode(2, INPUT_PULLUP); 
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), limit, FALLING); //add a flag to prevent wierd errors
  attachInterrupt(digitalPinToInterrupt(3), dir2, FALLING);
  //PULSE IN PIN 10, dir in pin 11 

}

void loop() {
  // put your main code here, to run repeatedly:
  float delayTime = vel; 
  digitalWrite(PUL_PIN, HIGH);
  delayMicroseconds(delayTime);
  digitalWrite(PUL_PIN, LOW);
  delayMicroseconds(delayTime);

} 

void dir2(){  
  if(forward == HIGH){
    dir = true;
    }
  else{
    dir = false;
    }
 } 

ISR(TIMER1_COMPA_vect){  //eveytime the acceleration interupt is fired, this ISR is pursued
   //interrupt commands here 
   if(vel >1){
   vel -= accel;
   }
} 

void limit(){
  while(forward == LOW && backward == LOW){}
  }
