// i2c_manager.h
// ============================================
// RESPONSABILIDAD: Hablar con el bus I2C (pines, velocidad, escaneo y verificacion).
// No sabe nada de: OLED, logos, ojos ni comandos del Monitor Serie.
// ============================================

#ifndef I2C_MANAGER_H
#define I2C_MANAGER_H

#include <Arduino.h>
#include <Wire.h>
#include "config.h"

// TODO 1.1: Inicializar bus I2C y configurar frecuencia
inline void initI2C() {
  Wire.begin();
  Wire.setClock(400000);
  Serial.println(F("[I2C] Bus I2C inicializado a 400 kHz"));
}

// TODO 1.2: Escaneo del bus I2C
inline void scanI2C() {
  Serial.println(F("[I2C] Escaneando bus..."));
  byte count = 0;
  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.print(F("[I2C] Dispositivo encontrado en 0x"));
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
      count++;
    }
  }
  if (count == 0) {
    Serial.println(F("[I2C] No se encontraron dispositivos"));
  }
}

// TODO 1.3: Prueba de comunicación con la pantalla en OLED_I2C_ADDRESS
inline void testI2CDevice() {
  Wire.beginTransmission(OLED_I2C_ADDRESS);
  byte error = Wire.endTransmission();
  if (error == 0) {
    Serial.print(F("[I2C] OLED respondiendo en 0x"));
    Serial.println(OLED_I2C_ADDRESS, HEX);
  } else {
    Serial.print(F("[I2C] ERROR: OLED no responde en 0x"));
    Serial.println(OLED_I2C_ADDRESS, HEX);
  }
}

#endif
