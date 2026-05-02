// ================= PIN DEFINITIONS =================
#define TEMP_PIN 34
#define CURRENT_PIN 35
#define VIBRATION_PIN 32

#define RELAY_PIN 26
#define BUZZER_PIN 25

#define LED_GREEN 21
#define LED_YELLOW 22
#define LED_RED 23

#define MOTOR_ENA 5
#define MOTOR_IN1 18
#define MOTOR_IN2 19

#define SWITCH_PIN 14

// ================= TEMPERATURE FUNCTION =================
float readTemperature() {
  int samples = 10;
  float sum = 0;

  for (int i = 0; i < samples; i++) {
    int raw = analogRead(TEMP_PIN);
    float voltage = (raw / 4095.0) * 3.3;
    float temp = voltage * 100.0;
    sum += temp;
    delay(10);
  }

  return (sum / samples);
}

// ================= SETUP =================
void setup() {
  Serial.begin(115200);

  analogSetAttenuation(ADC_11db);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  pinMode(MOTOR_ENA, OUTPUT);
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);

  pinMode(SWITCH_PIN, INPUT_PULLUP);

  digitalWrite(RELAY_PIN, HIGH); // OFF
}

// ================= LOOP =================
void loop() {

  // ----------- TEMPERATURE -----------
  float temperature = readTemperature();

  // Calibration (adjust if needed)
  temperature = temperature + 2.5;

  if (temperature < 0 || temperature > 100) {
    temperature = 25;
  }

  // ----------- CURRENT -----------
  int currentRaw = analogRead(CURRENT_PIN);
  float currentVoltage = (currentRaw / 4095.0) * 3.3;
  float current = abs((currentVoltage - 2.5) / 0.185);

  if (current < 0.05) current = 0;

  // ----------- VIBRATION -----------
  int vibRaw = analogRead(VIBRATION_PIN);
  float vibration = map(vibRaw, 0, 4095, 0, 100);

  float vibOffset = 18;
  vibration = vibration - vibOffset;
  if (vibration < 0) vibration = 0;

  // ----------- SWITCH -----------
  bool motorON = (digitalRead(SWITCH_PIN) == LOW);

  // ================= TEMPERATURE CONTROL LOGIC =================

  bool warning = false;
  bool fault = false;

  if (temperature > 36) {
    fault = true;
  } 
  else if (temperature > 27) {
    warning = true;
  }

  // ----------- MOTOR CONTROL -----------

  if (motorON && !fault) {
    digitalWrite(MOTOR_IN1, HIGH);
    digitalWrite(MOTOR_IN2, LOW);
    analogWrite(MOTOR_ENA, 200);

    digitalWrite(RELAY_PIN, LOW);  // ON
  } 
  else {
    digitalWrite(MOTOR_IN1, LOW);
    digitalWrite(MOTOR_IN2, LOW);
    analogWrite(MOTOR_ENA, 0);

    digitalWrite(RELAY_PIN, HIGH); // OFF
  }

  // ----------- LED STATUS -----------

  if (fault) {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, HIGH);
  } 
  else if (warning) {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_RED, LOW);
  } 
  else {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, LOW);
  }

  // ----------- BUZZER -----------

  if (fault) {
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  // ----------- SERIAL OUTPUT -----------

  Serial.print("Temp: ");
  Serial.print(temperature);

  Serial.print(" | Current: ");
  Serial.print(current);

  Serial.print(" | Vib: ");
  Serial.print(vibration);

  Serial.print(" | Health: ");
  Serial.print(fault ? 20 : (warning ? 60 : 100)); // simple mapping

  Serial.print(" | Fault: ");
  Serial.print(fault);

  Serial.print(" | Switch: ");
  Serial.println(motorON);

  delay(1000);
}