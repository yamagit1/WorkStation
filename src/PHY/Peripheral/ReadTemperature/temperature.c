/*==============================================================================
 *  Author  : YAMA team
 *  email   : yamateamhaui@gmail.com
 *  address : Ha Noi University
 *  ( Nhon - Bac Tu liem - Ha Noi - Viet Nam)
 *============================================================================*/


#include "temperature.h"

__int16 gCurrentTemperatureC;
__uint16 gCurrentTemperatureF;


/**
 *
 */

void TEM_initialize(void)
{
	TIM_TimeBaseInitTypeDef timInitConfig;
	ADC_InitTypeDef adcInitConfigure;
	ADC_CommonInitTypeDef adcCommonConfigure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	timInitConfig.TIM_Prescaler 		= 42000 - 1;    // This will configure the clock to 2 kHz
	timInitConfig.TIM_CounterMode 		= TIM_CounterMode_Up;  // Count-up timer mode
	timInitConfig.TIM_Period 			= 2000 - 1;     // 2 kHz down to 1 Hz = 1 second
	timInitConfig.TIM_ClockDivision 	= TIM_CKD_DIV1;  // Divide clock by 1
	timInitConfig.TIM_RepetitionCounter = 0;    // Set to 0, not used
	TIM_TimeBaseInit(TIM2, &timInitConfig);
	/* TIM2 enable counter */
	TIM_Cmd(TIM2, ENABLE);

	ADC_DeInit();

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	adcCommonConfigure.ADC_Mode 			= ADC_Mode_Independent;
	adcCommonConfigure.ADC_Prescaler 		= ADC_Prescaler_Div8;
	adcCommonConfigure.ADC_DMAAccessMode 	= ADC_DMAAccessMode_Disabled;
	adcCommonConfigure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;

	ADC_CommonInit(&adcCommonConfigure);

	adcInitConfigure.ADC_Resolution 			= ADC_Resolution_12b;
	adcInitConfigure.ADC_ScanConvMode 			= DISABLE;
	adcInitConfigure.ADC_ContinuousConvMode 	= ENABLE;
	adcInitConfigure.ADC_ExternalTrigConvEdge 	= ADC_ExternalTrigConvEdge_None;
	adcInitConfigure.ADC_ExternalTrigConv 		= ADC_ExternalTrigConv_T1_CC1;
	adcInitConfigure.ADC_DataAlign 				= ADC_DataAlign_Right;
	adcInitConfigure.ADC_NbrOfConversion 		= 1;

	ADC_Init(ADC1, &adcInitConfigure);

	// ADC1 Configuration, ADC_Channel_TempSensor is actual channel 16
	ADC_RegularChannelConfig(ADC1, ADC_Channel_TempSensor, 1, ADC_SampleTime_144Cycles);

	// Enable internal temperature sensor
	ADC_TempSensorVrefintCmd(ENABLE);

	// Enable ADC conversion
	ADC_Cmd(ADC1, ENABLE);
}

/**
 *
 */

void TEM_updateTemperature(void)
{
	float TemperatureValue = 0;

	ADC_SoftwareStartConv(ADC1); //Start the conversion

	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET); //Processing the conversion

	TemperatureValue = ADC_GetConversionValue(ADC1); //Return the converted data
	TemperatureValue *= 3300;
	TemperatureValue /= 0xfff; //Reading in mV
	TemperatureValue /= 1000.0; //Reading in Volts
	TemperatureValue -= 0.760; // Subtract the reference voltage at 25°C
	TemperatureValue /= .0025; // Divide by slope 2.5mV
	TemperatureValue += 25.0; // Add the 25°C

	gCurrentTemperatureC = (__int16)TemperatureValue;

	TemperatureValue = ( TemperatureValue * 1.8) + 32;

	gCurrentTemperatureF = (__uint16)TemperatureValue;

}
