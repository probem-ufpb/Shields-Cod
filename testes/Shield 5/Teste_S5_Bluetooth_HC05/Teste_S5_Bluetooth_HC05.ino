// Código para teste do módulo Bluetooth HC05 da Shield 5 do PROBEM
// Obs: Recomendo o uso dos APP's: "Serial Bluetooth Monitor" ou "Dabble" 

#include <SoftwareSerial.h>

SoftwareSerial bluetooth(10, 11); // SoftwareSerial nome(Pino_RX, Pino_TX);

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  Serial.println("\nDigite algo para enviar pelo módulo, ou receba dos dispositivos pareados.");
}

void loop() {
  if (bluetooth.available()) {
    char dadoRecebido = bluetooth.read(); 
    Serial.print(dadoRecebido);
  }

  if (Serial.available()) {
    char dadoEnviado = Serial.read();
    bluetooth.print(dadoEnviado);
  }
}