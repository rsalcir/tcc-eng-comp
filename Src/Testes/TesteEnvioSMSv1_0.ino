/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "SIM900.h"

#include <SoftwareSerial.h>

#include "sms.h"

  

SMSGSM sms;

int LED = 13;

boolean started=false;

char pos;

char message[180];

char number[13];

char *LedOn;

char *LedOff;

void setup()

{

  pinMode(LED, OUTPUT);

  digitalWrite(LED, LOW);

  number[12]='\0';

  Serial.begin(9600);

 

  if (gsm.begin(2400)) 

  {

    started=true;

    digitalWrite(LED, HIGH);

  }

}

void loop()

{

  if(started)

  {

    pos=sms.IsSMSPresent(SMS_UNREAD);

   

    if((int)pos>0 && (int)pos<=20)

    {

      message[0]='\0';

      sms.GetSMS((int)pos,number,message,180);

      LedOn = strstr(message,"Led on");

      LedOff = strstr(message,"Led off");

     

      if(LedOn)  digitalWrite(LED, HIGH);

      if(LedOff)  digitalWrite(LED, LOW);

     

      sms.DeleteSMS((int)pos);

    }

    delay(5000);

  }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
