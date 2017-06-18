#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 9, 8, 7, 6);

int analogInput = A1;          //Voltage sensor to Analog 1
float vout = 0.0;
float vin = 0.0;
float R1 = 30000.0;            //Two resistances on voltage sensor
float R2 = 7500.0;             //Its actually an voltage divider circuit
int value = 0;

int analogIn = A3;             //Current sensor to Analog 3
int mVperAmp = 185;            // use 100 for 20A Module and 66 for 30A Module
int RawValue = 0;
int ACSoffset = 2500;
double Voltage = 0;
double Amps = 0;

int yellowLed = 2;             //Leds to Digital 2 3 and 4
int greenLed = 3;
int redLed = 4;
int buzzer = 5;                //Buzzer to Digital 5

int i;                         //Counter variable for loops
int loopCount = 0;
void setup()
{
  pinMode(buzzer, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(3, 0);
  lcd.print("Electrical Performance Analyser");
  for (i = 1; i < 20; i++)
  {
    lcd.scrollDisplayLeft();
    delay(150);
  }
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Initializing...");
  lcd.setCursor(3, 1);
  lcd.print("Glowing LEDs");
  for (i = 1; i < 3; i++)
  {
    digitalWrite(redLed, HIGH);
    delay(250);
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    delay(250);
    digitalWrite(greenLed, LOW);
    digitalWrite(yellowLed, HIGH);
    delay(250);
    digitalWrite(yellowLed, LOW);
    digitalWrite(buzzer, HIGH);
    delay(25);
    digitalWrite(buzzer, LOW);
  }
}
void loop()
{
  for (i = 1; i < 3; i++)             //Double blink loop for hearbeat efect
  {
    digitalWrite(greenLed, HIGH);
    delay(10);                         //Green led turns ON only for a millisecord
    digitalWrite(greenLed, LOW);
    delay(100);                       //Delay gives an heartbeat effect to Arduino
  }

  lcd.clear();

  //------------------------------------Voltage------------------------------------
  value = analogRead(analogInput);
  vout = (value * 5.0) / 1024.0;
  vin = vout / (R2 / (R1 + R2));

  lcd.setCursor(0, 0);
  lcd.print("Vltg=");
  lcd.print(vin);
  lcd.print("V");

  //------------------------------------Current------------------------------------
  RawValue = analogRead(analogIn);
  Voltage = (RawValue / 1024.0) * 5000;   // Gets you mV
  Amps = ((Voltage - ACSoffset) / mVperAmp);
  Amps = abs(Amps * 1000);                //Current in milli and always positive

  lcd.setCursor(0, 1);
  lcd.print("Crnt=");
  lcd.print(Amps);
  lcd.print("mA");

  //-----------------------------------Loop Count----------------------------------
  lcd.setCursor(13, 0);
  loopCount++;
  lcd.print(loopCount);

}
