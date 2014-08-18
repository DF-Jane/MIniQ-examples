#define EN1 6//pin for run the right motor 
#define IN1 7//pin for control right motor direction
#define EN2 5//pin for run the left motor 
#define IN2 12//pin for control left motor direction

#define FORW 0
#define BACK 1

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
void setup()
{
  pinMode(5,OUTPUT);//init the motor driver pins
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(12,OUTPUT);
}
void loop()
{
  Motor_Control(FORW,100,FORW,100);//go forward
  delay(500);//500ms
  Motor_Control(FORW,0,FORW,0);//stop
  delay(500);//500ms
  Motor_Control(BACK,150,BACK,150);//go back
  delay(500);//500ms
   Motor_Control(FORW,0,FORW,0);//stop
  delay(500);//500ms
}

