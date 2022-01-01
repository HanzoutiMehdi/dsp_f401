/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : fft_task.c
  * @brief          : fft task
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "arm_math.h"

/*FFT---------------------*/


extern QueueHandle_t xQueue_fft;





void fft_task(void const * argument);
static void dft(FFT_TypeDef *hfft, uint32_t buffer);
static void fft(FFT_TypeDef *hfft, uint32_t buffer);
float32_t AmpResult_fft[FFT_LENGTH];
float32_t Ampinp_fft[FFT_LENGTH];
uint32_t uAmpIn_fft[FFT_LENGTH];
uint32_t uAmpResult_fft[FFT_LENGTH];




FFT_TypeDef  in_fft;
FFT_TypeDef  out_fft;




/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
static void dft(FFT_TypeDef *hfft, uint32_t buffer)
{


  uint32_t n,k;
  uint32_t indice_start;
  uint32_t indice_end;

  if (  buffer==FIRST_HALF)
  {
	indice_start=0 ;
	indice_end  =FFT_LENGTH/2;

  }
  else
  {
		indice_start=FFT_LENGTH/2 ;
		indice_end  =FFT_LENGTH;

  }

	  for (k=indice_start; k<indice_end; k++)
	  {
		 /*Clear */
		  hfft->Result[k]=0.0f;
		  hfft->Result[k+1]=0.0f;

	     for (n=indice_start ; n<indice_end ; n++)
     	   {
		     hfft->Result[k] += hfft->Input[n].real*cosf(2*PI*k*n/FFT_LENGTH) + hfft->Input[n].imag*sinf(2*M_PI*k*n/FFT_LENGTH);
		     hfft->Result[k+1] += hfft->Input[n].imag*cosf(2*PI*k*n/FFT_LENGTH) - hfft->Input[n].real*sinf(2*M_PI*k*n/FFT_LENGTH);
	       }
	     k++;
      }

}
/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
static void fft(FFT_TypeDef *hfft, uint32_t buffer)
{

}
float SAMPLING_FREQ = 100;
float FReqIn = 5.0;

void fft_task(void const * argument)
{
   uint32_t rx_mesage;
   uint32_t maxValue,maxIndex;
	while(1)
	{


		 if( xQueueReceive( xQueue_fft,  &( rx_mesage ),  20 ) == pdPASS )
		 {


		   	  dft(&in_fft,rx_mesage);

		   	  dft(&out_fft,rx_mesage);

		   	  /*Calcul amplitud when buffer is already processed */

		   	  if (rx_mesage==SECOND_HALF)
		   	  {
		   	   arm_cmplx_mag_f32(in_fft.Result ,(float*)Ampinp_fft,FFT_LENGTH);
		        /* Calculates maxValue and returns corresponding value */
		        arm_max_f32(Ampinp_fft, FFT_LENGTH, &maxValue, &maxIndex);


		   	   for(uint32_t i=0;i<FFT_LENGTH;i++)
		   		uAmpIn_fft[i]=Ampinp_fft[i];


		   	   arm_cmplx_mag_f32(out_fft.Result ,(float*)AmpResult_fft,FFT_LENGTH);

		   	   for(uint32_t i=0;i<FFT_LENGTH;i++)
		   		uAmpResult_fft[i]=AmpResult_fft[i];



		   	  }





		 }


	}



}





/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
