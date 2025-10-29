#include "mid_adc.h"
#include "stdio.h"
#include "string.h"

static uint8_t adc_convert_bit = ADC_CONVERT_UN_FINSIH;

/*
 * �������ݣ�ð������
 * ������������
 * ����ֵ����
 */
static void bubble_sort(float arr[], uint16_t len)
{
    uint16_t i = 0, j = 0;
    float temp = 0;
    for (i = 0; i < len - 1; i++)
    {
        for (j = 0; j < len - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

/*
 * �������ݣ��õ���ӦADCͨ��ֵ
 * ������������
 * ����ֵ����
 */
static uint16_t Get_ADC_Val(void)
{
	uint16_t val = 0;
	
	//���òɼ�ͨ��
	adc_software_trigger_enable(ADC_REGULAR_CHANNEL);
	//�ȴ� ADC ������� 
	while ( adc_flag_get(ADC_FLAG_EOC) == RESET ){            
	}
	val = adc_regular_data_read();
	
	return val;
}

/*
 * �������ݣ��õ�ADCͨ����ƽ��ֵֵ
 * ������������
 * ����ֵ����
 */
uint16_t Get_ADC_Average(uint16_t num)
{
    uint16_t i = 0,val = 0;
    uint32_t sum_val = 0;
    uint16_t max_value = 0,min_value = 9999;
    for(i =0;i<num;i++)
    {
        val = Get_ADC_Val();
        if(min_value > val){
            min_value = val;
        }
        if(max_value < val){
            max_value = val;
        }
        sum_val = sum_val + val;
    }
    sum_val = sum_val - max_value - min_value;
    sum_val = sum_val / (num - 2);
    return sum_val;
}

/*
 * �������ݣ�����ADCͨ��
 * ������������
 * ����ֵ����
 */
void Set_ADC_Channel(uint8_t channel)
{
	//ADC����ͨ������--PA3��˳����0��ͨ��3������ʱ��13.5��ʱ������
	adc_regular_channel_config(0, channel, ADC_SAMPLETIME_13POINT5);
}

/*
 * �������ݣ�ADCת������жϻص�
 * ������������
 * ����ֵ����
 */
void DMA_Channel0_IRQHandler(void)
{
	if(dma_interrupt_flag_get(DMA_CH0, DMA_INT_FLAG_FTF)){
		adc_convert_bit = ADC_CONVERT_FINSIH;
		dma_channel_disable(DMA_CH0);	//�ر�dma
		dma_interrupt_flag_clear(DMA_CH0, DMA_INT_FLAG_G);	//����жϱ�־λ
	}
}

/*
 * �������ݣ��õ�adcת����ɱ�־λ
 * ������������
 * ����ֵ��uint8_t
 */
uint8_t get_adc_convert_value(void)
{
	return adc_convert_bit;
}

/*
 * �������ݣ�����adcת����ɱ�־λ
 * ������������
 * ����ֵ��uint8_t
 */
void set_adc_convert_value(uint8_t bit)
{
	adc_convert_bit = bit;
}
