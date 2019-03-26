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
* (â€œSoftwareâ€?, is owned by Cypress Semiconductor Corporation or one of its
* subsidiaries (â€œCypressâ€? and is protected by and subject to worldwide patent
* protection (United States and foreign), United States copyright laws and
* international treaty provisions. Therefore, you may use this Software only
* as provided in the license agreement accompanying the software package from
* which you obtained this Software (â€œEULAâ€?.
*
* If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
* non-transferable license to copy, modify, and compile the Software source
* code solely for use in connection with Cypressâ€™s integrated circuit products.
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
* significant property damage, injury or death (â€œHigh Risk Productâ€?. By 
* including Cypressâ€™s product in a High Risk Product, the manufacturer of such 
* system or application assumes all risk of such use and in doing so agrees to 
* indemnify Cypress against all liability.
*******************************************************************************/
/**
 * Function: Ultra Low Frequency module. 
 * Author: Xi Ruan
 * Date: Mar.1st,2019
 * E-mail: ruanx@landicorp.com
 **/
#include <string.h>
#include "project.h"
#include "ULF.h"
#include "debug.h"
#include "main_cm4.h"

sys_LEDtimer_t Red_LED, Orange_LED;     /* LED Database.         */
ulf_userdb_t USER_DB_1;
unsigned char ULF_FieldDet_EN = 1;
unsigned int Sys_counter;               /* System Counter.       */

void System_Tick_ISR(void);
void SW2_ISR(void);
void SW3_ISR(void);
void ULF_FiledDetectInt_Disable(void);
void ULF_FiledDetectInt_Enable(void);
void SW2Int_Enable(void);
void System_Vice_Tick(void);
void HW_Startup(void);

#if 0
void Trace_Reader();
#endif
/* 10ms Timmer. */
void System_Tick_ISR(void)
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

void SW2_ISR(void)
{
    /* Optional check to determine if one pin in the port generated interrupt. */
    if(Cy_GPIO_GetInterruptStatus(SW2_PORT, SW2_NUM) == CY_GPIO_INTR_STATUS_MASK){
        /* Transmit interrupt disable. */
        ULF_FiledDetectInt_Disable();

        Orange_LED.sw = 1;
        ULF_Receive(&USER_DB_1, 32);
#if 0
        Cy_GPIO_Set(ULF_BB_PORT, ULF_BB_NUM);
        CyDelayUs(10);
        Cy_GPIO_Clr(ULF_BB_PORT, ULF_BB_NUM);
#endif
    }
    /* Clear pin interrupt logic. Required to detect next interrupt */
    Cy_GPIO_ClearInterrupt(SW2_PORT, SW2_NUM);
}

/* ULF Filed Detecting ISR. */
void SW3_ISR(void)
{
    int ret;
    /* Optional check to determine if one pin in the port generated interrupt. */
    if(Cy_GPIO_GetInterruptStatus(SW3_PORT, SW3_NUM) == CY_GPIO_INTR_STATUS_MASK){
#if 0
        /* Get the interrrupt edge setting of SW3 */
        ret = Cy_GPIO_GetInterruptEdge(SW3_PORT, SW3_NUM);
        DEBUG_PRINTF("Info:SW3 Edge:%d\n", ret);
        ret = SW3_PORT->INTR;
        DEBUG_PRINTF("Info:SW3 PORT INTR:%08X\n", ret);
 #endif
#if 0
        Cy_GPIO_Set(ULF_BB_PORT, ULF_BB_NUM);
        CyDelayUs(10);
        Cy_GPIO_Clr(ULF_BB_PORT, ULF_BB_NUM);
#endif
        /* Read the input state of SW3_PORT. */
        ret = Cy_GPIO_Read(SW3_PORT, SW3_NUM);
        //DEBUG_PRINTF("Info:SW3 Status:%d\n", ret);
#if 1   /* Falling edge activity. */
        if(1UL == ret){
            ULF_Transmit_Exit();
        }else{
            if(ULF_FieldDet_EN){
                Orange_LED.sw = 1;
                ULF_Transmit(&USER_DB_1, 128);
                //ULF_FiledDetectInt_Disable();
            }
        }
#else   /* Raising edge activity. */
        if(1UL == ret){
            Orange_LED.sw = 1;
            ULF_Transmit(&USER_DB_1, 256);
        }else{
            ULF_Transmit_Exit();
        }
#endif
    }
    /* Clear pin interrupt logic. Required to detect next interrupt */
    Cy_GPIO_ClearInterrupt(SW3_PORT, SW3_NUM);
}

void ULF_FiledDetectInt_Disable(void)
{
#if 0
    NVIC_ClearPendingIRQ(SysInt_SW3_cfg.intrSrc);
    NVIC_DisableIRQ((IRQn_Type)SysInt_SW3_cfg.intrSrc);
#else
    ULF_FieldDet_EN = 0;
#endif
    return;
}

void ULF_FiledDetectInt_Enable(void)
{
#if 0
    /* Configure CM4+ CPU interrupt vector for SW3. */
    Cy_SysInt_Init(&SysInt_SW3_cfg, SW3_ISR);
    NVIC_ClearPendingIRQ(SysInt_SW3_cfg.intrSrc);
    NVIC_EnableIRQ((IRQn_Type)SysInt_SW3_cfg.intrSrc);
#else
    ULF_FieldDet_EN = 1;
#endif
    return;
}

void SW2Int_Enable(void)
{
    /* Configure CM4+ CPU interrupt vector for SW2. */
    Cy_SysInt_Init(&SysInt_SW_cfg, SW2_ISR);
    NVIC_ClearPendingIRQ(SysInt_SW_cfg.intrSrc);
    NVIC_EnableIRQ((IRQn_Type)SysInt_SW_cfg.intrSrc);
    return;
}

void System_Vice_Tick(void)
{
    /* Configure CM4+ CPU interrupt vector for System Tick(1ms). */
    Cy_SysInt_Init(&SysInt_Tick_cfg, System_Tick_ISR);
    NVIC_ClearPendingIRQ(SysInt_Tick_cfg.intrSrc);
    NVIC_EnableIRQ((IRQn_Type)SysInt_Tick_cfg.intrSrc);
    return;
}

void HW_Startup(void)
{
    __disable_irq();

    /* Enable Debug UART. */
    UART_DEBUG_Start();
    
    System_Vice_Tick();

    SW2Int_Enable();
    
    /* Configure CM4+ CPU interrupt vector for SW3. */
    Cy_SysInt_Init(&SysInt_SW3_cfg, SW3_ISR);
    NVIC_ClearPendingIRQ(SysInt_SW3_cfg.intrSrc);
    NVIC_EnableIRQ((IRQn_Type)SysInt_SW3_cfg.intrSrc);
    
    /* Transmit interrupt enable. */
    ULF_FiledDetectInt_Enable();
    
    __enable_irq(); /* Enable global interrupts. */

    System_Tick_Start();    /* Enable System Tick. */

    /* Shine for testing. */
    Red_LED.sw = 1;
    Orange_LED.sw = 1;
    
    DEBUG_PRINTF("Info(%08x):Hardware init done.\n", Sys_counter);

    return;
}
#if 0
void Trace_Reader(){
    unsigned char i;
    unsigned char data[] = {0xAA,0x01,0x02,0x01,0x85,0x87,0xBB};
    for(i = 0; i < 7; i++){
        UART_DEBUG_PUT_CHAR(data[i]);
    }
}
#endif
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
    int ret;
    
    HW_Startup();       /* Initialize Hardware.      */

    memset(&USER_DB_1, 0, sizeof(ulf_userdb_t));
    
    /* Set USER option. */
    USER_DB_1.option = 1;

    ULF_Init();        /* Initialize ULF functions.  */
    
    /* Infinite loop */
    for(;;)
    {
        ret = ULF_Routine(&USER_DB_1);
        switch(ret){
            case GETCARD_INFO:
                Red_LED.sw = 1;
                ULF_FiledDetectInt_Enable();
                break;

            case CARRIER_TO:
                /* Transmit interrupt enable. */
                ULF_FiledDetectInt_Enable();
                break;
            
            case BASEBAND_TO:
                /* Transmit interrupt enable. */
                //ULF_FiledDetectInt_Enable();
                break;
            
            case TIMEOUT:
                
                break;
                
            default:
                break;
        }
        /* Put the CPU into Sleep mode to save power */
        //Cy_SysPm_Sleep(CY_SYSPM_WAIT_FOR_INTERRUPT);
    }
}

/* [] END OF FILE */

