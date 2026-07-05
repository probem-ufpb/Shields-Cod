// Código para teste do LED RGB da Shield 5 do PROBEM

int R = 3;
int G = 5;
int B = 6;

int val[4] = {20,100,180, 255};

void setup() {
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
}

void loop() {
  
  //Vermelho
  for (int i = 0; i<=3; i++) {
    seleCor(val[i], 0, 0);
    delay(500);
  }
  delay(1000);