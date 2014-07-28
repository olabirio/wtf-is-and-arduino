// Definimos os pinos que vamos usar
const int buttonPin = 2;
const int pedGreenPin = 3;
const int pedRedPin = 4;
const int carRedPin = 5;
const int carYellowPin = 6;
const int carGreenPin = 7;

// Esse vetor ajuda na hora de inicializar e testar os pinos
const int ledPins[] = {pedGreenPin, pedRedPin, carRedPin, carYellowPin, carGreenPin};

// Essa variável vai contar quantas vezes apertamos o botão
int timesButtonPressed = 0;

void setup()
{
  // Pino do botão definido como INPUT_PULLUP
  // Assim, usamos o resistor de pull-up interno e poupamos um resistor!
  pinMode(buttonPin, INPUT_PULLUP);
  
  // Pinos dos LEDs definidos como OUTPUT
  // Usamos o vetor ledPins e o for para não termos que nos repetir
  for(int i = 0; i < 5; i++)
    pinMode(ledPins[i], OUTPUT);
}

void loop()
{
  // Se botão for pressionado, incrementar a contagem
  // Lembrem-se: No modo INPUT_PULLUP, botão pressionado fica LOW!
  if(digitalRead(buttonPin) == LOW)
    timesButtonPressed++;
  
  // A % B faz a divisão de A por B e retorna o resto
  // Isso permite que testPin varie de forma circular: 0, 1, 2, 3, 4, 0, 1, 2, ...
  int testPin = timesButtonPressed % 5;
  
  // Pisca o LED que está sendo testado
  digitalWrite(ledPins[testPin],HIGH);
  delay(50);
  digitalWrite(ledPins[testPin],LOW);
  delay(50);
}
