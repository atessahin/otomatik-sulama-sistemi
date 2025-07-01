#include "config.h" 
#include "functionality.h"

int main(void) {
    systemClockConfig();
    gpioConfig();
    stopWatering();
		SysTick_Config(84000);
    
    while (1) {
					sulama();          
    }
}

