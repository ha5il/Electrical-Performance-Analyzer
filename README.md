# Electrical Performance Analyzer

> An Arduino UNO based project for data recording with analysis by PHP code or console app

**These are the codes written for following hardware components interfaced to Arduino UNO**

- SD Card Module
- Bluetooth Module
- Voltage Sensor
- Current Sensor
- Speedometer
- LEDs
- Buzzer
- RTC Module


## Download the latest Release

This is offline DATA.CSV analyser for Windows [32 bit system](https://github.com/ha5il/Electrical-Performance-Analyzer/raw/master/Performance%20Analyser/Release/Performance%20Analyser.exe) and [64 bit System](https://github.com/ha5il/Electrical-Performance-Analyzer/raw/master/Performance%20Analyser/x64/Release/Performance%20Analyser.exe)

View the [Sample File](https://github.com/ha5il/Electrical-Performance-Analyzer/raw/master/Performance%20Analyser/SAMPLE.CSV) for the console app.

## Online Analysis
Online analysis through PHP code is available [here.](http://hasilpaudyal.com.np/performance-analysis/)

## Main Features
- Logging DC Motor parameters to SD card.
- Bluetooth connect enables to view real-time values.
- Automated Software analysis on logged data to get a solution for better performance. 

### Analysis by PHP
Server side code is written to analyse DATA.CSV file.

### Analysis by Console Application
This app is written in C/C++ in Visual Basic 2017 for analysis of DATA.CSV.

### Processing for real-time graph
Current we are able to draw a real-time graph for any one parameter.

## Future Developments

### Firmata can be continued...
There are some standards to be followed to build Firmata based app and code on Arduino. Yes, this will make everything real-time including the dynamic graph feature that can be directly viewed on any Bluetooth enabled device.

### Warning operator before instability
As data is sent to server from n number of motors, whenever the same kind of performance issue is detected by Arduino which had created instability, the operator can be warned to not to go inside such zone.
