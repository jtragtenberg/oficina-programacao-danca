// ─────────────────────────────────────────────
// 01 · LED interno — desafio resolvido
// ─────────────────────────────────────────────
// LED piscando bem rápido (50ms aceso, 50ms apagado)

void setup() {
  pinMode(2, OUTPUT);
}

void loop() {
  digitalWrite(2, HIGH);
  delay(50);
  digitalWrite(2, LOW);
  delay(50);
}
