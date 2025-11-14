<h1 align="center"> Jogo de Reação com ESP32 + Servidor Web </h1>

<p align="center">
Um mini jogo de <b>reflexo</b> desenvolvido para <b>ESP32</b>, com interface web e acesso remoto via <b>Cloudflare Tunnel</b>.
<br>
Desafie seus reflexos e veja quem é o mais rápido da turma! 
</p>

---

## Funcionalidades

- Interface web responsiva (HTML + JS)  
- Cálculo preciso do tempo de reação  
- Ranking automático de melhores tempos  
- LED vermelho → aguarde  
- LED verde → reaja!  
- Servidor HTTP embarcado no ESP32  
- Acesso remoto opcional via Cloudflare Tunnel  

---

## Materiais Necessários

| Componente     | Quantidade | Observação         |
|----------------|------------:|--------------------|
| ESP32          | 1           | Modelo DevKit V1   |
| LED vermelho   | 1           | Indicador de espera|
| LED verde      | 1           | Indicador de reação|
| Botão (push)   | 1           | Entrada do jogador |
| Jumpers        | —           | Conexões diversas  |
| Protoboard     | —           | Montagem rápida    |

---

## Esquema de Conexão

| Componente    | Pino ESP32 |
|---------------|------------:|
| Botão         | D5          |
| LED Verde     | D23         |
| LED Vermelho  | D4          |

---

## Configuração do Código

Antes de enviar o código à ESP32, edite suas credenciais Wi-Fi no sketch:

```cpp
const char* ssid = "NOME_DA_REDE";
const char* password = "SENHA_DA_REDE";
```

Acesso Remoto com Cloudflare Tunnel (sem login)
Quer acessar o jogo de qualquer lugar? Use o Cloudflare Tunnel — rápido, gratuito e sem precisar de domínio. No computador da mesma rede execute:

# 1️⃣ Apague qualquer configuração antiga (opcional)
```cpp
rm -rf ~/.cloudflared
```

# 2️⃣ Crie um diretório novo e entre nele
```cpp
mkdir -p ~/.cloudflared && cd ~/.cloudflared
```

# 3️⃣ Inicie o túnel rápido (gera link .trycloudflare.com)
```cpp
cloudflared tunnel --url http://<IP.ESP32>
```

Após alguns segundos aparecerá algo como:

Exemplo:
Your quick Tunnel has been created! Visit it at:
https://example-tunnel.trycloudflare.com
➡️ Esse é o link público para acessar sua ESP32 enquanto o comando estiver rodando no terminal.

---

## Como Jogar

Conecte-se à rede Wi-Fi configurada.

Acesse o IP local ou o link do túnel Cloudflare.

Digite seu nome e clique em INICIAR JOGO.

Espere o LED verde acender.

Pressione o botão o mais rápido possível!

Veja seu tempo e tente bater o recorde.

---

## Tecnologias Utilizadas

- C++ (Arduino Core)

- WiFi.h e WebServer.h

- Cloudflare Tunnel (opcional)

- HTML / JavaScript (frontend)

## Créditos

Autor: Caio Breno de Souza Bezerra
Versão: 1.0

“Treine seus reflexos com a força da ESP32!” ⚡

<p align="center">Feito com ❤️ e <b>muita curiosidade IoT</b> 🧠</p> 