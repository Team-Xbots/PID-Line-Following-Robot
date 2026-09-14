// ================= MOTOR PINS =================
#define AIN1 0
#define AIN2 2
#define PWMA 15

#define BIN1 16
#define BIN2 17
#define PWMB 5

#define STBY 4

// ================= BUTTON =================
#define BUTTON 13

// ================= SENSOR PINS =================
int sensorPins[8] = {12, 14, 27, 26, 25, 33, 32, 35};

// ================= PID VALUES =================
float Kp = 24.0;  //22 set 22.0
float Ki = 0.7;   //1 set 0.6
float Kd = 44.0;  //32 set 40.0

float error = 0;
float lastError = 0;
float integral = 0;

int maxSpeed  = 255;

bool robotRunning = false;
bool lastButtonState = HIGH;

// ================= SETUP =================
void setup() {

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(STBY, OUTPUT);

  pinMode(BUTTON, INPUT_PULLUP);

  for (int i = 0; i < 8; i++)
    pinMode(sensorPins[i], INPUT);

  digitalWrite(STBY, HIGH);

  ledcAttach(PWMA, 20000, 8);
  ledcAttach(PWMB, 20000, 8);
}

// ================= MOTOR FUNCTION =================
void setMotor(int leftSpeed, int rightSpeed)
{
  if (leftSpeed >= 0) {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  } else {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    leftSpeed = -leftSpeed;
  }

  if (rightSpeed >= 0) {
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  } else {
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    rightSpeed = -rightSpeed;
  }

  leftSpeed  = constrain(leftSpeed, 0, maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, maxSpeed);

  ledcWrite(PWMA, leftSpeed);
  ledcWrite(PWMB, rightSpeed);
}

// ================= SENSOR READ =================
float readSensors(int &activeSensors)
{
  int weights[8] = {4, 3, 2, 1, -1, -2, -3, -4};

  int sum = 0;
  activeSensors = 0;

  for (int i = 0; i < 8; i++) {
    if (digitalRead(sensorPins[i]) == HIGH) {   // BLACK = HIGH
      sum += weights[i];
      activeSensors++;
    }
  }

  if (activeSensors == 0)
    return lastError;

  return (float)sum / activeSensors;
}

// ================= LOOP =================
void loop() {

  // -------- BUTTON --------
  bool currentButtonState = digitalRead(BUTTON);

  if (lastButtonState == HIGH && currentButtonState == LOW) {
    delay(150);
    robotRunning = !robotRunning;
  }

  lastButtonState = currentButtonState;

  if (!robotRunning) {
    setMotor(0, 0);
    return;
  }

  int activeSensors = 0;
  error = readSensors(activeSensors);

  // ================= LINE LOST =================
  if (activeSensors == 0) {
    integral = 0;  // reset integral

    if (lastError > 0)
      setMotor(-80, 150);
    else
      setMotor(150, -80);

    return;
  }

  // ================= SMART SPEED CONTROL =================
  int dynamicBase;

  if (abs(error) < 0.3)
    dynamicBase = 210;     // straight fast 185 set(210)
  else if (abs(error) < 1.5)
    dynamicBase = 160;     // curve medium 145 set(160)
  else
    dynamicBase = 120;     // sharp turn slow 110 set(120)

  // ================= FULL PID =================
  integral += error;
  integral = constrain(integral, -40, 40);

  float derivative = error - lastError;

  float correction = (error * Kp) +
                     (integral * Ki) +
                     (derivative * Kd);

  // Extra correction boost for sharp turn
  if (abs(error) > 2)
    correction *= 1.5; //set 1.5

  int leftSpeed  = dynamicBase - correction;
  int rightSpeed = dynamicBase + correction;

  setMotor(leftSpeed, rightSpeed);

  lastError = error;

  delay(2);
}