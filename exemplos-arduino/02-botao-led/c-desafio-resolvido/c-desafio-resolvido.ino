// ─────────────────────────────────────────────
// 02 · Botão + LED — desafio resolvido
// ─────────────────────────────────────────────
// Enquanto segurar o botão: LED pisca rápido.
// Ao soltar: LED apaga.

int pinoBotao = 13;
int pinoLED = 2;

void setup() {
  pinMode(pinoBotao, INPUT_PULLUP);
  pinMode(pinoLED,   OUTPUT);
}

void loop() {
  int botao = digitalRead(pinoBotao);

  if (botao == LOW) {
    digitalWrite(pinoLED, HIGH);
    delay(80);
    digitalWrite(pinoLED, LOW);
    delay(80);
  } else {
    digitalWrite(pinoLED, LOW);
  }
}
