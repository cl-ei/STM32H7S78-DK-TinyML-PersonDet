#include "ltdc_lcd.h"

#include "STM32H7S78-DK/stm32h7s78_discovery.h"
#include "STM32H7S78-DK/stm32h7s78_discovery_lcd.h"

//#include "stm32h7rsxx_hal_dma2d.h"

HAL_StatusTypeDef MX_LTDC_ClockConfig(LTDC_HandleTypeDef *hltdc) {
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hltdc);

  HAL_StatusTypeDef         status;
  RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct = {0};
  RCC_OscInitTypeDef rcc_oscinitstruct = {0};

  /* LCD clock configuration */
  /* Typical PCLK is 25 MHz so the PLL3R is configured to provide this clock */
  /* LCD clock configuration */
  /* PLL3_VCO Input = HSI_VALUE/PLL3M = 64 Mhz / 4 = 16 */
  /* PLL3_VCO Output = PLL3_VCO Input * PLL3N = 16 Mhz * 25 = 400 */
  /* PLLLCDCLK = PLL3_VCO Output/PLL3R = 400/16 = 25Mhz */
  /* LTDC clock frequency = PLLLCDCLK = 25 Mhz */
  rcc_oscinitstruct.PLL3.PLLState = RCC_PLL_ON;
  rcc_oscinitstruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  rcc_oscinitstruct.HSEState = RCC_HSE_ON;

  rcc_oscinitstruct.PLL1.PLLState = RCC_PLL_NONE;
  rcc_oscinitstruct.PLL2.PLLState = RCC_PLL_NONE;
  rcc_oscinitstruct.PLL3.PLLSource = RCC_PLLSOURCE_HSE;

  rcc_oscinitstruct.PLL3.PLLM = 8;
  rcc_oscinitstruct.PLL3.PLLN = 200;
  rcc_oscinitstruct.PLL3.PLLP = 20;
  rcc_oscinitstruct.PLL3.PLLQ = 20;
  rcc_oscinitstruct.PLL3.PLLR = 20;
  rcc_oscinitstruct.PLL3.PLLS = 20;
  rcc_oscinitstruct.PLL3.PLLT = 20;
  rcc_oscinitstruct.PLL3.PLLFractional = 0;

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
  PeriphClkInitStruct.LtdcClockSelection = RCC_LTDCCLKSOURCE_PLL3R;

  if (HAL_RCC_OscConfig(&rcc_oscinitstruct) != HAL_OK)
  {
    status = HAL_ERROR;
  }
  else
  {
    status = HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
  }

  status = HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
  return status;
}

int32_t LTDC_LCD_Init() {
	int32_t s = BSP_LCD_InitEx(0, 1, LCD_PIXEL_FORMAT_RGB565, 800, 480);
	if (s != HAL_OK) {
		return s;
	}

	s = BSP_LCD_SetBrightness(0, 80);
	return s;
}
