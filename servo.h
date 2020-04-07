#ifndef SERVO_H_
#define SERVO_H_

#include <inc/tm4c123gh6pm.h>
#include <stdbool.h>
#include <stdint.h>
#include "Timer.h"
#include "driverlib/interrupt.h"
#include "button.h"

void servo_init(void);
int servo_move(float cur_degrees, float degrees);
float button_move(float cur_degrees);

#endif /* SERVO_H_ */
