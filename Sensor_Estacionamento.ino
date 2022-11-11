// C++ code
//
#include <LiquidCrystal.h>
int totalVagas = 2;
const int rs = 3, en = 4, d4 = A2, d5 = A3, d6 = A4, d7 = A5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //LCD
byte pinoTransmissor_1=13; // trig1
byte pinoReceptor_1=12; //echo1

byte pinoTransmissor_2=11; // trig2
byte pinoReceptor_2=10; //echo2


void setup()
{
    
  //LCD
  lcd.begin(16, 2);
  // transmissores
  pinMode(pinoTransmissor_1, OUTPUT);
  pinMode(pinoTransmissor_2, OUTPUT);
  
  // receptores
  pinMode(pinoReceptor_1, INPUT);   
  pinMode(pinoReceptor_2, INPUT); 
  
  //Leds
  pinMode(9,OUTPUT); //LED1
  pinMode(8,OUTPUT); //LED2
  pinMode(7,OUTPUT); //LED3
  pinMode(6,OUTPUT); //LED4

  
  //porta serial
  Serial.begin(9600);
}

void loop()
{
  int vagasOcupadas = 0;
  vagasOcupadas += vaga_ocupada(1);
  vagasOcupadas += vaga_ocupada(2);
  
  int vagasLivres = totalVagas - vagasOcupadas;
  
  printString(vagasOcupadas, vagasLivres);
  delay(500);
}


int vaga_ocupada(int nmr_sensor){
  float cm;
  
  cm = distancia(nmr_sensor);
  
  if(cm >= 200){
	ledVerde(nmr_sensor);
    return 0;
  }
  else{
    ledVermelho(nmr_sensor);
    return 1;
  }

}

float distancia(int nmr_sensor){
  float duracao;
  byte pinoTrans, pinoRecept;
  if(nmr_sensor == 1){
    pinoTrans = pinoTransmissor_1;
    pinoRecept = pinoReceptor_1;
  }
  else{
    pinoTrans = pinoTransmissor_2;
    pinoRecept = pinoReceptor_2;
  }
  
  digitalWrite(pinoTrans, LOW);
  delayMicroseconds(5); 

  digitalWrite(pinoTrans, HIGH); 

  delayMicroseconds(10);
  
  digitalWrite(pinoTrans, LOW);
 
  duracao = pulseIn(pinoRecept, HIGH);
  
  float calcDistancia= (duracao/2) * 0.0343; 
  
  // fora do limite do sensor
  if (calcDistancia>=331){ 
      calcDistancia=0;
  }
  return calcDistancia;  
}

void ledVerde(int nmr_led){
  if(nmr_led == 1){
    digitalWrite(8,HIGH);
    digitalWrite(9,LOW);
  }
  else{
    digitalWrite(6,HIGH);
    digitalWrite(7,LOW);
  }

}

void ledVermelho(int nmr_led){
    if(nmr_led == 1){
    digitalWrite(9,HIGH);
    digitalWrite(8,LOW);
  }
  else{
    digitalWrite(7,HIGH);
    digitalWrite(6,LOW);
  }
}

void printString(int vagasOcupadas, int vagasLivres) {
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("vagas livres " + (String)vagasLivres);
lcd.setCursor(0, 1);
lcd.print("vagas ocupadas " + (String)vagasOcupadas);
delay(2000);
}
