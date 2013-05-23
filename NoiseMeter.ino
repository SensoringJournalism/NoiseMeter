/*
 Noise Meter Datalogger
  
 Matt Waite | Sensoring Journalism 2013
  
 This is highly, highly derivative of the work of Tom Igoe and his datalogger example code.
  
 
 This sketch takes input from one analog sensor and writes the values 
 to an SD card using the SD library.
 	
 The circuit:
 * output wire from sensor on analog pin 0
 ** CS - pin 4
 
 */

#include <SD.h>

// On the Ethernet Shield, CS is pin 4. Note that even if it's not
// used as the CS pin, the hardware CS pin (10 on most Arduino boards,
// 53 on the Mega) must be left as an output or the SD library
// functions will not work.
const int chipSelect = 4;

const int groundpin = 18;             // analog input pin 4 -- ground
const int powerpin = 19;              // analog input pin 5 -- voltage

int sensorValue = 0;

void setup()
{
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

void loop()
{
  int sensorValue = analogRead(A0);
  // Serial.println(analogValue);    // For debugging
     
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("noiselog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
     dataFile.print(sensorValue);
     dataFile.println();
     dataFile.close();
    // print to the serial port too:
    Serial.print(sensorValue);
    Serial.println();

    delay(10);
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  } 
}









