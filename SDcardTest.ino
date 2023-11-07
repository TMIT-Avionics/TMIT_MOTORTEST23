#include <SD.h>
#include <SPI.h>


File logFile;
static int logCount = 0;
const int chipSelect = BUILTIN_SDCARD;

void setup() {
  Serial.begin(9600);
  Serial.println("Serial Comm. Initialised. \n");

  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialisation failed. \n");
    return;
  }
  else {
    Serial.println("SD Card Initialised. \n");
  }
  
  logFile = SD.open("T4.txt", FILE_WRITE);
  if (!logFile) {
    Serial.println("Couldn't open log file");
  } 
  else {
    Serial.println("Logging to SD card...");
  }
  
}

void loop() {
  if (logCount < 20) {
    logFile.println("SD CARD TEST.");
    logCount++;
    Serial.println("SD CARD TEST. ");
    delay(2000);
  }
  else {
    logFile.close();
    Serial.println("Logging Complete. File Closed. ");
    delay(2000);

  }
}
