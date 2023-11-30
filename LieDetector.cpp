#include <Wire.h>
#include <LiquidCrystal_I2C.h>

float voltage = 0;
float LastVoltage = 0;
float rate = 0;
float ROC = 0;
unsigned long lastTime = 0;
unsigned long lastVoltage = 0;
float TruthROC = .5;
float percentage = 0;
float lvoltage1 = 0;
float lvoltage2 = 0;
const int PIN_RED   = 8;
const int PIN_GREEN = 4;
const int PIN_BLUE  = 7;

unsigned long dt = 100;

LiquidCrystal_I2C lcd(0x27, 20, 4); 
void setup(){
    Serial.begin(9600);
    lcd.init();
  lcd.backlight();
    int sensorValue = analogRead(A0);
  lvoltage1 = sensorValue * (5.0 / 1023.0);

pinMode(PIN_RED,   OUTPUT);
pinMode(PIN_GREEN, OUTPUT);
pinMode(PIN_BLUE,  OUTPUT);
  
  }

void loop() {
  
  
if (millis() - lastTime  >= dt)
  {
    lastTime = millis();
    int sensorValue = analogRead(A0);
    voltage = sensorValue * (5.0 / 1023.0);

    rate = (voltage-LastVoltage);
    ROC = abs((1000*rate/dt));
    LastVoltage = voltage;

    Serial.print("Voltage: ");
    Serial.println(voltage);
    Serial.print("Rate of Change: ");
    Serial.println(ROC);
    Serial.print("Lie or Truth? ");
  }
if(abs(ROC)> TruthROC){
  delay(1000);
  int sensorValue = analogRead(A0);
  lvoltage2 = sensorValue * (5.0 / 1023.0);
  if(lvoltage2 > lvoltage1 + (0.1*lvoltage1)){
    delay(1000);
percentage = 100*(lvoltage1/lvoltage2);
 lcd.clear();  // Clear the LCD display
  lcd.setCursor(3, 0);
  lcd.print(percentage);
  lcd.print("% ");
  lcd.print("Lie");
  
  delay(5000);
  lcd.clear();
}

}else{
  lcd.clear();  // Clear the LCD display
  lcd.setCursor(3, 0);
lcd.print("Truth");

}

delay(2000);
} 
