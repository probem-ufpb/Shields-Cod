void (*resetFunc) (void) = 0; // Declaração de uma função de SoftReset do Arduino 

#include <LiquidCrystal.h>
#include <stdlib.h>
#include <time.h>

// === NOTAS MUSICAIS USADAS NA INTRO DO PACMAN ===
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_E6  1319
#define NOTE_G6  1568

LiquidCrystal lcd(10, 9, 8, 7, 6, 5);

byte pacman[8] { // Pacman
    0b00000,
    0b01110,
    0b11011,
    0b11111,
    0b11110,
    0b11111,
    0b01110,
    0b00000
};

byte pacmanOM[8] { // Pacman abrindo a boca
    0b00000,
    0b01110,
    0b11011,
    0b11100,
    0b11000,
    0b11100,
    0b01110,
    0b00000
};

byte ghost[8] { // Fantasma
    0b00000,
    0b01110,
    0b10101,
    0b11111,
    0b10001,
    0b11111,
    0b10101,
    0b01010
};

byte maca[8] = { // maçã
    0b00010,
    0b00100,
    0b01010,
    0b11111,
    0b11111,
    0b11111,
    0b01110,
    0b00000
};

// Variáveis

unsigned long millisTarefa1 = millis();

int botao1 = 12;
int botao2 = 11;
int buzzer = 13;

int linha = 0;
int coluna = 0;

// Arrays separados para armazenar posicoes geradas dinamicamente
int posMacas[5][2];
int posFantasmas[5][2];
int inPosicao = 0;

int contador = 0;

// === CONFIGURAÇÕES DA MÚSICA INTRO ===
/* 
	Evitar mexer nas configurações de música da intro
   	Música de início do pacman
*/
int tempo = 105;

int melodia[] = {
  NOTE_B4, 16, NOTE_B5, 16, NOTE_FS5, 16, NOTE_DS5, 16, 
  NOTE_B5, 32, NOTE_FS5, -16, NOTE_DS5, 8, NOTE_C5, 16,
  NOTE_C6, 16, NOTE_G6, 16, NOTE_E6, 16, NOTE_C6, 32, NOTE_G6, -16, NOTE_E6, 8,
  NOTE_B4, 16,  NOTE_B5, 16,  NOTE_FS5, 16,   NOTE_DS5, 16,  NOTE_B5, 32,  
  NOTE_FS5, -16, NOTE_DS5, 8,  NOTE_DS5, 32, NOTE_E5, 32,  NOTE_F5, 32,
  NOTE_F5, 32,  NOTE_FS5, 32,  NOTE_G5, 32,  NOTE_G5, 32, NOTE_GS5, 32,  NOTE_A5, 16, NOTE_B5, 8
};

int totalNotas = sizeof(melodia) / sizeof(melodia[0]) / 2;
int notaInteira = (60000 * 4) / tempo;
int divisor = 0, duracaoNota = 0;

// === VARIÁVEIS DA MÚSICA DE FUNDO (BACKGROUND) ===
// Frequências e variáveis auxiliares
int notasFundo[] = { 330, 262, 330, 262, 349, 294, 349, 294 }; 
int duracoesFundo[] = { 250, 250, 250, 250, 250, 250, 250, 250 }; // Tempo em milissegundos
int totalNotasFundo = 8;
int indiceFundo = 0;
unsigned long ultimoTempoFundo = 0;
int tempoEsperaFundo = 0;

void setup() 
{
  	// Configura os pinos
    pinMode(botao1, INPUT);
    pinMode(botao2, INPUT);
    pinMode(buzzer, OUTPUT);
    lcd.createChar(1, pacman);
    lcd.createChar(2, pacmanOM);
    lcd.createChar(3, ghost);
  	lcd.createChar(4, maca);

  	// Menu inicial
    lcd.begin(16, 2);
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Pacman x Ghost");
    lcd.setCursor(7,1);
    lcd.write(1);
    lcd.setCursor(9,1);
    lcd.write(4);
  
    // Animação do menu
    menuDoJogo();
  
  	// Le o ruído de um pino analógico vazio para criar uma semente realmente aleatória
    srand(analogRead(A0));
  
  	// Gera as posições da maçã e do fantasma
    aleotorizarPosicoes();
  	
  	atualizarLCD();
}

void loop() 
{
  tocarMusicaFundo();
  
  if (contador >= 5) 
  {
    fimDeJogo();
  } 
  if (digitalRead(botao1) == LOW) 
  {
    linha = (linha == 0) ? 1 : 0;
    atualizarLCD();

    // Trava o jogo até soltar o botão 1
    while(digitalRead(botao1) == LOW) 
    {
      tocarMusicaFundo();
      delay(1); // **Talvez mexer dps <----
    }
    delay(50);
  }

  if (digitalRead(botao2) == LOW) 
  {
    coluna = (coluna < 15) ? ++coluna : 0;
    atualizarLCD();

    // Trava o jogo até soltar o botão 2
    while(digitalRead(botao2) == LOW) 
    {
      tocarMusicaFundo();
      delay(1); // **Talvez mexer dps <----
    }
    delay(50);
  }
  
  // Verificacao de colisao com o fantasma (Morte)
  if (coluna == posFantasmas[inPosicao][0] && linha == posFantasmas[inPosicao][1])
  {
    tocarMusicaMorte(); // Toca o som de morte
    
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("GAME OVER!"); // Mensagem de morte
    delay(1500);
    
    resetFunc(); // Volta pro menu resetando tudo
  }

  // Atualizado para checar a matriz posMacas
  if (coluna == posMacas[inPosicao][0] && linha == posMacas[inPosicao][1]) 
  {
    tone(buzzer, 300);
    delay(1000);
    noTone(buzzer);
    
    ultimoTempoFundo = millis(); // reinicia tempo da musica

    inPosicao = (inPosicao + 1) % 5; 
    
    // Retorna o amarelo pra posição inicial (0,0) ao passar de fase
    coluna = 0;
    linha = 0;
    
    atualizarLCD();
    contador++;
  }
}

void atualizarLCD() 
{
  lcd.clear();

  // Desenha a maçã primeiro pro amarelo não bugar
  lcd.setCursor(posMacas[inPosicao][0], posMacas[inPosicao][1]);
  lcd.write(4);

  // Desenha o fantasma
  lcd.setCursor(posFantasmas[inPosicao][0], posFantasmas[inPosicao][1]);
  lcd.write(3);

  // Verifica se o pacman está próximo da maçã ou exatamente em cima ou embaixo
  bool adjacenteOuEmCima = 
    (coluna == posMacas[inPosicao][0] - 1 && linha == posMacas[inPosicao][1]) || // esquerda
    (coluna == posMacas[inPosicao][0]); // Mesma coluna

  // Desenha o pacman so dps, garantindo que ele não seja apagado se estiver no mesmo quadrado
  if (adjacenteOuEmCima)
  {
    lcd.setCursor(coluna, linha);
    lcd.write(2); // pacman de boca aberta
  } 
  else 
  {
    lcd.setCursor(coluna, linha);
    lcd.write(1); // pacman de boca fechada
  }
}

// === FUNÇÃO PARA TOCAR A MÚSICA DA INTRO (USA DELAY) ===
void tocarIntroPacman(int pino) 
{
  for (int notaAtual = 0; notaAtual < totalNotas * 2; notaAtual = notaAtual + 2) 
  {
    divisor = melodia[notaAtual + 1];
    if (divisor > 0) 
    {
      duracaoNota = (notaInteira) / divisor;
    } 
    else if (divisor < 0) 
    {
      duracaoNota = (notaInteira) / abs(divisor);
      duracaoNota *= 1.5;
    }
    tone(pino, melodia[notaAtual], duracaoNota * 0.9);
    delay(duracaoNota);
    noTone(pino);
  }
}

// === FUNÇÃO PARA TOCAR A MÚSICA DE BACKGROUND (FUNDO) ===
void tocarMusicaFundo() 
{
    // Checa se é hora de iniciar a próxima nota
    if (millis() - ultimoTempoFundo >= tempoEsperaFundo) 
    {
        // Liga o som da nota atual
        tone(buzzer, notasFundo[indiceFundo]);
        
        // Atualiza os marcadores de tempo
        ultimoTempoFundo = millis();
        tempoEsperaFundo = duracoesFundo[indiceFundo];
        
        // Prepara o índice da próxima nota
        indiceFundo++;
        if (indiceFundo >= totalNotasFundo) 
        {
            indiceFundo = 0;
        }
    }
    
    // Desliga a nota após 80% do tempo passao
  	// (pra não ficar estranho)
    if (millis() - ultimoTempoFundo >= (tempoEsperaFundo * 0.8)) 
    {
        noTone(buzzer);
    }
}

// === FUNÇÃO PARA TOCAR A MÚSICA DE VITÓRIA ===
void tocarMusicaVitoria() 
{
  tone(buzzer, NOTE_C5); delay(150);
  tone(buzzer, NOTE_E5); delay(150);
  tone(buzzer, NOTE_G5); delay(150);
  tone(buzzer, NOTE_C6); delay(400);
  tone(buzzer, NOTE_G5); delay(150);
  tone(buzzer, NOTE_C6); delay(600);
  
  noTone(buzzer);
}

// Função para tocar som simulando a morte do amarelo
void tocarMusicaMorte() 
{
  noTone(buzzer);
  
  for (int i = 800; i >= 200; i -= 50) 
  {
    tone(buzzer, i);
    delay(40);
  }
  noTone(buzzer);
  delay(100);
  
  for (int i = 600; i >= 100; i -= 50) 
  {
    tone(buzzer, i);
    delay(40);
  }
  noTone(buzzer);
}

// Função para fim de jogo e chamar a musica de vitoria
void fimDeJogo()
{
  noTone(buzzer); // Para a musica de fundo
    
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("Parabens!!");
  lcd.setCursor(4,1);
  lcd.write(1);
  lcd.setCursor(6,1);
  lcd.print("Ganhou");

  tocarMusicaVitoria(); // Musica de fim

  delay(1000); // delay pra não acabar do nada

  resetFunc();
}

// Função para animação do menu
void menuDoJogo()
{
  while(digitalRead(botao1) == HIGH && digitalRead(botao2) == HIGH) 
  {
    if ((millis() - millisTarefa1) < 400) 
    {
      lcd.setCursor(7,1);
      lcd.print(" ");
      lcd.setCursor(8,1);
      lcd.write(2);
    } 
    else 
    {
      lcd.setCursor(8,1);
      lcd.print(" ");
      lcd.setCursor(7,1);
      lcd.write(1);
    }
    if ((millis() - millisTarefa1) > 1100) 
    {
      millisTarefa1 = millis();
    }
  }

  // Espera o jogador soltar os botões antes de começar o jogo de fato
  while(digitalRead(botao1) == LOW || digitalRead(botao2) == LOW) { delay(10); }

  // Start apertado
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Boa sorte!");
  // Toca a música uma única vez durante o "boa sorte!"
  tocarIntroPacman(buzzer);

  atualizarLCD();
}

// gera a matriz de posições de forma pseudoaleatoria
void aleotorizarPosicoes()
{
  for (int i = 0; i < 5; i++)
  {
    // Fantasma: coluna aleatória de 2 a 10, linha 0 ou 1
    posFantasmas[i][0] = 2 + (rand() % 9); 
    posFantasmas[i][1] = rand() % 2;       

    // Fruta (Maca): coluna aleatória de 11 a 15, linha 0 ou 1
    posMacas[i][0] = 11 + (rand() % 5);
    posMacas[i][1] = rand() % 2;
  }
}