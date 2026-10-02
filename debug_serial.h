// debug_serial.h
// ===================================================================
// RESPONSABILIDAD: Leer comandos del Monitor Serie y mostrar la ayuda.
// No sabe nada de: bus I2C, OLED, logos ni animacion interna de los ojos.
// ===================================================================

#ifndef DEBUG_SERIAL_H
#define DEBUG_SERIAL_H

#include <Arduino.h>
#include "config.h"
#include "eyes.h"

// TODO 4.1: Publica el bloque de ayuda con las 7 expresiones y la tecla de ayuda.
inline void printHelp() {
  Serial.println(F("[DEBUG] 1=DEFAULT 2=HAPPY 3=ANGRY 4=TIRED"));
  Serial.println(F("[DEBUG] 5=SLEEPY 6=SCARY 7=CURIOUS h=ayuda"));
}

// TODO 4.2: Atiende el puerto sin bloquear: una tecla, respuesta inmediata.
inline void debugSerialTick() {
  while (Serial.available() > 0) {
    char c = Serial.read();

    // Ignorar caracteres de control ASCII (saltos de línea '\n', '\r', espacios en blanco, etc.)
    if (c <= 32) {
      continue;
    }

    // Tecla de ayuda
    if (c == 'h' || c == 'H') {
      printHelp();
    } 
    // Selección de expresión ('1' a '7')
    else if (c >= '1' && c <= '7') {
      setEyesMood(c);
    } 
    // Carácter desconocido
    else {
      Serial.print(F("[DEBUG] comando desconocido: "));
      Serial.println(c);
    }
  }
}

#endif
