char reading = 0;
String output;
int idx = 0;

void setup() {
  Serial.begin(9600);
  Serial5.begin(9600);
  Serial.println("Serial comms. init. \n");
}

void loop() {
  if (Serial5.available()) {
    output = Serial5.readStringUntil(',');
    Serial.print("LOAD CELL READING: ");
    Serial.println(output);
  }
}
