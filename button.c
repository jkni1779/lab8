#include "button.h"


/**
 * Initialize PORTE and configure bits 0-3 to be used as inputs for the buttons.
 */
void button_init() {
	static uint8_t initialized = 0;
	if(initialized){
		return;
	}

	SYSCTL_RCGCGPIO_R |= 0x00000010;

	while((SYSCTL_PRGPIO_R & 0x00000010) == 0){}

	GPIO_PORTE_DIR_R &= 0xFFFFFF00;
	GPIO_PORTE_DEN_R |= 0x000000FF;

	initialized = 1;
}

uint8_t button_getButton() {
    long data = GPIO_PORTE_DATA_R & 0x0000000F;
    data = data ^= 0x0000000F;
    uint8_t i;
    for(i = 1; i <= 4; i++){
        if (data > 1){
            data = data >> 1;
        }
        else if(data == 1){
            return i;
        }
    }
    return 0;
}
