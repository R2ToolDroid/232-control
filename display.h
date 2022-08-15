#include <Arduino.h>

void showMode(){
 
    display.clearDisplay();
    display.setTextSize(1);      // Normal 1:1 pixel scale
    display.setTextColor(WHITE); // Draw white text
    display.setCursor(2, 4);     // Start at top-left corner
    display.print("STATUS : ");
    display.print(POSITION);  // 0=undefiniert | 1=twoleg | 2=move | 3=lookdown
    display.setCursor(2, 18);     // Start at top-left corner
    display.print("MODE : ");
    if (MODE == 0){ display.print("0 Automatic");}
    if (MODE == 1){ display.print("1 CentUp   ");}
    if (MODE == 2){ display.print("2 CentDown ");}
    if (MODE == 3){ display.print("3 LegCent  ");}
    if (MODE == 4){ display.print("4 LegMove  ");}
    if (MODE == 5){ display.print("5 LookDown  ");}
    if (MODE == 6){ display.print("6 Test MOT  ");}
    if (MODE == 7){ display.print("7 -SETUP-");}


    //int centup = digitalRead(CENTUP);
    //int centdown = digitalRead(CENTDOWN);
    //int legmove = digitalRead(LEGMOVE);
    //int legsens = map(analogRead(LEGSENS), 1023 ,0 , 200, 0);
    //int leglook = digitalRead(LEGLOOK);
    //display.setCursor(0, 25);     // Start at top-left corner
    //display.print("SEN: ");

    //if (centup == 1) {display.print ("UP 1");}
    //else {display.print ("UP 0");}
    //if (centdown == 1) {display.print (" DW 1");}
    //else {display.print (" DW 0");}
    //display.print (" -");
    //display.print (legsens);
    //display.print ("-");
    //if (POSITION == 0){display.drawBitmap(104,1,side_bmp, WIDTH, HEIGHT, 1);}
    //if (POSITION == 1){display.drawBitmap(104,1,front_bmp, WIDTH, HEIGHT, 1);}
    //if (POSITION == 2){display.drawBitmap(104,1,drive_bmp, WIDTH, HEIGHT, 1);}
    //if (POSITION == 3){display.drawBitmap(104,1,look_bmp, WIDTH, HEIGHT, 1);}
    display.display();
    
    
}

void showSens(){

    
  
    display.clearDisplay();
    display.setTextSize(1);      // Normal 1:1 pixel scale
    display.setTextColor(WHITE); // Draw white text
    display.setCursor(0, 4);     // Start at top-left corner
    display.print("VALUE : ");
    display.print(counter);  // 0=undefiniert | 1=twoleg | 2=move | 3=lookdown
    
}
