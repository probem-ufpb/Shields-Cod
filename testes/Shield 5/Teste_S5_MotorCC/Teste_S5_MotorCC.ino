// Código para teste do Motor CC da Shield 5 do PROBEM

#include <SoftPWM.h>

int INA = 7;
int INB = 12;
int ENABLE1 = 4; 

int velocidadePWM = 128;
enum Sentido { PARADO, HORARIO, ANTI_HORARIO };
Sentido sentAtual = PARADO;

void setup() {
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);

  SoftPWMBegin();
  SoftPWMSet(ENABLE1, 0); // Enable1 controla a velocidade via Software PWM.

  pararMotor(); // Motor começa parado e com velocidade igual a 0.

  Serial.begin(9600);
  exibirMenu();
}

void loop() {
  if (Serial.available() > 0) {
    String comando = Serial.readStringUntil('\n'); // Ler o comando no terminal.
    comando.trim();

    processarComando(comando); 
    
    atualizarMotor();
  }
}


void processarComando(String cmd) {
  if (cmd == "HORARIO") {
    sentAtual = HORARIO;
    Serial.println("-> Sentido: HORÁRIO");
  } 
  else if (cmd == "ANTIHORARIO") {
    sentAtual = ANTI_HORARIO;
    Serial.println("-> Sentido: ANTI-HORÁRIO");
  } 
  else if (cmd == "PARAR") {
    sentAtual = PARADO;
    Serial.println("-> Motor: PARADO");
  } 
  else if (cmd == "LENTO") {
    velocidadePWM = 64;
    Serial.println("-> Velocidade: LENTA (25%)");
  } 
  else if (cmd == "MEDIO") {
    velocidadePWM = 153; 
    Serial.println("-> Velocidade: MÉDIA (60%)");
  } 
  else if (cmd == "RAPIDO") {
    velocidadePWM = 255; 
    Serial.println("-> Velocidade: RÁPIDA (100%)");
  } 
  else {
    Serial.println("Comando errado. Digite: HORARIO, ANTIHORARIO, PARAR, LENTO, MEDIO ou RAPIDO.");
  }
}


void atualizarMotor() {
  if (sentAtual == PARADO) {
    pararMotor();
  } 
  else if (SsentAtual == HORARIO) {
    digitalWrite(INA, HIGH);
    digitalWrite(INB, LOW);
    SoftPWMSet(ENABLE1, velocidadePWM);
  } 
  else if (SsentAtual == ANTI_HORARIO) {
    digitalWrite(INA, LOW);
    digitalWrite(INB, HIGH);
    SoftPWMSet(ENABLE1, velocidadePWM); 
  }
}

void pararMotor() {
  digitalWrite(INA, LOW);
  digitalWrite(INB, LOW);
  SoftPWMSet(ENABLE1, 0); 
}

void exibirMenu() {
  Serial.println("==================================================");
  Serial.println("   Controle de motor DC com SoftPWM - Comandos ");
  Serial.println(" Sentidos: HORARIO | ANTIHORARIO | PARAR           ");
  Serial.println(" Velocidades: LENTO | MEDIO | RAPIDO              ");
  Serial.println("==================================================");
}  