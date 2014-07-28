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

// Essa variável guarda o estado atual
int state = 0;

void setup()
{
  // Pino do botão definido como INPUT_PULLUP
  // Assim, usamos o resistor de pull-up interno e poupamos um resistor!
  pinMode(buttonPin, INPUT_PULLUP);
  
  // Pinos dos LEDs definidos como OUTPUT
  // Usamos o vetor ledPins e o for para não termos que nos repetir
  for(int i = 0; i < 5; i++)
    pinMode(ledPins[i], OUTPUT);
    
  // Vamos usar a porta Serial para ver se estamos trocando de estado
  Serial.begin(9600);
  
  // Vamos ligar a interrupção externa no pino do botão, para a contagem mudar imediatamente
  // O parâmetro 0 representa o número da interrupção
  // O parâmetro buttonPressed é o nome da função que é chamada quando ocorre a interrupção
  // O parâmetro FALLING significa que a interrupção ocorre na borda de descida do pino de HIGH para LOW
  // Mais infos: http://arduino.cc/en/Reference/AttachInterrupt
  attachInterrupt(0, buttonPressed, FALLING);
  //attachInterrupt(0, debounceButtonPressed, FALLING);
}

void loop()
{  
  // A % B faz a divisão de A por B e retorna o resto
  // Isso permite que state varie de forma circular: 0, 1, 2, 3, 4, 0, 1, 2, ...
  state = timesButtonPressed % 5;
  
  // Esse switch/case permite que o comportamento mude, de acordo com o estado atual
  switch(state)
  {
    case 0:
      state_0();
      break;
    case 1:
      state_1();
      break;
    case 2:
      state_2();
      break;
    case 3:
      state_3();
      break;
    case 4:
      state_4();
      break;
    default:
      state_unknown();
      break;
  }
}

// Funções que dizem o que acontece em cada estado
void state_0()
{
  Serial.println("State 0");
  
  carGreen();
  pedRed();
}

void state_1()
{
  Serial.println("State 1");
  
  carYellow();
  pedRed();
}

void state_2()
{
  Serial.println("State 2");
  
  carRed();
  pedRed();
}

void state_3()
{
  Serial.println("State 3");
  
  carRed();
  pedGreen();
}

void state_4()
{
  Serial.println("State 4");
  
  carRed();
  pedRed();
}

void state_unknown()
{
  Serial.println("Unknown state!");
}

// Funções auxiliares para controlar as luzes
void carGreen()
{
  digitalWrite(carGreenPin, HIGH);
  digitalWrite(carYellowPin, LOW);
  digitalWrite(carRedPin, LOW);
}

void carYellow()
{
  digitalWrite(carGreenPin, LOW);
  digitalWrite(carYellowPin, HIGH);
  digitalWrite(carRedPin, LOW);
}

void carRed()
{
  digitalWrite(carGreenPin, LOW);
  digitalWrite(carYellowPin, LOW);
  digitalWrite(carRedPin, HIGH);
}

void pedGreen()
{
  digitalWrite(pedGreenPin, HIGH);
  digitalWrite(pedRedPin, LOW); 
}

void pedRed()
{
  digitalWrite(pedGreenPin, LOW);
  digitalWrite(pedRedPin, HIGH); 
}

// Função executada quando ocorre a interrupção do botão
void buttonPressed()
{
  timesButtonPressed++;
}

/*void debounceButtonPressed()
{
  static unsigned long debouncing_time = 100;
  static unsigned long last_millis = millis();
  
  if((millis() - last_millis) >= debouncing_time)
  {
    buttonPressed();
    last_millis = millis();
  }
}*/
