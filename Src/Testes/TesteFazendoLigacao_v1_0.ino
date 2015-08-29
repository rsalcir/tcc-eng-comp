#include "SIM900.h"
#include <SoftwareSerial.h>
#include "call.h"
 
CallGSM call;
 
void setup()
{
   Serial.begin(9600);
     Serial.println("Testando GSM Shield...");
     pinMode(8,INPUT);
     if (gsm.begin(2400))
          Serial.println("nstatus=READY");
     else Serial.println("nstatus=IDLE");
}
 
void loop(){
  if(digitalRead(8)==HIGH){
      Serial.println("ligando");
      call.Call("92874764");
       if(digitalRead(8)==HIGH){
          Serial.println("desligando");
          call.HangUp();
       }
  }
}
