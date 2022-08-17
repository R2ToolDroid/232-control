#include <Arduino.h>

void showMode(){
 
    display.clearDisplay();
    display.setTextSize(1);      // Normal 1:1 pixel scale
    display.setTextColor(WHITE); // Draw white text
    display.setCursor(1, 2);     // Start at top-left corner
    if (Start){
      display.drawRect(0,0,128,11,WHITE);
      display.print(" -R2 Ready to Start- ");
      
    } else {
    display.print("POS  :  ");
      // 0=undefiniert | 1=twoleg | 2=move | 3=lookdown
      switch (POSITION) {
            case 0:
            display.print("!undefined!");
            break;

            case 1:
            display.print("TWO LEG    ");
            break;

            case 2:
            display.print("THREE LEG  ");
            break;

            case 3:
            display.print("LOOK DOWN  ");
            break;
        
      }
    
    //display.print(POSITION);  
    }
    if(!Start){
    display.drawRect(37,12,91,11,WHITE);
    }
    display.setCursor(0, 14);     // Start at top-left corner
    display.print("MODE : ");
    if (MODE == 0){ display.print("0 Auto   ");}
    if (MODE == 1){ display.print("1 CentUp ");}
    if (MODE == 2){ display.print("2 CentDn ");}
    if (MODE == 3){ display.print("3 LegCent");}
    if (MODE == 4){ display.print("4 LegMove");}
    if (MODE == 5){ display.print("5 LookDn ");}
    if (MODE == 6){ display.print("6 Test   ");}
    if (MODE == 7){ display.print("7 -SETUP-");}
    if (MODE == 8){ display.print("8 Start");}

    //int centup = digitalRead(CENTUP);
   // int centdown = digitalRead(CENTDOWN);
    //int legmove = digitalRead(LEGMOVE);
    //int legsens = map(analogRead(LEGSENS), 1023 ,0 , 200, 0);
    //int leglook = digitalRead(LEGLOOK);
    display.setCursor(0, 25);     // Start at top-left corner
    display.print("SEN: ");

    if (READ_CENTUP == 1) {display.print ("UP 1");}
    else {display.print ("UP 0");}
    if (READ_CENTDOWN == 1) {display.print (" DW 1");}
    else {display.print (" DW 0");}
    display.print (" -");
    display.print (READ_LEGSENS);
    display.print ("-");
    //if (POSITION == 0){display.drawBitmap(104,1,side_bmp, WIDTH, HEIGHT, 1);}
    //if (POSITION == 1){display.drawBitmap(104,1,front_bmp, WIDTH, HEIGHT, 1);}
    //if (POSITION == 2){display.drawBitmap(104,1,drive_bmp, WIDTH, HEIGHT, 1);}
    //if (POSITION == 3){display.drawBitmap(104,1,look_bmp, WIDTH, HEIGHT, 1);}
    display.display();
    
    
}

void checkpos(){

          
  
          //bool centup = digitalRead(CENTUP);
          //bool centdown = digitalRead(CENTDOWN);
          //byte legsens = analogRead(LEGSENS);
          //int legcenter = digitalRead(LEGCENTER);
           //int legsens = READ_LEGSENS;
          //int leglook = digitalRead(LEGLOOK);
          int OLD_POSITION = POSITION;
          // 0=undefiniert | 1=twoleg | 2=move | 3=lookdown
          /// SLEGCENT ; SLEGMOVE ; SLEGLOOK;
          POSITION = 0;
            if (( READ_CENTUP == 0 )&&( inRange(READ_LEGSENS, SLEGCENT-SR, SLEGCENT+SR) )) {POSITION = 1;}
            
            if (( READ_CENTDOWN == 0 )&& ( inRange(READ_LEGSENS, SLEGMOVE-SR, SLEGMOVE+SR) )) {POSITION = 2;}
            
            if ((READ_CENTUP == 0)&& ( inRange(READ_LEGSENS, SLEGLOOK-SR, SLEGLOOK+SR)  )) {POSITION = 3;}
            
            //if ((READ_CENTUP == 0)&& (READ_CENTDOWN == 0 )) {POSITION = 0;}
            //if ((READ_CENTUP == 1)&& (READ_CENTDOWN == 1 )) {POSITION = 0;}

          //if ((centdown == 1)&&( legmove == 1 ) &&( legcenter == 1 ) && (centup == 1) ) {POSITION = 0;}
          //  if ((centdown == 0)&&( legmove == 0 ) &&( legcenter == 0 ) && (centup == 1) && (leglook == 1) ) {POSITION = 3;} 
            if (debug)
            {
              
            Serial.print("POS = ");
            Serial.print(POSITION);
            Serial.print(" - centup = ");
            Serial.print(READ_CENTUP);
            Serial.print(" | centdown = ");
            Serial.print(READ_CENTDOWN);
            Serial.print(" | legsens = ");
            Serial.println(READ_LEGSENS);
            
            }
            
          if (POSITION != OLD_POSITION){
              showMode();
            }
            
}///checkpos
