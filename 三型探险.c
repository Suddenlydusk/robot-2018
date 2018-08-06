//    崇宏感测 CHGC www.chgckj.com	
#include <includes.h> 
int CHGCi; 

//////////////////////////////设置灰度的最大值与最小值
int aq=520;//红色
int ah=530;//在灰色台子上的灰度
int amax=650;
int amini=350;
int a=610; /////////循迹卡灰度的阀值a17:150;   a18:600

int m;
int ar;
int t;
int c;
int v;
/* int QR_recognize(); */
int a_v;
int a_t;
int v0;
int v1;		
int q;
int i;
int i1;
///////////////////////////////////////////////////////定义数字端口
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
#define d1 digital(1)
#define d2 digital(2)
#define d3 digital(3)
#define d4 digital(4)		

///////////////////////////////////////////////////////命令简化定义
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
#define   ws   while(1){stop();}
#define   w while	
#define  st stop
#define  r  run
#define   s sleep	
#define   ms msleep
#define   rec digit_recognize()	
#define   com compass()

///////////////////////////////////////////////////////定义多通道灰度端口
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
#define a8 analog(8)
#define a7 analog(7)
#define a6 analog(6)
#define a5 analog(5)
#define a4 analog(4)
#define a3 analog(3)
#define a2 analog(2)
#define a1 analog(1)
#define a17 analog(17) //////左
#define a18 analog(18)
#define add  a1+a2+a3+a4+a5+a6+a7+a8	

///////////////////////////////////////////////////////灰度最大值通道状态的定义
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
#define maxa1 ((a1>a2)&&(a1>a3)&&(a1>a4)&&(a1>a5)&&(a1>a6)&&(a1>a7)&&(a1>a8))
#define maxa2 ((a2>a1)&&(a2>a3)&&(a2>a4)&&(a2>a5)&&(a2>a6)&&(a2>a7)&&(a2>a8))
#define maxa3 ((a3>a1)&&(a3>a2)&&(a3>a4)&&(a3>a5)&&(a3>a6)&&(a3>a7)&&(a3>a8))
#define maxa4 ((a4>a1)&&(a4>a2)&&(a4>a3)&&(a4>a5)&&(a4>a6)&&(a4>a7)&&(a4>a8))
#define maxa5 ((a5>a1)&&(a5>a2)&&(a5>a3)&&(a5>a4)&&(a5>a6)&&(a5>a7)&&(a5>a8))
#define maxa6 ((a6>a1)&&(a6>a2)&&(a6>a3)&&(a6>a4)&&(a6>a5)&&(a6>a7)&&(a6>a8))
#define maxa7 ((a7>a1)&&(a7>a2)&&(a7>a3)&&(a7>a4)&&(a7>a5)&&(a7>a6)&&(a7>a8))
#define maxa8 ((a8>a1)&&(a8>a2)&&(a8>a3)&&(a8>a4)&&(a8>a5)&&(a8>a6)&&(a8>a7))
#define maxaa ((a1>450)||(a2>450)||(a3>450)||(a6>450)||(a7>450)||(a8>450))
#define max45 ((a5>a6)&&(a5>a7)&&(a5>a8)&&(a4>a3)&&(a4>a2)&&(a4>a1))

#define min1 ((a1<a2)&&(a1<a3)&&(a1<a4)&&(a1<a5)&&(a1<a6)&&(a1<a7)&&(a1<a8))
#define min2 ((a2<a1)&&(a2<a3)&&(a2<a4)&&(a2<a5)&&(a2<a6)&&(a2<a7)&&(a2<a8))
#define min3 ((a3<a1)&&(a3<a2)&&(a3<a4)&&(a3<a5)&&(a3<a6)&&(a3<a7)&&(a3<a8))
#define min4 ((a4<a1)&&(a4<a2)&&(a4<a3)&&(a4<a5)&&(a4<a6)&&(a4<a7)&&(a4<a8))
#define min5 ((a5<a1)&&(a5<a2)&&(a5<a3)&&(a5<a4)&&(a5<a6)&&(a5<a7)&&(a5<a8))
#define min6 ((a6<a1)&&(a6<a2)&&(a6<a3)&&(a6<a4)&&(a6<a5)&&(a6<a7)&&(a6<a8))
#define min7 ((a7<a1)&&(a7<a2)&&(a7<a3)&&(a7<a4)&&(a7<a5)&&(a7<a6)&&(a7<a8))
#define min8 ((a8<a1)&&(a8<a2)&&(a8<a3)&&(a8<a4)&&(a8<a5)&&(a8<a6)&&(a8<a7))

///////////////////////////////////////////////////////函数定义
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
void start(void);
void run(unsigned a,unsigned b);
void cruise_50(void);
void cruise_2(void);
void alter_v_50(unsigned a, unsigned b, unsigned c);
void alter_v_2(unsigned a, unsigned b, unsigned c);
void alter_v(unsigned a, unsigned b, unsigned c);
void alter_v_dt(unsigned a, unsigned b, unsigned c);
void alter_v_right(unsigned a,unsigned b,unsigned c);
void alter_v_left(unsigned a,unsigned b,unsigned c);
void pass_bridge(void);
void cruise_max(void);
void cruise_circle1(void);
void cruise_circle2(void);

void check_a1(void);
void check_a8(void);
void check_a18(void);
void check_a17(void);
void rec2(void);
void rec3(void);
void rec4(void);
void rec5(void);
void rec6(void);

void znz(int a);
void zhuan(unsigned a);
void right(unsigned a);
void right_90(void);
void left(unsigned a);
void left_90(void);

void zhuan_p1(void);
void zhuan_p2(void);
void zhuan_p3(void);
void zhuan_p4(void);
void zhuan_p5(void);
void zhuan_p6(void);
void zhuan_p7(void);
void zhuan_p8(void);

void start_servo(void);
void p_servo(void);
void bao_servo(void);


///////////////////////////////////////////////////////基础自定义函数
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
void start(void){
  while(digital(2)==1){stop();msleep(15);}
  while(digital(2)==0){stop();msleep(15);}
}
void run(unsigned a,unsigned b){
    ar=b+135*b/3000;
	motor(2,a);motor(1,ar);
}
void cruise_50(void){//偏的高速寻线 
	 
	    float c=0.97;	
	 	float aa1=a1;
	 	float aa2=a2;
	 	float aa3=a3;
	 	float aa4=a4;
	 	float aa5=a5;
	 	float aa6=a6;
	 	float aa7=a7;
		float aa8=a8;
	 	
  if(v<5.1)	 
  {
  	if(maxa5)
   {
   	   if((a4>a)||(aa4<a4)) {run(c*v*10,10*v);/*motor(2,c*v*10);motor(1,10*v);*/}
   	   else {run(c*v*9.8,10*v);/*motor(2,c*v*9.8);motor(1,10*v);*/}   	   
   }
   else if(maxa4)
   {
   	   if((a5>a)||(aa5<a5)) {run(c*v*10,10*v);/*motor(2,c*v*10);motor(1,10*v);*/}
   	   else { run(c*v*10,9.8*v);/*motor(2,c*v*10);motor(1,9.8*v);*/}   	   
   }
   else if(maxa3)
   {
   	   if(aa4<a4) {run(c*v*10,10*v);/*motor(2,c*v*10);motor(1,10*v);*/}
   	   else {run(c*v*10,8*v);/*motor(2,c*v*10);motor(1,8*v);*/}   	   
   }  
    else if(maxa6)
   {
   	   if(aa5<a5) {run(c*v*10,10*v);/*motor(2,c*v*10);motor(1,10*v);*/}
   	   else {run(c*v*8,10*v);/*motor(2,c*v*8);motor(1,10*v);*/}   	   
   }  
     else if(maxa2)
   {
   	   if(aa3<a3) {run(c*v*10,10*v);/*motor(2,c*v*10);motor(1,10*v);*/}
   	   else {run(c*v*9,58/10*v);/*motor(2,c*v*9);motor(1,7*v);*/}   	   
   }  
     else if(maxa7)
   {
   	   if(aa6<a6) {run(c*v*10,10*v);/*motor(2,c*v*10);motor(1,10*v);*/}
   	   else {run(c*v*58/10,9*v);/*motor(2,c*v*7);motor(1,9*v);*/}   	   
   }  
     else if(maxa8)
   {
   	   if(aa7<a7) {run(c*v*10,10*v);/*motor(2,c*v*10);motor(1,10*v);*/}
   	   else {run(c*v*28/10,6*v);/*motor(2,c*v*4);motor(1,6*v);*/}   	   
   }  
      else if(maxa1)
   {
   	   if(aa2<a2) {run(c*v*10,10*v);/*motor(2,c*v*10);motor(1,10*v);*/}
   	   else {run(c*v*6,28/10*v);/*motor(2,c*v*6);motor(1,4*v);*/}   	   
   }  
      else 
   {
   	   run(c*v*6,6*v);/*motor(2,c*v*6);motor(1,6*v);*/	   
   } 
  }	
   else 
   {
   	   
   	if(maxa5)
   {
   	   if((a4>a)||(aa4<a4)) {run(c*v*10,10*v);/*motor(2,c*v*10);motor(1,10*v);*/}
   	   else {run(c*v*9.8,10*v);/*motor(2,c*v*9.8);motor(1,10*v);*/}   	   
   }
   else if(maxa4)
   {
   	   if((a5>a)||(aa5<a5)) {run(c*v*10,10*v);/*motor(2,c*v*10);motor(1,10*v);*/}
   	   else {run(c*v*10,9.8*v);/*motor(2,c*v*10);motor(1,9.8*v);*/}   	   
   }
   else if(maxa3)
   {
   	   if(aa4<a4) {run(c*v*10,10*v);/*motor(2,c*v*10);motor(1,10*v);*/}
   	   else {run(c*v*10,9*v);/*motor(2,c*v*10);motor(1,9*v);*/}   	   
   }  
    else if(maxa6)
   {
   	   if(aa5<a5) {run(c*v*10,10*v);/*motor(2,c*v*10);motor(1,10*v);*/}
   	   else {run(c*v*9,10*v);/*motor(2,c*v*9);motor(1,10*v);*/}   	   
   }  
     else if(maxa2)
   {
   	   if(aa3<a3) {run(c*v*10,10*v);/*motor(2,c*v*10);motor(1,10*v);*/}
   	   else {run(c*v*9,7*v);/*motor(2,c*v*9);motor(1,7*v);*/}   	   
   }  
     else if(maxa7)
   {
   	   if(aa6<a6) {run(c*v*10,10*v);/*motor(2,c*v*10);motor(1,10*v);*/}
   	   else {run(c*v*7,9*v);/*motor(2,c*v*7);motor(1,9*v);*/}   	   
   }  
     else if(maxa8)
   {
   	   if(aa7<a7) {run(c*v*10,10*v);/*motor(2,c*v*10);motor(1,10*v);*/}
   	   else {run(c*v*4,6*v);/*motor(2,c*v*4);motor(1,6*v);*/}   	   
   }  
      else if(maxa1)
   {
   	   if(aa2<a2) {run(c*v*10,10*v);/*motor(2,c*v*10);motor(1,10*v);*/}
   	   else {run(c*v*6,4*v);/*motor(2,c*v*6);motor(1,4*v);*/}   	   
   }  
      else 
   {
   	  run(c*v*6,6*v); /*motor(2,c*v*6);motor(1,6*v);*/	   
   } 
   }
}
void alter_v_50(unsigned a, unsigned b, unsigned c){//线性高速变速寻线系统-2（v值改变）
	reset_system_time( );t=0;
	v0=a;
	v1=b;
	a_t=c;
	while(1){
		t=mseconds();
		if(t>a_t){break;}
		else{
			a_v=(v1-v0)*t/a_t;
			v=v0+a_v;
			cruise_50();
		}
	}
}
void cruise_2(void){///////常规寻线{
	if((a4>a)&&(a5>a)){run(10*v,10*v);}
	else if(a4>a){run(10*v,9*v);}
	else if(a5>a){run(9*v,10*v);}
	else if(a3>a){run(10*v,7*v);}
	else if(a6>a){run(7*v,10*v);}
	else if(a2>a){run(10*v,6*v);}
	else if(a7>a){run(6*v,10*v);}
	else if(a1>a){run(10*v,5*v);}
	else if(a8>a){run(5*v,10*v);}
	else {run(10*v,10*v);}
}
  alter_v_50(2,7,588);
  alter_v_50(7,7,q);
  alter_v_50(7,2,386);
}
	m=a;
	reset_system_time();t=0;
	while(t<b){
		t=mseconds();
		if(maxa4){run(10*m,0*m);}
		else if(maxa5){run(0*m,10*m);}
		else if(maxa3){run(10*m,-5*m);}
		else if(maxa6){run(-5*m,10*m);}
		else if(maxa2){run(10*m,-8*m);}
		else if(maxa7){run(-8*m,10*m);}
		else if(maxa1){run(10*m,-10*m);}
		else if(maxa8){run(-10*m,10*m);}
		else {run(10*m,10*m);}
	}
}
void cruise_max(void){
            if(maxa5||maxa4) run(10*v,10*v);
            else if(maxa3)run(8*v,6*v); 
            else if(maxa2||maxa1)run(8*v,5*v);  
            else if(maxa6)run(6*v,8*v);  
            else if(maxa7||maxa8)run(5*v,8*v);  
}
void cruise_circle1(void){////////////////////////////圆循线逆时针
            if(maxa5) run(5*v,10*v);//7
			else if(maxa4)run(80*v/11,7*v); 
            else if(maxa3)run(8*v,7*v); 
            else if(maxa2||maxa7)run(8*v,5*v);  
            else if(maxa6)run(4*v,10*v);  //6
            else if(maxa7||maxa8)run(1*v,10*v);  //3
}

            if(maxa5) run(10*v,7*v);
			else if(maxa4)run(7*v,80*v/11);
            else if(maxa3)run(10*v,4*v); 
            else if(maxa2||maxa1)run(10*v,3*v);  
            else if(maxa6)run(4*v,10*v);  
            else if(maxa7||maxa8)run(3*v,10*v);  
}

void znz(int a){                         //指南针
	int c=compass();
	while(1){
		if (c>a){motor(1,10); motor(2,-10*0.96);msleep(20);}
		else if(c<a) {motor(1,-10);motor(2,10*0.96); msleep(20);}
		else {break;}
		c=compass();}
 }
void start_servo(void){//3身体（直0，躺800）;4右手（放下500,800抬起）；5左手（放下500，200抬起)
                    //6头（500正，300右转）
	 stop();msleep(300);
     servo(3,400); msleep(300);
	 servo(6,200); msleep(150); 
     servo(6,800);msleep(300);
	 servo(6,200); msleep(300); 
     servo(6,800);msleep(300);
     servo(6,500); msleep(150); 
     servo(3,800);msleep(300);
     stop();msleep(300);
 }
void p_servo(void){
	 stop();msleep(300);
     servo(3,400); msleep(300);
	 servo(4,900); msleep(150); 
     servo(4,500);msleep(300);
	 servo(5,100); msleep(150); 
     servo(5,500);msleep(300); 
     servo(3,800);msleep(300);
     stop();msleep(300);
 }
void bao_servo(void){
	 stop();msleep(300);
     servo(3,400); msleep(300);
	  reset_system_time();
     t=0;
    while(t<300)
    {
	  t=mseconds();
	  servo(4,900); servo(5,100);//同时举手
     }
    reset_system_time();
	 t=0;
    while(t<300)
   {
	t=mseconds();
	servo(4,500);servo(5,500);//同时放下
   }
     servo(3,800);msleep(300);
     stop();msleep(300);
 }

///////////////////////////////////////////////////////
void zhuan_p1(void){
	zhuan(1588);
	znz(124);
}
void zhuan_p2(void){
	alter_v(0,2,200);
	alter_v(2,0,200);
	p_servo();
	zhuan(1588);
	znz(334);
}
void zhuan_p3(void){
	alter_v(0,2,200);
	alter_v(2,0,200);
	p_servo();
	zhuan(1588);
	znz(334);
}
void zhuan_p4(void){
	alter_v(0,2,200);
	alter_v(2,0,200);
	p_servo();
	zhuan(1588);
	znz(178);
}
void zhuan_p5(void){
	alter_v(0,2,200);
	alter_v(2,0,200);
	p_servo();
	zhuan(1588);
	znz(176);
}
void zhuan_p6(void){
	alter_v(0,2,200);
	alter_v(2,0,200);
	p_servo();
	zhuan(1588);
	znz(244);
}
void zhuan_p7(void){
	alter_v(0,2,200);
	alter_v(2,0,200);
	alter_v_dt(0,2,200);
	alter_v_dt(2,0,200);
	p_servo();
	zhuan(1588);
	znz(186);
}
void zhuan_p8(void){
	alter_v(0,2,200);
	alter_v(2,0,200);
	alter_v_dt(0,2,200);
	alter_v_dt(2,0,200);
    p_servo();
	zhuan(1588);
	znz(346);
}
///////////////////////////////////////////////////////猪函数
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
void mainX1(void){
   pdown();
	gaogao(166);
	check_a1();
	stop();sleep(3);
	alter_v(2,2,1100);
    pass_bridge();
	alter_v(3,2,100);
	alter_v(2,2,1100);
	gaogao(211);
	check_a1();
	pup();
	zhuan_p1();
   stop();
}
void mainX2(void){
   test();
}
void mainX3(void){
 
   p7_m3();
   m3_straight();
   m3_p8();
   ws;
}
void mainX4(void){
 
}
void mainX5(void){
    start();
  start_servo();
  p1_p2();
  rec2();
   ws;
}

void mainX6(void){
  
}
void mainX7(void){
  
}

	
void mainX(void *p_arg) {

  servo(3, 800);	
  servo(4, 500);
  servo(5, 500);
  servo(6, 500);     
  set_name(MAINX1,"main1");
  set_name(MAINX2,"test");
  set_name(MAINX3,"main3");
  set_name(MAINX4,"main4");
  set_name(MAINX5,"main5");
  // .... x7
   
  select_main();
}
