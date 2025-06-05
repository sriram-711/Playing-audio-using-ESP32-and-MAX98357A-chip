#include <WiFi.h>
#include "AudioFileSourceICYStream.h"
#include "AudioFileSourceBuffer.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"

#define I2S_DOUT      25
#define I2S_BCLK      27
#define I2S_LRC       26
#define MAX98357_GAIN 2

const char* ssid = "CACTUS--AP";
const char* password = "Admin$cactus$23";
const int ledPin = 13;
const int switchPin = 12;

AudioGeneratorMP3 *mp3;
AudioFileSourceICYStream *file;
AudioFileSourceBuffer *buff;
AudioOutputI2S *out;

bool switchPressed = false;
int hostIndex = 0;

const char* hosts[] = {
  "https://a1.asurahosting.com:9580/radio.mp3",
  "https://boxstream.danceradiouk.com/stream",
};

void setup() {
  Serial.begin(115200);

  // WiFi Connect
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  pinMode(ledPin, OUTPUT);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }
  digitalWrite(ledPin, HIGH);
  Serial.println("WiFi connected");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  pinMode(MAX98357_GAIN, OUTPUT);
  digitalWrite(MAX98357_GAIN, LOW);  // low gain

  pinMode(switchPin, INPUT_PULLUP);

  // Setup audio output
  out = new AudioOutputI2S();
  out->SetPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  out->SetGain(0.5); // volume control 0.0 - 1.0

  // Setup streaming source
  file = new AudioFileSourceICYStream(hosts[hostIndex]);
  buff = new AudioFileSourceBuffer(file, 2048);
  mp3 = new AudioGeneratorMP3();

  mp3->begin(buff, out);
}

void loop() {
  if (digitalRead(switchPin) == LOW) {
    if (!switchPressed) {
      switchPressed = true;
      changeHost();
    }
  } else {
    switchPressed = false;
  }

  if (mp3->isRunning()) {
    if (!mp3->loop()) {
      Serial.printf("MP3 done\n");
      mp3->stop();
    }
  } else {
    // restart if stopped
    Serial.printf("MP3 restarting\n");
    file->open(hosts[hostIndex]);
    mp3->begin(buff, out);
  }
}

void changeHost() {
  hostIndex = (hostIndex + 1) % (sizeof(hosts) / sizeof(hosts[0]));
  Serial.printf("Switching to: %s\n", hosts[hostIndex]);

  if (mp3->isRunning()) {
    mp3->stop();
  }

  file->close();
  file->open(hosts[hostIndex]);
  mp3->begin(buff, out);
}
