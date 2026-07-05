// Código para teste do Sensor Infravermelho da Shield 5 do PROBEM

int obj;

void setup(void) {
  Serial.begin(9600);
  pinMode(9, INPUT);
}

void loop(void) {
  obj = digitalRead(9);

  if (obj == HIGH) {
    Serial.println("Nenhum objeto detectado.");
  } else{
    Serial.println("Objeto detectado.");
  }

  delay(300);
}