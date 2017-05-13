#include <Firmata.h>

int yellowLed = 2;
int greenLed = 3;
int redLed = 4;
int buzzer = 5;

void setup ()
{
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Firmata.begin(9600);
  Firmata.setPinMode(yellowLed, OUTPUT);

}

void loop ()
{
Firmata.sendString("Hello");
delay (1000);
}

