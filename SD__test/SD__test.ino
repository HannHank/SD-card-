
/*
  SD card read/write

 This example shows how to read and write data to and from an SD card file
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4

 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

#include <SPI.h>
#include <Wire.h>
#include <SD.h>
#include "DHT.h"
#include "Sodaq_DS3231.h"
File myFile;
#define DHTPIN 2     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHT11, 15);
int min;
int hour;

void setup() {
    dht.begin();
    Wire.begin();
    rtc.begin();
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
 

  // if the file opened okay, write to it:
 

  // re-open the file for reading:
/*  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  /*/
}

void loop() {
  String dataString = "";
  DateTime now = rtc.now(); 
  min = now.minute();
  hour = now.hour();
  float neueTemp = dht.readTemperature();
  dataString += hour;
  dataString += ":";
  dataString += min;
  dataString += ",";
  dataString += "Temperatur =";
  dataString += neueTemp;
  myFile = SD.open("test.txt", FILE_WRITE);
  // nothing happens after setup
  if (myFile) {
  Serial.print("Writing to test.txt...");
  myFile.println(dataString);
  // close the file:
  myFile.close();
  Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
   myFile.close();
   delay(10000);
}

