#include "mid_pwm.h"

static uint8_t 	pwm_state = PWM_OFF;
static uint16_t pwm_period = 1000;		//Ĭ������Ϊ1000
static uint16_t pwm_duty = 500;			//Ĭ��ռ�ձ�Ϊ500						
	
/*
 * �������ݣ�����pwm�����ռ�ձ�
 * ����������uint16_t pwm_duty -- pwmռ�ձ�
 * ����ֵ����
 */
void set_pwm_duty(uint16_t duty)
{
	pwm_duty = duty;
	timer_channel_output_pulse_value_config(TIMER14, TIMER_CH_0, duty);
}

/*
 * �������ݣ��õ�pwm�����ռ�ձ�
 * ������������
 * ����ֵ��uint16_t pwm_duty
 */
uint16_t get_pwm_duty(void)
{
	return pwm_duty;
}

/*
 * �������ݣ�����pwm���������
 * ����������uint16_t pwm_period -- pwm����
 * ����ֵ����
 */
void set_pwm_period(uint16_t period)
{
	pwm_period = period;
	timer_autoreload_value_config(TIMER14,period);
}

/*
 * �������ݣ��õ�pwm���������
 * ������������
 * ����ֵ��uint16_t pwm_period
 */
uint16_t get_pwm_period(void)
{
	return pwm_period;
}

/*
 * �������ݣ�����pwm�����״̬
 * ����������uint8_t state -- ״ֵ̬
 * ����ֵ����
 */
void set_pwm_state(uint8_t state)
{
	if(state == PWM_ON)
	{
		//timer_channel_output_state_config(TIMER14,TIMER_CH_0,TIMER_CCXN_ENABLE);
		timer_enable(TIMER14);	//��ʼpwm�����ʱ����ʱ
		pwm_state = PWM_ON;
	}
	else if(state == PWM_OFF)
	{
		//timer_channel_output_state_config(TIMER14,TIMER_CH_0,TIMER_CCXN_DISABLE); 
		timer_disable(TIMER14);	//��ʼpwm�����ʱ����ʱ
		pwm_state = PWM_OFF;
	}
}

/*
 * �������ݣ��õ�pwm�����״̬
 * ������������
 * ����ֵ��uint8_t -- pwm״̬
 */
uint8_t get_pwm_state(void)
{
	return pwm_state;
}

/*
 * �������ݣ��õ�pwm��Ƶ��
 * ������������
 * ����ֵ��uint16_t
 */
uint16_t get_pwm_out_freq(void)
{
	uint16_t pwm_freq = 0;
	pwm_freq = TIMER_FREQ / pwm_period;
	return pwm_freq;
}
