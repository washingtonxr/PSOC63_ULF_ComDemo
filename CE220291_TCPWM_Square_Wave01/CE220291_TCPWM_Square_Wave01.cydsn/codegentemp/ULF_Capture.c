/*******************************************************************************
* File Name: ULF_Capture.c
* Version 1.0
*
* Description:
*  This file provides the source code to the API for the ULF_Capture
*  component
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ULF_Capture.h"

/** Indicates whether or not the ULF_Capture has been initialized. 
*  The variable is initialized to 0 and set to 1 the first time 
*  ULF_Capture_Start() is called. This allows the Component to 
*  restart without reinitialization after the first call to 
*  the ULF_Capture_Start() routine.
*/
uint8_t ULF_Capture_initVar = 0U;

/** The instance-specific configuration structure. This should be used in the 
*  associated ULF_Capture_Init() function.
*/ 
cy_stc_tcpwm_counter_config_t const ULF_Capture_config =
{
        .period = 65535UL,
        .clockPrescaler = 0UL,
        .runMode = 0UL,
        .countDirection = 0UL,
        .compareOrCapture = 2UL,
        .compare0 = 16384UL,
        .compare1 = 16384UL,
        .enableCompareSwap = false,
        .interruptSources = 2UL,
        .captureInputMode = 2UL,
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
* Function Name: ULF_Capture_Start
****************************************************************************//**
*
*  Calls the ULF_Capture_Init() when called the first time and enables 
*  the ULF_Capture. For subsequent calls the configuration is left 
*  unchanged and the component is just enabled.
*
* \globalvars
*  \ref ULF_Capture_initVar
*
*******************************************************************************/
void ULF_Capture_Start(void)
{
    if (0U == ULF_Capture_initVar)
    {
        (void)Cy_TCPWM_Counter_Init(ULF_Capture_HW, ULF_Capture_CNT_NUM, &ULF_Capture_config); 

        ULF_Capture_initVar = 1U;
    }

    Cy_TCPWM_Enable_Multiple(ULF_Capture_HW, ULF_Capture_CNT_MASK);
    
    #if (ULF_Capture_INPUT_DISABLED == 7UL)
        Cy_TCPWM_TriggerStart(ULF_Capture_HW, ULF_Capture_CNT_MASK);
    #endif /* (ULF_Capture_INPUT_DISABLED == 7UL) */    
}


/* [] END OF FILE */
