<h1 align="center"> Smart ManHole 👷⚫</h1>
A Dynamic Flow é uma empresa de tecnologia voltada para soluções urbanas inteligentes, com foco na prevenção de enchentes e no enfrentamento dos desafios crescentes relacionados à drenagem urbana. Nascemos da necessidade urgente de repensar a infraestrutura das cidades frente ao avanço da impermeabilização do solo, das mudanças climáticas e do crescimento desordenado dos centros urbanos.

## 🚨 Problema
As enchentes urbanas são um dos problemas mais recorrentes e prejudiciais enfrentados pelas cidades brasileiras e de todo o mundo. A cada temporada de chuvas intensas, vias alagadas, prejuízos materiais, interrupção de serviços essenciais e, infelizmente, perdas humanas se tornam realidade para milhares de pessoas. Mas por que esses eventos se repetem com tanta frequência e intensidade?

Uma das causas centrais está na deficiência do escoamento fluvial – ou seja, na forma como a água da chuva é direcionada e absorvida pelo ambiente urbano. Em sua condição natural, o solo realiza um papel fundamental: absorver a água das chuvas e permitir que ela escoe gradualmente para os rios e lençóis freáticos. No entanto, nas cidades, essa dinâmica é drasticamente alterada.

A intensa impermeabilização do solo urbano, causada pelo asfalto, calçadas, construções e outras infraestruturas, impede a infiltração natural da água. Como consequência, grandes volumes de água pluvial precisam ser rapidamente escoados por meio das redes de drenagem — sistema esse que, na maioria das cidades, é antigo, mal dimensionado ou insuficiente para a demanda atual.

## 👍 Solução
Nosso propósito é transformar a forma como as cidades lidam com as águas pluviais, promovendo soluções que aliam inovação tecnológica, sustentabilidade e impacto social. Acreditamos que a cidade inteligente do futuro começa com intervenções práticas e eficazes no presente – e é com esse compromisso que desenvolvemos o Smart Manhole, um bueiro inteligente criado para revolucionar a drenagem urbana.

O Smart Manhole é uma solução tecnológica desenvolvida para otimizar o escoamento de águas pluviais em áreas urbanas e prevenir alagamentos. Seu funcionamento é baseado no uso de um sistema embarcado de baixo custo, utilizando o Arduino Uno R3 como microcontrolador central.

O monitoramento do nível de água dentro do bueiro é feito por meio de um sensor ultrassônico HC-SR04, que realiza medições contínuas da distância entre a superfície da água e o topo da estrutura. Com base nesses dados, o sistema é capaz de identificar o nível de ocupação do bueiro em tempo real.

Quando o nível da água ultrapassa a marca de 3 metros, o Smart Manhole entra em modo de emergência. Nesse momento, uma comporta automatizada, acionada por um servo motor, é aberta para permitir o escoamento rápido e controlado da água excedente. Essa ação visa reduzir a pressão no sistema de drenagem e evitar transbordamentos que possam causar alagamentos em vias públicas.

Além do controle automático da comporta, a solução conta com um sistema de sinalização por LED, que indica visualmente o status do nível de água no bueiro, facilitando a supervisão local ou remota por equipes de manutenção e defesa civil.

## 💻 Detalhes Técnicos

O cérebro do projeto é um código C++ rodando em um Arduino UNO. A lógica foi pensada para garantir confiabilidade e evitar acionamentos desnecessários da comporta.

### Leitura Estabilizada do Sensor

Para obter uma medição precisa do nível da água e evitar oscilações causadas por movimentos na água ou falhas pontuais do sensor, o sistema não confia em uma única leitura. A função `lerDistanciaMedia()` realiza 10 medições em rápida sucessão.

1. **Acionamento do Sensor:** Um pulso de 10 microssegundos é enviado ao pino `TRIG` do sensor HC-SR04.

2. **Escuta do Eco:** O sistema mede o tempo que o pino `ECHO` leva para retornar um sinal, usando a função `pulseIn()`. Um `timeout` é definido para descartar leituras inválidas caso o eco não retorne.

3. **Cálculo e Média:** A duração do pulso é convertida para centímetros. As leituras válidas são somadas e, ao final, a média é calculada. Isso resulta em um valor de distância muito mais estável.

4. **Cálculo do Nível:** O nível da água é determinado pela fórmula: `nível = altura total do bueiro - distância média medida`.

### Controle da Comporta com Histerese

Para impedir que a comporta abra e feche repetidamente quando o nível da água está próximo do limite, foi implementado um sistema de **histerese**. Isso cria duas faixas de acionamento distintas:

* **Limite para Abrir (`LIMITE_ABRIR` = 300 cm):** A comporta **só abre** se estiver fechada e o nível da água atingir ou ultrapassar os 3 metros.

* **Limite para Fechar (`LIMITE_FECHAR` = 290 cm):** Uma vez aberta, a comporta **só fecha** se o nível da água baixar para 2.9 metros ou menos.

Essa diferença de 10 cm entre os limites de abertura e fechamento garante que o servo motor não seja sobrecarregado, aumentando a vida útil do componente e a estabilidade do sistema.

### Gerenciamento de Estado

O sistema utiliza variáveis de controle para saber o estado atual da comporta (`comportaAberta`) e para garantir que a posição inicial seja definida corretamente na primeira vez que o sistema é ligado (`estadoInicializado`). A lógica principal é executada a cada segundo, conforme definido em `INTERVALO_LEITURA`, usando a função `millis()` para não travar o processador com `delay()`. Os LEDs verde e vermelho fornecem um feedback visual imediato, indicando se o nível da água está em uma faixa segura (verde) ou de risco (vermelho).

## ▶️ Requisitos Funcionais
1. O sistema deve fazer leituras da distancia da profunidade do bueiro utilizando o sensor ultrassonico
2. O sistema deve fazer leituras para indicar o nivel da agua presente no bueiro
3. O sistema deve validar as leituras para que estejam no parametro adequado levando em consideração a profunidade do bueiro
4. O sistema deve abrir a comporta utilizando o servo motor em caso de niveis de agua estarem maiores que 3m
5. O sistema deve manter a comporta fechada utilizando o servo motor em caso de niveis de agua estarem menores que 2.9m
6. O sistema deve manter o LED verde aceso em caso o nivel de agua for adequado
7. O sisema deve manter o LED Vermelho aceso em caso o nivel de agua nao for adequado

## 🛠️ Material
- 01 Arduino UNO = Para controlar o sistema
- 01 Breadboard = Para montagem do circuito
- Cabos Jumper = Para realizar as conexões na breadboard
- 02 Resistores = 220 Ohms para os Leds
- 01 LED Verde 🟢 = Indicar que o status do bueiro está dentro dos parâmetros
- 01 LED Vermelho 🔴 = Indicar que o bueiro está a ponto de alagar
- Sensor HC-SR04
- Servo = Controle da comporta


## 🔗 Como acessar o projeto
Para acessar o diagrama do projeto [clique aqui](https://wokwi.com/projects/432884789896311809)

Link para o vídeo sobre o projeto: [clique aqui](https://www.youtube.com/watch?v=_sHam_btzB8)

## 🧑‍💻 Tecnologias utilizadas
- Linguagem de programação: C
- Microcontrolador: Arduino R3 UNO
- Prototipagem: Wokwi
- Repositório Remoto: Github


## 👷‍♂️ Integrantes
<table>
  <tr><th><span>Integrantes</span></th><th><span>Tarefas</span></th></tr>
    <tr>
    <td align = "center">
      <img src="https://avatars.githubusercontent.com/u/105310868?v=4" width="100px" alt= "Guilherme Godoy Profile Image"/><p><a href = "https://github.com/godooooy">Guilherme Godoy </a></p><span><b>RM:564417</b></span>
    </td>
    <td>
      <ul>
        <li>Montagem Protoboard</li>
        <li>Setup dos sensores e servo</li>
      </ul>
    </td>
  </tr>
    <tr>
    <td align = "center">
      <img src="https://avatars.githubusercontent.com/u/101485201?v=4" width="100px" alt= "Pedro Lucas Profile Image"/><p><a href = "https://github.com/pedroviscz">Pedro Lucas Almeida</a></p><span><b>RM:566256</b></span>
    </td>
    <td>
      <ul>
        <li>Criar estrutura condicionais</li>
        <li>Revisão e melhoria de codigo</li>
      </ul>
    </td>
  </tr>
</table>
