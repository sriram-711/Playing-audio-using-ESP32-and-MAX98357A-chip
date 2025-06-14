# 🎧 Playing Audio Using ESP32 and MAX98357A Chip

This project streams MP3 audio from an online radio station and plays it using the **ESP32** and the **MAX98357A I2S DAC amplifier**.

---
### Connection Table

| MAX98357A Pin | ESP32 Pin | Description                                   |
|---------------|-----------|-----------------------------------------------|
| **Vin**       | 3.3V      | Power supply (3.3V)                           |
| **GND**       | GND       | Ground                                        |
| **GAIN**      | 3.3V      | Sets gain (connect to 3.3V for higher volume) |
| **DIN**       | GPIO 25   | I2S data input                                |
| **LRC**       | GPIO 26   | I2S word select (LRCLK)                       |
| **BCLK**      | GPIO 27   | I2S bit clock                                 |

📌 **Note:** Ensure your ESP32 is powered properly, and connect a speaker to the MAX98357A output.

---

## 📦 Libraries Required

Install the following libraries in the **Arduino IDE**:

1. **ESP8266Audio** by *Earle F. Philhower*
   - Provides: `AudioGeneratorMP3`, `AudioOutputI2S`, `AudioFileSourceICYStream`, etc.
   - Install via: **Library Manager** → Search for `ESP8266Audio`

2. **WiFi**
   - Included with the **ESP32 board package**
   - Used for Wi-Fi connectivity

---

