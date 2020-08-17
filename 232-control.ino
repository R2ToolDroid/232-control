/**************************************************************************
 Doc Snyders R2D2 232 Controller
 Display I2C 128x32
 **************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>   //Einfügen der EEPROM Bibliothek
#include "232.h"
#include "inputdef.h"




// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include "func.h"
#include "dosetup.h"

//R2D2 Moving; ///Classe Starten


void setup() {
  Serial.begin(9600);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  inputString.reserve(200);
  // Clear the buffer
  display.clearDisplay();
  
  pinMode(CENTUP, INPUT);
  pinMode(CENTDOWN, INPUT);

  pinMode(CENTLOCK, OUTPUT);
  pinMode(LEGSENS, INPUT);
  //pinMode(LEGLOOK, INPUT);

  //pinMode(PROG, INPUT);
 //Selector
  pinMode (outputA,INPUT_PULLUP);
  pinMode (outputB,INPUT_PULLUP);
  pinMode(TRIG, INPUT_PULLUP);
 


  pinMode(GSM1, OUTPUT);    
  pinMode(GSM2, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(BOOST, OUTPUT);
  digitalWrite(BOOST, HIGH);
  //bargraph();
  loadDefault();
 
  
}



void loop() {

 if (SETUP == 0) {
 checkpos();
 ceckMode();
 showMode();
 
 } else {
  doSetup();
 }
 
 doMove();

 if (ACTIV == 1)
 {
  move2to3();
 }
  //digitalWrite(BOOST, LOW);

if (stringComplete) {
    Serial.println(inputString);

    if (inputString == "A0\n") {ACTIV = 0;}
    if (inputString == "A1\n") {ACTIV = 1;}
    //if (inputString == "T1") {trig = 1;}
    //if (inputString == "T0") {trig = 0;}
    
    // clear the string:
    inputString = "";
    stringComplete = false;
    Serial.print( "Active = ");
    Serial.print (ACTIV);
    Serial.print( "MODE = ");
    Serial.print (MODE);
  }
 
 
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
