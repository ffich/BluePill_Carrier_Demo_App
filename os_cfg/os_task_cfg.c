/************************************************************************
*                               OS Task Cfg                         
*************************************************************************
* FileName:         os_task_cfg.c                                                                                
* Author:           F.Ficili                                            
*                                                                       
* Software License Agreement:                                           
*                                                                       
* THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,     
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED     
* TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A           
* PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE AUTHOR SHALL NOT,      
* IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR            
* CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.                     
*                                                                       
* --------------------------------------------------------------------- 
* File History:                                                                                         
* --------------------------------------------------------------------- 
* Author       Date        Version      Comment                         
* ---------------------------------------------------------------------	
*             
************************************************************************/

/************************************************************************
* Includes
************************************************************************/
#include "os_task.h"
#include "os_task_cfg.h"

/************************************************************************
* Typedefs
************************************************************************/


/************************************************************************
* LOCAL Variables
************************************************************************/


/************************************************************************
* TASK List
************************************************************************/
extern void CAN_Task (void);
extern void RS485_Task (void);
extern void LED_Task (void);
extern void Readings_Task (void);
extern void OLED_Task (void);
extern void Serial_Task (void);

/************************************************************************
* GLOBAL Variables
************************************************************************/
TbcType Tasks [] =
{
  /* -------------------------------------------------------------------- */
  /* ID                    Task              State           Priority     */
  /* -------------------------------------------------------------------- */   
  /* --------------------------------- Tasks ---------------------------- */   
  {CAN_Task_ID,           CAN_Task,         IDLE,           30},
  {RS485_Task_ID,           RS485_Task,         IDLE,           30},
  {LED_Task_ID,           LED_Task,         IDLE,           5},
  {Readings_Task_ID,           Readings_Task,         IDLE,           20},
  {OLED_Task_ID,           OLED_Task,         IDLE,           10},
  {Serial_Task_ID,           Serial_Task,         IDLE,           10},
  /* -------------------------------------------------------------------- */
};

/* Auto-calculation of task number */
const uint16_t TaskNumber = (uint16_t)(sizeof(Tasks)/sizeof(TbcType));  

/* List of auto-started Tasks */
AutoStarTaskType AutoStartedTasks[] =
{
};

/* Auto-calculation of auto-started task number */
const uint16_t AutoStartTaskNumber = (uint16_t)(sizeof(AutoStartedTasks)/sizeof(AutoStarTaskType));  

/************************************************************************
* LOCAL Functions
************************************************************************/


/************************************************************************
* GLOBAL Functions
************************************************************************/
