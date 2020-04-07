/*
 * adc.c
 *
 *  Created on: Feb 25, 2020
 *      Author: jkni1779
 */

#include "adc.h"
#include <stdint.h>
#include <adc.h>

void adc_init(){
    SYSCTL_RCGCADC_R |= 0b01;
    while ((SYSCTL_PRADC_R & 0b01) == 0) {};
    SYSCTL_RCGCGPIO_R |= 0x2;
    while ((SYSCTL_PRGPIO_R & 0x2) == 0) {};

    GPIO_PORTB_DIR_R &= 0xEF;
    GPIO_PORTB_DEN_R &= 0xEF;
    GPIO_PORTB_AFSEL_R |= 0x10;
    GPIO_PORTB_AMSEL_R |= 0x10;

    ADC0_ACTSS_R &= 0x7;
    ADC0_EMUX_R &= 0x0FFF;
    ADC0_SSMUX3_R &= 0x0;
    ADC0_SSMUX3_R |= 0xA;
    ADC0_SSCTL3_R &= 0x0;
    ADC0_SSCTL3_R |= 0x6;
    ADC0_IM_R &= 0xFFF0FFF0;
    ADC0_IM_R |= 0x8;
    ADC0_ACTSS_R |= 0x8;
    adc_read();
}

int adc_read(){
    ADC0_PSSI_R |= 0x8;
    int ain = ADC0_SSFIFO3_R;
    return ain;

}
