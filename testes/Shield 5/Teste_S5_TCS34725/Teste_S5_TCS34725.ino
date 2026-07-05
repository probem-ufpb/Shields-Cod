// Código para teste do sensor de cor TCS34725 da Shield 5 do PROBEM

#include "Wire.h"
#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725(
  TCS34725_INTEGRATIONTIME_600MS, // Tempo de integração (Quanto maior: Mais preciso, porém, mais lento.) 
  TCS34725_GAIN_1X); // Ganho de luz feito eletronicamente (1X se o ambiente for iluminado, se for escuro, pode-se aumentar.)

void setup(void) {
  Serial.begin(9600);
  
  if (tcs.begin()) {
    Serial.println("Sensor encontrado");
  } else {
    Serial.println("Sensor não encontrado");
    while(1);
  }
}

void loop(void) {
  uint16_t r, g, b, c;

  tcs.getRawData(&r, &g, &b, &c); // Lê os valores brutos de Vermelho (R), Verde (G), Azul (B) e Clear (C - luminosidade geral)

  uint16_t colorTemp = tcs.calculateColorTemperature(r, g, b); // Calcula a temperatura de cor (em Kelvin)

  Serial.print("Vermelho (R): "); Serial.print(r);
  Serial.print(" | Verde (G): "); Serial.print(g);
  Serial.print(" | Azul (B): "); Serial.print(b);
  Serial.print(" | Brilho (C): "); Serial.print(c);
  Serial.print(" || Temp Cor: "); Serial.print(colorTemp); Serial.println(" K");

  delay(500);
}