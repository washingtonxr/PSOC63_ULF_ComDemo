/*******************************************************************************
* File Name: System_Tick.h
* Version 1.0
*
* Description:
*  This file provides constants and parameter values for the System_Tick
*  component.
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(System_Tick_CY_TCPWM_COUNTER_PDL_H)
#define System_Tick_CY_TCPWM_COUNTER_PDL_H

#include "cyfitter.h"
#include "tcpwm/cy_tcpwm_counter.h"

   
/*******************************************************************************
* Variables
*******************************************************************************/
/**
* \addtogroup group_globals
* @{
*/
extern uint8_t  System_Tick_initVar;
extern cy_stc_tcpwm_counter_config_t const System_Tick_config;
/** @} group_globals */


/***************************************
*  Conditional Compilation Parameters
***************************************/

#define System_Tick_INIT_COMPARE_OR_CAPTURE    (2UL)


/***************************************
*        Function Prototypes
****************************************/
/**
* \addtogroup group_general
* @{
*/
void System_Tick_Start(void);
__STATIC_INLINE cy_en_tcpwm_status_t System_Tick_Init(cy_stc_tcpwm_counter_config_t const *config);
__STATIC_INLINE void System_Tick_DeInit(void);
__STATIC_INLINE void System_Tick_Enable(void);
__STATIC_INLINE void System_Tick_Disable(void);
__STATIC_INLINE uint32_t System_Tick_GetStatus(void);

#if(CY_TCPWM_COUNTER_MODE_CAPTURE == System_Tick_INIT_COMPARE_OR_CAPTURE)
    __STATIC_INLINE uint32_t System_Tick_GetCapture(void);
    __STATIC_INLINE uint32_t System_Tick_GetCaptureBuf(void);
#else
    __STATIC_INLINE void System_Tick_SetCompare0(uint32_t compare0);
    __STATIC_INLINE uint32_t System_Tick_GetCompare0(void);
    __STATIC_INLINE void System_Tick_SetCompare1(uint32_t compare1);
    __STATIC_INLINE uint32_t System_Tick_GetCompare1(void);
    __STATIC_INLINE void System_Tick_EnableCompareSwap(bool enable);
#endif /* (CY_TCPWM_COUNTER_MODE_CAPTURE == System_Tick_INIT_COMPARE_OR_CAPTURE) */

__STATIC_INLINE void System_Tick_SetCounter(uint32_t count);
__STATIC_INLINE uint32_t System_Tick_GetCounter(void);
__STATIC_INLINE void System_Tick_SetPeriod(uint32_t period);
__STATIC_INLINE uint32_t System_Tick_GetPeriod(void);
__STATIC_INLINE void System_Tick_TriggerStart(void);
__STATIC_INLINE void System_Tick_TriggerReload(void);
__STATIC_INLINE void System_Tick_TriggerStop(void);
__STATIC_INLINE void System_Tick_TriggerCapture(void);
__STATIC_INLINE uint32_t System_Tick_GetInterruptStatus(void);
__STATIC_INLINE void System_Tick_ClearInterrupt(uint32_t source);
__STATIC_INLINE void System_Tick_SetInterrupt(uint32_t source);
__STATIC_INLINE void System_Tick_SetInterruptMask(uint32_t mask);
__STATIC_INLINE uint32_t System_Tick_GetInterruptMask(void);
__STATIC_INLINE uint32_t System_Tick_GetInterruptStatusMasked(void);
/** @} general */


/***************************************
*           API Constants
***************************************/

/**
* \addtogroup group_macros
* @{
*/
/** This is a ptr to the base address of the TCPWM instance */
#define System_Tick_HW                 (System_Tick_TCPWM__HW)

/** This is a ptr to the base address of the TCPWM CNT instance */
#define System_Tick_CNT_HW             (System_Tick_TCPWM__CNT_HW)

/** This is the counter instance number in the selected TCPWM */
#define System_Tick_CNT_NUM            (System_Tick_TCPWM__CNT_IDX)

/** This is the bit field representing the counter instance in the selected TCPWM */
#define System_Tick_CNT_MASK           (1UL << System_Tick_CNT_NUM)
/** @} group_macros */

#define System_Tick_INPUT_MODE_MASK    (0x3U)
#define System_Tick_INPUT_DISABLED     (7U)


/*******************************************************************************
* Function Name: System_Tick_Init
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_Init() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_tcpwm_status_t System_Tick_Init(cy_stc_tcpwm_counter_config_t const *config)
{
    return(Cy_TCPWM_Counter_Init(System_Tick_HW, System_Tick_CNT_NUM, config));
}


/*******************************************************************************
* Function Name: System_Tick_DeInit
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_DeInit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void System_Tick_DeInit(void)                   
{
    Cy_TCPWM_Counter_DeInit(System_Tick_HW, System_Tick_CNT_NUM, &System_Tick_config);
}

/*******************************************************************************
* Function Name: System_Tick_Enable
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Enable_Multiple() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void System_Tick_Enable(void)                   
{
    Cy_TCPWM_Enable_Multiple(System_Tick_HW, System_Tick_CNT_MASK);
}


/*******************************************************************************
* Function Name: System_Tick_Disable
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Disable_Multiple() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void System_Tick_Disable(void)                  
{
    Cy_TCPWM_Disable_Multiple(System_Tick_HW, System_Tick_CNT_MASK);
}


/*******************************************************************************
* Function Name: System_Tick_GetStatus
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_GetStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t System_Tick_GetStatus(void)                
{
    return(Cy_TCPWM_Counter_GetStatus(System_Tick_HW, System_Tick_CNT_NUM));
}


#if(CY_TCPWM_COUNTER_MODE_CAPTURE == System_Tick_INIT_COMPARE_OR_CAPTURE)
    /*******************************************************************************
    * Function Name: System_Tick_GetCapture
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_GetCapture() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE uint32_t System_Tick_GetCapture(void)               
    {
        return(Cy_TCPWM_Counter_GetCapture(System_Tick_HW, System_Tick_CNT_NUM));
    }


    /*******************************************************************************
    * Function Name: System_Tick_GetCaptureBuf
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_GetCaptureBuf() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE uint32_t System_Tick_GetCaptureBuf(void)            
    {
        return(Cy_TCPWM_Counter_GetCaptureBuf(System_Tick_HW, System_Tick_CNT_NUM));
    }
#else
    /*******************************************************************************
    * Function Name: System_Tick_SetCompare0
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_SetCompare0() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE void System_Tick_SetCompare0(uint32_t compare0)      
    {
        Cy_TCPWM_Counter_SetCompare0(System_Tick_HW, System_Tick_CNT_NUM, compare0);
    }


    /*******************************************************************************
    * Function Name: System_Tick_GetCompare0
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_GetCompare0() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE uint32_t System_Tick_GetCompare0(void)              
    {
        return(Cy_TCPWM_Counter_GetCompare0(System_Tick_HW, System_Tick_CNT_NUM));
    }


    /*******************************************************************************
    * Function Name: System_Tick_SetCompare1
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_SetCompare1() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE void System_Tick_SetCompare1(uint32_t compare1)      
    {
        Cy_TCPWM_Counter_SetCompare1(System_Tick_HW, System_Tick_CNT_NUM, compare1);
    }


    /*******************************************************************************
    * Function Name: System_Tick_GetCompare1
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_GetCompare1() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE uint32_t System_Tick_GetCompare1(void)              
    {
        return(Cy_TCPWM_Counter_GetCompare1(System_Tick_HW, System_Tick_CNT_NUM));
    }


    /*******************************************************************************
    * Function Name: System_Tick_EnableCompareSwap
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_EnableCompareSwap() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE void System_Tick_EnableCompareSwap(bool enable)  
    {
        Cy_TCPWM_Counter_EnableCompareSwap(System_Tick_HW, System_Tick_CNT_NUM, enable);
    }
#endif /* (CY_TCPWM_COUNTER_MODE_CAPTURE == System_Tick_INIT_COMPARE_OR_CAPTURE) */


/*******************************************************************************
* Function Name: System_Tick_SetCounter
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_SetCounter() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void System_Tick_SetCounter(uint32_t count)          
{
    Cy_TCPWM_Counter_SetCounter(System_Tick_HW, System_Tick_CNT_NUM, count);
}


/*******************************************************************************
* Function Name: System_Tick_GetCounter
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_GetCounter() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t System_Tick_GetCounter(void)               
{
    return(Cy_TCPWM_Counter_GetCounter(System_Tick_HW, System_Tick_CNT_NUM));
}


/*******************************************************************************
* Function Name: System_Tick_SetPeriod
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_SetPeriod() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void System_Tick_SetPeriod(uint32_t period)          
{
    Cy_TCPWM_Counter_SetPeriod(System_Tick_HW, System_Tick_CNT_NUM, period);
}


/*******************************************************************************
* Function Name: System_Tick_GetPeriod
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_GetPeriod() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t System_Tick_GetPeriod(void)                
{
    return(Cy_TCPWM_Counter_GetPeriod(System_Tick_HW, System_Tick_CNT_NUM));
}


/*******************************************************************************
* Function Name: System_Tick_TriggerStart
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerStart() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void System_Tick_TriggerStart(void)             
{
    Cy_TCPWM_TriggerStart(System_Tick_HW, System_Tick_CNT_MASK);
}


/*******************************************************************************
* Function Name: System_Tick_TriggerReload
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerReloadOrIndex() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void System_Tick_TriggerReload(void)     
{
    Cy_TCPWM_TriggerReloadOrIndex(System_Tick_HW, System_Tick_CNT_MASK);
}


/*******************************************************************************
* Function Name: System_Tick_TriggerStop
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerStopOrKill() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void System_Tick_TriggerStop(void)
{
    Cy_TCPWM_TriggerStopOrKill(System_Tick_HW, System_Tick_CNT_MASK);
}


/*******************************************************************************
* Function Name: System_Tick_TriggerCapture
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerCaptureOrSwap() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void System_Tick_TriggerCapture(void)     
{
    Cy_TCPWM_TriggerCaptureOrSwap(System_Tick_HW, System_Tick_CNT_MASK);
}


/*******************************************************************************
* Function Name: System_Tick_GetInterruptStatus
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t System_Tick_GetInterruptStatus(void)       
{
    return(Cy_TCPWM_GetInterruptStatus(System_Tick_HW, System_Tick_CNT_NUM));
}


/*******************************************************************************
* Function Name: System_Tick_ClearInterrupt
****************************************************************************//**
*
* Invokes the Cy_TCPWM_ClearInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void System_Tick_ClearInterrupt(uint32_t source)     
{
    Cy_TCPWM_ClearInterrupt(System_Tick_HW, System_Tick_CNT_NUM, source);
}


/*******************************************************************************
* Function Name: System_Tick_SetInterrupt
****************************************************************************//**
*
* Invokes the Cy_TCPWM_SetInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void System_Tick_SetInterrupt(uint32_t source)
{
    Cy_TCPWM_SetInterrupt(System_Tick_HW, System_Tick_CNT_NUM, source);
}


/*******************************************************************************
* Function Name: System_Tick_SetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_TCPWM_SetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void System_Tick_SetInterruptMask(uint32_t mask)     
{
    Cy_TCPWM_SetInterruptMask(System_Tick_HW, System_Tick_CNT_NUM, mask);
}


/*******************************************************************************
* Function Name: System_Tick_GetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t System_Tick_GetInterruptMask(void)         
{
    return(Cy_TCPWM_GetInterruptMask(System_Tick_HW, System_Tick_CNT_NUM));
}


/*******************************************************************************
* Function Name: System_Tick_GetInterruptStatusMasked
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptStatusMasked() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t System_Tick_GetInterruptStatusMasked(void)
{
    return(Cy_TCPWM_GetInterruptStatusMasked(System_Tick_HW, System_Tick_CNT_NUM));
}

#endif /* System_Tick_CY_TCPWM_COUNTER_PDL_H */


/* [] END OF FILE */
