
#include <Wire.h>

#define Address_Bottom 2        //从机地址

char cmd[]={'F','B','L','R','S'};//保存命令字符，F为Forward，B为Back，L为Left，R为Right，S为Stop
int Distance[6];//存储6个模拟口采集到的数值
int Dist_Max=0,Num_Max=0;//采集到的六个值中的最大值和最大值所在的号码
void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop()
{
  Num_Max=0;
  Dist_Max=0;
  for(int i=0;i<6;i++)
  {
    Distance[i]=analogRead(i);//读出第i口的模拟量的值
  }
  for(int i=0;i<6;i++)        //找出最大值及其号码
  {
      if(Distance[i]>Dist_Max)
        {
          Dist_Max=Distance[i];
          Num_Max=i;
        }  
   Serial.print(Distance[i]);
   Serial.print(" ");
  }
  Serial.print("        ");
  Serial.print(Dist_Max);
  Serial.print("   ");
  Serial.println(Num_Max);
  if(Dist_Max>100)                            //根据最大值所在号码发出不同命令
  {
       if(Num_Max<2) {Send_Command(cmd[2],100);}//如果号码为0或1，则发送L100
  else if(Num_Max==4 || Num_Max==5) {Send_Command(cmd[3],100); }//如果号码为4或5则发送R100
  else if(Num_Max==2 || Num_Max==3) 
        {
          if(Dist_Max>800)//如果距离很近
          {
            Send_Command(cmd[4],100);Serial.println(cmd[4]);delay(200);//发送S100，即Stop
          }
          else
          {
            Send_Command(cmd[0],100);Serial.println(cmd[0]); //如果距离没有到达足够近，则发送F100
          }
         }
  }
  else 
  {
    Send_Command(cmd[4],80);Serial.println(cmd[2]); //如果接受到的值都小于100，则表示没有求，小车发送S80
  }
   
   delay(100);//延时100ms
   //Get_Value(Num_Max);
}

 void Send_Command(char command,int num)
 {
  Wire.beginTransmission(Address_Bottom); //发送数据给地址为2的器件
  Wire.write(command);        //发送数据
  Wire.write(num);        //发送数据
  Wire.endTransmission();    // 停止发送
  Serial.println(num);//串口打印，调试时用到的
 }
 

