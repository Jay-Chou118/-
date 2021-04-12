#ifndef __HC_04_H
#define __HC_04_H

#define before_TRIG_H GPIO_WriteBit(GPIOB, GPIO_Pin_11, Bit_SET)     //TRIG 输出
#define before_TRIG_L GPIO_WriteBit(GPIOB, GPIO_Pin_11, Bit_RESET)
#define back_TRIG_H GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET)
#define back_TRIG_L GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET)

#define before_ECHO	GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15)  //ECHO  输入
#define back_ECHO	GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2)


void GPIO_Configuration(void); 
void EXTIX_HC_04_Init_0(void);
void Hc_sr_04_Init(void);
void EXTIX_HC_04_Init_2(void);
void EXTIX_HC_04_Init_1(void);
void GPIO_HC_04_Configuration(void);
void EXTIX_HC_04_Init_1(void);
void EXTIX_HC_04_Init_2(void);	
void Hc_sr_04_Init_E15(void);
void Hc_sr_04_Init_C2(void);

void TIM8_Count_Init(void);   //计时器
float distance_test(void);

#endif




