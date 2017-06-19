#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 10, 9, 7, 6);

int tempPin = A0, val;              //Temperature sensor to Analog 0
float mv, cel;

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

int proxyPin = 8;              //Proximity sensor to Digital 8
int proxyRaw = 0;
unsigned long startTime = 0;
unsigned long elapsedTime = 0;
int rpm = 0;

int yellowLed = 2;             //Leds to Digital 2 3 and 4
int greenLed = 3;
int redLed = 4;
int buzzer = 5;                //Buzzer to Digital 5

int i;                         //Counter variable for loops

byte customChar_tempr_logo[8] = {B11000, B11011, B00111, B01100, B01100, B01100, B00111, B00011};
void setup()
{
  pinMode(buzzer, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(3, 0);
  lcd.print("Electrical Performance");
  lcd.setCursor(14, 1);
  lcd.print("Analyser");
  for (i = 1; i < 15; i++)
  {
    lcd.scrollDisplayLeft();
    delay(150);
  }
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Initializing...");
  lcd.setCursor(2, 1);
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
  // Create logo or symbol
  lcd.createChar(0, customChar_tempr_logo);
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
  //----------------------------------Temperature----------------------------------
  val = analogRead (tempPin);
  mv = ( val / 1024.0) * 5000;
  cel = mv / 10;
  lcd.setCursor(10, 1);
  lcd.print(cel);
  lcd.write(byte(0));
  //------------------------------------Voltage------------------------------------
  value = analogRead(analogInput);
  vout = (value * 5.0) / 1024.0;
  vin = vout / (R2 / (R1 + R2));

  lcd.setCursor(0, 0);
  lcd.print(vin);
  lcd.print("V");

  //------------------------------------Current------------------------------------
  RawValue = analogRead(analogIn);
  Voltage = (RawValue / 1024.0) * 5000;   // Gets you mV
  Amps = ((Voltage - ACSoffset) / mVperAmp);
  Amps = abs(Amps * 1000);                //Current in milli and always positive

  lcd.setCursor(8, 0);
  lcd.print(Amps);
  lcd.print("mA");

  //-------------------------------------Speed-------------------------------------
  digitalWrite(yellowLed, HIGH);       //YellowLed ON
  
  startTime = millis();                //Its Loop in time for break, will be replaced once out of loop
  while (digitalRead(proxyPin) == 0);  //Wait until signal is received
  
  digitalWrite(yellowLed, LOW);        //Metal is sensed so turn YellowLed OFF
  startTime = millis();                //Record the current time of Arduino session
  delay(10);                           //Wait 10ms so that fan blade moves away from sensor

  digitalWrite(yellowLed, HIGH);
  while (digitalRead(proxyPin) == 0);  //Wait until signal is received
  digitalWrite(yellowLed, LOW);
  elapsedTime = millis();              //Record the session time when metal is re-sensed

  rpm = (60000 / (elapsedTime - startTime));  //Unitary method: 1 rotation ----> x millisecond
  
  lcd.setCursor(0, 1);
  lcd.print(rpm);
  lcd.print("RPM");

}
