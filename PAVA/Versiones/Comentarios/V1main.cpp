#include "MAX6675.h"        
                         

int thermoDO  = 4;       
int thermoCS  = 5;       

int thermoCLK = 6;       

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
                         // Crea el objeto 'thermocouple' usando la librería.
                         // El orden de parámetros suele ser: (SCLK, CS, MISO/DO).
                         // Este objeto encapsula la lectura y conversiones necesarias.

void setup() {
  Serial.begin(9600);            // Inicia la comunicación serie a 9600 baudios para ver datos por el Monitor Serie.
                                 // Puedes usar 115200 si querés mayor velocidad; ambas deben coincidir con el Monitor.
  Serial.println("MAX6675 test"); // Imprime una línea inicial en el Monitor Serie (con salto de línea).
                                 // Útil para saber que el programa arrancó correctamente.
}

void loop() {
  Serial.print("Temperatura = ");      // Escribe texto sin salto de línea (nos preparamos para poner el valor).
  
  float temp = thermocouple.readCelsius();
                                     // Llama a la función de la librería que devuelve la temperatura en °C.
                                     // Tipo de retorno típico: float (puede variar según la librería).
                                     // Atención: si el termopar está desconectado o hay error, algunas librerías
                                     // devuelven NAN o un valor específico — conviene verificarlo antes de usarlo.
  
  Serial.print(temp);                 // Imprime el valor numérico de la temperatura (ej: 23.25).
  Serial.println(" °C");              // Imprime la unidad y agrega salto de línea para finalizar la línea.
  
  delay(1000);                        // Espera 1000 ms (1 s) antes de la siguiente lectura.
                                     // Nota: el MAX6675 necesita ~220 ms para la conversión interna,
                                     // así que no conviene leer mucho más seguido que eso.
}
