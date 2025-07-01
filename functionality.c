#include "config.h"

#define WATERING_DURATION 10000  // 10 saniye
#define CHECK_INTERVAL     60000 // Her 60 saniyede kontrol

volatile uint32_t systemTick = 0;
volatile uint32_t lastCheckTime = 60001;  
volatile uint32_t wateringStart = 0;  
volatile uint8_t isWatering = 0;      

void SysTick_Handler(void) {
    systemTick++;
}

void startWatering() {
    GPIOC->ODR |= (1 << 4);   // HIGH = Motor çalisir
		isWatering=1;
}

void stopWatering() {
    GPIOC->ODR &= ~(1 << 4);  // LOW = Motor durur  
}

uint8_t wetLevel(void)
{
   
    uint8_t moisture_status = !(GPIOC->IDR & (1 << 1));
    
    return moisture_status;   // 1 = Islak, 0 = Kuru
}

void sulama(void) {
    uint32_t current_time = systemTick;
    int wetLvl = wetLevel();
    
    if (isWatering) {
        if ((current_time - wateringStart) >= WATERING_DURATION) {
            stopWatering();	// Süre dolduysa motoru durdur
            isWatering = 0;
            lastCheckTime = current_time;
        }
        return; 
    }
    
    if (wetLvl == 0) {// Toprak kuruysa
        if ((current_time - lastCheckTime) >= CHECK_INTERVAL) {
            startWatering();	// Sulamayi baslat
            isWatering = 1;
            wateringStart = current_time;    
            lastCheckTime = current_time;
        }
        return;
    }
    
    else if (wetLvl == 1) {// Toprak islaksa
        isWatering = 0;  
				wateringStart = current_time; 
        lastCheckTime = current_time;
    }
}