#include <SD.h>
#include <SPI.h>               //Serial Peripheral Interface for SD card pins

////////////////////////////////////////////////////////

///////////////////////////////////////////////////////
int CS_PIN = 10;               //Only pin that can be varied for sd module

int tempPin = A0;              //Temperature sensor to Analog 0
int val;

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

int proxyPin = 8;              //Proximity sensor to Digital 8
int proxyRaw = 0;
unsigned long startTime = 0;
unsigned long elapsedTime = 0;
int rpm = 0;

int i;                         //Counter variable for loops
File file;                     // 'file' is File data type (like i is int data type)

int rawTempDataToSmooth [10];      // For temperature
int indexTemp = 0;                 // For temperature
/*
   Setup runs only once when arduino starts.
   All the initialization things has to be done here
   like declaring input and output pins.
*/
void setup()
{
  pinMode(analogInput, INPUT);
  pinMode(proxyPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  Serial.begin(9600);

  /* Checking if led and buzzer are
     workng well. Everytime you reset
     or restart this code runs once   */
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
  initializeSD();

  /*CSV file should contain parameters on first line.
    If no csv file exists we write the first line.    */
  if (SD.exists("data.csv"))
  {
    Serial.println("Old Data found on SD Card, Continuing with it");
  }
  else  {
    createFile("data.csv");
    writeToFile("Temperature,Voltage,Current,Speed");
    closeFile();
  }
  initializeRawTempDatas(1);         // 1 --> Smoothing required; any int character if not required
}

/* The loop function runs always.
   Unless the Arduino is reset or restarted,
   the setup doesn'r run again               */
void loop()
{
  for (i = 1; i < 3; i++)             //Double blink loop for hearbeat efect
  {
    digitalWrite(greenLed, HIGH);
    delay(1);                         //Green led turns ON only for a millisecord
    digitalWrite(greenLed, LOW);
    delay(100);                       //Delay gives an heartbeat effect to Arduino
  }

  /* Now the Analog signals are read, processed, printed
     serially (to USB or Bluetooth) and stored to SD card */

  //----------------------------------Temperature----------------------------------
  //...............................FOR SMOOTHING.......................................

  //..................................................................................


  float mv = ( val / 1024.0) * 5000;
  float cel = mv / 10;

  Serial.print("Temperature *C     :  ");
  Serial.println(cel);

  createFile("data.csv");
  file.print(cel);
  closeFile();

  //------------------------------------Voltage------------------------------------
  value = analogRead(analogInput);
  vout = (value * 5.0) / 1024.0;
  vin = vout / (R2 / (R1 + R2));

  //Removing offset reading. We will be at least using 1.2V battery
  if (vin < 0.5)
  {
    vin = 0;
  }

  Serial.print("Supply Voltage (V) :  ");
  Serial.println(vin);

  createFile("data.csv");
  file.print(",");
  file.print(vin);
  closeFile();

  //------------------------------------Current------------------------------------
  RawValue = analogRead(analogIn);
  Voltage = (RawValue / 1024.0) * 5000;   // Gets you mV
  Amps = ((Voltage - ACSoffset) / mVperAmp);
  Amps = abs(Amps * 1000);                //Current in milli and always positive

  //Forcing current to be 0 if voltage is 0.5 or less. If not internal offset current is seen
  if (vin == 0)
  {
    Amps = 0;
  }

  Serial.print("Current (mA)       :  ");
  Serial.println(Amps);

  createFile("data.csv");
  file.print(",");
  file.print(Amps);
  closeFile();

  //-------------------------------------Speed-------------------------------------
  /*As soosn as Arduino starts, a timer is also starts.
    millis() function returns milliseconds of this timer.
    This overflow (go back to zero), after approximately 50 days.*/
  digitalWrite(yellowLed, HIGH);       //YellowLed ON

  startTime = millis();                //Its Loop in time for break, will be replaced once out of loop
  while (digitalRead(proxyPin) == 0)  //Wait until Proximity sensor senses metatl
  {
    if (millis() - startTime >= 600) break; // for 600 ms speed is 100 RPM, considered as minimum speed
  }

  digitalWrite(yellowLed, LOW);        //Metal is sensed so turn YellowLed OFF
  startTime = millis();                //Record the current time of Arduino session
  delay(10);                           //Wait 10ms so that fan blade moves away from sensor

  digitalWrite(yellowLed, HIGH);
  while (digitalRead(proxyPin) == 0)
  {
    if (millis() - startTime >= 600) break;
  }
  digitalWrite(yellowLed, LOW);
  elapsedTime = millis();              //Record the session time when metal is re-sensed

  Serial.print("Speed (RPM)        :  ");
  rpm = (60000 / (elapsedTime - startTime));  //Unitary method: 1 rotation ----> x millisecond

  /* If motor doesn't rotate rpm is calculated as 6000
    // so Forcing speed to be 0. Anyway max speed cant be above 1500 or 2000 */
  if (rpm > 5000 || rpm < 102) // You get RPM less than 102, when motor isn't rotating. This is due to break command which takes 600 ms to operate
  {
    rpm = 0;
  }
  Serial.println(rpm);
  Serial.println();

  createFile("data.csv");
  file.print(",");
  file.println(rpm);
  closeFile();

  delay(1000);                               /*Wait 1 second before taking another reading
                                               Decrease or Increase it as per the rate of readings desired*/
}

/*------------------------------------------------------------------------------------------------------
  ------------------------------------------END OF PROGRAM----------------------------------------------
  ------------------------------------------------------------------------------------------------------*/
void initializeSD()
{
  Serial.println("Initializing SD card...");
  pinMode(CS_PIN, OUTPUT);                   // initializeSD is called from setup loop, so setting pin mode

  if (SD.begin())
  {
    //  Serial.println("SD card is ready to use.");  --> Uncomment while debugging
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
    //  Serial.println("File created successfully.");  --> Uncomment this and like this while debugging
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
    file.println(text);
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

void initializeRawTempDatas(int required)
{
  if (required == 1)
  {
    {
      for (i = 0; i < 10; i++)
      {
        rawTempDataToSmooth[i] = analogRead (tempPin);
        Serial.println (rawTempDataToSmooth[i]);
      }
    }

    rawTempDataToSmooth [indexTemp] = analogRead (tempPin);
    indexTemp++;
    if (indexTemp >= 10) indexTemp = 0;
    val = (rawTempDataToSmooth[0] + rawTempDataToSmooth[1] + rawTempDataToSmooth[2] + rawTempDataToSmooth[3] + rawTempDataToSmooth[4] + rawTempDataToSmooth[5] + rawTempDataToSmooth[6] + rawTempDataToSmooth[7] + rawTempDataToSmooth[8] + rawTempDataToSmooth[9]) / 10;
  }

  else
  {
  }
}
