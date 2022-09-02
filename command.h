#include <Arduino.h>    

//// Commandos ///////
void ProzessComando() {

     

    if (data == "move" )
      {             
       Serial.println("Move");
       MODE=0;
       ACTIV = true;
       
       
      }
      
    if (data == "shake" )
      {         
       Serial.println("Shake");
       Shake();
       
      }

    if (data == "look" )
      {         
       Serial.println("look");
       Shake();
       
      }  

    if (data == "center" )
      {         
       Serial.println("center");
       Shake();
       
      } 
      

    
    if (data == "debug on")
      {
        Serial.println("Debug Mode ON");
        debug = true;      
      }

    if (data == "debug off")
      {
        Serial.println("Debug Mode off");
        debug = false;
      }
    
    data = "";
}



void Comand() {
///Comando Pruefung////
   if(Serial.available() > 0)
    {
        
        data = Serial.readStringUntil('\n');         
        ProzessComando();       
    }
  /*///Prüfung 2///
  MainInput.listen();
  
   if (MainInput.available() > 0)
    {
        data = MainInput.readStringUntil('\r');
        Serial.println("main");
        Serial.println(data);
        ProzessComando();
        
    }
    */
}
