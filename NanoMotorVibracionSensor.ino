#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>

const int ledPin = 13;  // LED para indicar mediciones
const int motorPin = 9; // Pin para el motor de vibración

Adafruit_BMP085 bmp;    // Objeto para el sensor BMP180

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(motorPin, OUTPUT);

  if (!bmp.begin()) {
    Serial.println("No se pudo encontrar el sensor BMP180. Verifique la conexión o la dirección del sensor.");
    while (1);
  }
}

void loop() {
  // Medir presión arterial con el sensor
  float presionArterial = bmp.readPressure() / 100.0F;  // Convertir a hPa

  // Generar vibraciones controladas con el motor
  activarVibracion();

  // Registrar datos
  registrarDatos(presionArterial);

  // Desactivar vibración y esperar antes de la próxima medición
  desactivarVibracion();
  delay(5000);  // Intervalo de 5 segundos entre mediciones
}

void activarVibracion() {
  digitalWrite(motorPin, HIGH);
}

void desactivarVibracion() {
  digitalWrite(motorPin, LOW);
}

void registrarDatos(float presion) {
  // Puedes enviar datos a través de I2C, almacenarlos en una tarjeta SD, etc.
  // En este ejemplo, simplemente se imprimen en el monitor serial.
  Serial.print("Presión arterial: ");
  Serial.print(presion);
  Serial.println(" hPa");
}
