#include <FastIO.h>
#include <I2CIO.h>
#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal_SR.h>
#include <LiquidCrystal_SR2W.h>
#include <LiquidCrystal_SR3W.h>
#include <Wire.h>

 LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 
 int trigger = 8;           
 const int buzzer = 7;
 int echo = 9;           
 int Ptrigger = 10;           
 int Pecho = 11;
 float ttot,v,t0,tf;
 int ledPinR1 = 6;
 int ledPinV1 = 5;
 int ledPinR2 = 4;
 int ledPinA1yA2 = 3;//Los ambar van juntos
 int ledPinV2 = 2;
 int buttonPin = 13;
 int i;
 int j;
 int k=0;

void setup() {
  lcd.begin(16,2);
  lcd.backlight();
  lcd.backlight();
  Serial.begin (9600);   // establemos la comucicacion serial
  pinMode (trigger, OUTPUT); // declarmos el pin 9 como salida
  pinMode (echo, INPUT);   // declaramos el 8 como entrada
  pinMode (Ptrigger, OUTPUT); 
  pinMode (Pecho, INPUT);
  pinMode (13,INPUT);
  pinMode (6,OUTPUT);
  pinMode (5,OUTPUT);
  pinMode (4,OUTPUT);
  pinMode (3,OUTPUT);
  pinMode (2,OUTPUT);
  pinMode(buzzer, OUTPUT);
}  

void loop() {
  for(i=0;i<=70;i++)
  {
   j=digitalRead(13);
     if(j==LOW)
  {
    digitalWrite(6,LOW);
    digitalWrite(5,HIGH);
    digitalWrite(4,HIGH);
    digitalWrite(3,LOW);
    digitalWrite(2,LOW);
    delay(100);
  }
  else if(j==HIGH)
  {
   delay(3000);
   i=200;
  }
  }
  if(i>=200)
  {
   digitalWrite(6,HIGH);
   digitalWrite(5,LOW);
   digitalWrite(4,HIGH);
   digitalWrite(3,LOW);
   digitalWrite(2,LOW);
   delay(7000);   
  }
  else
  {
   digitalWrite(6,LOW);
   digitalWrite(5,HIGH);
   digitalWrite(4,HIGH);
   digitalWrite(3,LOW);
   digitalWrite(2,LOW);
   delay(7000); 
  }
  //Rojo 1 mas boton
  
  for(i=0;i<4;i++)
  {
      digitalWrite(6,LOW);
      digitalWrite(5,LOW);
      digitalWrite(4,LOW);
      digitalWrite(3,HIGH);
      digitalWrite(2,LOW);
      delay(500);
      digitalWrite(6,LOW);
      digitalWrite(5,LOW);
      digitalWrite(4,LOW);
      digitalWrite(3,LOW);
      digitalWrite(2,LOW);
      delay(500);
  }
  //S1 y S2 ambar
  digitalWrite(6,HIGH);
  digitalWrite(5,LOW);
  digitalWrite(4,LOW);
  digitalWrite(3,LOW);
  digitalWrite(2,HIGH);
  lcd.setCursor(1,0);
  lcd.print("L.VEL");
  lcd.setCursor(9,0);
  lcd.print("SU VEL");
  lcd.setCursor(1,1);
  lcd.print("80.00");
  for(i=0;i<500;i++)
  {
  int cm1 = ping(trigger, echo);
  int cm2 = ping(Ptrigger, Pecho);
  if (cm1>=2 && cm1 <=20){  
   t0=millis();
  }
  if (cm2>=2 && cm2 <=20){ 
   tf=millis();
   ttot = (tf - t0);
   v = 19000/ttot;
   lcd.setCursor(10,1);
   lcd.print(v);
   i=1000;
  }
  }
  if(v>80.00){
    digitalWrite(4,HIGH);
    digitalWrite(2,LOW);
    digitalWrite(buzzer, HIGH);  
    delay(500);               
    digitalWrite(buzzer, LOW);   
    delay(200);   
    digitalWrite(buzzer, HIGH);  
    delay(500);               
    digitalWrite(buzzer, LOW);   
    delay(200);   
    digitalWrite(buzzer, HIGH);  
    delay(500);               
    digitalWrite(buzzer, LOW);   
    delay(2000); 
  }
  else{
    delay(5000);
  }
  lcd.clear();
  //Radar
  for(i=0;i<4;i++)
  {
      digitalWrite(6,LOW);
      digitalWrite(5,LOW);
      digitalWrite(4,LOW);
      digitalWrite(3,HIGH);
      digitalWrite(2,LOW);
      delay(500);
      digitalWrite(6,LOW);
      digitalWrite(5,LOW);
      digitalWrite(4,LOW);
      digitalWrite(3,LOW);
      digitalWrite(2,LOW);
      delay(500);
  }
  //S1 y S2 ambar
  v=0;
}

int ping(int trigger, int echo){
   long duration,distance;
   digitalWrite(trigger, LOW);  //para generar un pulso limpio ponemo
   delayMicroseconds(4);
   digitalWrite(trigger, HIGH);  //generamos Trigger (disparo) de 10us
   delayMicroseconds(10);
   digitalWrite(trigger, LOW);
   
   duration = pulseIn(echo, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
   
   distance = duration * 10 / 292/ 2;   //convertimos a distancia, en cm
   return distance;
  }           
