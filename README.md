<h1 align="center">⚡ WebReflex-ESP32 — Jogo de Reação com ESP32 🌐</h1>

<p align="center">
Um mini jogo de <strong>reflexo</strong> para <strong>ESP32</strong> com interface web e acesso remoto via <strong>Cloudflare Tunnel</strong>.  
Desafie seus reflexos e compartilhe o link com seus amigos! 🏆
</p>

---

## 📦 Instalação rápida

Siga estes passos mínimos para rodar o projeto localmente e expor via Cloudflare (modo rápido, sem login).

1. Edite o sketch e configure sua rede Wi-Fi:
```cpp
const char* ssid = "NOME_DA_REDE";
const char* password = "SENHA_DA_REDE";
Abra o projeto no Arduino IDE, selecione a placa ESP32 correta e faça o upload.

Abra o Monitor Serial em 115200 baud para ver o IP atribuído:

arduino
Copiar código
Conectando-se a FRAN...
WiFi conectado!
IP: 192.168.1.27
Servidor Web iniciado com sucesso.
Acesse localmente:

cpp
Copiar código
http://192.168.1.27
(Opcional) Para acesso remoto rápido, no computador da mesma rede instale cloudflared e rode:

bash
Copiar código
# Apague configuração antiga (caso exista)
rm -rf ~/.cloudflared

# Crie pasta de trabalho
mkdir -p ~/.cloudflared && cd ~/.cloudflared

# Inicie túnel rápido (gera link .trycloudflare.com)
cloudflared tunnel --url http://192.168.1.27
A saída mostrará algo como:

nginx
Copiar código
Your quick Tunnel has been created! Visit it at:
https://example-tunnel.trycloudflare.com
O link funciona enquanto o processo estiver rodando no terminal.

🚀 Funcionalidades
Interface web responsiva (HTML + JS)

Medição precisa do tempo de reação (ms)

Ranking com os 5 melhores tempos

LED vermelho (aguarde) / LED verde (reaja)

Acesso remoto opcional via Cloudflare Tunnel

🧩 Materiais necessários
ESP32 (DevKit)

LED verde

LED vermelho

Botão pousador

Resistores apropriados (ex.: 220Ω para LEDs)

Jumpers e protoboard

🔌 Conexões (padrão no código)
Componente	Pino ESP32
Botão	D5 (GPIO 5)
LED Verde	D23 (GPIO 23)
LED Vermelho	D4 (GPIO 4)

Ajuste os pinos no código se sua montagem for diferente.

💻 Como usar
Conecte a ESP32 à energia e faça upload do sketch via Arduino IDE.

Abra o monitor serial (115200) e aguarde conexão Wi-Fi.

Abra o IP mostrado no navegador.

Na página web: digite seu nome → clique INICIAR JOGO → espere o LED verde → pressione o botão o mais rápido possível.

Seu tempo será exibido e salvo no ranking.

⚠️ Observações sobre o Cloudflare Tunnel
O modo “quick tunnel” (cloudflared tunnel --url ...) gera um subdomínio .trycloudflare.com temporário. Ele funciona sem autenticação, mas o link muda se você reiniciar o processo.

Se quiser link fixo e mais controle, é possível criar um túnel nomeado autenticado via conta Cloudflare (requer cloudflared login e criação de túnel na conta).

🧪 Tecnologias
C++ (Arduino Core para ESP32)

WiFi.h, WebServer.h

HTML / CSS / JavaScript para frontend

Cloudflare Tunnel (opcional)

📸 Sugestão: demonstrativos
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