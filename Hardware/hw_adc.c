#include "hw_adc.h"
#include "systick.h"

void mx_adc_init(void)
{
	//ʹ������
	rcu_periph_clock_enable(RCU_GPIOA);
	
	//ʹ��ADCʱ��
	rcu_periph_clock_enable(RCU_ADC);
	
	//ʹ��ʱ�����ã����28M
	rcu_adc_clock_config(RCU_ADCCK_AHB_DIV9);
	
	//�������ã�PA3��ģ�����룬��������
	gpio_mode_set(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_3);
	
	//ADC��������ʹ��
	adc_special_function_config(ADC_CONTINUOUS_MODE, ENABLE); 

	//ADCɨ�蹦��ʧ�ܣ������һ��ͨ��
	adc_special_function_config(ADC_SCAN_MODE, DISABLE);

	//ADCע�����Զ�ת��ģʽʧ�ܣ���������ע����
	adc_special_function_config(ADC_INSERTED_CHANNEL_AUTO, DISABLE);    
	
	//ADC�����Ҷ���
	adc_data_alignment_config(ADC_DATAALIGN_RIGHT);
	
	//ADCͨ����������
	adc_channel_length_config(ADC_REGULAR_CHANNEL, 1U);   

	//ADC����ͨ������--PA3��˳����0��ͨ��3������ʱ��13.5��ʱ������
	adc_regular_channel_config(0, ADC_CHANNEL_3, ADC_SAMPLETIME_13POINT5);    
	
	/* ADC temperature and Vrefint enable */
  adc_tempsensor_vrefint_enable();
		
	//ADC���������ã��������
	adc_external_trigger_source_config(ADC_REGULAR_CHANNEL, ADC_EXTTRIG_REGULAR_NONE); 
	adc_external_trigger_config(ADC_REGULAR_CHANNEL, ENABLE);
	
	//ʹ��ADC
	adc_enable();
	delay_1ms(1U);
	
	//ʹ��У׼�͸�λ
	adc_calibration_enable();
	
	//DMAģʽʹ��
	adc_dma_mode_enable();
	
	//ADC�������ʹ��
	adc_software_trigger_enable(ADC_REGULAR_CHANNEL);
}

void mx_adc_dma_init(uint32_t adc_value,uint32_t number)
{
    rcu_periph_clock_enable(RCU_DMA);	//DMAʱ��ʹ��
    
    dma_parameter_struct dma_data_parameter;	//DMA�����ṹ��
    
    nvic_irq_enable(DMA_Channel0_IRQn, 0U);	//ʹ��DMA�ж�
    
    dma_deinit(DMA_CH0);	//ͨ��0��λ
    
    dma_data_parameter.periph_addr  = (uint32_t)(&ADC_RDATA);       //�������ַ
    dma_data_parameter.periph_inc   = DMA_PERIPH_INCREASE_DISABLE;  //�����ַ������
    dma_data_parameter.memory_addr  = (uint32_t)(adc_value);       //�ڴ��ַ
    dma_data_parameter.memory_inc   = DMA_MEMORY_INCREASE_ENABLE;   //�ڴ��ַ����
    dma_data_parameter.periph_width = DMA_PERIPHERAL_WIDTH_16BIT;   //����λ��
    dma_data_parameter.memory_width = DMA_MEMORY_WIDTH_16BIT;       //�ڴ�λ��
    dma_data_parameter.direction    = DMA_PERIPHERAL_TO_MEMORY;     //���赽�ڴ�
    dma_data_parameter.number       = number;                				//����
    dma_data_parameter.priority     = DMA_PRIORITY_HIGH;            //�����ȼ�
    
    dma_init(DMA_CH0, &dma_data_parameter);                         //DMAͨ��0��ʼ��
    
    dma_circulation_enable(DMA_CH0);                               	//DMAѭ��ģʽʹ��
    
    dma_channel_enable(DMA_CH0);                                    //DMAͨ��0ʹ��
    
    dma_interrupt_enable(DMA_CH0, DMA_CHXCTL_FTFIE);								//ʹ��DMA��������ж�
}