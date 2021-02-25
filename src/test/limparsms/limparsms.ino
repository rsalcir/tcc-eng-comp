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
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

#define botaoDaCampainha 13
#define fechadura 12

char pos;
char message[180];
char number[13];
char *Abrindo;

void escreveNoDisplay(String primeiraLinha, String segundaLinha){
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print(primeiraLinha);
   lcd.setCursor(0,1);
   lcd.print(segundaLinha);
}

void configuraEntradasESaidas(){
  pinMode(botaoDaCampainha,INPUT);
  pinMode(fechadura, OUTPUT);
}

void iniciaDisplay(){
  lcd.begin (16,2);
  lcd.setBacklight(HIGH);
}

boolean verificaConexaoComARedeGSM(){
 return gsm.begin(2400);
}
 
void setup() {
 configuraEntradasESaidas();
  iniciaDisplay();
  escreveNoDisplay("Iniciando","Aguarde...");
  conectadoARedeGSM = verificaConexaoComARedeGSM();
}

void loop() {
if(conectadoARedeGSM){
    escreveNoDisplay("Sistema","Ativado");
    delay(1000);
    for (int i=0; i<10; i++){  //do it max 10 times
     int pos=sms.IsSMSPresent(SMS_ALL);
     if (pos!=0){
        escreveNoDisplay("Limpando ","SMS"); 
       if (sms.DeleteSMS(pos)==1){
        escreveNoDisplay("Ainda Tem: ",(String)pos+" SMS");
        } 
       }else{
          escreveNoDisplay("Nao Tem: ","Mais SMS");
          }   
    }
  }
}
