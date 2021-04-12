#include "pid.h"

#include "data_type.h"


static PID  sPID; 
static PID  *sptr = &sPID; 


int16_t IncPIDCalc(int16_t NextPoint) 
{  

		/********************增量式PID公式*****************************/  
		int16_t dError,Error,pError;
		int16_t iIncpid; 
		//增量法计算公式：
		//Pdt=Kp*[E(t)-E(t-1)]+Ki*E(t)+Kd*[E(t)-2*E(t-1)+E(t-2)]
		Error = NextPoint - sptr->SetPoint  ;        // 偏差E(t) 
		pError= Error - sptr->LastError;         //E(t)-E(t-1)
		dError= Error - 2 * sptr->LastError + sptr->PrevError; //E(t)-2*E(t-1)+E(t-2) 
		sptr->PrevError = sptr->LastError; 
		sptr->LastError = Error; 
		iIncpid = sptr->Proportion * pError + sptr->Integral * Error + sptr->Derivative * dError;
		return (iIncpid);

}