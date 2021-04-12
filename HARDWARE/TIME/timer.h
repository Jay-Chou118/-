#ifndef __TIMER_H_
#define __TIMER_H_

#include "stm32f4xx.h"

void TIM3_Int_Init(u16 arr,u16 psc);
void TIM14_Int_Init(u16 arr,u16 psc);
void TIM13_Int_Init(u16 arr,u16 psc);
void TIM7_Int_Init(u16 arr,u16 psc);

#endif








