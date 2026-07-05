// Código para teste a Shield 4 do PROBEM

#include <LiquidCrystal.h>
#include <Ultrasonic.h>

// Inicialização do Display LCD e do Sensor Ultrassônico
LiquidCrystal lcd(10, 9, 8, 7, 6, 5);
Ultrasonic ultrasonic(11, 12); // (Trig = 11, Echo = 12)

// Definição dos pinos
const int botao1 = 3;
const int botao2 = 4; 
const int buzzer = 2; 

// Variável de controle de unidade (false = cm, true = mm)
bool mostrarEmMilimetros = false; 

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Iniciando...");
  delay(1000);
  lcd.clear();

  pinMode(botao1, INPUT);
  pinMode(botao2, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  if (digitalRead(botao1) == LOW) {
    mostrarEmMilimetros = true;
  }
  
  if (digitalRead(botao2) == LOW) {
    mostrarEmMilimetros = false;
  }

  // (Caso sua biblioteca exija parâmetro, use ultrasonic.read(CM))
  int distanciaCM = ultrasonic.read(CM); 

  lcd.setCursor(0, 0);
  lcd.print("Distancia:      "); 
  
  lcd.setCursor(0, 1);
  if (mostrarEmMilimetros) {
    int distanciaMM = distanciaCM * 10;
    lcd.print(distanciaMM);
    lcd.print(" mm        ");
  } else {
    lcd.print(distanciaCM);
    lcd.print(" cm        "); 
  }


  if (distanciaCM > 0 && distanciaCM < 7) { 
    tone(buzzer, 1000);
  } else {
    noTone(buzzer); 
  }

  // Pequeno delay para não sobrecarregar o display e o sensor
  delay(300);
}