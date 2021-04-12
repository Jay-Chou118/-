#ifndef _INFAREDTUBE_H
#define _INFAREDTUBE_H
#include "data_type.h"
#include "sys.h"



void InfaredTube_GPIO_Config(void);
void InfaredTube_Read(void);
int InfaredTube_Transform(InfaredTube_Type a,int* buf_data);
void Down_Load_InfaredTube_number(void);
void original_red_data(void);
#endif

