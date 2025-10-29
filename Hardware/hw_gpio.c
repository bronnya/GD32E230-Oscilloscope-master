#include "hw_gpio.h"

/*
 * �������ݣ�gpio��ʼ��
 * ������������
 * ����ֵ����
 */
void mx_gpio_init(void)
{
	//ʹ��ʱ��
	rcu_periph_clock_enable(RCU_GPIOC);
	rcu_periph_clock_enable(RCU_GPIOB);
	rcu_periph_clock_enable(RCU_CFGCMP);
	
	//����Ĭ�����������ƽ
	gpio_bit_write(LED1_GPIO_Port,LED1_Pin,SET);
	gpio_bit_write(LED2_GPIO_Port,LED2_Pin,SET);
	gpio_bit_write(LCD_RES_GPIO_Port,LCD_RES_Pin,SET);
	gpio_bit_write(LCD_DC_GPIO_Port,LCD_DC_Pin,SET);
	gpio_bit_write(LCD_CS_GPIO_Port,LCD_CS_Pin,SET);
	gpio_bit_write(LCD_BLK_GPIO_Port,LCD_BLK_Pin,SET);
	
	//�������ģʽ����������
	gpio_mode_set(LED1_GPIO_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED1_Pin);
	//�������ģʽ����������
	gpio_mode_set(LED2_GPIO_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED2_Pin);
	//��������ģʽ������
	gpio_mode_set(KEY1_GPIO_Port, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, KEY1_Pin);
	//��������ģʽ������
	gpio_mode_set(KEY2_GPIO_Port, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, KEY2_Pin);
	//��������ģʽ������
	gpio_mode_set(KEY3_GPIO_Port, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, KEY3_Pin);
	//��������ģʽ������
	gpio_mode_set(KEYD_GPIO_Port, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, KEYD_Pin);
	//��������ģʽ������
	gpio_mode_set(KEYB_GPIO_Port, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, KEYB_Pin);
	//�������ģʽ����������
	gpio_mode_set(LCD_RES_GPIO_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LCD_RES_Pin);
	//�������ģʽ����������
	gpio_mode_set(LCD_DC_GPIO_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LCD_DC_Pin);
	//�������ģʽ����������
	gpio_mode_set(LCD_CS_GPIO_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LCD_CS_Pin);
	//�������ģʽ����������
	gpio_mode_set(LCD_BLK_GPIO_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LCD_BLK_Pin);
	
	//��������ģʽ������
	gpio_mode_set(KEYA_GPIO_Port, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, KEYA_Pin);
	
	//����������ͣ����������50Mhz
	gpio_output_options_set(LED1_GPIO_Port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LED1_Pin);
	//����������ͣ����������50Mhz
	gpio_output_options_set(LED2_GPIO_Port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LED2_Pin);
	//����������ͣ����������50Mhz
	gpio_output_options_set(LCD_RES_GPIO_Port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LCD_RES_Pin);
	//����������ͣ����������50Mhz
	gpio_output_options_set(LCD_DC_GPIO_Port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LCD_DC_Pin);
	//����������ͣ����������50Mhz
	gpio_output_options_set(LCD_CS_GPIO_Port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LCD_CS_Pin);
	//����������ͣ����������50Mhz
	gpio_output_options_set(LCD_BLK_GPIO_Port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LCD_BLK_Pin);
	
	//�ж���ʹ��
	nvic_irq_enable(EXTI4_15_IRQn,3U);
	//�����ж���
	syscfg_exti_line_config(EXTI_SOURCE_GPIOB,EXTI_SOURCE_PIN4);
	//��ʼ���ж��ߣ�����Ϊ�ж�ģʽ���������½��ش���
	exti_init(EXTI_4,EXTI_INTERRUPT,EXTI_TRIG_BOTH);
	//�жϱ�־λ���
	exti_interrupt_flag_clear(EXTI_4);
}
