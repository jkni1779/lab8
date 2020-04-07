#include <ping.h>
#include <timer.h>

volatile int timeStart;
volatile int timeFinish;
volatile int rising_falling; //0 if falling 1 if rising

void ping_init(){
    SYSCTL_RCGCGPIO_R |= 0x02;
    while((SYSCTL_PRGPIO_R & 0x02) == 0);
    SYSCTL_RCGCTIMER_R |= 0x08;
    while((SYSCTL_PRTIMER_R & 0x08) == 0);

    GPIO_PORTB_AFSEL_R = 0x08;
    GPIO_PORTB_PCTL_R |= 0x00007000;

    TIMER3_CTL_R &= 0xF2FF;
    TIMER3_CFG_R = 0x04;
    TIMER3_TBMR_R &= 0xB8;
    TIMER3_TBMR_R |= 0x47;
    TIMER3_IMR_R |= 0x100;
    TIMER3_CTL_R |= 0x0D00;
    TIMER3_TBPR_R |= 0xFF;
    TIMER3_TBILR_R |= 0xFFFF;

    NVIC_EN1_R |= 0x10;
    NVIC_PRI9_R |= 0x40;

    IntRegister(INT_TIMER3B, rupt_handler);
}

void rupt_handler() {
    TIMER3_ICR_R |= 0xF1F;

    if (rising_falling == 0){
        timeFinish = TIMER3_TBR_R;
        rising_falling = 1;
    }
    else if(rising_falling == 1){
        timeStart = TIMER3_TBR_R;
        rising_falling = 0;
    }
}

void ping_trigger() {
    GPIO_PORTB_DEN_R |= 0x08;
    GPIO_PORTB_DIR_R |= 0x08;
    GPIO_PORTB_AFSEL_R &= 0xF7;
    TIMER3_IMR_R &= 0xEFF;
    GPIO_PORTB_DATA_R |= 0x08;

    timer_waitMicros(5);

    GPIO_PORTB_DATA_R &= 0xFB;
    GPIO_PORTB_DIR_R &= 0xF7;
    GPIO_PORTB_AFSEL_R |= 0x8;
    TIMER3_IMR_R |= 0x100;
}


float ping_getDistance() {
    if(timeStart > timeFinish){
        timeFinish += 16777215;
    }
    float time = (timeFinish - timeStart) / 16000000;
    float distance = time * 34300;

    return distance;
}



