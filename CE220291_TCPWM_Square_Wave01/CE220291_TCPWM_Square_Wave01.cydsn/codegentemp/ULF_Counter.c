/*******************************************************************************
* File Name: ULF_Counter.c
* Version 1.0
*
* Description:
*  This file provides the source code to the API for the ULF_Counter
*  component
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ULF_Counter.h"

/** Indicates whether or not the ULF_Counter has been initialized. 
*  The variable is initialized to 0 and set to 1 the first time 
*  ULF_Counter_Start() is called. This allows the Component to 
*  restart without reinitialization after the first call to 
*  the ULF_Counter_Start() routine.
*/
uint8_t ULF_Counter_initVar = 0U;

/** The instance-specific configuration structure. This should be used in the 
*  associated ULF_Counter_Init() function.
*/ 
cy_stc_tcpwm_counter_config_t const ULF_Counter_config =
{
        .period = 7UL,
        .clockPrescaler = 0UL,
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
* Function Name: ULF_Counter_Start
****************************************************************************//**
*
*  Calls the ULF_Counter_Init() when called the first time and enables 
*  the ULF_Counter. For subsequent calls the configuration is left 
*  unchanged and the component is just enabled.
*
* \globalvars
*  \ref ULF_Counter_initVar
*
*******************************************************************************/
void ULF_Counter_Start(void)
{
    if (0U == ULF_Counter_initVar)
    {
        (void)Cy_TCPWM_Counter_Init(ULF_Counter_HW, ULF_Counter_CNT_NUM, &ULF_Counter_config); 

        ULF_Counter_initVar = 1U;
    }

    Cy_TCPWM_Enable_Multiple(ULF_Counter_HW, ULF_Counter_CNT_MASK);
    
    #if (ULF_Counter_INPUT_DISABLED == 7UL)
        Cy_TCPWM_TriggerStart(ULF_Counter_HW, ULF_Counter_CNT_MASK);
    #endif /* (ULF_Counter_INPUT_DISABLED == 7UL) */    
}


/* [] END OF FILE */
