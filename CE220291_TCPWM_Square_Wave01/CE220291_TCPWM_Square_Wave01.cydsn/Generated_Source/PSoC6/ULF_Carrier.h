/*******************************************************************************
* File Name: ULF_Carrier.h
* Version 1.0
*
* Description:
*  This file provides constants and parameter values for the ULF_Carrier
*  component.
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(ULF_Carrier_CY_TCPWM_PWM_PDL_H)
#define ULF_Carrier_CY_TCPWM_PWM_PDL_H

#include "cyfitter.h"
#include "tcpwm/cy_tcpwm_pwm.h"

   
/*******************************************************************************
* Variables
*******************************************************************************/
/**
* \addtogroup group_globals
* @{
*/
extern uint8_t  ULF_Carrier_initVar;
extern cy_stc_tcpwm_pwm_config_t const ULF_Carrier_config;
/** @} group_globals */


/***************************************
*        Function Prototypes
****************************************/
/**
* \addtogroup group_general
* @{
*/
void ULF_Carrier_Start(void);
__STATIC_INLINE cy_en_tcpwm_status_t ULF_Carrier_Init(cy_stc_tcpwm_pwm_config_t const *config);
__STATIC_INLINE void ULF_Carrier_DeInit(void);
__STATIC_INLINE void ULF_Carrier_Enable(void);
__STATIC_INLINE void ULF_Carrier_Disable(void);
__STATIC_INLINE uint32_t ULF_Carrier_GetStatus(void);
__STATIC_INLINE void ULF_Carrier_SetCompare0(uint32_t compare0);
__STATIC_INLINE uint32_t ULF_Carrier_GetCompare0(void);
__STATIC_INLINE void ULF_Carrier_SetCompare1(uint32_t compare1);
__STATIC_INLINE uint32_t ULF_Carrier_GetCompare1(void);
__STATIC_INLINE void ULF_Carrier_EnableCompareSwap(bool enable);
__STATIC_INLINE void ULF_Carrier_SetCounter(uint32_t count);
__STATIC_INLINE uint32_t ULF_Carrier_GetCounter(void);
__STATIC_INLINE void ULF_Carrier_SetPeriod0(uint32_t period0);
__STATIC_INLINE uint32_t ULF_Carrier_GetPeriod0(void);
__STATIC_INLINE void ULF_Carrier_SetPeriod1(uint32_t period1);
__STATIC_INLINE uint32_t ULF_Carrier_GetPeriod1(void);
__STATIC_INLINE void ULF_Carrier_EnablePeriodSwap(bool enable);
__STATIC_INLINE void ULF_Carrier_TriggerStart(void);
__STATIC_INLINE void ULF_Carrier_TriggerReload(void);
__STATIC_INLINE void ULF_Carrier_TriggerKill(void);
__STATIC_INLINE void ULF_Carrier_TriggerSwap(void);
__STATIC_INLINE uint32_t ULF_Carrier_GetInterruptStatus(void);
__STATIC_INLINE void ULF_Carrier_ClearInterrupt(uint32_t source);
__STATIC_INLINE void ULF_Carrier_SetInterrupt(uint32_t source);
__STATIC_INLINE void ULF_Carrier_SetInterruptMask(uint32_t mask);
__STATIC_INLINE uint32_t ULF_Carrier_GetInterruptMask(void);
__STATIC_INLINE uint32_t ULF_Carrier_GetInterruptStatusMasked(void);
/** @} general */


/***************************************
*           API Constants
***************************************/

/**
* \addtogroup group_macros
* @{
*/
/** This is a ptr to the base address of the TCPWM instance */
#define ULF_Carrier_HW                 (ULF_Carrier_TCPWM__HW)

/** This is a ptr to the base address of the TCPWM CNT instance */
#define ULF_Carrier_CNT_HW             (ULF_Carrier_TCPWM__CNT_HW)

/** This is the counter instance number in the selected TCPWM */
#define ULF_Carrier_CNT_NUM            (ULF_Carrier_TCPWM__CNT_IDX)

/** This is the bit field representing the counter instance in the selected TCPWM */
#define ULF_Carrier_CNT_MASK           (1UL << ULF_Carrier_CNT_NUM)
/** @} group_macros */

#define ULF_Carrier_INPUT_MODE_MASK    (0x3U)
#define ULF_Carrier_INPUT_DISABLED     (7U)


/*******************************************************************************
* Function Name: ULF_Carrier_Init
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_Init() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_tcpwm_status_t ULF_Carrier_Init(cy_stc_tcpwm_pwm_config_t const *config)
{
    return(Cy_TCPWM_PWM_Init(ULF_Carrier_HW, ULF_Carrier_CNT_NUM, config));
}


/*******************************************************************************
* Function Name: ULF_Carrier_DeInit
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_DeInit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void ULF_Carrier_DeInit(void)                   
{
    Cy_TCPWM_PWM_DeInit(ULF_Carrier_HW, ULF_Carrier_CNT_NUM, &ULF_Carrier_config);
}

/*******************************************************************************
* Function Name: ULF_Carrier_Enable
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Enable_Multiple() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void ULF_Carrier_Enable(void)                   
{
    Cy_TCPWM_Enable_Multiple(ULF_Carrier_HW, ULF_Carrier_CNT_MASK);
}


/*******************************************************************************
* Function Name: ULF_Carrier_Disable
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Disable_Multiple() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void ULF_Carrier_Disable(void)                  
{
    Cy_TCPWM_Disable_Multiple(ULF_Carrier_HW, ULF_Carrier_CNT_MASK);
}


/*******************************************************************************
* Function Name: ULF_Carrier_GetStatus
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t ULF_Carrier_GetStatus(void)                
{
    return(Cy_TCPWM_PWM_GetStatus(ULF_Carrier_HW, ULF_Carrier_CNT_NUM));
}


/*******************************************************************************
* Function Name: ULF_Carrier_SetCompare0
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetCompare0() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void ULF_Carrier_SetCompare0(uint32_t compare0)      
{
    Cy_TCPWM_PWM_SetCompare0(ULF_Carrier_HW, ULF_Carrier_CNT_NUM, compare0);
}


/*******************************************************************************
* Function Name: ULF_Carrier_GetCompare0
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetCompare0() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t ULF_Carrier_GetCompare0(void)              
{
    return(Cy_TCPWM_PWM_GetCompare0(ULF_Carrier_HW, ULF_Carrier_CNT_NUM));
}


/*******************************************************************************
* Function Name: ULF_Carrier_SetCompare1
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetCompare1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void ULF_Carrier_SetCompare1(uint32_t compare1)      
{
    Cy_TCPWM_PWM_SetCompare1(ULF_Carrier_HW, ULF_Carrier_CNT_NUM, compare1);
}


/*******************************************************************************
* Function Name: ULF_Carrier_GetCompare1
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetCompare1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t ULF_Carrier_GetCompare1(void)              
{
    return(Cy_TCPWM_PWM_GetCompare1(ULF_Carrier_HW, ULF_Carrier_CNT_NUM));
}


/*******************************************************************************
* Function Name: ULF_Carrier_EnableCompareSwap
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_EnableCompareSwap() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void ULF_Carrier_EnableCompareSwap(bool enable)  
{
    Cy_TCPWM_PWM_EnableCompareSwap(ULF_Carrier_HW, ULF_Carrier_CNT_NUM, enable);
}


/*******************************************************************************
* Function Name: ULF_Carrier_SetCounter
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetCounter() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void ULF_Carrier_SetCounter(uint32_t count)          
{
    Cy_TCPWM_PWM_SetCounter(ULF_Carrier_HW, ULF_Carrier_CNT_NUM, count);
}


/*******************************************************************************
* Function Name: ULF_Carrier_GetCounter
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetCounter() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t ULF_Carrier_GetCounter(void)               
{
    return(Cy_TCPWM_PWM_GetCounter(ULF_Carrier_HW, ULF_Carrier_CNT_NUM));
}


/*******************************************************************************
* Function Name: ULF_Carrier_SetPeriod0
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetPeriod0() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void ULF_Carrier_SetPeriod0(uint32_t period0)          
{
    Cy_TCPWM_PWM_SetPeriod0(ULF_Carrier_HW, ULF_Carrier_CNT_NUM, period0);
}


/*******************************************************************************
* Function Name: ULF_Carrier_GetPeriod0
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetPeriod0() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t ULF_Carrier_GetPeriod0(void)                
{
    return(Cy_TCPWM_PWM_GetPeriod0(ULF_Carrier_HW, ULF_Carrier_CNT_NUM));
}


/*******************************************************************************
* Function Name: ULF_Carrier_SetPeriod1
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetPeriod1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void ULF_Carrier_SetPeriod1(uint32_t period1)
{
    Cy_TCPWM_PWM_SetPeriod1(ULF_Carrier_HW, ULF_Carrier_CNT_NUM, period1);
}


/*******************************************************************************
* Function Name: ULF_Carrier_GetPeriod1
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetPeriod1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t ULF_Carrier_GetPeriod1(void)                
{
    return(Cy_TCPWM_PWM_GetPeriod1(ULF_Carrier_HW, ULF_Carrier_CNT_NUM));
}


/*******************************************************************************
* Function Name: ULF_Carrier_EnablePeriodSwap
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_EnablePeriodSwap() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void ULF_Carrier_EnablePeriodSwap(bool enable)
{
    Cy_TCPWM_PWM_EnablePeriodSwap(ULF_Carrier_HW, ULF_Carrier_CNT_NUM, enable);
}


/*******************************************************************************
* Function Name: ULF_Carrier_TriggerStart
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerStart() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void ULF_Carrier_TriggerStart(void)             
{
    Cy_TCPWM_TriggerStart(ULF_Carrier_HW, ULF_Carrier_CNT_MASK);
}


/*******************************************************************************
* Function Name: ULF_Carrier_TriggerReload
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerReloadOrIndex() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void ULF_Carrier_TriggerReload(void)     
{
    Cy_TCPWM_TriggerReloadOrIndex(ULF_Carrier_HW, ULF_Carrier_CNT_MASK);
}


/*******************************************************************************
* Function Name: ULF_Carrier_TriggerKill
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerStopOrKill() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void ULF_Carrier_TriggerKill(void)
{
    Cy_TCPWM_TriggerStopOrKill(ULF_Carrier_HW, ULF_Carrier_CNT_MASK);
}


/*******************************************************************************
* Function Name: ULF_Carrier_TriggerSwap
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerCaptureOrSwap() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void ULF_Carrier_TriggerSwap(void)     
{
    Cy_TCPWM_TriggerCaptureOrSwap(ULF_Carrier_HW, ULF_Carrier_CNT_MASK);
}


/*******************************************************************************
* Function Name: ULF_Carrier_GetInterruptStatus
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t ULF_Carrier_GetInterruptStatus(void)       
{
    return(Cy_TCPWM_GetInterruptStatus(ULF_Carrier_HW, ULF_Carrier_CNT_NUM));
}


/*******************************************************************************
* Function Name: ULF_Carrier_ClearInterrupt
****************************************************************************//**
*
* Invokes the Cy_TCPWM_ClearInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void ULF_Carrier_ClearInterrupt(uint32_t source)     
{
    Cy_TCPWM_ClearInterrupt(ULF_Carrier_HW, ULF_Carrier_CNT_NUM, source);
}


/*******************************************************************************
* Function Name: ULF_Carrier_SetInterrupt
****************************************************************************//**
*
* Invokes the Cy_TCPWM_SetInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void ULF_Carrier_SetInterrupt(uint32_t source)
{
    Cy_TCPWM_SetInterrupt(ULF_Carrier_HW, ULF_Carrier_CNT_NUM, source);
}


/*******************************************************************************
* Function Name: ULF_Carrier_SetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_TCPWM_SetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void ULF_Carrier_SetInterruptMask(uint32_t mask)     
{
    Cy_TCPWM_SetInterruptMask(ULF_Carrier_HW, ULF_Carrier_CNT_NUM, mask);
}


/*******************************************************************************
* Function Name: ULF_Carrier_GetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t ULF_Carrier_GetInterruptMask(void)         
{
    return(Cy_TCPWM_GetInterruptMask(ULF_Carrier_HW, ULF_Carrier_CNT_NUM));
}


/*******************************************************************************
* Function Name: ULF_Carrier_GetInterruptStatusMasked
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptStatusMasked() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t ULF_Carrier_GetInterruptStatusMasked(void)
{
    return(Cy_TCPWM_GetInterruptStatusMasked(ULF_Carrier_HW, ULF_Carrier_CNT_NUM));
}

#endif /* ULF_Carrier_CY_TCPWM_PWM_PDL_H */


/* [] END OF FILE */
