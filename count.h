// Rotary Encoder Inputs
#define CLK 11
#define DT 12
//#define SW 4

int currentStateCLK;
int lastStateCLK;
String currentDir ="";
//unsigned long lastButtonPress = 0;
bool count = false;

void getCounter() {
  
  // Read the current state of CLK
  currentStateCLK = digitalRead(CLK);

  count = false;

  // If last and current state of CLK are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){

    
    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(DT) != currentStateCLK) {
      counter --;
      currentDir ="CCW";
      //MODE = counter;
      //showMode();
      count = true;
      
      
    } else {
      // Encoder is rotating CW so increment
      counter ++;
      currentDir ="CW";
      //MODE = counter;
      //showMode();
      count = true;
    }

    /*
    Serial.print("MODE: ");
     Serial.print(MODE);
   
    Serial.print(" Direction: ");
    Serial.print(currentDir);
    Serial.print(" | Counter: ");
    Serial.println(counter);
    */
  }

  // Remember last CLK state
  lastStateCLK = currentStateCLK;


  // Read the button state
  
  
    
  // Put in a slight delay to help debounce the reading
  //delay(1);
}
