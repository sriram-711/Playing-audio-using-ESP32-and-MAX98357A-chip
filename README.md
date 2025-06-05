# Playing-audio-using-ESP32-and-MAX98357A-chip
# Connections
MAX98357A              ESP32
Vin pin    -------->  3.3v pin
GND pin    -------->  GND pin
GAIN pin   -------->  3.3v pin
Din pin    -------->  GPIO 25
LRC pin    -------->  GPIO 26
BCLK pin   -------->  GPIO 27



| MAX98357A Pin | ESP32 Pin | Description                                   |
| ------------- | --------- | --------------------------------------------- |
| **Vin**       | 3.3V      | Power supply (3.3V)                           |
| **GND**       | GND       | Ground                                        |
| **GAIN**      | 3.3V      | Sets gain (connect to 3.3V for higher volume) |
| **DIN**       | GPIO 25   | I2S data input                                |
| **LRC**       | GPIO 26   | I2S word select (LRCLK)                       |
| **BCLK**      | GPIO 27   | I2S bit clock                                 |



Note: Ensure your ESP32 is powered properly, and audio output is connected to a speaker or headphones via the MAX98357A.

Libraries Required
Install the following libraries in the Arduino IDE:

ESP8266Audio by Earle F. Philhower

WiFi (comes with ESP32 board support)



# 🎧 Playing Audio Using ESP32 and MAX98357A Chip

This project streams MP3 audio from an online radio station and plays it using the **ESP32** and the **MAX98357A I2S DAC amplifier**.

---

## 🔌 Connections

### Wiring Diagram

MAX98357A ESP32
========== =====
Vin --------> 3.3V
GND --------> GND
GAIN --------> 3.3V (or GND for lower gain)
DIN --------> GPIO 25
LRC (LRCLK) --------> GPIO 26
BCLK --------> GPIO 27



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

## 📄 Example Code Snippet

Here’s the main part of the working sketch:

```cpp
#include <WiFi.h>
#include "AudioFileSourceICYStream.h"
#include "AudioFileSourceBuffer.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"

// I2S pin definitions
#define I2S_DOUT      25
#define I2S_BCLK      27
#define I2S_LRC       26
#define MAX98357_GAIN 2

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

AudioGeneratorMP3 *mp3;
AudioFileSourceICYStream *file;
AudioFileSourceBuffer *buff;
AudioOutputI2S *out;

const char* streamURL = "https://a1.asurahosting.com:9580/radio.mp3";

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");

  pinMode(MAX98357_GAIN, OUTPUT);
  digitalWrite(MAX98357_GAIN, LOW); // Lower gain

  out = new AudioOutputI2S();
  out->SetPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  out->SetGain(0.5);

  file = new AudioFileSourceICYStream(streamURL);
  buff = new AudioFileSourceBuffer(file, 2048);
  mp3 = new AudioGeneratorMP3();
  mp3->begin(buff, out);
}

void loop() {
  if (mp3->isRunning()) {
    mp3->loop();
  }
}

