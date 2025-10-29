#include "hw_ec11.h"

/*
 * �������ݣ�EC11ע��
 * ����������
						GPIO_TypeDef *ec11_Agpio -- EC11��A�˿�
						uint16_t ec11_Apin -- EC11��A����
						GPIO_TypeDef *ec11_Bgpio -- EC11��B�˿�
						uint16_t ec11_Bpin -- EC11��B����
 * ����ֵ����
 */
struct ec11_class ec11_init(uint32_t ec11_Agpio,uint32_t ec11_Apin,uint32_t ec11_Bgpio,uint32_t ec11_Bpin)
{
	struct ec11_class handle;
	handle.ec11_Agpio = ec11_Agpio;
	handle.ec11_Apin = ec11_Apin;
	handle.ec11_Bgpio = ec11_Bgpio;
	handle.ec11_Bpin = ec11_Bpin;
	handle.ec11_direction = ec11_static;
	return handle;
}

/*
 * �������ݣ�EC11�жϻص�������������Ϊ˫���ش���
 * ����������struct ec11_class *handle -- ec11���
 * ����ֵ����
 */
void ec11_exti_callback(struct ec11_class *handle)
{
	static uint8_t cnt = 0,b_value = 0;
	
	//A���½������ȴ���һ��
	if((gpio_input_bit_get(handle->ec11_Agpio,handle->ec11_Apin) == RESET) && (cnt == 0))
	{
		cnt++;
		b_value = 0;
		//�����ʱB��Ϊ�ߵ�ƽ
		if(gpio_input_bit_get(handle->ec11_Bgpio,handle->ec11_Bpin) == SET)
		{
			b_value = 1;
		}
	}
	//A���������ٴ���һ��
	else if((gpio_input_bit_get(handle->ec11_Agpio,handle->ec11_Apin) == SET) && (cnt == 1))
	{
		cnt = 0;
		//���B���ʱ�ǵ͵�ƽ����֮ǰ�Ǹߵ�ƽ
		if((gpio_input_bit_get(handle->ec11_Bgpio,handle->ec11_Bpin) == RESET) && (b_value == 1))
		{
			//��ת
			handle->ec11_direction = ec11_reversal;
		}
		//�����ʱB���Ǹߵ�ƽ����֮ǰ�ǵ͵�ƽ
		else if((gpio_input_bit_get(handle->ec11_Bgpio,handle->ec11_Bpin) == SET) && (b_value == 0))
		{
			//��ת
			handle->ec11_direction = ec11_forward;
		}
	}
	exti_interrupt_flag_clear(EXTI_4);
}
