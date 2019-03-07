/*******************************************************************************
* File Name: System_Tick.c
* Version 1.0
*
* Description:
*  This file provides the source code to the API for the System_Tick
*  component
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "System_Tick.h"

/** Indicates whether or not the System_Tick has been initialized. 
*  The variable is initialized to 0 and set to 1 the first time 
*  System_Tick_Start() is called. This allows the Component to 
*  restart without reinitialization after the first call to 
*  the System_Tick_Start() routine.
*/
uint8_t System_Tick_initVar = 0U;

/** The instance-specific configuration structure. This should be used in the 
*  associated System_Tick_Init() function.
*/ 
cy_stc_tcpwm_counter_config_t const System_Tick_config =
{
        .period = 625UL,
        .clockPrescaler = 4UL,
        .runMode = 0UL,
        .countDirection = 0UL,
        .compareOrCapture = 2UL,
        .compare0 = 16384UL,
        .compare1 = 16384UL,
        .enableCompareSwap = false,
        .interruptSources = 1UL,
        .captureInputMode = 3UL,
        .captureInput = CY_TCPWM_INPUT_CREATOR,
        .reloadInputMode = 3UL,
        .reloadInput = CY_TCPWM_INPUT_CREATOR,
        .startInputMode = 3UL,
        .startInput = CY_TCPWM_INPUT_CREATOR,
        .stopInputMode = 3UL,
        .stopInput = CY_TCPWM_INPUT_CREATOR,
        .countInputMode = 3UL,
        .countInput = CY_TCPWM_INPUT_CREATOR,
};


/*******************************************************************************
* Function Name: System_Tick_Start
****************************************************************************//**
*
*  Calls the System_Tick_Init() when called the first time and enables 
*  the System_Tick. For subsequent calls the configuration is left 
*  unchanged and the component is just enabled.
*
* \globalvars
*  \ref System_Tick_initVar
*
*******************************************************************************/
void System_Tick_Start(void)
{
    if (0U == System_Tick_initVar)
    {
        (void)Cy_TCPWM_Counter_Init(System_Tick_HW, System_Tick_CNT_NUM, &System_Tick_config); 

        System_Tick_initVar = 1U;
    }

    Cy_TCPWM_Enable_Multiple(System_Tick_HW, System_Tick_CNT_MASK);
    
    #if (System_Tick_INPUT_DISABLED == 7UL)
        Cy_TCPWM_TriggerStart(System_Tick_HW, System_Tick_CNT_MASK);
    #endif /* (System_Tick_INPUT_DISABLED == 7UL) */    
}


/* [] END OF FILE */
