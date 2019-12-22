#include <Arduino.h>


void eepromWriteInt(int adr, int wert) {
// 2 Byte Integer Zahl im EEPROM ablegen an der Adresse
// Eingabe: 
//   adr: Adresse +0 und +1 wird geschrieben
//   wert: möglicher Wertebereich -32,768 bis 32,767
// Ausgabe: 
//   -
// 2 Byte Platz werden belegt.
//
// Matthias Busse 5.2014 V 1.0

byte low, high;

  low=wert&0xFF;
  high=(wert>>8)&0xFF;
  EEPROM.write(adr, low); // dauert 3,3ms 
  EEPROM.write(adr+1, high);
  return;
} //eepromWriteInt

int eepromReadInt(int adr) {
// 2 Byte Integer Zahl aus dem EEPROM lesen an der Adresse
// Eingabe: 
//   adr: Adresse +0 und +1 wird gelesen
// Ausgabe: int Wert
//
// Matthias Busse 5.2014 V 1.0

byte low, high;

  low=EEPROM.read(adr);
  high=EEPROM.read(adr+1);
  return low + ((high << 8)&0xFF00);
} //eepromReadInt



void doInput(int VAR, int VALUE ){

    delay(500);

    NVALUE = 0;
    
    while (SETTING == 1 )  
    {

     int trig = digitalRead(TRIG);  
     
     getCounter();

    display.clearDisplay();
    display.setTextSize(1);      // Normal 1:1 pixel scale
    display.setTextColor(WHITE); // Draw white text
    display.setCursor(0, 0);     // Start at top-left corner
    display.println("------ INPUT ------");

    display.print("SET: " );
    display.print(SensorArray[VAR]);
    display.print("= ");
    display.println(VALUE);
    NVALUE= VALUE+counter;
    display.print(NVALUE);
    
    
    display.display();
    

    if (trig == 0) {
      
      switch (VAR) {
        case 0:
        SLEGMOVE = NVALUE;        
        SETTING = 0;SETUP = 0;counter = 0;
        break;    
        case 1:
        SLEGCENT = NVALUE;        
        SETTING = 0;SETUP = 0;counter = 0;
        break; 
        case 2:
        SLEGLOOK = NVALUE;        
        SETTING = 0;SETUP = 0;counter = 0;
        break; 
        case 3:
        SR = NVALUE;        
        SETTING = 0;SETUP = 0;counter = 0;
        break; 
        case 4:
        CMOTPWR = NVALUE;        
        SETTING = 0;SETUP = 0;counter = 0;
        break; 
        case 5:
        LMOTPWR = NVALUE;        
        SETTING = 0;SETUP = 0;counter = 0;
        break; 
              
        default:
    // if nothing else matches, do the default
    // default is optional
        SETTING = 0;SETUP = 0;counter = 0;
    
        break;
      } //end switch
      
      } //end tirg


    
    } // edn while
    //delay(2000);


    
  
}


void SaveAlltoRom(){

  k=SLEGMOVE;
  eepromWriteInt(adr0,k);  
  Serial.println(eepromReadInt(adr0)); 

  k=SLEGCENT;
  eepromWriteInt(adr1,k);  
  Serial.println(eepromReadInt(adr1)); 

  k=SLEGLOOK;
  eepromWriteInt(adr2,k);  
  Serial.println(eepromReadInt(adr2)); 

  k=SR;
  eepromWriteInt(adr3,k);  
  Serial.println(eepromReadInt(adr3)); 

  k=CMOTPWR;
  eepromWriteInt(adr4,k);  
  Serial.println(eepromReadInt(adr4)); 

  k=LMOTPWR;
  eepromWriteInt(adr5,k);  
  Serial.println(eepromReadInt(adr5)); 
  delay(1000);
  bargraph();
        
/*
int SLEGMOVE = 440;
int SLEGCENT = 400;
int SLEGLOOK = 339;

int SR = 5;  //Sensor Range

int CMOTPWR = 255 ;  // Motorpower 255 Max
int LMOTPWR = 150 ;  // Motorpower 255 Max

*/

  
}



void doSetup(){

    getCounter();

    display.clearDisplay();
    display.setTextSize(1);      // Normal 1:1 pixel scale
    display.setTextColor(WHITE); // Draw white text
    display.setCursor(0, 0);     // Start at top-left corner
    display.println("------- SETUP ------");

    display.print("SET : ");
    /// POSITIONS BESTIMMUNG POTI LEGS

///int SLEGMOVE = 440;
///int SLEGCENT = 400;
///int SLEGLOOK = 339;

    switch (counter) {
  case 1:
   
    display.print("SLEGMOVE= ");
    display.print(SLEGMOVE);
    break;
  case 2:
   
    display.print("SLEGCENT= ");
    display.print(SLEGCENT);
    
    break;

   case 3:
   
    display.print("SLEGLOOK= ");
    display.print(SLEGLOOK);
    
    break;

   case 4:
   
    display.print("SR=         ");
    display.print(SR);
    
    break;
    
   case 5:
   
    display.print("CMOTPWR=  ");
    display.print(CMOTPWR);
    
    break;

   case 6:
   
    display.print("LMOTPWR=   ");
    display.print(LMOTPWR);
    
    break;
    
    case 7:
    display.print("-SELECT-");
    break; 


   case 9:
    display.print("-SAVE ALL-");
    break;

   case 8:
    display.print("EXIT");
    break;

   case 10:
    display.print("-Debug on-");
    break;

    case 11:
    display.print("-Debug off-");
    break;

    
  default:
    // if nothing else matches, do the default
    // default is optional
    
    
    break;
}
 int trig = digitalRead(TRIG);

    display.setCursor(0, 20); 
    display.print(NVALUE);
    display.setCursor(110, 20); 
    display.print(counter);
    display.display();


     //delay (2000);
   
    if (trig == 0) {

        if (counter == 1) {doInput(0,SLEGMOVE);SETTING = 1;}
        if (counter == 2) {doInput(1,SLEGCENT);SETTING = 1;}
        if (counter == 3) {doInput(2,SLEGLOOK);SETTING = 1;}
        if (counter == 4) {doInput(3,SR);SETTING = 1;}
        if (counter == 5) {doInput(4,CMOTPWR);SETTING = 1;}
        if (counter == 6) {doInput(5,LMOTPWR);SETTING = 1;}
        if (counter == 9) {SaveAlltoRom();SETTING = 1;}
                
        if (counter == 8) {SETUP = 0;}
        if (counter == 10) {debug = true;SETTING = 1;}
        if (counter == 11) {debug = false;SETTING = 1;}

      
    }

  
}

void loadDefault(){

    SLEGMOVE = eepromReadInt(adr0);
    if (SLEGMOVE < 1) {SLEGMOVE = 440;}
    
    SLEGCENT = eepromReadInt(adr1);
    if (SLEGCENT < 1) {SLEGCENT = 400;}

    SLEGLOOK = eepromReadInt(adr2);
    if (SLEGLOOK < 1) {SLEGLOOK = 340;}

    SR = eepromReadInt(adr3);
    if (SR < 1) {SR = 5;}

    CMOTPWR = eepromReadInt(adr4);
    if (CMOTPWR < 1) {CMOTPWR = 255;}

    LMOTPWR = eepromReadInt(adr5);
    if (LMOTPWR < 1) {LMOTPWR = 150;}   

}
