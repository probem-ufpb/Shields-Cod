// Código para teste da Shield 2 do PROBEM

void setup() {
    //LED's
    pinMode(3, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(13, OUTPUT);

    pinMode(9, OUTPUT); // Buzzer
    pinMode(8, INPUT); // Botão
}

void loop() {
    if (digitalRead(8) == HIGH) {

      tone(9, 500);
      digitalWrite(3, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(7, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(13, HIGH);

    }

      noTone(9);
      digitalWrite(3, LOW);
      digitalWrite(5, LOW);
      digitalWrite(7, LOW);
      digitalWrite(11, LOW);
      digitalWrite(13, LOW);
}
