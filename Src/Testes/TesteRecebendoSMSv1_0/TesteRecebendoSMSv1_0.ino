//Teste da Shield GSM Recebendo SMS e Acionando a Fechadura 
#include "SIM900.h"
#include <SoftwareSerial.h>
#include "sms.h"

SMSGSM sms;

int fechadura = 13;
char posicao;
char mensagem[180];
char numeroTelefonico[13];

void setup(){
  pinMode(fechadura, OUTPUT);
  numeroTelefonico[12]='\0';
  Serial.begin(9600);  
  gsm.begin(2400) 
}
void loop(){
  posicao=sms.IsSMSPresent(SMS_UNREAD);
    if((int)posicao>0 && (int)posicao<=20){
      mensagem[0]='\0';
      sms.GetSMS((int)posicao,numeroTelefonico,mensagem,180);
        if(strstr(message,"abrir")) digitalWrite(fechadura, HIGH);
	      sms.DeleteSMS((int)pos);
    }
  delay(5000);
}
