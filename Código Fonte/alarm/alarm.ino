const int fotoresistorePin = 3;
const int buzzerPin = 13; 
const int ledRed1 = 11;
const int buttonInclinacao = 12;
int estadoButton = 0;
const int sensorPin = 2; 
bool alarmInclinacao = false;
const int redPin = 10; //Pino do RED
const int bluePin = 9; //Pino do BLUE
const int greenPin = 8; //Pino do GREEN
const bool invert = true;
int color = 0; // valor HUE
int R, G, B; // variáveis RGB

void setup() {
  Serial.begin(9600);
  
  pinMode(fotoresistorePin, INPUT); // configura o fotoresistore como entrada
  pinMode(ledRed1, OUTPUT); // configura o LED multicolorido como saída
  pinMode(buzzerPin, OUTPUT); // configura a campainha como saída
  pinMode(sensorPin, INPUT_PULLUP); // configura o detetor de inclinação como entrada com pull-up interno
  pinMode(buttonInclinacao , INPUT);
  
  attachInterrupt(digitalPinToInterrupt(fotoresistorePin), ativarAlarmeFogo, CHANGE); // ativa a interrupção para o fotoresistore
  attachInterrupt(digitalPinToInterrupt(sensorPin), ativarAlarmeInclinacao, FALLING); // ativa a interrupção para o detetor de inclinação
}

void loop() {
  
  // ativa o alarme de inclinação
  if(alarmInclinacao == true)
  {
    digitalWrite(buzzerPin, HIGH);
    
    // Valor do brilho (0 - 255)
  	int brightness = 255;

  	hueToRGB(color, brightness);

    // Fornecer valores às variáveis
    analogWrite(redPin, R);
    analogWrite(greenPin, G);
    analogWrite(bluePin, B);

    color++;

    if (color > 255)
      color = 0;

    delay(5);
  }
  else
  {
    analogWrite(redPin, 0);
	analogWrite(greenPin, 0);
	analogWrite(bluePin, 0);
  	digitalWrite(buzzerPin, LOW);
  }
  
  // desativa o alarme de inclinação
  estadoButton = digitalRead(buttonInclinacao);
	if (estadoButton == HIGH) 
    {
      	Serial.print("Alarme de inclinacao desativado!\n");
      	alarmInclinacao = false;
		delay(100);
    }
}

// esta função é chamada quando o fotoresistore detecta uma mudança brusca na luminosidade
void ativarAlarmeFogo() {
  // ativa a campainha e o LED multicolorido
  digitalWrite(buzzerPin, HIGH);
  digitalWrite(ledRed1, HIGH);

  // espera 1 segundo
  delay(1000);

  // desativa a campainha e o LED multicolorido
  digitalWrite(buzzerPin, LOW);
  digitalWrite(ledRed1, LOW);
}

// esta função é chamada quando o detetor de inclinação detecta uma inclinação
void ativarAlarmeInclinacao() {
  alarmInclinacao = true;
}

//Função de conversão da cor para os componentes RGB
void hueToRGB(int hue, int brightness) {
  //Hue à escala
  unsigned int scaledHue = (hue * 6);

  //Segmento de 0 a 5 (ciclo de cores)
  unsigned int segment = scaledHue / 256;

  //Posição no segmento
  unsigned int segmentOffset = scaledHue - (segment * 256);
  
  unsigned int complement = 0;
  unsigned int prev = (brightness * (255 - segmentOffset)) / 256;
  unsigned int next = (brightness * segmentOffset) / 256;
  
  if (invert) {
    brightness = 255 - brightness;
    complement = 255;
    prev = 255 - prev;
    next = 255 - next;
  }

  switch (segment) {
    case 0:  // red
      R = brightness;
      G = next;
      B = complement;
      break;
    case 1:  // yellow
      R = prev;
      G = brightness;
      B = complement;
      break;
    case 2:  // green
      R = complement;
      G = brightness;
      B = next;
      break;
    case 3:  // cyan
      R = complement;
      G = prev;
      B = brightness;
      break;
    case 4:  // blue
      R = next;
      G = complement;
      B = brightness;
      break;
    case 5:  // magenta
    default:
      R = brightness;
      G = complement;
      B = prev;
      break;
  }
}