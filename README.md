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
