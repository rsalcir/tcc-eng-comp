//Teste da Shield GSM Realizando Uma Ligação
#include "SIM900.h"
#include <SoftwareSerial.h>
#include "call.h"
 
CallGSM call;
#define botao 8
 
void setup()
{
   pinMode(botao,INPUT);
   Serial.begin(9600);
   gsm.begin(2400);
}
 
void loop(){
  Serial.println("Testando GSM Shield...");
  if(digitalRead(botao)==HIGH){
      Serial.println("ligando para 92874764");
      call.Call("92874764");
      delay(10000);
      Serial.println("Encerrando a chamada");
      call.HangUp();
  }
}

