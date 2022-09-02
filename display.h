#include <Arduino.h>

void showMode(){
 
    display.clearDisplay();
    display.setTextSize(1);      // Normal 1:1 pixel scale
    display.setTextColor(WHITE); // Draw white text
    display.setCursor(1, 2);     // Start at top-left corner
    
    display.print(F("POS  : "));
      // 0=undefiniert | 1=twoleg | 2=move | 3=lookdown
      switch (POSITION) {
            case 0:        
            display.print(F("ERROR_POS"));            
            break;

            case 1:
            display.print(F("TWO LEG  "));
            break;

            case 2:
            display.print(F("THREE LEG"));
            break;

            case 3:
            display.print(F("LOOK DOWN"));
            break;

            case 4:
            display.print(F("TWO LEG +"));
            break;

            case 5:
            display.print(F("ERROR_TIME"));
            break;
        
      }
    
    display.setCursor(0, 14);     // Start at top-left corner
    display.print(F("MODE : "));
    if (MODE == 0){ display.print(F("0 Auto   "));}
    if (MODE == 1){ display.print(F("1 CentUp "));}
    if (MODE == 2){ display.print(F("2 CentDn "));}
    if (MODE == 3){ display.print(F("3 LegCent"));}
    if (MODE == 4){ display.print(F("4 LegMove"));}
    if (MODE == 5){ display.print(F("5 LookDn "));}
    if (MODE == 6){ display.print(F("6 Check  "));}
    if (MODE == 7){ display.print(F("7 -SETUP-"));}
    
    display.setCursor(0, 25);     // Start at top-left corner
    display.print(F("SEN: "));

    if (READ_CENTUP == 1) {display.print (F("UP 1"));}
    else {display.print (F("UP 0"));}
    if (READ_CENTDOWN == 1) {display.print (F(" DW 1"));}
    else {display.print (F(" DW 0"));}
    display.print (F(" -"));
    display.print (READ_LEGSENS);
    display.print (F("-"));
    display.display();
    
    
}

void checkpos(){       
        
   if (( T_CENTUP != READ_CENTUP ) || ( T_LEGSENS != READ_LEGSENS ) || ( T_CENTDOWN != READ_CENTDOWN ))
    {
       
       REFRESH = true;
    }

          T_LEGSENS = READ_LEGSENS;
          T_CENTUP = READ_CENTUP;
          T_CENTDOWN = READ_CENTDOWN;
          
          // 0=undefiniert | 1=twoleg | 2=move | 3=lookdown | 4=twoleg with middle down
          /// SLEGCENT ; SLEGMOVE ; SLEGLOOK;
          POSITION = 0;
            
            if (( READ_CENTUP == 0 )&&( inRange(READ_LEGSENS, SLEGCENT-SR, SLEGCENT+SR) )) {POSITION = 1;}
            
            if (( READ_CENTDOWN == 0 )&& ( inRange(READ_LEGSENS, SLEGMOVE-SR, SLEGMOVE+SR) )) {POSITION = 2;}
            
            if ((READ_CENTUP == 0)&& ( inRange(READ_LEGSENS, SLEGLOOK-SR, SLEGLOOK+SR)  )) {POSITION = 3;}
            
            //if ((READ_CENTDOWN == 0)&&( inRange(READ_LEGSENS, SLEGMOVE-SR, SLEGMOVE+SR != true)  )) {POSITION = 0;}

            if (( READ_CENTUP == 1 )&&( inRange(READ_LEGSENS, SLEGCENT-SR, SLEGCENT+SR) )) {POSITION = 4;}

            
            
            //if ((READ_CENTUP == 0)&& (READ_CENTDOWN == 0 )) {POSITION = 0;}
            //if ((READ_CENTUP == 1)&& (READ_CENTDOWN == 1 )) {POSITION = 0;}

          //if ((centdown == 1)&&( legmove == 1 ) &&( legcenter == 1 ) && (centup == 1) ) {POSITION = 0;}
          //  if ((centdown == 0)&&( legmove == 0 ) &&( legcenter == 0 ) && (centup == 1) && (leglook == 1) ) {POSITION = 3;} 
            
        if (REFRESH) {

          if (debug){
              
              Serial.println(POSITION);
              
            }
          showMode();    
        }
          
            
}///checkpos
