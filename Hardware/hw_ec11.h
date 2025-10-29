#ifndef __HW_EC11_H
#define __HW_EC11_H

#include "main.h"

struct ec11_class
{
	uint32_t ec11_Agpio;		//EC11��A�˿�
	uint32_t ec11_Apin;					//EC11��A����
	uint32_t ec11_Bgpio;		//EC11��B�˿�
	uint32_t ec11_Bpin;					//EC11��B����
	uint8_t ec11_direction;			//EC11�ķ���
};

#define ec11_forward 	0x01		//��ת
#define ec11_reversal 0x02		//��ת
#define ec11_static		0x03		//��ֹ

struct ec11_class ec11_init(uint32_t ec11_Agpio,uint32_t ec11_Apin,uint32_t ec11_Bgpio,uint32_t ec11_Bpin);
void ec11_exti_callback(struct ec11_class *handle);

#endif

