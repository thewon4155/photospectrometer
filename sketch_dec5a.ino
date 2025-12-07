// --------------------------------------------------------------
// Final tuned code for TCD1209DG CCD sensor (2048 pixels)
// --------------------------------------------------------------

const int SHpin  = 2;     // SH (Shift Gate)
const int ICGpin = 3;     // ICG (Integration Clear Gate)
const int CLKpin = 4;     // CLK (CCD Clock)
const int AOpin  = A0;    // Analog output of TCD1209DG

const int pixelCount = 2048;
int pixelData[pixelCount];

void setup()
{
    pinMode(SHpin, OUTPUT);
    pinMode(ICGpin, OUTPUT);
    pinMode(CLKpin, OUTPUT);

    digitalWrite(SHpin, LOW);
    digitalWrite(ICGpin, HIGH);
    digitalWrite(CLKpin, LOW);

    Serial.begin(115200);
}

// --------------------------------------------------------------
// Generate a clock pulse (approx 1 us high pulse)
// --------------------------------------------------------------
inline void CLK()
{
    digitalWrite(CLKpin, HIGH);
    delayMicroseconds(1);
    digitalWrite(CLKpin, LOW);
}

// --------------------------------------------------------------
// Read one pixel with double sampling to reduce noise
// --------------------------------------------------------------
int readPixel()
{
    int v1 = analogRead(AOpin);
    int v2 = analogRead(AOpin);
    return (v1 + v2) >> 1;   // 평균값
}

void loop()
{
    // 1) End previous integration
    digitalWrite(ICGpin, LOW);
    CLK();
    digitalWrite(ICGpin, HIGH);

    // 2) Start shifting pixel data (SH pulse)
    digitalWrite(SHpin, HIGH);
    CLK();
    digitalWrite(SHpin, LOW);

    // 3) Read 2048 pixels
    for (int i = 0; i < pixelCount; i++)
    {
        CLK();
        delayMicroseconds(8);   // 안정화 시간 (튜닝됨)
        pixelData[i] = readPixel();
    }

    // 4) Send data to PC as one line of 2048 values
    for (int i = 0; i < pixelCount; i++)
    {
        Serial.print(pixelData[i]);
        Serial.print(" ");
    }
    Serial.println();

    // Integration time control (튜닝 가능)
    delayMicroseconds(3000);   // 약 3ms
}
