/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f401_discovery_accelerometer.h"
#include "stm32f401_discovery_gyroscope.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
#define FFT_LENGTH         256
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
typedef struct {

	float in;
	float out;

}InformationTypeDef;
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
typedef struct
{
	float real;
	float imag;;

}ComplexTypeDef;

typedef enum{  NO_WIND, HM_WIND, HN_WIND }fftWindTyped;

typedef struct
{
	ComplexTypeDef  Input[FFT_LENGTH];
	float  Result[FFT_LENGTH*2];
	uint32_t        current_sample;
    fftWindTyped    fft_windowing;
} FFT_TypeDef;
/* USER CODE END EM */


#define FIRST_HALF           1
#define SECOND_HALF          2

typedef enum{  FIR_FILTRE, IIR_FILTRE, RC_FILTRE, NOTCH_FILTRE }FiltreType;


typedef enum {ACCELRO, SIN_WAVE,DUAL_SIN_WAVE, THRID_SIN_WAVE,GYRO_WAVE} InType;
typedef struct{
	InType Type;
    float inputFreq1_Hz;   /*2Hz*/
    float inputFreq2_Hz;
    float inputFreq3_Hz ;   /*2Hz*/

}inputSimuTypeDef;




typedef struct
{
  uint8_t fft_enable;
  uint8_t dft_enable;
  uint8_t arm_enable;


}fftType_TypedDef;

typedef struct{

	         inputSimuTypeDef   In;
	         FiltreType    filtre_Type;

	         uint8_t fir_enable;
	         uint8_t iir_enable;
	         uint8_t notch_enable;
	         fftType_TypedDef fft;


}SimuleTypeDef;

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
