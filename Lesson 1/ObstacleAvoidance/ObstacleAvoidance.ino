#define EN1 6//右侧电机使能端
#define IN1 7//右侧电机方向端
#define EN2 5//左侧电机使能端
#define IN2 12//左侧电机方向端

#define FORW 0//前进
#define BACK 1//后退

#define IR_IN  17//红外接收
#define L_IR 13//左红外发送
#define R_IR 8//右红外发送

int   count;//对返回的脉冲进行计数

//控制电机转动
void Motor_Control(int M1_DIR,int M1_EN,int M2_DIR,int M2_EN)
{
  //////////M1////////////////////////
  if(M1_DIR==FORW)  digitalWrite(IN1,FORW); else digitalWrite(IN1,BACK);
  if(M1_EN==0)       analogWrite(EN1,LOW);  else analogWrite(EN1,M1_EN);
  ///////////M2//////////////////////
  if(M2_DIR==FORW) digitalWrite(IN2,FORW);  else digitalWrite(IN2,BACK);
  if(M2_EN==0)     analogWrite(EN2,LOW);    else analogWrite(EN2,M2_EN);
}
//避障
void L_Send40KHZ(void)//左发射管发射频率为40kHZ脉冲
{
  int i;
  for(i=0;i<24;i++)
  {
    digitalWrite(L_IR,LOW);//设置左发射管为高电平
    delayMicroseconds(8);//延时
    digitalWrite(L_IR,HIGH);//设置左发射管为低电平
    delayMicroseconds(8);//延时
  }
}

void R_Send40KHZ(void)//右发射管发射频率为40kHZ脉冲
{
  int i;
  for(i=0;i<24;i++)
  {
    digitalWrite(R_IR,LOW);//设置右发射管为高电平
    delayMicroseconds(8);//延时
    digitalWrite(R_IR,HIGH);//设置右发射管为低电平
    delayMicroseconds(8);//延时
  }
}

void pcint0_init(void)//引脚变化中断初始化
{
  PCICR = 0X01;//使能第0组引脚变化中断
  PCMSK0 = 0X01;//使能第0组的第0个引脚变化中断
}
ISR(PCINT0_vect)//PB0引脚变化中断
{
  count++;//计数接收到的脉冲
}

void Obstacle_Avoidance(void)//避障子函数
{   
  char i;
  count=0;
  for(i=0;i<20;i++)//左发射管发射20个脉冲
  {
    L_Send40KHZ();
    delayMicroseconds(600);    
  }
  if(count>20)//接收超过10个脉冲，判断有障碍物 
  {
      Motor_Control(BACK,100,BACK,100);//后退
      delay(200);//延时
      Motor_Control(BACK,100,FORW,100);//右转
      delay(200);//延时
  }
  else
  {
      Motor_Control(FORW,100,FORW,100);//前进
  }
  count=0;
  for(i=0;i<20;i++)//右发射管发射20个脉冲
  {
    R_Send40KHZ(); 
    delayMicroseconds(600);        
  }
  if(count>20)
  {
      Motor_Control(BACK,100,BACK,100);//后退
      delay(200);//延时
      Motor_Control(FORW,100,BACK,100);//左转
      delay(200);//延时
  }
  else
  {
      Motor_Control(FORW,100,FORW,100);//前进
  }
}

void setup()
{
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(12,OUTPUT);
  
  pinMode(8,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(16,OUTPUT);
  pinMode(17,INPUT);

  pcint0_init();
}
void loop()
{
  Obstacle_Avoidance();
}
