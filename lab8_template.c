#include "Timer.h"
#include "lcd.h"
#include "cyBot_Scan.h"  // For scan sensors
#include "uart.h"
#include "math.h"
#include "adc.h"
#include "ping.h"
#include "servo.h"
#include "button.h"

int main(void) {
    volatile float cur_degrees = 90.0;
    timer_init();
    servo_init();
    lcd_init();
    button_init();

    while(1){
        cur_degrees = button_move(cur_degrees);
    }
}
