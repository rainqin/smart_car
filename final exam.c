#include <at898252.h>
#include <stdio.h>
#include <absacc.h>
#define uint unsigned int 
#define uchar unsigned char

sbit p11=P1^0;
sbit p12=P1^1;
sbit m1a=P1^2;
sbit m1b=P1^3;
sbit m2a=P1^4;
sbit m2b=P2^4;
sbit choice=P0^5;
sbit visf=P2^5;
sbit visr=P2^6;


uint count0=0;
uint count1=0;
uint motor1, motor2,flag;

uint sight(void);
void delay901(void);
void delay902(void);
void delay903(void);
void avoid(void);

void main(void)
{  
 TMOD=0x11;	   //open time0	and time1
 TH0=0XEF;	  //50ms per interruption
 TL0=0XF0;
 IE=0x8F;
 

 
 while(1)
{ 
 if(choice==0)
{
 if(visf==0)
 {
  avoid();
 }
 else
 {
  TR0=1;
 //p11=1;
 //p12=1;
  m1a=0;
  m1b=1;
  m2a=0;
  m2b=1;
   switch(sight()) 
   {
   case 4: count0=0; count1=0; flag=0;break;
   case 10: motor1=0; motor2=1; flag=1;break;
   case 8: count0=200; count1=0; flag=0;break;
   case 2: count0=0; count1=200;flag=0; break;
   case 1: motor1=1; motor2=0; flag=1;break;
   case 18: motor1=0; motor2=1;flag=1; break;
   case 3: motor1=1; motor2=0; flag=1;break;
   case 0: motor1=1; motor2=1; flag=2;break;
   case 13:count0=200; count1=0; flag=0;break;
   case 6: count0=0; count1=200; flag=0;break;
   default: count0=200; count1=200;flag=0; break;	//slow down
   }
  }
 }


  
  else
  {
  TR0=1;
  p11=1;
  p12=1;
  flag=3;
  }
  }
 }
 


void time0(void) interrupt 1
{
 uint i;
 TH0=0XFE; TL0=0XF0; 
 TR0=0;
 if(flag==1)
 {
  p11=motor1; 
  for(i=0;i<count0;i++)			  //the bigger count, the slower speed
  {} 
  p11=motor1;
  for(i=0;i<200-count0;i++)			  //the bigger count, the slower speed
  {} 
  p12=motor2;
  for(i=0;i<count1;i++)
  {}
  p12=motor2;
  for(i=0;i<200-count1;i++)
  {}
  TR0=1;
 }
 else
 if(flag==0)
 { 
  p11=0; 
  for(i=0;i<count0;i++)			  //the bigger count, the slower speed
  {} 
  p11=1;
  for(i=0;i<200-count0;i++)			  //the bigger count, the slower speed
  {} 
  p12=0;
  for(i=0;i<count1;i++)
  {}
  p12=1;
  for(i=0;i<200-count1;i++)
  {}
  TR0=1;
 } 
 else
 if(flag==2)
 {
  p11=motor1; m1a=0;m1b=1; p12=motor2;m2a=1;m2b=0;
  for(i=0;i<400;i++)			  //the bigger count, the slower speed
  {} 
  TR0=1;
 }
 else
 {
   switch(P2&0X0F)
  {
  case 0x01: m1a=0;m1b=1;m2a=0;m2b=1; break;
  case 0x02: m1a=1;m1b=0;m2a=0;m2b=1; break;
  case 0x04: m1a=0;m1b=1;m2a=1;m2b=0; break;
  case 0x08: m1a=1;m1b=0;m2a=1;m2b=0; break;
  default:   m1a=0;m1b=0;m2a=0;m2b=0; break;
  }
  TR0=1;
 }
}

uint sight(void)
{
 uint a;
 switch (P0&0x1F)
 { 
  case 0x04: a=4; break;
  case 0x10: a=10;break;
  case 0x08: a=8; break;
  case 0x02: a=2; break;
  case 0x01: a=1; break;
  case 0x18: a=18;break;
  case 0x03: a=3; break;
  case 0x00: a=0; break;
  case 0x0C: a=13;break;
  case 0x06: a=6; break;
  default:   a=99;break;
 }
 return(a);
}

void avoid(void)
{
 TR0=0;
 p11=1;
 p12=1;
 m1a=0;m1b=0;m2a=0;m2b=0;       //stop
 delay901();
 m1a=1;m1b=0;m2a=0;m2b=1;		//left
 delay901();
 m1a=0;m1b=1;m2a=0;m2b=1;		//forward
 delay903();
 m1a=1;m1b=0;m2a=0;m2b=0;		//right(small)
 delay902();
 m1a=0;m1b=1;m2a=0;m2b=1;		//forward
 delay903();
 m1a=1;m1b=0;m2a=0;m2b=0;		//right(small)
 delay902();
 m1a=0;m1b=1;m2a=0;m2b=1;		//forward
 delay903();
 m1a=1;m1b=0;m2a=0;m2b=1;		//left
 delay901();
 TR0=1;
}


void delay901()
{
 uint k,l;
 for(k=0;k<500;k++)
 {
 for(l=0;l<150;l++)
 {}
 l=0;
 }
}

void delay902()
{
 uint k,l;
 for(k=0;k<500;k++)
 {
 for(l=0;l<200;l++)
 {}
 l=0;
 }
}

void delay903()
{
 uint k,l;
 for(k=0;k<500;k++)
 {
 for(l=0;l<200;l++)
 {}
 l=0;
 }
}