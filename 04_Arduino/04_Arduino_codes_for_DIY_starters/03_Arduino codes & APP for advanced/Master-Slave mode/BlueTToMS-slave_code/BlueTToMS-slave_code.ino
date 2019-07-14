//----------------------------------------------------------------
//-- OTTO Dance smooth criminal
//-- Released under a GPL licencse
//-- Originally made for Zowi project remake for Otto
//-- Authors:  Javier Isabel:  javier.isabel@bq.com
//--           Juan Gonzalez (obijuan): juan.gonzalez@bq.com
//-----------------------------------------------------------------
#include <Servo.h>
#include <Oscillator.h>
#include <EEPROM.h>
#include <NewPing.h>

#include <SoftwareSerial.h>
SoftwareSerial BTserial(11, 12);

#define N_SERVOS 4
//-- First step: Configure the pins where the servos are attached
/*
         --------------- 
        |     O   O     |
        |---------------|
YR 3==> |               | <== YL 2
         --------------- 
            ||     ||
            ||     ||
RR 5==>   -----   ------  <== RL 4
         |-----   ------|
*/
#define EEPROM_TRIM false 
// Activate to take callibration data from internal memory
#define TRIM_RR 7
#define TRIM_RL 4
#define TRIM_YR  4
#define TRIM_YL -7
//OTTO.setTrims(-7,-4,-4,7);

#define PIN_RR 5
#define PIN_RL 4
#define PIN_YR 3
#define PIN_YL 2
 
#define TRIGGER_PIN  9
#define ECHO_PIN     10
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

#define INTERVALTIME 10.0 

Oscillator servo[N_SERVOS];

void goingUp(int tempo);
void drunk (int tempo);
void noGravity(int tempo);
void kickLeft(int tempo);
void kickRight(int tempo);
void run(int steps, int T=500);
void runback(int steps, int T=500);
void walk(int steps, int T=1000);
void backyard(int steps, int T=3000);
void backyardSlow(int steps, int T=5000);
void turnLeft(int steps, int T=3000);
void turnRight(int steps, int T=3000);
void moonWalkLeft(int steps, int T=1000);
void moonWalkRight(int steps, int T=1000);
void crusaito(int steps, int T=1000);
void swing(int steps, int T=1000);
void upDown(int steps, int T=1000);
void upDownleft(int steps, int T=1000);
void upDownright(int steps, int T=1000);
void flapping(int steps, int T=1000);

char data = 0;
char newdata = 0;

void setup()
{
  Serial.begin(9600);
  BTserial.begin(38400);
  
  servo[0].attach(PIN_RR);
  servo[1].attach(PIN_RL);
  servo[2].attach(PIN_YR);
  servo[3].attach(PIN_YL);
  
  //EEPROM.write(0,TRIM_RR);
  //EEPROM.write(1,TRIM_RL);
  //EEPROM.write(2,TRIM_YR);
  //EEPROM.write(3,TRIM_YL);
  
  int trim;
  
  if(EEPROM_TRIM){
    for(int x=0;x<4;x++){
      trim=EEPROM.read(x);
      if(trim>128)trim=trim-256;
      Serial.print("TRIM ");
      Serial.print(x);
      Serial.print(" en ");
      Serial.println(trim);
      servo[x].SetTrim(trim);
    }
  }
  else{
    servo[0].SetTrim(TRIM_RR);
    servo[1].SetTrim(TRIM_RL);
    servo[2].SetTrim(TRIM_YR);
    servo[3].SetTrim(TRIM_YL);
  }
  
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
}

// TEMPO: 121 BPM
int t=495;
double pause=0;hahaha

void loop()
{
   if(BTserial.available() > 0)  // Send data only when you receive data:
  {
    data = BTserial.read();      //Read the incoming data and store it into variable data
    Serial.print(data);        //Print Value inside data in Serial monitor
    Serial.print("\n");        //New line 
    if(data == '1')            //Checks whether value of data is equal to 1 
   {
    //dance();
    dancekickit();
    //danceluhan();
    for(int i=0;i<4;i++) servo[i].SetPosition(90);
   }  
    else if(data == '0')       //Checks whether value of data is equal to 0
    {
     // Forward();
      //for(int i=0;i<4;i++) servo[i].SetPosition(90);
      
       
        
       while(data!= '3'||newdata!='3'){
         if(Serial.available() > 0)  // Send data only when you receive data:
          data = Serial.read();      //Read the incoming data and store it into variable data
          Serial.print(data);        //Print Value inside data in Serial monitor
          Serial.print("\n");        //New line 
         delay(500);
    Serial.print("Ping: ");
    Serial.print(sonar.ping_cm());
  
    Serial.println("cm");
      long duration, distance;
      digitalWrite(TRIGGER_PIN, LOW);  // Added this line
    delayMicroseconds(2); // Added this line
    digitalWrite(TRIGGER_PIN, HIGH);
    //  delayMicroseconds(1000); - Removed this line
   delayMicroseconds(10); // Added this line
    digitalWrite(TRIGGER_PIN, LOW);
    duration = pulseIn(ECHO_PIN, HIGH);
    distance = (duration/2) / 29.1;
    /*if(data == '0')
    {
      for(int i=0;i<4;i++) servo[i].SetPosition(90);
    } 
    else */ if(sonar.ping_cm() < 7) {  // This is where the LED On/Off happens
        backyard(2,t*2);
       turnRight(4,t*2);
      
    }
     else{
       walk(4,t*2);
      
    
    } 
    newdata = BTserial.read();
       }
       

     
 
    }
    else if(data == '3')       //Checks whether value of data is equal to 0
    {
     Forward();
     for(int i=0;i<4;i++) servo[i].SetPosition(90);
    }
    else if(data == '4')       //Checks whether value of data is equal to 0
    {
      Lwalk();
      for(int i=0;i<4;i++) servo[i].SetPosition(90);
    }
      else if(data == '5')       //Checks whether value of data is equal to 0
    {
      Backward();
      for(int i=0;i<4;i++) servo[i].SetPosition(90);
    }
      else if(data == '6')       //Checks whether value of data is equal to 0
    {
      Rwalk();
      for(int i=0;i<4;i++) servo[i].SetPosition(90);
    }
    else if(data == '7')       //Checks whether value of data is equal to 0
    {
      
      Lturn();
      for(int i=0;i<4;i++) servo[i].SetPosition(90);
    }
    else if(data == '8')       //Checks whether value of data is equal to 0
    {
      
      Rturn();
      for(int i=0;i<4;i++) servo[i].SetPosition(90);
    }
    
      
  } 
 
}
void Forward(){
  walk(1,t*2);
}
void Backward(){
  backyard(1,t*2);
}
void Rwalk(){
  moonWalkRight(1,t*2);
 
}
void Lwalk(){
   moonWalkLeft(1,t*2);
}
void Rturn(){
  turnRight(1,t*2);
}
void Lturn(){
  turnLeft(1,t*2);
}

void danceluhan(){
 
  upDown(4, t/1.5);
  drunk(t*4);
  upDownright(1, t*1.2);
  upDownleft(1, t*1.2);
  upDownright(1, t*1.2);
  upDownleft(1, t*1.2);
  backyard(2,t*4);
  walk(3,t*2);

  delay(500);
  crusaito(1,t*7);
  run(5,t);
  delay(500);
  crusaito(2,t*3);
  goingUp(t);
  
}
void dancekickit(){
  drunk(t*4);
  drunk(t*4);
  turnLeft(4,t*2);
  upDown(6, t);
  turnRight(4,t*2);
  upDown(6, t);
  walk(2,t*2);
  backyard(2,t*2);
  walk(4,t);
  backyard(4,t);
  goingUp(t);
  crusaito(1,t*8);
  
  flapping(1,t/2);
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  delay(500);
  flapping(1,t/2);  
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  delay(700);
  flapping(1,t/2); 
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  backyard(1,t*2);
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  delay(500);
  flapping(1,t/2);
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  delay(700);
  flapping(1,t/2);
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  delay(700);
  flapping(1,t/2);

  swing(8,t);
  upDown(7, t);
  crusaito(2,t);
  
  delay(500);
  
  run(4,t/2);
  run(4,t/2);
  flapping(8,t/2);
  
  run(4,t/2);
  run(4,t/2);
  flapping(4,t/2);

  runback(4,t/2);
  runback(4,t/2);
  flapping(8,t/2);

  runback(4,t/2);
  runback(4,t/2);

  crusaito(4,t);
  kickLeft(t/1.5);
  kickLeft(t/1.5);
  kickRight(t/1.5);
  kickRight(t/1.5);

  delay(700);
  flapping(1,t/2);

  swing(8,t);
  upDown(7, t);
  crusaito(2,t);
}
void dance(){
  primera_parte();
  segunda_parte();
  moonWalkLeft(4,t*2);
  moonWalkRight(4,t*2);
  moonWalkLeft(4,t*2);
  moonWalkRight(4,t*2);
  primera_parte(); 
  crusaito(1,t*8);
  crusaito(1,t*7);

  for (int i=0; i<16; i++){
    flapping(1,t/4);
    delay(3*t/4);
  }
 
  moonWalkRight(4,t*2);
  moonWalkLeft(4,t*2);
  moonWalkRight(4,t*2);
  moonWalkLeft(4,t*2);

  drunk(t*4);
  drunk(t*4);
  drunk(t*4);
  drunk(t*4);
  kickLeft(t);
  kickRight(t);
  drunk(t*8);
  drunk(t*4);
  drunk(t/2);
  delay(t*4); 

  drunk(t/2);

  delay(t*4); 
  walk(2,t*2);
  backyard(2,t*2);
  goingUp(t*2);
  goingUp(t*1);
  noGravity(t*2);
  crusaito(1,t*2);
  crusaito(1,t*8);
  crusaito(1,t*2);
  crusaito(1,t*8);
  crusaito(1,t*2);
  crusaito(1,t*3);

  delay(t);
  primera_parte();
    for (int i=0; i<32; i++){
    flapping(1,t/2);
    delay(t/2);
  }
  
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
}




////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////FUNCIONES DE CONTROL//////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

void oscillate(int A[N_SERVOS], int O[N_SERVOS], int T, double phase_diff[N_SERVOS]){
  for (int i=0; i<4; i++) {
    servo[i].SetO(O[i]);
    servo[i].SetA(A[i]);
    servo[i].SetT(T);
    servo[i].SetPh(phase_diff[i]);
  }
  double ref=millis();
   for (double x=ref; x<T+ref; x=millis()){
     for (int i=0; i<4; i++){
        servo[i].refresh();
     }
  }
}

unsigned long final_time;
unsigned long interval_time;
int oneTime;
int iteration;
float increment[N_SERVOS]; 
int oldPosition[]={90,90,90,90};

void moveNServos(int time, int  newPosition[]){
  for(int i=0;i<N_SERVOS;i++)  increment[i] = ((newPosition[i])-oldPosition[i])/(time/INTERVALTIME);
  
  final_time =  millis() + time; 
  
  iteration = 1; 
  while(millis() < final_time){ //Javi del futuro cambia esto  
      interval_time = millis()+INTERVALTIME;  
      
      oneTime=0;      
      while(millis()<interval_time){    
          if(oneTime<1){ 
              for(int i=0;i<N_SERVOS;i++){
                  servo[i].SetPosition(oldPosition[i] + (iteration * increment[i]));
              }     
              iteration++;
              oneTime++;
          }
      }     
  }   

  for(int i=0;i<N_SERVOS;i++){  
    oldPosition[i] = newPosition[i];
  }   
}


//////////////////////////////////////////////////////////////////////////////
////////////////////////////////PASOS DE BAILE////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void goingUp(int tempo){
      if(data == '0')       //Checks whether value of data is equal to 0
    {
      digitalWrite(13, LOW);   //If value is 0 then LED turns OFF     
      for(int i=0;i<4;i++) servo[i].SetPosition(90);
    }
  
      pause=millis();
      for(int i=0;i<4;i++) servo[i].SetPosition(90);
      delay(tempo);
      servo[0].SetPosition(80);
      servo[1].SetPosition(100);
      delay(tempo);
      servo[0].SetPosition(70);
      servo[1].SetPosition(110);
      delay(tempo);
      servo[0].SetPosition(60);
      servo[1].SetPosition(120);
      delay(tempo);
      servo[0].SetPosition(50);
      servo[1].SetPosition(130);
      delay(tempo);
      servo[0].SetPosition(40);
      servo[1].SetPosition(140);
      delay(tempo);
      servo[0].SetPosition(30);
      servo[1].SetPosition(150);
      delay(tempo);
      servo[0].SetPosition(20);
      servo[1].SetPosition(160);
      delay(tempo);
      
      while(millis()<pause+8*t);

}

void primera_parte(){

  if(data == '0')       //Checks whether value of data is equal to 0
    {
      digitalWrite(13, LOW);   //If value is 0 then LED turns OFF     
      for(int i=0;i<4;i++) servo[i].SetPosition(90);
    }
    
  int move1[4] = {60,120,90,90};
  int move2[4] = {90,90,90,90};
  int move3[4] = {40,140,90,90};
  
  for(int x=0; x<3; x++){
    for(int i=0; i<3; i++){
      lateral_fuerte(1,t/2);
      lateral_fuerte(0,t/4);
      lateral_fuerte(1,t/4);
      delay(t);
    }
  
    pause=millis();
    for(int i=0;i<4;i++) servo[i].SetPosition(90);
    moveNServos(t*0.4,move1);
    moveNServos(t*0.4,move2);
    while(millis()<(pause+t*2));
  }
  
  for(int i=0; i<2; i++){
    lateral_fuerte(1,t/2);
    lateral_fuerte(0,t/4);
    lateral_fuerte(1,t/4);
    delay(t);
  }
    
  pause=millis();
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  crusaito(1,t*1.4);
  moveNServos(t*1,move3);
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  while(millis()<(pause+t*4));
}

void segunda_parte(){
  if(data == '0')       //Checks whether value of data is equal to 0
    {
      digitalWrite(13, LOW);   //If value is 0 then LED turns OFF     
      for(int i=0;i<4;i++) servo[i].SetPosition(90);
    }
  
  int move1[4] = {90,90,80,100};
  int move2[4] = {90,90,100,80};
  int move3[4] = {90,90,80,100};
  int move4[4] = {90,90,100,80};
    
  int move5[4] = {40,140,80,100};
  int move6[4] = {40,140,100,80};
  int move7[4] = {90,90,80,100};
  int move8[4] = {90,90,100,80};
       
  int move9[4] = {40,140,80,100};
  int move10[4] = {40,140,100,80};
  int move11[4] = {90,90,80,100};
  int move12[4] = {90,90,100,80};
  
  for(int x=0; x<7; x++){ 
    for(int i=0; i<3; i++){
      pause=millis();
      moveNServos(t*0.15,move1);
      moveNServos(t*0.15,move2);
      moveNServos(t*0.15,move3);
      moveNServos(t*0.15,move4);
      while(millis()<(pause+t));
    }
    pause=millis();
    moveNServos(t*0.15,move5);
    moveNServos(t*0.15,move6);
    moveNServos(t*0.15,move7);
    moveNServos(t*0.15,move8);
    while(millis()<(pause+t));
  }
 
  for(int i=0; i<3; i++){
    pause=millis();
    moveNServos(t*0.15,move9);
    moveNServos(t*0.15,move10);
    moveNServos(t*0.15,move11);
    moveNServos(t*0.15,move12);
    while(millis()<(pause+t));
  }
}

void lateral_fuerte(boolean side, int tempo){
  if(data == '0')       //Checks whether value of data is equal to 0
    {
      digitalWrite(13, LOW);   //If value is 0 then LED turns OFF     
      for(int i=0;i<4;i++) servo[i].SetPosition(90);
    }
  
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  if (side) servo[0].SetPosition(40);
  else servo[1].SetPosition(140);
  delay(tempo/2);
  servo[0].SetPosition(90);
  servo[1].SetPosition(90);
  delay(tempo/2);

}

void drunk (int tempo){
  if(data == '0')       //Checks whether value of data is equal to 0
    {
      digitalWrite(13, LOW);   //If value is 0 then LED turns OFF     
      for(int i=0;i<4;i++) servo[i].SetPosition(90);
    }
  
  pause=millis();
  
  int move1[] = {60,70,90,90};
  int move2[] = {110,120,90,90};
  int move3[] = {60,70,90,90};
  int move4[] = {110,120,90,90};
  
  moveNServos(tempo*0.235,move1);
  moveNServos(tempo*0.235,move2);
  moveNServos(tempo*0.235,move3);
  moveNServos(tempo*0.235,move4);
  while(millis()<(pause+tempo));

}


void noGravity(int tempo){
  
  int move1[4] = {120,140,90,90};
  int move2[4] = {140,140,90,90};
  int move3[4] = {120,140,90,90};
  int move4[4] = {90,90,90,90};
  
  
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  for(int i=0;i<N_SERVOS;i++) oldPosition[i]=90;
  moveNServos(tempo*2,move1);
  moveNServos(tempo*2,move2);
  delay(tempo*2);
  moveNServos(tempo*2,move3);
  moveNServos(tempo*2,move4);

 

}

void kickLeft(int tempo){
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  delay(tempo);
  servo[0].SetPosition(50); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo);
  servo[0].SetPosition(80); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(30); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(80); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(30); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(80); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo);
}

void kickRight(int tempo){
for(int i=0;i<4;i++) servo[i].SetPosition(90);
  delay(tempo);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(130); //pie izquiero
  delay(tempo);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(100); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(150); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(80); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(150); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(100); //pie izquiero
  delay(tempo);
}

void walk(int steps, int T){
    int A[4]= {15, 15, 30, 30};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void run(int steps, int T){
    int A[4]= {10, 10, 10, 10};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}
void runback(int steps, int T){
    int A[4]= {10, 10, 10, 10};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(-90), DEG2RAD(-90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}
void backyard(int steps, int T){
    int A[4]= {15, 15, 30, 30};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(-90), DEG2RAD(-90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void backyardSlow(int steps, int T){
    int A[4]= {15, 15, 30, 30};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(-90), DEG2RAD(-90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}


void turnLeft(int steps, int T){
    int A[4]= {20, 20, 10, 30};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void turnRight(int steps, int T){
    int A[4]= {20, 20, 30, 10};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void moonWalkRight(int steps, int T){
    int A[4]= {25, 25, 0, 0};
    int O[4] = {-15 ,15, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void moonWalkLeft(int steps, int T){
    int A[4]= {25, 25, 0, 0};
    int O[4] = {-15, 15, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 - 120), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void crusaito(int steps, int T){
    int A[4]= {25, 25, 30, 30};
    int O[4] = {- 15, 15, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void swing(int steps, int T){
    int A[4]= {25, 25, 0, 0};
    int O[4] = {-15, 15, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void upDown(int steps, int T){
    int A[4]= {25, 25, 0, 0};
    int O[4] = {-15, 15, 0, 0};
    double phase_diff[4] = {DEG2RAD(180), DEG2RAD(0), DEG2RAD(270), DEG2RAD(270)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}
void upDownleft(int steps, int T){
    int A[4]= {25, 0, 0, 0};
    int O[4] = {-15, 15, 0, 0};
    double phase_diff[4] = {DEG2RAD(180), DEG2RAD(0), DEG2RAD(270), DEG2RAD(270)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}
void upDownright(int steps, int T){
    int A[4]= {0, 25, 0, 0};
    int O[4] = {-15, 15, 0, 0};
    double phase_diff[4] = {DEG2RAD(180), DEG2RAD(0), DEG2RAD(270), DEG2RAD(270)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void flapping(int steps, int T){
    int A[4]= {15, 15, 8, 8};
    int O[4] = {-A[0], A[1], 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180), DEG2RAD(90), DEG2RAD(-90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void test(int steps, int T){
    int A[4]= {15, 15, 8, 8};
    int O[4] = {-A[0] + 10, A[1] - 10, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180), DEG2RAD(90), DEG2RAD(-90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}
