/**************************************************************************
 Doc Snyders R2D2 232 Controller
 Display I2C 128x32
 **************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "232.h"
#include "inputdef.h"

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#include "func.h"

//R2D2 Moving; ///Classe Starten


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

  pinMode(PROG, INPUT);
  pinMode(TRIG, INPUT);

  pinMode(GSM1, OUTPUT);    
  pinMode(GSM2, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  //bargraph();
}



void loop() {

 checkpos();
 ceckMode();
 showMode();
 doMove();
 

 if (ACTIV == 1)
 {
  move2to3();
 }

 

 //Serial.print( "Active =");
 //Serial.println (ACTIV);
 
}
