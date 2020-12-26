


bool dir = true;  
float vel;
   
float accel = 20;
bool should_stop = true;  
bool mid_stop = false;
 
bool quick_stop = true;

float ts = 300; 
float ss = 200; 
float fs = 200;

unsigned long int pulse =0;


//curent (A) at 1.5A
#define DIR_PIN 11
#define PUL_PIN 10
#define FWBW_INT_PIN 2 
#define LIMIT_PIN 3 
#define forward 4 
#define backward 5
#define rail_start 6 
#define rail_end 7 

void setup() {   
  vel = fs;

  Serial.begin(9600); 
  pinMode(DIR_PIN, OUTPUT);
  pinMode(PUL_PIN, OUTPUT);
  pinMode(rail_end, INPUT); //OUTPUT ONLY DURING TESTING  
  pinMode(rail_start, INPUT); 
  pinMode(forward, INPUT); 
  pinMode(backward, INPUT);
  digitalWrite(DIR_PIN,HIGH);

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

  //SETTING LIMIT SWITCHES AND FW/BW INTERRUPT PIN  
  pinMode(FWBW_INT_PIN, INPUT_PULLUP); 
  pinMode(LIMIT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(LIMIT_PIN), limit, FALLING); //add a flag to prevent wierd errors
  attachInterrupt(digitalPinToInterrupt(FWBW_INT_PIN), dir2, FALLING);
  //PULSE IN PIN 10, dir in pin 11 

}

void loop() {
  //speed control
  if(vel == ts && accel > 0){ 
  noInterrupts(); //we don't want any acceleration anymore 
  
} 
else if (vel == ss && accel < 0){  
  noInterrupts();   

  if(quick_stop == true){ //we reach stopping speed early in the track 
    
    delay(250); //stop the motor for a bit
    //switching directions 
    if(dir == true){ 
      digitalWrite(DIR_PIN,LOW); 
      dir = false;
    } 
    else if(dir == false){
      digitalWrite(DIR_PIN,HIGH); 
      dir = true;
      } 
    
    } 
  else if(mid_stop == true){  //if we reach ss in the middle of the track
    
    delay(250); 

    if(dir == true){ 
      digitalWrite(DIR_PIN,LOW); 
      dir = false;
    } 
    else if(dir == false){
      digitalWrite(DIR_PIN,HIGH); 
      dir = true;
      } 

    accel = abs(accel);   //let's reach target speed again
    interrupts(); //allow for acceleration to occur
    }
    
} 
  // actual speed code  
 
  if(pulse == 0){ //begin decline to ss. This code is only intended for testing, and MUST change later

    accel = -1*abs(accel); 
    interrupts();
   } 
  
  float delayTime = 1/vel; 
  digitalWrite(PUL_PIN, HIGH);
  delayMicroseconds(delayTime*10000); 
  ++pulse;
  digitalWrite(PUL_PIN, LOW);
  delayMicroseconds(delayTime*10000); 
  ++pulse; 
 
} 

void dir2(){  

  noInterrupts(); //we need to shut off the acceleration timer here. 
  
  if(digitalRead(forward) == HIGH){  //when forward button is pressed
    
    if(digitalRead(rail_end) == HIGH){ //we are at 100 % and are need to start moving in the other direction 
     vel = fs; //vel is equal to max speed without any acceleration 
     accel = abs(accel); //make sure the acceleration is positive, so that we can increase speed
     digitalWrite(DIR_PIN,HIGH); //switch direction to forward 
     dir = true; 
     interrupts();
     return;
    } 
    else if(vel < ts && accel < 0 && dir == false){ //we are in 80-100% endzone, we were moving towards 100%. Now we are moving from somewhere in 80-100% to 0%
            
      should_stop = false; //we need to continue decelerating to 100%, then start moving towards the 0% 
      interrupts();
      return; 
      
      }  
    else if(vel < ts && accel > 0 && dir == false){ //the motor is in 0-20% region, we were approaching target speed (towards 100%). Now the direction must be changed so the motor moves towards 0%

      accel = -abs(accel); //this will bring the motor speed down to stopping speed; 
      quick_stop = true; 
      interrupts();
      return; 
      
      }  
    else if(vel == ts && dir == false){ // we are at target speed
        accel = -abs(accel);
        mid_stop = true; 
        interrupts(); 
        return;
        }
      
    } 
  else if (digitalRead(backward) == HIGH){ 
    
     if(digitalRead(rail_start) == HIGH){ //we are at 0%
      vel = fs; 
      accel = abs(accel); 
      digitalWrite(DIR_PIN,LOW); 
      dir = false; 
      interrupts();
      return;

    }
    else if(vel < ts && accel < 0 && dir == true){ //we are in 0-20% endzone, we were moving towards 0%. Now we want to move from somewhere in 0-20% to 100%
      
      should_stop = false; //we need to continue decelerating to 0%, then start moving towards the 100% 
      return;
      
      }
      
    } 
    else if(vel < ts && accel > 0 && dir == true){ //the motor is in 80-100% region, we were approaching target speed (towards 0%). Now the direction must be changed so the motor moves towards 100%

      accel = -abs(accel); //this will bring the motor speed down to stopping speed; 
      quick_stop = true; 
      interrupts();
      return; 
      
    }  
    else if(vel == ts && dir == false){ //target speed
        accel = -abs(accel);
        mid_stop = true; 
        interrupts(); 
        return;
    }   

    
 }

ISR(TIMER1_COMPA_vect){  //eveytime the acceleration interupt is fired, this ISR is pursued
   //interrupt commands here  

  vel += accel;
} 

void limit(){
  if(should_stop == true){ 
    while(digitalRead(forward) == LOW && digitalRead(backward) == LOW){} //stop the motor
    }
  else{//go the otherway
    dir2(); //switch the direction 
    
    } 
    pulse =0;
  }
