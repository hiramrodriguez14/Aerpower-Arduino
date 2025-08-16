
#include "fsm.h"
#include "lcd.h"
#define EXITED_SUCCESSFULLY (0u)
int main(void) {
  lcd_run();            // Start running the LCD RTOS on core 1
  state_machine_run();  // Start running the Turbine FSM on core 0

  ASSERT(0);

  return EXITED_SUCCESSFULLY;
}
