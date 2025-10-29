#ifndef __MID_ADC_H
#define __MID_ADC_H

#include "main.h"

#define ADC_CONVERT_FINSIH    	0x01	//adc�ɼ����	
#define ADC_CONVERT_UN_FINSIH	0x02	//adc�ɼ�δ���
#define ADC_NUM 1000					//adc�ɼ�����

void get_adc_value_point(uint16_t *addr);
void Set_ADC_Channel(uint8_t channel);
uint16_t Get_ADC_Average(uint16_t num);
uint8_t get_adc_convert_value(void);
void set_adc_convert_value(uint8_t bit);

#endif
