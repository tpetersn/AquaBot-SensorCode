// BTS7960 Motor Driver + Serial Command Control

// --- Pin Definitions ---
const int R_EN  = 4;   // Right Enable
const int RPWM  = 5;   // PWM - forward direction
const int LPWM  = 6;   // PWM - reverse direction
const int L_EN  = 7;   // Left Enable

int speedPWM = 180;  // ~70% power (0–255). Adjust as needed.

void setup() {
  Serial.begin(9600);

  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);
  pinMode(R_EN, OUTPUT);
  pinMode(L_EN, OUTPUT);

  digitalWrite(R_EN, HIGH);
  digitalWrite(L_EN, HIGH);

  stopMotor();
  Serial.println("Arduino ready");
}

void stopMotor() {
  analogWrite(RPWM, 0);
  analogWrite(LPWM, 0);
}

void forward() {
  analogWrite(RPWM, speedPWM);
  analogWrite(LPWM, 0);
}

void back() {
  analogWrite(RPWM, 0);
  analogWrite(LPWM, speedPWM);
}

void left() {
  analogWrite(RPWM, speedPWM);
  analogWrite(LPWM, speedPWM / 2);  // soft differential turn
}

void right() {
  analogWrite(RPWM, speedPWM / 2);
  analogWrite(LPWM, speedPWM);
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    if (cmd == "forward") forward();
    else if (cmd == "back") back();
    else if (cmd == "left") left();
    else if (cmd == "right") right();
    else if (cmd == "stop") stopMotor();
  }
}
