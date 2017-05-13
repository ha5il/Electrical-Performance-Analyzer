#include <SD.h>
#include <SPI.h>

int CS_PIN = 10;
int val;
int tempPin = A0;
int analogInput = A1;
float vout = 0.0;
float vin = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
int value = 0;
int analogIn = A3;
int mVperAmp = 185; // use 100 for 20A Module and 66 for 30A Module
int RawValue = 0;
int ACSoffset = 2500;
double Voltage = 0;
double Amps = 0;

int buzzer = 5;
int redLed = 4;
int greenLed = 3;
int yellowLed = 2;

int proxyPin = 8;
int proxyRaw = 0;
unsigned long startTime = 0;
unsigned long elapsedTime = 0;
int rpm = 0;
File file;

void setup()
{
  pinMode(analogInput, INPUT);
  pinMode(proxyPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  Serial.begin(9600);

  //checking led and buzzer
  for (int i = 1; i < 3; i++)
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
  initializeSD();
  if (SD.exists("data.csv"))
  {

  }
  else  {
    createFile("data.csv");
    writeToFile("Temperature,Voltage,Current,Speed");
    closeFile();
  }
}
void loop()
{
  digitalWrite(greenLed, HIGH);
  delay(1);
  digitalWrite(greenLed, LOW);

  val = analogRead(tempPin);
  float mv = ( val / 1024.0) * 5000;
  float cel = mv / 10;

  value = analogRead(analogInput);
  vout = (value * 5.0) / 1024.0;
  vin = vout / (R2 / (R1 + R2));

  Serial.print("Temperature    :  ");
  Serial.print(cel);
  Serial.println("*C");

  createFile("data.csv");
  file.print(cel);
  closeFile();

  Serial.print("Supply Voltage :  ");
  Serial.println(vin);

  createFile("data.csv");
  file.print(",");
  file.print(vin);
  closeFile();

  RawValue = analogRead(analogIn);
  Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
  Amps = ((Voltage - ACSoffset) / mVperAmp);


  Serial.print("Supply Current :  ");
  Serial.println(Amps);

  createFile("data.csv");
  file.print(",");
  file.print(Amps);
  closeFile();

  digitalWrite(yellowLed, HIGH);
  while (digitalRead(proxyPin) == 0);
  digitalWrite(yellowLed, LOW);
  startTime = millis();
  delay(10);

  digitalWrite(yellowLed, HIGH);
  while (digitalRead(proxyPin) == 0);
  digitalWrite(yellowLed, LOW);
  elapsedTime = millis();

  createFile("data.csv");
  file.print(",");
  file.println(rpm);
  closeFile();

  Serial.print("Speed          :  ");
  rpm = (60000 / (elapsedTime - startTime));
  Serial.println(rpm);
Serial.println();

  delay(1000);
}

void initializeSD()
{
  Serial.println("Initializing SD card...");
  pinMode(CS_PIN, OUTPUT);

  if (SD.begin())
  {
    //  Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    digitalWrite(redLed, HIGH);
    digitalWrite(buzzer, HIGH);
    return;
  }
}

int createFile(char filename[])
{
  file = SD.open(filename, FILE_WRITE);

  if (file)
  {
    //  Serial.println("File created successfully.");
    return 1;
  } else
  {
    // Serial.println("Error while creating file.");
    return 0;
  }
}

int writeToFile(char text[])
{
  if (file)
  {
    //  file.println(text);
    // Serial.println("Writing to file: ");
    //  Serial.println(text);
    return 1;
  } else
  {
    //  Serial.println("Couldn't write to file");
    return 0;
  }
}

void closeFile()
{
  if (file)
  {
    file.close();
    //  Serial.println("File closed");
  }
}

int openFile(char filename[])
{
  file = SD.open(filename);
  if (file)
  {
    // Serial.println("File opened with success!");
    return 1;
  } else
  {
    //  Serial.println("Error opening file...");
    return 0;
  }
}

