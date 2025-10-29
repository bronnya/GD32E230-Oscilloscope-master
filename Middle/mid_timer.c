#include "mid_timer.h"

static __IO uint16_t key_timer_value;			//������ʱ��
static __IO uint16_t tft_timer_value;			//��Ļ��ʱ��
static uint8_t key_timer_bit = RUN_MS_TIMER;		//ms��ʱ����־λ
static uint8_t tft_timer_bit = RUN_MS_TIMER;		//ms��ʱ����־λ

/*
 * �������ݣ���ʱ�������жϻص�����
 * ����������TIM_HandleTypeDef *htim -- ��ʱ�����
 * ����ֵ����
 */
 
void TIMER15_IRQHandler(void)
{
	if(key_timer_bit == RUN_MS_TIMER)
	{
		key_timer_value++;
		if(key_timer_value >= 10000){
			key_timer_value = 0;		//��ֹ����Խ��
		}
	}

	if(tft_timer_bit == RUN_MS_TIMER)
	{
		tft_timer_value++;
		if(tft_timer_value >= 10000){
			tft_timer_value = 0;		//��ֹ����Խ��
		}
	}
	timer_interrupt_flag_clear(TIMER15,TIMER_INT_FLAG_UP);
}

/*
 * �������ݣ��õ�������ʱ��ֵ
 * ������������
 * ����ֵ��uint16_t -- ��ʱ��ֵ
 */
uint16_t get_key_timer_value(void)
{
	return key_timer_value;
}

/*
 * �������ݣ����ð�����ʱ��ֵ
 * ������������
 * ����ֵ��uint16_t -- ��ʱ��ֵ
 */
void set_key_timer_value(uint16_t value)
{
	key_timer_value =  value;
}

/*
 * �������ݣ����ð�����ʱ����־λֵ
 * ����������uint8_t value
 * ����ֵ����
 */
void set_key_bit_value(uint8_t value)
{
	key_timer_bit = value;
}

/*
 * �������ݣ��õ���Ļ��ʱ��ֵ
 * ������������
 * ����ֵ��uint16_t -- ��ʱ��ֵ
 */
uint16_t get_tft_timer_value(void)
{
	return tft_timer_value;
}

/*
 * �������ݣ�������Ļ��ʱ��ֵ
 * ������������
 * ����ֵ��uint16_t -- ��ʱ��ֵ
 */
void set_tft_timer_value(uint16_t value)
{
	tft_timer_value =  value;
}

/*
 * �������ݣ�������Ļ��ʱ����־λֵ
 * ����������uint8_t value
 * ����ֵ����
 */
void set_tft_bit_value(uint8_t value)
{
	tft_timer_bit = value;
}

static __IO uint16_t ccnumber = 0;						//�������
static __IO uint32_t freq = 0;							//Ƶ��ֵ
static __IO uint16_t readvalue1 = 0, readvalue2 = 0;	//���β���ֵ
static __IO uint32_t count = 0;							//���ڼ��ʱ��

/*
 * �������ݣ���ʱ��ͨ������ص�����
 * ����������TIM_HandleTypeDef *htim -- ��ʱ�����
 * ����ֵ����
 */
void TIMER2_IRQHandler(void)
{
	if(SET == timer_interrupt_flag_get(TIMER2, TIMER_INT_FLAG_CH0))
  {
		if(0 == ccnumber){
			readvalue1 = timer_channel_capture_value_register_read(TIMER2, TIMER_CH_0);
			ccnumber = 1;
		}
		else if(1 == ccnumber)
		{
			readvalue2 = timer_channel_capture_value_register_read(TIMER2, TIMER_CH_0);
			if(readvalue2 > readvalue1){
				count = (readvalue2 - readvalue1); 
			}else{
				count = ((0xFFFFU - readvalue1) + readvalue2); 
			}
			freq = 1000000U / count;			
			readvalue1 = 0;readvalue2 = 0;
			ccnumber = 0;
			count=0;
		}
		timer_interrupt_flag_clear(TIMER2, TIMER_INT_FLAG_CH0);
	}
}

/*
 * �������ݣ��õ�Ƶ��ֵ
 * ������������
 * ����ֵ��uint32_t -- Ƶ��ֵ
 */
uint32_t get_freq_value(void)
{
	return freq;
}
