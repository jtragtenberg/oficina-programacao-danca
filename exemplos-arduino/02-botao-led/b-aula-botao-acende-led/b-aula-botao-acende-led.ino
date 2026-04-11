int pinoBotao = 5;
int pinoLED   = 2;

void setup() {
  pinMode(pinoBotao, INPUT_PULLUP);
  pinMode(pinoLED,   OUTPUT);
}

void loop() {
  int botao = digitalRead(pinoBotao);

  if (botao == LOW) {
    digitalWrite(pinoLED, HIGH);
  } else {
    digitalWrite(pinoLED, LOW);
  }
}

// ─────────────────────────────────────────────
// DESAFIO: enquanto segurar o botão, o LED deve
// piscar rápido. Ao soltar, o LED apaga.
// (dica: coloque delay() dentro do if)
//
// BÔNUS: inverter a lógica — LED sempre aceso,
// apaga ao apertar o botão.
// ─────────────────────────────────────────────
