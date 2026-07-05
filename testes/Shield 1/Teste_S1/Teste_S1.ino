// Código para teste da Shield 1 do PROBEM

void setup() {
    //LED's
    pinMode(2, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(12, OUTPUT);
}

void loop() {
    digitalWrite(2, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(12, HIGH);
    delay(1000);
    digitalWrite(2, LOW);
    digitalWrite(4, LOW);
    digitalWrite(6, LOW);
    digitalWrite(8, LOW);
    digitalWrite(10, LOW);
    digitalWrite(12, LOW);
    delay(1000);
}
