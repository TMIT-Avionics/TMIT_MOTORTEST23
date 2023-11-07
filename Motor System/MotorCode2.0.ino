#include <SD.h>

#define key    38                                         //LED and Peripherals
#define arm    37
#define launch 35
#define comms  36
#define load   34
#define D1     18

File logFile;
float timeStamp = 0;

String output = "NULL";
int wheatStone;
float strain  = 0.0;

String receive;

typedef enum {                                            //State Machine Init
  SAFE,
  ARMED,
  LAUNCHED,
  FAILURE
} STATE;

STATE currentState = SAFE;

void logData() {
  if (logFile) {
    logFile.print(timeStamp, 2);
    logFile.print(",");
    logFile.print(output);
    logFile.print(",");
    logFile.println(strain, 2);
    logFile.flush();
  }
}

void Peripherals() {
  if (Serial5.available()) {
    output = Serial5.readStringUntil(',');
    wheatStone = analogRead(A15);
    strain = 1.4 * wheatStone / 1023;
    timeStamp = millis();
    timeStamp /= 1000;
    logData();
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Serial Comms. Initialised. ");
  Serial1.begin(9600);
  Serial.println("XBee Comms. initialised. ");
  Serial5.begin(9600);
  Serial.println("Load Cell Comms. Initialised. ");

  pinMode(key,    OUTPUT);                                //first three lines :-
  pinMode(arm,    OUTPUT);                                //LED configurations
  pinMode(launch, OUTPUT);
  pinMode(D1,     OUTPUT);
  pinMode(load,   OUTPUT);
  
  digitalWrite(D1, LOW);                                  //set D4184 for SAFETY
  digitalWrite(key, HIGH);

  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("SD CARD failed to initialize. ");
  } else {
    Serial.println("SD CARD initialized. ");
  }

  if (SD.exists("dataLog.csv")) {
    SD.remove("dataLog.csv");
    Serial.println("File Refreshed.");
  }

  logFile = SD.open("dataLog.csv", FILE_WRITE);
  if (logFile) {
    logFile.println("Time(s),LoadCell(kg),StrainGauge(%)");
    Serial.println("File initialized. ");
  } else {
    Serial.println("Unable to setup logFile. Logging Failed.");
  }

}

STATE getCurrentState() {                                  //Get current state 
  return currentState;
}

void checkInput() {                                       //Process received string
  if (receive == "ARMON" && currentState == SAFE) {
    Serial.println("CURRENT STATE: ARMED. ");
    currentState = ARMED;
    return;
  }
  else if (receive == "ARMOFF" && currentState == ARMED) {
    Serial.println("CURRENT STATE: SAFE. ");
    currentState = SAFE;
    return;
  }
  else if (receive == "LAUNCH" && currentState == ARMED) {
    Serial.println("CURRENT STATE: LAUNCHED. ");
    currentState = LAUNCHED;
    return;
  }
  else {
    //Serial.println("INVALID INPUT PROVIDED. ");
    return;
  }
}

void performOperation(STATE current) {                    //Perform Operation in State
  switch(current) {
    case SAFE:
      digitalWrite(key, HIGH);
      digitalWrite(arm, LOW);
      digitalWrite(launch, LOW);
      break;
    case ARMED:
      digitalWrite(key, HIGH);
      digitalWrite(arm, HIGH);
      digitalWrite(launch, LOW);
      break;
    case LAUNCHED:
      digitalWrite(key, HIGH);
      digitalWrite(arm, HIGH);
      digitalWrite(launch, HIGH);
      digitalWrite(D1,  HIGH);    //D4184 is pulled HIGH
      while (true) {
        Peripherals();
      }
      break;
    case FAILURE:
      break;
    default:
      break;
  }
}

void loop() {
  if (Serial1.available()) {
    receive = Serial1.readStringUntil('\n');
    Serial.println(receive);

    checkInput();
    performOperation(getCurrentState());
  }
}
