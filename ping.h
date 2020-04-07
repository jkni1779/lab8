#ifndef PING_H_
#define PING_H_

#include <stdint.h>
#include <inc/tm4c123gh6pm.h>

void rupt_handler(void);
void ping_init(void);
void ping_trigger(void);
float ping_getDistance(void);



#endif /* PING_H_ */
