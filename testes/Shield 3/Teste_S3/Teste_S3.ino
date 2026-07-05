// Código para teste a Shield 3 do PROBEM

// Definições dos pinos dos LEDs do display de 7 segmentos
int a = 11;
int b = 10;
int c = 7;
int d = 8;
int e = 9;
int f = 12;
int g = 13;

// Pino do LED normal
int ledNormal = 5;

// Pinos dos sensores
int pot = A0;  // Pino para o potenciômetro
int ldr = A1;  // Pino para o LDR

int valorPot;
int valorLdr;

void setup() {
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(ledNormal, OUTPUT);
  pinMode(pot, INPUT);
  pinMode(ldr, INPUT);

  Serial.begin(9600);

  ligarDisplay();

  digitalWrite(ledNormal, HIGH);
}

void loop() {
  // Leitura dos valores do potenciômetro e LDR
  valorPot = analogRead(pot);
  valorLdr = analogRead(ldr);

  // Envia os valores lidos para o monitor serial
  Serial.print("Valor do Potenciômetro (0-1023): ");
  Serial.println(valorPot);

  Serial.print("Valor do LDR (0-1023): ");
  Serial.println(valorLdr);

  delay(500);  // Atraso de 500ms para facilitar a leitura
}

void ligarDisplay() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
