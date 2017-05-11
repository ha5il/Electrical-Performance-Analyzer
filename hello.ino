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
File file;

void setup()
{
  pinMode(analogInput, INPUT);
  Serial.begin(9600);

  initializeSD();
  createFile("test.txt");
  writeToFile("============> New Data! <============");
  closeFile();
}
void loop()
{
  val = analogRead(tempPin);
float mv = ( val/1024.0)*5000; 
float cel = mv/10;

   value = analogRead(analogInput);
   vout = (value * 5.0) / 1024.0;
   vin = vout / (R2/(R1+R2)); 

Serial.print("TEMPRATURE = ");
Serial.print(cel);
Serial.print("*C");
Serial.println();

  createFile("test.txt");
    file.println(cel);
  closeFile();

Serial.print("INPUT V= ");
Serial.println(vin);

  createFile("test.txt");
    file.println(vin);
  closeFile();
  
delay(1000);
}

void initializeSD()
{
  Serial.println("Initializing SD card...");
  pinMode(CS_PIN, OUTPUT);

  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
}

int createFile(char filename[])
{
  file = SD.open(filename, FILE_WRITE);

  if (file)
  {
    Serial.println("File created successfully.");
    return 1;
  } else
  {
    Serial.println("Error while creating file.");
    return 0;
  }
}

int writeToFile(char text[])
{
  if (file)
  {
    file.println(text);
    Serial.println("Writing to file: ");
    Serial.println(text);
    return 1;
  } else
  {
    Serial.println("Couldn't write to file");
    return 0;
  }
}

void closeFile()
{
  if (file)
  {
    file.close();
    Serial.println("File closed");
  }
}

int openFile(char filename[])
{
  file = SD.open(filename);
  if (file)
  {
    Serial.println("File opened with success!");
    return 1;
  } else
  {
    Serial.println("Error opening file...");
    return 0;
  }
}
