#include <Arduino.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define HEIGHT   24  
#define WIDTH    24

int POSITION = 0 ;  // 0=undefiniert | 1=twoleg | 2=move | 3=lookdown 
int MODE = 0; // 0 = Start | 1 = CenterUp | 2 = CenterDown | 3 = LegCenter | 4 = LegMove | 5 = MotorTest | 6 = Look Down

int ACTIV = 0;  // 0 = Position eingenommen // 1 = In Transit

int CENTUP = 14;
int CENTDOWN = 15; 

//int LEGMOVE = 16; //RELAIS
int CENTLOCK = 16;

//int LEGCENTER = 17; ////POTI
int LEGSENS = 17;

int SCENTL = 290;
int SCENTH = 310;

int SMOVEL = 890;
int SMOVEH = 910;

int SLOOKL = 290;
int SLOOKH = 310;

/// center ca 400
/// move 900
/// lookdown 300

//int LEGLOOK = 3;

int PROG = 12; 
int TRIG = 4;

// Gleichstrommotor 1

int GSM1 = 10;
int in1 = 9;
int in2 = 8;

// Gleichstrommotor 1

int GSM2 = 5;
int in3 = 7;
int in4 = 6;


int debug = true;
