#include <Arduino.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define HEIGHT   24  
#define WIDTH    24

int POSITION = 0 ;  // 0=undefiniert | 1=twoleg | 2=move | 3=lookdown 
int MODE = 0; // 0 = Start | 1 = CenterUp | 2 = CenterDown | 3 = LegCenter | 4 = LegMove | 5 = MotorTest | 6 = Look Down

int ACTIV = 0;  // 0 = Position eingenommen // 1 = In Transit
int SETUP = 0;  // 0 = Normal // 1 = Setup
int SETTING = 0; /// Ping for Setting
int NVALUE = 0;

int CENTUP = 14;
int CENTDOWN = 15; 

//int LEGMOVE = 16; //RELAIS
int CENTLOCK = 16;

//int LEGCENTER = 17; ////POTI
int LEGSENS = 17;


/// POSITIONS BESTIMMUNG POTI LEGS

int SLEGMOVE = 440;
int SLEGCENT = 400;
int SLEGLOOK = 339;

int SR = 5;  //Sensor Range

int CMOTPWR = 255 ;  // Motorpower 255 Max
int LMOTPWR = 150 ;  // Motorpower 255 Max

String SensorArray[6]={"SLEGMOVE", "SLEGCENT", "SLEGLOOK", "SR", "CMOTPWR", "LMOTPWR" };

int TRIG = 4;

///Rotation Sensor

#define outputA 12
#define outputB 11

int counter = 0; 
int aState;
int aLastState; 

////
// Gleichstrommotor 1

int GSM1 = 10;
int in1 = 9;
int in2 = 8;

// Gleichstrommotor 1

int GSM2 = 5;
int in3 = 7;
int in4 = 6;

// BOOST RELAIS

int BOOST = 3;
int BTIME = 20;
//EEPROMSPEICHER
//String SensorArray[6]={"SLEGMOVE", "SLEGCENT", "SLEGLOOK", "SR", "CMOTPWR", "LMOTPWR" };

int adr0=103; //SLEGMOVE
int adr1=105; //SLEGCENT
int adr2=107; //SLEGLOOK
int adr3=109; //SR
int adr4=111; //CMOTPWR
int adr5=113; //LMOTPWR
int adr12=115; //BTIME

int k;



int debug = false;
