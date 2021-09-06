#include <reg52.h>

//定义步进电机连接端口
sbit A1=P1^0;
sbit B1=P1^1;
sbit C1=P1^2;
sbit D1=P1^3;
//按键位定义
sbit key_s2 = P3^0;
sbit key_s3 = P3^1;
sbit key_s4 = P3^2;//
sbit key_s5 = P3^3;//
//LED灯位定义
sbit LED1 = P0^0;
sbit LED2 = P0^1;
sbit LED3 = P0^2;

#define Coil_AB1 {A1=1;B1=1;C1=0;D1=0;}//AB相通电，其他相断电
#define Coil_BC1 {A1=0;B1=1;C1=1;D1=0;}//BC相通电，其他相断电
#define Coil_CD1 {A1=0;B1=0;C1=1;D1=1;}//CD相通电，其他相断电
#define Coil_DA1 {A1=1;B1=0;C1=0;D1=1;}//D相通电，其他相断电

#define Coil_A1 {A1=1;B1=0;C1=0;D1=0;}//A相通电，其他相断电
#define Coil_B1 {A1=0;B1=1;C1=0;D1=0;}//B相通电，其他相断电
#define Coil_C1 {A1=0;B1=0;C1=1;D1=0;}//C相通电，其他相断电
#define Coil_D1 {A1=0;B1=0;C1=0;D1=1;}//D相通电，其他相断电

#define Coil_OFF {A1=0;B1=0;C1=0;D1=0;}//全部断电

unsigned char Speed;
unsigned char i;
/*------------------------------------------------
uS延时函数，含有输入参数 unsigned char t，无返回值
unsigned char 是定义无符号字符变量，其值的范围是
0~255 这里使用晶振12M，精确延时请使用汇编,大致延时
长度如下 T=tx2+5 uS 
------------------------------------------------*/
void DelayUs2x(unsigned char t)
{   
while(--t);
}
/*------------------------------------------------
mS延时函数，含有输入参数 unsigned char t，无返回值
unsigned char 是定义无符号字符变量，其值的范围是
0~255 这里使用晶振12M，精确延时请使用汇编
------------------------------------------------*/
void DelayMs(unsigned char t)
{

while(t--)
{
     //大致延时1mS
     DelayUs2x(245);
         DelayUs2x(245);
}
}
/*------------------------------------------------
                    主函数
------------------------------------------------*/
main()
{
unsigned int i=512;//旋转一周时间
unsigned char num;
EA=1;          //全局中断开
EX0=1;         //外部中断0开
IT0=1;         //1表示边沿触发
while(1)
{
		Coil_OFF
		Speed = 1;
	    num = 0;
		 	if(key_s2 == 0)	 //
		{
						DelayMs(10);
						if(key_s2 == 0)
					{
						 Coil_OFF
					}
		}
		if(key_s3 == 0)	 //
		{
						DelayMs(10);
						if(key_s3 == 0)
					{
						for(i=0;i++;i<255)
						{
						 
						 Speed++;
						}
					}
		}
		if(key_s5 == 0)	 //
		{
						DelayMs(10);
						if(key_s5 == 0)
					{

					     if(i >= 0)
						 {
						  Speed--;}
					}
		}
		while((i--)&&key_s2)  //正向
		  {  
		     Coil_A1       
		     DelayMs(Speed);
		     Coil_AB1                //遇到Coil_AB1  用{A1=1;B1=1;C1=0;D1=0;}代替
		     DelayMs(Speed);         //改变这个参数可以调整电机转速 ,
		                             //数字越小，转速越大,力矩越小
		         Coil_B1       
		     DelayMs(Speed);
		     Coil_BC1
		     DelayMs(Speed);
		         Coil_C1       
		     DelayMs(Speed);
		     Coil_CD1
		     DelayMs(Speed);
		         Coil_D1       
		     DelayMs(Speed);
		     Coil_DA1
		     DelayMs(Speed);
		  }
		  Coil_OFF
		  i=512;
		  while((i--)&&(!key_s2))//反向
		  {  
		     Coil_A1       
		     DelayMs(Speed);
		     Coil_DA1                //遇到Coil_AB1  用{A1=1;B1=1;C1=0;D1=0;}代替
		     DelayMs(Speed);         //改变这个参数可以调整电机转速 ,
		                             //数字越小，转速越大,力矩越小
		         Coil_D1       
		     DelayMs(Speed);
		     Coil_CD1
		     DelayMs(Speed);
		         Coil_C1       
		     DelayMs(Speed);
		     Coil_BC1
		     DelayMs(Speed);
		         Coil_B1       
		     DelayMs(Speed);
		     Coil_AB1
		     DelayMs(Speed);
		  }
		}
		
}
/*------------------------------------------------
                 外部中断程序
------------------------------------------------*/
void ISR_INT0(void) interrupt 0 
{

if(!INT0)
   {
   DelayMs(10);//在此处可以添加去抖动程序，防止按键抖动造成错误
   if(!INT0)
//  while(!INT1);//等待按键释放
     {
     key_s2=!key_s2;   
     }
   }
}