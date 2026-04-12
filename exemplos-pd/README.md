# Exemplos Pure Data

Patches de exemplo para a oficina, organizados em ciclos progressivos.

Requer o Giromin.app rodando com OSC na porta 1333 (a partir do ciclo 03).

## Estrutura

Cada ciclo tem:
- `a-base/` — patch inicial para completar em aula
- `b-aula/` — patch construído durante a aula + desafio comentado
- `c-desafio-resolvido/` — solução do desafio

## Ciclos

### 01 — Som Ligado
`[osc~]` → `[*~]` → `[dac~]`  
toggle liga/desliga, slider controla volume.  
**Analogia Arduino:** `pinMode` + `digitalWrite`

### 02 — Metro e Ritmo
`[metro]` → `[line~]` → `[osc~]`  
temporizador dispara som percussivo, slider muda BPM.  
**Analogia Arduino:** `delay()`

### 03 — Sensor → Volume
OSC do Giromin → `[giromin.map]` → volume do `[osc~]`  
**Analogia Arduino:** `analogRead` → `analogWrite`

### 04 — Sensor → Pitch
Dois eixos: x=volume, y=frequência, z=limiar on/off.  
`[>]` + `[sel]` para lógica condicional.  
**Analogia Arduino:** `map()` + `if/else`
