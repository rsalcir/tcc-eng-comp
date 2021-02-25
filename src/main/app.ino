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

char posicao;
char textoDoSMS[180];
char telefoneDoSMS[13];

#define botaoDaCampainha 13
#define fechadura 12
#define alarme 11

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

boolean alarmeAtivado(){
 return digitalRead(alarme)==HIGH;
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

boolean existeAlgumSMSNoSIMCard(){
 posicao =  sms.IsSMSPresent(SMS_UNREAD);
 return (int)posicao>0 && (int)posicao<=20;
}

boolean telefoneQueEnviouOSMSEstaCadastrado(){
 char *telefoneCadastrado = "+556792874764"; 
 return strstr(telefoneDoSMS,telefoneCadastrado);
}

boolean textoDoSMSContemCodigoDeAberturaDaFechadura(){
 char *codigoDaFechadura = "123";
 return strstr(textoDoSMS,codigoDaFechadura);
}

void verificarSeRecebeuSMS(){
  if(existeAlgumSMSNoSIMCard()){
     textoDoSMS[0]='\0';
     sms.GetSMS((int)posicao,telefoneDoSMS,textoDoSMS,180);
     if(telefoneQueEnviouOSMSEstaCadastrado()){
        analisaTextoDoSMS();
        deletaSMS();
      }else{
        escreveNoDisplay("Telefone Nao","Cadastrado");
        delay(100);
        deletaSMS();
       }
    }
}

void analisaTextoDoSMS(){
  if(textoDoSMSContemCodigoDeAberturaDaFechadura()){
    escreveNoDisplay("Abrindo","Fechadura");
    abreAFechadura();
   }else{
    escreveNoDisplay("Codigo","Invalido");
    }
  deletaSMS();
}

void abreAFechadura(){
   for (int i=0; i<10; i++){
     digitalWrite(fechadura,HIGH);
     delay(100);
     digitalWrite(fechadura,LOW);
     delay(100);
   }
}

void deletaSMS(){
  sms.DeleteSMS(posicao);
}  

void loop()
{
  if(alarmeAtivado()){
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
       verificarSeRecebeuSMS();
     }
 } else{
    escreveNoDisplay("Sistema","Desativado");
    delay(100);
  }
}


