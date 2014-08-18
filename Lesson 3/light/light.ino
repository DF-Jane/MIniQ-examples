
#define BUZZER 16//定义BUZZER的值为16，即数字脚16号引脚

void setup()    //程序初始化
{
  pinMode(BUZZER,OUTPUT);//设置数字脚16号脚为输出模式
  Serial.begin(9600);//串口通讯速率设置为9600
}

void loop()             //会一直循环运行主函数，会一直循环运行
{
  int i=0,j=0;
  i=analogRead(5);      //i的值为5号模拟引脚读到的电压值
  Serial.println(i);    //使用串口将数值打印到电脑上
  if(i<400)             //如果左边有光
  {
    for(i=0;i<80;i++)    //蜂鸣器以一定频率鸣叫
    {
      digitalWrite(BUZZER,HIGH);//16号引脚输出为5V
      delay(1);                 // 延时1ms
      digitalWrite(BUZZER,LOW);//16号引脚输出为0V
      delay(1);   //延时1ms
    }
  }
  else if (i>600)         //如果左边没有光的情况下右边有光
  {
    for(i=0;i<80;i++)       //蜂鸣器以另一种频率鸣叫
    {
      digitalWrite(BUZZER,HIGH);//16号引脚输出为5V
      delay(3);                 // 延时3ms
      digitalWrite(BUZZER,LOW);//16号引脚输出为0V
      delay(3);   //延时3ms
    }
  }
}



