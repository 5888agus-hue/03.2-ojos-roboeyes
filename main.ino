// main.ino
// ============================================================================
// RESPONSABILIDAD: Orquestar arranque y bucle principal del sistema.
// No sabe como hacer nada: solo llama a cada modulo en el orden correcto.
// ============================================================================

#include "config.h"
#include "i2c_manager.h"
#include "display.h"
#include "logo.h"
#include "logboot.h"
#include "eyes.h"
#include "debug_serial.h"

bool bootComplete = false;
unsigned long bootTime = 0;

void setup() {
  Serial.begin(115200);
  Serial.println(F("[BOOT] sistema de ojos OLED"));

  // Reto 01: Inicialización de bus I2C
  initI2C();
  scanI2C();
  testI2CDevice();

  // Reto 02: Inicialización de pantalla, POST y Logo
  initDisplay();
  testDisplay();
  delay(500);
  showLogo();

  // Reto 03: Inicialización de los ojos
  initEyes();

  bootTime = millis();

  // TODO 4.3: Paso 8 - Ayuda publicada al finalizar el arranque
  printHelp();
}

void loop() {
  // Ventana de arranque (FSM: Estado BOOT)
  if (!bootComplete) {
    if (millis() - bootTime >= LOGO_TIME_MS) {
      bootComplete = true;
      Serial.println(F("[BOOT] BOOT -> RUN"));
    } else {
      showLogo();
    }
    return;
  }

  // Estado RUN: Atención continua a la consola y animación de los ojos sin bloqueo
  debugSerialTick();
  updateEyes();
}