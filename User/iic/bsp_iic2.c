/*******************************************************************************/
  
#include "bsp_iic.h"
#include "stm32f10x_i2c.h"


uint8_t I2c_Buf[3] = "AB0"; //�¶ȴ��

//*****************************************************  
// IIC2��ʼ����������ʼ��STM32Ӳ���Դ���IIC1  
//                 IIC1_SCL��ӦGPIO.B6  
//                 IIC1_SDA��ӦGPIO.B7  
//*****************************************************  
void I2C1_Init(void)  
{  
    /*GPIO��IIC��ʼ���ṹ��*/  
    GPIO_InitTypeDef GPIO_InitStructure;  
    I2C_InitTypeDef I2C_InitStructure;  
      
    /*GPIO��IICʱ��ʹ��*/  
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );     //GPIOBʱ��ʹ��  
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C1, ENABLE );      //IIC2ʱ��ʹ��  
  
    /*��ʼ��GPIO*/  
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;     //��ʼ��GPIO.B6(IIC2_SCL)��GPIO.B7(IIC2_SDA)  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;           //�������ٶ�50Hz  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;             //�������ģʽΪ���ù��ܿ�©���  
    GPIO_Init( GPIOB, &GPIO_InitStructure );                    //����GPIO��ʼ���ṹ���ʼ��GPIOB  
      
    /*��ʼ��IIC1*/
		I2C_DeInit(I2C1);
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;                  //����ΪIICģʽ  
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;          //����IIC��ռ�ձȣ��͵�ƽ���Ըߵ�ƽֵΪ2  
    I2C_InitStructure.I2C_OwnAddress1 = 0x0A;                   //STM32�����ַ, ������������   
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;                 //ʹ��ACK�ź�  
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;   //ָ��7λ��ַ  
    I2C_InitStructure.I2C_ClockSpeed = 100000;                  //ʱ��Ƶ�ʣ�����С�ڵ���400KHz  
      
    I2C_Cmd( I2C1, ENABLE );                                    //ʹ��IIC1 
    I2C_Init( I2C1, &I2C_InitStructure );                       //����IIC��ʼ���ṹ���ʼ��IIC1  
      
    /*����һ�ֽ�һӦ��ģʽ*/  
    I2C_AcknowledgeConfig( I2C1, ENABLE );                      //ʹ��IIC1Ӧ��״̬    
}



void I2C1_Read_Tmp(uint16_t *temp)
{
	//while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)); //��������Ƿ�æ ���ǿ� SCL ��SDA�Ƿ�Ϊ �� 
	//uint8_t i;
	float temperature;
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);  //����1�ֽ�1Ӧ��ģʽ
	
	I2C_GenerateSTART(I2C1, ENABLE);  // ������ʼλ 
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)); //EV5,��ģʽ
	
	I2C_Send7bitAddress(I2C1, 0x80, I2C_Direction_Transmitter);  //����������ַ(д) ����ĵ�ַ�������ֲ��ϵõ��ģ�Ҫ����һλ��
																															 //0x40->0x80, ��ַ��7bit���������ں��������ǰ�油0��8bit�� 
	
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	I2C_SendData(I2C1, 0xe3);  //����Measure Temperature Command
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //�����ѷ���
	
	I2C_GenerateSTART(I2C1, ENABLE);  //��ʼλ
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C1, 0x80, I2C_Direction_Receiver);  //����������ַ(��)
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	//��Temperature Register
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)); /* EV7 */ 
	temp[0]= I2C_ReceiveData(I2C1);
	//printf("temp[0]: %2x", temp[0]);
	temp[0] = temp[0] << 8;
	
	
	
	I2C_AcknowledgeConfig(I2C1, DISABLE); //���һλ��Ҫ�ر�Ӧ��� 
	I2C_GenerateSTOP(I2C1, ENABLE); //����ֹͣλ
	
	/*
	�� Ϊ�����յ����һ���ֽں����һ��NACK���壬�ڶ������ڶ��������ֽ�֮��(�ڵ����ڶ���RxNE�¼�֮��)�������ACKλ�� 
	�� Ϊ�˲���һ��ֹͣ/����ʼ��������������ڶ������ڶ��������ֽ�֮��(�ڵ����ڶ���RxNE�¼�֮��)����STOP/STARTλ�� 
	�� ֻ����һ���ֽ�ʱ���պ���EV6֮��(EV6_1ʱ�����ADDR֮��)Ҫ�ر�Ӧ���ֹͣ�����Ĳ���λ��
	*/
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)); /* EV7 */ 
	temp[1]= I2C_ReceiveData(I2C1);
	
	temperature = (temp[0]+temp[1])*175.72/65536-46.85;
	
	//for(i=0; i<2; i++)
	printf("\r\n Si7051: %.2f \r\n", temperature);
	
	//Decrement the read bytes counter 
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);  //�ٴ�����Ӧ��ģʽ
}

float Return_7051_Tmp(void)
{
	//while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)); //��������Ƿ�æ ���ǿ� SCL ��SDA�Ƿ�Ϊ �� 
	//uint8_t i;
	float temperature;
	uint16_t temp[2];
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);  //����1�ֽ�1Ӧ��ģʽ
	
	I2C_GenerateSTART(I2C1, ENABLE);  // ������ʼλ 
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)); //EV5,��ģʽ
	
	I2C_Send7bitAddress(I2C1, 0x80, I2C_Direction_Transmitter);  //����������ַ(д) ����ĵ�ַ�������ֲ��ϵõ��ģ�Ҫ����һλ��
																															 //0x40->0x80, ��ַ��7bit���������ں��������ǰ�油0��8bit�� 
	
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	I2C_SendData(I2C1, 0xe3);  //����Measure Temperature Command
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //�����ѷ���
	
	I2C_GenerateSTART(I2C1, ENABLE);  //��ʼλ
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C1, 0x80, I2C_Direction_Receiver);  //����������ַ(��)
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	//��Temperature Register
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)); /* EV7 */ 
	temp[0]= I2C_ReceiveData(I2C1);
	//printf("temp[0]: %2x", temp[0]);
	temp[0] = temp[0] << 8;
	
	
	
	I2C_AcknowledgeConfig(I2C1, DISABLE); //���һλ��Ҫ�ر�Ӧ��� 
	I2C_GenerateSTOP(I2C1, ENABLE); //����ֹͣλ
	
	/*
	�� Ϊ�����յ����һ���ֽں����һ��NACK���壬�ڶ������ڶ��������ֽ�֮��(�ڵ����ڶ���RxNE�¼�֮��)�������ACKλ�� 
	�� Ϊ�˲���һ��ֹͣ/����ʼ��������������ڶ������ڶ��������ֽ�֮��(�ڵ����ڶ���RxNE�¼�֮��)����STOP/STARTλ�� 
	�� ֻ����һ���ֽ�ʱ���պ���EV6֮��(EV6_1ʱ�����ADDR֮��)Ҫ�ر�Ӧ���ֹͣ�����Ĳ���λ��
	*/
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)); /* EV7 */ 
	temp[1]= I2C_ReceiveData(I2C1);
	
	temperature = (temp[0]+temp[1])*175.72/65536-46.85;
	
	
	return temperature;
	//for(i=0; i<2; i++)
	//printf("\r\n Si7051: %.2f \r\n", temperature);
	
	//Decrement the read bytes counter 
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);  //�ٴ�����Ӧ��ģʽ
}


void I2C1_Read_Tmp_7(uint16_t *temp, float *temperature)
{
	//while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)); //��������Ƿ�æ ���ǿ� SCL ��SDA�Ƿ�Ϊ �� 
	//uint8_t i;
	//float temperature;
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);  //����1�ֽ�1Ӧ��ģʽ
	
	I2C_GenerateSTART(I2C1, ENABLE);  // ������ʼλ 
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)); //EV5,��ģʽ
	
	I2C_Send7bitAddress(I2C1, 0x80, I2C_Direction_Transmitter);  //����������ַ(д) ����ĵ�ַ�������ֲ��ϵõ��ģ�Ҫ����һλ��
																															 //0x40->0x80, ��ַ��7bit���������ں��������ǰ�油0��8bit�� 
	
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	I2C_SendData(I2C1, 0xe3);  //����Measure Temperature Command
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //�����ѷ���
	
	I2C_GenerateSTART(I2C1, ENABLE);  //��ʼλ
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C1, 0x80, I2C_Direction_Receiver);  //����������ַ(��)
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	//��Temperature Register
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)); /* EV7 */ 
	temp[0]= I2C_ReceiveData(I2C1);
	//printf("temp[0]: %2x", temp[0]);
	temp[0] = temp[0] << 8;
	
	
	
	I2C_AcknowledgeConfig(I2C1, DISABLE); //���һλ��Ҫ�ر�Ӧ��� 
	I2C_GenerateSTOP(I2C1, ENABLE); //����ֹͣλ
	
	/*
	�� Ϊ�����յ����һ���ֽں����һ��NACK���壬�ڶ������ڶ��������ֽ�֮��(�ڵ����ڶ���RxNE�¼�֮��)�������ACKλ�� 
	�� Ϊ�˲���һ��ֹͣ/����ʼ��������������ڶ������ڶ��������ֽ�֮��(�ڵ����ڶ���RxNE�¼�֮��)����STOP/STARTλ�� 
	�� ֻ����һ���ֽ�ʱ���պ���EV6֮��(EV6_1ʱ�����ADDR֮��)Ҫ�ر�Ӧ���ֹͣ�����Ĳ���λ��
	*/
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)); /* EV7 */ 
	temp[1]= I2C_ReceiveData(I2C1);
	
	temperature[0] = (temp[0]+temp[1])*175.72/65536-46.85;
	
	//for(i=0; i<2; i++)
	printf("\r\n Si7051: %.2f \r\n", temperature[0]);
	
	//Decrement the read bytes counter 
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);  //�ٴ�����Ӧ��ģʽ
}

void I2C1_Read_Tmp_47(uint16_t *temp, float *temperature)
{
	//while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)); //��������Ƿ�æ ���ǿ� SCL ��SDA�Ƿ�Ϊ �� 
	//uint8_t i;
	//float temperature;
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);  //����1�ֽ�1Ӧ��ģʽ
	
	I2C_GenerateSTART(I2C1, ENABLE);  // ������ʼλ 
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)); //EV5,��ģʽ
	
	I2C_Send7bitAddress(I2C1, 0x80, I2C_Direction_Transmitter);  //����������ַ(д) ����ĵ�ַ�������ֲ��ϵõ��ģ�Ҫ����һλ��
																															 //0x40->0x80, ��ַ��7bit���������ں��������ǰ�油0��8bit�� 
	
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	I2C_SendData(I2C1, 0xe3);  //����Measure Temperature Command
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //�����ѷ���
	
	I2C_GenerateSTART(I2C1, ENABLE);  //��ʼλ
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C1, 0x80, I2C_Direction_Receiver);  //����������ַ(��)
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	//��Temperature Register
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)); /* EV7 */ 
	temp[0]= I2C_ReceiveData(I2C1);
	//printf("temp[0]: %2x", temp[0]);
	temp[0] = temp[0] << 8;
	
	
	
	I2C_AcknowledgeConfig(I2C1, DISABLE); //���һλ��Ҫ�ر�Ӧ��� 
	I2C_GenerateSTOP(I2C1, ENABLE); //����ֹͣλ
	
	/*
	�� Ϊ�����յ����һ���ֽں����һ��NACK���壬�ڶ������ڶ��������ֽ�֮��(�ڵ����ڶ���RxNE�¼�֮��)�������ACKλ�� 
	�� Ϊ�˲���һ��ֹͣ/����ʼ��������������ڶ������ڶ��������ֽ�֮��(�ڵ����ڶ���RxNE�¼�֮��)����STOP/STARTλ�� 
	�� ֻ����һ���ֽ�ʱ���պ���EV6֮��(EV6_1ʱ�����ADDR֮��)Ҫ�ر�Ӧ���ֹͣ�����Ĳ���λ��
	*/
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)); /* EV7 */ 
	temp[1]= I2C_ReceiveData(I2C1);
	
	temperature[1] = (temp[0]+temp[1])*175.72/65536-46.85;
	
	//for(i=0; i<2; i++)
	printf("\r\n Si7051: %.2f \r\n", temperature[1]);
	
	//Decrement the read bytes counter 
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);  //�ٴ�����Ӧ��ģʽ
}


void I2C1_7051_Test(uint8_t *temp)
{
	//while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)); //��������Ƿ�æ ���ǿ� SCL ��SDA�Ƿ�Ϊ �� 
	uint8_t i;
	
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);  //����1�ֽ�1Ӧ��ģʽ
	
	I2C_GenerateSTART(I2C1, ENABLE);  // ������ʼλ 
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)); //EV5,��ģʽ
	
	I2C_Send7bitAddress(I2C1, 0x80, I2C_Direction_Transmitter);  //����������ַ(д)
	
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	//I2C_SendData(I2C1, 0xe3);  //����Measure Temperature Command
	//while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //�����ѷ���
	I2C_SendData(I2C1, 0xfc);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //�����ѷ���
	I2C_SendData(I2C1, 0xc9);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //�����ѷ���
	
	I2C_GenerateSTART(I2C1, ENABLE);  //��ʼλ
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C1, 0x80, I2C_Direction_Receiver);  //����������ַ(��)
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	//��Temperature Register
	for(i=0; i<8; i++) {
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)); /* EV7 */ 
		temp[i]= I2C_ReceiveData(I2C1);
	}
	
	for(i=0; i<8; i++)
		printf("temp[%d]: %2x", i, temp[i]);
	
	I2C_AcknowledgeConfig(I2C1, DISABLE); //���һλ��Ҫ�ر�Ӧ��� 
	I2C_GenerateSTOP(I2C1, ENABLE); //����ֹͣλ
	
	/*
	�� Ϊ�����յ����һ���ֽں����һ��NACK���壬�ڶ������ڶ��������ֽ�֮��(�ڵ����ڶ���RxNE�¼�֮��)�������ACKλ�� 
	�� Ϊ�˲���һ��ֹͣ/����ʼ��������������ڶ������ڶ��������ֽ�֮��(�ڵ����ڶ���RxNE�¼�֮��)����STOP/STARTλ�� 
	�� ֻ����һ���ֽ�ʱ���պ���EV6֮��(EV6_1ʱ�����ADDR֮��)Ҫ�ر�Ӧ���ֹͣ�����Ĳ���λ��
	*/
	
	//while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)); //EV7  
	//temp[1]= I2C_ReceiveData(I2C1);
	
	//printf("temp[1]: %2x", temp[1]);
	
	//Decrement the read bytes counter 
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);  //�ٴ�����Ӧ��ģʽ
} 



//*****************************************************  
// IIC2��ʼ����������ʼ��STM32Ӳ���Դ���IIC2  
//                 IIC2_SCL��ӦGPIO.B10  
//                 IIC2_SDA��ӦGPIO.B11  
//*****************************************************  
void I2C2_Init(void)  
{  
    /*GPIO��IIC��ʼ���ṹ��*/  
    GPIO_InitTypeDef GPIO_InitStructure;  
    I2C_InitTypeDef I2C_InitStructure;  
      
    /*GPIO��IICʱ��ʹ��*/  
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );     //GPIOBʱ��ʹ��  
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C2, ENABLE );      //IIC2ʱ��ʹ��  
  
    /*��ʼ��GPIO*/  
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10 | GPIO_Pin_11;   //��ʼ��GPIO.B10(IIC2_SCL)��GPIO.B11(IIC2_SDA)  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;           //�������ٶ�50Hz  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;             //�������ģʽΪ���ù��ܿ�©���  
    GPIO_Init( GPIOB, &GPIO_InitStructure );                    //����GPIO��ʼ���ṹ���ʼ��GPIOB  
      
    /*��ʼ��IIC2*/  
    I2C_DeInit(I2C2);
		I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;                  //����ΪIICģʽ  
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;          //����IIC��ռ�ձȣ��͵�ƽ���Ըߵ�ƽֵΪ2  
    I2C_InitStructure.I2C_OwnAddress1 = 0x0A;                   //STM32�����ַ, ������������  
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;                 //ʹ��ACK�ź�  
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;   //ָ��7λ��ַ  
    I2C_InitStructure.I2C_ClockSpeed = 100000;                  //ʱ��Ƶ�ʣ�����С�ڵ���400KHz  
      
    I2C_Cmd( I2C2, ENABLE );                                    //ʹ��IIC2  
    I2C_Init(I2C2, &I2C_InitStructure);                       //����IIC��ʼ���ṹ���ʼ��IIC2  
      
    /*����һ�ֽ�һӦ��ģʽ*/  
    I2C_AcknowledgeConfig( I2C2, ENABLE );                      //ʹ��IIC2Ӧ��״̬    
}
 

//void I2C2_Read_Tmp(uint16_t *temp, uint8_t index)
//{
//	uint8_t sign;
//	uint8_t integer;
//	float deci;
//	
//	uint8_t data;
//	float temperature;
//	
//	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY)); //��������Ƿ�æ ���ǿ� SCL ��SDA�Ƿ�Ϊ �� 
//	
//	I2C_AcknowledgeConfig(I2C2, ENABLE);  //����1�ֽ�1Ӧ��ģʽ
//	
//	I2C_GenerateSTART(I2C2, ENABLE);  // ������ʼλ 
//	
//	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT)); //EV5,��ģʽ
//	
//	if(index == 0)
//		I2C_Send7bitAddress(I2C2, 0x90, I2C_Direction_Transmitter);  //����������ַ(д)
//	else if(index == 1)
//		I2C_Send7bitAddress(I2C2, 0x92, I2C_Direction_Transmitter);  //����������ַ(д)
//	
//	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
//	
//	I2C_SendData(I2C2, 0x00);  //����Pointer Register
//	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //�����ѷ���
//	
//	I2C_GenerateSTART(I2C2, ENABLE);  //��ʼλ
//	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
//	
//	if(index == 0)
//		I2C_Send7bitAddress(I2C2, 0x90, I2C_Direction_Receiver);  //����������ַ(��)
//	else if(index == 1)
//		I2C_Send7bitAddress(I2C2, 0x92, I2C_Direction_Receiver);  //����������ַ(��)
//	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
//	
//	//��Temperature Register
//	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED)); /* EV7 */ 
//	temp[0]= I2C_ReceiveData(I2C2);
//	
//	sign = temp[0] >> 7;
//	
//	//printf("\r\n");
//	//printf("TMP116 No.%d temp[0]: %2x\r\n", index, temp[0]);
//	
//	I2C_AcknowledgeConfig(I2C2, DISABLE); //���һλ��Ҫ�ر�Ӧ��� 
//	I2C_GenerateSTOP(I2C2, ENABLE); //����ֹͣλ
//	
//	/*
//	�� Ϊ�����յ����һ���ֽں����һ��NACK���壬�ڶ������ڶ��������ֽ�֮��(�ڵ����ڶ���RxNE�¼�֮��)�������ACKλ�� 
//	�� Ϊ�˲���һ��ֹͣ/����ʼ��������������ڶ������ڶ��������ֽ�֮��(�ڵ����ڶ���RxNE�¼�֮��)����STOP/STARTλ�� 
//	�� ֻ����һ���ֽ�ʱ���պ���EV6֮��(EV6_1ʱ�����ADDR֮��)Ҫ�ر�Ӧ���ֹͣ�����Ĳ���λ��
//	*/
//	
//	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED)); //EV7  
//	temp[1]= I2C_ReceiveData(I2C2);
//	
//	

//	//printf("TMP116 No.%d temp[1]: %2x\r\n", index, temp[1]);
//	//printf("\r\n");
//	
//	temp[0] = temp[0] << 1;
//	data = temp[1] >> 7;
//	integer = temp[0] + data;
//	
//	if(sign == 1 && integer > 0)
//		integer = (integer^255) + 1;
//	
//	if(sign == 0)
//		deci = ((temp[1] << 1) >> 1) * 0.0078125;
//	else if(sign == 1)
//		deci = (((temp[1] << 1) >> 1)^255 + 1) * 0.0078125;
//	
//	temperature = integer + deci;
//	
//	if(sign == 1)
//		temperature = temperature * -1;
//	//printf("TMP116 No.%d temp int: %d\r\n", index, integer);
//	
//	//Decrement the read bytes counter 
//	
//	printf("\r\n temperature read from TMP116 No. %d: %.2f \r\n", index, temperature);
//	
//	I2C_AcknowledgeConfig(I2C2, ENABLE);  //�ٴ�����Ӧ��ģʽ
//} 


void I2C2_Read_SHT30(uint16_t *temp, uint8_t index)
{
	uint8_t sign;
	uint8_t integer;
	float deci;
	
	uint8_t data;
	float temperature;
	uint32_t tem,hum;
	float tem_res, hum_res;
	
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY)); //��������Ƿ�æ ���ǿ� SCL ��SDA�Ƿ�Ϊ �� 
	
	I2C_AcknowledgeConfig(I2C2, ENABLE);  //����1�ֽ�1Ӧ��ģʽ
	
	I2C_GenerateSTART(I2C2, ENABLE);  // ������ʼλ 
	
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT)); //EV5,��ģʽ
	
	if(index == 0)
		I2C_Send7bitAddress(I2C2, 0x8a, I2C_Direction_Transmitter);  //����������ַ(д)
	else if(index == 1)
		I2C_Send7bitAddress(I2C2, 0x8a, I2C_Direction_Transmitter);  //����������ַ(д)
	
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	I2C_SendData(I2C2, 0x2c);  //����Pointer Register
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //�����ѷ���
	I2C_SendData(I2C2, 0x06);  //����Pointer Register
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //�����ѷ���
	
	
	I2C_GenerateSTART(I2C2, ENABLE);  //��ʼλ
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
	
	if(index == 0)
		I2C_Send7bitAddress(I2C2, 0x8a, I2C_Direction_Receiver);  //����������ַ(��)
	else if(index == 1)
		I2C_Send7bitAddress(I2C2, 0x8a, I2C_Direction_Receiver);  //����������ַ(��)
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	//��Temperature Register
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED)); /* EV7 */ 
	temp[0]= I2C_ReceiveData(I2C2);
	
	printf("\r\n");
	printf("SHT30 byte0: %2x\r\n", temp[0]);
	
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED)); /* EV7 */ 
	temp[1]= I2C_ReceiveData(I2C2);
	
	printf("\r\n");
	printf("SHT30 byte1: %2x\r\n", temp[1]);
	
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED)); /* EV7 */ 
	temp[2]= I2C_ReceiveData(I2C2);
	
	printf("\r\n");
	printf("SHT30 byte2: %2x\r\n", temp[2]);
	
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED)); /* EV7 */ 
	temp[3]= I2C_ReceiveData(I2C2);
	
	printf("\r\n");
	printf("SHT30 byte3: %2x\r\n", temp[3]);
	
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED)); /* EV7 */ 
	temp[4]= I2C_ReceiveData(I2C2);
	
	printf("\r\n");
	printf("SHT30 byte4: %2x\r\n", temp[4]);
	
	
	I2C_AcknowledgeConfig(I2C2, DISABLE); //���һλ��Ҫ�ر�Ӧ��� 
	I2C_GenerateSTOP(I2C2, ENABLE); //����ֹͣλ
	
	/*
	�� Ϊ�����յ����һ���ֽں����һ��NACK���壬�ڶ������ڶ��������ֽ�֮��(�ڵ����ڶ���RxNE�¼�֮��)�������ACKλ�� 
	�� Ϊ�˲���һ��ֹͣ/����ʼ��������������ڶ������ڶ��������ֽ�֮��(�ڵ����ڶ���RxNE�¼�֮��)����STOP/STARTλ�� 
	�� ֻ����һ���ֽ�ʱ���պ���EV6֮��(EV6_1ʱ�����ADDR֮��)Ҫ�ر�Ӧ���ֹͣ�����Ĳ���λ��
	*/
	
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED)); //EV7  
	temp[5]= I2C_ReceiveData(I2C2);
	
	

	printf("\r\n");
	printf("SHT30 byte5: %2x\r\n", temp[5]);
	printf("\r\n");
	
	
  tem = (temp[0]<<8) | temp[1];
  hum = (temp[3]<<8) | temp[4];
  
	tem_res = (175.0 * tem)/65535 - 45;
	hum_res = 100.0 * hum / 65535;
	tem = ((21875 * tem) >> 13) - 45000;
  hum = ((12500 * hum) >> 13);
	
	//printf("\r\n Temp: %d\r\n", tem);
	//printf("\r\n Humi: %d\r\n", hum);
	
	printf("\r\n Temp: %f\r\n", tem_res);
	printf("\r\n Humi: %f\r\n", hum_res);
	
	printf("\r\n");
	
	I2C_AcknowledgeConfig(I2C2, ENABLE);  //�ٴ�����Ӧ��ģʽ
}


void I2C2_Read_SHT30_2(uint16_t *temp, uint8_t index)
{
	uint8_t sign;
	uint8_t integer;
	float deci;
	
	uint8_t data;
	float temperature;
	uint32_t tem,hum;
 	float tem_res, hum_res;
	
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY)); //��������Ƿ�æ ���ǿ� SCL ��SDA�Ƿ�Ϊ �� 
	
	I2C_AcknowledgeConfig(I2C2, ENABLE);  //����1�ֽ�1Ӧ��ģʽ
	
	I2C_GenerateSTART(I2C2, ENABLE);  // ������ʼλ 
	
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT)); //EV5,��ģʽ
	
	if(index == 0)
		I2C_Send7bitAddress(I2C2, 0x8a, I2C_Direction_Transmitter);  //����������ַ(д)
	else if(index == 1)
		I2C_Send7bitAddress(I2C2, 0x8a, I2C_Direction_Transmitter);  //����������ַ(д)
	
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	I2C_SendData(I2C2, 0x21);  //����Pointer Register
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //�����ѷ���
	I2C_SendData(I2C2, 0x30);  //����Pointer Register
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //�����ѷ���
	
	I2C_AcknowledgeConfig(I2C2, ENABLE);  //�ٴ�����Ӧ��ģʽ
}

/************************************************* 

**������:void I2C_InitTmp(uint8_t index) 
**����:��ʼ��TMP116 

*************************************************/

void I2C2_Init_Tmp(uint8_t index)
{
	I2C_GenerateSTART(I2C2, ENABLE); 
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
	
	if(index == 0)
		I2C_Send7bitAddress(I2C2, 0x90, I2C_Direction_Transmitter);  //����������ַ(д)
	else if(index == 1)
		I2C_Send7bitAddress(I2C2, 0x92, I2C_Direction_Transmitter);  //����������ַ(д)
	
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	I2C_SendData(I2C2, 0x01);  //����Pointer Register
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_SendData(I2C2, 0xFE);  //дConfiguration Register �߰�λ
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_SendData(I2C2, 0xFE);  //дConfiguration Register �Ͱ�λ
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_GenerateSTOP(I2C2, ENABLE);
} 
 
 
/*********************************************END OF FILE**********************/
