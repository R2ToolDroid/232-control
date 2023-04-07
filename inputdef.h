#include <Arduino.h>

//#define HEIGHT   24  
//#define WIDTH    24

// VARS:
// Byte    0-255

String data = "";

int counter = 8; 
byte POSITION = 0 ;  // 0=undefiniert | 1=twoleg | 2=move | 3=lookdown 
byte MODE = 8; //
/*  0 Automatic | 
 *  1 CenterUp
 *  2 CenterDown
 *  3 LegCenter
 *  4 LegMove
 *  5 MotorTest
 *  6 Look Down
 *  7 Setup
 *  8 Start
 */ //1 = CenterUp | 2 = CenterDown | 3 = LegCenter | 4 = LegMove | 5 = MotorTest | 6 = Look Down




bool ACTIV = false;  // 0 = Position eingenommen // 1 = In Transit

bool SETUP = 0;  // 0 = Normal // 1 = Setup
bool SETTING = 0; /// Ping for Setting
int NVALUE = 0;

#define CENTUP  14    // Sensor Oben
#define CENTDOWN  15  //Sensor Untern
#define CENTLOCK  16  //Relais für Lock
#define LEGSENS  17

int T_LEGSENS;
bool T_CENTUP;
bool T_CENTDOWN;

#define READ_LEGSENS map(analogRead(LEGSENS), 1023 ,0 , 100, 0)
#define READ_CENTUP digitalRead(CENTUP)
#define READ_CENTDOWN digitalRead(CENTDOWN)

/// POSITIONS BESTIMMUNG POTI LEGS

byte SLEGMOVE = 85;    //28
byte SLEGCENT = 50;    //24
byte SLEGLOOK = 35;     //20

byte SR = 5;  //Sensor Range

bool REFRESH = false;

byte CMOTPWR = 200 ;  // Motorpower 255 Max

unsigned long maxCentTime = 4000;

unsigned long ShakeTime = 100;


byte LMOTPWR_B = 255 ;  // Motorpower 255 Max
byte LMOTPWR_F = 255 ;  // Motorpower 255 Max
byte LMOTPWR = 0;

///Sensor Array für Display Input
String SensorArray[13]={
  "SLEGMOVE", 
  "SLEGCENT", 
  "SLEGLOOK", 
  "SR", 
  "CMOTPWR",
  "LMOTPWR_B",
  "LMOTPWR_F" ,
  "8" ,
  "9" ,
  "10" ,
  "11" ,
  "12", 
  "13" 
  };

#define TRIG  4

bool trig = 1;

bool lauf = 0;


//int aState;
//int aLastState; 
//int check;

////
// Gleichstrommotor 1
#define GSM1 10
#define in1 9
#define in2 8
 
//int GSM1 = 10;
//int in1 = 9;
//int in2 = 8;

// Gleichstrommotor 1

#define GSM2 5
#define in3 7
#define in4 6

//int GSM2 = 5;
//int in3 = 7;
//int in4 = 6;


//EEPROMSPEICHER
//String SensorArray[6]={"SLEGMOVE", "SLEGCENT", "SLEGLOOK", "SR", "CMOTPWR", "LMOTPWR" };

#define adr0 103 //SLEGMOVE
#define adr1 105 //SLEGCENT
#define adr2 107 //SLEGLOOK
#define adr3 109 //SR
#define adr4 111 //CMOTPWR
#define adr5 113 //LMOTPWR_B
#define adr6 115 //LMOTPWR_F

/*
int adr0=103; //SLEGMOVE
int adr1=105; //SLEGCENT
int adr2=107; //SLEGLOOK
int adr3=109; //SR
int adr4=111; //CMOTPWR
int adr5=113; //LMOTPWR_B
int adr6=115; //LMOTPWR_F
//int adr12=115; //BTIME
*/

int k;



bool debug = false;
