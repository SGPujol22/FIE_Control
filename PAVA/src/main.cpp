#include <Arduino.h>
#include <SPI.h>
#include <max6675.h>

#define MAX6675_SO   D6
#define MAX6675_CS   D8
#define MAX6675_SCK  D5

MAX6675 thermocouple(MAX6675_SCK, MAX6675_CS, MAX6675_SO);

// Variable global para guardar la temperatura
volatile float temperatura = 0.0;
volatile bool nuevaLectura = false;

ETSTimer miTimer;

// Función que actúa como ISR (disparo interno)
void onTimer(void *pArg) {
  temperatura = thermocouple.readCelsius();

//Grupo hora
  unsigned long ms = millis();
  Serial.printf("%lu,%0.2f\n", ms, temperatura);

  nuevaLectura = true;
}

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("MAX6675 con Timer interno actualizado (ESP8266)");

  // Configurar timer: apuntamos a la función de callback
  os_timer_setfn(&miTimer, onTimer, NULL);

  // Disparo cada 1000 ms, repetitivo
  os_timer_arm(&miTimer, 1000, true); // true → repetitivo
}

void loop() {
  if (nuevaLectura) {
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" °C");
    nuevaLectura = false;
  }
}
