#include "hw_key.h"

/*
 * �������ݣ�����ʵ��ע��
 * ����������
							GPIO_TypeDef *key_gpio -- �����˿�
							uint16_t key_pin -- ��������
							key_press_level -- ��������ʱ��ƽ
 * ����ֵ��struct key_class -- �������
 */
struct key_class key_init(uint32_t key_gpio,uint32_t key_pin,uint8_t key_press_level)
{
	struct key_class key_handle;
	key_handle.key_gpio = key_gpio;
	key_handle.key_pin = key_pin;
	key_handle.key_press_level = key_press_level;
	key_handle.key_state = KEY_NoPress;
	key_handle.keyCnt = 0;
	key_handle.keyCount = 0;
	key_handle.keyFcnt = 0;
	key_handle.keyLongFlag = 0;
	return key_handle;
}

/*
 * �������ݣ�ɨ�赥��ʵ������ -- ÿ��10ms����һ��
 * ����������struct key_class *key_handle -- �������
 * ����ֵ����
 */
void key_scanf(struct key_class *key_handle)
{
	key_handle->key_state = KEY_NoPress;	//Ĭ����û�а�������
	//����а�������
	if(gpio_input_bit_get(key_handle->key_gpio,key_handle->key_pin) == key_handle->key_press_level)
	{
		key_handle->keyCnt++;						//��¼��������ʱ��
		if(key_handle->keyCnt >= 120)
		{
			key_handle->keyCnt = 120;			//��ֹ����Խ��
		}
	}
	else
	{
		//�������̧��
		if((key_handle->keyCnt >= 100) && (key_handle->keyLongFlag == 0)){
			//��������1s��֮ǰû�ж����֤���ǳ���
			key_handle->key_state = KeyLongPress;
		}
		else if(key_handle->keyCnt >= 2)
		{
			//��������ʱ�����20ms��֤����һ�ΰ���
			key_handle->keyCount++;     			//�������µĴ�������
			key_handle->keyFcnt = DOUBLE_TIME;   	//��ָ��ʱ�����ٴΰ�����˫��
			key_handle->keyLongFlag = 1;    		//�Ѿ���һ�ζ̰��ˣ����ܵȴ����������ſɳ���
		}
		key_handle->keyCnt = 0;
		if(key_handle->keyFcnt)
		{
			key_handle->keyFcnt--;  //���ʱ�䲻�ϼ���
			if(key_handle->keyFcnt <= 0)    
			{
					//���ʱ�䵽��
					if(key_handle->keyCount == 1){
							//����
							key_handle->key_state = KeyPress;
					}
					else if(key_handle->keyCount == 2){
							//˫��
							key_handle->key_state = KeyDoublePress;
					}
					key_handle->keyFcnt = 0;
					key_handle->keyCount = 0;
					key_handle->keyLongFlag = 0;
			}
		}
	}
}

/*
 * �������ݣ�����ɨ��,ȫ��ɨ�裬��Ҫ����ÿһ�����������ж� -- ÿ��10ms����һ��
 * ������������
 * ����ֵ���ж����ĸ��������£�֧�ֳ�����˫�����ǵ����жϣ�ͬһʱ�̽������һ�������ж�
 */
uint8_t key_scanf_all(void)
{
    uint8_t ret = KEY_ERROR;    //��������ֵ
    static uint8_t keyCnt[3] = {0};  //���ڰ�����ʱ����
    static uint8_t keyFcnt[3] = {0}; //�����жϰ�����ü����˫��
    static uint8_t keyCount[3] = {0};    //�������µĴ���
    static uint8_t keyLongFlag[3] = {0}; //����������־λ��ֻ�г�������ʱ�жϳ�������Ч
    if(GET_KEY1_IN == RESET){   
        keyCnt[KEY1]++;           //��ʱ��������¼�������µ͵�ƽʱ��
        if(keyCnt[KEY1] >= 120){
            //��ֹ����Խ��
            keyCnt[KEY1] = 120;
        }
    }     
    if(GET_KEY1_IN == SET)
    {
        //�������̧��
        if((keyCnt[KEY1] >= 100) && (keyLongFlag[KEY1] == 0)){
            //��������1s��֮ǰû�ж����֤���ǳ���
            ret = Key1LongPress;
        }
        else if(keyCnt[KEY1] >= 2)
        {
            //��������ʱ�����20ms��֤����һ�ΰ���
            keyCount[KEY1]++;     //�������µĴ�������
            keyFcnt[KEY1] = DOUBLE_TIME;   //��300ms���ٴΰ�����˫��
            keyLongFlag[KEY1] = 1;    //�Ѿ���һ�ζ̰��ˣ����ܵȴ����������ſɳ���
        }
        keyCnt[KEY1] = 0;
        if(keyFcnt[KEY1])
        {
            keyFcnt[KEY1]--;  //���ʱ�䲻�ϼ���
            if(keyFcnt[KEY1] <= 0)    
            {
                //���ʱ�䵽��
                if(keyCount[KEY1] == 1){
                    //����
                    ret = Key1Press;
                }
                else if(keyCount[KEY1] ==2){
                    //˫��
                    ret = Key1DoublePress;
                }
                keyFcnt[KEY1] = 0;
                keyCount[KEY1] = 0;
                keyLongFlag[KEY1] = 0;
            }
        }
    }

    if(GET_KEY2_IN == RESET){   
        keyCnt[KEY2]++;           //��ʱ��������¼�������µ͵�ƽʱ��
        if(keyCnt[KEY2] >= 120){
            //��ֹ����Խ��
            keyCnt[KEY2] = 120;
        }
    }     
    if(GET_KEY2_IN == SET)
    {
        //�������̧��
        if((keyCnt[KEY2] >= 100) && (keyLongFlag[KEY2] == 0)){
            //��������1s��֮ǰû�ж����֤���ǳ���
            ret = Key2LongPress;
        }
        else if(keyCnt[KEY2] >= 2)
        {
            //��������ʱ�����20ms��֤����һ�ΰ���
            keyCount[KEY2]++;     //�������µĴ�������
            keyFcnt[KEY2] = DOUBLE_TIME;   //��300ms���ٴΰ�����˫��
            keyLongFlag[KEY2] = 1;    //�Ѿ���һ�ζ̰��ˣ����ܵȴ����������ſɳ���
        }
        keyCnt[KEY2] = 0;
        if(keyFcnt[KEY2])
        {
            keyFcnt[KEY2]--;  //���ʱ�䲻�ϼ���
            if(keyFcnt[KEY2] <= 0)    
            {
                //���ʱ�䵽��
                if(keyCount[KEY2] == 1){
                    //����
                    ret = Key2Press;
                }
                else if(keyCount[KEY2] ==2){
                    //˫��
                    ret = Key2DoublePress;
                }
                keyFcnt[KEY2] = 0;
                keyCount[KEY2] = 0;
                keyLongFlag[KEY2] = 0;
            }
        }
    }
		
		if(GET_KEY3_IN == RESET){   
        keyCnt[KEY3]++;           //��ʱ��������¼�������µ͵�ƽʱ��
        if(keyCnt[KEY3] >= 120){
            //��ֹ����Խ��
            keyCnt[KEY3] = 120;
        }
    }     
    if(GET_KEY3_IN == SET)
    {
        //�������̧��
        if((keyCnt[KEY3] >= 100) && (keyLongFlag[KEY3] == 0)){
            //��������1s��֮ǰû�ж����֤���ǳ���
            ret = Key3LongPress;
        }
        else if(keyCnt[KEY3] >= 2)
        {
            //��������ʱ�����20ms��֤����һ�ΰ���
            keyCount[KEY3]++;     //�������µĴ�������
            keyFcnt[KEY3] = DOUBLE_TIME;   //��300ms���ٴΰ�����˫��
            keyLongFlag[KEY3] = 1;    //�Ѿ���һ�ζ̰��ˣ����ܵȴ����������ſɳ���
        }
        keyCnt[KEY3] = 0;
        if(keyFcnt[KEY3])
        {
            keyFcnt[KEY3]--;  //���ʱ�䲻�ϼ���
            if(keyFcnt[KEY3] <= 0)    
            {
                //���ʱ�䵽��
                if(keyCount[KEY3] == 1){
                    //����
                    ret = Key3Press;
                }
                else if(keyCount[KEY3] ==2){
                    //˫��
                    ret = Key3DoublePress;
                }
                keyFcnt[KEY3] = 0;
                keyCount[KEY3] = 0;
                keyLongFlag[KEY3] = 0;
            }
        }
    }
    return ret;
}

