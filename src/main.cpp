#include <Arduino.h>
#include <LiquidCrystal.h>

#define D2 2
#define D3 3
#define D5 5
#define D6 6


int _A2;
int _A1;
int _A0;
int _D2;
int _D3;

const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


int calculateLightValue(){
  int photoCell1 = map(_A0 * 0.0048828125, 0, 5, 0, 100);
  int photoCell2 = map(_A1 * 0.0048828125, 0, 5, 0, 100);

  int photoCellAvg = (photoCell1 + photoCell2) / 2;
  return photoCellAvg;
}

int calculateLEDDutyCycle(){
  int photoCellAvg = calculateLightValue();
  int dutyCycle;

  if(photoCellAvg >= 0 && photoCellAvg < 25){
    dutyCycle = 100;
  }
  else if(photoCellAvg >= 25 && photoCellAvg < 50){
    dutyCycle = 75;
  }
  else if(photoCellAvg >= 50 && photoCellAvg < 75){
    dutyCycle = 50;
  }
  else if(photoCellAvg >= 75 && photoCellAvg < 100){
    dutyCycle = 25;
  }

  return dutyCycle;
}

int calculateTempValue(){
  float temp_float = (_A2 * 4.88)/10;
  int temp = (int)temp_float;
  return temp;
}

int calculateMotorDutyCycle(){
  int temp = calculateTempValue();
  int dutyCycle;

  if(temp >= 30 && temp < 35){
    dutyCycle = 30;
  }
  else if(temp >= 35 && temp < 40){
    dutyCycle = 50;
  }
  else if(temp >= 40 && temp < 45){
    dutyCycle = 70;
  }
  else if(temp >= 45 && temp < 50){
    dutyCycle = 100;
  }
  return dutyCycle;
}

void automaticLightingSystem(){
  int lightDutyCycle = calculateLEDDutyCycle();
  analogWrite(D6, (lightDutyCycle / 100.0) * 255);
}

void manualLightingSystem(){
  Serial.println("manual light");
}

void manualAirConditionSystem(){
  Serial.println("manual air condition");
}

void automaticAirConditionSystem(){
  int tempDutyCycle = calculateMotorDutyCycle();
  analogWrite(D5, (tempDutyCycle / 100.0) * 255);
}

void showTemperatureOnLCD(){
  int temp = calculateTempValue();
  lcd.setCursor(0,0);
  lcd.print("Temperature:");
  lcd.print(temp);
}

void showLightOnLCD(){
  int light = calculateLightValue();
  lcd.setCursor(0,1);
  lcd.print("Light:");
  lcd.print(light);
}

void setup() {
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);  
  pinMode(A2, INPUT);  

  lcd.begin(16, 2);
  Serial.begin(9600);
}

int last;
void loop() {
  int current = millis();
  if(current - last >=2000){
    last = current;
    _A0 = analogRead(A0); // photoCell 1
    _A1 = analogRead(A1); // photoCell 2
    _A2 = analogRead(A2); // LM35
  }

  _D2 = digitalRead(D2);
  _D3 = digitalRead(D3);

  if(_D2 == 0 && _D3 == 0){
    automaticLightingSystem();
    automaticAirConditionSystem();
  }
  else if(_D2 == 1 && _D3 == 0){
    manualLightingSystem();
    automaticAirConditionSystem();
  }
  else if(_D2 == 0 && _D3 == 1){
    automaticLightingSystem();
    manualAirConditionSystem();
  }
  else if(_D2 == 1 && _D3 == 1){
    manualLightingSystem();
    manualAirConditionSystem();
  }

  showTemperatureOnLCD();
  showLightOnLCD();

}
