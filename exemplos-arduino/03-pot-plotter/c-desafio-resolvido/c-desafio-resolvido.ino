// ─────────────────────────────────────────────
// 03 · Potenciômetro + Serial Plotter — desafio resolvido
// ─────────────────────────────────────────────
// O pot controla a velocidade do piscar do LED.
// Gire para um lado: pisca devagar.
// Gire para o outro: pisca rápido.

int pinoPot = 32;  // pinos analógicos disponíveis: 32, 33, 34, 35, 36, 39
int pinoLED = 13;

void setup() {
  Serial.begin(9600);
  pinMode(pinoLED, OUTPUT);
}

void loop() {
  int valor = analogRead(pinoPot);  // 0 a 1023
  Serial.println(valor);

  digitalWrite(pinoLED, HIGH);
  delay(valor);
  digitalWrite(pinoLED, LOW);
  delay(valor);
}
