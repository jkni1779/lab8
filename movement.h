/*
 * Header file for the movement class.
 * All functions are based in mm
 * Jesse Knight
 * Eli Davidson
 *
 */

#ifndef MOVEMENT
#define MOVEMENT

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inc/tm4c123gh6pm.h>
#include "Timer.h"

double move_forward(oi_t *sensor_data, double distance_mm);
double move_backward(oi_t *sensor_data, double distance_mm);
double turn_right(oi_t *sensor, double degrees);
double turn_left(oi_t *sensor, double degrees);

#endif
