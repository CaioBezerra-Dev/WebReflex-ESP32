# ⚡ WebReflex-ESP32 — Jogo de Reação com ESP32 🌐

Um mini jogo de reflexo para ESP32 com interface web e acesso remoto via Cloudflare Tunnel.  
Desafie seus reflexos e compartilhe o link com seus amigos! 🏆

---

## 📦 Instalação Rápida

Siga estes passos mínimos para rodar o projeto localmente e expor via Cloudflare (modo rápido, sem login).

### 1️⃣ Configure sua rede Wi-Fi

No código, edite as linhas:

```cpp
const char* ssid = "NOME_DA_REDE";
const char* password = "SENHA_DA_REDE";
Depois, abra o projeto no Arduino IDE, selecione a placa ESP32 correta e faça o upload.

2️⃣ Verifique o IP no Monitor Serial
Abra o monitor serial em 115200 baud e veja algo como:

bash
Copiar código
Conectando-se a FRAN...
WiFi conectado!
IP: 192.168.1.27
Servidor Web iniciado com sucesso.
Acesse localmente no navegador:

cpp
Copiar código
http://192.168.1.27
3️⃣ 🌍 Acesso remoto rápido (sem login)
No computador da mesma rede, instale o cloudflared e execute:

bash
Copiar código
# Apague configuração antiga (caso exista)
rm -rf ~/.cloudflared

# Crie pasta de trabalho
mkdir -p ~/.cloudflared && cd ~/.cloudflared

# Inicie túnel rápido (gera link .trycloudflare.com)
cloudflared tunnel --url http://192.168.1.27
Após alguns segundos, aparecerá algo como:

bash
Copiar código
Your quick Tunnel has been created! Visit it at:
https://example-tunnel.trycloudflare.com
➡️ Esse é o link público temporário para acessar sua ESP32 enquanto o comando estiver rodando.

🚀 Funcionalidades
Interface web responsiva (HTML + JS)

Medição precisa do tempo de reação (ms)

Ranking com os 5 melhores tempos

LED vermelho (aguarde) / LED verde (reaja)

Acesso remoto opcional via Cloudflare Tunnel

🧩 Materiais Necessários
Componente	Quantidade	Observação
ESP32 DevKit	1	—
LED Verde	1	Pino D23 (GPIO 23)
LED Vermelho	1	Pino D4 (GPIO 4)
Botão Pousador	1	Pino D5 (GPIO 5)
Resistores	2	220Ω (para LEDs)
Jumpers	—	—
Protoboard	—	—

Ajuste os pinos no código se sua montagem for diferente.

💻 Como Jogar
Conecte a ESP32 à energia e envie o sketch.

Abra o monitor serial (115200) e aguarde a conexão Wi-Fi.

Acesse o IP mostrado (ou o link do túnel).

Digite seu nome → clique em INICIAR JOGO.

Espere o LED verde → pressione o botão o mais rápido possível!

Veja seu tempo e tente bater o recorde.

⚠️ Observações sobre o Cloudflare Tunnel
O modo “quick tunnel” (cloudflared tunnel --url ...) cria um subdomínio temporário *.trycloudflare.com.
Ele funciona sem login, mas o link muda toda vez que você reinicia o comando.

Se quiser um link fixo e persistente, é possível criar um túnel autenticado na sua conta Cloudflare com:

bash
Copiar código
cloudflared login
cloudflared tunnel create nome-do-tunel
🧪 Tecnologias Utilizadas
⚙️ C++ (Arduino Core para ESP32)

📡 WiFi.h, WebServer.h

💡 HTML / CSS / JavaScript (frontend)

🌩️ Cloudflare Tunnel (opcional)

📸 Sugestão: Demonstrações
Inclua imagens/screenshots com:

Tela do jogo no navegador

Montagem do circuito

Monitor serial mostrando o IP

🧾 Licença & Créditos
Autor: Caio Breno de Souza Bezerra
Versão: 1.0
Licença: MIT

“Treine seus reflexos com a força da ESP32!” ⚡

<p align="center"> Feito com ❤️ e muita curiosidade IoT 🧠 </p> ```