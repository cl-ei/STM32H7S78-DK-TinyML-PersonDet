#ifndef __EXT_FLASH_H
#define __EXT_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32h7rsxx_hal.h"
#include "STM32H7S78-DK/stm32h7s78_discovery.h"
#include "ltdc_lcd.h"

void RedLedBlink() {
	// RED LED -> PO1
	BSP_LED_Init(LED_RED);

	while (1) {
		BSP_LED_Off(LED_RED);
		HAL_Delay(700);

		BSP_LED_On(LED_RED);
		HAL_Delay(20);

		BSP_LED_Off(LED_RED);
		HAL_Delay(100);

		BSP_LED_On(LED_RED);
		HAL_Delay(20);
	}
}


void MyMain() {
	print("enter my main.");

	int32_t s = LTDC_LCD_Init();
	print("lcd init result: %d", s);

	uint16_t *addr;
	uint16_t x = 30, y = 100;
	while(1) {
		HAL_Delay(1500);
		addr = 0x90000000;
		for (uint32_t i = 0; i < 480*800; i++) {
			*addr = 0xFF00;
			addr++;
		}

		addr = 0x90000000;
		*(addr + 800*y + x) = 0xFFFF;
		*(addr + 800*y + x + 1) = 0xFFFF;
		*(addr + 800*(y+1) + x) = 0xFFFF;
		*(addr + 800*(y+1) + x + 1) = 0xFFFF;

		HAL_Delay(1500);
		addr = 0x90000000;
		for (uint32_t i = 0; i < 480*800; i++) {
			*addr = 0x0550;
			addr++;
		}

		addr = 0x90000000;
		*(addr + 800*y + x) = 0xF000;
		*(addr + 800*y + x + 1) = 0xF000;
		*(addr + 800*(y+1) + x) = 0xF000;
		*(addr + 800*(y+1) + x + 1) = 0xF000;
	}
}

#ifdef __cplusplus
}
#endif

#endif
