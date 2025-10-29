#include "hw_led.h"

/*
 * �������ݣ�����LED
 * ����������struct led_class--led��ָ��
 * ����ֵ����
 */
void led_turn_on(struct led_class *led)
{
	if(led->led_on_level == RESET)
	{
		gpio_bit_write(led->led_gpio,led->led_pin,RESET);
	}
	else
	{
		gpio_bit_write(led->led_gpio,led->led_pin,SET);
	}
	led->led_state = LED_ON;
}

/*
 * �������ݣ�Ϩ��LED
 * ����������struct led_class--led��ָ��
 * ����ֵ����
 */
void led_turn_off(struct led_class *led)
{
	if(led->led_on_level == RESET)
	{
		gpio_bit_write(led->led_gpio,led->led_pin,SET);
	}
	else
	{
		gpio_bit_write(led->led_gpio,led->led_pin,RESET);
	}
	led->led_state = LED_OFF;
}

/*
 * �������ݣ���תLED
 * ����������struct led_class--led��ָ��
 * ����ֵ����
 */
void led_toggle(struct led_class *led)
{
	if(led->led_state == LED_ON)
	{
		led_turn_off(led);
	}
	else
	{
		led_turn_on(led);
	}
}

/*
 * �������ݣ�ע��ledʵ��
 * ����������
					GPIO_TypeDef *led_gpio -- �˿ں�
					uint16_t led_pin -- ���ź�
					uint8_t led_on_level -- �򿪵�ƽ��׼
 * ����ֵ��struct led_class -- ledʵ�����
 */
struct led_class led_init(uint32_t led_gpio,uint32_t led_pin,uint8_t led_on_level)
{
	struct led_class led_handle;
	led_handle.led_gpio = led_gpio;
	led_handle.led_pin = led_pin;
	led_handle.led_on_level = led_on_level;
	led_handle.led_state = RESET;
	return led_handle;
}

/*
 * �������ݣ�������LED��ֱ�Ӹ���Ӳ������������װ
 * ����������
 * ����ֵ����
 */
void led_turn_on_all(void)
{
	gpio_bit_write(LED1_GPIO_Port,LED1_Pin,RESET);
	gpio_bit_write(LED2_GPIO_Port,LED2_Pin,RESET);
}

/*
 * �������ݣ��ر�����LED��ֱ�Ӹ���Ӳ������������װ
 * ����������
 * ����ֵ����
 */
void led_turn_off_all(void)
{
	gpio_bit_write(LED1_GPIO_Port,LED1_Pin,SET);
	gpio_bit_write(LED2_GPIO_Port,LED2_Pin,SET);
}

/*
 * �������ݣ���ת��ֱ�Ӹ���Ӳ������������װ
 * ����������
 * ����ֵ����
 */
void led_toggle_all(void)
{
	gpio_bit_toggle(LED1_GPIO_Port,LED1_Pin);
	gpio_bit_toggle(LED2_GPIO_Port,LED2_Pin);
}

