<h1 align="center">⚡ Jogo de Reação com ESP32 + Servidor Web 🌐</h1>

<p align="center">
Um mini jogo de <b>reflexo</b> desenvolvido para <b>ESP32</b>, com interface web e acesso remoto via <b>Cloudflare Tunnel</b>.
<br>
Desafie seus reflexos e veja quem é o mais rápido da turma! 🏆
</p>

---

## 🚀 Funcionalidades

✨ Interface web responsiva (HTML + JS)  
🧠 Cálculo preciso do tempo de reação  
🏅 Ranking automático de melhores tempos  
🔴 LED vermelho → aguarde  
🟢 LED verde → reaja!  
⚙️ Servidor HTTP embarcado no ESP32  
☁️ Acesso remoto opcional via Cloudflare Tunnel  

---

## 🧩 Materiais Necessários

| Componente     | Quantidade | Observação         |
|----------------|------------:|--------------------|
| ESP32          | 1           | Modelo DevKit V1   |
| LED vermelho   | 1           | Indicador de espera|
| LED verde      | 1           | Indicador de reação|
| Botão (push)   | 1           | Entrada do jogador |
| Jumpers        | —           | Conexões diversas  |
| Protoboard     | —           | Montagem rápida    |

---

## 🔌 Esquema de Conexão

| Componente    | Pino ESP32 |
|---------------|------------:|
| Botão         | D5          |
| LED Verde     | D23         |
| LED Vermelho  | D4          |

---

## 💻 Configuração do Código

Antes de enviar o código à ESP32, edite suas credenciais Wi-Fi no sketch:

```cpp
const char* ssid = "NOME_DA_REDE";
const char* password = "SENHA_DA_REDE";
Após o upload, abra o Monitor Serial (115200 baud) — você verá algo como:

arduino
Copiar código
Conectando-se a FRAN...
WiFi conectado!
IP: 192.168.1.27
Servidor Web iniciado com sucesso.
Agora é só acessar no navegador:

cpp
Copiar código
http://192.168.1.27
🌍 Acesso Remoto com Cloudflare Tunnel (sem login)
Quer acessar o jogo de qualquer lugar? Use o Cloudflare Tunnel — rápido, gratuito e sem precisar de domínio. No computador da mesma rede execute:

bash
Copiar código
# 1️⃣ Apague qualquer configuração antiga (opcional)
rm -rf ~/.cloudflared

# 2️⃣ Crie um diretório novo e entre nele
mkdir -p ~/.cloudflared && cd ~/.cloudflared

# 3️⃣ Inicie o túnel rápido (gera link .trycloudflare.com)
cloudflared tunnel --url http://192.168.1.27
Após alguns segundos aparecerá algo como:

nginx
Copiar código
Your quick Tunnel has been created! Visit it at:
https://example-tunnel.trycloudflare.com
➡️ Esse é o link público para acessar sua ESP32 enquanto o comando estiver rodando no terminal.

🕹️ Como Jogar
Conecte-se à rede Wi-Fi configurada.

Acesse o IP local ou o link do túnel Cloudflare.

Digite seu nome e clique em INICIAR JOGO.

Espere o LED verde acender.

Pressione o botão o mais rápido possível!

Veja seu tempo e tente bater o recorde.

📸 Demonstração
(adicione aqui prints da interface ou fotos da montagem)

Exemplos sugeridos:

Tela inicial do jogo

Ranking em tempo real

LEDs e botão conectados na ESP32

🧠 Tecnologias Utilizadas
⚙️ C++ (Arduino Core)

📡 WiFi.h e WebServer.h

🌩️ Cloudflare Tunnel (opcional)

💡 HTML / JavaScript (frontend)

🧪 Créditos
Autor: Caio Breno de Souza Bezerra
Versão: 1.0
Licença: MIT

“Treine seus reflexos com a força da ESP32!” ⚡

<p align="center">Feito com ❤️ e <b>muita curiosidade IoT</b> 🧠</p> ```