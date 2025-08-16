#include "gpio.h"

// Inicializa los pines según su modo
void gpio_init() {
    pinMode(gpios.led.pin, gpios.led.mode);
    pinMode(gpios.button.pin, gpios.button.mode);
    pinMode(gpios.servo.pin, gpios.servo.mode);
    // Agrega más inicializaciones aquí si agregas más pines
}

// Ejemplo de inicialización de los pines (modifica según tu hardware)
GPIOs gpios = {
    .led = { .pin = 2, .mode = OUTPUT },
    .button = { .pin = 13, .mode = INPUT_PULLUP },
    .servo = { .pin = 21, .mode = OUTPUT },
    .hall_sensor = { .pin = 34, .mode = INPUT },
    .hot_wire_anemometer = { .pin = 35, .mode = INPUT },
    .I2C_SDA = { .pin = 16, .mode = OUTPUT },
    .I2C_SCL = { .pin = 2, .mode = OUTPUT }
    // Agrega más pines aquí
};
