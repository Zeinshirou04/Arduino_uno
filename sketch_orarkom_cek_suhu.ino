// Blynk Config
#define BLYNK_TEMPLATE_ID "TMPLEefkEANU"
#define BLYNK_DEVICE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "p6by6yxE-2koM2BWN9F67gJJoU7nGO6D"

// Import Library OneWire, Chat Bot dan Blynk
#include "OneWire.h"
#include "DallasTemperature.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Define Jalur data yang dipilih
#define ONE_WIRE_BUS D4

// Komen baris dibawah ini jika tidak ingin mencetak tulisan
#define BLYNK_PRINT Serial

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Authentikasi
char auth[] = BLYNK_AUTH_TOKEN;

// Configurasi Jaringan
// Isi "" Jika tidak memiliki password
char ssid[] = "YUWONO1960D"; 
char pass[] = "2bima30#30a";

// Timer untuk Blynk
BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  // Update state
  Blynk.virtualWrite(V1, value);
}

// Fungsi dibawah akan dipanggil setiap IoT terhubung ke Blynk 
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, millis() / 1000);
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  sensors.begin();

  // Set Timer
  timer.setInterval(1000L, myTimerEvent);
}

void loop() {
  sensors.requestTemperatures();
  Blynk.run();
  timer.run();
  int suhu = sensors.getTempCByIndex(0);

  // Kondisi Membeku
  if (suhu < 10) {
    // Mengirimkan pesan ke Telegram
    Serial.println("Kondisi membeku dengan suhu " + suhu); 
  } else if ((suhu > 10) && (suhu < 30)) {
    // Mengirimkan pesan ke Telegram
    Serial.println("Kondisi normal dengan suhu " + suhu);
  } else if (suhu > 30) {
    // Mengirimkan pesan ke Telegram
    Serial.println("Kondisi mendidih dengan suhu " + suhu);
  } else {
    // Mengirimkan pesan ke Telegram
    Serial.println("SUHU DILUAR JANGKAUAN!");
  }
  delay(2000);
}
