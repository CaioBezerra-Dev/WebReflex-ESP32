#include <WiFi.h>
#include <WebServer.h>

// ===================== CONFIGURAÇÃO WI-FI =====================
// *** Mantenha Wokwi-GUEST para a simulação ***
const char* ssid = ""; 
const char* password = ""; 
WebServer server(80); // Servidor HTTP na porta padrão

// ===================== PINOS =====================
const int buttonPin = 5;
const int ledVerde = 23;
const int ledVermelho = 4;

// ===================== VARIÁVEIS DO JOGO =====================
unsigned long startTime = 0;
unsigned long reactionTime = 0; // Armazena o tempo de reação em milissegundos
bool esperandoReacao = false;
unsigned long lastButtonTime = 0;
const unsigned long debounceDelay = 20000; // 20 ms em microssegundos (20000)

// ===================== VARIÁVEIS DO SERVIDOR E RANKING =====================
#define MAX_RANKING 5
String nomesRanking[MAX_RANKING];
long temposRanking[MAX_RANKING];
int rankingCount = 0;

bool jogoIniciadoPorWeb = false; // Sinaliza que a rodada foi solicitada pelo navegador
String jogadorAtual = ""; // Armazena o nome do jogador da rodada atual

// ===================== FUNÇÕES DE RANKING =====================

/**
 * @brief Adiciona o novo resultado na lista e reordena o ranking.
 */
void updateRankingList(String nome, long tempo) {
    // 1. Encontra a posição correta (inserção ordenada)
    int i = rankingCount;
    if (i < MAX_RANKING) {
        rankingCount++;
    } else {
        // Se o ranking estiver cheio, ignora se o tempo for pior que o pior tempo no ranking
        if (tempo >= temposRanking[MAX_RANKING - 1]) {
            return;
        }
        i = MAX_RANKING - 1;
    }

    // 2. Desloca os elementos maiores para baixo (para abrir espaço)
    while (i > 0 && temposRanking[i-1] > tempo) {
        temposRanking[i] = temposRanking[i-1];
        nomesRanking[i] = nomesRanking[i-1];
        i--;
    }

    // 3. Insere o novo resultado
    temposRanking[i] = tempo;
    nomesRanking[i] = nome;
}

// ===================== FUNÇÕES DO SERVIDOR WEB =====================

/**
 * @brief Devolve a página principal HTML/JS.
 */
void handleRoot() {
  String html = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <head>
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <title>Jogo de Reação ESP32</title>
      <style>
          body { font-family: sans-serif; text-align: center; background-color: #f4f4f9; color: #333; }
          .container { max-width: 450px; margin: 50px auto; padding: 25px; background-color: #fff; border-radius: 12px; box-shadow: 0 4px 8px rgba(0,0,0,0.1); }
          h2 { color: #007bff; margin-bottom: 20px; }
          input[type="text"], button { padding: 12px; margin: 8px 0; width: 100%; box-sizing: border-box; border-radius: 6px; border: 1px solid #ccc; font-size: 16px; }
          button { background-color: #28a745; color: white; border: none; cursor: pointer; transition: background-color 0.3s; }
          button:hover { background-color: #218838; }
          #status { margin: 15px 0; font-weight: bold; padding: 10px; border-radius: 6px; }
          .pronto { background-color: #e9ecef; color: #333; }
          .espera { background-color: #fff3cd; color: #856404; }
          .finalizado { background-color: #d4edda; color: #155724; }
          h3 { margin-top: 30px; color: #6c757d; }
          #rankingTable { width: 100%; border-collapse: collapse; margin-top: 15px; }
          #rankingTable th, #rankingTable td { border: 1px solid #ddd; padding: 10px; }
          #rankingTable th { background-color: #f8f9fa; color: #333; }
      </style>
  </head>
  <body>
      <div class="container">
          <h2>Jogo de Reacao</h2>
          <form id="startForm">
              <label for="nome" style="display: block; text-align: left; margin-bottom: 5px;">Seu Nome:</label>
              <input type="text" id="nome" name="nome" placeholder="Digite seu nome aqui" required><br>
              <button type="submit" id="startButton">INICIAR JOGO</button>
          </form>
          <p id="status" class="pronto">Pronto. Digite seu nome e clique em INICIAR.</p>
          
          <h3>Ranking de Melhores Tempos</h3>
          <table id="rankingTable">
              <thead><tr><th>Pos.</th><th>Nome</th><th>Tempo (ms)</th></tr></thead>
              <tbody id="rankingBody"></tbody>
          </table>
      </div>

      <script>
          const form = document.getElementById('startForm');
          const nomeInput = document.getElementById('nome');
          const status = document.getElementById('status');
          const rankingBody = document.getElementById('rankingBody');
          const startButton = document.getElementById('startButton');

          function setStatus(text, className) {
              status.textContent = text;
              status.className = ''; // Limpa classes
              status.classList.add(className);
          }

          // Função para iniciar o jogo na ESP32
          form.addEventListener('submit', function(e) {
              e.preventDefault();
              const nome = nomeInput.value;
              if (nome.trim() === "") {
                  alert("Por favor, digite seu nome.");
                  return;
              }

              setStatus("Jogo iniciado! Olhe para o LED. Prepare-se para reagir...", 'espera');
              startButton.disabled = true; // Desabilita o botão enquanto o jogo está rolando
              
              // Envia o nome e o comando de iniciar para a ESP32
              fetch('/iniciar?nome=' + encodeURIComponent(nome), { method: 'POST' })
                  .catch(error => {
                      console.error('Erro ao iniciar:', error);
                      setStatus("Erro de conexão. Tente novamente.", 'pronto');
                      startButton.disabled = false;
                  });
          });
          
          // Função para atualizar o ranking
          function updateRanking() {
              fetch('/ranking')
                  .then(response => response.json())
                  .then(data => {
                      rankingBody.innerHTML = '';
                      data.forEach((item, index) => {
                          const row = rankingBody.insertRow();
                          row.insertCell(0).textContent = index + 1;
                          row.insertCell(1).textContent = item.nome;
                          row.insertCell(2).textContent = item.tempo;
                      });
                  })
                  .catch(error => console.error('Erro ao carregar ranking:', error));
          }

          // Função para checar o status do jogo (e ver se já terminou)
          function checkGameStatus() {
              fetch('/status')
                  .then(response => response.json())
                  .then(data => {
                      if (data.status === "finalizado") {
                          setStatus(`Rodada finalizada! Seu tempo: ${data.tempo} ms.`, 'finalizado');
                          nomeInput.value = data.nome; 
                          startButton.disabled = false;
                          updateRanking();
                      } else if (data.status === "pronto") {
                          if (startButton.disabled) {
                              setStatus("Opa! Jogo pronto. Clique em INICIAR.", 'pronto');
                              startButton.disabled = false;
                          }
                      } 
                      // Se o status for "jogando" ou "esperando", o status ja foi atualizado no form.submit
                  })
                  .catch(error => console.error('Erro ao checar status:', error));
          }

          // Atualiza o ranking e o status periodicamente (a cada 1 segundo)
          setInterval(checkGameStatus, 1000);
          updateRanking(); // Carrega o ranking inicial
      </script>
  </body>
  </html>
  )rawliteral";
  server.send(200, "text/html", html);
}

/**
 * @brief Manipula a requisição POST para iniciar o jogo.
 */
void handleIniciar() {
  if (server.hasArg("nome")) {
    jogadorAtual = server.arg("nome");
    jogoIniciadoPorWeb = true; // Sinaliza para o loop() iniciar a rodada
    reactionTime = 0; // Zera o tempo para uma nova rodada
    server.send(200, "text/plain", "OK");
  } else {
    server.send(400, "text/plain", "Erro: Nome nao fornecido.");
  }
}

/**
 * @brief Devolve a lista de ranking em formato JSON.
 */
void handleRanking() {
  String json = "[";
  for (int i = 0; i < rankingCount; i++) {
    if (i > 0) json += ",";
    json += "{\"nome\":\"" + nomesRanking[i] + "\",\"tempo\":" + String(temposRanking[i]) + "}";
  }
  json += "]";
  server.send(200, "application/json", json);
}

/**
 * @brief Devolve o status atual do jogo para o JavaScript.
 */
void handleStatus() {
    String statusJson = "";
    
    if (!esperandoReacao && reactionTime > 0) {
        // Jogo acabou e o resultado está pronto para ser lido pelo navegador
        statusJson = "{\"status\":\"finalizado\", \"nome\":\"" + jogadorAtual + "\", \"tempo\":" + String(reactionTime) + "}";
        reactionTime = 0; // Zera para indicar que o resultado já foi enviado
    } else if (esperandoReacao) {
        // Jogo em andamento (esperando o LED acender ou o botão ser pressionado)
        statusJson = "{\"status\":\"jogando\"}";
    } else {
        // ESP32 está em repouso
        statusJson = "{\"status\":\"pronto\"}";
    }

    server.send(200, "application/json", statusJson);
}

// ===================== FUNÇÕES ARDUINO PADRÃO =====================

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);

  Serial.begin(115200);

  // Inicializa LED Vermelho Aceso
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledVermelho, HIGH); 
  randomSeed(analogRead(0));

  // === Conexão Wi-Fi ===
  Serial.print("Conectando-se a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  // Imprime pontos enquanto tenta conectar (com limite de 20 tentativas)
  int tentativas = 0;
  while (WiFi.status() != WL_CONNECTED && tentativas < 20) { 
    delay(500);
    Serial.print(".");
    tentativas++;
  }

  // A MUDANÇA ESTÁ AQUI: Inicialização do servidor apenas se a conexão for bem-sucedida.
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi conectado!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    // === Configuração e Inicialização do Servidor Web ===
    server.on("/", HTTP_GET, handleRoot);      
    server.on("/iniciar", HTTP_POST, handleIniciar);
    server.on("/ranking", HTTP_GET, handleRanking);
    server.on("/status", HTTP_GET, handleStatus);

    server.begin(); 
    Serial.println("Servidor Web iniciado com sucesso. Procure o link do IoT Gateway!"); // Mensagem de sucesso revisada
    
  } else {
    Serial.println("\nFalha na conexao. Verifique o SSID e a senha.");
    // Deixa os LEDs apagados para sinalizar falha no setup
    digitalWrite(ledVermelho, LOW); 
    digitalWrite(ledVerde, LOW);
  }
}

void loop() {
  // Apenas lide com clientes se o WiFi estiver conectado.
  if (WiFi.status() == WL_CONNECTED) {
    server.handleClient(); // Essencial: processa requisições HTTP do navegador
  }

  static unsigned long waitStart = 0;
  static unsigned long waitDelay = 0;

  // 1. Inicia Rodada - Apenas se o comando veio da Web e não há jogo em andamento
  if (jogoIniciadoPorWeb && !esperandoReacao) {
    waitStart = micros();
    waitDelay = random(2000000, 5000000); // Espera de 2 a 5 segundos (micros)
    esperandoReacao = true;
    jogoIniciadoPorWeb = false; 
    
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(ledVerde, LOW);
    startTime = 0;
  }

  // 2. Acende Verde após tempo aleatório (Lógica Não Bloqueante)
  if (esperandoReacao && micros() - waitStart >= waitDelay && startTime == 0) {
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledVerde, HIGH);
    startTime = micros(); // Marca o exato momento de ligar o LED (Início da Reação)
    Serial.println("LED VERDE ACESO! Reaja!");
  }

  // 3. Lê o botão e finaliza a rodada (Alta Precisão)
  if (startTime > 0) {
    int buttonState = digitalRead(buttonPin);
    
    // Verifica se o botão foi pressionado (LOW, por causa do PULLUP) e se passou do debounce
    if (buttonState == LOW && (micros() - lastButtonTime) > debounceDelay) {
      lastButtonTime = micros();
      
      // Calcula o tempo de reação em ms
      unsigned long tempoMs = (micros() - startTime) / 1000; 
      
      // Salva o tempo na variável global para o /status ler
      reactionTime = tempoMs;
      
      // Salva o resultado no ranking
      updateRankingList(jogadorAtual, reactionTime);
      
      // Reseta estado do jogo
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledVermelho, HIGH);
      esperandoReacao = false;
      startTime = 0;
      
      Serial.print("Reacao medida: ");
      Serial.print(reactionTime);
      Serial.println(" ms.");

      // Pausa curta para a experiência do usuário (Led Vermelho aceso por 1s)
      delay(1000); 
    }
  }
}