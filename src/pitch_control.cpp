

#include "../include/pitch_control.h"

#include "../include/common.h"
using namespace std;

PitchController::PitchController() { pitchInit(); }

void pitchInit() {
  blades.attach(gpios.servo.pin, 500, 2500);

  // Set initial servo position

  pinMode(gpios.button.pin, gpios.button.mode);
  attachInterrupt(digitalPinToInterrupt(gpios.button.pin), countPulse, FALLING);

  rpmQueue = xQueueCreate(1, sizeof(double));
  if (rpmQueue == NULL) {
    Serial.println("Queue creation failed!");
    while (1);  // Stop execution if queue creation fails
  }
  /*
  // Set timer frequency to 1Mhz
  timer = timerBegin(1000000);
  if (timer) {
    // Attach onTimer function to our timer.
    timerAttachInterrupt(timer, &onTimer);

    // Set alarm to call onTimer function every second (value in microseconds).
    // Repeat the alarm (third parameter) with unlimited count = 0 (fourth
    // parameter).
    timerAlarm(timer, 3000000, true, 0);
  } else {
    Serial.println("Timer initialization failed!");
  } */
}

void update() {}

void reset() {}

void IRAM_ATTR countPulse() {
  Serial.println("Interrupted");
  pulseCount += 1;
}

void IRAM_ATTR OnTimer() {
  double rpm = 0;  // Default value to prevent errors
  if (pulseCount > 0) {
    rpm = (pulseCount * 60.0) / 5;  // Ensure divisor is nonzero
  }
  pulseCount = 0;
  xQueueOverwriteFromISR(rpmQueue, &rpm, NULL);
  Serial.println("RPM SENT");
}

void PIDTask(void *pvParameters) {
  double receivedRPM;

  while (1) {
    if (xQueueReceive(rpmQueue, &receivedRPM, portMAX_DELAY)) {
      Serial.println("RPM Received in PIDTask");
      int error = targetRPM - receivedRPM;
      int proportional = Kp * error;
      integral += Ki * error * dt;
      int derivative = Kd * (error - previousError) / dt;

      // Calculate the control output
      int output = proportional + integral + derivative;
      output =
          constrain(output, 0, 180);  // si el servo está entre 0 y 180 grados

      // Apply the control output to the servo
      Serial.print("OUTPUT: ");
      Serial.println(output);
      servoControl(output);

      previousError = error;
    }
    vTaskDelay(pdMS_TO_TICKS(dt * 1000));
  }
}
