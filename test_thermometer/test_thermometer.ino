const int tempSensorPin = 6;  
int sensorValue = 0;       
float degreesC = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(tempSensorPin);
  degreesC = sensorValue/2.046 - 50.0;

  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t degrees C = ");
  Serial.println(degreesC);

  delay(1000);
}
