/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */

// Using analog pins as digital output
// http://forum.arduino.cc/index.php/topic,48864.0.html
int led[] = {14, 15, 16, 17, 18, 19};
int idx = 0;
int dir = 1;

void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  for(int i = 0; i < 6; i++)
    pinMode(led[i], OUTPUT);
    
  int idx = 0;
  int dir = 1;
}

void loop() {
  
  int lvl = (dir == 1) ? HIGH : LOW;
  
  digitalWrite(led[idx], lvl);
  
  idx = idx+dir;
  
  if(idx > 5)
  {
     dir = -1;
     idx = 5; 
  }
  else if(idx < 0)
  {
    dir = 1;
    idx = 0;
  }
  
  delay(100);
}
