int sensorPin = A0;                         // Moisture Sensor location
int led = 11;                               // Led connected pin
int rawData;                                // Holds sensor value

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(led, OUTPUT);                     // Pins declared whether input or output
  Serial.begin(9600);                       // Using 9600 baudrate to print on Arduino IDE for easier debugging
}

void loop() {
  rawData = analogRead(sensorPin);          // Get raw data from sensor
  rawData = map (rawData, 1023, 0, 0, 255); /* Sensor shows 1023 when on no moisture
                                               mapping 1023 from sensor as 0
                                               and 0 from sensor as 255              */
  Serial.println(rawData);                  // Printing to Arduino IDE console
  analogWrite(led, rawData);                /* Compare with analogWrite(led, brightness)
                                               0 = Min Illuminance i.e., OFF
                                               255 = Max Illuminance                 */
  delay(1000);                              // Wait a sec before starting another loop
}
