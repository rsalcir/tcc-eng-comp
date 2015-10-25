//Teste Do Componente Display LCD 16x2 Com Modulo I2C
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inicialização do display LCD no endereco 0x27 do modulo I2C
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);
 
void setup()
{
 lcd.begin (16,2);
}
 
void loop()
{
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("Teste Display");
  lcd.setCursor(0,1);
  lcd.print("LCD e modulo I2C");
  delay(1000);
}

