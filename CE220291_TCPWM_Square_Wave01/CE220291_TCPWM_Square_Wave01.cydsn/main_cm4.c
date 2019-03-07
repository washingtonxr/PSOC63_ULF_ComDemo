/******************************************************************************
* File Name: main_cm4.c
*
* Version: 1.20
*
* Description: This is the source code for the TCPWM (Square wave) code example.
*
* Related Document: CE220291.pdf
*
* Hardware Dependency: See CE220290.pdf
*
*******************************************************************************
* Copyright (2017), Cypress Semiconductor Corporation. All rights reserved.
*******************************************************************************
* This software, including source code, documentation and related materials
* (“Software�?, is owned by Cypress Semiconductor Corporation or one of its
* subsidiaries (“Cypress�? and is protected by and subject to worldwide patent
* protection (United States and foreign), United States copyright laws and
* international treaty provisions. Therefore, you may use this Software only
* as provided in the license agreement accompanying the software package from
* which you obtained this Software (“EULA�?.
*
* If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
* non-transferable license to copy, modify, and compile the Software source
* code solely for use in connection with Cypress’s integrated circuit products.
* Any reproduction, modification, translation, compilation, or representation
* of this Software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, 
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED 
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress 
* reserves the right to make changes to the Software without notice. Cypress 
* does not assume any liability arising out of the application or use of the 
* Software or any product or circuit described in the Software. Cypress does 
* not authorize its products for use in any products where a malfunction or 
* failure of the Cypress product may reasonably be expected to result in 
* significant property damage, injury or death (“High Risk Product�?. By 
* including Cypress’s product in a High Risk Product, the manufacturer of such 
* system or application assumes all risk of such use and in doing so agrees to 
* indemnify Cypress against all liability.
*******************************************************************************/

#include "project.h"
#include "ULF.h"
#include "debug.h"
#include "main_cm4.h"

ulf_ctrl_t ULF_CTRL;                    /* ULF Transmit Control. */
ulf_user_db_t ULF_DB;                   /* ULF Control Database. */
sys_LEDtimer_t Red_LED, Orange_LED;     /* LED Database.         */
unsigned int Sys_counter;               /* System Counter.       */

/* 10ms Timmer. */
void System_Tick_ISR()
{
    int ret;
    static char System_HB;
    
    ret = System_Tick_GetInterruptStatus();
    //DEBUG_PRINTF("Counter_1_GetInterruptStatus = %d\n", ret);
#if 1
    /* Red LED routine. */
    if(Red_LED.sw){
        if(Red_LED.counter++ >= LED_TO){
            Red_LED.counter = 0;
            Cy_GPIO_Set(Red_LED_PORT, Red_LED_NUM);
            Red_LED.sw = 0;
        }else{
            Cy_GPIO_Clr(Red_LED_PORT, Red_LED_NUM);
        }
    }

    /* Orange LED routine. */
    if(Orange_LED.sw){
        if(Orange_LED.counter++ >= LED_TO){
            Orange_LED.counter = 0;
            Cy_GPIO_Set(Orange_LED_PORT, Orange_LED_NUM);
            Orange_LED.sw = 0;
        }else{
            Cy_GPIO_Clr(Orange_LED_PORT, Orange_LED_NUM);
        }
    }

    /* Heard beat LED. */
    if(System_HB >= 100){
        System_HB = 0;
        Orange_LED.sw = 1;
    }else{
        System_HB++;
    }

    Sys_counter++;

#else
    Cy_GPIO_Clr(Red_LED_PORT, Red_LED_NUM);
    Cy_SysLib_Delay(10);
    Cy_GPIO_Set(Red_LED_PORT, Red_LED_NUM);
    Cy_SysLib_Delay(10);
#endif
    System_Tick_ClearInterrupt(ret);

}

static void SW2_ISR()
{
    {
        /* Optional check to determine if one pin in the port generated interrupt. */
        if(Cy_GPIO_GetInterruptStatus(SW2_PORT, SW2_NUM) == CY_GPIO_INTR_STATUS_MASK)
        {
            Orange_LED.sw = 1;
        }
    }
    /* Clear pin interrupt logic. Required to detect next interrupt */
    Cy_GPIO_ClearInterrupt(SW2_PORT, SW2_NUM);
}

void HW_Startup(void)
{
    __disable_irq();

    /* Enable Debug UART. */
    UART_DEBUG_Start();
    
    /* Configure CM4+ CPU interrupt vector for System Tick(1ms). */
    Cy_SysInt_Init(&SysInt_Tick_cfg, System_Tick_ISR);
    NVIC_ClearPendingIRQ(SysInt_Tick_cfg.intrSrc);
    NVIC_EnableIRQ((IRQn_Type)SysInt_Tick_cfg.intrSrc);

    /* Configure CM4+ CPU interrupt vector for SW2. */
    Cy_SysInt_Init(&SysInt_SW_cfg, SW2_ISR);
    NVIC_ClearPendingIRQ(SysInt_SW_cfg.intrSrc);
    NVIC_EnableIRQ((IRQn_Type)SysInt_SW_cfg.intrSrc);

    __enable_irq(); /* Enable global interrupts. */

    System_Tick_Start();    /* Enable System Tick. */

    /* Shine for testing. */
    Red_LED.sw = 1;
    Orange_LED.sw = 1;
    
    DEBUG_PRINTF("Info(%08x):Hardware init done.\n", Sys_counter);

    return;
}

/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary: This is the system entrance point for Cortex-M4.
* This function initializes the PSoC Components and puts the Cortex-M4 CPU
* in Sleep mode to save power.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  None  
*
*******************************************************************************/
int main(void)
{

    HW_Startup();   /* Initialize Hardware.      */
#if 0
    ULF_Init();     /* Initialize ULF functions. */

    DEBUG_PRINTF("Info(%08x):Info:Hello world.\n", Sys_counter);

    ULF_CTRL.ULF_TRANSMIT_START = 1;

    ULF_Test();     /* Testing ULF module. */
    
    /* Infinite loop */
    for(;;)
    {
        ULF_Routine();
        /* Put the CPU into Sleep mode to save power */
        //Cy_SysPm_Sleep(CY_SYSPM_WAIT_FOR_INTERRUPT);
    }
#else
    ULF_Init2();     /* Initialize ULF2 functions. */

    /* Infinite loop */
    for(;;)
    {
        ULF_Routine();
        /* Put the CPU into Sleep mode to save power */
        //Cy_SysPm_Sleep(CY_SYSPM_WAIT_FOR_INTERRUPT);
    }

#endif
}


/* [] END OF FILE */