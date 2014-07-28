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

// Variáveis de temporização
const unsigned long t_state[] = {5000, 2000, 1000, 4000, 3000};
unsigned long t_init;

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
  //attachInterrupt(0, buttonPressed, FALLING);
  attachInterrupt(0, debounceButtonPressed, FALLING);
  
  // Guardamos a contagem atual: temporização começa agora!
  t_init = millis();
}

void loop()
{ 
  // Aqui mostramos que a interrupção continua funcionando 
  Serial.print("timesButtonPressed: ");
  Serial.println(timesButtonPressed);
  
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
  
  // Saída
  carGreen();
  pedRed();
  
  // Transição de Estado
  if(isStateTimeOver(0))
  {
    state = 1;
    t_init = millis();
  }
}

void state_1()
{
  Serial.println("State 1");
  
  // Saída
  carYellow();
  pedRed();
  
  // Transição de Estado
  if(isStateTimeOver(1))
  {
    state = 2;
    t_init = millis();
  }
}

void state_2()
{
  Serial.println("State 2");
  
  // Saída
  carRed();
  pedRed();
  
  // Transição de Estado
  if(isStateTimeOver(2))
  {
    state = 3;
    t_init = millis();
  }
}

void state_3()
{
  Serial.println("State 3");
  
  // Saída
  carRed();
  pedGreen();
  
  // Transição de Estado
  if(isStateTimeOver(3))
  {
    state = 4;
    t_init = millis();
  }
}

void state_4()
{
  Serial.println("State 4");
  
  // Saída
  carRed();
  pedRed();
  
  // Transição de Estado
  if(isStateTimeOver(4))
  {
    state = 0;
    t_init = millis();
  }
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

void debounceButtonPressed()
{
  static unsigned long debouncing_time = 100;
  static unsigned long last_millis = millis();
  
  if((millis() - last_millis) >= debouncing_time)
  {
    buttonPressed();
    last_millis = millis();
  }
}

// Função que diz se tempo para cada estado terminou
boolean isStateTimeOver(int state)
{
  unsigned long t = millis();
  
  if(t-t_init > t_state[state])
  {
    return true;
  }
  else
    return false;
}


