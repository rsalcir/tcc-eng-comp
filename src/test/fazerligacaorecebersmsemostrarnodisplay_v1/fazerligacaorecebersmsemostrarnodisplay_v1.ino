#include "SIM900.h"
#include <SoftwareSerial.h>
#include "call.h"
#include "sms.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

CallGSM call;
SMSGSM sms;
int botao = 13;
int fechadura = 12;
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);
boolean started=false;
boolean atendeu = false;
char pos;
char message[180];
char number[13];
char *Abrindo;

void setup()

{
  pinMode(botao,INPUT);
  pinMode(fechadura, OUTPUT);
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
        
        if(atendeu == false && digitalRead(botao)==HIGH){
            lcd.clear();
            lcd.setBacklight(HIGH);
            lcd.setCursor(0,0);
            lcd.print("Ligando Para ");
            lcd.setCursor(0,1);
            lcd.print("92874764");
            call.Call("909092874764");
            atendeu = true;
       }
       if(atendeu == true && digitalRead(botao)==HIGH){
        lcd.clear();
            lcd.setBacklight(HIGH);
            lcd.setCursor(0,0);
            lcd.print("desligando ");
            call.HangUp();
            atendeu = false;
       }
       
    pos=sms.IsSMSPresent(SMS_UNREAD);

       if((int)pos>0 && (int)pos<=20) {
        
         message[0]='\0';
         sms.GetSMS((int)pos,number,message,180);
         Abrindo = strstr(message,"On");
       
          if(Abrindo){
             digitalWrite(fechadura,HIGH);
             delay(100);
             digitalWrite(fechadura,LOW);
             delay(100);
             digitalWrite(fechadura,HIGH);
             delay(100);
             digitalWrite(fechadura,LOW);
             delay(100);
             digitalWrite(fechadura,HIGH);
             delay(100);
             digitalWrite(fechadura,LOW);
             delay(100);
          }
       }
       
  }
}



