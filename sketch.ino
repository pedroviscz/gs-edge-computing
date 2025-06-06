#include <Servo.h>

// ====== Definições de Pinos ======
#define PINO_TRIG 2
#define PINO_ECHO 3
#define LED_VERDE 5
#define LED_VERMELHO 6
#define PINO_SERVO 9

// ====== Configurações ======
unsigned int ALTURA_BUEIRO = 400; // cm - 4m
unsigned int LIMITE_ABRIR = 300; // cm - a comporta só fecha se o nível da água é 3m
unsigned int LIMITE_FECHAR = 290; // cm - a comporta só abre quando o nível da água é menor que 2.9m
unsigned int ANGULO_ABERTO = 90;  // grau do servo
unsigned int ANGULO_FECHADO = 0;   // grau do servo

unsigned long INTERVALO_LEITURA = 1000; // 1 segundo
unsigned int NUM_LEITURAS = 10; //Contador leituras
unsigned int TIMEOUT_US = 15000; // 20 ms
unsigned int DELAY_ENTRE_LEITURAS_MS = 50;

Servo comporta;
bool comportaAberta = false;
bool estadoInicializado = false;
unsigned long ultimoTempo = 0;

void setup() {
  //inicia comunicação serial
  Serial.begin(9600);
  // define os modos dos pinos do sensor, LEDs e servo.
  pinMode(PINO_TRIG, OUTPUT);
  pinMode(PINO_ECHO, INPUT);
  
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  // anexa o servo ao pino PINO_SERVO.
  comporta.attach(PINO_SERVO);
  // o sistema inicia com a comporta fechada
  comporta.write(ANGULO_FECHADO);
  // digitalWrite(LED_VERDE, HIGH);
  // digitalWrite(LED_VERMELHO, LOW);
}

void loop() {
  unsigned long agora = millis();

  // a cada 1s o loop se repete
  if (agora - ultimoTempo >= INTERVALO_LEITURA) {
    ultimoTempo = agora;

    float distanciaMedia = lerDistanciaMedia();
    float nivelAgua = max(0.0f, ALTURA_BUEIRO - distanciaMedia);

    Serial.print("Distancia media: ");
    Serial.print(distanciaMedia);
    Serial.print(" cm    |  Nivel da agua: ");
    Serial.print(nivelAgua);
    Serial.println(" cm");

    if (!estadoInicializado) {
      sincronizarEstadoInicial(nivelAgua);
    } else {
      controlarHisterese(nivelAgua);
    }
  }
}

float lerDistanciaMedia() {
  int leiturasValidas = 0;
  float soma = 0;
  int tentativas = 0;
  // enquanto houver menos de 10 leituras válidas E menos de 20 tentativas o while roda
  // se 10 leituras forem válidas o while já para
  while (leiturasValidas < NUM_LEITURAS && tentativas < NUM_LEITURAS * 2) {
    tentativas++;

    // Pulso TRIG
    // garante que o TRIG esteja em nível BAIXO antes de enviar o pulso
    digitalWrite(PINO_TRIG, LOW);
    // aguarda 2 microssegundos para estabilizar.
    delayMicroseconds(2);
    // envia um pulso de 10 microssegundos em nível ALTO no pino TRIG.
    digitalWrite(PINO_TRIG, HIGH);
    delayMicroseconds(10);
    // finaliza o pulso, voltando o TRIG ao nível BAIXO.
    digitalWrite(PINO_TRIG, LOW);

    // aguarda o pino ECHO ficar em nível ALTO.
    // quando fica ALTO, inicia a contagem de tempo.
    // quando o ECHO volta a ser BAIXO, a contagem para.
    // se o eco não voltar em 15ms, pulseIn retorna 0, indicando falha.
    unsigned int duracao = pulseIn(PINO_ECHO, HIGH, TIMEOUT_US);

    // se a duração for maior que zero (falha),
    // calcula a distância e incrementa na soma total
    if (duracao > 0) {
      // (duração da ida e volta do pulso * velocidade do som) / 2 (ida e volta)
      float dist = duracao * 0.0343f / 2.0f;
      soma += dist;
      leiturasValidas++;
    }
    // para tudo por 50ms antes da próxima 
    delay(DELAY_ENTRE_LEITURAS_MS);
  }
  if (leiturasValidas == 0) return ALTURA_BUEIRO; // valor seguro (nível zero)
  return soma / leiturasValidas;
}

// só roda na primeira execução para iniciar o sistema
void sincronizarEstadoInicial(float nivel) {
  if (nivel >= LIMITE_ABRIR) {
    abrirComporta();
  } else {
    fecharComporta();
  }
  estadoInicializado = true;
}

// essa função controla o limite de abrir e fechar
// é necessário implementar a histerese para evitar
// abertura e fechamento constante da comporta
void controlarHisterese(float nivel) {
  if (!comportaAberta && nivel >= LIMITE_ABRIR) {
    abrirComporta();
  } else if (comportaAberta && nivel <= LIMITE_FECHAR) {
    fecharComporta();
  }
}

// funções para comporta
void abrirComporta() {
  comporta.write(ANGULO_ABERTO);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_VERMELHO, HIGH);
  comportaAberta = true;
}

void fecharComporta() {
  comporta.write(ANGULO_FECHADO);
  digitalWrite(LED_VERDE, HIGH);
  digitalWrite(LED_VERMELHO, LOW);
  comportaAberta = false;
}