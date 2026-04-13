# Externals do Giromin para Pure Data / PlugData

Escolha o arquivo correspondente ao seu sistema operacional:

| Arquivo | Sistema |
|---|---|
| `giromin-externals-mac.zip` | macOS |
| `giromin-externals-linux.zip` | Linux |
| `giromin-externals-windows.zip` | Windows |

---

## macOS

1. Extraia o zip
2. Mova a pasta extraída para:
   ```
   ~/Documents/PlugData/Externals/Giromin/
   ```
   (crie a pasta `Giromin` se não existir)
3. No PlugData: **Settings → Paths** → adicione o caminho da pasta `Giromin`
4. Reinicie o PlugData

---

## Linux

1. Extraia o zip
2. Mova a pasta extraída para:
   ```
   ~/.local/lib/pd/Giromin/
   ```
   (crie a pasta se não existir)
3. No PlugData: **Settings → Paths** → adicione o caminho da pasta `Giromin`
4. Reinicie o PlugData

---

## Windows

1. Extraia o zip
2. Mova a pasta extraída para:
   ```
   %APPDATA%\PlugData\Externals\Giromin\
   ```
   (cole esse caminho no Explorador de Arquivos — crie a pasta `Giromin` se não existir)
3. No PlugData: **Settings → Paths** → adicione o caminho da pasta `Giromin`
4. Reinicie o PlugData

---

## Verificar se funcionou

Abra o PlugData, crie um novo patch e digite `giromin.map` numa caixa de objeto.  
Se o objeto aparecer sem erro, os externals estão instalados corretamente.
