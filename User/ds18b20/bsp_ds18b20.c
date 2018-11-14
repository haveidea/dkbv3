#include <stdio.h>
#include <math.h> 
#include <string.h>
#include <stdlib.h>   	//ZYL
#include "bsp_DS18B20.h"
#include "stm32f10x_tim.h"
#include "stm32f10x.h"
#include "misc.h"

#include "bsp_iic.h"




/*
 * FUNC: TOTAL_DQ_OUT_GPIO_Config
 * DESCRIP: TOTAL_DQ_OUT's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void TOTAL_DQ_OUT_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open DS18B20_IN3_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(TOTAL_DQ_OUT_CLK, ENABLE); 

	/*select DS18B20_IN3_PORT pin to control*/														   
  GPIO_InitStructure.GPIO_Pin = TOTAL_DQ_OUT_PIN;	

	#ifdef OD
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 
  #else
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	#endif   

	/*set pin speed to 50MHz */ 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial DS18B20_IN3_PORT*/
  	GPIO_Init(TOTAL_DQ_OUT_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(TOTAL_DQ_OUT_PORT, TOTAL_DQ_OUT_PIN);	 
}
/*
 * FUNC: DUT_DQ_OUT_GPIO_Config
 * DESCRIP: DUT_DQ_OUT's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void DUT_DQ_OUT_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open DUT_DQ_OUT_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(DUT_DQ_OUT_CLK, ENABLE); 

	/*select DUT_DQ_OUT_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = DUT_DQ_OUT_PIN;	

	/*set pin mode to push-pull out mode*/
  #ifdef OD
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 
  #else
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	#endif 	
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
		//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial DUT_DQ_OUT_PORT*/
  	GPIO_Init(DUT_DQ_OUT_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(DUT_DQ_OUT_PORT, DUT_DQ_OUT_PIN);	 
}

/*
 * FUNC: MUX_18B20_OUT_GPIO_Config
 * DESCRIP: MUX_18B20_OUT's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void MUX_18B20_OUT_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open DUT_DQ_OUT_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(MUX_18B20_OUT_CLK, ENABLE); 

	/*select DUT_DQ_OUT_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = MUX_18B20_OUT_PIN;	

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial DUT_DQ_OUT_PORT*/
  	GPIO_Init(MUX_18B20_OUT_PORT, &GPIO_InitStructure);
	
		GPIO_SetBits(MUX_18B20_OUT_PORT, MUX_18B20_OUT_PIN);	 
}

/*
 * FUNC: MUX_E5_GPIO_Config
 * DESCRIP: MUX_E5's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void MUX_E5_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_E5_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(MUX_E5_CLK, ENABLE); 

	/*select MUX_E5_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = MUX_E5_PIN;	

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_E5_PORT*/
  	GPIO_Init(MUX_E5_PORT, &GPIO_InitStructure);
	
		GPIO_SetBits(MUX_E5_PORT, MUX_E5_PIN);	 
}

/*
 * FUNC: MUX_E3_GPIO_Config
 * DESCRIP: MUX_E3's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void MUX_E3_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_E3_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(MUX_E3_CLK, ENABLE); 

	/*select MUX_E3_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = MUX_E3_PIN;	

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
		//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	
	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial SWITCH_18B20_OUT_PORT*/
  	GPIO_Init(MUX_E3_PORT, &GPIO_InitStructure);
	
		GPIO_SetBits(MUX_E3_PORT, MUX_E3_PIN);	 
}

/*
 * FUNC: STRONG_PULLUP_GPIO_Config
 * DESCRIP: STRONG_PULLUP's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void STRONG_PULLUP_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open STRONG_PULLUP_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(STRONG_PULLUP_CLK, ENABLE); 

	/*select STRONG_PULLUP_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = STRONG_PULLUP_PIN;	

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial STRONG_PULLUP_PORT*/
  	GPIO_Init(STRONG_PULLUP_PORT, &GPIO_InitStructure);
	
		GPIO_SetBits(STRONG_PULLUP_PORT, STRONG_PULLUP_PIN);	 
}

/*
 * FUNC: MUX_E1_GPIO_Config
 * DESCRIP: MUX_E1's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void MUX_E1_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_E1_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(MUX_E1_CLK, ENABLE); 

	/*select MUX_E1_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = MUX_E1_PIN;	

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_E1_PORT*/
  	GPIO_Init(MUX_E1_PORT, &GPIO_InitStructure);
	
		GPIO_SetBits(MUX_E1_PORT, MUX_E1_PIN);	 
}

/*
 * FUNC: MUX_E2_GPIO_Config
 * DESCRIP: MUX_E2's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void MUX_E2_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_E2_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(MUX_E2_CLK, ENABLE); 

	/*select MUX_E2_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = MUX_E2_PIN;	

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_E2_PORT*/
  	GPIO_Init(MUX_E2_PORT, &GPIO_InitStructure);
	
		GPIO_SetBits(MUX_E2_PORT, MUX_E2_PIN);	 
}

/*
 * FUNC: TEST_ADDR0_GPIO_Config
 * DESCRIP: TEST_ADDR0's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void TEST_ADDR0_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open TEST_ADDR0_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(TEST_ADDR0_CLK, ENABLE); 

	/*select TEST_ADDR0_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = TEST_ADDR0_PIN;	

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial TEST_ADDR0_PORT*/
  	GPIO_Init(TEST_ADDR0_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(TEST_ADDR0_PORT, TEST_ADDR0_PIN);	 
}

/*
 * FUNC: TEST_ADDR1_GPIO_Config
 * DESCRIP: TEST_ADDR1's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void TEST_ADDR1_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open TEST_ADDR1_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(TEST_ADDR1_CLK, ENABLE); 

	/*select TEST_ADDR1_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = TEST_ADDR1_PIN;	

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial TEST_ADDR1_PORT*/
  	GPIO_Init(TEST_ADDR1_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(TEST_ADDR1_PORT, TEST_ADDR1_PIN);	 
}

/*
 * FUNC: TEST_ADDR2_GPIO_Config
 * DESCRIP: TEST_ADDR2's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void TEST_ADDR2_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open TEST_ADDR2_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(TEST_ADDR2_CLK, ENABLE); 

	/*select TEST_ADDR2_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = TEST_ADDR2_PIN;	

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial TEST_ADDR2_PORT*/
  	GPIO_Init(TEST_ADDR2_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(TEST_ADDR2_PORT, TEST_ADDR2_PIN);	 
}

/*
 * FUNC: TEST_ADDR3_GPIO_Config
 * DESCRIP: TEST_ADDR3's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void TEST_ADDR3_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open TEST_ADDR3_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(TEST_ADDR3_CLK, ENABLE); 

	/*select TEST_ADDR3_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = TEST_ADDR3_PIN;	

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial TEST_ADDR3_PORT*/
  	GPIO_Init(TEST_ADDR3_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(TEST_ADDR3_PORT, TEST_ADDR3_PIN);	 
}

/*
 * FUNC: TEST_ADDR4_GPIO_Config
 * DESCRIP: TEST_ADDR4's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void TEST_ADDR4_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open TEST_ADDR4_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(TEST_ADDR4_CLK, ENABLE); 

	/*select TEST_ADDR4_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = TEST_ADDR4_PIN;	

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial TEST_ADDR4_PORT*/
  	GPIO_Init(TEST_ADDR4_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(TEST_ADDR4_PORT, TEST_ADDR4_PIN);	 
}

/*
 * FUNC: TEST_ADDR5_GPIO_Config
 * DESCRIP: TEST_ADDR5's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void TEST_ADDR5_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open TEST_ADDR5_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(TEST_ADDR5_CLK, ENABLE); 

	/*select TEST_ADDR5_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = TEST_ADDR5_PIN;	

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial TEST_ADDR5_PORT*/
  	GPIO_Init(TEST_ADDR5_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(TEST_ADDR5_PORT, TEST_ADDR5_PIN);	 
}

/*
 * FUNC: TEST_ADDR6_GPIO_Config
 * DESCRIP: TEST_ADDR6's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void TEST_ADDR6_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open TEST_ADDR6_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(TEST_ADDR6_CLK, ENABLE); 

	/*select TEST_ADDR6_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = TEST_ADDR6_PIN;	

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial TEST_ADDR6_PORT*/
  	GPIO_Init(TEST_ADDR6_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(TEST_ADDR6_PORT, TEST_ADDR6_PIN);	 
}

/*
 * FUNC: TEST_ADDR7_GPIO_Config
 * DESCRIP: TEST_ADDR7's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void TEST_ADDR7_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open TEST_ADDR7_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(TEST_ADDR7_CLK, ENABLE); 

	/*select TEST_ADDR7_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = TEST_ADDR7_PIN;	

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial TEST_ADDR7_PORT*/
  	GPIO_Init(TEST_ADDR7_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(TEST_ADDR7_PORT, TEST_ADDR7_PIN);	 
}

/*
 * FUNC: MUX_S3_GPIO_Config
 * DESCRIP: MUX_S3's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void MUX_S3_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_S3_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(MUX_S3_CLK, ENABLE); 

	/*select MUX_S3_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = MUX_S3_PIN;	

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_S3_PORT*/
  	GPIO_Init(MUX_S3_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(MUX_S3_PORT, MUX_S3_PIN);	 
}

/*
 * FUNC: MUX_S2_GPIO_Config
 * DESCRIP: MUX_S2's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void MUX_S2_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_S2_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(MUX_S2_CLK, ENABLE); 

	/*select MUX_S2_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = MUX_S2_PIN;	

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_S2_PORT*/
  	GPIO_Init(MUX_S2_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(MUX_S2_PORT, MUX_S2_PIN);	 
}

/*
 * FUNC: MUX_S1_GPIO_Config
 * DESCRIP: MUX_S1's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void MUX_S1_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_S1_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(MUX_S1_CLK, ENABLE); 

	/*select MUX_S1_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = MUX_S1_PIN;	

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_S1_PORT*/
  	GPIO_Init(MUX_S1_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(MUX_S1_PORT, MUX_S1_PIN);	 
}

/*
 * FUNC: MUX_S0_GPIO_Config
 * DESCRIP: MUX_S0's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void MUX_S0_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_S0_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(MUX_S0_CLK, ENABLE); 

	/*select MUX_S0_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = MUX_S0_PIN;	

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_S0_PORT*/
  	GPIO_Init(MUX_S0_PORT, &GPIO_InitStructure);
	
		GPIO_ResetBits(MUX_S0_PORT, MUX_S0_PIN);	 
}

/*
 * FUNC: MUX_E4_GPIO_Config
 * DESCRIP: MUX_E4's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void MUX_E4_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open MUX_E4_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(MUX_E4_CLK, ENABLE); 

	/*select MUX_E4_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = MUX_E4_PIN;	

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial MUX_E4_PORT*/
  	GPIO_Init(MUX_E4_PORT, &GPIO_InitStructure);
	
		GPIO_SetBits(MUX_E4_PORT, MUX_E4_PIN);	 
}

/*
 * FUNC: TEST_DATA0_GPIO_Config
 * DESCRIP: TEST_DATA0's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void TEST_DATA0_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open TEST_DATA0_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(TEST_DATA0_CLK, ENABLE); 

	/*select TEST_DATA0_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = TEST_DATA0_PIN;	

	/*set pin mode to input pull up mode*/
  	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial TEST_DATA0_PORT*/
  	GPIO_Init(TEST_DATA0_PORT, &GPIO_InitStructure);
 
}

/*
 * FUNC: TEST_DATA1_GPIO_Config
 * DESCRIP: TEST_DATA1's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void TEST_DATA1_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open TEST_DATA1_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(TEST_DATA1_CLK, ENABLE); 

	/*select TEST_DATA1_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = TEST_DATA1_PIN;	

	/*set pin mode to input pull up mode*/
  	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial TEST_DATA1_PORT*/
  	GPIO_Init(TEST_DATA1_PORT, &GPIO_InitStructure);
 
}

/*
 * FUNC: TEST_DATA2_GPIO_Config
 * DESCRIP: TEST_DATA2's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void TEST_DATA2_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open TEST_DATA2_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(TEST_DATA2_CLK, ENABLE); 

	/*select TEST_DATA2_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = TEST_DATA2_PIN;	

	/*set pin mode to input pull up mode*/
  	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial TEST_DATA2_PORT*/
  	GPIO_Init(TEST_DATA2_PORT, &GPIO_InitStructure);
 
}

/*
 * FUNC: TEST_DATA3_GPIO_Config
 * DESCRIP: TEST_DATA3's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void TEST_DATA3_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open TEST_DATA3_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(TEST_DATA3_CLK, ENABLE); 

	/*select TEST_DATA3_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = TEST_DATA3_PIN;	

	/*set pin mode to input pull up mode*/
  	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial TEST_DATA3_PORT*/
  	GPIO_Init(TEST_DATA3_PORT, &GPIO_InitStructure);
 
}

/*
 * FUNC: TEST_DATA4_GPIO_Config
 * DESCRIP: TEST_DATA4's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void TEST_DATA4_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open TEST_DATA4_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(TEST_DATA4_CLK, ENABLE); 

	/*select TEST_DATA4_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = TEST_DATA4_PIN;	

	/*set pin mode to input pull up mode*/
  	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial TEST_DATA4_PORT*/
  	GPIO_Init(TEST_DATA4_PORT, &GPIO_InitStructure);
 
}

/*
 * FUNC: TEST_DATA5_GPIO_Config
 * DESCRIP: TEST_DATA5's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void TEST_DATA5_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open TEST_DATA5_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(TEST_DATA5_CLK, ENABLE); 

	/*select TEST_DATA5_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = TEST_DATA5_PIN;	

	/*set pin mode to input pull up mode*/
  	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial TEST_DATA5_PORT*/
  	GPIO_Init(TEST_DATA5_PORT, &GPIO_InitStructure);
 
}

/*
 * FUNC: TEST_DATA6_GPIO_Config
 * DESCRIP: TEST_DATA6's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void TEST_DATA6_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open TEST_DATA6_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(TEST_DATA6_CLK, ENABLE); 

	/*select TEST_DATA6_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = TEST_DATA6_PIN;	

	/*set pin mode to input pull up mode*/
  	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial TEST_DATA6_PORT*/
  	GPIO_Init(TEST_DATA6_PORT, &GPIO_InitStructure);
 
}

/*
 * FUNC: TEST_DATA7_GPIO_Config
 * DESCRIP: TEST_DATA7's I/O configuration
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void TEST_DATA7_GPIO_Config(void)
{		
	/*define GPIO_InitTypeDef type's structure*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*open TEST_DATA7_PORT Periph Clock*/
	RCC_APB2PeriphClockCmd(TEST_DATA7_CLK, ENABLE); 

	/*select TEST_DATA3_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = TEST_DATA7_PIN;	

	/*set pin mode to input pull up mode*/
  	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   

	/*set pin speed to 50MHz */
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*initial TEST_DATA7_PORT*/
  	GPIO_Init(TEST_DATA7_PORT, &GPIO_InitStructure);
 
}

void GPIO_Config(void)
{
		DUT_DQ_OUT_GPIO_Config();
		MUX_18B20_OUT_GPIO_Config();
		MUX_E5_GPIO_Config();
		TOTAL_DQ_OUT_GPIO_Config();
		STRONG_PULLUP_GPIO_Config();
		MUX_E1_GPIO_Config();
		MUX_E2_GPIO_Config();
		MUX_E3_GPIO_Config();
		MUX_E4_GPIO_Config();
		TEST_ADDR0_GPIO_Config();
		TEST_ADDR1_GPIO_Config();
		TEST_ADDR2_GPIO_Config();
		TEST_ADDR3_GPIO_Config();
		TEST_ADDR4_GPIO_Config();
		TEST_ADDR5_GPIO_Config();
		TEST_ADDR6_GPIO_Config();
		TEST_ADDR7_GPIO_Config();
		MUX_S0_GPIO_Config();
		MUX_S1_GPIO_Config();
		MUX_S2_GPIO_Config();
		MUX_S3_GPIO_Config();
		TEST_DATA0_GPIO_Config();
		TEST_DATA1_GPIO_Config();
		TEST_DATA2_GPIO_Config();
		TEST_DATA3_GPIO_Config();
		TEST_DATA4_GPIO_Config();
		TEST_DATA5_GPIO_Config();
		TEST_DATA6_GPIO_Config();
		TEST_DATA7_GPIO_Config();
}



/*
 * FUNC: TOTAL_DQ_OUT_Mode_IPU
 * DESCRIP: set TOTAL_DQ_OUT-DATA pin to be input mode
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void TOTAL_DQ_OUT_Mode_IPU(void)
{
 	  GPIO_InitTypeDef GPIO_InitStructure;

	//printf("\r 1 \n");
	  /*select TOTAL_DQ_OUT_PORT pin to control*/	
	  GPIO_InitStructure.GPIO_Pin = TOTAL_DQ_OUT_PIN;

	//printf("\r 2 \n");
	  /*set pin mode to input pull up mode*/
	  //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		

	//printf("\r 3\n");
	  /*initial TOTAL_DQ_OUT_PORT*/
	  GPIO_Init(TOTAL_DQ_OUT_PORT, &GPIO_InitStructure);
	
	//printf("\r 4 \n");
	
}

/*
 * FUNC: DUT_DQ_OUT_Mode_IPU
 * DESCRIP: set DUT_DQ_OUT-DATA pin to be input mode
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void DUT_DQ_OUT_Mode_IPU(void)
{
 	  GPIO_InitTypeDef GPIO_InitStructure;

	  /*select DUT_DQ_OUT_PORT pin to control*/	
	  GPIO_InitStructure.GPIO_Pin = DUT_DQ_OUT_PIN;

	  /*set pin mode to input pull up mode*/ 
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	
		//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;

	  /*initial DUT_DQ_OUT_PORT*/
	  GPIO_Init(DUT_DQ_OUT_PORT, &GPIO_InitStructure);
}

/*
 * FUNC: MUX_18B20_OUT_Mode_IPU
 * DESCRIP: set MUX_18B20_OUT-DATA pin to be input mode
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void MUX_18B20_OUT_Mode_IPU(void)
{
 	  GPIO_InitTypeDef GPIO_InitStructure;

	  /*select DUT_DQ_OUT_PORT pin to control*/	
	  GPIO_InitStructure.GPIO_Pin = MUX_18B20_OUT_PIN;

	  /*set pin mode to input pull up mode*/ 
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	

	  /*initial DUT_DQ_OUT_PORT*/
	  GPIO_Init(MUX_18B20_OUT_PORT, &GPIO_InitStructure);
}








/*
 * FUNC: TOTAL_DQ_OUT_Mode_Out_PP
 * DESCRIP: set TOTAL_DQ_OUT-DATA pin to be output mode
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void TOTAL_DQ_OUT_Mode_Out_PP(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;

	 	/*select TOTAL_DQ_OUT_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = TOTAL_DQ_OUT_PIN;	

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/*initial TOTAL_DQ_OUT_PORT*/
  	GPIO_Init(TOTAL_DQ_OUT_PORT, &GPIO_InitStructure);
}

static void TOTAL_DQ_OUT_Mode_Out_OD(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;

	 	/*select TOTAL_DQ_OUT_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = TOTAL_DQ_OUT_PIN;	

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;   

	/*set pin speed to 50MHz */   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/*initial TOTAL_DQ_OUT_PORT*/
  	GPIO_Init(TOTAL_DQ_OUT_PORT, &GPIO_InitStructure);
}

/*
 * FUNC: DUT_DQ_OUT_Mode_Out_PP
 * DESCRIP: set DUT_DQ_OUT-DATA pin to be output mode
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void DUT_DQ_OUT_Mode_Out_PP(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;

	 	/*select DUT_DQ_OUT_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = DUT_DQ_OUT_PIN;	

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */    
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/*initial DUT_DQ_OUT_PORT*/
  	GPIO_Init(DUT_DQ_OUT_PORT, &GPIO_InitStructure);
}

/*
 * FUNC: DUT_DQ_OUT_Mode_Out_PP
 * DESCRIP: set DUT_DQ_OUT-DATA pin to be output mode
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void DUT_DQ_OUT_Mode_Out_OD(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;

	 	/*select DUT_DQ_OUT_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = DUT_DQ_OUT_PIN;	

	/*set pin mode to open-drain out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;   

	/*set pin speed to 50MHz */    
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/*initial DUT_DQ_OUT_PORT*/
  	GPIO_Init(DUT_DQ_OUT_PORT, &GPIO_InitStructure);
}

/*
 * FUNC: MUX_18B20_OUT_Mode_Out_PP
 * DESCRIP: set MUX_18B20_OUT-DATA pin to be output mode
 * INPUT: N/A
 * OUTPUT: N/A
 */
static void MUX_18B20_OUT_Mode_Out_PP(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;

	 	/*select MUX_18B20_OUT_PORT pin to control*/															   
  	GPIO_InitStructure.GPIO_Pin = MUX_18B20_OUT_PIN;	

	/*set pin mode to push-pull out mode*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*set pin speed to 50MHz */    
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/*initial MUX_18B20_OUT_PORT*/
  	GPIO_Init(MUX_18B20_OUT_PORT, &GPIO_InitStructure);
}




/*
 * master send reset pulse to slave
 */
static void TOTAL_DQ_OUT_Rst(void)
{
	int j;
	/*set pin mode to push-pull out mode*/
	#ifdef OD
		TOTAL_DQ_OUT_Mode_Out_OD(); 
  #else
		TOTAL_DQ_OUT_Mode_Out_PP(); 
	#endif
	
	TOTAL_DQ_OUT_DATA_OUT(LOW);
	/* master drive bus low at least 480us */
	Delay_us(550);
	
	/* master release bus */
	TOTAL_DQ_OUT_DATA_OUT(HIGH);
	//Delay_us(1);
	//TOTAL_DQ_OUT_DATA_OUT(LOW);
	//Delay_us(30);
	
	for(j=0;j<90;j++){
				__nop();
	}
	TOTAL_DQ_OUT_Mode_IPU();
	
	/*once slave receive reset signal, it will send presence pulse to master after 15~60us*/
	//Delay_us(15);
	j=0;
	
	while(TOTAL_DQ_OUT_DATA_IN())//??x=0?????? x=1??????
	{
			 if(++j >= 1000) //???????    1000   --- 30.4us
			 {
				 break;
			 }
	}
	Delay_us(100);//100
	
//	Delay_us(30);
//	TOTAL_DQ_OUT_Mode_Out_PP(); 
//	TOTAL_DQ_OUT_DATA_OUT(HIGH);
//	Delay_us(1);
//	TOTAL_DQ_OUT_Mode_IPU();
	
}

/*
 * master send reset pulse to slave
 */

//static void DUT_DQ_OUT_Rst(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	
//	/*set pin mode to push-pull out mode*/
//	#ifdef OD
//		DUT_DQ_OUT_Mode_Out_OD(); 
//  #else
//		DUT_DQ_OUT_Mode_Out_PP(); 
//	#endif
//	
//	//DUT_DQ_OUT_Mode_Out_PP();
//	//Delay_us(500);
//	
//	DUT_DQ_OUT_DATA_OUT(LOW);
//	/* master drive bus low at least 480us */
//	Delay_us(480);
//	
//	/* master release bus */
//	//DUT_DQ_OUT_DATA_OUT(HIGH);
//	/*once slave receive reset signal, it will send presence pulse to master after 15~60us*/
//	Delay_us(15);
//	DUT_DQ_OUT_Mode_IPU();
//	Delay_us(60);
//	//if(DUT_DQ_OUT_DATA_IN() == 0)
//   	//Delay_us(30);	
//}

static void DUT_DQ_OUT_Rst(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*set pin mode to push-pull out mode*/
	#ifdef OD
		DUT_DQ_OUT_Mode_Out_OD(); 
  #else
		DUT_DQ_OUT_Mode_Out_PP(); 
	#endif
	
	DUT_DQ_OUT_DATA_OUT(LOW);
	/* master drive bus low at least 480us */
	Delay_us(RST_LOW);
	
	/* master release bus */
	//DUT_DQ_OUT_DATA_OUT(HIGH);
	DUT_DQ_OUT_Mode_IPU();
	//DUT_DQ_OUT_Mode_Out_PP(); 
	/*once slave receive reset signal, it will send presence pulse to master after 15~60us*/
	Delay_us(15);	
	Delay_us(60);
	if(DUT_DQ_OUT_DATA_IN() == 0)
   	Delay_us(40);
	else 
		printf("There is no presence pulse.");

}


void test_Rst(void)
{
	/*set pin mode to push-pull out mode*/
	#ifdef OD
		DUT_DQ_OUT_Mode_Out_OD(); 
  #else
		DUT_DQ_OUT_Mode_Out_PP(); 
	#endif
	
	//DUT_DQ_OUT_Mode_Out_PP();
	//Delay_us(500);
	
	DUT_DQ_OUT_DATA_OUT(LOW);
	/* master drive bus low at least 480us */
	Delay_us(680);
	
	/* master release bus */
	DUT_DQ_OUT_DATA_OUT(HIGH);
	//DUT_DQ_OUT_Mode_IPU();
	//DUT_DQ_OUT_Mode_Out_PP(); 
	/*once slave receive reset signal, it will send presence pulse to master after 15~60us*/
	Delay_us(15);
	DUT_DQ_OUT_Mode_IPU();
	Delay_us(60);
	if(DUT_DQ_OUT_DATA_IN() == 0)
   	Delay_us(300);	

//Delay_us(100);
	//DUT_DQ_OUT_Mode_Out_PP(); 
	//DUT_DQ_OUT_DATA_OUT(1);
	//Delay_us(50);
	//Delay_us(150);

}



/*
 * master send reset pulse to slave
 */
static void MUX_18B20_OUT_Rst(void)
{
	/*set pin mode to push-pull out mode*/
	MUX_18B20_OUT_Mode_Out_PP();
//		Delay_us(11750);

	
	MUX_18B20_OUT_DATA_OUT(LOW);
	/* master drive bus low at least 480us */
	//Delay_us(255);
	Delay_us(480);


	/* master release bus */
	MUX_18B20_OUT_DATA_OUT(HIGH);
	
	/*once slave receive reset signal, it will send presence pulse to master after 15~60us*/
	Delay_us(15);
}



/*
 * master send reset pulse to slave
 */
static void DQ_Rst(uint8_t type)
{
		switch(type) {
			case DUT_DQ_OUT:
				DUT_DQ_OUT_Rst();
				break;
			case MUX_18B20_OUT:
				MUX_18B20_OUT_Rst();
				break;
			case TOTAL_DQ_OUT:
				TOTAL_DQ_OUT_Rst();
				break;
			default:
				MUX_18B20_OUT_Rst();
				break;
		}
}





/*
 * check presence pulse
 * 0: success
 * 1: failure
 */
static uint8_t TOTAL_DQ_OUT_Presence(void)
{
	uint8_t pulse_time = 0;
	
	/*set pin mode to input pull up mode*/
	TOTAL_DQ_OUT_Mode_IPU();
	Delay_us(1);
	
	/* wait for presence pulse, 60~240us low level signal
	 * if presence pulse does not come, then timeout; once slave receive reset signal, it will send presence pulse to master after 15~60us
	 */
	while( TOTAL_DQ_OUT_DATA_IN() && pulse_time<4 )
	{
		pulse_time++;
		Delay_us(10);
	}	
	/* after 100us, presence pulse does not come*/
	if( pulse_time >=100 ) {
		printf("error");
		return 1;
	}
	else
		pulse_time = 0;
	
	/* presence pulse comes and not sustain over 240us */
	while( !TOTAL_DQ_OUT_DATA_IN() && pulse_time<20 )
	{
		pulse_time++;
		Delay_us(10);
	}

//	//TOTAL_DQ_OUT_Mode_Out_PP();
//	//TOTAL_DQ_OUT_DATA_OUT(1);
//	//Delay_us(100);
//	
//	if( pulse_time >=240 )
//		return 1;
//	else
//		return 0;

//	Delay_us(110);
//	
//	DUT_DQ_OUT_Mode_Out_PP();
//	DUT_DQ_OUT_DATA_OUT(1);
//	Delay_us(50);
	
	if( pulse_time >=240 ) {
	  printf("error");
		return 1;
	}
	else
		return 0;

}

uint8_t BUSY_DUT(void) {
	return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4);

}




static uint8_t DUT_DQ_OUT_Presence(void)
{
	uint16_t pulse_time = 0;
	
	/*set pin mode to input pull up mode*/
	
	//DUT_DQ_OUT_Mode_IPU();
		//Delay_us(1);
	
//	/* wait for presence pulse, 60~240us low level signal
//	 * if presence pulse does not come, then timeout; once slave receive reset signal, it will send presence pulse to master after 15~60us
//	 */
//	//while( DUT_DQ_OUT_DATA_IN() && pulse_time<200 )
//	while( BUSY_DUT() && pulse_time<300 )
//	{
//		pulse_time++;
//		Delay_us(1);
//	}	
//	/* after 100us, presence pulse does not come*/
//	if( pulse_time >=300 )
//		return 1;
//	else
//		pulse_time = 0;
//	
//	//printf("Presence high: %d", pulse_time);
//	
//	/* presence pulse comes and not sustain over 240us */
//	//while( !DUT_DQ_OUT_DATA_IN() && pulse_time<240 )
//	while( !BUSY_DUT() && pulse_time<480 )
//	{
//		pulse_time++;
//		Delay_us(1);
//	}	
	
	//Delay_us(48);
	
	//DUT_DQ_OUT_Mode_Out_PP();
	//DUT_DQ_OUT_Mode_Out_OD();
	//DUT_DQ_OUT_DATA_OUT(1);
	Delay_us(50);
	
	if( pulse_time >=240 )
		return 1;
	else
		return 0;
}


/*
 * check presence pulse
 * 0: success
 * 1: failure
 */
static uint8_t MUX_18B20_OUT_Presence(void)
{
	uint8_t pulse_time = 0;
	
	/*set pin mode to input pull up mode*/
	MUX_18B20_OUT_Mode_IPU();
	
	/* wait for presence pulse, 60~240us low level signal
	 * if presence pulse does not come, then timeout; once slave receive reset signal, it will send presence pulse to master after 15~60us
	 */
	while( MUX_18B20_OUT_DATA_IN() && pulse_time<100 )
	{
		pulse_time++;
		Delay_us(1);
	}	
	/* after 100us, presence pulse does not come*/
	if( pulse_time >=100 )
		return 1;
	else
		pulse_time = 0;
	
	/* presence pulse comes and not sustain over 240us */
	while( !MUX_18B20_OUT_DATA_IN() && pulse_time<240 )
	{
		pulse_time++;
		Delay_us(1);
	}	
	if( pulse_time >=240 )
		return 1;
	else
		return 0;
}



/*
 * check presence pulse
 * 0: success
 * 1: failure
 */
static uint8_t DQ_Presence(uint8_t type)
{
		switch(type) {
			case DUT_DQ_OUT:
				return DUT_DQ_OUT_Presence();
				break;
			case MUX_18B20_OUT:
				return MUX_18B20_OUT_Presence();
				break;
			case TOTAL_DQ_OUT:
				return TOTAL_DQ_OUT_Presence();
				//Delay_us(100);
				break;
			default:
				return MUX_18B20_OUT_Presence();
				break;
		}
}



/*
 * TOTAL_DQ_OUT read one bit
 */
static uint8_t TOTAL_DQ_OUT_Read_Bit(void)
{
	uint8_t dat; 
	int j;
	
	/* time slot of read 1 and read 0 need to be over 60us */		
	#ifdef OD
		TOTAL_DQ_OUT_Mode_Out_OD(); 
  #else
		TOTAL_DQ_OUT_Mode_Out_PP(); 
	#endif
	/* master drive bus low >1us <15us*/
	TOTAL_DQ_OUT_DATA_OUT(LOW);
	//Delay_us(2);
	//for(j=0;j<1;j++){
		//__nop();
	//}
//	__nop();
//	__nop();
//	__nop();
//	__nop();
//	__nop();
//	
//	__nop();
//	__nop();
//	__nop();
//	__nop();
//	__nop();
   for(j=0;j<4;j++){
			__nop();
	}
	
	//printf("\r WAIT 1us \n");
	/* set pin to inputmode, release bus, then pull up by pull-up resistor*/
	TOTAL_DQ_OUT_Mode_IPU();
	
	//Delay_us(5);
	//printf("\r WAIT 5us \n");
	for(j=0;j<4;j++){
				__nop();
	}
	
	if( TOTAL_DQ_OUT_DATA_IN() == SET )
		dat = 1;
	else
		dat = 0;
	
	/* based on Time Slot Timing Diagram */
	//	printf("\r data read \n");
	//DUT_DQ_OUT_Mode_Out_PP();
	//DUT_DQ_OUT_Mode_Out_OD();
	//DUT_DQ_OUT_DATA_OUT(HIGH);
	//Delay_us(55);
	
	for(j=0;j<315;j++) {
		__nop();
	}
	
	return dat;
}

/*
 * DUT_DQ_OUT read one bit
 */
static uint8_t DUT_DQ_OUT_Read_Bit(void)
{
	uint8_t dat;
	
	/* time slot of read 1 and read 0 need to be over 60us */	
	#ifdef OD
		DUT_DQ_OUT_Mode_Out_OD(); 
  #else
		DUT_DQ_OUT_Mode_Out_PP(); 
	#endif
	
	//DUT_DQ_OUT_Mode_Out_PP();
	
	/* master drive bus low >1us <15us*/
	DUT_DQ_OUT_DATA_OUT(LOW);
	Delay_us(RD_WR1_LOW);
	DUT_DQ_OUT_Mode_IPU();
	
	Delay_us(RD_SAMPLE);
	
	if( DUT_DQ_OUT_DATA_IN() == SET )
		dat = 1;
	else
		dat = 0;
	Delay_us(RECOVER_RD_WR1);

	return dat;
}



/*
 * MUX_18B20_OUT read one bit
 */
static uint8_t MUX_18B20_OUT_Read_Bit(void)
{
	uint8_t dat;
	//int i;
	volatile int t;
	t = 0;
	/* time slot of read 1 and read 0 need to be over 60us */	
	MUX_18B20_OUT_Mode_Out_PP();
	/* master drive bus low >1us <15us*/
	
	MUX_18B20_OUT_DATA_OUT(LOW);
	Delay_us(2);
	//for(i=0;i<1;i++)
		//t++;
	MUX_18B20_OUT_DATA_OUT(HIGH);
	STRONG_PULLUP_DATA_OUT(0);
	Delay_us(5);
	STRONG_PULLUP_DATA_OUT(1);	
	
	//MUX_18B20_OUT_DATA_OUT(HIGH);
	
	/* set pin to inputmode, release bus, then pull up by pull-up resistor*/
	MUX_18B20_OUT_Mode_IPU();
	//Delay_us(2);
	
	if( MUX_18B20_OUT_DATA_IN() == SET )
		dat = 1;
	else
		dat = 0;
	
	/* based on Time Slot Timing Diagram */
	Delay_us(45);
	
	return dat;
}



/*
 * DQ read one bit
 */
static uint8_t DQ_Read_Bit(uint8_t type)
{
		switch(type) {
			case DUT_DQ_OUT:
				return DUT_DQ_OUT_Read_Bit();
				break;
			case MUX_18B20_OUT:
				return MUX_18B20_OUT_Read_Bit();
				break;
			case TOTAL_DQ_OUT:
				return TOTAL_DQ_OUT_Read_Bit();
				break;
			default:
				return MUX_18B20_OUT_Read_Bit();
				break;
		}
}



uint8_t TOTAL_DQ_OUT_Read2Bit(void)  
{    
		uint8_t i, j, dat;	
	  dat = 0;
	
		for(i=0; i<2; i++) 
		{
			j = TOTAL_DQ_OUT_Read_Bit();		
			dat = (dat) | (j<<i);
		}
	
		return dat;
}

uint8_t MUX_18B20_OUT_Read2Bit(void)  
{    
		uint8_t i, j, dat;	
	  dat = 0;
	
		for(i=0; i<2; i++) 
		{
			j = MUX_18B20_OUT_Read_Bit();		
			dat = (dat) | (j<<i);
		}
	
		return dat;
}

uint8_t DQ_Read2Bit(uint8_t type)  
{    
		uint8_t i, j, dat;	
	  dat = 0;
	
		for(i=0; i<2; i++) 
		{
			j = DQ_Read_Bit(type);		
			dat = (dat) | (j<<i);
		}
	
		return dat;
}






/*
 * TOTAL_DQ_OUT read one byte, LSB first
 */
uint8_t TOTAL_DQ_OUT_Read_Byte(void)
{
	uint8_t i, j, dat = 0;	
	
	for(i=0; i<8; i++) 
	{
		j = TOTAL_DQ_OUT_Read_Bit();		
		dat = (dat) | (j<<i);
		
		
	}
	
	return dat;
}

/*
 * DUT_DQ_OUT read one byte, LSB first
 */
uint8_t DUT_DQ_OUT_Read_Byte(void)
{
	uint8_t i, j, dat = 0;	
	
	for(i=0; i<8; i++) 
	{
		j = DUT_DQ_OUT_Read_Bit();		
		dat = (dat) | (j<<i);
	}
	
	return dat;
}



/*
 * MUX_18B20_OUT read one byte, LSB first
 */
uint8_t MUX_18B20_OUT_Read_Byte(void)
{
	uint8_t i, j, dat = 0;	
	
	for(i=0; i<8; i++) 
	{
		j = MUX_18B20_OUT_Read_Bit();		
		dat = (dat) | (j<<i);
		//Delay_us(200);
	}
	
	return dat;
}

/*
 * DQ read one byte, LSB first   
 */
uint8_t DQ_Read_Byte(uint8_t type)
{
	uint8_t i, j, dat = 0;	
	
	for(i=0; i<8; i++) 
	{
		j = DQ_Read_Bit(type);		
		dat = (dat) | (j<<i);
	}
	return dat;
}




void TOTAL_DQ_OUT_Write_Bit(uint8_t bit)  
{  
		uint8_t testb;
		int j;
	
		#ifdef OD
		TOTAL_DQ_OUT_Mode_Out_OD(); 
  #else
		TOTAL_DQ_OUT_Mode_Out_PP(); 
	#endif
		testb = bit&0x01;	
		/* time slot of write 1 and read 0 need to be over 60us */
		if (testb)
		{			
			TOTAL_DQ_OUT_DATA_OUT(LOW);
			/* 1us < this delay < 15us */
			//Delay_us(1);
			//Delay_us(rand() % 12 + 2);
			for(j=0;j<34;j++) {
					__nop();
			}	
			
			TOTAL_DQ_OUT_DATA_OUT(HIGH);
			//Delay_us(58);
			for(j=0;j<340;j++) {
				  __nop();
			}
		}		
		else
		{			
			TOTAL_DQ_OUT_DATA_OUT(LOW);
			/* 60us < Tx 0 < 120us */
			//Delay_us(60);
			//Delay_us(rand() % 58 + 61);
			for(j=0;j<450;j++){
					__nop();
			}
			
			TOTAL_DQ_OUT_DATA_OUT(HIGH);			
			/* 1us < Trec < infinity*/
			//Delay_us(5);
			//Delay_us(rand() % 6 + 2);
			for(j=0;j<20;j++) {
				  __nop();
			}
		}

		//Delay_us(500);
}


void MUX_18B20_OUT_Write_Bit(uint8_t bit)  
{  
		uint8_t testb;
	  //int i;
	  volatile int t = 0;
		MUX_18B20_OUT_Mode_Out_PP();
		testb = bit&0x01;	
		/* time slot of write 1 and read 0 need to be over 60us */
		if (testb)
		{			
			MUX_18B20_OUT_DATA_OUT(LOW);
			/* 1us < this delay < 15us */
			Delay_us(2);
			//Delay_us(rand() % 12 + 2);
			
			MUX_18B20_OUT_DATA_OUT(HIGH);
			Delay_us(58);
		}		
		else
		{			
			MUX_18B20_OUT_DATA_OUT(LOW);
			/* 60us < Tx 0 < 120us */
			Delay_us(60);
			//Delay_us(rand() % 58 + 61);
			
			MUX_18B20_OUT_DATA_OUT(HIGH);			
			/* 1us < Trec < infinity*/
			Delay_us(1);
			//for(i=0;i<1;i++)
				//t++;
			//Delay_us(rand() % 6 + 2);
		}	  
}





void DUT_DQ_OUT_Write_Bit(uint8_t bit)  
{  
		uint8_t testb;
		#ifdef OD
		DUT_DQ_OUT_Mode_Out_OD(); 
		#else
			DUT_DQ_OUT_Mode_Out_PP(); 
		#endif
	
	//DUT_DQ_OUT_Mode_Out_PP();
		
		testb = bit&0x01;	
		/* time slot of write 1 and read 0 need to be over 60us */
		if (testb)
		{			
			DUT_DQ_OUT_DATA_OUT(LOW);
			/* 1us < this delay < 15us */
			Delay_us(RD_WR1_LOW);
			//Delay_us(rand() % 12 + 2);
			DUT_DQ_OUT_DATA_OUT(HIGH);
			Delay_us(RECOVER_RD_WR1);
		}		
		else
		{			
			DUT_DQ_OUT_DATA_OUT(LOW);
			/* 60us < Tx 0 < 120us */
			Delay_us(WR0_LOW); /// Time Slot
			//Delay_us(rand() % 58 + 61);
			DUT_DQ_OUT_DATA_OUT(HIGH);			
			/* 1us < Trec < infinity*/
			Delay_us(RECOVER_WR0); /// Recovery Time
			//Delay_us(rand() % 6 + 2);
		}
			//Delay_us(200);
}

void DQ_Write_Bit(uint8_t bit, uint8_t type)  
{  
		switch(type) {
			case DUT_DQ_OUT:
				DUT_DQ_OUT_Write_Bit(bit);
				break;
			case MUX_18B20_OUT:
				MUX_18B20_OUT_Write_Bit(bit);
				break;
			case TOTAL_DQ_OUT:
				TOTAL_DQ_OUT_Write_Bit(bit);
				break;
			default:
				MUX_18B20_OUT_Write_Bit(bit);
				break;
		}	  
}




/*
 * TOTAL_DQ_OUT write one byte, LSB first
 */
void TOTAL_DQ_OUT_Write_Byte(uint8_t dat)
{
	uint8_t i, testb;
	int j;
	volatile int t = 0;
	
	#ifdef OD
		TOTAL_DQ_OUT_Mode_Out_OD(); 
  #else
		TOTAL_DQ_OUT_Mode_Out_PP(); 
	#endif
	
	for( i=0; i<8; i++ )
	{
		testb = dat&0x01;
		dat = dat>>1;		
		/* time slot of write 1 and read 0 need to be over 60us */
		if (testb)
		{			
			TOTAL_DQ_OUT_DATA_OUT(LOW);
			/* 1us < this delay < 15us */
			//Delay_us(5);
			for(j=0;j<34;j++) {
					__nop();
			}
			
			TOTAL_DQ_OUT_DATA_OUT(HIGH);
			//Delay_us(60);
			//Delay_us(100);
			for(j=0;j<340;j++) {
				  __nop();
			}
		}		
		else
		{			
			TOTAL_DQ_OUT_DATA_OUT(LOW);
			/* 60us < Tx 0 < 120us */
			//Delay_us(60);
			for(j=0;j<250;j++){
					__nop();
			}
			
			TOTAL_DQ_OUT_DATA_OUT(HIGH);			
			/* 1us < Trec < 无穷大*/
			
			//Delay_us(2);
			//for(j=0;j<13;j++)
				//t++;
			for(j=0;j<220;j++) {
				  __nop();
			}
		}
		//Delay_us(1000);
	}
}

/*
 * DUT_DQ_OUT write one byte, LSB first
 */
void DUT_DQ_OUT_Write_Byte(uint8_t dat)
{
	uint8_t i, testb;
	//int j;
	volatile int t = 0;
	
	#ifdef OD
		DUT_DQ_OUT_Mode_Out_OD(); 
  #else
		DUT_DQ_OUT_Mode_Out_PP(); 
	#endif
	
	//DUT_DQ_OUT_Mode_Out_PP();
	
	
	for( i=0; i<8; i++ )
	{
		testb = dat&0x01;
		dat = dat>>1;		
		/* time slot of write 1 and read 0 need to be over 60us */
		if (testb)
		{			
			DUT_DQ_OUT_DATA_OUT(LOW);
			/* 1us < this delay < 15us */
			Delay_us(2);
			
			DUT_DQ_OUT_DATA_OUT(HIGH);
			Delay_us(50);
		}		
		else
		{			
			DUT_DQ_OUT_DATA_OUT(LOW);
			/* 60us < Tx 0 < 120us */
			Delay_us(60);  //// Time Slot
			
			DUT_DQ_OUT_DATA_OUT(HIGH);			
			/* 1us < Trec < 无穷大*/
			Delay_us(1);  //// Recovery
			//for(j=0;j<2;j++)
				//t++;
		
		}
		
		//Delay_us(200);
	}
	
	
}



/*
 * MUX_18B20_OUT write one byte, LSB first
 */
void MUX_18B20_OUT_Write_Byte(uint8_t dat)
{
	uint8_t i, testb;
	//int j;
	volatile int t = 0;
	MUX_18B20_OUT_Mode_Out_PP();
	
	for( i=0; i<8; i++ )
	{
		testb = dat&0x01;
		dat = dat>>1;		
		/* time slot of write 1 and read 0 need to be over 60us */
		if (testb)
		{			
			MUX_18B20_OUT_DATA_OUT(LOW);
			/* 1us < this delay < 15us */
			Delay_us(8);
			
			MUX_18B20_OUT_DATA_OUT(HIGH);
			Delay_us(58);
		}		
		else
		{			
			MUX_18B20_OUT_DATA_OUT(LOW);
			/* 60us < Tx 0 < 120us */
			Delay_us(60);
			
			MUX_18B20_OUT_DATA_OUT(HIGH);			
			/* 1us < Trec < 无穷大*/
			Delay_us(100);
			//for(j=0;j<2;j++)
				//t++;
			//Delay_us(200);
		}
	}
}


/*
 * DQ write one byte, LSB first
 */
void DQ_Write_Byte(uint8_t dat, uint8_t type)
{
		switch(type) {
			case DUT_DQ_OUT:
				DUT_DQ_OUT_Write_Byte(dat);
				break;
			case MUX_18B20_OUT:
				MUX_18B20_OUT_Write_Byte(dat);
				break;
			case TOTAL_DQ_OUT:
				TOTAL_DQ_OUT_Write_Byte(dat);
				break;
			default:
				MUX_18B20_OUT_Write_Byte(dat);
				break;
		}
}



/*
 * DS18B20
 * when 12-bit resolution ratio, 5 sign bits，7 integer bits, 4 decimal bits
 *
 *         |---------integer----------|-----decimal resolution ratio 1/(2^4)=0.0625----|
 * LSB  | 2^3 | 2^2 | 2^1 | 2^0 | 2^(-1) | 2^(-2) | 2^(-3) | 2^(-4) |
 *
 *
 *         |-----sign bit: 0->positive  1->negative-------|-----------integer-----------|
 * MSB  |  s  |  s  |  s  |  s  |    s   |   2^6  |   2^5  |   2^4  |
 *
 * 
 * temperature = sign bit + integer + decimal*0.0625
 */
float TOTAL_DQ_OUT_Get_Temp(void)
{
	uint8_t tpmsb, tplsb;
	short s_tem;
	float f_tem;
	
	TOTAL_DQ_OUT_Rst();	   
	TOTAL_DQ_OUT_Presence();	 
	TOTAL_DQ_OUT_Write_Byte(SKIP_ROM);				
	TOTAL_DQ_OUT_Write_Byte(CONVERT_T);	

  Delay_us(8000);

	
	TOTAL_DQ_OUT_Rst();
  TOTAL_DQ_OUT_Presence();
	TOTAL_DQ_OUT_Write_Byte(SKIP_ROM);				
  TOTAL_DQ_OUT_Write_Byte(READ_SCRATCHPAD);				
	
	tplsb = TOTAL_DQ_OUT_Read_Byte();		 
	tpmsb = TOTAL_DQ_OUT_Read_Byte(); 
	
	s_tem = tpmsb<<8;
	s_tem = s_tem | tplsb;
	
	s_tem = s_tem & 4095;
	
	if( (s_tem & 2048) == 2048 )	{
		s_tem = (s_tem^4095) & 4095;
		f_tem = -1*(s_tem+1) * 0.0625;
	}	/* negative */
			
	else
		f_tem = s_tem * 0.0625;
	
	return f_tem;  	
}

float MUX_18B20_OUT_Get_Temp(void)
{
	uint8_t tpmsb, tplsb;
	short s_tem;
	float f_tem;
	
	MUX_18B20_OUT_Rst();	   
	MUX_18B20_OUT_Presence();	 
	MUX_18B20_OUT_Write_Byte(SKIP_ROM);				
	MUX_18B20_OUT_Write_Byte(CONVERT_T);	

  Delay_us(10000);

	
	MUX_18B20_OUT_Rst();
  MUX_18B20_OUT_Presence();
	MUX_18B20_OUT_Write_Byte(SKIP_ROM);				
  MUX_18B20_OUT_Write_Byte(READ_SCRATCHPAD);				
	
	tplsb = MUX_18B20_OUT_Read_Byte();		 
	tpmsb = MUX_18B20_OUT_Read_Byte(); 
	
	//for(i=0;i<7;i++)
		//tempp = MUX_18B20_OUT_Read_Byte(); 
	
	s_tem = tpmsb<<8;
	s_tem = s_tem | tplsb;
	
	s_tem = s_tem & 4095;
	
	if( (s_tem & 2048) == 2048 )	{
		s_tem = (s_tem^4095) & 4095;
		f_tem = -1*(s_tem+1) * 0.0625;
	}	/* negative */
			
	else
		f_tem = s_tem * 0.0625;
	
	return f_tem;  	
}


/*
 * DS18B20
 * when 12-bit resolution ratio, 5 sign bits，7 integer bits, 4 decimal bits
 *
 *         |---------integer----------|-----decimal resolution ratio 1/(2^4)=0.0625----|
 * LSB  | 2^3 | 2^2 | 2^1 | 2^0 | 2^(-1) | 2^(-2) | 2^(-3) | 2^(-4) |
 *
 *
 *         |-----sign bit: 0->positive  1->negative-------|-----------integer-----------|
 * MSB  |  s  |  s  |  s  |  s  |    s   |   2^6  |   2^5  |   2^4  |
 *
 * 
 * temperature = sign bit + integer + decimal*0.0625
 */
float DUT_DQ_OUT_Get_Temp(void)
{
	uint8_t tpmsb, tplsb, done;
	short s_tem;
	float f_tem;
	int i;
	uint8_t serial[9];
//	uint8_t ID_Buff1[80][8];
	
	DUT_DQ_OUT_Rst();	   
	DUT_DQ_OUT_Presence();	
	DUT_DQ_OUT_Write_Byte(SKIP_ROM);				
	DUT_DQ_OUT_Write_Byte(CONVERT_T);				
	
	//Delay_us(1500000);
	
//	DUT_DQ_OUT_Rst();
//  DUT_DQ_OUT_Presence();				
//  DUT_DQ_OUT_Write_Byte(READ_ROM);	 
//  
////	printf("\r 33H sent \n");
//	
//	for(i=0; i<8; i++) {
//     serial[i] = DUT_DQ_OUT_Read_Byte(); 
//		//Delay_us(500);
//	//	printf("\r Loop %d \n",i);
//	//	 printf("\r\n ROM byte %d : %2x\r",i, serial[i]);
//		printf("%2x",serial[i]);
//	}	
	//DQ_SearchROM(ID_Buff1,MAXNUM_SWITCH_18B20_OUT, DUT_DQ_OUT);
	
	
	do{
		done = DUT_DQ_OUT_Read_Bit();
	}while(done != 1);
	
	DUT_DQ_OUT_Rst();
  DUT_DQ_OUT_Presence();
	DUT_DQ_OUT_Write_Byte(SKIP_ROM);				
  DUT_DQ_OUT_Write_Byte(READ_SCRATCHPAD);				
	
	tplsb = DUT_DQ_OUT_Read_Byte();		 
	tpmsb = DUT_DQ_OUT_Read_Byte(); 
	
	//printf("\r\n Temp byte LO : %2x\r\n",tplsb);
	//printf("\r\n Temp byte HI : %2x\r\n",tpmsb);

	//for(i=2; i<9; i++) {
     //serial[i] = DUT_DQ_OUT_Read_Byte(); 
		 //printf("\r\n serial %d is : %2x\r\n",i,serial[i]);
		// printf("\r\n Temp byte LO : %2x\r\n",tplsb);
	//}
	
	
	s_tem = tpmsb<<8;
	s_tem = s_tem | tplsb;
	
	s_tem = s_tem & 4095;
	
	if( (s_tem & 2048) == 2048 )	{
		s_tem = (s_tem^4095) & 4095;
		f_tem = -1*(s_tem+1) * 0.0625;
	}	/* negative */
			
	else
		f_tem = s_tem * 0.0625;
	
	return f_tem; 	
}

void print_th(void) {
		uint8_t b1, b2, b3, b4;
	
	  DUT_DQ_OUT_Rst();	   
		DUT_DQ_OUT_Presence();	
		//Delay_us(500);	
		DUT_DQ_OUT_Write_Byte(SKIP_ROM);				
		DUT_DQ_OUT_Write_Byte(0x44);				
	
		Delay_us(3000000);
    
	  
		DUT_DQ_OUT_Rst();	   
		DUT_DQ_OUT_Presence();	
		//Delay_us(500);	
		DUT_DQ_OUT_Write_Byte(SKIP_ROM);				
		DUT_DQ_OUT_Write_Byte(0xbe);
	  
		b1 = DUT_DQ_OUT_Read_Byte();
		b2 = DUT_DQ_OUT_Read_Byte();
		b3 = DUT_DQ_OUT_Read_Byte();
	  b3 = DUT_DQ_OUT_Read_Byte();
	  b3 = DUT_DQ_OUT_Read_Byte();
	  b3 = DUT_DQ_OUT_Read_Byte();
	  b3 = DUT_DQ_OUT_Read_Byte(); // Hcode
	  b4 = DUT_DQ_OUT_Read_Byte();
		b4 = DUT_DQ_OUT_Read_Byte();
	  
	
	  printf("\r\n Temp byte LO : %2x\r\n",b1);
		printf("\r\n Temp byte HI : %2x\r\n",b2);
	  printf("\r\n Humi byte : %2x\r\n",b3);
		printf("\r\n CRC byte : %2x\r\n",b4);
}



float DUT_DQ_OUT_Get_Temp_14bit(void)
{
	uint8_t tpmsb, tplsb, done, i;
	short temp;
	uint16_t s_tem;
	uint16_t lsb_tem;
	float f_tem;
	
	DUT_DQ_OUT_Rst();	   
	DUT_DQ_OUT_Presence();	 
	DUT_DQ_OUT_Write_Byte(SKIP_ROM);	
	//Delay_us(100);	
	DUT_DQ_OUT_Write_Byte(CONVERT_T);				
		
	//Delay_us(15000);
	do{
		done = DUT_DQ_OUT_Read_Bit();
	}while(done != 1);
	
	
	DUT_DQ_OUT_Rst();
  DUT_DQ_OUT_Presence();
	DUT_DQ_OUT_Write_Byte(SKIP_ROM);				
  DUT_DQ_OUT_Write_Byte(READ_SCRATCHPAD);				
	
	tplsb = DUT_DQ_OUT_Read_Byte();		 
	tpmsb = DUT_DQ_OUT_Read_Byte(); 
	
	//printf("\r\n Temp byte HI : %2x\r\n",tpmsb);
	//printf("\r\n Temp byte LO : %2x\r\n",tplsb);
	
	for(i=0; i<7; i++) {
		
	DUT_DQ_OUT_Read_Byte();
     //serial[i] =  
		 //printf("\r\n Temp byte HI : %2x\r\n",tpmsb);
		 //printf("\r\n Temp byte LO : %2x\r\n",tplsb);
	}
	
	s_tem = tpmsb<<8;
	s_tem = s_tem | tplsb;
	
	//printf("\r\n Temp code ori: %4x\r\n",s_tem);
	
	lsb_tem = s_tem & 49152;
	lsb_tem = lsb_tem >> 14;
	//printf("\r\n lsb code ori: %4x\r\n",lsb_tem);
	
	s_tem = s_tem & 4095;
	temp = s_tem << 2;
	s_tem = temp | lsb_tem;
	
	//printf("\r\n Temp code final: %4x\r\n",s_tem);
	
	if( (s_tem & 8192) == 8192 ) {
		s_tem = (s_tem^16383) & 16383;
		f_tem = (-1)*(s_tem+1) * 0.015625;	
	}		/* negative */	
	else
		f_tem = s_tem * 0.015625;
	
	return f_tem; 	
}



float MUX_DQ_OUT_Get_Temp(void)
{
	uint8_t tpmsb, tplsb, done;
	short s_tem;
	float f_tem;
	
	MUX_18B20_OUT_Rst();	   
	MUX_18B20_OUT_Presence();	 
	MUX_18B20_OUT_Write_Byte(SKIP_ROM);				
	MUX_18B20_OUT_Write_Byte(CONVERT_T);				
	
	
	Delay_us(8000);
	do{
		done = DUT_DQ_OUT_Read_Bit();
	}while(done != 1);
	
	
	MUX_18B20_OUT_Rst();	   
	MUX_18B20_OUT_Presence();	 
	MUX_18B20_OUT_Write_Byte(SKIP_ROM);						
  MUX_18B20_OUT_Write_Byte(READ_SCRATCHPAD);				
	
	tplsb = MUX_18B20_OUT_Read_Byte();		 
	tpmsb = MUX_18B20_OUT_Read_Byte(); 
	
	//for(i=0; i<8; i++) {
     //serial[i] = DQ_Read_Byte(type); 
		 //printf("\r\n Temp byte HI : %2x\r\n",tpmsb);
		 //printf("\r\n Temp byte LO : %2x\r\n",tplsb);
	//}
	
	s_tem = tpmsb<<8;
	s_tem = s_tem | tplsb;
	
	s_tem = s_tem & 4095;
	
	if( (s_tem & 2048) == 2048 )	{
		s_tem = (s_tem^4095) & 4095;
		f_tem = -1*(s_tem+1) * 0.0625;
	}	/* negative */
			
	else
		f_tem = s_tem * 0.0625;
	
	return f_tem; 	
}



void MUX_18B20_OUT_Read_Temperaure_Match(uint8_t *rom, uint8_t temp_lo, uint8_t temp_hi) 
{
		int i;
	
		MUX_18B20_OUT_Rst();	   
		MUX_18B20_OUT_Presence();	 
		MUX_18B20_OUT_Write_Byte(MATCH_ROM);
		
		for(i=0; i<8; i++) {
			MUX_18B20_OUT_Write_Byte(rom[i]);
		}
			
	  MUX_18B20_OUT_Write_Byte(READ_SCRATCHPAD);

		temp_lo = MUX_18B20_OUT_Read_Byte();
		temp_hi = MUX_18B20_OUT_Read_Byte();
		
		printf("\r\ntemp_lo: %x\r\n", temp_lo);
		printf("\r\ntemp_hi: %x\r\n", temp_hi);
		
}

void MUX_18B20_OUT_Read_Temperaure_Match_v2(uint8_t *rom, uint8_t *temp) 
{
		int i;
	
		MUX_18B20_OUT_Rst();	   
		MUX_18B20_OUT_Presence();	 
		MUX_18B20_OUT_Write_Byte(MATCH_ROM);
		
		for(i=0; i<8; i++) {
			MUX_18B20_OUT_Write_Byte(rom[i]);
		}
			
	  MUX_18B20_OUT_Write_Byte(READ_SCRATCHPAD);

		temp[0] = MUX_18B20_OUT_Read_Byte();
		temp[1] = MUX_18B20_OUT_Read_Byte();
		
		//printf("\r\ntemp_lo: %x\r\n", temp[0]);
		//printf("\r\ntemp_hi: %x\r\n", temp[1]);
		
}

void MUX_18B20_OUT_Read_Temperaure_Skip(uint8_t *temp, float *temp_trans , uint8_t index) 
{
		short s_tem;
	
		MUX_18B20_OUT_Rst();	   
		MUX_18B20_OUT_Presence();	 
		MUX_18B20_OUT_Write_Byte(SKIP_ROM);				
		MUX_18B20_OUT_Write_Byte(CONVERT_T);
		
		Delay_us(8000);
	
	  MUX_18B20_OUT_Rst();	   
		MUX_18B20_OUT_Presence();	 
		MUX_18B20_OUT_Write_Byte(SKIP_ROM);
	  MUX_18B20_OUT_Write_Byte(READ_SCRATCHPAD);

		temp[0] = MUX_18B20_OUT_Read_Byte();
		temp[1] = MUX_18B20_OUT_Read_Byte();
		
		s_tem = temp[1]<<8;
		s_tem = s_tem | temp[0];
	
		s_tem = s_tem & 4095;
	
		if( (s_tem & 2048) == 2048 )	{
			s_tem = (s_tem^4095) & 4095;
			temp_trans[index] = -1*(s_tem+1) * 0.0625;
		}	/* negative */	
		else
			temp_trans[index] = s_tem * 0.0625;
		
}





void MUX_18B20_OUT_Read_Temperaure_Skip_7(uint8_t *temp, float *temp_trans, uint8_t index) 
{
		short s_tem;
	
	  MUX_18B20_OUT_Rst();	   
		MUX_18B20_OUT_Presence();	 
		MUX_18B20_OUT_Write_Byte(SKIP_ROM);				
		MUX_18B20_OUT_Write_Byte(CONVERT_T);
		
		Delay_us(8000);
	
	  MUX_18B20_OUT_Rst();	   
		MUX_18B20_OUT_Presence();	 
		MUX_18B20_OUT_Write_Byte(SKIP_ROM);
	  MUX_18B20_OUT_Write_Byte(READ_SCRATCHPAD);

		temp[0] = MUX_18B20_OUT_Read_Byte();
		temp[1] = MUX_18B20_OUT_Read_Byte();
		
		s_tem = temp[1]<<8;
		s_tem = s_tem | temp[0];
	
		s_tem = s_tem & 4095;
	
		if( (s_tem & 2048) == 2048 )	{
			s_tem = (s_tem^4095) & 4095;
			temp_trans[index] = -1*(s_tem+1) * 0.0625;
		}	/* negative */	
		else
			temp_trans[index] = s_tem * 0.0625;
		
}


void MUX_18B20_OUT_Read_Temperaure_Skip_47(uint8_t *temp, float *temp_trans, uint8_t index) 
{
		short s_tem;
		
		MUX_18B20_OUT_Rst();	   
		MUX_18B20_OUT_Presence();	 
		MUX_18B20_OUT_Write_Byte(SKIP_ROM);				
		MUX_18B20_OUT_Write_Byte(CONVERT_T);
		
		Delay_us(8000);
	
	  MUX_18B20_OUT_Rst();	   
		MUX_18B20_OUT_Presence();	 
		MUX_18B20_OUT_Write_Byte(SKIP_ROM);
	  MUX_18B20_OUT_Write_Byte(READ_SCRATCHPAD);

		temp[0] = MUX_18B20_OUT_Read_Byte();
		temp[1] = MUX_18B20_OUT_Read_Byte();
		
		s_tem = temp[1]<<8;
		s_tem = s_tem | temp[0];
	
		s_tem = s_tem & 4095;
	
		if( (s_tem & 2048) == 2048 )	{
			s_tem = (s_tem^4095) & 4095;
			temp_trans[index] = -1*(s_tem+1) * 0.0625;
		}	/* negative */	
		else
			temp_trans[index] = s_tem * 0.0625;
		
}




uint8_t DQ_SearchROM(uint8_t (*pID)[8],uint8_t Num, uint8_t type)  
{   
    unsigned char k,l = 0,ConflictBit,m,n;  
    unsigned char BUFFER[MAXNUM_SWITCH_18B20_OUT] = {0};  
    unsigned char ss[64];
		unsigned char s = 0;  
    uint8_t num = 0;
		int ii, jj;
		uint8_t serial[8];
	  
		do  
    {  
        //Delay_us(1000);
			  DQ_Rst(type);
				DQ_Presence(type);
        DQ_Write_Byte(SEARCH_ROM, type);	   
			     
				for(m=0; m<8; m++)  
        {    
            for(n=0; n<8; n++)  
            {  
                k = DQ_Read2Bit(type);		//read two bits
							
								k = k&0x03;  
                s = s>>1;  
                
								if(k == 0x02)							//0000 0010, if get data of 0
                {             
                    DQ_Write_Bit(0, type);  //write 0, let devices of 0 on bus response
                    ss[(m*8+n)]=0;
									  //printf("SEARCH_ROM: byte: %d bit %d, hit 0\r\n",m, n);
                }  
                else if(k == 0x01)				//0000 0001, if get data of 1
                {  
                    s = s|0x80;  
                    DQ_Write_Bit(1, type);  //write 1, let devices of 1 on bus response   
                    ss[(m*8+n)] = 1;  
									  //printf("SEARCH_ROM: byte: %d bit %d, hit 1\r\n",m, n);
                }  
                else if(k == 0x00)  //if get 00, then there is confliction, needs to check  
                {                
                    ConflictBit = m*8+n+1;                   
                    
										if(ConflictBit > BUFFER[l])  //if conflict bit greater than top of stack, then write 0   
                    {                         
                        DQ_Write_Bit(0, type);  
                        ss[(m*8+n)] = 0;                                                
                        BUFFER[++l] = ConflictBit;                         
											  //printf("SEARCH_ROM: byte: %d bit %d, conflist choose branch 0\r\n",m, n);
                    }  
                    else if(ConflictBit < BUFFER[l])  //if conflict bit less than top of stack, then write previous data
                    {  
                        s = s|((ss[(m*8+n)]&0x01)<<7);  
                        DQ_Write_Bit(ss[(m*8+n)], type);  
											  //printf("SEARCH_ROM: byte: %d bit %d, conflist choose branch %d\r\n",m, n,ss[(m*8+n)]);
                    }  
                    else if(ConflictBit == BUFFER[l])  //if conflict bit equal to top of stack, then write 1
                    {  
                        s = s|0x80;  
                        DQ_Write_Bit(1, type);  
                        ss[(m*8+n)] = 1;  
                        l = l-1;  
											  //printf("SEARCH_ROM: byte: %d bit %d, conflist choose branch 1\r\n",m, n);
                    }  
                }  
                else  //if get 0x03(0000 0011), then there's no device on bus
                {  
									  printf("SEARCH_ROM: byte: %d bit %d, got 0x03, device not exist\r\n",m,n);
                    return num;  //search finish, return number of devices
                }
            }  
            pID[num][m] = s;
						s = 0;
        }  
        num = num+1;
				
//				DQ_Write_Byte(READ_SCRATCHPAD, type); 
//  
//			for(i=0; i<9; i++) {
//				serial[i] = DQ_Read_Byte(type); 
//				printf("\r\n Scratchpad byte %d : %2x\r\n",i, serial[i]);
//			}
				
    }  
    while(BUFFER[l] != 0&&(num < MAXNUM_SWITCH_18B20_OUT));   
    
		Delay_us(800);
		
//		DQ_Write_Byte(READ_SCRATCHPAD, type); 
//  
//		for(i=0; i<9; i++) {
//			serial[i] = DQ_Read_Byte(type); 
//			printf("\r\n Scratchpad byte %d : %2x\r\n",i, serial[i]);
//		}

			
		
		for(ii=0;ii<num;ii++) {
			printf("\r\nROM#%d:",ii+1);
			for(jj=0;jj<8;jj++) {
				printf("0x%2x, ",pID[ii][jj]);
			}
		}
		//DQ_Write_Byte(RECALL_E2, type);
	//DQ_Rst(type);
	//DQ_Presence(type);
  //DQ_Write_Byte(SKIP_ROM, type);
  //DQ_Write_Byte(READ_USER_EXT, type);
		
    return num;     //return number of devices
}

uint8_t DQ_SearchROM_Write_Scratchpad(uint8_t (*pID)[8],uint8_t Num, uint8_t type, uint8_t TH,uint8_t TL,uint8_t CFG)  
{   
    unsigned char k,l = 0,ConflictBit,m,n;  
    unsigned char BUFFER[MAXNUM_SWITCH_18B20_OUT] = {0};  
    unsigned char ss[64];
		unsigned char s = 0;  
    uint8_t num = 0;
		int ii, jj;
		uint8_t serial[8];
	  
		do  
    {  
        //Delay_us(1000);
			  DQ_Rst(type);
				DQ_Presence(type);
        DQ_Write_Byte(SEARCH_ROM, type);	   
			     
				for(m=0; m<8; m++)  
        {    
            for(n=0; n<8; n++)  
            {  
                k = DQ_Read2Bit(type);		//read two bits
							
								k = k&0x03;  
                s = s>>1;  
                
								if(k == 0x02)							//0000 0010, if get data of 0
                {             
                    DQ_Write_Bit(0, type);  //write 0, let devices of 0 on bus response
                    ss[(m*8+n)]=0;
									  //printf("SEARCH_ROM: byte: %d bit %d, hit 0\r\n",m, n);
                }  
                else if(k == 0x01)				//0000 0001, if get data of 1
                {  
                    s = s|0x80;  
                    DQ_Write_Bit(1, type);  //write 1, let devices of 1 on bus response   
                    ss[(m*8+n)] = 1;  
									  //printf("SEARCH_ROM: byte: %d bit %d, hit 1\r\n",m, n);
                }  
                else if(k == 0x00)  //if get 00, then there is confliction, needs to check  
                {                
                    ConflictBit = m*8+n+1;                   
                    
										if(ConflictBit > BUFFER[l])  //if conflict bit greater than top of stack, then write 0   
                    {                         
                        DQ_Write_Bit(0, type);  
                        ss[(m*8+n)] = 0;                                                
                        BUFFER[++l] = ConflictBit;                         
											  //printf("SEARCH_ROM: byte: %d bit %d, conflist choose branch 0\r\n",m, n);
                    }  
                    else if(ConflictBit < BUFFER[l])  //if conflict bit less than top of stack, then write previous data
                    {  
                        s = s|((ss[(m*8+n)]&0x01)<<7);  
                        DQ_Write_Bit(ss[(m*8+n)], type);  
											  //printf("SEARCH_ROM: byte: %d bit %d, conflist choose branch %d\r\n",m, n,ss[(m*8+n)]);
                    }  
                    else if(ConflictBit == BUFFER[l])  //if conflict bit equal to top of stack, then write 1
                    {  
                        s = s|0x80;  
                        DQ_Write_Bit(1, type);  
                        ss[(m*8+n)] = 1;  
                        l = l-1;  
											  //printf("SEARCH_ROM: byte: %d bit %d, conflist choose branch 1\r\n",m, n);
                    }  
                }  
                else  //if get 0x03(0000 0011), then there's no device on bus
                {  
									  printf("SEARCH_ROM: byte: %d bit %d, got 0x03, device not exist\r\n",m,n);
                    return num;  //search finish, return number of devices
                }
            }  
            pID[num][m] = s;
						s = 0;
        }  
        num = num+1;
				
//				DQ_Write_Byte(READ_SCRATCHPAD, type); 
//  
//			for(i=0; i<9; i++) {
//				serial[i] = DQ_Read_Byte(type); 
//				printf("\r\n Scratchpad byte %d : %2x\r\n",i, serial[i]);
//			}
				
    }  
    while(BUFFER[l] != 0&&(num < MAXNUM_SWITCH_18B20_OUT));   
    
		DQ_Write_Byte(WRITE_SCRATCHPAD, type); 
		DQ_Write_Byte(TH, type); 
		DQ_Write_Byte(TL, type); 
		DQ_Write_Byte(CFG, type);		
    return num;     //return number of devices
}

uint8_t DQ_SearchROM_Read_Scratchpad(uint8_t (*pID)[8],uint8_t Num, uint8_t type, uint8_t *serial)  
{   
    unsigned char k,l = 0,ConflictBit,m,n,i;  
    unsigned char BUFFER[MAXNUM_SWITCH_18B20_OUT] = {0};  
    unsigned char ss[64];
		unsigned char s = 0;  
    uint8_t num = 0;
		int ii, jj;
	  
		do  
    {  
			  DQ_Rst(type);
				DQ_Presence(type);
        DQ_Write_Byte(SEARCH_ROM, type);	   
			     
				for(m=0; m<8; m++)  
        {    
            for(n=0; n<8; n++)  
            {  
                k = DQ_Read2Bit(type);		//read two bits
							
								k = k&0x03;  
                s = s>>1;  
                
								if(k == 0x02)							//0000 0010, if get data of 0
                {             
                    DQ_Write_Bit(0, type);  //write 0, let devices of 0 on bus response
                    ss[(m*8+n)]=0;
									  //printf("SEARCH_ROM: byte: %d bit %d, hit 0\r\n",m, n);
                }  
                else if(k == 0x01)				//0000 0001, if get data of 1
                {  
                    s = s|0x80;  
                    DQ_Write_Bit(1, type);  //write 1, let devices of 1 on bus response   
                    ss[(m*8+n)] = 1;  
									  //printf("SEARCH_ROM: byte: %d bit %d, hit 1\r\n",m, n);
                }  
                else if(k == 0x00)  //if get 00, then there is confliction, needs to check  
                {                
                    ConflictBit = m*8+n+1;                   
                    
										if(ConflictBit > BUFFER[l])  //if conflict bit greater than top of stack, then write 0   
                    {                         
                        DQ_Write_Bit(0, type);  
                        ss[(m*8+n)] = 0;                                                
                        BUFFER[++l] = ConflictBit;                         
											  //printf("SEARCH_ROM: byte: %d bit %d, conflist choose branch 0\r\n",m, n);
                    }  
                    else if(ConflictBit < BUFFER[l])  //if conflict bit less than top of stack, then write previous data
                    {  
                        s = s|((ss[(m*8+n)]&0x01)<<7);  
                        DQ_Write_Bit(ss[(m*8+n)], type);  
											  //printf("SEARCH_ROM: byte: %d bit %d, conflist choose branch %d\r\n",m, n,ss[(m*8+n)]);
                    }  
                    else if(ConflictBit == BUFFER[l])  //if conflict bit equal to top of stack, then write 1
                    {  
                        s = s|0x80;  
                        DQ_Write_Bit(1, type);  
                        ss[(m*8+n)] = 1;  
                        l = l-1;  
											  //printf("SEARCH_ROM: byte: %d bit %d, conflist choose branch 1\r\n",m, n);
                    }  
                }  
                else  //if get 0x03(0000 0011), then there's no device on bus
                {  
									  printf("SEARCH_ROM: byte: %d bit %d, got 0x03, device not exist\r\n",m,n);
                    return num;  //search finish, return number of devices
                }
            }  
            pID[num][m] = s;
						s = 0;
        }  
        num = num+1;		
    }  
    while(BUFFER[l] != 0&&(num < MAXNUM_SWITCH_18B20_OUT));   
    
		Delay_us(800);
		
		DQ_Write_Byte(READ_SCRATCHPAD, type); 
  
		for(i=0; i<9; i++) {
			serial[i] = DQ_Read_Byte(type); 
			//printf("\r\n Scratchpad byte %d : %2x\r\n",i, serial[i]);
		}
    return num;     //return number of devices
}


uint8_t DQ_Alarm_SearchROM(uint8_t (*pID)[8],uint8_t Num, uint8_t type)  
{   
    unsigned char k,l = 0,ConflictBit,m,n;  
    unsigned char BUFFER[MAXNUM_SWITCH_18B20_OUT] = {0};  
    unsigned char ss[64];
		unsigned char s = 0;  
    uint8_t num = 0;      
	  
		do  
    {  
        DQ_Rst(type);
				DQ_Presence(type);
        DQ_Write_Byte(ALARM_SEARCH, type);	   
			     
				for(m=0; m<8; m++)  
        {    
            for(n=0; n<8; n++)  
            {  
                k = DQ_Read2Bit(type);		//read two bits
							
								k = k&0x03;  
                s = s>>1;  
                
								if(k == 0x02)							//0000 0010, if get data of 0
                {             
                    DQ_Write_Bit(0, type);  //write 0, let devices of 0 on bus response
                    ss[(m*8+n)]=0;
									  //printf("SEARCH_ROM: byte: %d bit %d, hit 0\r\n",m, n);
                }  
                else if(k == 0x01)				//0000 0001, if get data of 1
                {  
                    s = s|0x80;  
                    DQ_Write_Bit(1, type);  //write 1, let devices of 1 on bus response   
                    ss[(m*8+n)] = 1;  
									  //printf("SEARCH_ROM: byte: %d bit %d, hit 1\r\n",m, n);
                }  
                else if(k == 0x00)  //if get 00, then there is confliction, needs to check  
                {                
                    ConflictBit = m*8+n+1;                   
                    
										if(ConflictBit > BUFFER[l])  //if conflict bit greater than top of stack, then write 0   
                    {                         
                        DQ_Write_Bit(0, type);  
                        ss[(m*8+n)] = 0;                                                
                        BUFFER[++l] = ConflictBit;                         
											  //printf("SEARCH_ROM: byte: %d bit %d, conflist choose branch 0\r\n",m, n);
                    }  
                    else if(ConflictBit < BUFFER[l])  //if conflict bit less than top of stack, then write previous data
                    {  
                        s = s|((ss[(m*8+n)]&0x01)<<7);  
                        DQ_Write_Bit(ss[(m*8+n)], type);  
											  //printf("SEARCH_ROM: byte: %d bit %d, conflist choose branch %d\r\n",m, n,ss[(m*8+n)]);
                    }  
                    else if(ConflictBit == BUFFER[l])  //if conflict bit equal to top of stack, then write 1
                    {  
                        s = s|0x80;  
                        DQ_Write_Bit(1, type);  
                        ss[(m*8+n)] = 1;  
                        l = l-1;  
											  //printf("SEARCH_ROM: byte: %d bit %d, conflist choose branch 1\r\n",m, n);
                    }  
                }  
                else  //if get 0x03(0000 0011), then there's no device on bus
                {  
									  printf("SEARCH_ROM: byte: %d bit %d, got 0x03, device not exist\r\n",m,n);
                    return num;  //search finish, return number of devices
                }
            }  
            pID[num][m] = s;
						s = 0;
        }  
        num = num+1;
    }  
    while(BUFFER[l] != 0&&(num < MAXNUM_SWITCH_18B20_OUT));   
      
    return num;     //return number of devices
}


void DQ_Read_Scrpad(uint8_t *serial, uint8_t type)  
{
  uint8_t i;

	DQ_Rst(type);
	DQ_Presence(type);
  DQ_Write_Byte(SKIP_ROM, type); 
	DQ_Write_Byte(READ_SCRATCHPAD, type); 
  
	for(i=0; i<9; i++) {
     serial[i] = DQ_Read_Byte(type); 
		 //printf("\r\n Scratchpad byte %d : %02x\r\n",i, serial[i]);
	}
	
	//for(i=0; i<9; i++) {
     //serial[i] = DQ_Read_Byte(type); 
		 //printf("\r\n Scratchpad byte %d : %02x\r\n",i, serial[i]);
	//}
	
	if(Calcrc_byte(serial,8) == serial[8]) {
		//printf("\r\nSCR CRC right.\r\n");
	}
	else {
		printf("\r\nSCR CRC wrong.\r\n");
		printf("\r\n Scratchpad crc byte read is : %02x\r\n", serial[8]);
		printf("\r\n Scratchpad crc byte calculate is : %02x\r\n", Calcrc_byte(serial,8));
	}
}

void DQ_Read_Scrpad_Ext(uint8_t *serial, uint8_t type)  
{
  uint8_t i;
  DQ_Rst(type);
  DQ_Presence(type);
  DQ_Write_Byte(SKIP_ROM, type); 
  DQ_Write_Byte(READ_SCRATCHPAD_EXT, type); 
  
	for(i=0; i<5; i++) {
     serial[i] = DQ_Read_Byte(type); 
		 //printf("\r\n Scratchpad Extend byte %d : %2x\r\n",i, serial[i]);
	}	
}

void DQ_Read_User_Ext(uint8_t *serial, uint8_t type)  
{
  uint8_t i;
  DQ_Rst(type);
  DQ_Presence(type);
  DQ_Write_Byte(SKIP_ROM, type); 
  DQ_Write_Byte(READ_USER_EXT, type); 
  
	for(i=0; i<5; i++) {
     serial[i] = DQ_Read_Byte(type); 
		 //printf("\r\n User Extend byte %d : %2x\r\n",i, serial[i]);
	}	
}

void DQ_Read_Rom_Code(uint8_t *serial, uint8_t type)  
{
  uint8_t i;

  DQ_Rst(type);
  DQ_Presence(type);
	
//	printf("\r ready to READROM \n");
	DQ_Write_Byte(READ_ROM, type); 
  
//	printf("\r 33H sent \n");
	
	for(i=0; i<8; i++) {
     serial[i] = DQ_Read_Byte(type); 
		//Delay_us(500);
	//	printf("\r Loop %d \n",i);
		 //printf("\r\n ROM byte %d : %02x\r",i, serial[i]);
		//printf("%2x",serial[i]);
	}	
	
	//for(i=0; i<8; i++) {
     //serial[i] = DQ_Read_Byte(type); 
		 //printf("\r\n ROM byte %d : %2x\r\n",i, serial[i]);
	//}
	
	if(Calcrc_byte(serial,7) == serial[7]) {
		printf("\r\nROM CRC right.\r\n");
	}
	else {
		printf("\r\nROM CRC wrong.\r\n");
	}
	
	//DQ_Rst(type);
	//DQ_Presence(type);
	//DQ_Write_Byte(SKIP_ROM, type);
	//DQ_Write_Byte(RECALL_E2, type);

}

void DQ_Read_Rom_Code_for_match(uint8_t *serial, uint8_t type)  
{
  uint8_t i;

  DQ_Rst(type);
  DQ_Presence(type);
	
//	printf("\r ready to READROM \n");
	DQ_Write_Byte(READ_ROM, type); 
  
//	printf("\r 33H sent \n");
	
	for(i=0; i<8; i++) {
     serial[i] = DQ_Read_Byte(type); 
		//Delay_us(500);
	//	printf("\r Loop %d \n",i);
		 //printf("\r\n ROM byte %d : %2x\r",i, serial[i]);
		//printf("%2x",serial[i]);
	}	
	
	//for(i=0; i<8; i++) {
     //serial[i] = DQ_Read_Byte(type); 
		 //printf("\r\n ROM byte %d : %2x\r\n",i, serial[i]);
	//}
	
	//DQ_Rst(type);
	//DQ_Presence(type);
	//DQ_Write_Byte(SKIP_ROM, type);
	//DQ_Write_Byte(RECALL_E2, type);

}



void DQ_Read_Parameters(uint8_t *serial, uint8_t type)  
{
  uint8_t i;
  DQ_Rst(type);
  DQ_Presence(type);
	DQ_Write_Byte(SKIP_ROM, type); 
  DQ_Write_Byte(READ_PARAMETERS, type); 
  
	for(i=0; i<9; i++) {
     serial[i] = DQ_Read_Byte(type); 
		 //printf("\r\n Parameter byte %d : %02x\r",i, serial[i]);
		//printf("%2x",serial[i]);
	}	
}

void DQ_Read_Parameters_match(uint8_t *serial, uint8_t type)  
{
  uint8_t i;
	uint8_t rom[8];
	
	//DQ_Read_Rom_Code(rom, type);
	DQ_Read_Rom_Code_for_match(rom, type);
  
	DQ_Rst(type);
  DQ_Presence(type);
  DQ_Write_Byte(MATCH_ROM, type);
		
	for(i=0; i<8; i++) {
		DQ_Write_Byte(rom[i], type);
	} 
  
	
	DQ_Write_Byte(READ_PARAMETERS, type); 
  
	for(i=0; i<8; i++) {
     serial[i] = DQ_Read_Byte(type); 
		 printf("\r\n Parameter byte %d : %2x\r",i, serial[i]);
		//printf("%2x",serial[i]);
	}	
}

void DQ_Read_Parameters_match2(uint8_t *serial, uint8_t type, uint8_t *rom)  
{
  uint8_t i;
	
	DQ_Rst(type);
  DQ_Presence(type);
  DQ_Write_Byte(MATCH_ROM, type);
		
	for(i=0; i<8; i++) {
		DQ_Write_Byte(rom[i], type);
	} 
  Delay_us(20);
	
//	//DQ_Write_Byte(READ_PARAMETERS, type);
//	DQ_Rst(type);
//  DQ_Presence(type);
//  DQ_Write_Byte(READ_ROM, type);
//  
//	for(i=0; i<8; i++) {
//     serial[i] = DQ_Read_Byte(type); 
//		 //printf("\r\n Parameter byte %d : %2x\r",i, serial[i]);
//		 printf("\r\n ROM byte %d : %2x\r",i, serial[i]);
//		//printf("%2x",serial[i]);
//	}	
}


void DQ_Read_Scrpad_match2(uint8_t *serial, uint8_t type, uint8_t *rom)  
{
  uint8_t i;
  
	DQ_Rst(type);
  DQ_Presence(type);
  DQ_Write_Byte(MATCH_ROM, type);
		
	for(i=0; i<8; i++) {
		DQ_Write_Byte(rom[i], type);
	} 
	DQ_Write_Byte(READ_SCRATCHPAD, type); 
  
	for(i=0; i<9; i++) {
     serial[i] = DQ_Read_Byte(type); 
		 //printf("\r\n Scratchpad byte %d : %2x\r",i, serial[i]);
	}	
}

void DQ_Read_User_Ext_match2(uint8_t *serial, uint8_t type, uint8_t *rom)  
{
  uint8_t i;
  
	DQ_Rst(type);
  DQ_Presence(type);
  DQ_Write_Byte(MATCH_ROM, type);
		
	for(i=0; i<8; i++) {
		DQ_Write_Byte(rom[i], type);
	} 
	DQ_Write_Byte(READ_USER_EXT, type); 
  
	for(i=0; i<5; i++) {
     serial[i] = DQ_Read_Byte(type); 
		 //printf("\r\n Scratchpad byte %d : %2x\r",i, serial[i]);
	}	
}

void DQ_Read_Scrpad_Ext_match2(uint8_t *serial, uint8_t type, uint8_t *rom)  
{
  uint8_t i;
  
	DQ_Rst(type);
  DQ_Presence(type);
  DQ_Write_Byte(MATCH_ROM, type);
		
	for(i=0; i<8; i++) {
		DQ_Write_Byte(rom[i], type);
	} 
	DQ_Write_Byte(READ_SCRATCHPAD_EXT, type); 
  
	for(i=0; i<5; i++) {
     serial[i] = DQ_Read_Byte(type); 
		 //printf("\r\n Scratchpad byte %d : %2x\r",i, serial[i]);
	}	
}

void DQ_Check_Power_Supply(uint8_t type)
{
		char mode;
		DQ_Rst(type);
		DQ_Presence(type);
    DQ_Write_Byte(SKIP_ROM, type);  
    DQ_Write_Byte(READ_POWER_SUPPLY, type);
	
		mode = DQ_Read_Bit(type);
		
		if(mode != 1) {
			printf("ERROR: Power supply mode check error!!!");
		}
		else {
			printf("PASS: Power supply mode check pass!");
		}
}

void DQ_Recall_EE(uint8_t type)
{
		
		DQ_Rst(type);
		DQ_Presence(type);
    DQ_Write_Byte(SKIP_ROM, type);  
    DQ_Write_Byte(RECALL_E2, type); 
	  Delay_us(100000);
	
}


void DQ_Recall_PAGE0_RES(uint8_t type)
{
		
		DQ_Rst(type);
		DQ_Presence(type);
    DQ_Write_Byte(SKIP_ROM, type);  
    DQ_Write_Byte(RECALL_PAGE0_RES, type); 
	  Delay_us(100000);
	
}


void DQ_Recall_PAGE1(uint8_t type)
{
		
		DQ_Rst(type);
		DQ_Presence(type);
    DQ_Write_Byte(SKIP_ROM, type);  
    DQ_Write_Byte(RECALL_PAGE1, type); 	
	
			
		Delay_us(30000);
}



void DQ_Copy_PAGE0(uint8_t type)  
{    
		uint8_t done = 0;
	  DQ_Rst(type);
		DQ_Presence(type);
    DQ_Write_Byte(SKIP_ROM, type);  
    DQ_Write_Byte(COPY_PAGE0, type); 
		
		do{
			done = DUT_DQ_OUT_Read_Bit();
		}while(done != 1);
}


void DQ_Copy_PAGE1(uint8_t type)  
{    
		uint8_t done = 0;
	  DQ_Rst(type);
		DQ_Presence(type);
    DQ_Write_Byte(SKIP_ROM, type);  
    DQ_Write_Byte(COPY_PAGE1, type);
		
		do{
			done = DUT_DQ_OUT_Read_Bit();
		}while(done != 1);
}



void DQ_Write_Scratchpad(uint8_t TH,uint8_t TL,uint8_t CFG, uint8_t type)  
{  
		DQ_Rst(type);
		DQ_Presence(type);
    DQ_Write_Byte(SKIP_ROM, type);  
    DQ_Write_Byte(WRITE_SCRATCHPAD, type); 
		DQ_Write_Byte(TH, type); 
		DQ_Write_Byte(TL, type); 
		DQ_Write_Byte(CFG, type);		      
}

void DQ_Write_Scratchpad_Match(uint8_t TH,uint8_t TL,uint8_t CFG, uint8_t type, uint8_t *rom)  
{  
		uint8_t i;
		DQ_Rst(type);
		DQ_Presence(type);
		DQ_Write_Byte(MATCH_ROM, type);
		for(i=0; i<8; i++) {
			DQ_Write_Byte(rom[i], type);
		}  
    DQ_Write_Byte(WRITE_SCRATCHPAD, type); 
		DQ_Write_Byte(TH, type); 
		DQ_Write_Byte(TL, type); 
		DQ_Write_Byte(CFG, type);		      
}

void DQ_Write_User(uint8_t UDF0,uint8_t UDF1,uint8_t UDF2, uint8_t type)  
{  
		DQ_Rst(type);
		DQ_Presence(type);
    DQ_Write_Byte(SKIP_ROM, type);  
    DQ_Write_Byte(WRITE_USER, type); 
		DQ_Write_Byte(UDF0, type); 
		DQ_Write_Byte(UDF1, type); 
		DQ_Write_Byte(UDF2, type);		      
}

void DQ_Write_User_Match(uint8_t UDF0,uint8_t UDF1,uint8_t UDF2, uint8_t type, uint8_t *rom)  
{  
		uint8_t i;
		DQ_Rst(type);
		DQ_Presence(type);
		DQ_Write_Byte(MATCH_ROM, type);
		for(i=0; i<8; i++) {
			DQ_Write_Byte(rom[i], type);
		}  
    DQ_Write_Byte(WRITE_USER, type); 
		DQ_Write_Byte(UDF0, type); 
		DQ_Write_Byte(UDF1, type); 
		DQ_Write_Byte(UDF2, type);		      
}

void DQ_Write_Scratchpad_Ext(uint8_t TTHRES_HI,uint8_t TTHRES_LO, uint8_t ADC_COEFF_EXT0,uint8_t ADC_COEFF_EXT1,uint8_t ADC_COEFF_EXT2, uint8_t type)  
{  
		DQ_Rst(type);
		DQ_Presence(type);
    DQ_Write_Byte(SKIP_ROM, type);  
    DQ_Write_Byte(WRITE_SCRATCHPAD_EXT, type); 
		DQ_Write_Byte(TTHRES_HI, type); 
		DQ_Write_Byte(TTHRES_LO, type);
		DQ_Write_Byte(ADC_COEFF_EXT0, type); 
		DQ_Write_Byte(ADC_COEFF_EXT1, type); 
		DQ_Write_Byte(ADC_COEFF_EXT2, type);	
}

void DQ_Write_Scratchpad_Ext_Match(uint8_t TTHRES_HI,uint8_t TTHRES_LO, uint8_t ADC_COEFF_EXT0,uint8_t ADC_COEFF_EXT1,uint8_t ADC_COEFF_EXT2, uint8_t type, uint8_t *rom)  
{  
		uint8_t i;
		DQ_Rst(type);
		DQ_Presence(type);
		DQ_Write_Byte(MATCH_ROM, type);
		for(i=0; i<8; i++) {
			DQ_Write_Byte(rom[i], type);
		}  
    DQ_Write_Byte(WRITE_SCRATCHPAD_EXT, type); 
		DQ_Write_Byte(TTHRES_HI, type); 
		DQ_Write_Byte(TTHRES_LO, type);
		DQ_Write_Byte(ADC_COEFF_EXT0, type); 
		DQ_Write_Byte(ADC_COEFF_EXT1, type); 
		DQ_Write_Byte(ADC_COEFF_EXT2, type);	
}

void DQ_Write_User_Ext(uint8_t UDF_EXT0,uint8_t UDF_EXT1,uint8_t UDF_EXT2,uint8_t UDF_EXT3,uint8_t UDF_EXT4, uint8_t type)  
{  
		DQ_Rst(type);
		DQ_Presence(type);
    DQ_Write_Byte(SKIP_ROM, type);  
    DQ_Write_Byte(WRITE_USER_EXT, type); 
		DQ_Write_Byte(UDF_EXT0, type); 
		DQ_Write_Byte(UDF_EXT1, type); 
		DQ_Write_Byte(UDF_EXT2, type);
		DQ_Write_Byte(UDF_EXT3, type); 
		DQ_Write_Byte(UDF_EXT4, type);	
}

void DQ_Write_User_Ext_Match(uint8_t UDF_EXT0,uint8_t UDF_EXT1,uint8_t UDF_EXT2,uint8_t UDF_EXT3,uint8_t UDF_EXT4, uint8_t type, uint8_t *rom)  
{  
		uint8_t i;
		DQ_Rst(type);
		DQ_Presence(type);
		DQ_Write_Byte(MATCH_ROM, type);
		for(i=0; i<8; i++) {
			DQ_Write_Byte(rom[i], type);
		}  
    DQ_Write_Byte(WRITE_USER_EXT, type); 
		DQ_Write_Byte(UDF_EXT0, type); 
		DQ_Write_Byte(UDF_EXT1, type); 
		DQ_Write_Byte(UDF_EXT2, type);
		DQ_Write_Byte(UDF_EXT3, type); 
		DQ_Write_Byte(UDF_EXT4, type);	
}

void DQ_Write_Parameters(uint8_t TTRIM, uint8_t ANA_CONF,uint8_t ADC_CONF,uint8_t ADC_COEFF0,uint8_t ADC_COEFF1,uint8_t ADC_COEFF2,uint8_t ANA_CAL0,uint8_t ANA_CAL1, uint8_t type)  
{  
		DQ_Rst(type);
		DQ_Presence(type);
	  // Delay_us(1000);
    DQ_Write_Byte(SKIP_ROM, type);
		DQ_Write_Byte(WRITE_PARAMETERS, type);   
		DQ_Write_Byte(TTRIM, type); 
		DQ_Write_Byte(ANA_CONF, type); 
		DQ_Write_Byte(ADC_CONF, type);
		DQ_Write_Byte(ADC_COEFF0, type); 
		DQ_Write_Byte(ADC_COEFF1, type); 
		DQ_Write_Byte(ADC_COEFF2, type);
		DQ_Write_Byte(ANA_CAL0, type);
		DQ_Write_Byte(ANA_CAL1, type); 
}

void DQ_Write_Parameters_3byte(uint8_t TTRIM, uint8_t ANA_CONF,uint8_t ADC_CONF,uint8_t type)  
{  
		DQ_Rst(type);
		DQ_Presence(type);
	  // Delay_us(1000);
    DQ_Write_Byte(SKIP_ROM, type);
		DQ_Write_Byte(WRITE_PARAMETERS, type);   
		DQ_Write_Byte(TTRIM, type); 
		DQ_Write_Byte(ANA_CONF, type); 
		DQ_Write_Byte(ADC_CONF, type);
		 
}



void DQ_Setup_ROM(uint8_t ROM0,uint8_t ROM1,uint8_t ROM2,uint8_t ROM3,uint8_t ROM4,uint8_t ROM5,uint8_t ROM6,uint8_t ROM7, uint8_t type)  
{  
		DQ_Rst(type);
		DQ_Presence(type);
    DQ_Write_Byte(SETUP_ROM, type);   
		DQ_Write_Byte(ROM0, type); 
		DQ_Write_Byte(ROM1, type); 
		DQ_Write_Byte(ROM2, type);
		DQ_Write_Byte(ROM3, type); 
		DQ_Write_Byte(ROM4, type); 
		DQ_Write_Byte(ROM5, type);
		DQ_Write_Byte(ROM6, type);   // Fixed mark
		DQ_Write_Byte(ROM7, type); 
}
	  



uint8_t CRC8_Cal(uint8_t *serial, uint8_t length) {
	uint8_t result = 0x00;
	uint8_t pDataBuf;
	uint8_t i;
	
	while(length--) {
		pDataBuf = *serial++;
		
		for(i=0;i<8;i++) {
			if((result^(pDataBuf))&0x01) {
				result ^= 0x18;
				result >>= 1;
				result |= 0x80;
			}
			else {
				result >>= 1;
			}
			pDataBuf >>= 1;
		}
			
	}
	return result;
}










	
uint8_t CRC8_1byte(uint8_t dat)
{
    uint8_t i;
	  uint8_t crc8 = 0;
	  for(i=0;i<8;i++)
	  {
		    if((crc8 ^ dat) & 0x01)
				{
				    crc8 ^= 0x18;
					  crc8 >>= 1;
					  crc8 |= 0x80;
				}
				else
				    crc8 >>= 1;				
		    dat >>= 1;
		}
		return crc8;
}


uint8_t Calcrc_byte(uint8_t *p,uint8_t len)
{
   uint8_t crc = 0;	
	 while(len--)
	 { 
	     crc = CRC8_1byte(crc^*p++);  
	 }
   return crc;
}

void Check_rw_scratchpad(void) {
		uint8_t serial[9], i;
		DQ_Write_Scratchpad(0xf1,0x2e,0x5f, DUT_DQ_OUT);
		DQ_Read_Scrpad(serial, DUT_DQ_OUT);
	
		if(serial[2] != 0xf1 || serial[3] != 0x2e || serial[4] != 0x5f) {
			printf("\r\nERROR: Scratchpad RW Check Error!!!\r\n");
			for(i=0; i<9; i++) { 
				printf("\r\n Scratchpad byte %d : %02x\r\n",i, serial[i]);
	    }
		}
		else {
			DQ_Write_Scratchpad(0xff,0xff,0xff, DUT_DQ_OUT);
			DQ_Read_Scrpad(serial, DUT_DQ_OUT);
	
			if(serial[2] != 0xff || serial[3] != 0xff || serial[4] != 0x7f) {
				printf("\r\nERROR: Scratchpad RW Check all 1 Error!!!\r\n");
				for(i=0; i<9; i++) { 
					printf("\r\n Scratchpad byte %d : %02x\r\n",i, serial[i]);
				}
			}
			else {
				DQ_Write_Scratchpad(0x00,0x00,0x00, DUT_DQ_OUT);
				DQ_Read_Scrpad(serial, DUT_DQ_OUT);
	
				if(serial[2] != 0x00 || serial[3] != 0x00 || serial[4] != 0x1f) {
					printf("\r\nERROR: Scratchpad RW Check all 0 Error!!!\r\n");
					for(i=0; i<9; i++) { 
						printf("\r\n Scratchpad byte %d : %02x\r\n",i, serial[i]);
					}
				}
				else {
					printf("\r\nPASS: Scratchpad RW Check Pass!!!\r\n");
				}
			}
		}
}

void Check_rw_user(void) {
		uint8_t serial[9], i;
		DQ_Write_User(0x4c,0xb5,0x6a, DUT_DQ_OUT);
		DQ_Read_Scrpad(serial, DUT_DQ_OUT);
	
		if(serial[5] != 0x4c || serial[6] != 0xb5 || serial[7] != 0x6a) {
			printf("\r\nERROR: User RW Check Error!!!\r\n");
			for(i=5; i<8; i++) {
				printf("\r\n User byte %d : %02x\r\n",i, serial[i]);
	    }
		}
		else {
			DQ_Write_User(0xff,0xff,0xff, DUT_DQ_OUT);
			DQ_Read_Scrpad(serial, DUT_DQ_OUT);
	
			if(serial[5] != 0xff || serial[6] != 0xff || serial[7] != 0xff) {
				printf("\r\nERROR: User RW Check all 1 Error!!!\r\n");
				for(i=5; i<8; i++) {
					printf("\r\n User byte %d : %02x\r\n",i, serial[i]);
				}
			}
			else {
				DQ_Write_User(0x00,0x00,0x00, DUT_DQ_OUT);
				DQ_Read_Scrpad(serial, DUT_DQ_OUT);
		
				if(serial[5] != 0x00 || serial[6] != 0x00 || serial[7] != 0x00) {
					printf("\r\nERROR: User RW Check all 0 Error!!!\r\n");
					for(i=6; i<8; i++) {
						printf("\r\n User byte %d : %02x\r\n",i, serial[i]);
					}
				}
				else {
					printf("\r\nPASS: User RW Check Pass!!!\r\n");
				}
			}
		}
}

void Check_rw_user_ext(void) {
		uint8_t serial[9], i;
		DQ_Write_User_Ext(0x97,0x88,0x79,0xa6,0x5b, DUT_DQ_OUT);
		DQ_Read_User_Ext(serial, DUT_DQ_OUT);
	
		if(serial[0] != 0x97 || serial[1] != 0x88 || serial[2] != 0x79 || serial[3] != 0xa6 || serial[4] != 0x5b) {
			printf("\r\nERROR: User Ext RW Check Error!!!\r\n");
			for(i=0; i<5; i++) {
				printf("\r\n User Ext byte %d : %02x\r\n",i, serial[i]);
	    }
		}
		else {
			DQ_Write_User_Ext(0xff,0xff,0xff,0xff,0xff, DUT_DQ_OUT);
			DQ_Read_User_Ext(serial, DUT_DQ_OUT);
		
			if(serial[0] != 0xff || serial[1] != 0xff || serial[2] != 0xff || serial[3] != 0xff || serial[4] != 0xff) {
				printf("\r\nERROR: User Ext RW Check all 1 Error!!!\r\n");
				for(i=0; i<5; i++) {
					printf("\r\n User Ext byte %d : %02x\r\n",i, serial[i]);
				}
			}
			else {
				DQ_Write_User_Ext(0x00,0x00,0x00,0x00,0x00, DUT_DQ_OUT);
				DQ_Read_User_Ext(serial, DUT_DQ_OUT);
			
				if(serial[0] != 0x00 || serial[1] != 0x00 || serial[2] != 0x00 || serial[3] != 0x00 || serial[4] != 0x00) {
					printf("\r\nERROR: User Ext RW Check all 1 Error!!!\r\n");
					for(i=0; i<5; i++) {
						printf("\r\n User Ext byte %d : %02x\r\n",i, serial[i]);
					}
				}
				else {
					printf("\r\nPASS: User Ext RW Check Pass!!!\r\n");
				}
			}
		}
}

void Check_rw_scratchpad_ext(void) {
		uint8_t serial[9], i;
		DQ_Write_Scratchpad_Ext(0xc4,0x3d,0xe2,0x1f,0x12, DUT_DQ_OUT);
		DQ_Read_Scrpad_Ext(serial, DUT_DQ_OUT);
	
		if(serial[0] != 0xc4 || serial[1] != 0x3d || serial[2] != 0xe2 || serial[3] != 0x1f || serial[4] != 0x12) {
			printf("\r\nERROR: Scratchpad Ext RW Check Error!!!\r\n");
			for(i=0; i<5; i++) {
				printf("\r\n Scratchpad Ext byte %d : %02x\r\n",i, serial[i]);
	    }
		}
		else {
			DQ_Write_Scratchpad_Ext(0xff,0xff,0xff,0xff,0xff, DUT_DQ_OUT);
			DQ_Read_Scrpad_Ext(serial, DUT_DQ_OUT);
		
			if(serial[0] != 0xff || serial[1] != 0xff || serial[2] != 0xff || serial[3] != 0xff || serial[4] != 0xff) {
				printf("\r\nERROR: Scratchpad Ext RW Check all 1 Error!!!\r\n");
				for(i=0; i<5; i++) {
					printf("\r\n Scratchpad Ext byte %d : %02x\r\n",i, serial[i]);
				}
			}
			else {
				DQ_Write_Scratchpad_Ext(0x00,0x00,0x00,0x00,0x00, DUT_DQ_OUT);
				DQ_Read_Scrpad_Ext(serial, DUT_DQ_OUT);
			
				if(serial[0] != 0x00 || serial[1] != 0x00 || serial[2] != 0x00 || serial[3] != 0x00 || serial[4] != 0x00) {
					printf("\r\nERROR: Scratchpad Ext RW Check all 0 Error!!!\r\n");
					for(i=0; i<5; i++) {
						printf("\r\n Scratchpad Ext byte %d : %02x\r\n",i, serial[i]);
					}
				}
				else {
					printf("\r\nPASS: Scratchpad Ext RW Check Pass!!!\r\n");
				}
			}
		}
}


void Check_rw_rom_code(void) {
		uint8_t serial[9], rom_ori[8], i;
		DQ_Read_Rom_Code(rom_ori, DUT_DQ_OUT);
	  DQ_Setup_ROM(0xfc,0xde,0xed,0xcf,0x1b,0xa2,0x39,0x84, DUT_DQ_OUT);
		DQ_Read_Rom_Code(serial, DUT_DQ_OUT);
	
		if(serial[0] != 0xfc || serial[1] != 0xde || serial[2] != 0xed || serial[3] != 0xcf || serial[4] != 0x1b || serial[5] != 0xa2 || serial[6] != 0x39 || serial[7] != 0x84) {
			printf("\r\nERROR: ROM Code RW Check Error!!!\r\n");
			for(i=0; i<8; i++) {
				printf("\r\n ROM Code byte %d : %02x\r\n",i, serial[i]);
	    }
		}
		else {
			DQ_Setup_ROM(0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, DUT_DQ_OUT);
			DQ_Read_Rom_Code(serial, DUT_DQ_OUT);
		
			if(serial[0] != 0xff || serial[1] != 0xff || serial[2] != 0xff || serial[3] != 0xff || serial[4] != 0xff || serial[5] != 0xff || serial[6] != 0xff || serial[7] != 0xff) {
				printf("\r\nERROR: ROM Code RW Check all 1 Error!!!\r\n");
				for(i=0; i<8; i++) {
					printf("\r\n ROM Code byte %d : %02x\r\n",i, serial[i]);
				}
			}
			else {
				DQ_Setup_ROM(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, DUT_DQ_OUT);
				DQ_Read_Rom_Code(serial, DUT_DQ_OUT);
			
				if(serial[0] != 0x00 || serial[1] != 0x00 || serial[2] != 0x00 || serial[3] != 0x00 || serial[4] != 0x00 || serial[5] != 0x00 || serial[6] != 0x00 || serial[7] != 0x00) {
					printf("\r\nERROR: ROM Code RW Check all 0 Error!!!\r\n");
					for(i=0; i<8; i++) {
						printf("\r\n ROM Code byte %d : %02x\r\n",i, serial[i]);
					}
				}
				else {
					printf("\r\nPASS: ROM Code RW Check Pass!!!\r\n");
				}
			}
		}
		DQ_Setup_ROM(rom_ori[0],rom_ori[1],rom_ori[2],rom_ori[3],rom_ori[4],rom_ori[5],rom_ori[6],rom_ori[7], DUT_DQ_OUT);
}

void Check_rw_parameters(void) {
		uint8_t serial[9], para_ori[9], i;
		DQ_Read_Parameters(para_ori, DUT_DQ_OUT);
	  DQ_Write_Parameters(0x57,0x66,0x75,0x48,0x93,0x2a,0xb1,0x0c, DUT_DQ_OUT);
		DQ_Read_Parameters(serial, DUT_DQ_OUT);
	
		if(serial[0] != 0x57 || serial[1] != 0x66 || serial[2] != 0x75 || serial[3] != 0x48 || serial[4] != 0x93 || serial[5] != 0x2a || serial[6] != 0xb1 || serial[7] != 0x0c || serial[8] != 0xa5) {
			printf("\r\nERROR: Parameters RW Check Error!!!\r\n");
			for(i=0; i<8; i++) {
				printf("\r\n Parameters byte %d : %02x\r\n",i, serial[i]);
	    }
		}
		else {
			DQ_Write_Parameters(0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, DUT_DQ_OUT);
			DQ_Read_Parameters(serial, DUT_DQ_OUT);
		
			if(serial[0] != 0xff || serial[1] != 0xff || serial[2] != 0xff || serial[3] != 0xff || serial[4] != 0xff || serial[5] != 0xff || serial[6] != 0xff || serial[7] != 0xff || serial[8] != 0xa5) {
				printf("\r\nERROR: Parameters RW Check all 1 Error!!!\r\n");
				for(i=0; i<8; i++) {
					printf("\r\n Parameters byte %d : %02x\r\n",i, serial[i]);
				}
			}
			else {
				DQ_Write_Parameters(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, DUT_DQ_OUT);
				DQ_Read_Parameters(serial, DUT_DQ_OUT);
			
				if(serial[0] != 0x00 || serial[1] != 0x00 || serial[2] != 0x00 || serial[3] != 0x00 || serial[4] != 0x00 || serial[5] != 0x00 || serial[6] != 0x00 || serial[7] != 0x00 || serial[8] != 0xa5) {
					printf("\r\nERROR: Parameters RW Check all 0 Error!!!\r\n");
					for(i=0; i<8; i++) {
						printf("\r\n Parameters byte %d : %02x\r\n",i, serial[i]);
					}
				}
				else {
					printf("\r\nPASS: Parameters RW Check Pass!!!\r\n");
				}
			}
		}
		DQ_Write_Parameters(para_ori[0],para_ori[1],para_ori[2],para_ori[3],para_ori[4],para_ori[5],para_ori[6],para_ori[6], DUT_DQ_OUT);
}

void Check_Search_ROM(void) {
		uint8_t serial[9];
		DQ_Setup_ROM(0x82,0xf1,0x1f,0xe2,0x2e,0xd3,0x3d,0xc4, DUT_DQ_OUT);
		if(DQ_SearchROM(ID_Buff,MAXNUM_SWITCH_18B20_OUT, DUT_DQ_OUT)==1) {
					if(ID_Buff[0][0] == 0x82 && ID_Buff[0][1] == 0xf1 && ID_Buff[0][2] == 0x1f && ID_Buff[0][3] == 0xe2 && ID_Buff[0][4] == 0x2e && ID_Buff[0][5] == 0xd3 && ID_Buff[0][6] == 0x3d && ID_Buff[0][7] == 0xc4) {
							printf("\r\nPASS: Search ROM Check Pass!!!\r\n");
					}
					else {
							printf("\r\nERROR: Search ROM Check Error!!!\r\n");
					}
		}
		else {
				printf("\r\nERROR: Search ROM Check Error!!!\r\n");
		}
}

void Check_Alarm_Search(void) {
		uint8_t serial[9];
		DQ_Write_Scratchpad(0x00,0x00,0x7f, DUT_DQ_OUT);
		DQ_Setup_ROM(0x39,0x4c,0xb5,0x5b,0xa6,0x6a,0x97,0x79, DUT_DQ_OUT);
		if(DQ_Alarm_SearchROM(ID_Buff,MAXNUM_SWITCH_18B20_OUT, DUT_DQ_OUT)==1) {
					if(ID_Buff[0][0] == 0x39 && ID_Buff[0][1] == 0x4c && ID_Buff[0][2] == 0xb5 && ID_Buff[0][3] == 0x5b && ID_Buff[0][4] == 0xa6 && ID_Buff[0][5] == 0x6a && ID_Buff[0][6] == 0x97 && ID_Buff[0][7] == 0x79) {
							DQ_Write_Scratchpad(0x7d,0xc9,0x7f, DUT_DQ_OUT);
							if(DQ_Alarm_SearchROM(ID_Buff,MAXNUM_SWITCH_18B20_OUT, DUT_DQ_OUT)==0) {
									printf("\r\nPASS: Alarm Search Check Pass!!!\r\n");
							}
							else {
									printf("\r\nERROR: Alarm Search (not alarm) Check Error!!!\r\n");
							}
					}
					else {
							printf("\r\nERROR: Alarm Search Check Error!!!\r\n");
					}
		}
		else {
				printf("\r\nERROR: Alarm Search (alarm) Check Error!!!\r\n");
		}
}

void Check_ConvertT(void) {
		if(DUT_DQ_OUT_Get_Temp() > 40 || DUT_DQ_OUT_Get_Temp() < 10) {
				printf("\r\nERROR: ConvertT Check Error!!!\r\n");
		}
		else {
				printf("\r\nPASS: ConvertT Check Pass!!!\r\n");
		}
}

void Check_Match_ROM(void) {
		uint8_t serial[9];
	  uint8_t rom[8] = {0x28,0x27,0x26,0x25,0x24,0x23,0x22,0x21};
		DQ_Setup_ROM(rom[0],rom[1],rom[2],rom[3],rom[4],rom[5],rom[6],rom[7], DUT_DQ_OUT);
		DQ_Write_Scratchpad_Match(0x00,0x01,0x02, DUT_DQ_OUT,rom);
		DQ_Write_User_Match(0x03,0x04,0x05, DUT_DQ_OUT, rom);
		DQ_Write_User_Ext_Match(0x06,0x07,0x08,0x09,0x0a, DUT_DQ_OUT,rom);
		DQ_Write_Scratchpad_Ext_Match(0x0b,0x0c,0x0d,0x0e,0x0f, DUT_DQ_OUT,rom);
		DQ_Read_Scrpad_match2(serial, DUT_DQ_OUT, rom);
		if(serial[2] == 0x00 && serial[3] == 0x01 && serial[4] == 0x1f && serial[5] == 0x03 && serial[6] == 0x04 && serial[7] == 0x05) {
				printf("\r\nPASS: Match ROM + RW Scratchpad Check Pass!!!\r\n");
		}
		else {
				printf("\r\nERROR: Match ROM + RW Scratchpad Check Error!!!\r\n");
		}
		DQ_Read_User_Ext_match2(serial, DUT_DQ_OUT, rom);
		if(serial[0] == 0x06 && serial[1] == 0x07 && serial[2] == 0x08 && serial[3] == 0x09 && serial[4] == 0x0a) {
				printf("\r\nPASS: Match ROM + RW User Ext Check Pass!!!\r\n");
		}
		else {
				printf("\r\nERROR: Match ROM + RW User Ext Check Error!!!\r\n");
		}
		DQ_Read_Scrpad_Ext_match2(serial, DUT_DQ_OUT, rom);
		if(serial[0] == 0x0b && serial[1] == 0x0c && serial[2] == 0x0d && serial[3] == 0x0e && serial[4] == 0x0f) {
				printf("\r\nPASS: Match ROM + RW Scratchpad Ext Check Pass!!!\r\n");
		}
		else {
				printf("\r\nERROR: Match ROM + RW Scratchpad Ext Check Error!!!\r\n");
		}
		DQ_Recall_EE(DUT_DQ_OUT);
		DQ_Recall_PAGE0_RES(DUT_DQ_OUT);
		DQ_Recall_PAGE1(DUT_DQ_OUT);
}

void Check_MTP(void) {
		uint8_t serial_scrpad[9], serial_user_ext[5], serial_scrpad_ext[5],serial_rom[8], serial_para[9], serial[9], i;
	  
		DQ_Recall_EE(DUT_DQ_OUT);
		DQ_Recall_PAGE0_RES(DUT_DQ_OUT);
		DQ_Recall_PAGE1(DUT_DQ_OUT);
	
		DQ_Read_Scrpad(serial_scrpad, DUT_DQ_OUT);
		DQ_Read_User_Ext(serial_user_ext, DUT_DQ_OUT);
		DQ_Read_Scrpad_Ext(serial_scrpad_ext, DUT_DQ_OUT);
		DQ_Read_Rom_Code(serial_rom, DUT_DQ_OUT);
		DQ_Read_Parameters(serial_para, DUT_DQ_OUT);
	
		DQ_Write_Scratchpad(0x00,0x00,0x00, DUT_DQ_OUT);
		DQ_Write_User(0x00,0x00,0x00, DUT_DQ_OUT);
		DQ_Write_User_Ext(0x00,0x00,0x00,0x00,0x00, DUT_DQ_OUT);
		DQ_Write_Scratchpad_Ext(0x00,0x00,0x00,0x00,0x00, DUT_DQ_OUT);
		DQ_Setup_ROM(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, DUT_DQ_OUT);
		DQ_Write_Parameters(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, DUT_DQ_OUT);
	
		DQ_Read_Scrpad(serial, DUT_DQ_OUT);
		for(i=2; i<8; i++) {
				if(serial[i] != 0x00 && i != 4) {
					printf("\r\nERROR: Scratchpad write all 0 error !!!\r\n");
					return;
				}
		}
		DQ_Read_User_Ext(serial, DUT_DQ_OUT);
		for(i=0; i<5; i++) {
				if(serial[i] != 0x00) {
					printf("\r\nERROR: User ext write all 0 error !!!\r\n");
					return;
				}
		}
		DQ_Read_Scrpad_Ext(serial, DUT_DQ_OUT);
		for(i=0; i<5; i++) {
				if(serial[i] != 0x00) {
					printf("\r\nERROR: Scratchpad ext write all 0 error !!!\r\n");
					return;
				}
		}
		DQ_Read_Rom_Code(serial, DUT_DQ_OUT);
		for(i=0; i<8; i++) {
				if(serial[i] != 0x00) {
					printf("\r\nERROR: ROM write all 0 error !!!\r\n");
					return;
				}
		}
		DQ_Read_Parameters(serial, DUT_DQ_OUT);
		for(i=0; i<8; i++) {
				if(serial[i] != 0x00) {
					printf("\r\nScratchpad Ext Byte %d is: %02x, it should be 0x00\r\n", i, serial[i]);
					printf("\r\nERROR: Parameters write all 0 error !!!\r\n");
					return;
				}
		}	
		DQ_Copy_PAGE0(DUT_DQ_OUT);
		DQ_Copy_PAGE1(DUT_DQ_OUT);
		
		DQ_Write_Scratchpad(0xff,0xff,0xff, DUT_DQ_OUT);
		DQ_Write_User(0xff,0xff,0xff, DUT_DQ_OUT);
		DQ_Write_User_Ext(0xff,0xff,0xff,0xff,0xff, DUT_DQ_OUT);
		DQ_Write_Scratchpad_Ext(0xff,0xff,0xff,0xff,0xff, DUT_DQ_OUT);
		DQ_Setup_ROM(0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, DUT_DQ_OUT);
		DQ_Write_Parameters(0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, DUT_DQ_OUT);
		
		DQ_Read_Scrpad(serial, DUT_DQ_OUT);
		for(i=2; i<8; i++) {
				if(serial[i] != 0xff && i != 4) {
					printf("\r\nScratchpad Byte %d is: %02x, it should be 0xff\r\n", i, serial[i]);
					printf("\r\nERROR: Scratchpad write all 1 error !!!\r\n");
					return;
				}
		}
		DQ_Read_User_Ext(serial, DUT_DQ_OUT);
		for(i=0; i<5; i++) {
				if(serial[i] != 0xff) {
					printf("\r\nUser Ext Byte %d is: %02x, it should be 0xff\r\n", i, serial[i]);
					printf("\r\nERROR: User ext write all 1 error !!!\r\n");
					return;
				}
		}
		DQ_Read_Scrpad_Ext(serial, DUT_DQ_OUT);
		for(i=0; i<5; i++) {
				if(serial[i] != 0xff) {
					printf("\r\nScratchpad Ext Byte %d is: %02x, it should be 0xff\r\n", i, serial[i]);
					printf("\r\nERROR: Scratchpad ext write all 1 error !!!\r\n");
					return;
				}
		}
		DQ_Read_Rom_Code(serial, DUT_DQ_OUT);
		for(i=0; i<8; i++) {
				if(serial[i] != 0xff) {
					printf("\r\nROM Byte %d is: %02x, it should be 0xff\r\n", i, serial[i]);
					printf("\r\nERROR: ROM write all 1 error !!!\r\n");
					return;
				}
		}
		DQ_Read_Parameters(serial, DUT_DQ_OUT);
		for(i=0; i<8; i++) {
				if(serial[i] != 0xff) {
					printf("\r\nParameters Byte %d is: %02x, it should be 0xff\r\n", i, serial[i]);
					printf("\r\nERROR: Parameters write all 1 error !!!\r\n");
					return;
				}
		}

		DQ_Recall_EE(DUT_DQ_OUT);
		DQ_Recall_PAGE0_RES(DUT_DQ_OUT);
		DQ_Recall_PAGE1(DUT_DQ_OUT);
		
		DQ_Read_Scrpad(serial, DUT_DQ_OUT);
		for(i=2; i<8; i++) {
				if(serial[i] != 0x00 && i != 4) {
					printf("\r\nScratchpad Byte %d is: %02x, it should be 0x00\r\n", i, serial[i]);
					printf("\r\nERROR: Scratchpad copy/recall error !!!\r\n");
					return;
				}
		}
		DQ_Read_User_Ext(serial, DUT_DQ_OUT);
		for(i=0; i<5; i++) {
				if(serial[i] != 0x00) {
					printf("\r\nUser Ext Byte %d is: %02x, it should be 0x00\r\n", i, serial[i]);
					printf("\r\nERROR: User ext copy/recall error !!!\r\n");
					return;
				}
		}
		DQ_Read_Scrpad_Ext(serial, DUT_DQ_OUT);
		for(i=0; i<5; i++) {
				if(serial[i] != 0x00) {
					printf("\r\nScratchpad Ext Byte %d is: %02x, it should be 0x00\r\n", i, serial[i]);
					printf("\r\nERROR: Scratchpad ext copy/recall error !!!\r\n");
					return;
				}
		}
		DQ_Read_Rom_Code(serial, DUT_DQ_OUT);
		for(i=0; i<8; i++) {
				//printf("\r\nROM Byte %d is: %02x, \r\n", i, serial[i]);
				if(serial[i] != 0x00) {
					printf("\r\nROM Byte %d is: %02x, it should be 0x00\r\n", i, serial[i]);
					printf("\r\nERROR: ROM copy/recall error !!!\r\n");
					return;
				}
		}
		DQ_Read_Parameters(serial, DUT_DQ_OUT);
		for(i=0; i<8; i++) {
				if(serial[i] != 0x00) {
					printf("\r\nParameters Byte %d is: %02x, it should be 0x00\r\n", i, serial[i]);
					printf("\r\nERROR: Parameters copy/recall error !!!\r\n");
					return;
				}
		}	
	
		printf("\r\nPASS: MTP Operation Check pass!!!\r\n");
	
	  DQ_Write_Scratchpad(serial_scrpad[2],serial_scrpad[3],serial_scrpad[4], DUT_DQ_OUT);
		DQ_Write_User(serial_scrpad[5],serial_scrpad[6],serial_scrpad[7], DUT_DQ_OUT);
		DQ_Write_User_Ext(serial_user_ext[0],serial_user_ext[1],serial_user_ext[2],serial_user_ext[3],serial_user_ext[4], DUT_DQ_OUT);
		DQ_Write_Scratchpad_Ext(serial_scrpad_ext[0],serial_scrpad_ext[1],serial_scrpad_ext[2],serial_scrpad_ext[3],serial_scrpad_ext[4], DUT_DQ_OUT);
		DQ_Setup_ROM(serial_rom[0],serial_rom[1],serial_rom[2],serial_rom[3],serial_rom[4],serial_rom[5],serial_rom[6],serial_rom[7], DUT_DQ_OUT);
		DQ_Write_Parameters(serial_para[0],serial_para[1],serial_para[2],serial_para[3],serial_para[4],serial_para[5],serial_para[6],serial_para[7], DUT_DQ_OUT);	

		DQ_Copy_PAGE0(DUT_DQ_OUT);
		DQ_Copy_PAGE1(DUT_DQ_OUT);
}

void Check_All_Basic_CMD(void) {
		Check_rw_scratchpad();
		Check_rw_user();
		Check_rw_user_ext();
		Check_rw_scratchpad_ext();
		Check_rw_rom_code();
		Check_rw_parameters();
	
		DQ_Check_Power_Supply(DUT_DQ_OUT);
		Check_Search_ROM();
		Check_Alarm_Search();
		Check_ConvertT();
		Check_Match_ROM();	

		Check_MTP();
}

void Check_Search_follow_function(void) {
		uint8_t serial[9];
		DQ_Write_Scratchpad(0x00,0x00,0x00, DUT_DQ_OUT);
		if(DQ_SearchROM_Write_Scratchpad(ID_Buff,MAXNUM_SWITCH_18B20_OUT, DUT_DQ_OUT, 0x55,0x05,0x5f)) {
					if(DQ_SearchROM_Read_Scratchpad(ID_Buff,MAXNUM_SWITCH_18B20_OUT, DUT_DQ_OUT, serial)) {
								if(serial[2] == 0x55 && serial[3] == 0x05 && serial[4] == 0x5f) {
										printf("\r\nPASS: Search ROM + RW Scratchpad Check Pass!!!\r\n");
								}
								else {
										printf("\r\nERROR: Search ROM (hit) + Read Scratchpad Check Error!!!\r\n");
								}
					}
					else {
							printf("\r\nERROR: Search ROM (not hit) + Read Scratchpad Check Error!!!\r\n");
					}
		}
		else {
				printf("\r\nERROR: Search ROM (not hit) + Write Scratchpad Check Error!!!\r\n");
		}
}

void Check_Back_to_Back_Rst(void) {
	uint8_t i, serial[9];
	
	GPIO_InitTypeDef GPIO_InitStructure;
	/*set pin mode to push-pull out mode*/
	#ifdef OD
		DUT_DQ_OUT_Mode_Out_OD(); 
  #else
		DUT_DQ_OUT_Mode_Out_PP(); 
	#endif
	DUT_DQ_OUT_DATA_OUT(HIGH);
	Delay_us(100);
	DUT_DQ_OUT_DATA_OUT(LOW);
	Delay_us(480);
	DUT_DQ_OUT_Mode_IPU();
	Delay_us(5);
	#ifdef OD
		DUT_DQ_OUT_Mode_Out_OD(); 
  #else
		DUT_DQ_OUT_Mode_Out_PP(); 
	#endif
	DUT_DQ_OUT_DATA_OUT(LOW);
	Delay_us(480);
	
	DUT_DQ_OUT_Mode_IPU();
	Delay_us(80);
	if(DUT_DQ_OUT_DATA_IN() == 0)
   	Delay_us(150);
	else {
		printf("\r\nThere's no presence pulse 1 !!!\r\n");
	  return;
	}
	
	DQ_Write_Byte(SKIP_ROM, DUT_DQ_OUT);  
  DQ_Write_Byte(WRITE_SCRATCHPAD, DUT_DQ_OUT); 
	DQ_Write_Byte(0xd7, DUT_DQ_OUT); 
	DQ_Write_Byte(0x9c, DUT_DQ_OUT); 
	DQ_Write_Byte(0xf7, DUT_DQ_OUT);
	
	DUT_DQ_OUT_DATA_OUT(LOW);
	Delay_us(480);
	DUT_DQ_OUT_Mode_IPU();
	Delay_us(10);
	#ifdef OD
		DUT_DQ_OUT_Mode_Out_OD(); 
  #else
		DUT_DQ_OUT_Mode_Out_PP(); 
	#endif
	DUT_DQ_OUT_DATA_OUT(LOW);
	Delay_us(480);
	DUT_DQ_OUT_Mode_IPU();
	Delay_us(60);
	if(DUT_DQ_OUT_DATA_IN() == 0)
   	Delay_us(150);
	else {
		printf("\r\nThere's no presence pulse 2 !!!\r\n");
	  return;
	}
	
	DQ_Write_Byte(SKIP_ROM, DUT_DQ_OUT);
	DQ_Write_Byte(READ_SCRATCHPAD, DUT_DQ_OUT); 
  
	for(i=0; i<9; i++) {
     serial[i] = DQ_Read_Byte(DUT_DQ_OUT); 
	}
	
	if(serial[2] == 0xd7 && serial[3] == 0x9c && serial[4] == 0x7f ) {
			printf("\r\nPASS: Back to Back Reset Check Pass!!!\r\n");
	}
	else {
			printf("\r\nERROR: Back to Back Reset Check Error!!!\r\n");
			for(i=0; i<9; i++) { 
					printf("\r\n Scratchpad byte %d : %02x\r\n",i, serial[i]);
			}
	}
	DQ_Recall_EE(DUT_DQ_OUT);
}

void Check_Temperature_Code(void) {
		float max = -255.0, min = 255.0, temperature, sum = 0.0;
	  int i;
		
		DQ_Write_Scratchpad(0x00,0x00,0x7f, DUT_DQ_OUT);
		for(i=0; i<300; i++) {
				temperature = DUT_DQ_OUT_Get_Temp();
			  printf("\r\nThe %d Temperature is %f\r\n", i+1, temperature);
				if(temperature > max) {
						max = temperature;
				}
				if(temperature < min) {
						min = temperature;
				}
				sum += temperature;
				//Delay_us(50000);
		}
		printf("\r\nThe avg value is %f\r\n", (sum/300));
		printf("\r\nThe max value is %f\r\n", max);
		printf("\r\nThe min value is %f\r\n", min);
		printf("\r\nThe difference is %f, it's %f LSB\r\n", (max-min), ((max-min)/0.0625));
		DQ_Write_Scratchpad(0x00,0x00,0x00, DUT_DQ_OUT);
}

void Check_Temperature_Code_14bit(void) {
		float max = -255.0, min = 255.0, temperature, sum = 0.0;
	  int i;
	  uint8_t serial[9];
		DQ_Read_Parameters(serial, DUT_DQ_OUT);
		DQ_Write_Parameters_3byte((serial[0]|0x01), serial[1], serial[2],DUT_DQ_OUT);
		
		for(i=0; i<300; i++) {
				temperature = DUT_DQ_OUT_Get_Temp_14bit();
			  printf("\r\nThe %d Temperature is %f\r\n", i+1, temperature);
				if(temperature > max) {
						max = temperature;
				}
				if(temperature < min) {
						min = temperature;
				}
				sum += temperature;
				//Delay_us(50000);
		}
		printf("\r\nThe avg value is %f\r\n", (sum/300));
		printf("\r\nThe max value is %f\r\n", max);
		printf("\r\nThe min value is %f\r\n", min);
		printf("\r\nThe difference is %f, it's %f LSB\r\n", (max-min), ((max-min)/0.0625));
		DQ_Write_Parameters_3byte((serial[0]&0xfe), serial[1], serial[2],DUT_DQ_OUT);
}

void open_powerdn(void) {
		uint8_t serial[9];
		DQ_Read_Parameters(serial, DUT_DQ_OUT);
		DQ_Write_Parameters_3byte(serial[0], (serial[1]|0x80), serial[2],DUT_DQ_OUT);
}

void close_powerdn(void) {
		uint8_t serial[9];
		DQ_Read_Parameters(serial, DUT_DQ_OUT);
		DQ_Write_Parameters_3byte(serial[0], (serial[1]&0x7f), serial[2],DUT_DQ_OUT);
}

void open_pulldown_powerdn(void) {
		uint8_t serial[9];
		DQ_Read_Parameters(serial, DUT_DQ_OUT);
		DQ_Write_Parameters_3byte(serial[0], (serial[1]|0xa0), serial[2],DUT_DQ_OUT);
}

void close_pulldown_powerdn(void) {
		uint8_t serial[9];
		DQ_Read_Parameters(serial, DUT_DQ_OUT);
		DQ_Write_Parameters_3byte(serial[0], (serial[1]&0x5f), serial[2],DUT_DQ_OUT);
}

void open_adc_avg(void) {
		uint8_t serial[9];
		DQ_Read_Parameters(serial, DUT_DQ_OUT);
		DQ_Write_Parameters_3byte((serial[0]&0xfd), serial[1], serial[2],DUT_DQ_OUT);
}

void close_adc_avg(void) {
		uint8_t serial[9];
		DQ_Read_Parameters(serial, DUT_DQ_OUT);
		DQ_Write_Parameters_3byte((serial[0]|0x02), serial[1], serial[2],DUT_DQ_OUT);
}

void adc_dr_512(void) {
		uint8_t serial[9];
		DQ_Read_Parameters(serial, DUT_DQ_OUT);
		DQ_Write_Parameters_3byte((serial[0]&0xfb), serial[1], serial[2],DUT_DQ_OUT);
}

void adc_dr_256(void) {
		uint8_t serial[9];
		DQ_Read_Parameters(serial, DUT_DQ_OUT);
		DQ_Write_Parameters_3byte((serial[0]|0x04), serial[1], serial[2],DUT_DQ_OUT);
}

void open_adc_delay(void) {
		uint8_t serial[9];
		DQ_Read_Parameters(serial, DUT_DQ_OUT);
		DQ_Write_Parameters_3byte((serial[0]&0xef), serial[1], serial[2],DUT_DQ_OUT);
}

void close_adc_delay(void) {
		uint8_t serial[9];
		DQ_Read_Parameters(serial, DUT_DQ_OUT);
		DQ_Write_Parameters_3byte((serial[0]|0x10), serial[1], serial[2],DUT_DQ_OUT);
}

void show_system_parameters(void) {
		uint8_t serial[9], i;
		DQ_Read_Rom_Code(serial, DUT_DQ_OUT);
		for(i=0; i<8; i++) {
			printf("\r\nROM Code Byte %d is: 0x%02x\r\n", i, serial[i]);
		}
	  DQ_Read_Parameters(serial, DUT_DQ_OUT);
	  for(i=0; i<8; i++) {
			printf("\r\nParameter Byte %d is: 0x%02x\r\n", i, serial[i]);
		}
		printf("A5 Byte is: %02x\r\n", serial[8]);
		DQ_Read_Scrpad(serial, DUT_DQ_OUT);
		for(i=0; i<8; i++) {
			printf("\r\nScratchpad Byte %d is: 0x%02x\r\n", i, serial[i]);
		}
}

void search_device_on_bus(void) {
		uint8_t rom_num;
	  rom_num = DQ_SearchROM(ID_Buff,MAXNUM_SWITCH_18B20_OUT, DUT_DQ_OUT);
	  printf("\r\n There are %d 18B20!\r\n", rom_num);
}

void check_coeff_boundary(void) {
		uint8_t serial[9];
	  printf("\r\nThe original Temperature is %f\r\n", DUT_DQ_OUT_Get_Temp());
		DQ_Read_Parameters(serial, DUT_DQ_OUT);
		DQ_Write_Parameters(serial[0], serial[1], serial[2],0xff,0x07,0x00,serial[6],serial[7],DUT_DQ_OUT);
		printf("\r\nThe MAX coeff A Temperature is %f\r\n", DUT_DQ_OUT_Get_Temp());
		DQ_Write_Parameters(serial[0], serial[1], serial[2],0x00,0x08,0x00,serial[6],serial[7],DUT_DQ_OUT);
		printf("\r\nThe MIN coeff A Temperature is %f\r\n", DUT_DQ_OUT_Get_Temp());
	
		DQ_Read_Parameters(serial, DUT_DQ_OUT);
		DQ_Write_Parameters(serial[0], serial[1], serial[2],0x00,0xf0,0x7f,serial[6],serial[7],DUT_DQ_OUT);
		printf("\r\nThe MAX coeff B Temperature is %f\r\n", DUT_DQ_OUT_Get_Temp());
		DQ_Write_Parameters(serial[0], serial[1], serial[2],0x00,0x00,0xd0,serial[6],serial[7],DUT_DQ_OUT);
		printf("\r\nThe MIN coeff B Temperature is %f\r\n", DUT_DQ_OUT_Get_Temp());
	
		DQ_Recall_PAGE1(DUT_DQ_OUT);
}	

/*************************************END OF FILE******************************/
