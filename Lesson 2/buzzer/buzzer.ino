#define BUZZER 16//蜂鸣器连接芯片的引脚号为数字脚16号脚

void setup()   //初始化设置
{
  pinMode(BUZZER,OUTPUT);//初始化设置封面器引脚，设置为输出模式
}
void loop()           //程序运行主函数，会一直循环运行
{
  int i=0;
  //播放声音
  for(i=0;i<80;i++)
  {
    digitalWrite(BUZZER,HIGH);//使16号脚输出5V
    delay(1);                 // 延时1ms
    digitalWrite(BUZZER,LOW);//使16号脚输出0V
    delay(1);               //延时1ms
  }
  //播放另一种音乐
  for(i=0;i<100;i++)
  {
    digitalWrite(BUZZER,HIGH);//使16号脚输出5V
    delay(2);			//延时2ms
    digitalWrite(BUZZER,LOW);//使16号脚输出0V
    delay(2);			//延时2ms
  }
}


