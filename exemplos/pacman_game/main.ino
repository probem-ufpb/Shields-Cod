void (*resetFunc) (void) = 0;

#include <LiquidCrystal.h>
LiquidCrystal lcd(10, 9, 8, 7, 6, 5);

byte pacman[8] {
    0b00000,
    0b01110,
    0b11011,
    0b11111,
    0b11000,
    0b11111,
    0b01110,
    0b00000
};

byte pacmanOM[8] {
    0b00000,
    0b01110,
    0b11011,
    0b11111,
    0b11000,
    0b11000,
    0b01100,
    0b00111
};

byte ghost[8] {
    0b00000,
    0b01110,
    0b10101,
    0b11111,
    0b10001,
    0b11111,
    0b10101,
    0b01010
};

long millisTarefa1 = millis();

int botao1 = 3;
int botao2 = 4;
int buzzer = 2;

int linha = 0;
int coluna = 0;

int posicoes[5][2] = {{3, 0}, {7, 1}, {12, 0}, {5, 1}, {10, 0}};
int inPosicao = 0;

int contador = 0;

void setup() {

    pinMode(botao1, INPUT);
    pinMode(botao2, INPUT);
    pinMode(buzzer, OUTPUT);
    lcd.createChar(1, pacman);
    lcd.createChar(2, pacmanOM);
    lcd.createChar(3, ghost);

    lcd.begin(16, 2);
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Pacman x Ghost");
    lcd.setCursor(7,1);
    lcd.write(1);
    lcd.setCursor(9,1);
    lcd.write(3);
    while(digitalRead(botao1) != HIGH && digitalRead(botao2) != HIGH) {
        if ((millis() - millisTarefa1) < 400) {
            lcd.setCursor(7,1);
            lcd.print(" ");
            lcd.setCursor(8,1);
            lcd.write(2);
        } else {
            lcd.setCursor(8,1);
            lcd.print(" ");
            lcd.setCursor(7,1);
            lcd.write(1);
        }
        if ((millis() - millisTarefa1) > 1100) {
            millisTarefa1 = millis();
        }

    }
    atualizarLCD();
}

void loop() {

    if (contador >= 5) {
        lcd.clear();
        lcd.setCursor(4,0);
        lcd.print("Parabens!!");
        lcd.setCursor(4,1);
        lcd.write(1);
        lcd.setCursor(6,1);
        lcd.write("Ganhou");
        delay(2000);
        resetFunc();
    } 

    if (digitalRead(botao1) == HIGH) {
        delay(200);
        linha = (linha == 0) ? 1 : 0;
        atualizarLCD();
    }

    if (digitalRead(botao2) == HIGH) {
        delay(200);
        if (coluna < 15) {
            coluna++;
        } else {
            coluna = 0;
        }
        atualizarLCD();
    }

    if (coluna == posicoes[inPosicao][0] && linha == posicoes[inPosicao][1]) {
        tone(buzzer, 300);
        delay(1000);
        noTone(buzzer);

        inPosicao = (inPosicao + 1) % 5;
        atualizarLCD();
        contador++;
    }

}

void atualizarLCD() {

    lcd.clear();
    
    if (coluna == (posicoes[inPosicao][0]-1) && linha == posicoes[inPosicao][1]){
        lcd.setCursor(coluna, linha);
        lcd.write(2);
    } else {
        lcd.setCursor(coluna, linha);
        lcd.write(1);
    }
    lcd.setCursor(posicoes[inPosicao][0], posicoes[inPosicao][1]);
    lcd.write(3);
    
}