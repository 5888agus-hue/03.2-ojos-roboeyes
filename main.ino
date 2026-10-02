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

// Estados de la maquina de arranque y marca de tiempo de su ventana
bool bootComplete = false;
unsigned long bootTime = 0;

void setup() {
  Serial.begin(115200);
  Serial.println(F("[BOOT] sistema de ojos OLED"));

  // TODO 1.5 (Reto 01)
  initI2C();
  scanI2C();
  testI2CDevice();

  // TODO 2.4: Escribe las llamadas de los pasos 5 y 6 para pintar el logo y ejecutar el POST de pantalla
  // Paso 5 - Panel inicializado
  initDisplay();

  // Paso 6 - Logo pintado y POST de pantalla
  testDisplay();
  delay(500); // Pausa breve de 500 ms para visibilidad de la autoprueba POST
  showLogo();

  // Guardar marca de tiempo del inicio del estado BOOT
  bootTime = millis();

  // TODO 3.4 (Retos posteriores)
  // Paso 7 - Ojos inicializados

  // TODO 4.3 (Retos posteriores)
  // Paso 8 - Ayuda publicada y ventana de arranque armada
}

void loop() {
  // TODO 2.4 (continuación): Mientras la ventana de arranque no expire, mantén el logo
  // en pantalla; al meceder/expirar, cambia de estado y repórtalo por el monitor.
  if (!bootComplete) {
    if (millis() - bootTime >= LOGO_TIME_MS) {
      bootComplete = true;
      Serial.println(F("[BOOT] BOOT -> RUN"));
    } else {
      showLogo();
    }
    return; // Sale del loop mientras siga en BOOT para no ejecutar lógica de RUN
  }

  // TODO 4.3 (continuación): Con el arranque terminado, atiende la consola en cada
  // vuelta y deja que la animación avance un paso sin bloquear el bucle.
}
