// ─────────────────────────────────────────────
// 02 · Botão + LED — bônus resolvido
// ─────────────────────────────────────────────
// Lógica invertida: LED fica sempre aceso.
// Ao apertar o botão, o LED apaga.

int pinoBotao = 2;
int pinoLED = 4;

void setup() {
  pinMode(pinoBotao, INPUT_PULLUP);
  pinMode(pinoLED,   OUTPUT);
}

void loop() {
  int botao = digitalRead(pinoBotao);

  if (botao == LOW) {
    digitalWrite(pinoLED, LOW);   // apaga quando aperta
  } else {
    digitalWrite(pinoLED, HIGH);  // aceso o tempo todo
  }
}
