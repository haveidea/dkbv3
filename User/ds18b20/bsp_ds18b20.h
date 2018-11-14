#ifndef __DS18B20_H
#define	__DS18B20_H

#include "stm32f10x.h"
#include "bsp_SysTick.h"

#define HIGH  1
#define LOW   0

#define RST_LOW 480
#define RD_WR1_LOW  2
#define WR0_LOW 60
#define RD_SAMPLE 2
#define RECOVER_WR0 1
#define RECOVER_RD_WR1 50




////////////////////////////////////////////////////////////
#define DS18B20_IN1_CLK     RCC_APB2Periph_GPIOA
#define DS18B20_IN1_PIN     GPIO_Pin_1                 
#define DS18B20_IN1_PORT		GPIOA 

#define STRONG_PULLUP_CLK     RCC_APB2Periph_GPIOA
#define STRONG_PULLUP_PIN     GPIO_Pin_2                
#define STRONG_PULLUP_PORT		GPIOA 

#define TOTAL_DQ_OUT_CLK     RCC_APB2Periph_GPIOA
#define TOTAL_DQ_OUT_PIN     GPIO_Pin_3                 
#define TOTAL_DQ_OUT_PORT		GPIOA 

#define DUT_DQ_OUT_CLK     RCC_APB2Periph_GPIOA
#define DUT_DQ_OUT_PIN     GPIO_Pin_4                 
#define DUT_DQ_OUT_PORT		 GPIOA 

#define MUX_E1_CLK     RCC_APB2Periph_GPIOA
#define MUX_E1_PIN     GPIO_Pin_5                 
#define MUX_E1_PORT		 GPIOA 

#define MUX_18B20_OUT_CLK     RCC_APB2Periph_GPIOA
#define MUX_18B20_OUT_PIN     GPIO_Pin_6                 
#define MUX_18B20_OUT_PORT		GPIOA

#define MUX_E2_CLK     RCC_APB2Periph_GPIOA
#define MUX_E2_PIN     GPIO_Pin_7                 
#define MUX_E2_PORT		 GPIOA

#define TEST_ADDR2_CLK     RCC_APB2Periph_GPIOA
#define TEST_ADDR2_PIN     GPIO_Pin_8                 
#define TEST_ADDR2_PORT		 GPIOA

#define TEST_ADDR1_CLK     RCC_APB2Periph_GPIOA
#define TEST_ADDR1_PIN     GPIO_Pin_11                 
#define TEST_ADDR1_PORT		 GPIOA

#define TEST_ADDR0_CLK     RCC_APB2Periph_GPIOA
#define TEST_ADDR0_PIN     GPIO_Pin_12                 
#define TEST_ADDR0_PORT		 GPIOA

#define TEST_DATA7_CLK     RCC_APB2Periph_GPIOA
#define TEST_DATA7_PIN     GPIO_Pin_15                 
#define TEST_DATA7_PORT		 GPIOA

#define MUX_E5_CLK     RCC_APB2Periph_GPIOB
#define MUX_E5_PIN     GPIO_Pin_0                 
#define MUX_E5_PORT		 GPIOB

#define TEST_ADDR7_CLK     RCC_APB2Periph_GPIOB
#define TEST_ADDR7_PIN     GPIO_Pin_1                 
#define TEST_ADDR7_PORT		 GPIOB

#define TEST_DATA2_CLK     RCC_APB2Periph_GPIOB
#define TEST_DATA2_PIN     GPIO_Pin_3                 
#define TEST_DATA2_PORT		 GPIOB

#define TEST_DATA1_CLK     RCC_APB2Periph_GPIOB
#define TEST_DATA1_PIN     GPIO_Pin_4                 
#define TEST_DATA1_PORT		 GPIOB

#define TEST_DATA0_CLK     RCC_APB2Periph_GPIOB
#define TEST_DATA0_PIN     GPIO_Pin_5                 
#define TEST_DATA0_PORT		 GPIOB

#define MUX_S3_CLK     RCC_APB2Periph_GPIOB
#define MUX_S3_PIN     GPIO_Pin_12                 
#define MUX_S3_PORT		 GPIOB

#define MUX_S2_CLK     RCC_APB2Periph_GPIOB
#define MUX_S2_PIN     GPIO_Pin_13                 
#define MUX_S2_PORT		 GPIOB

#define MUX_S1_CLK     RCC_APB2Periph_GPIOB
#define MUX_S1_PIN     GPIO_Pin_14                 
#define MUX_S1_PORT		 GPIOB

#define MUX_S0_CLK     RCC_APB2Periph_GPIOB
#define MUX_S0_PIN     GPIO_Pin_15                 
#define MUX_S0_PORT		 GPIOB

#define MUX_E3_CLK     RCC_APB2Periph_GPIOC
#define MUX_E3_PIN     GPIO_Pin_4                 
#define MUX_E3_PORT		 GPIOC

#define MUX_E4_CLK     RCC_APB2Periph_GPIOC
#define MUX_E4_PIN     GPIO_Pin_5                 
#define MUX_E4_PORT		GPIOC

#define TEST_ADDR6_CLK     RCC_APB2Periph_GPIOC
#define TEST_ADDR6_PIN     GPIO_Pin_6                 
#define TEST_ADDR6_PORT		 GPIOC

#define TEST_ADDR5_CLK     RCC_APB2Periph_GPIOC
#define TEST_ADDR5_PIN     GPIO_Pin_7                 
#define TEST_ADDR5_PORT		 GPIOC

#define TEST_ADDR4_CLK     RCC_APB2Periph_GPIOC
#define TEST_ADDR4_PIN     GPIO_Pin_8                 
#define TEST_ADDR4_PORT		 GPIOC

#define TEST_ADDR3_CLK     RCC_APB2Periph_GPIOC
#define TEST_ADDR3_PIN     GPIO_Pin_9                 
#define TEST_ADDR3_PORT		 GPIOC

#define TEST_DATA6_CLK     RCC_APB2Periph_GPIOC
#define TEST_DATA6_PIN     GPIO_Pin_10                 
#define TEST_DATA6_PORT		 GPIOC

#define TEST_DATA5_CLK     RCC_APB2Periph_GPIOC
#define TEST_DATA5_PIN     GPIO_Pin_11                 
#define TEST_DATA5_PORT		 GPIOC

#define TEST_DATA4_CLK     RCC_APB2Periph_GPIOC
#define TEST_DATA4_PIN     GPIO_Pin_12                 
#define TEST_DATA4_PORT		 GPIOC

#define TEST_DATA3_CLK     RCC_APB2Periph_GPIOD
#define TEST_DATA3_PIN     GPIO_Pin_2                 
#define TEST_DATA3_PORT		 GPIOD

///////////////////////////////////////////////////////////

//output 1 or 0
#define DS18B20_IN1_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_1);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_1)

#define STRONG_PULLUP_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_2);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_2)

#define TOTAL_DQ_OUT_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_3);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_3)

#define DUT_DQ_OUT_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_4);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_4)
					
#define MUX_E1_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_5);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_5)

#define MUX_18B20_OUT_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_6);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_6)

#define MUX_E2_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_7);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_7)
					
#define TEST_ADDR2_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_8);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_8)
					
#define TEST_ADDR1_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_11);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_11)

#define TEST_ADDR0_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_12);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_12)

#define MUX_E5_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_0);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_0)

#define TEST_ADDR7_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_1);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_1)
#define TEST_DATA0_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_5);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_5)
#define TEST_DATA1_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_4);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_4)
#define TEST_DATA2_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_3);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_3)
#define TEST_DATA3_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOD,GPIO_Pin_2);\
					else		\
					GPIO_ResetBits(GPIOD,GPIO_Pin_2)
#define TEST_DATA4_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_12);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_12)
#define TEST_DATA5_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_11);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_11)
#define TEST_DATA6_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_10);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_10)
#define TEST_DATA7_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_15);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_15)

#define MUX_S3_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_12);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_12)

#define MUX_S2_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_13);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_13)

#define MUX_S1_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_14);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_14)

#define MUX_S0_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_15);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_15)

#define MUX_E3_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_4);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_4)

#define MUX_E4_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_5);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_5)

#define TEST_ADDR6_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_6);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_6)
					
#define TEST_ADDR5_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_7);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_7)

#define TEST_ADDR4_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_8);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_8)

#define TEST_ADDR3_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_9);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_9)
					
////////////////////////////////////////////////////////////////////

#define  DS18B20_IN1_DATA_IN()	   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)

#define  TOTAL_DQ_OUT_DATA_IN()	   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)
#define  DUT_DQ_OUT_DATA_IN()	     GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)
#define  MUX_18B20_OUT_DATA_IN()	     GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)

#define  TEST_DATA7_DATA_IN()	     GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)
#define  TEST_DATA2_DATA_IN()	     GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)
#define  TEST_DATA1_DATA_IN()	     GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)
#define  TEST_DATA0_DATA_IN()	     GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)					

//#define  A05_DQ_OUT_DATA_IN()	   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)					


#define  TEST_DATA6_DATA_IN()	     GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10)
#define  TEST_DATA5_DATA_IN()	     GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11)
#define  TEST_DATA4_DATA_IN()	     GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_12)					
#define  TEST_DATA3_DATA_IN()	     GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)					


#define MAXNUM_IN1 8
//#define MAXNUM_IN2 8
#define MAXNUM_SWITCH_18B20_OUT 55
#define MAXNUM_MUX_18B20_OUT 55

//#define MAXNUM_IN4 8

#define IN1_TEST 0
//#define IN2_TEST 0
#define IN3_TEST 1
//#define IN4_TEST 0	

//#define OD 

					
typedef enum   
{  
    SETUP_ROM           =   0xa6,
	  SEARCH_ROM          =   0xf0,     
    READ_ROM            =   0x33,   
    MATCH_ROM           =   0x55,   
    SKIP_ROM            =   0xcc,   
    ALARM_SEARCH        =   0xec,    
    CONVERT_T           =   0x44,   
    WRITE_SCRATCHPAD    =   0x4e,   
    READ_SCRATCHPAD     =   0xbe,   
    WRITE_SCRATCHPAD_EXT =   0x88,   
    READ_SCRATCHPAD_EXT  =   0xee,
	  WRITE_USER_EXT      =   0x77,   
    READ_USER_EXT       =   0xdd,
	  WRITE_PARAMETERS    =   0xab,   
    READ_PARAMETERS     =   0x8b,
		WRITE_USER          =   0x66,
		COPY_PAGE0          =   0x48,     
    COPY_PAGE1          =   0x4d,
		RECALL_E2           =   0xb8,
    RECALL_PAGE0_RES    =   0xbb,
    RECALL_PAGE1        =   0xba,	
    READ_POWER_SUPPLY   =   0xb4,    
} QIANTANG_CMD;		

typedef enum   
{  
    DUT_DQ_OUT           =   0x01,
	  MUX_18B20_OUT        =   0x02,     
    //A05_DQ_OUT           =   0x03,   
    TOTAL_DQ_OUT         =   0x04,       
} DQ_TYPE;
					

extern uint8_t ID_Buff[80][8];


void GPIO_Config(void);

//uint8_t DS18B20_IN1_Init(void);
//uint8_t DS18B20_IN2_Init(void);
uint8_t DS18B20_IN3_Init(void);
uint8_t DUT_DQ_OUT_Init(void);
//float DS18B20_IN1_Get_Temp(void);
//float DS18B20_IN2_Get_Temp(void);
float DS18B20_IN3_Get_Temp(void);
float DUT_DQ_OUT_Get_Temp(void);
float TOTAL_DQ_OUT_Get_Temp(void);
float MUX_18B20_OUT_Get_Temp(void);

uint8_t DQ_Read2Bit(uint8_t type);
void DQ_Write_Bit(uint8_t bit, uint8_t type);
void DQ_Read_Rom_Code(uint8_t *serial, uint8_t type);


void DQ_Read_Scrpad(uint8_t *serial, uint8_t type);
void DQ_Read_Scrpad_Ext(uint8_t *serial, uint8_t type);
void DQ_Read_User_Ext(uint8_t *serial, uint8_t type);
void DQ_Read_Parameters(uint8_t *serial, uint8_t type);

void DQ_Setup_ROM(uint8_t ROM0,uint8_t ROM1,uint8_t ROM2,uint8_t ROM3,uint8_t ROM4,uint8_t ROM5,uint8_t ROM6,uint8_t ROM7, uint8_t type);

uint8_t DQ_SearchROM(uint8_t (*pID)[8],uint8_t Num, uint8_t type);
uint8_t DQ_Alarm_SearchROM(uint8_t (*pID)[8],uint8_t Num, uint8_t type);

void DQ_Recall_EE(uint8_t type);
void DQ_Recall_PAGE0_RES(uint8_t type);
void DQ_Recall_PAGE1(uint8_t type);

void DQ_Copy_PAGE0(uint8_t type);
void DQ_Copy_PAGE1(uint8_t type);



void DQ_Write_Scratchpad(uint8_t TH,uint8_t TL,uint8_t CFG, uint8_t type);
void DQ_Write_User(uint8_t UDF0,uint8_t UDF1,uint8_t UDF2, uint8_t type);
void DQ_Write_Scratchpad_Ext(uint8_t TTHRES_HI,uint8_t TTHRES_LO, uint8_t ADC_COEFF_EXT0,uint8_t ADC_COEFF_EXT1,uint8_t ADC_COEFF_EXT2, uint8_t type);
void DQ_Write_User_Ext(uint8_t UDF_EXT0,uint8_t UDF_EXT1,uint8_t UDF_EXT2,uint8_t UDF_EXT3,uint8_t UDF_EXT4, uint8_t type);
void DQ_Write_Parameters(uint8_t TTRIM, uint8_t ANA_CONF,uint8_t ADC_CONF,uint8_t ADC_COEFF0,uint8_t ADC_COEFF1,uint8_t ADC_COEFF2,uint8_t ANA_CAL0,uint8_t ANA_CAL1, uint8_t type);


void DS18B20_IN3_Convert_Temperaure_Match(uint8_t *rom);
void DS18B20_IN3_Convert_Temperaure_Skip(void);

void DS18B20_IN3_Read_Temperaure_Match(uint8_t *rom, uint8_t *serial);
void MUX_18B20_OUT_Read_Temperaure_Match(uint8_t *rom, uint8_t temp_lo, uint8_t temp_hi);
float MUX_DQ_OUT_Get_Temp(void);
//void Timer3_Init(u16 arr,u16 psc);

//void Delay_us(uint64_t _ulDelayTime);

void ROM_redo(uint8_t (*pID)[8]);
void QIANTANG_CP_35_1(uint8_t *serial, uint8_t type);
void QIANTANG_CP_37_1(uint8_t *serial, uint8_t type);
void QIANTANG_CP_35_2(uint8_t *serial, uint8_t type);
void QIANTANG_MTP(uint8_t *serial_1, uint8_t *serial_2, uint8_t *serial_3, uint8_t type);

void Send_Convert_Temp(void);
void Array_ROM_Read(uint8_t (*pID)[8]);
void Array_ROM_Write(uint8_t (*pID)[8]);
void Array_PARA_Read(uint8_t (*pID)[8]);
void Array_Para_Write(uint8_t (*pID)[8]);
void Array_Temp_Read_MUX(uint8_t (*Temp)[2],float (*Temp_trans)[10], uint8_t index);
void Array_Temp_Read_Switch(uint8_t (*pID)[8], uint8_t (*Temp)[2]);

void MUX_18B20_OUT_Setup_ROM(uint8_t ROM0,uint8_t ROM1,uint8_t ROM2,uint8_t ROM3,uint8_t ROM4,uint8_t ROM5,uint8_t ROM6,uint8_t ROM7);

void Print_ROM_ID(uint8_t (*pID)[8], int num); 

void DQ_Write_Test(uint8_t data, uint8_t type);

void MUX_18B20_OUT_Read_Temperaure_Match_v2(uint8_t *rom, uint8_t *temp);

void Array_Temp_Read_v2(uint8_t (*pID)[8], uint8_t (*Temp)[2]);

void Print_Temp(uint8_t (*Temp)[2], float (*Temp_trans)[10],int num, int delta, float temp_ref);

void MUX_18B20_OUT_Read_Temperaure_Skip(uint8_t *temp, float *temp_trans, uint8_t index);

float SWITCH_18B20_OUT_Get_Temp(void);

void Send_Convert(void);

float DUT_DQ_OUT_Get_Temp_14bit(void);

uint8_t CRC8_Cal(uint8_t *serial, uint8_t length);

void ROM_Code_Cal(uint8_t (*pID)[8], int pair);

void Write_ROM_Code(uint8_t *serial, uint8_t type);

void DQ_Check_Power_Supply(uint8_t type);

void Send_Convert_Temp_MUX(uint8_t type);

void Array_Send_Convert_Temp(void);

void Temp_Calibre(float *temp_cal, uint32_t *temp_cal_res, float *temperature_7051);

void Array_AB_Calibre_MUX(float (*Temp_Cal)[2], uint32_t (*Temp_Cal_Res)[1], float *temperature_7051);

void Array_Temp_Read_MUX_7(uint8_t (*Temp)[2], float (*Temp_trans)[2], float *array);

void Array_Temp_Read_MUX_47(uint8_t (*Temp)[2], float (*Temp_trans)[2], float *array);

void Check_Temp_4_47(float (*Temp_trans)[2],int num);

void Check_7051_4_47(float *Temp_trans);

void Array_Set_Page0(void);

void Array_Reset_Para(void);

void Ref_Temp_Get_7051_7(float *temperature_7051);

void Ref_Temp_Get_7051_47(float *temperature_7051);

void Array_Copy_Page0(void); 

void Array_Copy_Page1(void);

void Array_Scratchpad_Ext_Read(uint8_t (*pID)[6]);

void Array_Scratchpad_Read(uint8_t (*pID)[9]);

void DQ_Read_Parameters_match(uint8_t *serial, uint8_t type);

void DQ_Read_Parameters_match2(uint8_t *serial, uint8_t type, uint8_t *rom);

void DQ_Read_Scrpad_match2(uint8_t *serial, uint8_t type, uint8_t *rom);

void DQ_Write_Parameters_3byte(uint8_t TTRIM, uint8_t ANA_CONF,uint8_t ADC_CONF,uint8_t type);

uint8_t Calcrc_byte(uint8_t *p,uint8_t len);

void test_Rst(void);

void print_th(void);

void Check_All_Basic_CMD(void);

void Check_Search_follow_function(void);

void Check_Back_to_Back_Rst(void);

void Check_Temperature_Code(void);
void Check_Temperature_Code_14bit(void);

void open_powerdn(void);
void close_powerdn(void);
void open_pulldown_powerdn(void);
void close_pulldown_powerdn(void);
void open_adc_avg(void);
void close_adc_avg(void);
void open_adc_delay(void);
void close_adc_delay(void);
void adc_dr_512(void);
void adc_dr_256(void);

void show_system_parameters(void);
void search_device_on_bus(void);
void check_coeff_boundary(void);
#endif /* __DS18B20_IN1_H */







