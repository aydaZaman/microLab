#include <Arduino.h>
#define D2 2
#define D3 3
#define D5 5
#define D6 6
//0 is auto
//1 is manuall
int _A2;
int _A1;
int _A0;
int _D2;
int _D3;
int last =0;




int photoCellsOutput(){
    int photoCell1=map(_A0, 0, 1023, 0, 100);
    int photoCell2=map(_A1, 0, 1023, 0, 100);
    return (photoCell1 + photoCell2) / 2;
}

int LM35Output(){
    int tempA2=map(_A2, 0, 5, 0, 150);
    return tempA2;
}

int autoLightMode(){

  int light=photoCellsOutput();
  int dutyCycle;

  if(0<light && light<25)
    dutyCycle=100;
  
  else if(25<=light && light<50)
    dutyCycle=75;
    
  else if(50<=light && light<75)
      dutyCycle=50;
  
  else if(75<=light && light<=100)
    dutyCycle=25;

  return dutyCycle;

}

int autoTempMode(){
  int temp=LM35Output();
  //todo
  int dutyCycle;

  if(30<=temp && temp<35)
    dutyCycle=100;
  
  else if(35<=temp && temp<40)
    dutyCycle=75;
    
  else if(40<=temp && temp<45)
      dutyCycle=50;
  
  else if(45<=temp && temp<=50)
    dutyCycle=25;
  else if(temp<=25)
    dutyCycle=0;

  return dutyCycle;

}

void tempControl(int mode){
    if(mode==0){
    int temp=autoTempMode();
    analogWrite(D5, (temp/100)*255);
    }

    //else
    //manuall
}
void lightControl(int mode){
    if(mode==0){
      int light=autoLightMode();
      analogWrite(D6, (light/100)*255);
}
    //else
    //manuall
}

void setup() {
  // put your setup code here, to run once:
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);  
  pinMode(A2, INPUT);  
}


void loop() {
// put your main code here, to run repeatedly: 
  int current = millis();

  if(current - last >= 2){
    last = millis();
    _A0=analogRead(A0); 
    _A1=analogRead(A1);
    _A2=analogRead(A2);
    _D2=digitalRead(D2);
    _D3=digitalRead(D3);

    switch (_D3){
    case 0 :
      tempControl(0);
      break;
    
    default:
      tempControl(1); 
      break;
    }

    switch (_D2){
    case 0:
      lightControl(0);
      break;

    default:
      lightControl(1);
      break;
    }
  }
}