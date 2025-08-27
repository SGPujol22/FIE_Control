//---------------------------------------------------------------------------------------------------
//                                      Control Avanzado I
//                                          Cursada 2025
//---------------------------------------------------------------------------------------------------
/*                         Trabajo Práctico N°1: Estudio de una planta
-----------------------------------------------------------------------------------------------------

  * Programa utilizado para evaluar la temperatura de una pava, mediante el módulos max6675, una 
  Esp8266 y una termocupla*/
//---------------------------------------------------------------------------------------------------

#include <Arduino.h>   // Librería base de Arduino (setup, loop, millis, etc.)
#include <SPI.h>       // Librería para comunicación SPI
#include <max6675.h>   // Librería del sensor MAX6675

// Definimos los pines usados en el ESP8266 (NodeMCU)
#define MAX6675_SO   D6   // SO (Serial Out / MISO) del MAX6675 → D6 en NodeMCU
#define MAX6675_CS   D8   // CS (Chip Select) del MAX6675 → D8 en NodeMCU
#define MAX6675_SCK  D5   // SCK (Serial Clock) del MAX6675 → D5 en NodeMCU

// Creamos el objeto "thermocouple" para manejar el MAX6675
MAX6675 thermocouple(MAX6675_SCK, MAX6675_CS, MAX6675_SO);

// Variables globales
volatile float temperatura = 0.0;   // Guarda la última lectura de temperatura
volatile bool nuevaLectura = false; // Bandera que indica si hay un nuevo dato

ETSTimer miTimer;  // Declaramos un timer del ESP8266

// ------------------------------------------------------
// Función que se ejecuta cada vez que se dispara el timer
// ------------------------------------------------------
void onTimer(void *pArg) {
  temperatura = thermocouple.readCelsius();  // Leer temperatura en °C

  unsigned long ms = millis();               // Tiempo desde que arrancó el ESP
  Serial.printf("%lu,%0.2f\n", ms, temperatura); // Imprime: tiempo, temperatura

  nuevaLectura = true;   // Activa la bandera para avisar al loop()
}

void setup() {
  Serial.begin(115200);   // Inicia el puerto serie a 115200 baudios
  delay(500);             // Pequeña pausa para estabilizar
  Serial.println("MAX6675 con Timer interno actualizado (ESP8266)");

  // Configuramos el timer → le decimos qué función ejecutar
  os_timer_setfn(&miTimer, onTimer, NULL);

  // Activamos el timer cada 1000 ms (1 segundo), en modo repetitivo
  os_timer_arm(&miTimer, 1000, true); // true = que se repita
}

void loop() {
  // Si hay una nueva lectura disponible…
  if (nuevaLectura) {
    Serial.print("Temperatura: ");  // Texto fijo
    Serial.print(temperatura);      // Valor de la temperatura
    Serial.println(" °C");          // Unidad
    nuevaLectura = false;           // Reseteamos la bandera
  }
}
