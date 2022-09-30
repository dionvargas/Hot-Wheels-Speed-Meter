//Carrega a biblioteca LiquidCrystal
#include <LiquidCrystal.h>

#define sensor1 8
#define sensor2 9

int distancia = 126;    //Distância dos sensores em milímetros

unsigned long timeFst; // Tempo que passou pelo primeiro sensor
unsigned long timeScd; // Tempo que passou pelo segundo sensor
unsigned long diff;    // Diferença de tempo entre a passagem do primeiro e do segundo sensor

float vel;

byte arrow1[] = {
  B10000,
  B11000,
  B10100,
  B10010,
  B10010,
  B10100,
  B11000,
  B10000
};

byte arrow2[] = {
  B10000,
  B11000,
  B11100,
  B11110,
  B11110,
  B11100,
  B11000,
  B10000
};

//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  lcd.createChar(0, arrow1);
  lcd.createChar(1, arrow2);

  //Define o número de colunas e linhas do LCD
  lcd.begin(16, 2);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
}

void startDisplay() {
  //Limpa a tela
  lcd.clear();

  lcd.setCursor(3, 0);
  lcd.print("SPEED TEST");

  for (int i = 0; i < 16; i++) {
    lcd.setCursor(i, 1);
    lcd.write(byte(0));
    delay(50);
  }
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(i, 1);
    lcd.write(byte(1));
    delay(50);
  }

  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("                ");
  delay(100);
  lcd.setCursor(3, 1);
  lcd.print("GO");
  delay(100);
  lcd.setCursor(6, 1);
  lcd.print("GO");
  delay(100);
  lcd.setCursor(9, 1);
  lcd.print("GO!!!");
}

void showSpeed(){
  diff = timeScd - timeFst;
  vel = (float(distancia)/float(diff))*3.6;
  
  lcd.clear();

  lcd.setCursor(4, 0);
  lcd.print(diff);
  lcd.print(" ms");

  lcd.setCursor(4, 1);
  lcd.print(vel, 3);
  lcd.print(" km/h");
  

  delay(4000);
}

void loop()
{
  startDisplay();

  while (digitalRead(sensor1));
  timeFst = millis();

  while (digitalRead(sensor2));
  timeScd = millis();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SENSOR 1: ");
  lcd.print(timeFst);
  
  lcd.setCursor(0, 1);
  lcd.print("SENSOR 2: ");
  lcd.print(timeScd);

  delay(1000);

  showSpeed();
}
