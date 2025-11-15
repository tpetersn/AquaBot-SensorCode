const float VREF = 4.90;      // adjust if your 5V rail is different

// Calibration from your measurements:
const float PH_SLOPE     = -4.4615;   // m
const float PH_INTERCEPT = 13.2077;   // b

// Quick fix offset so baking soda reads closer to 8.3
const float PH_OFFSET    = -0.7;      // was reading ~9.0, want ~8.3

int raw;
float voltage;
float pH;

void setup() {
  Serial.begin(9600);
}

void loop() {
  long sum = 0;
  const int N = 10;
  for (int i = 0; i < N; i++) {
    sum += analogRead(A0);
    delay(20);
  }

  raw = sum / N;
  voltage = raw * (VREF / 1023.0);

  float pH_raw = PH_SLOPE * voltage + PH_INTERCEPT;
  pH = pH_raw + PH_OFFSET;

  Serial.print("Raw: ");
  Serial.print(raw);
  Serial.print("  Voltage: ");
  Serial.print(voltage, 3);
  Serial.print(" V  pH: ");
  Serial.println(pH, 2);

  delay(500);
}
