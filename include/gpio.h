
#ifndef GPIO_H
#define GPIO_H

#include <Arduino.h>

#define GPIO_INPUT INPUT
#define GPIO_OUTPUT OUTPUT

// Estructura para un pin con su modo
typedef struct {
  int pin;
  int mode;
} GPIO_Pin;

// Estructura para todos los pines
typedef struct {
  GPIO_Pin led;
  GPIO_Pin button;
  GPIO_Pin servo;
  GPIO_Pin hall_sensor;
  GPIO_Pin hot_wire_anemometer;
  GPIO_Pin I2C_SDA;
  GPIO_Pin I2C_SCL;

  // Agrega más pines aquí según tu proyecto
} GPIOs;

extern GPIOs gpios;

void gpio_init();

#endif // GPIO_H

