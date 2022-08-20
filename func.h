#include <Arduino.h>

// Check in Range inRange(x, 0, 200)
bool inRange(byte val, byte minimum, byte maximum)
{
  return ((minimum <= val) && (val <= maximum));
}



void showRun(){
    display.clearDisplay();
    display.setTextSize(2);      // Normal 1:1 pixel scale
    display.setTextColor(WHITE); // Draw white text
    display.setCursor(0, 0);     // Start at top-left corner
    //int legsens = analogRead(LEGSENS);
    int TARGET;
    if (MODE == 0){ display.print("RUN       ");}
    if (MODE == 1){ display.print("CentUp   ");}
    if (MODE == 2){ display.print("CentDown ");}
    if (MODE == 3){ display.print("LegCent  ");TARGET = SLEGCENT;}
    if (MODE == 4){ display.print("LegMove  ");TARGET = SLEGMOVE;}
    if (MODE == 5){ display.print("Look     ");TARGET = SLEGLOOK;}
    //if (MODE == 6){ display.print("Test MOT ");}

    display.setTextSize(1);
    display.setCursor(0, 16);     // Start at top-left corner
    display.print("LSens: ");
    display.print(READ_LEGSENS);
    display.print(" -> ");
    display.print(TARGET);
    display.setCursor(0, 25);     // Start at top-left corner
    display.print("SEN: ");

    if (READ_CENTUP == 1) {display.print ("UP 1");}
    else {display.print ("UP 0");}
    if (READ_CENTDOWN == 1) {display.print (" DW 1");}
    else {display.print (" DW 0");}
        
    display.display();
}


void bargraph(void) {
  //display.clearDisplay();

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.setCursor(0, 5);     // Start at top-left corner
  //display.cp437(true);
  
  
  for(int16_t i=0; i<= 100; i++) {
    display.clearDisplay();
    
    display.drawRect(10,10,108,10,1);
    
    display.print("%");
    // The INVERSE color is used so rectangles alternate white/black
    display.fillRect(14, 12, i, 6, 1);
    display.print(i);
    display.setCursor(55, 25);
    display.display(); // Update screen with each newly-drawn rectangle
    delay(1);
  }

  delay(100);
  display.clearDisplay();
  counter = 0;
}

void centerUp(){

     showRun();

     int centup = READ_CENTUP;

          
     digitalWrite(CENTLOCK,HIGH);
     
     delay(1000); 

    while (centup == 1) {

      showRun();
      centup = READ_CENTUP;
      digitalWrite(in1, LOW);  // Motor 1 beginnt zu rotieren
      digitalWrite(in2, HIGH);
      analogWrite(GSM1, CMOTPWR);   // Motor 1 soll mit der Geschwindigkeit "200" (max. 255) rotieren
      Serial.println("Center UP");
      
      
    }
      digitalWrite(in1, LOW);   // Anschließend sollen die Motoren 2 Sekunden ruhen.
      digitalWrite(in2, LOW);
      digitalWrite(CENTLOCK,LOW);

      ACTIV = false;
      counter = 0;
}


void centerDown(){

      int centdown = READ_CENTDOWN;

      //showRun();

    while (centdown == 1) {
      
      showRun();
      
      centdown = READ_CENTDOWN;
      digitalWrite(in1, HIGH);  // Motor 1 beginnt zu rotieren
      digitalWrite(in2, LOW);
      analogWrite(GSM1, CMOTPWR);   // Motor 1 soll mit der Geschwindigkeit "200" (max. 255) rotieren
      Serial.println("Center Down");
      
    }
      digitalWrite(in1, LOW);   // Anschließend sollen die Motoren 2 Sekunden ruhen.
      digitalWrite(in2, LOW);
      
}

void LegCenter(){
  
     
      int lauf = 1;
     
       // 0=undefiniert | 1=twoleg | 2=move | 3=lookdown

    while (lauf == 1) {

       showRun();
 
      if ((READ_LEGSENS > SLEGCENT-SR) &&( READ_LEGSENS < SLEGCENT+SR)) { lauf = 0;} else { lauf = 1;}

      if (READ_LEGSENS < SLEGCENT ){
      digitalWrite(in3, HIGH);  // Motor 1 beginnt zu rotieren
      digitalWrite(in4, LOW);
      LMOTPWR = LMOTPWR_B;
      Serial.println("Leg rechtsrum");
      } else {
        digitalWrite(in3, LOW);  // Motor 1 beginnt zu rotieren
        digitalWrite(in4, HIGH);
        LMOTPWR = LMOTPWR_F;
        Serial.println("Leg linksrum");
      }
      analogWrite(GSM2, LMOTPWR );   // Motor 1 soll mit der Geschwindigkeit "200" (max. 255) rotieren
      //Serial.println("Leg Center");

      

      
    }
      digitalWrite(in3, LOW);   // Anschließend sollen die Motoren 2 Sekunden ruhen.
      digitalWrite(in4, LOW);
      //digitalWrite(BOOST, HIGH);
      ACTIV = false;
      counter = 0;
}

void LegMove(){

       
       int lauf = 1;
       

    while (lauf == 1) {

      showRun();

      // 0=undefiniert | 1=twoleg | 2=move | 03=lookdown
      if ((READ_LEGSENS > SLEGMOVE-SR )&&( READ_LEGSENS < SLEGMOVE+SR)) { lauf = 0;}  else { lauf = 1;}
      digitalWrite(in3, LOW);  // Motor 2 beginnt zu rotieren
      digitalWrite(in4, HIGH);
      Serial.println("Leg linksrum");
      analogWrite(GSM2, LMOTPWR_F);   // Motor 1 soll mit der Geschwindigkeit "200" (max. 255) rotieren
      //Serial.println("Leg Move");
  
      
      
    }
      digitalWrite(in3, LOW);   // Anschließend sollen die Motoren 2 Sekunden ruhen.
      digitalWrite(in4, LOW);
      ACTIV = false;
      counter = 0;
}

void Look(){

       //int READ_LEGSENS = map(analogRead(LEGSENS), 1023 ,0 , 200, 0);
       int lauf = 1;
       
    while ( lauf == 1) {

      showRun();
      //legsens = READ_LEGSENS;
      if ((READ_LEGSENS > SLEGLOOK-SR)&&( READ_LEGSENS < SLEGLOOK+SR)) { lauf = 0;} else { lauf = 1;}
      digitalWrite(in3, HIGH);  // Motor 1 beginnt zu rotieren
      digitalWrite(in4, LOW);
      analogWrite(GSM2, LMOTPWR_F);   // Motor 1 soll mit der Geschwindigkeit "200" (max. 255) rotieren      
      
    }
      digitalWrite(in3, LOW);   // Anschließend sollen die Motoren 2 Sekunden ruhen.
      digitalWrite(in4, LOW);
      ACTIV = false;
      counter = 0;
}






void move2to3() {

     

      // 0=undefiniert | 1=twoleg | 2=move | 03=lookdown
    if (POSITION == 1)
    {
      centerDown();
      delay(500);
      LegMove();
    }

    if (POSITION == 2)
    {
      LegCenter();
      delay(1000);
      centerUp();
    }

    if (POSITION == 3)
    {
      LegCenter();
    }

    if (POSITION == 0)
    {
      LegCenter();
    }



}



void doMove() {

    trig = digitalRead(TRIG);


  if (( trig == 0 ) || ( rc_trig >= 1200 )) {

   if (MODE == 0){ACTIV = true;}
   
   if (MODE == 1){centerUp();}
   if (MODE == 2){centerDown();}
   if (MODE == 3){LegCenter();}
   if (MODE == 4){LegMove();}
   if (MODE == 5){Look();}
   if (MODE == 6){CheckSens = true;}
   if (MODE == 7){SETUP = 1;}
   

  }// END trig


}
