#include "common.h"
#include "gpio.h"
#include "state.h"

class PitchController : public State {
 private:
  // Internal variables
  const int targetRPM = 150;
  float integral = 0;
  const float Kp = 0.5, Ki = 0.01, Kd = 0.0, dt = 3.0;
  float previousError = 0;
  volatile unsigned long pulseCount = 0;
  hw_timer_t *timer = NULL;

 public:
  PitchController();
  ~PitchController() {};

  void pitchInit();
  void IRAM_ATTR countPulse();
  void IRAM_ATTR onTimer();
  void update();

  void reset();
};
