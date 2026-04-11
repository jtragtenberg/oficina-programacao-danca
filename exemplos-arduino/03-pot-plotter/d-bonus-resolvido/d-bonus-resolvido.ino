// ─────────────────────────────────────────────
// 03 · Potenciômetro + Serial Plotter — bônus resolvido
// ─────────────────────────────────────────────
// Botão liga/desliga o piscar.
// Pot controla a velocidade quando está ligado.

int pinoPot = 32;  // pinos analógicos disponíveis: 32, 33, 34, 35, 36, 39
int pinoBotao = 2;
int pinoLED = 4;

void setup() {
  Serial.begin(9600);
  pinMode(pinoLED,   OUTPUT);
  pinMode(pinoBotao, INPUT_PULLUP);
}

void loop() {
  int valor = analogRead(pinoPot);
  int botao = digitalRead(pinoBotao);
  Serial.println(valor);

  if (botao == LOW) {
    digitalWrite(pinoLED, HIGH);
    delay(valor);
    digitalWrite(pinoLED, LOW);
    delay(valor);
  } else {
    digitalWrite(pinoLED, LOW);
  }
}
