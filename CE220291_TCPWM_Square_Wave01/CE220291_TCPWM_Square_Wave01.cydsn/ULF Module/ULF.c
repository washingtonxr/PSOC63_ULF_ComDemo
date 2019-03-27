/**
 * @File    ULF.c
 * @Date    Friday, Mar. 1st 2019 at 09:41:12 PM BJT
 * @Author  Washington Ruan
 * @Email   ruanx@landicorp.com or washingtonxr@live.com
 *
 * This file contains the implementation of the gravity sensor device for motion detecting
 * module.
 *
 * This file contains common code that is intended to be used across
 * boards so that it's not replicated.
 *
 * Copyright (C) 2019 Washington Ruan, washingtonxr@live.com
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 **/
/**
 * Version 1.
 * Function: Ultra Low Frequency module. 
 * Author: Xi Ruan
 * Date: Mar.1st,2019
 * E-mail: washingtonxr@live.com
 **/
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <project.h>
#include "ULF.h"
#include "debug.h"
#include "ULF_Carrier.h"

static ulf_ctrl_t ULF_CTRL;                    /* ULF Transmit Control. */
static ulf_user_db_t ULF_DB;                   /* ULF Control Database. */
static ulf_recv_value_t ULF_Recv_Val;
static ulf_trans_value_t ULF_Trans_Val;

#if 0
static unsigned int ulf_transmit_id[2] = {0xff824006, 0x18C350BC};
#endif
static void ULF_Carrier_Stop(void);
static void CarrierCnt_Isr_Disable(void);
static void CarrierCnt_Isr_Enable(void);
static void ULF_CarrierCnt_Isr(void);
static void ULF_Counter_Stop(void);
static void ULF_MainCnt_Isr(void);
static unsigned char ULF_Baseband_GetPeriod(unsigned int Curr_data, \
                                                    unsigned int Post_data);
static void ULF_BasebandCnt_Isr_Enable(void);
static void ULF_BasebandCnt_Isr_Disable(void);
static void ULF_MainCnt_Isr_Enable(void);
static void ULF_MainCnt_Isr_Disable(void);
static void ULF_BasebandCnt_Isr(void);
#if 0
static void ULF_BasebandIn_Isr(void);
#endif
static void ULF_FiledDetect_Disable(void);
static void ULF_FiledDetect_Enable(void);

#if 0
/**
* @func: ULF_SysInt_BasebandIn_start.
* @data: 0
* @retn: 0
* @node: NULL.
* @note: NULL.
* @auth: Washington Ruan
* @date: Mar.05th,2019
* @vers: v1.1
*
*/
void ULF_SysInt_BasebandIn_start(void)
{
    /* Configure CM4+ CPU interrupt vector for SysInt_ULFBasebandIn_cfg. */
    Cy_SysInt_Init(&SysInt_ULFBasebandIn_cfg, ULF_BasebandIn_Isr);
    NVIC_ClearPendingIRQ(SysInt_ULFBasebandIn_cfg.intrSrc);
    NVIC_EnableIRQ((IRQn_Type)SysInt_ULFBasebandIn_cfg.intrSrc);
    return;
}
/**
* @func: ULF_SysInt_BasebandIn_stop.
* @data: 0
* @retn: 0
* @node: NULL.
* @note: NULL.
* @auth: Washington Ruan
* @date: Mar.05th,2019
* @vers: v1.1
*
*/
void ULF_SysInt_BasebandIn_stop(void)
{
    NVIC_ClearPendingIRQ(SysInt_ULFBasebandIn_cfg.intrSrc);
    NVIC_DisableIRQ((IRQn_Type)SysInt_ULFBasebandIn_cfg.intrSrc);
    return;
}
#endif
/**
* @func: ULF_Carrier_Stop.
* @data: 0
* @retn: 0
* @node: NULL.
* @note: NULL.
* @auth: Washington Ruan
* @date: Mar.05th,2019
* @vers: v1.1
*
*/
static void ULF_Carrier_Stop(void)
{
#if 0
    Cy_TCPWM_TriggerStopOrKill(ULF_Carrier_HW, ULF_Carrier_CNT_MASK);
    Cy_TCPWM_Disable_Multiple(ULF_Carrier_HW, ULF_Carrier_CNT_MASK);
#endif
    Cy_TCPWM_PWM_Disable(ULF_Carrier_HW, ULF_Carrier_CNT_NUM);
    //Cy_TCPWM_PWM_DeInit(ULF_Carrier_HW, ULF_Carrier_CNT_NUM, &ULF_Carrier_config);
}
#if 0
/**
* @func: ULF_Capture_Stop.
* @data: 0
* @retn: 0
* @node: NULL.
* @note: NULL.
* @auth: Washington Ruan
* @date: Mar.05th,2019
* @vers: v1.1
*
*/
static void ULF_Capture_Stop(void)
{
#if 0
    Cy_TCPWM_TriggerStopOrKill(ULF_Capture_HW, ULF_Capture_CNT_NUM);
    Cy_TCPWM_Disable_Multiple(ULF_Capture_HW, ULF_Capture_CNT_NUM);
#else
    Cy_TCPWM_Counter_Disable(ULF_Capture_HW, ULF_Capture_CNT_NUM);
#endif
}
#endif
/**
* @func: ULF_Counter_Stop.
* @data: 0
* @retn: 0
* @node: NULL
* @note: NULL.
* @auth: Washington Ruan
* @date: Mar.05th,2019
* @vers: v1.1
*
*/
static void ULF_Counter_Stop(void)
{
#if 0
    Cy_TCPWM_TriggerStopOrKill(ULF_Capture_HW, ULF_Capture_CNT_NUM);
    Cy_TCPWM_Disable_Multiple(ULF_Capture_HW, ULF_Capture_CNT_NUM);
#else
    Cy_TCPWM_Counter_Disable(ULF_Counter_HW, ULF_Counter_CNT_NUM);
#endif
}
/**
* @func: CarrierCnt_Isr_Disable.
* @data: 0
* @retn: 0
* @node: NULL
* @note: NULL.
* @auth: Washington Ruan
* @date: Mar.07th,2019
* @vers: v1.2
*
*/
static void CarrierCnt_Isr_Disable(void)
{
    NVIC_ClearPendingIRQ(SysInt_ULFCarrierCnt_cfg.intrSrc);
    NVIC_DisableIRQ((IRQn_Type)SysInt_ULFCarrierCnt_cfg.intrSrc);
    return;
}
/**
* @func: CarrierCnt_Isr_Enable.
* @data: 0
* @retn: 0
* @node: NULL
* @note: Main carrier counter to latch baseband.
* @auth: Washington Ruan
* @date: Mar.07th,2019
* @vers: v1.2
*
*/
static void CarrierCnt_Isr_Enable(void)
{
    /* Configure CM4+ CPU interrupt vector for SysInt_ULFCnt_cfg Timmer. */
    Cy_SysInt_Init(&SysInt_ULFCarrierCnt_cfg, ULF_CarrierCnt_Isr);
    NVIC_ClearPendingIRQ(SysInt_ULFCarrierCnt_cfg.intrSrc);
    NVIC_EnableIRQ((IRQn_Type)SysInt_ULFCarrierCnt_cfg.intrSrc);
    return;
}
/**
* @func: ULF_CarrierCnt_Isr
* @data: unsigned int Curr_data and unsigned int Post_data
* @retn: 0
* @node: Null.
* @note: ISR set process:
*
*           0.Get interrupt notice.
*           1.Time counter when is reach ULF_T4100_PPDU_TXSIZE.
*           2.Check transmit round.
*               2.1.Disable Carrier Counter.
*               2.2.Stop Carrier transmiting.
*               2.3.Enable filed detecting.
*               2.4.Send notice.
*           3.Clear interrupt.
*
* @auth: Washington Ruan
* @date: Mar.21th,2019
* @vers: v1.2
*
*/
static void ULF_CarrierCnt_Isr(void)
{
    int ret;

    ret = ULF_Carrier_GetInterruptStatus();
    
    /* Time counter when is reach ULF_T4100_PPDU_TXSIZE. */
    if(ULF_CTRL.ULF_TRANSMIT_TIME++ >= ULF_T4100_PPDU_TXSIZE){
        ULF_CTRL.ULF_TRANSMIT_TIME = 0;

        /* Check transmit round. */
        if(ULF_CTRL.ULF_TRANSMIT_ROUND > 0){
            ULF_CTRL.ULF_TRANSMIT_ROUND--;
        }
        else
        {
            /* Disable Carrier Counter. */
            CarrierCnt_Isr_Disable();

            /* Stop Carrier transmiting. */
            ULF_Carrier_Stop();

            /* Enable filed detecting. */
            ULF_FiledDetect_Enable();

            /* Send notice. */
            ULF_CTRL.ULF_TRANSMIT_NOTE = CARRIER_TO;
        }    
    }
   
    ULF_Carrier_ClearInterrupt(ret);

    return;
}
/**
* @func: ULF_MainCnt_Isr.
* @data: unsigned int Curr_data and unsigned int Post_data
* @retn: 0
* @node: Maintenance a FSM for main carrier counter which is to absorb baseband data and set a case.
* @note: Main carrier counter to latch baseband.
* @auth: Washington Ruan
* @date: Mar.17th,2019
* @vers: v1.8
*
*/
static unsigned char ULF_BO_BIT;
static unsigned int ULF_BO_BYTE;
static unsigned int ULF_Recv_Num;
static void ULF_MainCnt_Isr(void)
{
    int ret;
    ret = ULF_Counter_GetInterruptStatus();

    ULF_CTRL.ULF_TRANSMIT_CNT++;
    
    switch(ULF_CTRL.ULF_TRANSMIT_STATE){
        case 0: /* Warming Up. */
            if(ULF_CTRL.ULF_TRANSMIT_CNT > ULF_TRANS_GAP){
                ULF_CTRL.ULF_TRANSMIT_CNT = 0;
                ULF_CTRL.ULF_TRANSMIT_STATE  = 1;
                //ULF_BO_BYTE = ulf_transmit_id[0];
                ULF_BO_BYTE = ULF_Trans_Val.ULF_TransValue[0];
            }
            break;
            
        case 1: /* Sending Raw Data. */
            /* Send Code. */
            if(ULF_CTRL.ULF_TRANSMIT_CNT == 1){
                /* Get data. */
                ULF_BO_BIT = (ULF_BO_BYTE >> (ULF_MANCHISTER_P1 - 1)) & 0x1;
                
                if(ULF_BO_BIT){
                    Cy_GPIO_Set(ULF_BO_PORT, ULF_BO_NUM);
                }else{
                    Cy_GPIO_Clr(ULF_BO_PORT, ULF_BO_NUM);
                }
            }else
            if(ULF_CTRL.ULF_TRANSMIT_CNT == ULF_MANCHISTER_P1){
                /* Get data. */
                ULF_BO_BIT = (ULF_BO_BYTE >> (ULF_MANCHISTER_P1 - 1)) & 0x1;
                
                if(ULF_BO_BIT){
                    Cy_GPIO_Clr(ULF_BO_PORT, ULF_BO_NUM);
                }else{
                    Cy_GPIO_Set(ULF_BO_PORT, ULF_BO_NUM);
                }
            }else
            if(ULF_CTRL.ULF_TRANSMIT_CNT == ULF_MANCHISTER_P2){
                
                ULF_CTRL.ULF_TRANSMIT_CNT = 0;
                
                ULF_BO_BYTE <<= 1;
                ULF_CTRL.ULF_TRANSMIT_DLEN++;
    
                if(ULF_CTRL.ULF_TRANSMIT_DLEN == ULF_MANCHISTER_P1){
                    //ULF_BO_BYTE = ulf_transmit_id[1];
                    ULF_BO_BYTE = ULF_Trans_Val.ULF_TransValue[1];
                }else
                if(ULF_CTRL.ULF_TRANSMIT_DLEN == ULF_MANCHISTER_P2){
                    ULF_CTRL.ULF_TRANSMIT_STATE = 2;
                    ULF_CTRL.ULF_TRANSMIT_DLEN = 0;
                }
            }
            break;
            
        case 2:
            if(ULF_CTRL.ULF_BBTRANS_ROUND > 0){
                ULF_CTRL.ULF_BBTRANS_ROUND--;
                ULF_CTRL.ULF_TRANSMIT_CNT = 0;
                ULF_CTRL.ULF_TRANSMIT_STATE = 0;
            }else{
                ULF_CTRL.ULF_TRANSMIT_STATE = 3;

                /* Clear Baseband Port. */
                Cy_GPIO_Clr(ULF_BO_PORT, ULF_BO_NUM);

                /* Check ULF Field exist or not. */
                if(1UL == Cy_GPIO_Read(SW3_PORT, SW3_NUM)){
                    
                    ULF_CTRL.ULF_BBTRANS_NOTE = BASEBAND_TO;
                    
                    ULF_MainCnt_Isr_Disable();
                    ULF_Counter_Stop();
                }else{
                    ULF_CTRL.ULF_BBTRANS_ROUND = 16;
                }
            }
            break;
            
        case 3:
            break;
        default: /* Never suppose to be here. */
            break;
    }
   
    ULF_Counter_ClearInterrupt(ret);
    return;
}
#if 0
/**
* @func: ULF_Baseband_GetData.
* @data: unsigned int Curr_data and unsigned int Post_data
* @retn: 0
* @node: Null
* @note: GetData.
* @auth: Washington Ruan
* @date: Mar.17th,2019
* @vers: v1.8
*
*/
static void ULF_Baseband_GetData(void){
    unsigned char tmp_val;
    /* Read the input state of ULF_IN_PORT */
    if(1UL == Cy_GPIO_Read(ULF_IN_PORT, ULF_IN_NUM)){
        tmp_val = 1;     /* Insert logic for High pin state */
    }else{
        tmp_val = 0;     /* Insert logic for Low pin state */
    }
    
    ULF_Recv_Num++;
    ULF_Recv_Val.ULF_RecvBitNum++;
    ULF_Recv_Val.ULF_RecvValue[ULF_CTRL.ULF_RECEIVE_PAGE] <<= 1;
    ULF_Recv_Val.ULF_RecvValue[ULF_CTRL.ULF_RECEIVE_PAGE] += tmp_val;
    
    if(ULF_Recv_Num >= ULF_T4100_PAGE_LEN){
        ULF_Recv_Num = 0;
        ULF_CTRL.ULF_RECEIVE_PAGE++;
    }
    /* Reset ULF_RECEIVE_CNT. */
    ULF_CTRL.ULF_RECEIVE_CNT = 0;

    return;
}
#endif
/**
* @func: ULF_Baseband_GetPeriod.
* @data: unsigned int Curr_data and unsigned int Post_data
* @retn: 
*           Default:     0
*           Phase 0:     1
*           Phase 2:     2
* @node: Null
* @note: GetPeriod of baseband from L1 layer.
* @auth: Washington Ruan
* @date: Mar.14th,2019
* @vers: v1.9
*
*/
static unsigned char ULF_Baseband_GetPeriod(unsigned int Curr_data, \
                                                    unsigned int Post_data)
{
    unsigned int temp;
    /* Compare T1 and set mean value. */
    if(Curr_data < Post_data){
        temp = (ULF_RECV_CAPTURE_PERIOD - Post_data) + Curr_data;
    }else{
        temp = Curr_data - Post_data;
    }
    
    /* Set date when Tx is defined. */
    if((ULF_RECV_LOW_TH0 < temp) && (temp < ULF_RECV_LOW_TH1)){
        return 1;
    }else 
    if((ULF_RECV_HIGH_TH0 < temp) && (temp < ULF_RECV_HIGH_TH1)){
        return 2;
    }
    return 0;
}
/**
* @func: ULF_BasebandCnt_Isr.
* @data: void
* @retn: 0
* @node: Null
* @note: Fix to interrupt initializing process.
* @auth: Washington Ruan
* @date: Mar.12th,2019
* @vers: v1.8
*
*/
static void ULF_BasebandCnt_Isr(void)
{
    int ret;
    unsigned char Isr_Period = 0;

    ret = ULF_Capture_GetInterruptStatus();

    switch(ULF_CTRL.ULF_RECEIVE_STATE){
        /* Latch Piolt. */
        case WARMUP:
            /* Get Counter. */
            ULF_Recv_Val.ULF_RecvCurr_Data = ULF_Capture_GetCounter();

            if(0 == ULF_Recv_Val.ULF_RecvLock){
                ULF_Recv_Val.ULF_RecvPost_Data = ULF_Recv_Val.ULF_RecvCurr_Data;
                ULF_Recv_Val.ULF_RecvLock = 1;
            }else{

                Isr_Period = ULF_Baseband_GetPeriod(ULF_Recv_Val.ULF_RecvCurr_Data, \
                                                    ULF_Recv_Val.ULF_RecvPost_Data);

                ULF_Recv_Val.ULF_RecvPost_Data = ULF_Recv_Val.ULF_RecvCurr_Data;        /* Move forward. */

                if(0 == ULF_CTRL.ULF_RECEIVE_START){
                    if(2 == Isr_Period){
                        ULF_CTRL.ULF_RECEIVE_START = 1;
                    }
                }else{
                    if(ULF_Recv_Val.ULF_RecvPiolt_Num < ULF_RECV_PIOLT_CIR1){
                        if(1 == Isr_Period){
                            ULF_Recv_Val.ULF_RecvPiolt_Num++;
                        }else{                                                          /* Restart Collect Piolt. */
                            ULF_Recv_Val.ULF_RecvPiolt_Num = 0;
                            break;                                                      /* Touch & Go. */
                        }

                        if(ULF_RECV_PIOLT_CIR1 == ULF_Recv_Val.ULF_RecvPiolt_Num){
                            ULF_CTRL.ULF_RECEIVE_START = 0;
                            ULF_CTRL.ULF_RECEIVE_STATE = BUSY;
                            ULF_CTRL.ULF_RECEIVE_CNT = 0;
                            ULF_Recv_Val.ULF_RecvBitNum = 0;
                        }
                    }
                }
            }
            break;
            
        /* Latch Data. */
        case BUSY:
            /* Get Counter. */
            ULF_Recv_Val.ULF_RecvCurr_Data = ULF_Capture_GetCounter();
            
            Isr_Period = ULF_Baseband_GetPeriod(ULF_Recv_Val.ULF_RecvCurr_Data, \
                                                ULF_Recv_Val.ULF_RecvPost_Data);
            if(Isr_Period <= 0){
                goto Piolt_err;
            }
            
            ULF_Recv_Val.ULF_RecvPost_Data = ULF_Recv_Val.ULF_RecvCurr_Data;            /* Move forward. */

            ULF_Recv_Val.ULF_Recv_PeriodBuf[ULF_Recv_Val.ULF_RecvPeri_Num++] = Isr_Period;

            ULF_Recv_Val.ULF_Recv_PeriHNum += Isr_Period;
            
            /* End of latching data status. */
            if(ULF_Recv_Val.ULF_Recv_PeriHNum >= (ULF_T4100_MPDU_LEN*2)){
                ULF_CTRL.ULF_RECEIVE_NOTE = 1;
                ULF_CTRL.ULF_RECEIVE_STATE = IDLE;
                ULF_Recv_Num = 0;
            }
            break;

        case IDLE:
            break;
        /* Not suppose to be here. */
        default:
            break;
    }
    
    /* Clear Interrupt. */
    ULF_Capture_ClearInterrupt(ret);
    return;
Piolt_err:
    /* Reset all things. */
    ULF_Recv_Num = 0;
    memset(&ULF_Recv_Val, 0, sizeof(ULF_Recv_Val));
    memset(&ULF_CTRL, 0, sizeof(ULF_CTRL));
    return;
}
#if 0
/**
* @func: ULF_BasebandIn_Isr.
* @data: void
* @retn: 0
* @node: Null
*
* @auth: Washington Ruan
* @date: Mar.05th,2019
* @vers: v1.0
*
*/
static void ULF_BasebandIn_Isr(void)
{
#if 1
    int ret;
#endif
    /* Optional check to determine if one pin in the port generated interrupt. */
    if(Cy_GPIO_GetInterruptStatus(ULF_IN_PORT, ULF_IN_NUM) == CY_GPIO_INTR_STATUS_MASK)
    {
#if 1
        ret = Cy_GPIO_GetInterruptEdge(ULF_IN_PORT, ULF_IN_NUM);
        if(CY_GPIO_INTR_RISING == ret){
            Cy_GPIO_Set(ULF_BB_PORT, ULF_BB_NUM);
            CyDelayUs(1);
            Cy_GPIO_Clr(ULF_BB_PORT, ULF_BB_NUM);
        }else if(CY_GPIO_INTR_FALLING == ret){
            Cy_GPIO_Set(ULF_BB_PORT, ULF_BB_NUM);
            CyDelayUs(1);
            Cy_GPIO_Clr(ULF_BB_PORT, ULF_BB_NUM);
        }
#endif
#if 0
        ULF_CTRL.ULF_RECEIVE_START = 1;

        /* Stop BasebandIn Isr, Start& reload BasebandCnt. */
        ULF_SysInt_BasebandIn_stop();

        ULF_Capture_Start();

        memset(&ULF_Recv_Val, 0, sizeof(ULF_Recv_Val));

        ULF_CTRL.ULF_RECEIVE_CNT = 0;

        ULF_Recv_Num = 0;
#endif
    }
    /* Clear interrupt sign and prepare for next detecting. */
    Cy_GPIO_ClearInterrupt(ULF_IN_PORT, ULF_IN_NUM);
    return;
}
#endif
/**
* @func: ULF_BasebandCnt_Isr_Enable.
* @data: void
* @retn: 0
* @node: Null
*
* @auth: Washington Ruan
* @date: Mar.05th,2019
* @vers: v1.0
*
*/
static void ULF_BasebandCnt_Isr_Enable(void)
{
    /* Configure CM4+ CPU interrupt vector for SysInt_ULFBasebandCnt_cfg Capture. */
    Cy_SysInt_Init(&SysInt_ULFBasebandCnt_cfg, ULF_BasebandCnt_Isr);
    NVIC_ClearPendingIRQ(SysInt_ULFBasebandCnt_cfg.intrSrc);
    NVIC_EnableIRQ((IRQn_Type)SysInt_ULFBasebandCnt_cfg.intrSrc);
    return;
}
/**
* @func: ULF_BasebandCnt_Isr_Disable.
* @data: void
* @retn: 0
* @node: Null
*
* @auth: Washington Ruan
* @date: Mar.05th,2019
* @vers: v1.0
*
*/
static void ULF_BasebandCnt_Isr_Disable(void)
{
    NVIC_ClearPendingIRQ(SysInt_ULFBasebandCnt_cfg.intrSrc);
    NVIC_DisableIRQ((IRQn_Type)SysInt_ULFBasebandCnt_cfg.intrSrc);
    return;
}
/**
* @func: ULF_MainCnt_Isr_Enable.
* @data: void
* @retn: 0
* @node: Null
*
* @auth: Washington Ruan
* @date: Mar.05th,2019
* @vers: v1.0
*
*/
static void ULF_MainCnt_Isr_Enable(void)
{ 
    /* Configure CM4+ CPU interrupt vector for SysInt_ULFMainCnt_cfg PWM Generator. */
    Cy_SysInt_Init(&SysInt_ULFMainCnt_cfg, ULF_MainCnt_Isr);
    NVIC_ClearPendingIRQ(SysInt_ULFMainCnt_cfg.intrSrc);
    NVIC_EnableIRQ((IRQn_Type)SysInt_ULFMainCnt_cfg.intrSrc);
    return;
}
/**
* @func: ULF_MainCnt_Isr_Disable.
* @data: void
* @retn: 0
* @node: Null
*
* @auth: Washington Ruan
* @date: Mar.05th,2019
* @vers: v1.0
*
*/
static void ULF_MainCnt_Isr_Disable(void)
{
    NVIC_ClearPendingIRQ(SysInt_ULFMainCnt_cfg.intrSrc);
    NVIC_DisableIRQ((IRQn_Type)SysInt_ULFMainCnt_cfg.intrSrc);
    return;
}
/**
* @func: Ultra Low Frequency ULF_init.
* @data: void
* @retn: 0
* @node: Null
*
* Note: 1.Initializing all Control and spec.
*       2.Disable ULF Field Detecting.
*
* @auth: Washington Ruan
* @date: Mar.07th,2019
* @vers: v1.0
*
*/
void ULF_Init(void)
{
    /* Initializing all Control and spec. */
    memset(&ULF_CTRL, 0, sizeof(ULF_CTRL));
    memset(&ULF_DB, 0, sizeof(ULF_DB));
    memset(&ULF_Recv_Val, 0, sizeof(ULF_Recv_Val));
    memset(&ULF_Trans_Val, 0, sizeof(ULF_Trans_Val));
   
    /* Disable ULF Field Detecting. */
    ULF_CTRL.ULF_DETECT_CARRIER = 1;

    return;
}
/**
* @func: ULF_FiledDetect_Disable.
* @data: void
* @retn: 0
* @node: Null
*
* Note: 1.Set ULF_DETECT_CARRIER.
*       2.Disable transmit counter & ISR.
*       3.Clear TXen pin.
*       4.Clear ULF_BO pin.
*       5.Reset Trans Carrier time.
*
* @auth: Washington Ruan
* @date: Mar.08th,2019
* @vers: v1.3
*
*/
static void ULF_FiledDetect_Disable(void)
{
    /* Disable ULF Field Detecting. */
    ULF_CTRL.ULF_DETECT_CARRIER = 0;

    /* Disable transmit counter & ISR. */
    ULF_MainCnt_Isr_Disable();

    /* Clear TXen pin. */
    Cy_GPIO_Clr(ULF_TXen_PORT, ULF_TXen_NUM);

    /* Clear ULF_BO pin. */
    Cy_GPIO_Clr(ULF_BO_PORT, ULF_BO_NUM);
   
    /* Reset Trans Carrier time. */
    ULF_CTRL.ULF_TRANSMIT_TIME = 0;
}
/**
* @func: ULF_FiledDetect_Enable.
* @data: void
* @retn: 0
* @node: Null
*
* Note: Just set ULF_TXen_PORT and ULF_DETECT_CARRIER.
* @auth: Washington Ruan
* @date: Mar.08th,2019
* @vers: v0.1
*
*/
static void ULF_FiledDetect_Enable(void)
{
    /* Enable TXen pin. */
    Cy_GPIO_Set(ULF_TXen_PORT, ULF_TXen_NUM);

    /* Enable ULF Field Detecting. */
    ULF_CTRL.ULF_DETECT_CARRIER = 1;
}
/**
* @func: Transmit exit.
* @data: void
* @retn: 0
* @node: NUMA node that we want to schedule this on or close to
*
* Note: This function is for Transmit Carrier and wait for L1 data form a card.
* @auth: Washington Ruan
* @date: Mar.08th,2019
* @vers: v0.1
*
*/
unsigned int ULF_Transmit_Exit(void)
{
    //ULF_CTRL.ULF_DETECT_CARRIER = 0;

    Cy_GPIO_Clr(ULF_BO_PORT, ULF_BO_NUM);
#if 0
    /* Clear TXen pin. */
    Cy_GPIO_Clr(ULF_TXen_PORT, ULF_TXen_NUM);
#endif
    ULF_MainCnt_Isr_Disable();

    ULF_Counter_Stop();
    
    ULF_CTRL.ULF_DETECT_CARRIER = 1;

    return 0;
}
/**
* @func: Transmit baseband to L1.(4100).
* @data: ulf_userdb_t *userdb, unsigned char round.
*           This layer needa check userdb->option and round parameter before it's sending.
* @retn: 0
* @node: NUMA node that we want to schedule this on or close to
*
* Note: This function is for Transmit Baseband for a card.
* @auth: Washington Ruan
* @date: Mar.11th,2019
* @vers: v0.4
*
*/
unsigned int ULF_Transmit(ulf_userdb_t *userdb, unsigned short round)
{
    int i;

    if(0 != ULF_CTRL.ULF_DETECT_CARRIER){

        if((1 == userdb->option) && (round > 0)){

            ULF_CTRL.ULF_TRANSMIT_CNT = 0;
            ULF_CTRL.ULF_TRANSMIT_STATE = 0;
            ULF_CTRL.ULF_BBTRANS_ROUND = round;
        
            /* Set ID. */
            memcpy(ULF_Trans_Val.ULF_TransValue, userdb->raw_data, sizeof(userdb->raw_data));
        
            if(ULF_Trans_Val.ULF_TransValue[0] != 0 ){
                
                /* Disable reader. */
                ULF_BasebandCnt_Isr_Disable();
                
                /* Enable card simulator. */
                ULF_MainCnt_Isr_Enable();
                
                /* Baseband transmit counter start. */
                ULF_Counter_Start();
                
                /* Push Transmit ID. */
                DEBUG_PRINTF("Info(%08X):Transmit ID =>> ", Sys_counter);
                for(i = 0; i < 10; i++){
                    DEBUG_PRINTF("%1X", userdb->pure_data[i]);
                }
                DEBUG_PRINTF("\n");
                
            }else{
                DEBUG_PRINTF("Error(%08X):No vailid card ID.\n", Sys_counter);
            }
        }
    }else{
        DEBUG_PRINTF("Info(%08X):Transmit machine is not ready.\n", Sys_counter);
    }
    return 0;
}
/**
* @func: Transmit Carrier and prepare to detect card.(4100).
* @data: ulf_userdb_t *userdb, unsigned char round.
* @retn: 0
* @node: NUMA node that we want to schedule this on or close to
*
* Note: This function is for Transmit Carrier and wait for L1 data form a card.
* @auth: Washington Ruan
* @date: Mar.11th,2019
* @vers: v0.4
*
*/
unsigned int ULF_Receive(ulf_userdb_t *userdb, unsigned char round)
{
    /* Start Carrier. */
    if((1 == userdb->option) && (round > 0)){    /* T4100:1 ... */     
        /* Set try round. */
        ULF_CTRL.ULF_TRANSMIT_ROUND = round;
        
        /* Disable transmit counter & ISR. */
        ULF_MainCnt_Isr_Disable();
    
        /* Disable Detecting. */
        ULF_FiledDetect_Disable();
        
        /* Enable Carrier Counter. */
        CarrierCnt_Isr_Enable();
        
        /* ULF Carrier engine start. */
        ULF_Carrier_Start();
        
        /* Capture for ULF baseband. */
        ULF_Capture_Start();
        
        /* Enable Baseband Counter ISR. */
        ULF_BasebandCnt_Isr_Enable();
    }
    return 0;
}
/**
* @func: ULF_Encode(4100).
* @data: void.
* @retn: 0
* @node: NUMA node that we want to schedule this on or close to
*
* Note: This function is under TBD.
* @auth: Washington Ruan
* @date: Mar.12th,2019
* @vers: v0.1
*
*/
unsigned int ULF_Encode(void)
{
    return 0;
}
 /**
 * @func: Ultra Low Frequency Decode module(4100).
 * @data: input is ULF_Recv_Val.
 * @retn: 0
 * @node: NUMA node that we want to schedule this on or close to
 *
 * Note: This function may be called from atomic or non-atomic contexts.
 * @auth: Washington Ruan
 * @date: Mar.26th,2019
 * @vers: v1.5
 *
 */
unsigned int ULF_Decode_L1_T4100(void)
{
    unsigned short i;
    unsigned char tempbuf = 0;
    
    unsigned char ULF_Decode_start = 0;
    unsigned char ULF_RecvLock_Bit = 0;
    unsigned char ULF_RecvCurr_Period = 0;
    unsigned char ULF_RecvPost_Period = 0;
    unsigned char ULF_RecvPost_Bit = 0;
    
#if (ULF_Debug == 1)
    DEBUG_PRINTF("Info(%08x):ULF_Recv_PeriodBuf\n", Sys_counter);
    for(i = 0; i<= ULF_Recv_Val.ULF_RecvPeri_Num; i++){
        DEBUG_PRINTF("%d ", ULF_Recv_Val.ULF_Recv_PeriodBuf[i]);
    }
    DEBUG_PRINTF("\n");
#endif
    for(i = 0; i<= ULF_Recv_Val.ULF_RecvPeri_Num; i++){
        
        tempbuf = ULF_Recv_Val.ULF_Recv_PeriodBuf[i];
    
        if(0 == ULF_RecvLock_Bit){
            if(1 == tempbuf){
                ULF_Decode_start = 0;
            }else 
            if(2 == tempbuf){
                ULF_Decode_start = 1;
                ULF_RecvPost_Period = tempbuf;
            }
            
            ULF_RecvLock_Bit = 1;
            ULF_RecvPost_Bit = 1;
        }else{
            if(ULF_Decode_start){

                ULF_Decode_start = 0;
                
                ULF_RecvCurr_Period = tempbuf;
                
                ULF_Recv_Val.ULF_RecvValue[ULF_CTRL.ULF_RECEIVE_PAGE] <<= 1;
                
                if(ULF_RecvPost_Period != ULF_RecvCurr_Period){
                    if((1 == ULF_RecvPost_Period) && (2 == ULF_RecvCurr_Period)){
                        ULF_Recv_Val.ULF_RecvValue[ULF_CTRL.ULF_RECEIVE_PAGE] += ULF_RecvPost_Bit;
                        ULF_RecvPost_Period = 2;
                        ULF_Decode_start = 1;
                    }else
                    if((2 == ULF_RecvPost_Period) && (1 == ULF_RecvCurr_Period)){
                        
                        if(1 == ULF_RecvPost_Bit){
                            ULF_Recv_Val.ULF_RecvValue[ULF_CTRL.ULF_RECEIVE_PAGE] += 0;
                            ULF_RecvPost_Bit = 0;
                        }else{
                            ULF_Recv_Val.ULF_RecvValue[ULF_CTRL.ULF_RECEIVE_PAGE] += 1;
                            ULF_RecvPost_Bit = 1;
                        }
                    }
                }else{
                    if(1 == ULF_RecvPost_Period){
                        ULF_Recv_Val.ULF_RecvValue[ULF_CTRL.ULF_RECEIVE_PAGE] += ULF_RecvPost_Bit;
                    }else
                    if(2 == ULF_RecvPost_Period){
                        if(1 == ULF_RecvPost_Bit){
                            ULF_Recv_Val.ULF_RecvValue[ULF_CTRL.ULF_RECEIVE_PAGE] += 0;
                            ULF_RecvPost_Bit = 0;
                        }else{
                            ULF_Recv_Val.ULF_RecvValue[ULF_CTRL.ULF_RECEIVE_PAGE] += 1;
                            ULF_RecvPost_Bit = 1;
                        }
                        ULF_RecvPost_Period = 2;
                        ULF_Decode_start = 1;
                    }
                }
                
                ULF_Recv_Val.ULF_RecvBitNum ++;

                ULF_Recv_Num++;
                if(ULF_Recv_Num >= 32){
                    ULF_Recv_Num = 0;
                    ULF_CTRL.ULF_RECEIVE_PAGE++;
                }
            }else{
                ULF_RecvPost_Period = tempbuf;
                ULF_Decode_start = 1;
            }
        }
    }
    
#if (ULF_Debug == 1)
    DEBUG_PRINTF("\n");
    DEBUG_PRINTF("Info(%08x):Card RAW data:\n", Sys_counter);
    for(i = 0; i<= ULF_CTRL.ULF_RECEIVE_PAGE; i++){
        DEBUG_PRINTF("%08x ", ULF_Recv_Val.ULF_RecvValue[i]);
    }
    DEBUG_PRINTF("\n");
#endif
    return 0;
}
/**
 * @func: Function for ULF_Decode_L2_T4100
 * @data: Data pointer to pass to the function, ulf_userdb_t
 * @retn: 
 *          Correct:    0
 *          Error:      1
 * @node: NUMA node that we want to schedule this on or close to
 *
 * Note: This function may be called from atomic or non-atomic contexts.
 * @auth: Washington Ruan
 * @date: Mar.26th,2019
 * @vers: v1.7
 *
 */
unsigned int ULF_Decode_L2_T4100(ulf_userdb_t *userdb)
{
    unsigned char i, j;
    unsigned int CARD_RAW_DATA[2] = {0, 0};                             /* First 9 Piolt bits.  */
    unsigned char CARD_SDATA[11] = {0,};
    unsigned char CARD_DATA[10] = {0,};
    unsigned char CRCx[11] = {0,}, CRCy[4] = {0,};
    
    CARD_RAW_DATA[0] = ULF_Recv_Val.ULF_RecvValue[0] >> 9;              /* Block 1:(23)bits.     */
    CARD_RAW_DATA[0] ^= 0xFF800000;

    CARD_RAW_DATA[1] = (ULF_Recv_Val.ULF_RecvValue[0] & 0x1FF);         /* Block 2:(23 + 9)bits. */
    CARD_RAW_DATA[1] <<= 23;
    CARD_RAW_DATA[1] ^= ULF_Recv_Val.ULF_RecvValue[1];

#if (ULF_Debug == 1)
    for(i = 0; i<= ULF_CTRL.ULF_RECEIVE_PAGE; i++){
        DEBUG_PRINTF("%08x ", CARD_RAW_DATA[i]);
    }
    DEBUG_PRINTF("\n");
#endif

    for(i = 0; i < 6; i++){
        CARD_SDATA[i] = (ULF_Recv_Val.ULF_RecvValue[0] >> (32 - 5*(1+i))) & 0x1F;
    }
    
    CARD_SDATA[6] = (ULF_Recv_Val.ULF_RecvValue[0] & 0x03);
    CARD_SDATA[6] <<= 3;
    CARD_SDATA[6] += ULF_Recv_Val.ULF_RecvValue[1] >> 20;
    
    for(i = 0; i < 3; i++){
        CARD_SDATA[7 + i] += (ULF_Recv_Val.ULF_RecvValue[1] >> (5*(3-i))) & 0x1F;
    }
    
    CARD_SDATA[10] = ULF_Recv_Val.ULF_RecvValue[1] & 0x1F;
#if (ULF_Debug == 1)
    for(i = 0; i < 11; i++){
        DEBUG_PRINTF("%02d:%08x\n", i, CARD_SDATA[i]);
    }
#endif

    /* Check CRC for each column. */
    for(i = 0; i < 10; i++){
        for(j = 0; j < 5; j++){
            CRCx[i] ^= ( CARD_SDATA[i] & (0x10 >> j)) >> (4 - j);
        }
        if(0 != CRCx[i]){
            return 0;
        }
    }
    /* Check CRC for each row. */
    for(i = 0; i < 4; i++){
        for(j = 0; j < 11; j++){
            CRCy[i] ^= ( CARD_SDATA[j] & (0x10 >> (2*i))) >> (4 - i);
        }
        if(0 != CRCy[i]){
            return 0;
        }
    }

#if (ULF_Debug == 1)
    for(i = 0; i < 10; i++){
        DEBUG_PRINTF("%02x ", CRCx[i]);
    }
    DEBUG_PRINTF("\n");
    for(i = 0; i < 4; i++){
        DEBUG_PRINTF("%02x ", CRCy[i]);
    }
    DEBUG_PRINTF("\n");
#endif

    for(i = 0; i < 10; i++){
        CARD_DATA[i] = CARD_SDATA[i] >> 1;
    }

    memcpy(userdb->raw_data, CARD_RAW_DATA, sizeof(CARD_RAW_DATA));
    memcpy(userdb->pure_data, CARD_DATA, sizeof(CARD_DATA));
    
    return 0;
}

/**
 * @func: Function for Routine
 * @data: Data pointer to pass to the function
 * @retn: 
 *          Get a card ID:              GETCARD_INFO
 *          Carrier transmit timeout:   CARRIER_TO
 *          Baseband transmit timeout:  BASEBAND_TO
 * @node: NUMA node that we want to schedule this on or close to
 *
 * Note: This function may be called from atomic or non-atomic contexts.
 * @auth: Washington Ruan
 * @date: Mar.26th,2019
 * @vers: v2.3
 * The node requested will be honored on a best effort basis. If the node
 * has no CPUs associated with it then the work is distributed among all
 * available CPUs.
 */
int ULF_Routine(ulf_userdb_t *userdb)
{
    int i;

    if(ULF_CTRL.ULF_RECEIVE_NOTE){
        ULF_CTRL.ULF_RECEIVE_NOTE = 0;
        
        /* Latch L1 data flow. */
        ULF_Decode_L1_T4100();
    
        /* Decode 4100 RAW data. */
        ULF_Decode_L2_T4100(userdb);

        if((0 != userdb->raw_data[0])||(0 != userdb->raw_data[1])){
            DEBUG_PRINTF("Info(%08X):Receive ID =>> ", Sys_counter);
            for(i = 0; i < 10; i++){
                DEBUG_PRINTF("%1X", userdb->pure_data[i]);
            }
            DEBUG_PRINTF("\n");
        }
#if 1
        ULF_CTRL.ULF_RECEIVE_STATE = WARMUP;
        ULF_CTRL.ULF_RECEIVE_PAGE = 0;
        ULF_CTRL.ULF_RECEIVE_CNT = 0;
#endif
        /* Reset ULF_Recv_Val database tempratory. */
        memset(&ULF_Recv_Val, 0, sizeof(ULF_Recv_Val));

        return GETCARD_INFO;
    }

    if(CARRIER_TO == ULF_CTRL.ULF_TRANSMIT_NOTE){
        ULF_CTRL.ULF_TRANSMIT_NOTE = 0;
        return CARRIER_TO;
    }
    
    if(BASEBAND_TO == ULF_CTRL.ULF_BBTRANS_NOTE){
        ULF_CTRL.ULF_BBTRANS_NOTE = 0;
        return BASEBAND_TO;
    }
    return 0;
}

/* The end of file. */

