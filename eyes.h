// eyes.h
// ============================================
// RESPONSABILIDAD: Animar los ojos del OLED y aplicar la expresion elegida.
// No sabe nada de: bus I2C, logos de arranque, POST ni Monitor Serie.
// ============================================

#ifndef EYES_H
#define EYES_H

#include <Arduino.h>
#include "display.h"
#include "config.h"

// Arduino.h del ESP32 define DEFAULT como 1 y RoboEyes lo define como 0. Se
// limpia esa macro (sin uso en el core) para evitar el aviso de redefinicion.
#undef DEFAULT

#include <FluxGarage_RoboEyes.h>

// Instancia global: el sistema tiene un solo par de ojos
RoboEyes<Adafruit_SSD1306> roboEyes(display);

// TODO 3.1: Inicializa los ojos con las dimensiones del panel y el objetivo de cuadros por segundo
inline void initEyes() {
  // Tres parámetros: Ancho del panel, Alto del panel y FPS objetivo (60)
  roboEyes.begin(OLED_WIDTH, OLED_HEIGHT, 60);
  Serial.println(F("[EYES] RoboEyes listo a 60 fps"));
}

// TODO 3.2: Avanza la animación un paso sin bloquear
inline void updateEyes() {
  // La librería es dueña del borrado y la presentación del cuadro
  roboEyes.update();
}

// TODO 3.3: Aplica la expresión pedida por tecla (1 a 7) y restablece la base limpia
inline void setEyesMood(char key) {
  // Validación de rango
  if (key < '1' || key > '7') {
    return;
  }

  // --- RESTABLECER BASE LIMPIA ---
  roboEyes.setCuriosity(OFF);
  roboEyes.setHFlicker(OFF, 0);
  roboEyes.setVFlicker(OFF, 0);
  roboEyes.setAutoblinker(ON, 4, 2);
  roboEyes.setIdleMode(OFF);

  // --- MAPA DE EXPRESIONES (1 A 7) ---
  switch (key) {
    case '1': // Neutra
      roboEyes.setMood(DEFAULT);
      roboEyes.setIdleMode(ON);
      break;

    case '2': // Feliz
      roboEyes.setMood(HAPPY);
      roboEyes.setIdleMode(ON);
      break;

    case '3': // Enojada
      roboEyes.setMood(ANGRY);
      roboEyes.setIdleMode(OFF);
      break;

    case '4': // Cansada
      roboEyes.setMood(TIRED);
      roboEyes.setIdleMode(OFF);
      break;

    case '5': // Soñolienta
      roboEyes.setMood(TIRED);
      roboEyes.setAutoblinker(ON, 1, 1);
      roboEyes.setIdleMode(OFF);
      break;

    case '6': // Temible
      roboEyes.setMood(ANGRY);
      roboEyes.setAutoblinker(OFF, 0, 0);
      roboEyes.setVFlicker(ON, 2);
      roboEyes.setIdleMode(OFF);
      break;

    case '7': // Curiosa
      roboEyes.setMood(DEFAULT);
      roboEyes.setCuriosity(ON);
      roboEyes.setIdleMode(ON, 2, 2);
      break;
  }

  Serial.print(F("[EYES] expresion aplicada: "));
  Serial.println(key);
}

#endif
