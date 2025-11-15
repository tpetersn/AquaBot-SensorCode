int sensorValue;
float voltage;
const float VREF = 5.00;   // or 4.90 if you measured it

void setup() {
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(A0);
  voltage = sensorValue * (VREF / 1023.0);
  Serial.println(voltage);
  delay(500);
}
