# Oficina de Programação através da Dança

Materiais da oficina: códigos Arduino, patches PlugData, externals do Giromin e apresentações.

---

## Downloads necessários

**PlugData**
→ https://plugdata.org/download.html

**Protokol** (visualizar dados OSC)
→ https://hexler.net/protokol

**Arduino IDE**
→ https://arduino.cc/en/software

**Driver USB-UART para ESP32**
→ https://www.silabs.com — CP210x VCP Drivers

---

## Repositório

→ https://github.com/jtragtenberg/oficina-programacao-danca

Códigos Arduino, patches PlugData, externals do Giromin, apresentações.

---

## Configurar placa ESP32 no Arduino IDE

```
Tools → Board → Boards Manager → buscar "esp32 by Espressif Systems"
Tools → Board → esp32 → ESP32 Dev Module
Tools → PSRAM → Disabled
```

---

## Externals do Giromin para PlugData

Baixar a versão mais recente em:
→ https://github.com/jtragtenberg/giromin-software/releases

Copiar os arquivos para:
- **macOS**: `~/Documents/PlugData/Externals/Giromin/`
- **Linux**: `~/.local/lib/pd/`
- **Windows**: pasta de externals do PlugData

Depois: **PlugData → Settings → Paths** → adicionar o caminho → reiniciar.

### Objetos disponíveis

| Objeto | Descrição |
|---|---|
| `giromin.angulos` | converte quaternion para ângulos de Euler |
| `giromin.suavizar` | filtro EMA assimétrico (rise/fall) |
| `giromin.map` | remapeia valores entre faixas |
| `giromin.centro` | detecta centro de oscilação |
| `giromin.pico` | detecta picos com debounce |
| `giromin.fusao` | fusão de sensores (Madgwick) |
