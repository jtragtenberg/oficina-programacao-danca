# Código da Oficina — Programação e Dança

Bem-vinde! Aqui estão os códigos que usamos na oficina.

A lógica de cada ciclo é sempre a mesma: você vê o código funcionando, replica no seu computador, e depois recebe um desafio para modificar. Não precisa entender tudo de uma vez — o importante é experimentar.

---

## Como usar esses arquivos

Cada pasta tem dois tipos de código:

- **inicio** — é o ponto de partida. Já tem o que você precisa para começar, e o desafio está escrito como comentário lá dentro.
- **desafio-resolvido** — uma versão possível do desafio. Tente resolver antes de olhar!

---

## Os ciclos

### 01 · LED interno
Fazer o LED que já vem na placa piscar.  
Funções novas: `setup()`, `loop()`, `pinMode()`, `digitalWrite()`, `delay()`

**Desafio:** mudar o tempo que o LED pisca.

---

### 02 · Botão + LED
Ligar um LED físico e um botão. Quando apertar, acende.  
Funções novas: `digitalRead()`, `if(){} else(){}`

**Desafio:** enquanto segurar o botão, o LED pisca rápido. Ao soltar, apaga.  
**Bônus:** inverter — LED sempre aceso, apaga ao apertar.

---

### 03 · Potenciômetro + Serial Plotter
Girar um botão e ver o valor mudando no computador em tempo real.  
Funções novas: `analogRead()`, `Serial.println()`  
Ferramenta nova: **Serial Plotter** (Tools → Serial Plotter)

**Desafio:** usar o valor do pot para controlar a velocidade do piscar do LED.  
**Bônus:** combinar com o botão — pot controla a velocidade, botão liga/desliga.

---

### 04 · Sensor de movimento + Serial Plotter
Ler o acelerômetro e o giroscópio do sensor MPU6050 e visualizar no plotter.  
Biblioteca necessária: instalar **Adafruit MPU6050** no Library Manager.

**Desafio:** segurar o sensor e mover o corpo — descobrir qual dado (AccelX, AccelY, AccelZ, GyroX, GyroY, GyroZ) corresponde a qual gesto.

---

### 05 · Sensor de movimento + OSC via Wi-Fi *(bônus)*
Mandar os dados do sensor pelo Wi-Fi usando o protocolo OSC.  
Biblioteca necessária: instalar **OSC** by Adrian Freed no Library Manager.  
Para receber os dados: abrir o **Protokol** e escutar na porta `9999`.

Depois de gravar, desligar o cabo USB, ligar no powerbank e colocar no corpo.

---

## Bibliotecas para instalar

Vá em **Tools → Manage Libraries** e busque:

| Ciclo | O que buscar |
|-------|-------------|
| 04 e 05 | `Adafruit MPU6050` |
| 05 | `OSC` (escolher o de Adrian Freed) |
