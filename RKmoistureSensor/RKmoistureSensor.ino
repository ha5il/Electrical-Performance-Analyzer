/*
  If Sensor value is 1023 --> No moisture; turn on Red Led
  If Sensor value is 0 --> High moisture; turn on everything
*/

// Declare Moisture Level
int Lowest = 360;
int Low = 410;
int Normal = 615;
int High = 820;
int Heighest = 1024;

int buzzer = 11;
int greenLed = 2;
int yellowLed1 = 4;
int yellowLed2 = 7;
int redLed = 8;
int sensor = A0;
int rawData = 0;

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed1, OUTPUT);
  pinMode(yellowLed2, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop() {
  rawData = analogRead(sensor);
  Serial.println (rawData);
  if (rawData < Lowest)
  {
    digitalWrite(redLed, HIGH);
    digitalWrite(yellowLed2, HIGH);
    digitalWrite(yellowLed1, HIGH);
    digitalWrite(greenLed, HIGH);
    digitalWrite(buzzer, HIGH);
  }
  else if (rawData < Low)
  {
    digitalWrite(redLed, HIGH);
    digitalWrite(yellowLed2, HIGH);
    digitalWrite(yellowLed1, HIGH);
    digitalWrite(greenLed, HIGH);
    digitalWrite(buzzer, LOW);
  }
  else if (rawData < Normal)
  {
    digitalWrite(redLed, HIGH);
    digitalWrite(yellowLed2, HIGH);
    digitalWrite(yellowLed1, HIGH);
    digitalWrite(greenLed, LOW);
    digitalWrite(buzzer, LOW);
  }
  else  if (rawData < High)
  {
    digitalWrite(redLed, HIGH);
    digitalWrite(yellowLed2, HIGH);
    digitalWrite(yellowLed1, LOW);
    digitalWrite(greenLed, LOW);
    digitalWrite(buzzer, LOW);
  }
  else  if (rawData < Heighest)
  {
    digitalWrite(redLed, HIGH);
    digitalWrite(yellowLed2, LOW);
    digitalWrite(yellowLed1, LOW);
    digitalWrite(greenLed, LOW);
    digitalWrite(buzzer, LOW);
  }
  delay (1000);
}

