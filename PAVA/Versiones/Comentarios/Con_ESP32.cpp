//Código para ESP32
//-------------------------------------------------------------------------------------------------

/* Poner en el platformio.ino lo siguiente

[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino

lib_deps =
   adafruit/MAX6675 library

----------------------------------------------------------------------------------------------------   
*/

// en el archivo.cpp poner lo siguiente

#include <Arduino.h>   // Librería base de Arduino
#include <SPI.h>       // Librería SPI
#include <max6675.h>   // Librería MAX6675

// Definimos los pines del ESP32
#define MAX6675_SO   19   // MISO (Serial Out del MAX6675)
#define MAX6675_CS   5    // CS (Chip Select)
#define MAX6675_SCK  18   // CLK (Serial Clock)

// Creamos el objeto "thermocouple"
MAX6675 thermocouple(MAX6675_SCK, MAX6675_CS, MAX6675_SO);

// Variables para manejar la lectura periódica
float temperatura = 0.0;
unsigned long lastRead = 0; // almacena el último tiempo de lectura

void setup() {
  Serial.begin(115200);   // Abrimos el puerto serie a 115200 baudios
  delay(500);             // Pequeña pausa
  Serial.println("MAX6675 en ESP32 con millis()");
}

void loop() {
  unsigned long now = millis();           // Tiempo actual en ms
  if (now - lastRead >= 1000) {           // Si pasó 1 segundo...
    lastRead = now;                       // Guardamos el tiempo actual

    temperatura = thermocouple.readCelsius();  // Leemos el sensor

    // Imprimimos por Serial
    Serial.printf("%lu ms -> %.2f °C\n", now, temperatura);
  }
}
