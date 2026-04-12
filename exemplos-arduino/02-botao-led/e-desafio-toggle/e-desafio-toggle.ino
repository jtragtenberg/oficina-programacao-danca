int pinoBotao  = 5;
int pinoLED    = 2;

int estadoLED  = LOW;
int ultimoBotao = HIGH;

void setup() {
  pinMode(pinoBotao, INPUT_PULLUP);
  pinMode(pinoLED,   OUTPUT);
}

void loop() {
  int botao = digitalRead(pinoBotao);

  if (botao == LOW && ultimoBotao == HIGH) {
    if (estadoLED == LOW) {
      estadoLED = HIGH;
    } else {
      estadoLED = LOW;
    }
    digitalWrite(pinoLED, estadoLED);
    // delay(20);
  }

  ultimoBotao = botao;
}
