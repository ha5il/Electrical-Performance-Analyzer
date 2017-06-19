#include <LiquidCrystal.h>        // For LCD

LiquidCrystal lcd(5, 4, 3, 2, 1, 0);

int LDR = A1;
int CB1 = 8;
int CB2 = 9;
int CB3 = 10;
int CBS = 11;
int CBSLon = 12;
int CBSLoff = 13;
int ch;
int Pload = 0, sms = 0, done = 0, countN = 0, done1 = 0;

const int currentPin = A0;
const unsigned long sampleTime = 100000UL;                         // sample over 100ms, it is an exact number of cycles for both 50Hz and 60Hz mains
const unsigned long numSamples = 250UL;                            // choose the number of samples to divide sampleTime exactly, but low enough for the ADC to keep up
const unsigned long sampleInterval = sampleTime / numSamples;      // the sampling interval, must be longer than then ADC conversion time
const int adc_zero = 510;
float new1 = 0;                                        // relative digital zero of the arudino input from ACS712 (could make this a variable and auto-adjust it)
int val = 0;

void setup()
{
  // Declare the pins as Output
  pinMode(CB1, OUTPUT);
  pinMode(CB2, OUTPUT);
  pinMode(CB3, OUTPUT);
  pinMode(CBS, OUTPUT);
  pinMode(CBSLon, OUTPUT);
  pinMode(CBSLoff, OUTPUT);

  // Turn all ports Low i.e., turn all CB1, CB2,... off
  digitalWrite(CB1, LOW);
  digitalWrite(CB2, LOW);
  digitalWrite(CB3, LOW);
  digitalWrite(CBS, LOW);
  digitalWrite(CBSLon, LOW);
  digitalWrite(CBSLoff, LOW);

  lcd.begin(16, 2);                     // Divide LCD in 16 columns and 2 rows

  // GSM is Ready and we are turning all circuti breakes ON. Tripping (turning on) sound comes at this moment
  lcd.setCursor(0, 0);
  lcd.print("  Demand Side");
  lcd.setCursor(0, 1);
  lcd.print("   Management");
  delay(1500);
  digitalWrite(CB1, HIGH);
  digitalWrite(CB2, HIGH);
  digitalWrite(CB3, HIGH);
  lcd.clear();
  // Everything is ready i.e., setup function is over
}

// Program inside loop runs always
void loop()
{
  ACSread();                //Reading the current function
  StreetCtrl();               //Controlling the sreet function
}

// Current read function
void ACSread()
{
  unsigned long currentAcc = 0;
  unsigned int count = 0;
  unsigned long prevMicros = micros() - sampleInterval ;
  while (count < numSamples)
  {
    if (micros() - prevMicros >= sampleInterval)
    {
      int adc_raw = analogRead(currentPin) - adc_zero;
      currentAcc += (unsigned long)(adc_raw * adc_raw);
      ++count;
      prevMicros += sampleInterval;
    }
  }
  float rms = sqrt((float)currentAcc / (float)numSamples) * (75.7576 / 1024.0);
  new1 = new1 + rms;
  if (val == 10);
  {
    new1 = new1 / 10;
    new1 = new1 * 4.89;
    lcd.setCursor(0, 0);
    lcd.print("Demand =");
    lcd.print(new1, 2); // the '3' after voltage allows you to display 3 digits after decimal point
    delay(200);
    check();
    new1 = 0;
    val = 0;
  }
  val++;
}

void ACSread1()
{
  unsigned long currentAcc = 0;
  unsigned int count = 0;
  unsigned long prevMicros = micros() - sampleInterval ;
  while (count < numSamples)
  {
    if (micros() - prevMicros >= sampleInterval)
    {
      int adc_raw = analogRead(currentPin) - adc_zero;
      currentAcc += (unsigned long)(adc_raw * adc_raw);
      ++count;
      prevMicros += sampleInterval;
    }
  }

  float rms = sqrt((float)currentAcc / (float)numSamples) * (75.7576 / 1024.0);

  new1 = new1 + rms;

  if (val == 10);
  {
    new1 = new1 / 10;
    new1 = new1 * 4.89;
    lcd.setCursor(0, 0);
    lcd.print("Demand =");
    lcd.print(new1, 2);
    delay(200);
    new1 = 0;
    val = 0;
  }
  val++;
}

void check()
{
  if (new1 > 1.57)
  {
    lcd.clear();
    digitalWrite(CBS, LOW);
    digitalWrite(CB1, LOW);
    digitalWrite(CB2, LOW);
    digitalWrite(CB3, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Shut Down due 2");
    lcd.setCursor(0, 1);
    lcd.print(" Sys Over Load");
    delay(5000);
    done1 = 0;
  }
  if (new1 < 0.83)
  {
    if (done == 0);
    {
      digitalWrite(CBS, LOW);
      digitalWrite(CB1, HIGH);
      digitalWrite(CB2, HIGH);
      digitalWrite(CB3, HIGH);
      lcd.setCursor(0, 1);
      lcd.print("   Normal Load  ");
      delay(200);
      done1 = 1;
    }
  }
  if (new1 > 0.8 && new1 < 1.3)
  {
    lcd.clear();
    digitalWrite(CB3, LOW);
    delay(100);
    Pload = 0;
    sms = 0;
    lcd.setCursor(0, 0);
    lcd.print(" Agri feeder ");
    lcd.setCursor(0, 1);
    lcd.print("Shut Dwn to MPL");
    delay(2000);
    done1 = 0;
  }
  if (new1 > 1.3 && new1 < 1.5)
  {
    if (sms == 0)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Sustainable Load");
      lcd.setCursor(0, 1);
      lcd.print("Snd Msg 2 HEC");
      sms = 1;
      delay(2000);
      done1 = 0;
    }
    Pload++;
  }
  if (Pload == 120)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CB2 Mall Breaker");
    lcd.setCursor(0, 1);
    lcd.print("Off to MSPL");
    digitalWrite(CB2, LOW);
    for (int k = 0; k < 10; k++)
    { delay(1000);
      ACSread1();
    }
    if (new1 >= 1.3)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("CB1 Indu Breaker");
      lcd.setCursor(0, 1);
      lcd.print("Off to MSPL");
      digitalWrite(CB1, LOW);
      delay(2000);
    }
    Pload = 0;
    done1 = 0;
    new1 = 0;
  }
}

void StreetCtrl()
{
  int LDRvalue = analogRead(LDR);
  if (LDRvalue > 600)
  {
    if (done == 0)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Good Evening");
      lcd.setCursor(0, 1);
      lcd.print("St Light Sw ON");
      digitalWrite(CBSLon, HIGH);
      digitalWrite(CBSLoff, HIGH);
      done = 1;
      delay(2000);
      lcd.clear();
    }
    countN++;
    if (countN == 75)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Some SL & H OFF");
      lcd.setCursor(0, 1);
      lcd.print(" 2 red Base Load");
      digitalWrite(CBSLoff, LOW);
      delay(2000);
      countN = 0;
      lcd.clear();
    }
  }
  if (LDRvalue < 400)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Good Morning");
    lcd.setCursor(0, 1);
    lcd.print("St Light Turn OFF");
    digitalWrite(CBSLoff, LOW);
    delay(2000);
    digitalWrite(CBSLon, LOW);
    done = 0;
    countN = 0;
    lcd.clear();
  }
}

