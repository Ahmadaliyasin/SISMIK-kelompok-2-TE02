#include <DHT.h>
#include <ESP32Servo.h>
#include <analogWrite.h>




// Inisialisasi DHT
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Inisialisasi servo
Servo servo1;

// Inisialisasi pin sensor
const int pinHujan = 26;
const int pinLdr = 27;

// Inisialisasi pembacaan sensor
int hujan, cahaya;

// Inisialisasi derajat buka-tutup servo
int tutup = 250;
int buka = 10;

void setup() {
  // Setting baud rate serial monitor
  Serial.begin(9600);

  // Inisialisasi DHT
  Serial.println("Menginisialisasi sensor DHT11...");
  dht.begin();

  // Inisialisasi pin servo
  servo1.attach(25);

  // Inisialisasi status input/output pin
  pinMode(pinHujan, INPUT);
  pinMode(pinLdr, INPUT);
}

void loop() {
  // Pembacaan sensor
  hujan = digitalRead(pinHujan);
  cahaya = digitalRead(pinLdr);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Gagal membaca sensor DHT11!");
   
  }

  // Menulis pada serial monitor pembacaan sensor hujan dan cahaya
  Serial.print(hujan);
  Serial.print(" ");
  Serial.println(cahaya);
  Serial.println(" ");
  Serial.print("Kelembapan: ");
  Serial.print(humidity);
  Serial.println("%");
  Serial.print("Suhu: ");
  Serial.print(temperature);
  Serial.println("°C");

  // Sensor hujan akan bernilai 0 saat ada air
  // Sensor cahaya akan bernilai 1 saat gelap
  // dan berlaku sebaliknya

  // Jika kondisi hujan dan mendung
  if (hujan == 0 && cahaya == 1) {
    // Servo menutup
    servo1.write(tutup);
  }

  // Jika kondisi hujan
  else if (hujan == 0 && cahaya == 0) {
    // Servo menutup
    servo1.write(tutup);
  }

  // Jika kondisi mendung
  else if (hujan == 1 && cahaya == 1) {
    // Servo menutup
    servo1.write(tutup);
  }

  // Jika kondisi tidak hujan dan tidak mendung
  else if (hujan == 1 && cahaya == 0) {
    // Servo membuka jika suhu di atas 25 derajat, jika tidak servo menutup
    if (temperature > 25) {
      servo1.write(buka);
    } else {
      servo1.write(tutup);
    }

    // Jika kelembapan di atas 80%, servo menutup; jika di bawah 50%, servo membuka
    if (humidity > 80) {
      servo1.write(tutup);
    } else if (humidity < 50) {
      servo1.write(buka);
    }
  }

  // Delay jalannya program
  delay(300);
}
