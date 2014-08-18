

#define EN1 5//pin for run the left motor 
#define IN1 12//pin for control left motor direction
#define EN2 6//pin for run the right motor 
#define IN2 7//pin for control right motor direction


#define Forward 0      //前进值
#define Back 1         //后退值

int data[5]={};

void Motor(int M1_DIR,int M1_EN,int M2_DIR,int M2_EN)//control the motor
{
  //////////M1为左边电机////////////////////////
  if(M1_DIR==Forward)//判断M1电机的方向
    digitalWrite(IN1,Forward);//前进
  else
    digitalWrite(IN1,Back);//后退
  if(M1_EN==0)
    analogWrite(EN1,LOW);//停止 
 else
    analogWrite(EN1,M1_EN);//速度设置

  ///////////M2为右边电机//////////////////////
  if(M2_DIR==Forward)
    digitalWrite(IN2,Forward);
  else
    digitalWrite(IN2,Back);
  if(M2_EN==0)
    analogWrite(EN2,LOW);
  else
    analogWrite(EN2,M2_EN);
}

void Read_Value(void)//读出5路巡线传感器的返回值
{  
  char i;
  for(i=0;i<5;i++)
  {
    data[i]=analogRead(i);//将5路巡线传感器的返回值存在数组里
  }
}

void huntline_deal( )//巡线函数，为白纸上巡黑线，样板黑色返回值小于700，白色大于800
{
  if((data[0]<650 || data[1] <650) && (data[3]>800 && data[4]>800))//左边黑线
  { 
    Motor(Forward,0,Forward,110);//右转
    delay(10);
  }
  else  if((data[3]<650 || data[4] <650) && (data[0]>800 && data[1]>800))//右边黑线
  {
    Motor(Forward,110,Forward,0);//左转
    delay(10);
  }
  else if(data[2]<700)//中间黑线
  {
    Motor(Forward,90,Forward,90);//执行
    delay(20);
  }
  else 
  {
    Motor(Forward,70,Forward,70);//不明状况暂定为较缓前进
  }
}


void setup()
{
  pinMode(5,OUTPUT);//初始化电机控制脚为输出
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(12,OUTPUT); 
  Motor(Forward,0,Forward,0);//电机停转
}

void loop()
{
  Read_Value();//读取巡线传感器返回值
  huntline_deal();//巡线程序
}









