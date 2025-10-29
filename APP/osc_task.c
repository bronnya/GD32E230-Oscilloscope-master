#include "osc_task.h"
#include "mid_lcd.h"
#include "stdio.h"
#include "string.h"
#include "mid_pwm.h"
#include "mid_timer.h"
#include "mid_adc.h"
#include "hw_key.h"
#include "hw_adc.h"

#define volThreshold 40								//��ʼ������ʾλ��
#define wave_width	 100							//������ʾ����-���
#define wave_height	 128							//������ʾ����-�߶�

static uint8_t step_value = 10;						//����ɨ�貽��ֵ
static int16_t oldWave[wave_width];					//��һ����ʾ�Ĳ�������
static int16_t newWave[wave_width];					//�µ���ʾ��������
static float maxVol = 0;							//�����ź�����ѹ
static float minVol = 0;							//�����ź���С��ѹ
static uint16_t adc_value[ADC_NUM];					//���adcԭʼ����
static uint16_t adc_value2[ADC_NUM];				//���adcԭʼ����
static uint8_t osc_stop_bit = OSC_RUN;				//������ͣ��־λ


/*
*   �������ݣ�ע�Შ�����ݲɼ�
*   ������������
*   ����ֵ��  ��
*/
void Register_oscShowData(void)
{
	mx_adc_dma_init((uint32_t)(&adc_value), ADC_NUM);
}

/*
*   �������ݣ����������ʾ����
*   ������������
*   ����ֵ��  ��
*/
void clear_adc_value(void)
{
	set_adc_convert_value(ADC_CONVERT_UN_FINSIH);
	memset(adc_value,0,ADC_NUM);
}

/*
*   �������ݣ�����ɨ�貽��ֵ
*   ����������uint8_t value -- ����ֵ
*   ����ֵ��  ��
*/
void set_step_value(uint8_t value)
{
	step_value = value;
}

/*
*   �������ݣ��õ�ɨ�貽��ֵ
*   ������������
*   ����ֵ��  uint8_t value -- ����ֵ
*/
uint8_t get_step_value(void)
{
	return step_value;
}

/*
*   �������ݣ����ò��α�־λ
*   ����������uint8_t value -- 
						��OSC_PAUSE/OSC_RUN
*   ����ֵ��  ��
*/
void set_osc_stop_bit(uint8_t value)
{
	osc_stop_bit = value;
}

/*
*   �������ݣ��õ����α�־λ
*   ������������
*   ����ֵ��  uint8_t value -- 
						��OSC_PAUSE/OSC_RUN
*/
uint8_t get_osc_stop_bit(void)
{
	return osc_stop_bit;
}


/*
 * �������ݣ�TFT��ʾ��̬UI
 * ������������
 * ����ֵ����
 */
void TFT_StaticUI(void)
{
    uint16_t i=0;
    
    char showData[32]={0};
    
    TFT_ShowChinese(10,0,(uint8_t *)"����ʾ����",BLACK,GREEN,16,0);
    
    sprintf(showData,"  PWM ");
    TFT_ShowString(110,0,(uint8_t *)showData,BLACK,YELLOW,16,0);  
    memset(showData,0,32);
    
    TFT_ShowChinese(110,20,(uint8_t *)"���״̬",WHITE,PURPLE,12,0);
    
    sprintf(showData,"      ");
    TFT_ShowString(110,36,(uint8_t *)showData,BLACK,YELLOW,16,0);  
    memset(showData,0,32);
    
    TFT_ShowChinese(110,56,(uint8_t *)"���Ƶ��",WHITE,PURPLE,12,0);
    
    sprintf(showData,"      ");
    TFT_ShowString(110,72,(uint8_t *)showData,BLACK,YELLOW,16,0);  
    memset(showData,0,32);
    
    sprintf(showData,"      ");
    TFT_ShowString(110,92,(uint8_t *)showData,WHITE,PURPLE,12,0);  
    memset(showData,0,32);
    TFT_ShowChinese(118,92,(uint8_t *)"ռ�ձ�",WHITE,PURPLE,12,0);
    
    sprintf(showData,"      ");
    TFT_ShowString(110,106,(uint8_t *)showData,BLACK,YELLOW,16,0);  
    memset(showData,0,32);
    
    TFT_ShowChinese(5,92,(uint8_t *)"�����ֵ",WHITE,PURPLE,12,0);
    
    TFT_ShowChinese(55,92,(uint8_t *)"����Ƶ��",WHITE,PURPLE,12,0);
    
    for(i=0;i<=128;i=i+2)
    {
        TFT_DrawPoint(106,i,YELLOW);
    }
    
    for(i=0;i<100;i++)
    {
        TFT_DrawPoint(i,81,GREEN);
    }
    for(i=30;i<=80;i++)
    {
        TFT_DrawPoint(0,i,GREEN);
    }
    for(i=0;i<10;i++)
    {
        TFT_DrawPoint((i*10)+2,82,GREEN); 
        TFT_DrawPoint((i*10)+3,82,GREEN); 
    }
    for(i=0;i<10;i++)
    {
        TFT_DrawPoint((i*10)+2,83,GREEN); 
        TFT_DrawPoint((i*10)+3,83,GREEN);
    }
}

/*
 * �������ݣ�����ɨ�账����
 * ����������const uint16_t key_pin -- �������ţ�const uint8_t key_state -- ����״̬
 * ����ֵ����
 */
void key_scanf_handle(const uint16_t key_pin,const uint8_t key_state)
{
	uint16_t temp_period = 0;
	float temp_duty = 0;
	if(key_pin == KEY1_Pin)
	{
		switch(key_state)
		{
			case KeyPress:
				if(get_pwm_state() == PWM_OFF)
				{
					set_pwm_period(get_pwm_period());
					set_pwm_duty(get_pwm_duty());
					set_pwm_state(PWM_ON);
				}
				else
				{
					set_pwm_state(PWM_OFF);
				}
				break;
			default:
				break;
		}
	}
	else if(key_pin == KEY2_Pin)
	{
		switch(key_state)
		{
			case KeyPress:
				temp_duty = (get_pwm_duty()*1.0f / get_pwm_period());
				temp_period = get_pwm_period();
				temp_period = temp_period / 2;
				if(temp_period < 125)
				{
					temp_period = 1000;
				}
				set_pwm_period(temp_period);
				set_pwm_duty(temp_period * temp_duty);
				break;
			default:
				break;
		}
	}
	else if(key_pin == KEY3_Pin)
	{
		switch(key_state)
		{
			case KeyPress:
				temp_duty = get_pwm_period() * 0.04f + get_pwm_duty();
				if(temp_duty > get_pwm_period())
				{
					temp_duty = get_pwm_period();
				}
				set_pwm_duty(temp_duty);
				break;
			case KeyDoublePress:
				temp_duty = get_pwm_duty() - get_pwm_period() * 0.04f;
				if(temp_duty < 0)
				{
					temp_duty = 0;
				}
				set_pwm_duty(temp_duty);
				break;
			default:
				break;
		}
	}
	else if(key_pin == KEYD_Pin)
	{
		switch(key_state)
		{
			case KeyPress:
				if(get_osc_stop_bit() == OSC_RUN)
				{
					set_osc_stop_bit(OSC_PAUSE);
				}
				else
				{
					set_osc_stop_bit(OSC_RUN);
				}
				break;
			default:
				break;
		}
	}
}

/*
*   �������ݣ�  ��ʾUIЧ��
*   ����������  ��
*   ����ֵ��    ��
*/
void TFT_ShowUI(void)
{	
	uint32_t freq = 0;
	uint8_t pwm_state = 0;
	char showData[32]={0};
	
	sprintf(showData,"%1.2fV ",(maxVol - minVol) * 2);
	TFT_ShowString(5,106,(uint8_t *)showData,BLACK,GREEN,16,0);
	memset(showData,0,32);
	
	freq = get_freq_value();
	if(freq >= 1000)
	{
		sprintf(showData,"%3.1fKHz",(freq / 1000.0f));
		TFT_ShowString(55,106,(uint8_t *)showData,BLACK,GREEN,16,0);  
		memset(showData,0,32);
	}
	else
	{
		sprintf(showData,"%3dHz ",freq);
		TFT_ShowString(55,106,(uint8_t *)showData,BLACK,GREEN,16,0);  
		memset(showData,0,32);  
	}
	
	pwm_state = get_pwm_state();
	if(pwm_state == PWM_ON)
	{   
		TFT_ShowChinese(118,36,(uint8_t *)"��",BLACK,YELLOW,16,0);
	}
	else
	{
		TFT_ShowChinese(118,36,(uint8_t *)"�ر�",BLACK,YELLOW,16,0);     
	}
	
	if(get_pwm_out_freq() >= 1000)
	{
		sprintf(showData,"%3dKHz",get_pwm_out_freq()/1000);
		TFT_ShowString(110,72,(uint8_t *)showData,BLACK,YELLOW,16,0); 	
		memset(showData,0,32); 
	}
	else
	{
		sprintf(showData," %3dHz",get_pwm_out_freq());
		TFT_ShowString(110,72,(uint8_t *)showData,BLACK,YELLOW,16,0);  
		memset(showData,0,32);
	} 
	sprintf(showData,"  %2d%%",(uint16_t)(( get_pwm_duty()*1.0f / get_pwm_period()) * 100));
	TFT_ShowString(110,106,(uint8_t *)showData,BLACK,YELLOW,16,0);  
	memset(showData,0,32); 
}

/*
*   �������ݣ�ʾ��������������ʾ
*   ������������
*   ����ֵ��  ��
*/
void osc_waveShow(uint16_t vref_value)
{
	uint16_t i = 0,t = 0,num = 0;
	int16_t prePos = 0;				//ǰһ��������
	float v_max = 0,v_min = 9999;
	if(get_adc_convert_value() == ADC_CONVERT_FINSIH)
	{
		//���adc���ݲɼ������
		for(i=0;i<ADC_NUM;i=i+step_value)
		{
			//��adc����ת��Ϊ��ѹֵ���Ŵ�20����3.3V���66��������Ʋ���
			//adc_value2[num] = ((adc_value[i] * 3.3f * 20) / 4095.0f);
			adc_value2[num] = (uint16_t)((((adc_value[i] * 1.0f) / vref_value) * 1.21f) * 20);
			if(v_min > adc_value2[num]){
				v_min = adc_value2[num];
			}
			else if(v_max < adc_value2[num]){
				v_max = adc_value2[num];
			}
			adc_value2[num] = 95 - adc_value2[num];
			num++;
		}
		for(i=0;i<ADC_NUM;i++)
		{
			//�õ�һ����ʼ����λ��
			if((adc_value2[i] < volThreshold) && (adc_value2[i+2] > volThreshold))
			{
				if(i > (ADC_NUM - wave_width))
				{
					t = 0;
				}
				else
				{
					t = i;
				}
				break;
			}
		}
		for(i=0;i<wave_width;i++)
		{
			//��ȡ��ʾ�������ݣ�����ʼ����λ�ÿ�ʼ
			newWave[i] = adc_value2[t+i];
		}
		prePos = newWave[0];
		for(i=1;i<wave_width-2;i++)
		{
			TFT_DrawLine(i,oldWave[i],i+1,oldWave[i+1],BLACK);	//�����һ���߶�	
			TFT_DrawLine(i,prePos,i+1,newWave[i],GREEN);		//��ʾ��ǰ�߶�
			prePos = newWave[i];
		}
		for(i=1;i<wave_width;i++)
		{
			//��¼��һ�β�������
			oldWave[i] = newWave[i-1];
		}
		maxVol = v_max / 20.0f;
		minVol = v_min / 20.0f;
		clear_adc_value();
		Register_oscShowData();
	}
}
