/*
Final ground station code for motor test 2023.
Components-
  Teensy 4.1 microcontroller.
  Xbee for communication 
*/

//pin definitions
const int KeyLED = 38;
const int ArmLED = 37;
const int LaunchLED = 35;
const int KEY_PIN = 29;
const int ARM_PIN = 28;
const int LAUNCH_PIN = 33;

// States present in the FSM.
typedef enum {
  KEY,
  ARM,
  LAUNCH,
} States;

States Current_state = KEY;        //Initial state of the board is KEY.
char message[7];                   //message array that is being transmitted.
byte* mess = (byte*)&message;      //Xbees read and transmit bytes.Hence the address is being typecasted to byte address.

void setup(){
  pinMode(KeyLED, OUTPUT);
  pinMode(ArmLED, OUTPUT);
  pinMode(LaunchLED, OUTPUT);
  pinMode(KEY_PIN, INPUT_PULLDOWN); //Configured input pulldown to ensure no floating value.
  pinMode(ARM_PIN, INPUT_PULLDOWN);
  pinMode(LAUNCH_PIN, INPUT_PULLDOWN);

  Serial.begin(9600);
  Serial1.begin(9600);              //Xbee serial communication using Serial1. 
}

void loop(){
  switch (Current_state) {
    case KEY:
      digitalWrite(KeyLED,HIGH);  //Initial state KEY hence KeyLED it will remain HIGH.
      if (digitalRead(ARM_PIN) == HIGH) {
        digitalWrite(ArmLED,HIGH);
        Current_state = ARM;      //If ARM pin has been switched ON then Current_State changes to ARM.
        strcpy(message, "ARMON");
        Serial.println("Current state = ARM");
        Serial1.write(mess, sizeof(message));  //If not working try message.
        delay(1000);              //Delays are necessary when transmitting to avoid debouncing issues when reading toggle pin state.
      }
      break;

    case ARM:
      if (digitalRead(LAUNCH_PIN) == HIGH) {
        digitalWrite(LaunchLED,HIGH);
        Current_state = LAUNCH;    //If LAUNCH pin has been switched ON then Current_State changes to LAUNCH.
        strcpy(message, "LAUNCH");
        Serial.println("Current state = LAUNCH");
        Serial1.write(mess, sizeof(message));
      }

      if (digitalRead(ARM_PIN) == LOW) {
        digitalWrite(ArmLED,LOW);
        Current_state = KEY;       //If ARM pin has been switched OFF then Current_State changes back to KEY.
        strcpy(message, "ARMOFF");      
        Serial.println("Current state = KEY");
        Serial1.write(mess, sizeof(message));
      }
      delay(1000);                //Delays are necessary when transmitting to avoid debouncing issues when reading toggle pin state.
      break;

    case LAUNCH:   
      break;

    default:
      break;
  }
}
