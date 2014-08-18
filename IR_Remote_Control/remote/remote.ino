#include <IRremote.h>

#define EN1 6//pin for run the right motor 
#define IN1 7//pin for control right motor direction
#define EN2 5//pin for run the left motor 
#define IN2 12//pin for control left motor direction

#define FORW 0//go forward
#define BACK 1//go back

#define IR_IN  17//IR receiver pin
IRrecv irrecv(IR_IN);
decode_results results;

int count;//count the motor speed pulse

void Motor_Control(int M1_DIR,int M1_EN,int M2_DIR,int M2_EN)//control motor
{
  //////////M1////////////////////////
  if(M1_DIR==FORW)//M1 motor direction
    digitalWrite(IN1,FORW);//forward
  else
    digitalWrite(IN1,BACK);//back
  if(M1_EN==0)
    analogWrite(EN1,LOW);//stop
  else
    analogWrite(EN1,M1_EN);//set speed

  ///////////M2//////////////////////
  if(M2_DIR==FORW)
    digitalWrite(IN2,FORW);
  else
    digitalWrite(IN2,BACK);
  if(M2_EN==0)
    analogWrite(EN2,LOW);
  else
    analogWrite(EN2,M2_EN);
}

void dump(decode_results *results)
{
  if(results->value==0x00fd00ff)
  {
    Motor_Control(FORW,0,FORW,0);//停止   
  }
  if(results->value==0x00fd807f)
  {
    Motor_Control(FORW,100,FORW,100);//前进 
  }
  if(results->value==0x00fd906f)
  {
    Motor_Control(BACK,100,BACK,100);//后退
  }
  if(results->value==0x00fd20df)
  {
    Motor_Control(FORW,100,BACK,100);//左转 
  }
  if(results->value==0x00fd609f)
  {
    Motor_Control(BACK,100,FORW,100);//右转
  }
}

void setup()
{
  pinMode(5,OUTPUT);//init the motor driver pins
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(12,OUTPUT);
  
  irrecv.enableIRIn();
}
void loop()
{
  Motor_Control(FORW,0,FORW,0);//run motor
  while(1)
  {
   if(irrecv.decode(&results))
   {
      dump(&results);
      irrecv.resume();
   }
  }
}
