// Código para teste do Servo Motor da Shield 5 do PROBEM

#include <Servo.h>

Servo Serv;  

void setup() {
  Serv.attach(8);  
}

void loop() {
  // Move o servo de 0 até os 180 graus
  for (int angulo = 0; angulo <= 180; angulo += 1) { 
    Serv.write(angulo);              
    delay(15);                           
  }
  delay(500);
  
  // Move o servo de 180 a 0 graus
  for (int angulo = 180; angulo >= 0; angulo -= 1) { 
    Serv.write(angulo);              
    delay(15);                           
  }
  delay(500);
}