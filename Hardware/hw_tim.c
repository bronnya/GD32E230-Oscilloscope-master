#include "hw_tim.h"

/*
*   �������ݣ���ʼ��ͨ�ö�ʱ��15
*   ������������
*   ����ֵ��  ��
*/
void mx_tim15_init(void)
{   
    rcu_periph_clock_enable(RCU_TIMER15);	//ʹ��ʱ��
    
    timer_parameter_struct timer_initpara;	//��ʱ����ʼ�������ṹ��
    
		timer_deinit(TIMER15);	//��λ��ʱ��15
    
    timer_prescaler_config(TIMER15,1,TIMER_PSC_RELOAD_NOW);	//��������Ԥ��Ƶ��    
    
    timer_struct_para_init(&timer_initpara);	// ��ʼ���ṹ��
    
    // ���ö�ʱ������ 
		timer_initpara.prescaler        = 71;                 	//  ʱ��Ԥ��Ƶֵ 0-65535  psc_clk = CK_TIMER / pre
		timer_initpara.alignedmode      = TIMER_COUNTER_EDGE;   // ��Ե����
		timer_initpara.counterdirection = TIMER_COUNTER_UP;     // ���ϼ���
		timer_initpara.period           = 999;                  // ����
		//�����벶���ʱ��ʹ��  �����˲���ʹ�õĲ���Ƶ��֮��ķ�Ƶ���� 
		timer_initpara.clockdivision = TIMER_CKDIV_DIV1;        // ��Ƶ����
		//ֻ�и߼���ʱ������ ����Ϊx�����ظ�x+1�ν����ж� 
		timer_initpara.repetitioncounter = 0; 									// �ظ������� 0-255  
		timer_init(TIMER15,&timer_initpara); 										// ��ʼ����ʱ��
    
    timer_interrupt_flag_clear(TIMER15,TIMER_INT_FLAG_UP);	//��ʱ�������жϱ�־λ���
    
    nvic_irq_enable(TIMER15_IRQn,2);	//�ж����ȼ�
    
    timer_interrupt_enable(TIMER15,TIMER_INT_UP); //ʹ�ܸ����¼��ж�

    timer_disable(TIMER15);	//ʧ�ܶ�ʱ��15
}

/*
*   �������ݣ���ʼ��ͨ�ö�ʱ��2
*   ������������
*   ����ֵ��  ��
*/
void mx_tim2_init(void)
{
    timer_ic_parameter_struct timer_icinitpara;	//��ʱ��ͨ����������ṹ�� 
    
    timer_parameter_struct timer_initpara;	//��ʱ�������ṹ��
    
    rcu_periph_clock_enable(RCU_GPIOA);	//ʹ��ʱ��
    rcu_periph_clock_enable(RCU_TIMER2);
    
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_6);	//��������ģʽ
    
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_6);	//�������״̬
    
    gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_6);	//����Ϊ���ù���
    
    nvic_irq_enable(TIMER2_IRQn, 1U);	//��ʱ���ж�ʹ��
    
    timer_deinit(TIMER2);	//��λ��ʱ��
     
    timer_struct_para_init(&timer_initpara);	//��ʱ��������ʼ��
    
    timer_initpara.prescaler         = 71;                  //Ԥ��Ƶ������
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;  //���ض���
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;    //���ϼ���
    timer_initpara.period            = 65535;               //����
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;    //ʱ�ӷ�Ƶ
    timer_init(TIMER2, &timer_initpara);                    //������ʼ��
    
    timer_channel_input_struct_para_init(&timer_icinitpara);	//��ʱ��ͨ�����������ʼ��
    
    timer_icinitpara.icpolarity  = TIMER_IC_POLARITY_RISING;        //ͨ�����뼫��
    timer_icinitpara.icselection = TIMER_IC_SELECTION_DIRECTTI;     //ͨ������ģʽѡ��
    timer_icinitpara.icprescaler = TIMER_IC_PSC_DIV1;               //ͨ�����벶��Ԥ��Ƶ
    timer_icinitpara.icfilter    = 0x00;                            //ͨ�����벶���˲�
    timer_input_capture_config(TIMER2,TIMER_CH_0,&timer_icinitpara);
    
    timer_auto_reload_shadow_enable(TIMER2);	//ʹ���Զ���װ��ֵ
    
    timer_interrupt_flag_clear(TIMER2,TIMER_INT_FLAG_CH0);	//����жϱ�־λ
    
    timer_interrupt_enable(TIMER2,TIMER_INT_CH0);	//ʹ�ܶ�ʱ��ͨ���ж�
    
    timer_disable(TIMER2);	//��ʱ���ж�ʧ��
}

/*
*   �������ݣ���ʼ��ͨ�ö�ʱ��14
*   ������������
*   ����ֵ��  ��
*/
void mx_tim14_init(void)
{
	timer_oc_parameter_struct timer_ocinitpara;	//��ʱ����������ṹ��
	
  timer_parameter_struct timer_initpara;	//��ʱ����ʼ�������ṹ��
	
	rcu_periph_clock_enable(RCU_GPIOA);	//ʹ��ʱ��
	
	rcu_periph_clock_enable(RCU_TIMER14);	//ʹ�ܶ�ʱ��14
	
	gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_2);	//GPIO����ģʽ����--PA2-TIMER14_CH0
	
	gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_2);	//�����������
	
	gpio_af_set(GPIOA, GPIO_AF_0, GPIO_PIN_2);	//����ģʽ0
	
	timer_deinit(TIMER14);	//��λ��ʱ��14
	
	timer_struct_para_init(&timer_initpara);	//��ʼ����ʱ���ṹ�����
	
	timer_initpara.prescaler         = 71;									//Ԥ��Ƶ������
	timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;	//���ض���
	timer_initpara.counterdirection  = TIMER_COUNTER_UP;		//���ϼ���
	timer_initpara.period            = 999;									//����
	timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;		//ʱ�ӷ�Ƶ
	timer_initpara.repetitioncounter = 0;								    //��װ��ֵ
	timer_init(TIMER14, &timer_initpara);
	
	timer_channel_output_struct_para_init(&timer_ocinitpara);	//��ʼ����ʱ��ͨ����������ṹ��
	
	timer_ocinitpara.outputstate  = TIMER_CCX_ENABLE;						//���״̬�������ͨ������
	timer_ocinitpara.outputnstate = TIMER_CCXN_DISABLE;			    //�������״̬�ر�
	timer_ocinitpara.ocpolarity   = TIMER_OC_POLARITY_LOW;	    //�������Ϊ��
	timer_ocinitpara.ocnpolarity  = TIMER_OCN_POLARITY_LOW;     //�����������Ϊ��
	timer_ocinitpara.ocidlestate  = TIMER_OC_IDLE_STATE_HIGH;   //����״̬ͨ�����
	timer_ocinitpara.ocnidlestate = TIMER_OCN_IDLE_STATE_HIGH;  //����״̬����ͨ�����
	
	timer_channel_output_config(TIMER14, TIMER_CH_0, &timer_ocinitpara);
	
	timer_channel_output_pulse_value_config(TIMER14, TIMER_CH_0, 500);	//����Ƚ�ֵ
	
	//���ģʽ0������ʱ��С�ڱȽ�ֵʱ�������Ч��ƽ��Ϊ�ߣ����ڱȽ���ֵʱ���Ϊ��
	timer_channel_output_mode_config(TIMER14, TIMER_CH_0, TIMER_OC_MODE_PWM0);
	
	//Ӱ��ģʽ����ر�
	timer_channel_output_shadow_config(TIMER14, TIMER_CH_0, TIMER_OC_SHADOW_DISABLE);
	
	timer_auto_reload_shadow_enable(TIMER14);	//ʹ���Զ���װ��
	
	timer_primary_output_config(TIMER14, ENABLE);	//���ö�ʱ��Ϊ��Ҫ�������������ͨ��ʹ��
	
	timer_disable(TIMER14);		//ʧ�ܶ�ʱ��
}