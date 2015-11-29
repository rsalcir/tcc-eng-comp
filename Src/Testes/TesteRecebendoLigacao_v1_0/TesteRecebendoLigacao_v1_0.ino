//Bibliotecas
#include "SIM900.h"
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "sms.h"
#include "call.h"
  
SMSGSM sms;
int LED = 13;
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);
boolean started=false;
boolean statusLed =false;
char pos;
char message[180];
char number[13];
char *smsDisplayOn;
char *smsDisplayOff;

void setup()

{
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  lcd.begin (16,2);
  number[12]='\0';
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
  if(started)
  {
  lcd.clear();
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("Aguardando SMS");
  delay(1000);
    
    pos=sms.IsSMSPresent(SMS_UNREAD);

    if((int)pos>0 && (int)pos<=20)

    {

      message[0]='\0';

      sms.GetSMS((int)pos,number,message,180);

      smsDisplayOn = strstr(message,"On");

      smsDisplayOff = strstr(message,"Off");

     
      if(smsDisplayOn){
        digitalWrite(LED, HIGH);
        statusLed = true;
        lcd.clear();
        lcd.setBacklight(HIGH);
        lcd.setCursor(0,0);
        lcd.print("SMS ON");
        lcd.setCursor(0,1);
        lcd.print("Recebido");
        delay(1000);
      }
      
      if(smsDisplayOff){
        digitalWrite(LED, LOW);
        statusLed = false;
        lcd.clear();
        lcd.setBacklight(HIGH);
        lcd.setCursor(0,0);
        lcd.print("SMS OFF");
        lcd.setCursor(0,1);
        lcd.print("Recebido");
        delay(1000);
      }
      
      sms.DeleteSMS((int)pos);
    }

switch (call.CallStatus())
  {
    case CALL_NONE: // Nothing is happening
        lcd.clear();
        lcd.setBacklight(HIGH);
        lcd.setCursor(0,0);
        lcd.print("CALL_NONE");
      break;

    case CALL_INCOM_VOICE : // Yes! Someone is calling us
        lcd.clear();
        lcd.setBacklight(HIGH);
        lcd.setCursor(0,0);
        lcd.print("CALL_INCOM_VOICE");
       call.PickUp();
       lcd.clear();
        lcd.setBacklight(HIGH);
        lcd.setCursor(0,0);
        lcd.print("call.PickUp");
      break;

    case CALL_COMM_LINE_BUSY:  // In this case the call would be established
      lcd.clear();
        lcd.setBacklight(HIGH);
        lcd.setCursor(0,0);
        lcd.print("CALL_COMM_LINE_BUSY");;
      break;
  }

      if(statusLed){
        lcd.clear();
        lcd.setBacklight(HIGH);
        lcd.setCursor(0,0);
        lcd.print("LED Aceso");
        delay(1000);
      }else{
        lcd.clear();
        lcd.setBacklight(HIGH);
        lcd.setCursor(0,0);
        lcd.print("LED Apagado");
        delay(1000);
      }

    delay(2000);

  }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


