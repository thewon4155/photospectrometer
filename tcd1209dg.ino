// TCD1209DG Arduino Interface
const int SH = 5;     // Shift Pulse
const int CP = 6;     // Clamp Pulse
const int RS = 7;     // Reset Pulse
const int PHI2 = 8;   // Clock 2
const int PHI1 = 9;   // Clock 1
const int AOUT = A0;  // Analog output (OS)

const int PIXELS = 2048;

void setup() {
  pinMode(SH, OUTPUT);
  pinMode(CP, OUTPUT);
  pinMode(RS, OUTPUT);
  pinMode(PHI1, OUTPUT);
  pinMode(PHI2, OUTPUT);

  digitalWrite(SH, LOW);
  digitalWrite(CP, LOW);
  digitalWrite(RS, LOW);
  digitalWrite(PHI1, LOW);
  digitalWrite(PHI2, HIGH); // 초기 상태: PHI2 HIGH

  Serial.begin(115200);
  delay(500); // 센서 안정화 대기
}

void loop() {
  // 리셋 시퀀스
  digitalWrite(RS, HIGH);
  delayMicroseconds(1);
  digitalWrite(RS, LOW);

  // 클램프
  digitalWrite(CP, HIGH);
  delayMicroseconds(1);
  digitalWrite(CP, LOW);

  // 데이터 수집 루프
  for (int i = 0; i < PIXELS; i++) {
    // Clock φ1 HIGH, φ2 LOW
    digitalWrite(PHI1, HIGH);
    digitalWrite(PHI2, LOW);
    
    // Shift Pulse
    digitalWrite(SH, HIGH);
    delayMicroseconds(4);
    digitalWrite(SH, LOW);
    
    // Clock φ1 LOW, φ2 HIGH
    digitalWrite(PHI1, LOW);
    digitalWrite(PHI2, HIGH);

    // Read pixel value
    int val = analogRead(AOUT);
    int invertedVal = 1023 - val;
    Serial.println(invertedVal);
  }

  delay(100); // 한 프레임 간격
}
