
#define BUZZER 16//buzzer io pin
#define Vr   5//reference voltage

float data=0xff;//save the button input value

void buzzer(void)//buzzer sound
{
  digitalWrite(BUZZER,HIGH);//turn it on
  delay(1);
  digitalWrite(BUZZER,LOW);//turn it off
  delay(10);
}


void setup()
{
  pinMode(BUZZER,OUTPUT);//init buzzer
}
void loop()
{
  data=analogRead(6);
  data = ((data * Vr) / 1024);

  if(data>4.50&&data<6.00)//no input
    return;
  else
  {
    if(data>=0.00&&data<0.80)//press button1
    {
      delay(180);//remove noise
      if(data>=0.00&&data<0.80)//confirm the button pressed
      {
        for(int i=0;i<60;i++)
        {
          digitalWrite(BUZZER,HIGH);//turn it on
          delay(1);
          digitalWrite(BUZZER,LOW);//turn it off
          delay(1);
        }
      }
    }
    else if(data>=0.8&&data<3)
    {
      delay(180);
      if(data>=0.8&&data<3)
      {
        for(int i=0;i<60;i++)
        {
          digitalWrite(BUZZER,HIGH);//turn it on
          delay(3);
          digitalWrite(BUZZER,LOW);//turn it off
          delay(1);
        }
      }
    }
    else if(data>=3&&data<4)
    {
      delay(180);
      if(data>=3&&data<4)
      {
        for(int i=0;i<60;i++)
        {
          digitalWrite(BUZZER,HIGH);//turn it on
          delay(2);
          digitalWrite(BUZZER,LOW);//turn it off
          delay(2);
        }
      }
    }
  }
}




