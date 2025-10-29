#include "hw_spi.h"

/*
*   �������ݣ���ʼ��SPI0
*   ������������
*   ����ֵ����
*/
void mx_spi0_init(void)
{
    //spi�ṹ�����
    spi_parameter_struct spi_init_struct;
    
    //ʹ��GPIOAʱ��
    rcu_periph_clock_enable(RCU_GPIOA);
    
    //ʹ��SPI0ʱ��
    rcu_periph_clock_enable(RCU_SPI0);
    
    //���ø��ù���
    gpio_af_set(GPIOA, GPIO_AF_0,   GPIO_PIN_5 | GPIO_PIN_7);
    
    //ģʽ����
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_5 | GPIO_PIN_7);
    
    //�������
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5 | GPIO_PIN_7);
    
    //SPI0��λ
    spi_i2s_deinit(SPI0);
    
    //SPI������ʼ��
    spi_struct_para_init(&spi_init_struct);
    
    spi_init_struct.trans_mode           = SPI_TRANSMODE_BDTRANSMIT;//����˫���˫������ģʽ
    spi_init_struct.device_mode          = SPI_MASTER;              //����ģʽ
    spi_init_struct.frame_size           = SPI_FRAMESIZE_8BIT;      //8λ����λ��
    spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE; //���Ըߣ���2����Ե����
    spi_init_struct.nss                  = SPI_NSS_SOFT;            //NSS�������
    spi_init_struct.prescale             = SPI_PSC_2;               //2��Ƶ
    spi_init_struct.endian               = SPI_ENDIAN_MSB;          //��λ��ǰ
    spi_init(SPI0, &spi_init_struct);
    
    spi_enable(SPI0);
}