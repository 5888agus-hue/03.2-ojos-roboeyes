// logboot.h
// ============================================================================
// RESPONSABILIDAD: Dibujar el logo de arranque y hacer el POST de pantalla.
// No sabe nada de: ojos, bus I2C ni comandos del Monitor Serie.
// ============================================================================

#ifndef LOGBOOT_H
#define LOGBOOT_H

#include <Arduino.h>
#include "display.h"
#include "logo.h"

// TODO 2.2: Pinta el marco del logo desde logo_bitmap y preséntalo en el panel.
// Pregunta Guía: ¿Qué debe verse en el panel durante la ventana de arranque?
inline void showLogo() {
  display.clearDisplay();
  // drawBitmap(x, y, bitmap, ancho, alto, color)
  display.drawBitmap(0, 0, logo_bitmap, LOGO_WIDTH, LOGO_HEIGHT, SSD1306_WHITE);
  display.display();
}

// TODO 2.3: Dibuja el cuadrado de autoprueba centrado e informa sus coordenadas.
// Pregunta Guía: ¿Cómo compruebas que el cuadrado quedó centrado sin medir a ojo?
inline void testDisplay() {
  uint8_t size = 8; // Cuadrado de 8x8 píxeles
  
  // Cálculo matemático para centrado en pantalla de 128x64:
  // x = (128 - 8) / 2 = 60
  // y = (64 - 8) / 2 = 28
  uint8_t x = (LOGO_WIDTH - size) / 2;
  uint8_t y = (LOGO_HEIGHT - size) / 2;

  display.clearDisplay();
  display.fillRect(x, y, size, size, SSD1306_WHITE);
  display.display();

  // Impresión por monitor serie requerida por las pruebas automatizadas
  Serial.print(F("[POST] cuadrado de pantalla en x="));
  Serial.print(x);
  Serial.print(F(" y="));
  Serial.println(y);
}

#endif
