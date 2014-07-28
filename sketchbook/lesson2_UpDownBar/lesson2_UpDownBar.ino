/*
 Input Pullup Serial
 
 This example demonstrates the use of pinMode(INPUT_PULLUP). It reads a 
 digital input on pin 2 and prints the results to the serial monitor.
 
 The circuit: 
 * Momentary switch attached from pin 2 to ground 
 * Built-in LED on pin 13
 
 Unlike pinMode(INPUT), there is no pull-down resistor necessary. An internal 
 20K-ohm resistor is pulled to 5V. This configuration causes the input to 
 read HIGH when the switch is open, and LOW when it is closed. 
 
 created 14 March 2012
 by Scott Fitzgerald
 
 http://www.arduino.cc/en/Tutorial/InputPullupSerial
 
 This example code is in the public domain
 
 */
 
//int led[] = {14, 15, 16, 17, 18, 19};
int led[] = {A0, A1, A2, A3, A4, A5};
int idx = 0;
int dir = 1;

void setup()
{
  //configure pin2 as an input and enable the internal pull-up resistor
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  
  for(int i = 0; i < 6; i++)
    pinMode(led[i], OUTPUT);
    
  int idx = 0;
  int dir = 1;
  
  Serial.begin(9600);
}

void loop()
{ 
  //read the pushbutton value into a variable
  int up = digitalRead(2);
  
  //read the pushbutton value into a variable
  int down = digitalRead(3);
  
  // Keep in mind the pullup means the pushbutton's
  // logic is inverted. It goes HIGH when it's open,
  // and LOW when it's pressed. Turn on pin 13 when the 
  // button's pressed, and off when it's not:
  if (up == HIGH && down == LOW)
  {
    dir = -1;
    Serial.println(dir);
    delay(100);
  }
  else if (up == LOW && down == HIGH)
  {
    dir = 1;
    Serial.println(dir);
    delay(100);
  }
  else
  {
    dir = 0;
  }
  
  idx = idx+dir;
  
  if(idx > 6)
  {
    idx = 6; 
  }
  else if(idx < 0)
  {
    idx = 0;
  }
  
  Serial.println(idx);
  
  for(int i = 0; i < idx; i++)
    digitalWrite(led[i], HIGH);
  
  for(int i = idx; i < 6; i++)
    digitalWrite(led[i], LOW);
}
