# photospectrometer
Arudino Photospectrometer using TCD1109DG Sensor

# Arudino - TCD1109DG Sensor Pin

| TCD1209DG Pin | 기능             | Arduino 연결 핀 |
| ------------- | -------------- | ------------ |
| 1 (OS)        | Analog Out     | A0           |
| 2 (SS)        | Ground         | GND          |
| 3 (OD)        | VOD (+5V)      | 5V           |
| 4 (NC)        | No Connect     | -            |
| 5 (φ1)        | Clock 1 (phi1) | D9           |
| 6 (φ2)        | Clock 2 (phi2) | D8           |
| 7\~11         | NC             | -            |
| 12\~16        | NC             | -            |
| 17 (φ2B)      | φ2 mirror      | GND          | <- essential GND. Otherwise, Clock won't work properly.
| 18 (RS)       | Reset Pulse    | D7           |
| 19\~20 (NC)   | -              | -            |
| 21 (CP)       | Clamp Pulse    | D6           |
| 22 (SH)       | Shift Pulse    | D5           |
