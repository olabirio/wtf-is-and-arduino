int led[] = {11, 10, 9, 6, 5, 3};
int pot = A0;

void setup()
{
  int i = 0;
  while(i < 6)
  {
    pinMode(led[i], OUTPUT);
    i++;
  }
  
  pinMode(pot, INPUT); // not needed, but good to be sure
}

void loop()
{
  int sensorValue = analogRead(pot);

  int numPins = map(sensorValue, 0, 1023, 0, 6);
 
  for(int i = 0; i < numPins; i++)
    digitalWrite(led[i], HIGH);
    
  for(int i = numPins; i < 6; i++) 
    digitalWrite(led[i], LOW);
    
  delay(2);
}
