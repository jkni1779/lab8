/*
 * movement.c
 *
 *  Created on: Jan 28, 2020
 *      Author: jkni1779
 */

#include "open_interface.h"
#include "movement.h"

double move_forward(oi_t *sensor_data, double distance_mm){

    oi_setWheels(100,100);
    double sum = 0;
    while(sum < distance_mm){
        oi_update(sensor_data);
        sum += sensor_data->distance;

    }
    oi_setWheels(0,0);

    return sum;
}

double move_backward(oi_t *sensor_data, double distance_mm){

    oi_setWheels(-100,-100);
    double sum = 0;
    while(sum < distance_mm){
        oi_update(sensor_data);
        sum -= sensor_data->distance;

    }
    oi_setWheels(0,0);

    return sum;
}

double turn_right(oi_t *sensor_data, double degrees) {

    if (degrees < 0) {
        degrees = degrees*(-1);
        return (-1.0)*turn_left(sensor_data, degrees);

    }

    oi_setWheels(-30,30);
    double sum = 0;
    while(sum < degrees) {
        oi_update(sensor_data);
        sum -= sensor_data->angle;
    }
    oi_setWheels(0,0);

    return sum;
}

double turn_left(oi_t *sensor_data, double degrees) {


    if (degrees < 0) {
        degrees = degrees*(-1);
        return (-1.0)*turn_right(sensor_data, degrees);

    }
    oi_setWheels(30,-30);
    double sum = 0;
    while(sum < degrees) {
        oi_update(sensor_data);
        sum += sensor_data->angle;
    }
    oi_setWheels(0,0);

    return sum;
}
