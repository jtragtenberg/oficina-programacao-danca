void setup() {
  pinMode(2, OUTPUT);
}

void loop() {
  digitalWrite(2, HIGH);
  delay(1000);
  digitalWrite(2, LOW);
  delay(1000);
}

// ─────────────────────────────────────────────
// DESAFIO: mude os valores de delay() para o LED
// piscar mais rápido ou mais devagar.
// Os dois podem ser diferentes!
// ─────────────────────────────────────────────
