/**************************************************************************
 Doc Snyders R2D2 232 Controller
 Display I2C 128x32
 **************************************************************************/


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>   //Einfügen der EEPROM Bibliothek

#include "inputdef.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include "count.h"
#include "func.h"
#include "dosetup.h"
//R2D2 Moving; ///Classe Starten

#include "display.h"

long position  = -999;
int tmpPos = 0;


//#include "func.h"

void setup() {
  
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  // Clear the buffer
  display.clearDisplay();
 
  
  pinMode(CENTUP, INPUT);
  pinMode(CENTDOWN, INPUT);

  pinMode(CENTLOCK, OUTPUT);
  pinMode(LEGSENS, INPUT);
  //pinMode(LEGLOOK, INPUT);

  //pinMode(PROG, INPUT);
 //Selector
 // pinMode (outputA,INPUT_PULLUP);
 // pinMode (outputB,INPUT_PULLUP);
  pinMode(TRIG, INPUT_PULLUP);
  pinMode(RC_TRIG, INPUT_PULLUP);

  pinMode(GSM1, OUTPUT);    
  pinMode(GSM2, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  //bargraph();
  

  loadDefault();
  //bargraph();
  //delay(8000);
  showMode();
}

void checkMode(){
  
  
  if (counter > 8){counter = 0;}
  if (counter < 0){counter = 8;}
  
  if (counter != MODE){  
    MODE = counter;
    showMode();
  }
  getCounter();
}  

void loop() {
  

    if (SETUP == 0) {
       checkpos();
       
        int select = digitalRead(TRIG);
        if ( select == 0 ){
            Start = false;
            delay(500);
        }

        
        if (Start){
          showMode();
        } else {
          
          checkMode();
          doMove();
        }    
        
        
 
    } else {
        doSetup();
    }
    
 if (ACTIV)
 {
  move2to3();
 }
  

  
}
