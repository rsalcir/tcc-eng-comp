#include "SIM900.h"
#include "call.h"
#include "sms.h"
#include <Wire.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

CallGSM call;
SMSGSM sms;
boolean conectadoARedeGSM = false;
boolean atendeuAChamada = false;
boolean interfone = false;
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

#define botaoDaCampainha 13
#define fechadura 12
#define alarme 11

char pos;
char message[180];
char number[13];

void escreveNoDisplay(String primeiraLinha, String segundaLinha){
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print(primeiraLinha);
   lcd.setCursor(0,1);
   lcd.print(segundaLinha);
}

void configuraEntradasESaidas(){
  pinMode(botaoDaCampainha,INPUT);
  pinMode(alarme,INPUT);
  pinMode(fechadura, OUTPUT);
}

void iniciaDisplay(){
  lcd.begin (16,2);
  lcd.setBacklight(HIGH);
}

boolean verificaConexaoComARedeGSM(){
 return gsm.begin(2400);
}
 
void setup()
{
  configuraEntradasESaidas();
  iniciaDisplay();
  escreveNoDisplay("Iniciando","Aguarde...");
  conectadoARedeGSM = verificaConexaoComARedeGSM();
}

boolean botaoFoiPressionado(){
 return digitalRead(botaoDaCampainha)==HIGH;
}

void realizaUmaChamada(char *numeroTelefonico){
 call.Call(numeroTelefonico);
}

void encerraUmaChamada(){
 call.HangUp();
}

boolean alarmeLigado(){
return digitalRead(alarme)==HIGH;
}

void loop()
{
 if(alarmeLigado()){
  char *numeroTelefonico = "909092874764";
  if(conectadoARedeGSM){
    escreveNoDisplay("Sistema","Ativado");
    delay(1000);
    
     if(atendeuAChamada == false && botaoFoiPressionado()){
       escreveNoDisplay("Ligando para",numeroTelefonico);
       realizaUmaChamada(numeroTelefonico);
       atendeuAChamada = true;
     }else if(atendeuAChamada && botaoFoiPressionado()) {
       escreveNoDisplay("Encerrando","chamada");
       encerraUmaChamada();
       atendeuAChamada = false;
     }
        pos=sms.IsSMSPresent(SMS_UNREAD);

       if((int)pos>0 && (int)pos<=20) {
        
         message[0]='\0';
         sms.GetSMS((int)pos,number,message,180);
         sms.DeleteSMS(pos);
        
          if(strstr(message,"1")){
             escreveNoDisplay("Abrindo","fechadura");
             for (int i=0; i<10; i++){
               digitalWrite(fechadura,HIGH);
               delay(100);
               digitalWrite(fechadura,LOW);
               delay(100);
             }
          }
       }
  }
 } else{
    escreveNoDisplay("Sistema","Desativado");
    delay(1000);
  }
}


