int pinoPot = 32;  // pinos analógicos disponíveis: 32, 33, 34, 35, 36, 39

void setup() {
  Serial.begin(9600);
}

void loop() {
  int valor = analogRead(pinoPot);
  Serial.print(0); Serial.print(", ");
  Serial.print(4095); Serial.print(", ");
  Serial.println(valor);
  delay(100);
}

// ─────────────────────────────────────────────
// DESAFIO: use o valor do pot para controlar a
// velocidade do piscar do LED.
// (dica: coloque 'valor' dentro do delay())
//
// BÔNUS: combinar com o botão — pot controla
// velocidade, botão liga/desliga o piscar.
// ─────────────────────────────────────────────
