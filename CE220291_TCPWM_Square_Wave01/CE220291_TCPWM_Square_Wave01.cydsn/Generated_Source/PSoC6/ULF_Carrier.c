/*******************************************************************************
* File Name: ULF_Carrier.c
* Version 1.0
*
* Description:
*  This file provides the source code to the API for the ULF_Carrier
*  component.
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ULF_Carrier.h"

/** Indicates whether or not the ULF_Carrier has been initialized. 
*  The variable is initialized to 0 and set to 1 the first time 
*  ULF_Carrier_Start() is called. This allows the Component to 
*  restart without reinitialization after the first call to 
*  the ULF_Carrier_Start() routine.
*/
uint8_t ULF_Carrier_initVar = 0U;

/** The instance-specific configuration structure. This should be used in the 
*  associated ULF_Carrier_Init() function.
*/ 
cy_stc_tcpwm_pwm_config_t const ULF_Carrier_config =
{
    .pwmMode = 4UL,
    .clockPrescaler = 0UL,
    .pwmAlignment = 0UL,
    .deadTimeClocks = 0UL,
    .runMode = 0UL,
    .period0 = 7UL,
    .period1 = 32768UL,
    .enablePeriodSwap = false,
    .compare0 = 4UL,
    .compare1 = 16384UL,
    .enableCompareSwap = false,
    .interruptSources = 1UL,
    .invertPWMOut = 0UL,
    .invertPWMOutN = 0UL,
    .killMode = 2UL,
    .swapInputMode = 3UL,
    .swapInput = CY_TCPWM_INPUT_CREATOR,
    .reloadInputMode = 3UL,
    .reloadInput = CY_TCPWM_INPUT_CREATOR,
    .startInputMode = 3UL,
    .startInput = CY_TCPWM_INPUT_CREATOR,
    .killInputMode = 3UL,
    .killInput = CY_TCPWM_INPUT_CREATOR,
    .countInputMode = 3UL,
    .countInput = CY_TCPWM_INPUT_CREATOR,
};


/*******************************************************************************
* Function Name: ULF_Carrier_Start
****************************************************************************//**
*
*  Calls the ULF_Carrier_Init() when called the first time and enables 
*  the ULF_Carrier. For subsequent calls the configuration is left 
*  unchanged and the component is just enabled.
*
* \globalvars
*  \ref ULF_Carrier_initVar
*
*******************************************************************************/
void ULF_Carrier_Start(void)
{
    if (0U == ULF_Carrier_initVar)
    {
        (void) Cy_TCPWM_PWM_Init(ULF_Carrier_HW, ULF_Carrier_CNT_NUM, &ULF_Carrier_config);

        ULF_Carrier_initVar = 1U;
    }

    Cy_TCPWM_Enable_Multiple(ULF_Carrier_HW, ULF_Carrier_CNT_MASK);
    
    #if (ULF_Carrier_INPUT_DISABLED == 7UL)
        Cy_TCPWM_TriggerStart(ULF_Carrier_HW, ULF_Carrier_CNT_MASK);
    #endif /* (ULF_Carrier_INPUT_DISABLED == 7UL) */    
}


/* [] END OF FILE */
