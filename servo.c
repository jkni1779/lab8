#include <inc/tm4c123gh6pm.h>
#include <stdbool.h>
#include <stdint.h>
#include "driverlib/interrupt.h"
#include <servo.h>
#include "Timer.h"
#include <math.h>
#include <button.h>
#include <lcd.h>

volatile int servo_dir = 1; //-1 is clockwise, 1 is counter clockwise

void servo_init(){
    SYSCTL_RCGCGPIO_R |= 0x2;
    while((SYSCTL_PRGPIO_R & 0x2) == 0);
    SYSCTL_RCGCTIMER_R |= 0x2;
    while((SYSCTL_PRTIMER_R & 0x2) == 0);

    GPIO_PORTB_DEN_R |= 0x20;
    GPIO_PORTB_AFSEL_R |= 0x20;
    GPIO_PORTB_DIR_R |= 0x20;
    GPIO_PORTB_PCTL_R &= 0x11011111;
    GPIO_PORTB_PCTL_R |= 0x00700000;

    TIMER1_CTL_R &= 0x9480;
    TIMER1_CFG_R = 0x4;
    TIMER1_TBPR_R = 0xFF;
    TIMER1_TBMR_R |= 0x900A;
    TIMER1_TBILR_R = 0x4E200; //set period to 20ms
    TIMER1_TBMATCHR_R = 0xA380; //set to 0 degrees
    TIMER1_TBPMR_R = 0x4; //will always be 0x4
    TIMER1_CTL_R |= 0x0100;

    servo_dir = 1;
    servo_move(0.0, 90.0);
    return;
}

int servo_move(float cur_degrees, float degrees){
    if(degrees > 180){
        degrees = 180;
    }
    else if(degrees < 0){
        degrees = 0;
    }
    int match_val = (degrees * (-88.9)) + 41856;
    TIMER1_TBMATCHR_R = match_val;
    float d_degrees = abs(cur_degrees - degrees);
    int time = 5 * d_degrees;
    timer_waitMillis(time);

    return degrees;
}

float button_move(float cur_degrees){
    int button = 0;
    while((button = button_getButton()) == 0);

    switch (button){
        case 1:
            cur_degrees = servo_move(cur_degrees,(cur_degrees + (1.0 * servo_dir)));
            break;
        case 2:
            cur_degrees = servo_move(cur_degrees,(cur_degrees + (5.0 * servo_dir)));
            break;
        case 3:
            servo_dir *= -1;
            break;
        case 4:
            if(servo_dir > 0){
                cur_degrees = servo_move(cur_degrees,175.0);
            }
            else{
                cur_degrees = servo_move(cur_degrees,5.0);
            }
            break;
        default:
            return 0.0;
    }

    int match = 0x40000 + TIMER1_TBMATCHR_R;

    if(servo_dir > 0){
        lcd_printf("%d CCW",&match);
    }
    else{
        lcd_printf("%d CW",&match);
    }

    return cur_degrees;
}
