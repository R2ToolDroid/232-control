#include <Arduino.h>

void ceckMode(){
   
    int prog = digitalRead(PROG);
    if (MODE >= 7) {MODE = 0;}
    if (prog == 0) {MODE = MODE +1;delay(500); }   
  
}
   
void checkpos(){
          int centup = digitalRead(CENTUP);
          int centdown = digitalRead(CENTDOWN);
          int legsens = analogRead(LEGSENS);
          //int legcenter = digitalRead(LEGCENTER);
          //int leglook = digitalRead(LEGLOOK);

          // 0=undefiniert | 1=twoleg | 2=move | 3=lookdown 
          /// SLEGCENT ; SLEGMOVE ; SLEGLOOK;      
         
            if ((centup == 0)&&(legsens > SLEGCENT-SR ) && (legsens < SLEGCENT +SR)) {POSITION = 1;}      
            if ((centdown == 0)&& (legsens > SLEGMOVE ) ) {POSITION = 2;}          
            if ((centup == 0)&& (legsens <= SLEGLOOK )) {POSITION = 3;} 
            if ((centup == 0)&& (centdown == 0 )) {POSITION = 0;} 
            if ((centup == 1)&& (centdown == 1 )) {POSITION = 0;} 
            

            
            
            //if ((centdown == 1)&&( legmove == 1 ) &&( legcenter == 1 ) && (centup == 1) ) {POSITION = 0;} 
          //  if ((centdown == 0)&&( legmove == 0 ) &&( legcenter == 0 ) && (centup == 1) && (leglook == 1) ) {POSITION = 3;} 
          
                     
            if (debug) 
            {
            Serial.print("Status= ");
            Serial.print(POSITION);
            Serial.print(" - centup = ");
            Serial.print(centup);
 
            Serial.print(" | centdown = ");
            Serial.print(centdown);
            Serial.print(" | legsens = ");
            Serial.println(legsens);
            
            
            }
            
            
}///checkpos

void showMode(){
  
    display.clearDisplay();
    display.setTextSize(1);      // Normal 1:1 pixel scale
    display.setTextColor(WHITE); // Draw white text
    display.setCursor(0, 4);     // Start at top-left corner
    display.print("STATUS : ");
    display.print(POSITION);  // 0=undefiniert | 1=twoleg | 2=move | 3=lookdown 
    display.setCursor(0, 12);     // Start at top-left corner
    display.print("MODE : ");
    if (MODE == 0){ display.print("Automatic");}
    
    if (MODE == 1){ display.print("CentUp   ");}
    if (MODE == 2){ display.print("CentDown ");}
    if (MODE == 3){ display.print("LegCent  ");}
    if (MODE == 4){ display.print("LegMove  ");}
    if (MODE == 5){ display.print("LookDown  ");}
    if (MODE == 6){ display.print("Test MOT  ");}
    


    int centup = digitalRead(CENTUP);
    int centdown = digitalRead(CENTDOWN);
    //int legmove = digitalRead(LEGMOVE);
    int legsens = analogRead(LEGSENS);
    //int leglook = digitalRead(LEGLOOK);
    display.setCursor(0, 25);     // Start at top-left corner
    display.print("SEN: "); 

    if (centup == 1) {display.print ("|1  ");}
    else {display.print ("UP 0");}
    if (centdown == 1) {display.print (" |1 ");}
    else {display.print ("DW 0");}
    display.print ("-");  
    display.print (legsens); 
    display.print ("-");  
     
    if (POSITION == 0){display.drawBitmap(104,1,side_bmp, WIDTH, HEIGHT, 1);}
    if (POSITION == 1){display.drawBitmap(104,1,front_bmp, WIDTH, HEIGHT, 1);}
    if (POSITION == 2){display.drawBitmap(104,1,drive_bmp, WIDTH, HEIGHT, 1);}
    if (POSITION == 3){display.drawBitmap(104,1,look_bmp, WIDTH, HEIGHT, 1);}
    display.display();
    //delay(2000);  
  
}

void showRun(){
  
    display.clearDisplay();
    display.setTextSize(2);      // Normal 1:1 pixel scale
    display.setTextColor(WHITE); // Draw white text
    display.setCursor(8, 8);     // Start at top-left corner
    int legsens = analogRead(LEGSENS);
    
    if (MODE == 0){ display.print("RUN       ");}
    
    if (MODE == 1){ display.print("CentUp   ");}
    if (MODE == 2){ display.print("CentDown ");}
    if (MODE == 3){ display.print("LegCent  ");}
    if (MODE == 4){ display.print("LegMove  ");}
    if (MODE == 5){ display.print("Look     ");}
    if (MODE == 6){ display.print("Test MOT ");}

    display.setTextSize(1); 
    display.setCursor(20, 0);     // Start at top-left corner
    
    display.print("...wait for Sensor");     
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
       
    display.print("%"); 
    // The INVERSE color is used so rectangles alternate white/black
    display.fillRect(14, 10, i, 4, 1);
    display.print(i);
    display.setCursor(40, 18);
    display.display(); // Update screen with each newly-drawn rectangle
    delay(1);
    
  }
  
  delay(1000);
  display.clearDisplay();
}

void centerUp(){
  
     int centup = digitalRead(CENTUP);

     digitalWrite(CENTLOCK,HIGH);
     delay(1000);

     showRun();
     

    while (centup == 1) {
      centup = digitalRead(CENTUP);
      digitalWrite(in1, LOW);  // Motor 1 beginnt zu rotieren
      digitalWrite(in2, HIGH);  
      analogWrite(GSM1, CMOTPWR);   // Motor 1 soll mit der Geschwindigkeit "200" (max. 255) rotieren 
      Serial.println("Center UP");
      
    }
      digitalWrite(in1, LOW);   // Anschließend sollen die Motoren 2 Sekunden ruhen.
      digitalWrite(in2, LOW);  
       digitalWrite(CENTLOCK,LOW);

      ACTIV = 0;
  
}
  


void centerDown(){

      int centdown = digitalRead(CENTDOWN);

      showRun();

    while (centdown == 1) {
      centdown = digitalRead(CENTDOWN);
      digitalWrite(in1, HIGH);  // Motor 1 beginnt zu rotieren
      digitalWrite(in2, LOW);  
      analogWrite(GSM1, CMOTPWR);   // Motor 1 soll mit der Geschwindigkeit "200" (max. 255) rotieren 
      Serial.println("Center Down");
      
    }
      digitalWrite(in1, LOW);   // Anschließend sollen die Motoren 2 Sekunden ruhen.
      digitalWrite(in2, LOW);  
      
      
}

void LegCenter(){
      
      int legsens = analogRead(LEGSENS);
      int lauf = 1;
      showRun();
      
       // 0=undefiniert | 1=twoleg | 2=move | 3=lookdown     

    while (lauf == 1) {
     
      legsens = analogRead(LEGSENS);
      
      if ((legsens > SLEGCENT-SR) &&( legsens < SLEGCENT+SR)) { lauf = 0;} else { lauf = 1;}

      if (legsens > SLEGCENT ){
      digitalWrite(in3, HIGH);  // Motor 1 beginnt zu rotieren
      digitalWrite(in4, LOW);  

      Serial.println("Leg rechtsrum");
      } else {    
      
        digitalWrite(in3, LOW);  // Motor 1 beginnt zu rotieren
        digitalWrite(in4, HIGH);  
        Serial.println("Leg linksrum");
      }
      analogWrite(GSM2, LMOTPWR );   // Motor 1 soll mit der Geschwindigkeit "200" (max. 255) rotieren 
      //Serial.println("Leg Center");
    }
      digitalWrite(in3, LOW);   // Anschließend sollen die Motoren 2 Sekunden ruhen.
      digitalWrite(in4, LOW);  
      
      ACTIV = 0;
}

void LegMove(){

       int legsens = analogRead(LEGSENS);
       int lauf = 1;
       showRun();

    while (lauf == 1) {
      legsens = analogRead(LEGSENS);

      // 0=undefiniert | 1=twoleg | 2=move | 03=lookdown 
      
      if ((legsens > SLEGMOVE-SR )&&( legsens < SLEGMOVE+SR)) { lauf = 0;}  else { lauf = 1;}
      
      digitalWrite(in3, LOW);  // Motor 2 beginnt zu rotieren
      digitalWrite(in4, HIGH);  
      Serial.println("Leg linksrum");
      
      analogWrite(GSM2, LMOTPWR);   // Motor 1 soll mit der Geschwindigkeit "200" (max. 255) rotieren 
      //Serial.println("Leg Move");
    }
      digitalWrite(in3, LOW);   // Anschließend sollen die Motoren 2 Sekunden ruhen.
      digitalWrite(in4, LOW);  
      ACTIV = 0;
      
}

void Look(){

       int legsens = analogRead(LEGSENS);
       int lauf = 1;
       showRun();

    while ( lauf == 1) {
      legsens = analogRead(LEGSENS);
       if ((legsens > SLEGLOOK-SR)&&( legsens < SLEGLOOK+SR)) { lauf = 0;} else { lauf = 1;}
      digitalWrite(in3, HIGH);  // Motor 1 beginnt zu rotieren
      digitalWrite(in4, LOW);  
      analogWrite(GSM2, LMOTPWR);   // Motor 1 soll mit der Geschwindigkeit "200" (max. 255) rotieren 
      
    }
      
      digitalWrite(in3, LOW);   // Anschließend sollen die Motoren 2 Sekunden ruhen.
      digitalWrite(in4, LOW);  
      ACTIV = 0;
      
}
  


void doTest(){

  bargraph();
  
  digitalWrite(in1, HIGH);  // Motor 1 beginnt zu rotieren
  digitalWrite(in2, LOW);

  analogWrite(GSM1, 100);   // Motor 1 soll mit der Geschwindigkeit "200" (max. 255) rotieren 

  digitalWrite(in3, HIGH);  // Motor 2 beginnt zu rotieren
  digitalWrite(in4, LOW);

  analogWrite(GSM2, 100);   // Motor 2 soll ebenfalls mit der Geschwindigkeit "200" (max. 255) rotieren
  delay(1000);

  digitalWrite(in1, LOW);   // Durch die Veränderung von HIGH auf LOW (bzw. LOW auf HIGH) wird die Richtung der Rotation verändert.
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
  delay(1000);

  digitalWrite(in1, LOW);   // Anschließend sollen die Motoren 2 Sekunden ruhen.
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  delay(1000);
}


void move2to3() {

     int centup = digitalRead(CENTUP);
     int centdown = digitalRead(CENTDOWN);
     int legsens = analogRead(LEGSENS);

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





    
}



void doMove() {

  int trig = digitalRead(TRIG);
  int prog = digitalRead(PROG);

  if (trig == 0) {
   
   if (MODE == 1){centerUp();} 
   if (MODE == 2){centerDown();}
   if (MODE == 3){LegCenter();}
   if (MODE == 4){LegMove();}
   if (MODE == 5){Look();}
   if (MODE == 6){doTest();}
   
   if (MODE == 0){ACTIV = 1;} 
   // 0=undefiniert | 1=twoleg | 2=move | 3=lookdown 
   
  //move2to3();
   

  //if ((MODE == 0) && (POSITION == 1)){move2to3(); }
   //if ((MODE == 0) && (POSITION == 2)){ LegCenter(); centerUp(); }
   //if ((MODE == 0) && (POSITION == 0)){ bargraph(); } 
   //if ((MODE == 0) && (POSITION == 1) && (prog == 1)){ Look(); }
   
   //if ((MODE == 0) && (POSITION == 2)){ centerDown(); }
   //if ((MODE == 0) && (POSITION == 2)){ centerDown(); } 
    
  }// END trig

  
}







  
