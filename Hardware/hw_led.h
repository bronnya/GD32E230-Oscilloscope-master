#ifndef __HW_LED_H
#define __HW_LED_H

#include "main.h"

//led����
struct led_class
{
	uint8_t led_state;			//LED��״̬
	uint8_t led_on_level;		//��LED�ĵ�ƽ
	uint32_t led_pin;				//LED������
	uint32_t led_gpio;			//LED�Ķ˿�
};

#define LED_ON 	0x01
#define LED_OFF 0x02

//��������װ�����һ����ʵ��
void led_turn_on(struct led_class *led);
void led_turn_off(struct led_class *led);
void led_toggle(struct led_class *led);
struct led_class led_init(uint32_t led_gpio,uint32_t led_pin,uint8_t led_on_level);

//������װ��ֱ�Ӹ���������
void led_turn_on_all(void);
void led_turn_off_all(void);
void led_toggle_all(void);

#endif

