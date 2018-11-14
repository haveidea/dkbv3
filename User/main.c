#include <stdio.h>
#include "stm32f10x.h"
#include "bsp_SysTick.h"
#include "bsp_led.h"
#include "bsp_usart1.h"
#include "bsp_DS18B20.h"
#include "bsp_iic.h"

#include "stm32f10x_rtc.h"
#include "misc.h"

//#define SYSCLK_FREQ_24MHz

//uint8_t ID_Buff_IN2[MAXNUM_IN2][8];
int aa,bb;
			 
uint8_t ID_Buff[80][8];
uint8_t PARA_Buff[80][8];
uint8_t Scrpad_Buff[80][9];
uint8_t Scrpad_Ext_Buff[80][6];

//uint8_t ID_Buff_Save[80][8];

uint8_t TEMP_Buff[80][2];
float TEMP_TRANS_Buff[80][10];

float TEMP_TRANS_Buff_Calibre[80][2];

//float TEMP_TRANS_Buff_7[80][1];
//float TEMP_TRANS_Buff_47[80][1];
float TEMP_TRANS_Buff_27[80][1];

uint8_t TMP116_Buff[MAXNUM_SWITCH_18B20_OUT][2];
uint8_t SI7051_Buff[MAXNUM_SWITCH_18B20_OUT][2];

uint32_t temp_cal_res[80][1];
//static float temp_cal[80][2];
//static float temperature_7051[2];

uint8_t serial[8];
uint8_t serial_test[9];
uint8_t serial_rom[8] = {0x28,0x3a,0x47,0x74,0x08,0x00,0x00,0x07};



uint16_t temp[8];

uint8_t temp_hi[32];
uint8_t temp_lo[32];

float array[10];

float temp_call[2];
float temp_7051[2];
uint32_t temp_result[1];

extern u8 FUNC;
extern void MUX_Channel_SEL(uint8_t i);

extern uint32_t SystemCoreClock; 

uint8_t rom_num = 0;

uint8_t ROM_Buff[80][8] = {0x28,0x00,0x00,0x00,0x00,0xee,0xff,0xff};

//static float temp_cal[2];  //temp_cal[0] for point 7 and temp_cal[1] for point 47 

//static float temp_cal_res[2];  //temp_cal_res[0] for A and temp_cal_res[1] for B

uint8_t trim;
int i;



/*********************************Test Function Tasks End************************************************************/

//static const int *pcTextForTask1 = (int*)2;
//static const int *pcTextForTask2 = (int*)3;

void NVIC_Configuration(void)
{    
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Configure the NVIC Preemption Priority Bits */  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  
  /* Enable the USART1 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  //NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  
}



/**
  * @brief  main function
  * @param  N/A  
  * @retval N/A
  */
int main(void)
{ 

	SysTick_Init();/* configure SysTick */ 	
	USART1_Config();
	NVIC_Configuration();//USART1 receive interruption configure	
	GPIO_Config();
	I2C1_Init();
	I2C2_Init();
	
	//while(1) {
		//I2C2_Read_SHT30(temp, 0);
		//Delay_us(1000000);
	//}
	printf("\r*********Please Enter Command(Hex)*********\r\n");
					
	printf("\r\n Test All Commands:   \r%02x\n", 0x01);
	printf("\r\n Coeff Check:         \r%02x\n", 0x02);
	printf("\r\n ADC Delay mode and avg Check:         \r%02x\n", 0x03);
	printf("\r\n Temperature Read Test(12-bit):    \r%02x\r\n", 0x04);
	printf("\r\n Search ROM + FUNC Command Test: \r%02x\r\n", 0x05);   				
	printf("\r\n Back to Back Reset:  \r%02x\r\n", 0x06);
	
	printf("\r\n Open Power down (idle): \r%02x\r\n", 0x07);   				
	printf("\r\n Close Power down (idle):  \r%02x\r\n", 0x08);
	printf("\r\n Open Pulldown Power down: \r%02x\r\n", 0x09);   				
	printf("\r\n Close Pulldown Power down:  \r%02x\r\n", 0x0a);
	printf("\r\n Open ADC Average Mode: \r%02x\r\n", 0x0b);   				
	printf("\r\n Close ADC Average Mode:  \r%02x\r\n", 0x0c);
	printf("\r\n Open ADC Delay Mode: \r%02x\r\n", 0x0d);   				
	printf("\r\n Close ADC Delay Mode:  \r%02x\r\n", 0x0e);
	printf("\r\n ADC DR 512: \r%02x\r\n", 0x0f);   				
	printf("\r\n ADC DR 256:  \r%02x\r\n", 0x10);
	printf("\r\n Show System Parameters:  \r%02x\r\n", 0x11);
	printf("\r\n Search Device on Bus:  \r%02x\r\n", 0x12);
	printf("\r\n Recall All:  \r%02x\r\n", 0x13);
	printf("\r\n Temperature Read Test(14-bit):    \r%02x\r\n", 0x14);
	
	printf("\r**************************************\r\n");
		
	for(;;) {
		switch(FUNC) {
			case 0x00:
				printf("\r*********Please Enter Command(Hex)*********\r\n");	
				printf("\r\n Test All Commands:   \r%02x\n", 0x01);
				printf("\r\n Coeff Check:         \r%02x\n", 0x02);
				printf("\r\n ADC Delay mode and avg Check:         \r%02x\n", 0x03);
				printf("\r\n Temperature Read Test:    \r%02x\r\n", 0x04);
				printf("\r\n Search ROM + FUNC Command Test: \r%02x\r\n", 0x05);   				
				printf("\r\n Back to Back Reset:  \r%02x\r\n", 0x06);
			
				printf("\r\n Open Power down (idle): \r%02x\r\n", 0x07);   				
				printf("\r\n Close Power down (idle):  \r%02x\r\n", 0x08);
				printf("\r\n Open Pulldown Power down: \r%02x\r\n", 0x09);   				
				printf("\r\n Close Pulldown Power down:  \r%02x\r\n", 0x0a);
				printf("\r\n Open ADC Average Mode: \r%02x\r\n", 0x0b);   				
				printf("\r\n Close ADC Average Mode:  \r%02x\r\n", 0x0c);
				printf("\r\n Open ADC Delay Mode: \r%02x\r\n", 0x0d);   				
				printf("\r\n Close ADC Delay Mode:  \r%02x\r\n", 0x0e);
				printf("\r\n ADC DR 512: \r%02x\r\n", 0x0f);   				
				printf("\r\n ADC DR 256:  \r%02x\r\n", 0x10);
				printf("\r\n Show System Parameters:  \r%02x\r\n", 0x11);
				printf("\r\n Search Device on Bus:  \r%02x\r\n", 0x12);
				printf("\r\n Recall All:  \r%02x\r\n", 0x13);
				printf("\r\n Temperature Read Test(14-bit):    \r%02x\r\n", 0x14);
				printf("\r**************************************\r\n");
				FUNC = -1;
				break;
			case 0x01:
				Check_All_Basic_CMD();
				printf("\r\n Go back to main manu: 00\r\n");
				printf("********************************************\r\n\n");
				FUNC = -1;
				break;
			case 0x02:
				check_coeff_boundary();
				printf("\r\n Go back to main manu: 00\r\n");
				printf("********************************************\r\n\n");
				FUNC = -1;
				break;
			case 0x03:
				
				printf("\r\n Go back to main manu: 00\r\n");
				printf("********************************************\r\n\n");
				FUNC = -1;
				break;
			case 0x04:
				Check_Temperature_Code();
				printf("\r\n Go back to main manu: 00\r\n");
				printf("********************************************\r\n\n");
				FUNC = -1;
				break;
			case 0x05:
				Check_Search_follow_function();
				printf("\r\n Go back to main manu: 00\r\n");
				printf("********************************************\r\n\n");
				FUNC = -1;
				break;
			case 0x06:
				Check_Back_to_Back_Rst();
				printf("\r\n Go back to main manu: 00\r\n");
				printf("********************************************\r\n\n");
				FUNC = -1;
				break;
			case 0x07:
				open_powerdn();
			  printf("\r\nPower down mode (idle) opened.\r\n");
				printf("\r\n Go back to main manu: 00\r\n");
				printf("********************************************\r\n\n");
				FUNC = -1;
				break;
			case 0x08:
				close_powerdn();
				printf("\r\nPower down mode (idle) closed.\r\n");
				printf("\r\n Go back to main manu: 00\r\n");
				printf("********************************************\r\n\n");
				FUNC = -1;
				break;
			case 0x09:
				open_pulldown_powerdn();
				printf("\r\nPower down mode (pull down) opened.\r\n");
				printf("\r\n Go back to main manu: 00\r\n");
				printf("********************************************\r\n\n");
				FUNC = -1;
				break;
			case 0x0a:
				close_pulldown_powerdn();
				printf("\r\nPower down mode (pull down) closed.\r\n");
				printf("\r\n Go back to main manu: 00\r\n");
				printf("********************************************\r\n\n");
				FUNC = -1;
				break;
			case 0x0b:
				open_adc_avg();
				printf("\r\nADC average mode opened.\r\n");
				printf("\r\n Go back to main manu: 00\r\n");
				printf("********************************************\r\n\n");
				FUNC = -1;
				break;
			case 0x0c:
				close_adc_avg();
				printf("\r\nADC average mode closed.\r\n");
				printf("\r\n Go back to main manu: 00\r\n");
				printf("********************************************\r\n\n");
				FUNC = -1;
				break;
			case 0x0d:
				open_adc_delay();
				printf("\r\nADC delay mode opened.\r\n");
				printf("\r\n Go back to main manu: 00\r\n");
				printf("********************************************\r\n\n");
				FUNC = -1;
				break;
			case 0x0e:
				close_adc_delay();
				printf("\r\nADC delay mode closed.\r\n");
				printf("\r\n Go back to main manu: 00\r\n");
				printf("********************************************\r\n\n");
				FUNC = -1;
				break;
			case 0x0f:
				adc_dr_512();
				printf("\r\nADC DR 512 Set.\r\n");
				printf("\r\n Go back to main manu: 00\r\n");
				printf("********************************************\r\n\n");
				FUNC = -1;
				break;
			case 0x10:
				adc_dr_256();
				printf("\r\nADC DR 256 Set.\r\n");
				printf("\r\n Go back to main manu: 00\r\n");
				printf("********************************************\r\n\n");
				FUNC = -1;
				break;
			case 0x11:
				show_system_parameters();
				printf("\r\n Go back to main manu: 00\r\n");
				printf("********************************************\r\n\n");
				FUNC = -1;
				break;
			case 0x12:
				search_device_on_bus();
				printf("\r\n Go back to main manu: 00\r\n");
				printf("********************************************\r\n\n");
				FUNC = -1;
				break;
			case 0x13:
				DQ_Recall_EE(DUT_DQ_OUT);
				DQ_Recall_PAGE0_RES(DUT_DQ_OUT);
				DQ_Recall_PAGE1(DUT_DQ_OUT);
				printf("\r\nRecall All done.\r\n");
				printf("\r\n Go back to main manu: 00\r\n");
				printf("********************************************\r\n\n");
				FUNC = -1;
			  break;
			case 0x14:
				Check_Temperature_Code_14bit();
				printf("\r\n Go back to main manu: 00\r\n");
				printf("********************************************\r\n\n");
				FUNC = -1;
				break;
			default :
				
				break;
		}
	}
	
	
/////////////////////Test Area End/////////////////////////////////////////////
	
		
}



