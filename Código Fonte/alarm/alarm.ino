const int fotoresistorePin = 3; // pino de entrada do fotoresistore
const int buzzerPin = 13; // pino de saída do buzzer
const int ledRed1 = 12;
const int ledRedRGB = 10;
const int ledBlueRGB = 9;
const int ledGreenRGB = 8;
const int sensorPin = 2; // pino de entrada do sensor de inclinação

void setup() {
  pinMode(fotoresistorePin, INPUT); // configura o fotoresistore como entrada
  pinMode(ledRed1, OUTPUT); // configura o LED multicolorido como saída
  pinMode(ledRedRGB, OUTPUT); // configura o LED multicolorido como saída
  pinMode(ledBlueRGB, OUTPUT); // configura o LED multicolorido como saída
  pinMode(ledGreenRGB, OUTPUT); // configura o LED multicolorido como saída
  pinMode(buzzerPin, OUTPUT); // configura a campainha como saída
  pinMode(sensorPin, INPUT_PULLUP); // configura o detetor de inclinação como entrada com pull-up interno

  attachInterrupt(digitalPinToInterrupt(fotoresistorePin), ativarAlarmeFogo, CHANGE); // ativa a interrupção para o fotoresistore
  attachInterrupt(digitalPinToInterrupt(sensorPin), ativarAlarmeInclinacao, FALLING); // ativa a interrupção para o detetor de inclinação
}

void loop() {
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
  // ativa a campainha e os LEDs vermelhos
  digitalWrite(buzzerPin, HIGH);
  // pode-se utilizar mais de um LED vermelho para indicar a inclinação, basta ligá-los a pinos de saída diferentes
  digitalWrite(ledRedRGB, HIGH); // liga o LED vermelho do RGB
  digitalWrite(ledBlueRGB, LOW); // desliga o LED azul do RGB
  digitalWrite(ledGreenRGB, LOW); // desliga o LED verde do RGB
  	delay(5000);
  digitalWrite(ledRedRGB, LOW); // liga o LED vermelho do RGB
  digitalWrite(ledBlueRGB, HIGH); // desliga o LED azul do RGB
  	delay(5000);
  digitalWrite(ledBlueRGB, LOW); // desliga o LED azul do RGB
  digitalWrite(ledGreenRGB, HIGH); // desliga o LED verde do RGB
  	delay(5000);
  digitalWrite(ledGreenRGB, LOW); // desliga o LED verde do RGB
  // desativa a campainha e os LEDs vermelhos
  digitalWrite(buzzerPin, LOW);
}
