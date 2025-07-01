#include "config.h"

void systemClockConfig(void)
{
	RCC->CR|=(1<<16); // HSE etkinlestir
	
	while(!(RCC->CR & (1<<17))); // HSE hazir olana kadar bekle
	
	FLASH->ACR|=(3U<<1)|(1<<8)|(1<<9)|(1<<10); // Flash bellegi yapilandir

	RCC->APB1ENR|=(1<<28); // Güç arabirimini etkinlestir
	PWR->CR|=(3U<<14); 

  RCC->CR &= ~(1 << 24);  // PLL devre disi birak
  while(RCC->CR & (1<<25)); // PLL kapanmasini bekle

	RCC->PLLCFGR|=(8<<0)| // PLLM degeri
	(336<<6)| // PLLN degeri
	(4<<16)| // PLLP degeri
	(1<<22); // PLL için HSE kaynagi seçimi
	
	RCC->CR |= (1 << 24);  // PLL etkinlestir
  while(!(RCC->CR & (1<<25))); // PLL kilitlenmesini bekle

  RCC->CFGR&=~(15U<<4); // AHB bölücü yok 84 MHz
  RCC->CFGR|=(4U<<10);  // APB1 /2 = 42 MHz
  RCC->CFGR&=~(7U<<13); // APB2 /1 = 84 MHz 
	
	RCC->CFGR|=(2<<0); // Sistemi PLL'e geçir
	while((RCC->CFGR & (3 << 2)) != (2 << 2));  // Sistem saatinin PLL oldugunu bekle
	
	SystemCoreClockUpdate(); // Sistem saat degiskenini güncelle
}


void gpioConfig()
{
    RCC->AHB1ENR |= (1<<2); // GPIOC clock enable
    RCC->AHB1ENR|=(1<<0); // GPIOA clock enable
	
		// PC4: Röle 
    GPIOC->MODER &= ~(3 << 8); 
    GPIOC->MODER |=  (1 << 8); 
    GPIOC->OTYPER &= ~(1 << 4); 
    GPIOC->PUPDR  &= ~(3 << 8); 
	 
	  // PC1: YL-69 
    GPIOC->MODER &= ~(3<<2);  
    GPIOC->PUPDR |= (1<<2); 
	
	
		// Configure PA2, PA3 
		/*GPIOA->MODER|=(2U<<4)|(2U<<6);
		GPIOA->OSPEEDR |= (3 << 4) | (3 << 6); 
		GPIOA->AFR[0] |= (7U << 8) | (7U << 12); */
}

//----------------
// !! UART TAMAMEN DEBUGLAMAK IÇIN YAZILDI!!
//----------------


/*
void UART2_SendChar(char ch)
{
    while(!(USART2->SR & (1 << 7)));  // Wait for TXE flag
    USART2->DR = ch;
}
void UART2_SendString(char *str)
{
    while(*str)
    {
        UART2_SendChar(*str);
        str++;
    }
}
void uartConfig()
{
	RCC->APB1ENR|=(1<<17);          // USART2 saatini etkinlestir
	
	USART2->CR1&=~(1<<13);          // USART2 devre disi
	
	USART2->BRR = 42000000 / 115200;   // Baud hizi için (115200)

	USART2->BRR = (22 << 4) | 13;  // Tam sayi = 22, Kesir = 13
	
	// 8 veri biti, parity yok, 1 stop biti
	USART2->CR1 &= ~((1 << 12) | (1 << 10));  // 8 bit veri, parity devre disi
	USART2->CR2 &= ~(3 << 12);      // 1 stop biti
	
	USART2->CR1 |= (1 << 3);        // Gönderme aktif
	USART2->CR1 |= (1 << 2);        // Alma aktif
	
	USART2->CR1|= (1<<13);          // UART aktif
}*/

void delay(uint32_t time)
{
    while(time--);
}