/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
 #include <stdio.h>
 #include <string.h>
#include "LCD16x2.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
char time[30];
char date[30];
RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;


/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
RTC_HandleTypeDef hrtc;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
RTC_TimeTypeDef RtcTime;
RTC_DateTypeDef RtcDate;

uint8_t CompareHours = 6;
uint8_t CompareMinutes = 0;

uint8_t GlobalHours = 0;
uint8_t GlobalMinutes = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_RTC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void SetRTC(void);
void BackupDateToBR(void);

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_RTC_Init();

  /* USER CODE BEGIN 2 */

   LCD_Init();
   LCD_Clear();
   LCD_Set_Cursor(1, 1);
   LCD_Write_String("KONEWKA");
   LCD_Set_Cursor(2, 1);
   LCD_Write_String("USTAW GODZINE");
   HAL_Delay(1000);

   volatile uint8_t H_now = 0;
   volatile uint8_t Min_now = 0;

   uint8_t Flaga_ustawiania_godziny = 0;

   char H_char[2];
   char Min_char[2];

   LCD_Clear();

   // Flag_setting_time - if 0 it means that nothing is set, you need to set the hour,
   // if 1, minutes are set, and if 2, confirmation of the hour
   while(Flaga_ustawiania_godziny<2)
   {

	   if(Flaga_ustawiania_godziny==0)
	   {
		       // up button pressed - hour +1
			   if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)==GPIO_PIN_SET)
			   {
				   HAL_Delay(10);
				   H_now = H_now + 1;
				   if (H_now > 23)
				   {
					   H_now = 0;
				   }

			   }

			   //  down up button pressed - hour -1
			   if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2)==GPIO_PIN_SET)
			   {
				   HAL_Delay(10);
				   H_now = H_now - 1;
				   if (H_now >23 )
				   {
					   H_now = 23;
				   }
			   }

			   // get text to display
			   itoa(H_now,H_char,10);
			   LCD_Clear();
			   LCD_Set_Cursor(1, 1);
			   LCD_Write_String("GODZINA");
			   LCD_Set_Cursor(2, 1);
			   LCD_Write_String(H_char);
			   HAL_Delay(10);

	   }else if(Flaga_ustawiania_godziny==1) // set minutes
	   {
	       // up button pressed - minutes +1
		   if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)==GPIO_PIN_SET)
		   {
			   HAL_Delay(10);
			   Min_now = Min_now + 1;
			   if (Min_now > 59)
			   {
				   Min_now = 0;
			   }

		   }

		   //  down button pressed - minutes -1
		   if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2)==GPIO_PIN_SET)
		   {
			   HAL_Delay(10);
			   Min_now = Min_now - 1;
			   if (Min_now > 59)
			   {
				   Min_now = 59;
			   }

		   }

		   itoa(Min_now,Min_char,10);
		   LCD_Clear();
		   LCD_Set_Cursor(1, 1);
		   LCD_Write_String("MINUTA");
		   LCD_Set_Cursor(2, 1);
		   LCD_Write_String(Min_char);
		   HAL_Delay(10);
	   }

	   // ok button pressed
	   if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)==GPIO_PIN_SET)
	   {
		   HAL_Delay(30);
		   Flaga_ustawiania_godziny = Flaga_ustawiania_godziny +1;
	   }
   }

   //nice display of digits
   char H_Min_now[12] =  "0";
   if (H_now < 10) {
	   H_char[1] = H_char[0];
   	     H_char[0] = '0';
   	     //strcpy(H_Min_now, H_char);
   }
   strcpy(H_Min_now, H_char);
   strcat(H_Min_now, ":");
   if (Min_now < 10) {
	   Min_char[1] = Min_char[0];
	   Min_char[0] = '0';
    }
   strcat(H_Min_now, Min_char);

  //display
   LCD_Init();
   LCD_Clear();
   LCD_Set_Cursor(1, 1);
   LCD_Write_String("GODZINA:");
   LCD_Set_Cursor(2, 1);
   LCD_Write_String(H_Min_now);
   HAL_Delay(500);

   GlobalHours = H_now;
   GlobalMinutes = Min_now;

   MX_RTC_Init();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	// Measurement start
	  RTC_DateTypeDef gDate;
	  RTC_TimeTypeDef gTime;
	 // Get the RTC current Time
	  HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
	 // Get the RTC current Date
	  HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);


	  // check the hour of moisture measurement
	  if(gTime.Hours == CompareHours && gTime.Minutes == CompareMinutes && gTime.Seconds <= 5)
	  {
		  	  // moisture check on the sensor
			 if( HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0)!=GPIO_PIN_SET )
			 {
				 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
			     HAL_Delay(1000);
				 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
			 }
	  }



	  /*
	  if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0)==GPIO_PIN_SET) {
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
	  } else {
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
	  }
	  */

/*
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET); // zapalenie diody
	  HAL_Delay(1000);
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET); // zgaszenie diody
	  HAL_Delay(1000);
	  */

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_RTC;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = GlobalHours;
  sTime.Minutes = GlobalMinutes;
  sTime.Seconds = 0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_SUNDAY;
  sDate.Month = RTC_MONTH_MAY;
  sDate.Date = 6;
  sDate.Year = 23;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}


/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, PC1_pompa_Pin|LD4_Pin|LD3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, D4_PIN_Pin|D5_PIN_Pin|D6_PIN_Pin|D7_PIN_Pin
                          |EN_PIN_Pin|RS_PIN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC0_czujnik_Pin */
  GPIO_InitStruct.Pin = PC0_czujnik_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(PC0_czujnik_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PC1_pompa_Pin LD4_Pin LD3_Pin */
  GPIO_InitStruct.Pin = PC1_pompa_Pin|LD4_Pin|LD3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : Btn_OK_Pin Btn_Up_Pin Btn_Down_Pin */
  GPIO_InitStruct.Pin = Btn_OK_Pin|Btn_Up_Pin|Btn_Down_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : D4_PIN_Pin D5_PIN_Pin D6_PIN_Pin D7_PIN_Pin
                           EN_PIN_Pin RS_PIN_Pin */
  GPIO_InitStruct.Pin = D4_PIN_Pin|D5_PIN_Pin|D6_PIN_Pin|D7_PIN_Pin
                          |EN_PIN_Pin|RS_PIN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : TEST_clock_Pin */
  GPIO_InitStruct.Pin = TEST_clock_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(TEST_clock_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void set_time (void)
{
  RTC_TimeTypeDef sTime;
  RTC_DateTypeDef sDate;
  sTime.Hours = 0x10; // set hours
  sTime.Minutes = 0x20; // set minutes
  sTime.Seconds = 0x30; // set seconds
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
  sDate.WeekDay = RTC_WEEKDAY_THURSDAY; //  day
  sDate.Month = RTC_MONTH_AUGUST; //   month
  sDate.Date = 0x9; // date
  sDate.Year = 0x18; // year
  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
  //HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0x32F2); // backup register
}

void get_time(void)
{
 RTC_DateTypeDef gDate;
 RTC_TimeTypeDef gTime;
/* Get the RTC current Time */
 HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
/* Get the RTC current Date */
 HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);
/* Display time Format: hh:mm:ss */
 sprintf((char*)time,"%02d:%02d:%02d",gTime.Hours, gTime.Minutes, gTime.Seconds);
/* Display date Format: dd-mm-yy */
 sprintf((char*)date,"%02d-%02d-%2d",gDate.Date, gDate.Month, 2000 + gDate.Year);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
