#include <SD.h>
#include <SPI.h>

File file;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.begin(9600);
  initializeSD();
  file = SD.open("count.txt");
  Serial.print(file.read());
  file.close();
}


