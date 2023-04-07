#include <Arduino.h>    

//// Commandos ///////
void ProzessComando() {

     

    if (data == "move" )
      {             
       Serial.println("move");
       MODE=0;
       ACTIV = true;    
       
      }

        
      
    if (data == "shake" )
      {         
       Serial.println("shake");
       Shake();
       
      }

    if (data == "look" )
      {         
       Serial.println("look");
       Look();
       
      }  

    if (data == "Lcenter" )
      {         
       Serial.println("Lcenter");
       LegCenter();
       
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

    
  
  MainInput.listen();
  
   if (MainInput.available() > 0)
    {
        data = MainInput.readStringUntil('\r');
        Serial.print("main_");
        Serial.println(data);
        ProzessComando();
        
    }
    
}
