/*******************************************************************************/
  
#include "bsp_iic.h"
#include "stm32f10x_i2c.h"


uint8_t I2c_Buf[3] = "AB0"; //温度存放

//*****************************************************  
// IIC2初始化函数：初始化STM32硬件自带的IIC1  
//                 IIC1_SCL对应GPIO.B6  
//                 IIC1_SDA对应GPIO.B7  
//*****************************************************  
void I2C1_Init(void)  
{  
    /*GPIO与IIC初始化结构体*/  
    GPIO_InitTypeDef GPIO_InitStructure;  
    I2C_InitTypeDef I2C_InitStructure;  
      
    /*GPIO与IIC时钟使能*/  
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );     //GPIOB时钟使能  
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C1, ENABLE );      //IIC2时钟使能  
  
    /*初始化GPIO*/  
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;     //初始化GPIO.B6(IIC2_SCL)，GPIO.B7(IIC2_SDA)  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;           //最高输出速度50Hz  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;             //输入输出模式为复用功能开漏输出  
    GPIO_Init( GPIOB, &GPIO_InitStructure );                    //根据GPIO初始化结构体初始化GPIOB  
      
    /*初始化IIC1*/
		I2C_DeInit(I2C1);
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;                  //设置为IIC模式  
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;          //设置IIC的占空比，低电平除以高电平值为2  
    I2C_InitStructure.I2C_OwnAddress1 = 0x0A;                   //STM32自身地址, 主机不需设置   
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;                 //使能ACK信号  
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;   //指定7位地址  
    I2C_InitStructure.I2C_ClockSpeed = 100000;                  //时钟频率，必须小于等于400KHz  
      
    I2C_Cmd( I2C1, ENABLE );                                    //使能IIC1 
    I2C_Init( I2C1, &I2C_InitStructure );                       //根据IIC初始化结构体初始化IIC1  
      
    /*允许一字节一应答模式*/  
    I2C_AcknowledgeConfig( I2C1, ENABLE );                      //使能IIC1应答状态    
}



void I2C1_Read_Tmp(uint16_t *temp)
{
	//while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)); //检测总线是否忙 就是看 SCL 或SDA是否为 低 
	//uint8_t i;
	float temperature;
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);  //允许1字节1应答模式
	
	I2C_GenerateSTART(I2C1, ENABLE);  // 发送起始位 
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)); //EV5,主模式
	
	I2C_Send7bitAddress(I2C1, 0x80, I2C_Direction_Transmitter);  //发送器件地址(写) 传输的地址（数据手册上得到的）要左移一位，
																															 //0x40->0x80, 地址是7bit，但必须在后面而不是前面补0到8bit。 
	
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	I2C_SendData(I2C1, 0xe3);  //发送Measure Temperature Command
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //数据已发送
	
	I2C_GenerateSTART(I2C1, ENABLE);  //起始位
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C1, 0x80, I2C_Direction_Receiver);  //发送器件地址(读)
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	//读Temperature Register
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)); /* EV7 */ 
	temp[0]= I2C_ReceiveData(I2C1);
	//printf("temp[0]: %2x", temp[0]);
	temp[0] = temp[0] << 8;
	
	
	
	I2C_AcknowledgeConfig(I2C1, DISABLE); //最后一位后要关闭应答的 
	I2C_GenerateSTOP(I2C1, ENABLE); //发送停止位
	
	/*
	● 为了在收到最后一个字节后产生一个NACK脉冲，在读倒数第二个数据字节之后(在倒数第二个RxNE事件之后)必须清除ACK位。 
	● 为了产生一个停止/重起始条件，软件必须在读倒数第二个数据字节之后(在倒数第二个RxNE事件之后)设置STOP/START位。 
	● 只接收一个字节时，刚好在EV6之后(EV6_1时，清除ADDR之后)要关闭应答和停止条件的产生位。
	*/
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)); /* EV7 */ 
	temp[1]= I2C_ReceiveData(I2C1);
	
	temperature = (temp[0]+temp[1])*175.72/65536-46.85;
	
	//for(i=0; i<2; i++)
	printf("\r\n Si7051: %.2f \r\n", temperature);
	
	//Decrement the read bytes counter 
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);  //再次允许应答模式
}

float Return_7051_Tmp(void)
{
	//while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)); //检测总线是否忙 就是看 SCL 或SDA是否为 低 
	//uint8_t i;
	float temperature;
	uint16_t temp[2];
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);  //允许1字节1应答模式
	
	I2C_GenerateSTART(I2C1, ENABLE);  // 发送起始位 
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)); //EV5,主模式
	
	I2C_Send7bitAddress(I2C1, 0x80, I2C_Direction_Transmitter);  //发送器件地址(写) 传输的地址（数据手册上得到的）要左移一位，
																															 //0x40->0x80, 地址是7bit，但必须在后面而不是前面补0到8bit。 
	
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	I2C_SendData(I2C1, 0xe3);  //发送Measure Temperature Command
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //数据已发送
	
	I2C_GenerateSTART(I2C1, ENABLE);  //起始位
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C1, 0x80, I2C_Direction_Receiver);  //发送器件地址(读)
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	//读Temperature Register
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)); /* EV7 */ 
	temp[0]= I2C_ReceiveData(I2C1);
	//printf("temp[0]: %2x", temp[0]);
	temp[0] = temp[0] << 8;
	
	
	
	I2C_AcknowledgeConfig(I2C1, DISABLE); //最后一位后要关闭应答的 
	I2C_GenerateSTOP(I2C1, ENABLE); //发送停止位
	
	/*
	● 为了在收到最后一个字节后产生一个NACK脉冲，在读倒数第二个数据字节之后(在倒数第二个RxNE事件之后)必须清除ACK位。 
	● 为了产生一个停止/重起始条件，软件必须在读倒数第二个数据字节之后(在倒数第二个RxNE事件之后)设置STOP/START位。 
	● 只接收一个字节时，刚好在EV6之后(EV6_1时，清除ADDR之后)要关闭应答和停止条件的产生位。
	*/
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)); /* EV7 */ 
	temp[1]= I2C_ReceiveData(I2C1);
	
	temperature = (temp[0]+temp[1])*175.72/65536-46.85;
	
	
	return temperature;
	//for(i=0; i<2; i++)
	//printf("\r\n Si7051: %.2f \r\n", temperature);
	
	//Decrement the read bytes counter 
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);  //再次允许应答模式
}


void I2C1_Read_Tmp_7(uint16_t *temp, float *temperature)
{
	//while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)); //检测总线是否忙 就是看 SCL 或SDA是否为 低 
	//uint8_t i;
	//float temperature;
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);  //允许1字节1应答模式
	
	I2C_GenerateSTART(I2C1, ENABLE);  // 发送起始位 
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)); //EV5,主模式
	
	I2C_Send7bitAddress(I2C1, 0x80, I2C_Direction_Transmitter);  //发送器件地址(写) 传输的地址（数据手册上得到的）要左移一位，
																															 //0x40->0x80, 地址是7bit，但必须在后面而不是前面补0到8bit。 
	
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	I2C_SendData(I2C1, 0xe3);  //发送Measure Temperature Command
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //数据已发送
	
	I2C_GenerateSTART(I2C1, ENABLE);  //起始位
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C1, 0x80, I2C_Direction_Receiver);  //发送器件地址(读)
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	//读Temperature Register
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)); /* EV7 */ 
	temp[0]= I2C_ReceiveData(I2C1);
	//printf("temp[0]: %2x", temp[0]);
	temp[0] = temp[0] << 8;
	
	
	
	I2C_AcknowledgeConfig(I2C1, DISABLE); //最后一位后要关闭应答的 
	I2C_GenerateSTOP(I2C1, ENABLE); //发送停止位
	
	/*
	● 为了在收到最后一个字节后产生一个NACK脉冲，在读倒数第二个数据字节之后(在倒数第二个RxNE事件之后)必须清除ACK位。 
	● 为了产生一个停止/重起始条件，软件必须在读倒数第二个数据字节之后(在倒数第二个RxNE事件之后)设置STOP/START位。 
	● 只接收一个字节时，刚好在EV6之后(EV6_1时，清除ADDR之后)要关闭应答和停止条件的产生位。
	*/
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)); /* EV7 */ 
	temp[1]= I2C_ReceiveData(I2C1);
	
	temperature[0] = (temp[0]+temp[1])*175.72/65536-46.85;
	
	//for(i=0; i<2; i++)
	printf("\r\n Si7051: %.2f \r\n", temperature[0]);
	
	//Decrement the read bytes counter 
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);  //再次允许应答模式
}

void I2C1_Read_Tmp_47(uint16_t *temp, float *temperature)
{
	//while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)); //检测总线是否忙 就是看 SCL 或SDA是否为 低 
	//uint8_t i;
	//float temperature;
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);  //允许1字节1应答模式
	
	I2C_GenerateSTART(I2C1, ENABLE);  // 发送起始位 
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)); //EV5,主模式
	
	I2C_Send7bitAddress(I2C1, 0x80, I2C_Direction_Transmitter);  //发送器件地址(写) 传输的地址（数据手册上得到的）要左移一位，
																															 //0x40->0x80, 地址是7bit，但必须在后面而不是前面补0到8bit。 
	
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	I2C_SendData(I2C1, 0xe3);  //发送Measure Temperature Command
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //数据已发送
	
	I2C_GenerateSTART(I2C1, ENABLE);  //起始位
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C1, 0x80, I2C_Direction_Receiver);  //发送器件地址(读)
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	//读Temperature Register
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)); /* EV7 */ 
	temp[0]= I2C_ReceiveData(I2C1);
	//printf("temp[0]: %2x", temp[0]);
	temp[0] = temp[0] << 8;
	
	
	
	I2C_AcknowledgeConfig(I2C1, DISABLE); //最后一位后要关闭应答的 
	I2C_GenerateSTOP(I2C1, ENABLE); //发送停止位
	
	/*
	● 为了在收到最后一个字节后产生一个NACK脉冲，在读倒数第二个数据字节之后(在倒数第二个RxNE事件之后)必须清除ACK位。 
	● 为了产生一个停止/重起始条件，软件必须在读倒数第二个数据字节之后(在倒数第二个RxNE事件之后)设置STOP/START位。 
	● 只接收一个字节时，刚好在EV6之后(EV6_1时，清除ADDR之后)要关闭应答和停止条件的产生位。
	*/
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)); /* EV7 */ 
	temp[1]= I2C_ReceiveData(I2C1);
	
	temperature[1] = (temp[0]+temp[1])*175.72/65536-46.85;
	
	//for(i=0; i<2; i++)
	printf("\r\n Si7051: %.2f \r\n", temperature[1]);
	
	//Decrement the read bytes counter 
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);  //再次允许应答模式
}


void I2C1_7051_Test(uint8_t *temp)
{
	//while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)); //检测总线是否忙 就是看 SCL 或SDA是否为 低 
	uint8_t i;
	
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);  //允许1字节1应答模式
	
	I2C_GenerateSTART(I2C1, ENABLE);  // 发送起始位 
	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)); //EV5,主模式
	
	I2C_Send7bitAddress(I2C1, 0x80, I2C_Direction_Transmitter);  //发送器件地址(写)
	
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	//I2C_SendData(I2C1, 0xe3);  //发送Measure Temperature Command
	//while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //数据已发送
	I2C_SendData(I2C1, 0xfc);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //数据已发送
	I2C_SendData(I2C1, 0xc9);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //数据已发送
	
	I2C_GenerateSTART(I2C1, ENABLE);  //起始位
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C1, 0x80, I2C_Direction_Receiver);  //发送器件地址(读)
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	//读Temperature Register
	for(i=0; i<8; i++) {
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)); /* EV7 */ 
		temp[i]= I2C_ReceiveData(I2C1);
	}
	
	for(i=0; i<8; i++)
		printf("temp[%d]: %2x", i, temp[i]);
	
	I2C_AcknowledgeConfig(I2C1, DISABLE); //最后一位后要关闭应答的 
	I2C_GenerateSTOP(I2C1, ENABLE); //发送停止位
	
	/*
	● 为了在收到最后一个字节后产生一个NACK脉冲，在读倒数第二个数据字节之后(在倒数第二个RxNE事件之后)必须清除ACK位。 
	● 为了产生一个停止/重起始条件，软件必须在读倒数第二个数据字节之后(在倒数第二个RxNE事件之后)设置STOP/START位。 
	● 只接收一个字节时，刚好在EV6之后(EV6_1时，清除ADDR之后)要关闭应答和停止条件的产生位。
	*/
	
	//while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)); //EV7  
	//temp[1]= I2C_ReceiveData(I2C1);
	
	//printf("temp[1]: %2x", temp[1]);
	
	//Decrement the read bytes counter 
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);  //再次允许应答模式
} 



//*****************************************************  
// IIC2初始化函数：初始化STM32硬件自带的IIC2  
//                 IIC2_SCL对应GPIO.B10  
//                 IIC2_SDA对应GPIO.B11  
//*****************************************************  
void I2C2_Init(void)  
{  
    /*GPIO与IIC初始化结构体*/  
    GPIO_InitTypeDef GPIO_InitStructure;  
    I2C_InitTypeDef I2C_InitStructure;  
      
    /*GPIO与IIC时钟使能*/  
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );     //GPIOB时钟使能  
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C2, ENABLE );      //IIC2时钟使能  
  
    /*初始化GPIO*/  
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10 | GPIO_Pin_11;   //初始化GPIO.B10(IIC2_SCL)，GPIO.B11(IIC2_SDA)  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;           //最高输出速度50Hz  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;             //输入输出模式为复用功能开漏输出  
    GPIO_Init( GPIOB, &GPIO_InitStructure );                    //根据GPIO初始化结构体初始化GPIOB  
      
    /*初始化IIC2*/  
    I2C_DeInit(I2C2);
		I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;                  //设置为IIC模式  
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;          //设置IIC的占空比，低电平除以高电平值为2  
    I2C_InitStructure.I2C_OwnAddress1 = 0x0A;                   //STM32自身地址, 主机不需设置  
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;                 //使能ACK信号  
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;   //指定7位地址  
    I2C_InitStructure.I2C_ClockSpeed = 100000;                  //时钟频率，必须小于等于400KHz  
      
    I2C_Cmd( I2C2, ENABLE );                                    //使能IIC2  
    I2C_Init(I2C2, &I2C_InitStructure);                       //根据IIC初始化结构体初始化IIC2  
      
    /*允许一字节一应答模式*/  
    I2C_AcknowledgeConfig( I2C2, ENABLE );                      //使能IIC2应答状态    
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
//	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY)); //检测总线是否忙 就是看 SCL 或SDA是否为 低 
//	
//	I2C_AcknowledgeConfig(I2C2, ENABLE);  //允许1字节1应答模式
//	
//	I2C_GenerateSTART(I2C2, ENABLE);  // 发送起始位 
//	
//	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT)); //EV5,主模式
//	
//	if(index == 0)
//		I2C_Send7bitAddress(I2C2, 0x90, I2C_Direction_Transmitter);  //发送器件地址(写)
//	else if(index == 1)
//		I2C_Send7bitAddress(I2C2, 0x92, I2C_Direction_Transmitter);  //发送器件地址(写)
//	
//	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
//	
//	I2C_SendData(I2C2, 0x00);  //发送Pointer Register
//	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //数据已发送
//	
//	I2C_GenerateSTART(I2C2, ENABLE);  //起始位
//	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
//	
//	if(index == 0)
//		I2C_Send7bitAddress(I2C2, 0x90, I2C_Direction_Receiver);  //发送器件地址(读)
//	else if(index == 1)
//		I2C_Send7bitAddress(I2C2, 0x92, I2C_Direction_Receiver);  //发送器件地址(读)
//	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
//	
//	//读Temperature Register
//	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED)); /* EV7 */ 
//	temp[0]= I2C_ReceiveData(I2C2);
//	
//	sign = temp[0] >> 7;
//	
//	//printf("\r\n");
//	//printf("TMP116 No.%d temp[0]: %2x\r\n", index, temp[0]);
//	
//	I2C_AcknowledgeConfig(I2C2, DISABLE); //最后一位后要关闭应答的 
//	I2C_GenerateSTOP(I2C2, ENABLE); //发送停止位
//	
//	/*
//	● 为了在收到最后一个字节后产生一个NACK脉冲，在读倒数第二个数据字节之后(在倒数第二个RxNE事件之后)必须清除ACK位。 
//	● 为了产生一个停止/重起始条件，软件必须在读倒数第二个数据字节之后(在倒数第二个RxNE事件之后)设置STOP/START位。 
//	● 只接收一个字节时，刚好在EV6之后(EV6_1时，清除ADDR之后)要关闭应答和停止条件的产生位。
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
//	I2C_AcknowledgeConfig(I2C2, ENABLE);  //再次允许应答模式
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
	
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY)); //检测总线是否忙 就是看 SCL 或SDA是否为 低 
	
	I2C_AcknowledgeConfig(I2C2, ENABLE);  //允许1字节1应答模式
	
	I2C_GenerateSTART(I2C2, ENABLE);  // 发送起始位 
	
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT)); //EV5,主模式
	
	if(index == 0)
		I2C_Send7bitAddress(I2C2, 0x8a, I2C_Direction_Transmitter);  //发送器件地址(写)
	else if(index == 1)
		I2C_Send7bitAddress(I2C2, 0x8a, I2C_Direction_Transmitter);  //发送器件地址(写)
	
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	I2C_SendData(I2C2, 0x2c);  //发送Pointer Register
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //数据已发送
	I2C_SendData(I2C2, 0x06);  //发送Pointer Register
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //数据已发送
	
	
	I2C_GenerateSTART(I2C2, ENABLE);  //起始位
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
	
	if(index == 0)
		I2C_Send7bitAddress(I2C2, 0x8a, I2C_Direction_Receiver);  //发送器件地址(读)
	else if(index == 1)
		I2C_Send7bitAddress(I2C2, 0x8a, I2C_Direction_Receiver);  //发送器件地址(读)
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	//读Temperature Register
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
	
	
	I2C_AcknowledgeConfig(I2C2, DISABLE); //最后一位后要关闭应答的 
	I2C_GenerateSTOP(I2C2, ENABLE); //发送停止位
	
	/*
	● 为了在收到最后一个字节后产生一个NACK脉冲，在读倒数第二个数据字节之后(在倒数第二个RxNE事件之后)必须清除ACK位。 
	● 为了产生一个停止/重起始条件，软件必须在读倒数第二个数据字节之后(在倒数第二个RxNE事件之后)设置STOP/START位。 
	● 只接收一个字节时，刚好在EV6之后(EV6_1时，清除ADDR之后)要关闭应答和停止条件的产生位。
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
	
	I2C_AcknowledgeConfig(I2C2, ENABLE);  //再次允许应答模式
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
	
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY)); //检测总线是否忙 就是看 SCL 或SDA是否为 低 
	
	I2C_AcknowledgeConfig(I2C2, ENABLE);  //允许1字节1应答模式
	
	I2C_GenerateSTART(I2C2, ENABLE);  // 发送起始位 
	
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT)); //EV5,主模式
	
	if(index == 0)
		I2C_Send7bitAddress(I2C2, 0x8a, I2C_Direction_Transmitter);  //发送器件地址(写)
	else if(index == 1)
		I2C_Send7bitAddress(I2C2, 0x8a, I2C_Direction_Transmitter);  //发送器件地址(写)
	
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	I2C_SendData(I2C2, 0x21);  //发送Pointer Register
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //数据已发送
	I2C_SendData(I2C2, 0x30);  //发送Pointer Register
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //数据已发送
	
	I2C_AcknowledgeConfig(I2C2, ENABLE);  //再次允许应答模式
}

/************************************************* 

**函数名:void I2C_InitTmp(uint8_t index) 
**功能:初始化TMP116 

*************************************************/

void I2C2_Init_Tmp(uint8_t index)
{
	I2C_GenerateSTART(I2C2, ENABLE); 
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
	
	if(index == 0)
		I2C_Send7bitAddress(I2C2, 0x90, I2C_Direction_Transmitter);  //发送器件地址(写)
	else if(index == 1)
		I2C_Send7bitAddress(I2C2, 0x92, I2C_Direction_Transmitter);  //发送器件地址(写)
	
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	I2C_SendData(I2C2, 0x01);  //发送Pointer Register
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_SendData(I2C2, 0xFE);  //写Configuration Register 高八位
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_SendData(I2C2, 0xFE);  //写Configuration Register 低八位
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_GenerateSTOP(I2C2, ENABLE);
} 
 
 
/*********************************************END OF FILE**********************/
