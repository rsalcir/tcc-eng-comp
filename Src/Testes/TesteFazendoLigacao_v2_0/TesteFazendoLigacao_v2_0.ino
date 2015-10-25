#include "SIM900.h"
#include <SoftwareSerial.h>
#include "call.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

CallGSM call;
int Botao = 13;
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);
boolean started=false;
boolean atendeu = false;

void setup()

{
  pinMode(Botao,INPUT);
  lcd.begin (16,2);
  Serial.begin(9600);
   lcd.setBacklight(HIGH);
   lcd.setCursor(0,0);
   lcd.print("   Iniciando.");
   lcd.setCursor(0,1);
   lcd.print("Aguarde...");
   delay(1000);

  if (gsm.begin(2400)) 
  {
  started=true;
  }
}

void loop(){
    if(started){
        lcd.clear();
        lcd.setBacklight(HIGH);
        lcd.setCursor(0,0);
        lcd.print("Aguardando Chamada");
        delay(1000);
        
        if(atendeu == false && digitalRead(Botao)==HIGH){
            lcd.clear();
            lcd.setBacklight(HIGH);
            lcd.setCursor(0,0);
            lcd.print("Ligando Para ");
            lcd.setCursor(0,1);
            lcd.print("92874764");
            call.Call("909092874764");
            atendeu = true;
       }
       if(atendeu == true && digitalRead(Botao)==HIGH){
        lcd.clear();
            lcd.setBacklight(HIGH);
            lcd.setCursor(0,0);
            lcd.print("desligando ");
            call.HangUp();
            atendeu = false;
       }
  }
}



