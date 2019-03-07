/**
 * @File    ULF.c
 * @Date    Friday, Mar. 1st 2019 at 09:41:12 PM BJT
 * @Author  Washington Ruan
 * @Email   ruanx@landicorp.com or washingtonxr@live.com
 *
 * This file contains the implementation of the gravity sensor device for motion detecting
 * module.
 *
 * @bug No known bugs.
 **/

/**
 * Function: Ultra Low Frequency module. 
 * Author: Xi Ruan
 * Date: Mar.1st,2019
 * E-mail: ruanx@landicorp.com
 **/

#include <string.h>
#include <math.h>
#include <project.h>
#include "ULF.h"
#include "debug.h"

static ulf_recv_value_t ULF_Recv_Val;
static ulf_trans_value_t ULF_Trans_Val;

static unsigned int ulf_transmit_id[2] = {0xff824006,0x18C350BC};
    
void ULF_SysInt_BasebandIn_start();
void ULF_SysInt_BasebandIn_stop();
void ULF_Carrier_Stop();

static void ULF_CarrierCnt_Isr();
static void ULF_MainCnt_Isr();
static void ULF_BasebandCnt_Isr();
static void ULF_BasebandIn_Isr();

#if 0
void ULF_SysInt_BasebandIn_start()
{
    /* Configure CM4+ CPU interrupt vector for SysInt_ULFBasebandIn_cfg. */
    Cy_SysInt_Init(&SysInt_ULFBasebandIn_cfg, ULF_BasebandIn_Isr);
    NVIC_ClearPendingIRQ(SysInt_ULFBasebandIn_cfg.intrSrc);
    NVIC_EnableIRQ((IRQn_Type)SysInt_ULFBasebandIn_cfg.intrSrc);
}

void ULF_SysInt_BasebandIn_stop()
{
    NVIC_ClearPendingIRQ(SysInt_ULFBasebandIn_cfg.intrSrc);
    NVIC_DisableIRQ((IRQn_Type)SysInt_ULFBasebandIn_cfg.intrSrc);
}
#endif

void ULF_Carrier_Stop()
{
#if 0
    Cy_TCPWM_TriggerStopOrKill(ULF_Carrier_HW, ULF_Carrier_CNT_MASK);
    Cy_TCPWM_Disable_Multiple(ULF_Carrier_HW, ULF_Carrier_CNT_MASK);
#else
    Cy_TCPWM_Counter_Disable(ULF_Carrier_HW, ULF_Carrier_CNT_MASK);
#endif
}

void ULF_Capture_Stop()
{
#if 0
    Cy_TCPWM_TriggerStopOrKill(ULF_Capture_HW, ULF_Capture_CNT_NUM);
    Cy_TCPWM_Disable_Multiple(ULF_Capture_HW, ULF_Capture_CNT_NUM);
#else
    Cy_TCPWM_Counter_Disable(ULF_Capture_HW, ULF_Capture_CNT_NUM);
#endif
}

/**
 * Ultra Low Frequency ISR.
 */
static unsigned char ULF_BO_BIT;
static unsigned int ULF_BO_BYTE;
static unsigned int ULF_Recv_Num;

static void ULF_CarrierCnt_Isr()
{
    int ret;
    unsigned char tmp_val;

    ret = ULF_Carrier_GetInterruptStatus();
    
    ULF_CTRL.ULF_TRANSMIT_CNT++;

    switch(ULF_CTRL.ULF_TRANSMIT_STATE){
        case 0: /* Warming Up. */
            if(ULF_CTRL.ULF_TRANSMIT_CNT > ULF_TRANS_GAP){
                ULF_CTRL.ULF_TRANSMIT_CNT = 0;
                ULF_CTRL.ULF_TRANSMIT_STATE  = 1;
                ULF_BO_BYTE = ulf_transmit_id[0];
            }
            break;
        case 1: /* Sending Raw Data. */
            /* Send Code. */
            if(ULF_CTRL.ULF_TRANSMIT_CNT == 1){
                /* Get data. */
                ULF_BO_BIT = (ULF_BO_BYTE >> 31) & 0x1;
                
                if(ULF_BO_BIT){
                    Cy_GPIO_Set(ULF_BO_PORT, ULF_BO_NUM);
                }else{
                    Cy_GPIO_Clr(ULF_BO_PORT, ULF_BO_NUM);
                }
            }else
            if(ULF_CTRL.ULF_TRANSMIT_CNT == ULF_MANCHISTER_P1){
                /* Get data. */
                ULF_BO_BIT = (ULF_BO_BYTE >> 31) & 0x1;
                
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
                    ULF_BO_BYTE = ulf_transmit_id[1];
                }else
                if(ULF_CTRL.ULF_TRANSMIT_DLEN == ULF_MANCHISTER_P2){
                    ULF_CTRL.ULF_TRANSMIT_STATE = 0;
                    ULF_CTRL.ULF_TRANSMIT_DLEN = 0;
                }
            }
            break;
        default: /* Never suppose to be here. */
            break;
    }

    if(1 == ULF_CTRL.ULF_RECEIVE_STATE){

        ULF_CTRL.ULF_RECEIVE_CNT++;

        if(ULF_RECV_LATCH_PT == ULF_CTRL.ULF_RECEIVE_CNT){          /* Latch Data. */
            
            /* Read the input state of ULF_IN_PORT */
            if(1UL == Cy_GPIO_Read(ULF_IN_PORT, ULF_IN_NUM)){
                tmp_val = 1;     /* Insert logic for High pin state */
            }else{
                tmp_val = 0;     /* Insert logic for Low pin state */
            }
            
            ULF_Recv_Val.ULF_RecvValue[ULF_CTRL.ULF_RECEIVE_PAGE] <<= 1;
            ULF_Recv_Val.ULF_RecvValue[ULF_CTRL.ULF_RECEIVE_PAGE] += tmp_val;
            
            ULF_Recv_Num++;
            ULF_Recv_Val.ULF_RecvBitNum++;
            
            if(ULF_Recv_Num >= 32){
                ULF_Recv_Num = 0;
                ULF_CTRL.ULF_RECEIVE_PAGE++;
            }

        }else
        if(ULF_CTRL.ULF_RECEIVE_CNT >= ULF_MANCHISTER_P2){    /* Go around. */

            if(ULF_Recv_Val.ULF_RecvBitNum >= 54){

                ULF_Recv_Num = 0;

                Cy_GPIO_Set(ULF_BB_PORT, ULF_BB_NUM);
                CyDelayUs(1);
                Cy_GPIO_Clr(ULF_BB_PORT, ULF_BB_NUM);
                
                ULF_CTRL.ULF_RECEIVE_NOTE = 1;
                ULF_CTRL.ULF_RECEIVE_STATE = 2;
            }
            ULF_CTRL.ULF_RECEIVE_CNT = 0;
        }
    }
    ULF_Carrier_ClearInterrupt(ret);

    return;
}

static void ULF_MainCnt_Isr()
{
    int ret;
    ret = ULF_Counter_GetInterruptStatus();
    
    ULF_CTRL.ULF_TRANSMIT_TIME++;
    
#if 0
    if(ULF_CTRL.ULF_TRANSMIT_TIME == 1024){
        ULF_Carrier_Start();
        Cy_GPIO_Set(ULF_BB_PORT, ULF_BB_NUM);
    }else if(ULF_CTRL.ULF_TRANSMIT_TIME >= 4096+1024){
        Cy_GPIO_Clr(ULF_BB_PORT, ULF_BB_NUM);
        ULF_Carrier_Stop();
        ULF_CTRL.ULF_TRANSMIT_TIME = 0;
    }
#endif

#if 0
    if(ULF_CTRL.ULF_TRANSMIT_BUSY == CONT){
        ULF_CTRL.ULF_TRANSMIT_BIT = 1;
        ULF_CTRL.ULF_TRANSMIT_DLEN ++;
    
        if(ULF_CTRL.ULF_TRANSMIT_BIT == 1)
            Cy_GPIO_Set(ULF_BB_PORT, ULF_BB_NUM);
        else
            Cy_GPIO_Clr(ULF_BB_PORT, ULF_BB_NUM);
        
        ULF_CTRL.ULF_TRANSMIT_BUSY = BUSY;
        ULF_CTRL.ULF_TRANSMIT_CNT = 0;
        
    }else if(ULF_CTRL.ULF_TRANSMIT_BUSY == BUSY){
        if(ULF_CTRL.ULF_TRANSMIT_CNT == ULF_MANCHISTER_P1){
            if(ULF_CTRL.ULF_TRANSMIT_BIT == 1)
                Cy_GPIO_Clr(ULF_BB_PORT, ULF_BB_NUM);
            else
                Cy_GPIO_Set(ULF_BB_PORT, ULF_BB_NUM);
        }else if(ULF_CTRL.ULF_TRANSMIT_CNT == ULF_MANCHISTER_P1){
            ULF_CTRL.ULF_TRANSMIT_CNT = 0;
            if(ULF_CTRL.ULF_TRANSMIT_DLEN >= 9){
                ULF_CTRL.ULF_TRANSMIT_BUSY = IDLE;
            }else{
                ULF_CTRL.ULF_TRANSMIT_BUSY = CONT;
            }

        }
    }else{
        ULF_CTRL.ULF_TRANSMIT_TIME = 0;
    }
#endif
#if 0
    switch(ULF_CTRL.ULF_TRANSMIT_BUSY){
        case CONT:
            ULF_CTRL.ULF_TRANSMIT_BIT = 1;
            ULF_CTRL.ULF_TRANSMIT_DLEN ++;
            if(ULF_CTRL.ULF_TRANSMIT_BIT == 1)
                Cy_GPIO_Set(ULF_BB_PORT, ULF_BB_NUM);
            else
                Cy_GPIO_Clr(ULF_BB_PORT, ULF_BB_NUM);
            
            ULF_CTRL.ULF_TRANSMIT_BUSY = BUSY;
            ULF_CTRL.ULF_TRANSMIT_TIME = 0;
            //ULF_Carrier_Start();
            return;
            
        case BUSY:
            switch(ULF_CTRL.ULF_TRANSMIT_TIME){
                case ULF_MANCHISTER_P1:
                    if(ULF_CTRL.ULF_TRANSMIT_BIT == 1)
                        Cy_GPIO_Clr(ULF_BB_PORT, ULF_BB_NUM);
                    else
                        Cy_GPIO_Set(ULF_BB_PORT, ULF_BB_NUM);
                case ULF_MANCHISTER_P2:
                        ULF_CTRL.ULF_TRANSMIT_TIME = 0;
                        //ULF_Carrier_Stop();
                        if(ULF_CTRL.ULF_TRANSMIT_DLEN >= 9){
                            ULF_CTRL.ULF_TRANSMIT_BUSY = IDLE;
                        }else{
                            ULF_CTRL.ULF_TRANSMIT_BUSY = CONT;
                        }
                default:
                    return;
            }
            return;
            
        case IDLE:
            return;
            
        default:
            return;
    }
#endif
    ULF_Counter_ClearInterrupt(ret);
    return;
}

static void ULF_Baseband_GetData(){
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
    
    if(ULF_Recv_Num >= 32){
        ULF_Recv_Num = 0;
        ULF_CTRL.ULF_RECEIVE_PAGE++;
    }
    
    ULF_CTRL.ULF_RECEIVE_CNT = 0;

    return;
}
#if 0
static unsigned char ULF_BB_GetNum;
static unsigned int ULF_BB_Counter[128];
static unsigned int ULF_BB_DCnt[128];
static unsigned int ULF_BB_PosCnt;
#endif
static void ULF_BasebandCnt_Isr()
{
    int ret;
    unsigned char time_last = 0;
    unsigned int i;
    
    ret = ULF_Capture_GetInterruptStatus();

    switch(ULF_CTRL.ULF_RECEIVE_STATE){
        case 0:     /* Latch Piolt. */
            /* Get Counter. */
            ULF_Recv_Val.ULF_RecvCurr_Data = ULF_Capture_GetCounter();
    
            if(0 == ULF_Recv_Val.ULF_RecvLock){
                ULF_Recv_Val.ULF_RecvPost_Data = ULF_Recv_Val.ULF_RecvCurr_Data;
                ULF_Recv_Val.ULF_RecvLock = 1;
            }else{
                if((ULF_RECV_LOW_TH0 < (ULF_Recv_Val.ULF_RecvCurr_Data - ULF_Recv_Val.ULF_RecvPost_Data)) && \
                    ((ULF_Recv_Val.ULF_RecvCurr_Data - ULF_Recv_Val.ULF_RecvPost_Data) < ULF_RECV_LOW_TH1)){
                    time_last = 1;
                }else
                if((ULF_RECV_HIGH_TH0 < (ULF_Recv_Val.ULF_RecvCurr_Data - ULF_Recv_Val.ULF_RecvPost_Data)) && \
                    ((ULF_Recv_Val.ULF_RecvCurr_Data - ULF_Recv_Val.ULF_RecvPost_Data) < ULF_RECV_HIGH_TH1)){
                    time_last = 2;
                }

                ULF_Recv_Val.ULF_RecvPost_Data = ULF_Recv_Val.ULF_RecvCurr_Data;   /* Move forward. */

                if(0 == ULF_CTRL.ULF_RECEIVE_START){
                    if(2 == time_last){
                        ULF_CTRL.ULF_RECEIVE_START = 1;
                    }
                }else{
                    if(ULF_Recv_Val.ULF_RecvPiolt_Num < ULF_RECV_PIOLT_CIR1){
                        if(1 == time_last){
                            ULF_Recv_Val.ULF_RecvPiolt_Num++;
                        }else{
                            goto Piolt_err;
                        }
                    }else if(ULF_Recv_Val.ULF_RecvPiolt_Num == ULF_RECV_PIOLT_CIR1){
                        if(2 == time_last){
                            Cy_GPIO_Set(ULF_BB_PORT, ULF_BB_NUM);
                            CyDelayUs(1);
                            Cy_GPIO_Clr(ULF_BB_PORT, ULF_BB_NUM);

                            //ULF_CTRL.ULF_RECEIVE_STATE = 0;
                            ULF_CTRL.ULF_RECEIVE_START = 0;
                            ULF_CTRL.ULF_RECEIVE_STATE = 1;
                            ULF_CTRL.ULF_RECEIVE_CNT = 0;
                            //goto Piolt_err;
                        }else{
                            goto Piolt_err;
                        }
                    }

                }
                
            }
        
        break;
        case 1:
#if 0
            if(ULF_RECV_LATCH_PT == ULF_CTRL.ULF_RECEIVE_CNT){          /* Latch Data. */

                /* Read the input state of ULF_IN_PORT */
                if(1UL == Cy_GPIO_Read(ULF_IN_PORT, ULF_IN_NUM)){
                    tmp_val = 1;     /* Insert logic for High pin state */
                }else{
                    tmp_val = 0;     /* Insert logic for Low pin state */
                }
                
                ULF_Recv_Val.ULF_RecvValue[ULF_CTRL.ULF_RECEIVE_PAGE] += tmp_val;
                ULF_Recv_Val.ULF_RecvValue[ULF_CTRL.ULF_RECEIVE_PAGE] <<= 1;

            }else if(ULF_CTRL.ULF_RECEIVE_CNT >= ULF_MANCHISTER_P2){    /* Go around. */
                ULF_Recv_Num++;
                ULF_Recv_Val.ULF_RecvBitNum++;
                
                if(ULF_Recv_Num >= 32){
                    ULF_Recv_Num = 0;
                    ULF_CTRL.ULF_RECEIVE_PAGE++;
                }

                if(ULF_Recv_Val.ULF_RecvBitNum >= 54){
                    ULF_CTRL.ULF_RECEIVE_NOTE = 1;
                }
                ULF_CTRL.ULF_RECEIVE_CNT = 0;
            }
#endif
        break;

        default:
        break;
    }
    
#if 0
    if(ULF_Recv_Val.ULF_RecvLock == 0){
#if 0
        Cy_GPIO_Set(ULF_BB_PORT, ULF_BB_NUM);
        CyDelayUs(1);
        Cy_GPIO_Clr(ULF_BB_PORT, ULF_BB_NUM);
#endif
        temp = ULF_Capture_GetCounter();
        
        ULF_BB_Counter[ULF_BB_GetNum++] = temp;

        if((256 - 64 < (temp - ULF_BB_PosCnt)) && ((temp - ULF_BB_PosCnt)< 256 + 64)){
            Cy_GPIO_Set(ULF_BB_PORT, ULF_BB_NUM);
            CyDelayUs(1);
            Cy_GPIO_Clr(ULF_BB_PORT, ULF_BB_NUM);
        }else 
        if((512 - 64 < (temp - ULF_BB_PosCnt)) && ((temp - ULF_BB_PosCnt)< 512 + 64 )){
            Cy_GPIO_Set(ULF_BB_PORT, ULF_BB_NUM);
            CyDelayUs(2);
            Cy_GPIO_Clr(ULF_BB_PORT, ULF_BB_NUM);
        }

        ULF_BB_PosCnt = ULF_Capture_GetCounter();
        
        if(ULF_BB_GetNum >= 0xff){
#if 1
            for(i = 1; i< ULF_BB_GetNum - 1; i++){
                if((256 - 64 < (ULF_BB_Counter[i] - ULF_BB_Counter[i-1])) && \
                    ((ULF_BB_Counter[i] - ULF_BB_Counter[i-1]) < 256 + 64)){
                    ULF_BB_DCnt[i] = 1;
                }else 
                if((512 - 64 < (ULF_BB_Counter[i] - ULF_BB_Counter[i-1])) && \
                    ((ULF_BB_Counter[i] - ULF_BB_Counter[i-1]) < 512 + 64)){
                    ULF_BB_DCnt[i] = 2;
                }
            }
#endif     
            ULF_Recv_Val.ULF_RecvLock = 1;
        }
    }
#endif

#if 0
    if(ULF_Recv_Val.ULF_RecvLock == 0){

        ULF_CTRL.ULF_RECEIVE_CNT++;
/* Latch First Edge of Baseband Signal. */
#if 1
        if(0 == ULF_Recv_Val.ULF_RecvBitNum){
            if(ULF_CTRL.ULF_RECEIVE_CNT >= ULF_RECV_D_OFFSET){
                ULF_Baseband_GetData();
            }
        }else{
            if(ULF_CTRL.ULF_RECEIVE_CNT >= 64){
                ULF_Baseband_GetData();

                if(ULF_Recv_Val.ULF_RecvBitNum >= (64*(ULF_RECV_BUF_DEPTH/2))){

                    ULF_Capture_Stop();
                
                    ULF_CTRL.ULF_RECEIVE_NOTE = 1;
                    ULF_Recv_Val.ULF_RecvLock = 1;
                }
            }
        }
#else
        if((64 - 16) == ULF_CTRL.ULF_RECEIVE_CNT){  /* Latch data from line. */

            /* Read the input state of ULF_IN_PORT */
            if(1UL == Cy_GPIO_Read(ULF_IN_PORT, ULF_IN_NUM)){
                tmp_val = 1;     /* Insert logic for High pin state */
            }else{
                tmp_val = 0;     /* Insert logic for Low pin state */
            }

            ULF_Recv_Num++;
            ULF_Recv_Val.ULF_RecvBitNum++;
            
            Cy_GPIO_Set(ULF_BB_PORT, ULF_BB_NUM);
            CyDelayUs(1);
            Cy_GPIO_Clr(ULF_BB_PORT, ULF_BB_NUM);
            
            if(ULF_Recv_Num >= 32){
                ULF_Recv_Num = 0;
                ULF_CTRL.ULF_RECEIVE_PAGE++;
            }
        
            ULF_Recv_Val.ULF_RecvValue[ULF_CTRL.ULF_RECEIVE_PAGE] <<= 1;
            ULF_Recv_Val.ULF_RecvValue[ULF_CTRL.ULF_RECEIVE_PAGE] += tmp_val;

        }else if(ULF_CTRL.ULF_RECEIVE_CNT >= 64){   /* Go along. */
                  
            ULF_Recv_Val.ULF_RecvTick += ULF_CTRL.ULF_RECEIVE_CNT;
        
            ULF_CTRL.ULF_RECEIVE_CNT = 0;
#if 0
            /* Read the input state of ULF_IN_PORT */
            if(1UL == Cy_GPIO_Read(ULF_IN_PORT, ULF_IN_NUM)){
                tmp_val = 1;     /* Insert logic for High pin state */
            }else{
                tmp_val = 0;     /* Insert logic for Low pin state */
            }

            ULF_Recv_Num++;
            ULF_Recv_Val.ULF_RecvBitNum++;
            
            if(ULF_Recv_Num >= 32){
                ULF_Recv_Num = 0;
                ULF_CTRL.ULF_RECEIVE_PAGE++;
            }
        
            ULF_Recv_Val.ULF_RecvValue[ULF_CTRL.ULF_RECEIVE_PAGE] <<= 1;
            ULF_Recv_Val.ULF_RecvValue[ULF_CTRL.ULF_RECEIVE_PAGE] += tmp_val;
#endif
            if(ULF_Recv_Val.ULF_RecvBitNum >= (64*(ULF_RECV_BUF_DEPTH/2))){
                ULF_CTRL.ULF_RECEIVE_NOTE = 1;
                ULF_Recv_Val.ULF_RecvLock = 1;
            }
        }
#endif
    }
#endif
    ULF_Capture_ClearInterrupt(ret);
    return;
Piolt_err:
    ULF_Recv_Val.ULF_RecvLock = 0;  /* Latch Piolt Error. */
    memset(&ULF_Recv_Val,0,sizeof(ULF_Recv_Val));
    return;
}

static void ULF_BasebandIn_Isr()
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
            CyDelayUs(2);
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
    /* Clear pin interrupt logic. Required to detect next interrupt */
    Cy_GPIO_ClearInterrupt(ULF_IN_PORT, ULF_IN_NUM);
}

/**
 * Ultra Low Frequency ULF_init.
 */
void ULF_Init()
{
    memset(&ULF_CTRL,0,sizeof(ULF_CTRL));
    memset(&ULF_DB,0,sizeof(ULF_DB));
    
    /* Configure CM4+ CPU interrupt vector for SysInt_ULFMainCnt_cfg PWM Generator. */
    Cy_SysInt_Init(&SysInt_ULFMainCnt_cfg, ULF_MainCnt_Isr);
    NVIC_ClearPendingIRQ(SysInt_ULFMainCnt_cfg.intrSrc);
    NVIC_EnableIRQ((IRQn_Type)SysInt_ULFMainCnt_cfg.intrSrc);
    
    /* Configure CM4+ CPU interrupt vector for SysInt_ULFCnt_cfg Timmer. */
    Cy_SysInt_Init(&SysInt_ULFCarrierCnt_cfg, ULF_CarrierCnt_Isr);
    NVIC_ClearPendingIRQ(SysInt_ULFCarrierCnt_cfg.intrSrc);
    NVIC_EnableIRQ((IRQn_Type)SysInt_ULFCarrierCnt_cfg.intrSrc);

    /* Configure CM4+ CPU interrupt vector for SysInt_ULFBasebandCnt_cfg Capture. */
    Cy_SysInt_Init(&SysInt_ULFBasebandCnt_cfg, ULF_BasebandCnt_Isr);
    NVIC_ClearPendingIRQ(SysInt_ULFBasebandCnt_cfg.intrSrc);
    NVIC_EnableIRQ((IRQn_Type)SysInt_ULFBasebandCnt_cfg.intrSrc);

    ULF_SysInt_BasebandIn_start();

#if 0
#if 0
    /* Configure CM4+ CPU interrupt vector for ULF_Cnt_Isr. */
    Cy_SysInt_Init(&SysInt_ULFCnt_cfg, ULF_Cnt_Isr);
    NVIC_ClearPendingIRQ(SysInt_ULFCnt_cfg.intrSrc);
    NVIC_EnableIRQ((IRQn_Type)SysInt_ULFCnt_cfg.intrSrc);
#else
    /* Start the PWM component */
    (void) Cy_TCPWM_PWM_Init(ULF_Carrier_HW, ULF_Carrier_CNT_NUM, &ULF_Carrier_config);
    Cy_TCPWM_Enable_Multiple(ULF_Carrier_HW, ULF_Carrier_CNT_MASK);
    Cy_TCPWM_TriggerStart(ULF_Carrier_HW, ULF_Carrier_CNT_MASK);
#endif
#endif
    return;
}

void ULF_Init2()
{
    memset(&ULF_CTRL,0,sizeof(ULF_CTRL));
    memset(&ULF_DB,0,sizeof(ULF_DB));
    memset(&ULF_Recv_Val,0,sizeof(ULF_Recv_Val));
    memset(&ULF_Trans_Val,0,sizeof(ULF_Trans_Val));

    /* Configure CM4+ CPU interrupt vector for SysInt_ULFBasebandCnt_cfg Capture. */
    Cy_SysInt_Init(&SysInt_ULFBasebandCnt_cfg, ULF_BasebandCnt_Isr);
    NVIC_ClearPendingIRQ(SysInt_ULFBasebandCnt_cfg.intrSrc);
    NVIC_EnableIRQ((IRQn_Type)SysInt_ULFBasebandCnt_cfg.intrSrc);

    ULF_Capture_Start();

    /* Configure CM4+ CPU interrupt vector for SysInt_ULFCnt_cfg Timmer. */
    Cy_SysInt_Init(&SysInt_ULFCarrierCnt_cfg, ULF_CarrierCnt_Isr);
    NVIC_ClearPendingIRQ(SysInt_ULFCarrierCnt_cfg.intrSrc);
    NVIC_EnableIRQ((IRQn_Type)SysInt_ULFCarrierCnt_cfg.intrSrc);

    ULF_Carrier_Start();
}

unsigned int ULF_Transmit()
{


    return 0;
}

unsigned int ULF_Receive()
{


    return 0;
}

unsigned int ULF_Encode()
{


    return 0;
}

unsigned int ULF_Decode_4100()
{

    unsigned int i;
    unsigned int CARD_RAW_DATA[2] = {0, 0};                /* First 9 Piolt bits. */

    CARD_RAW_DATA[0] = 0xFF800000;
    CARD_RAW_DATA[0] ^= (ULF_Recv_Val.ULF_RecvValue[0] >> 5);           /* Block 1 20bits.     */

    CARD_RAW_DATA[1] = (ULF_Recv_Val.ULF_RecvValue[0] & 0x1F);     /* 5bits. */
    CARD_RAW_DATA[1] ^= ULF_Recv_Val.ULF_RecvValue[1];              /* 27bit. */
    
    for(i = 0; i<= 1; i++){
        DEBUG_PRINTF("%08x ", CARD_RAW_DATA[i]);
    }
    DEBUG_PRINTF("\n");

    return 0;
}

unsigned int ULF_Test()
{

    if(ULF_CTRL.ULF_TRANSMIT_START == 1){
        
        ULF_Counter_Start();
        
        ULF_Carrier_Start();
        
        ULF_CTRL.ULF_TRANSMIT_BUSY = CONT;
        ULF_CTRL.ULF_TRANSMIT_START = 0;
    }

    DEBUG_PRINTF("Info(%08x):ULF_Test done.\n", Sys_counter);

#if 0
    switch(ULF_CTRL.ULF_TRANSMIT_STATE){
        case ULF_TRANS_STATE0:
            Cy_GPIO_Set(ULF_BB_PORT, ULF_BB_NUM);
            CyDelayUs(10);
            Cy_GPIO_Clr(ULF_BB_PORT, ULF_BB_NUM);
            ULF_Counter_Start();
            ULF_Carrier_Start();
            ULF_CTRL.ULF_TRANSMIT_STATE = ULF_TRANS_STATE1;
            return 0;

        case ULF_TRANS_STATE1:

            if(ULF_CTRL.ULF_TRANSMIT_CNT >= 125000){
                ULF_CTRL.ULF_TRANSMIT_CNT = 0;
                
                Cy_GPIO_Set(ULF_BB_PORT, ULF_BB_NUM);
                Cy_GPIO_Clr(ULF_BB_PORT, ULF_BB_NUM);
                
                Cy_TCPWM_TriggerStopOrKill(ULF_Carrier_HW, ULF_Carrier_CNT_MASK);

                ULF_CTRL.ULF_TRANSMIT_STATE = ULF_TRANS_STATE2;
            }
            ULF_CTRL.ULF_TRANSMIT_STATE = ULF_TRANS_STATE1;
            return 0;
            
        case ULF_TRANS_STATE2:

            Cy_GPIO_Set(ULF_BB_PORT, ULF_BB_NUM);
            Cy_GPIO_Clr(ULF_BB_PORT, ULF_BB_NUM);

            ULF_CTRL.ULF_TRANSMIT_STATE = ULF_TRANS_STATE3;
            return 0;
            
        case ULF_TRANS_STATE3:
            Cy_GPIO_Set(ULF_BB_PORT, ULF_BB_NUM);
            Cy_GPIO_Clr(ULF_BB_PORT, ULF_BB_NUM);

            ULF_CTRL.ULF_TRANSMIT_STATE = ULF_TRANS_STATE4;
            return 0;
            
        case ULF_TRANS_STATE4:
            Cy_GPIO_Set(ULF_BB_PORT, ULF_BB_NUM);
            Cy_GPIO_Clr(ULF_BB_PORT, ULF_BB_NUM);

            ULF_CTRL.ULF_TRANSMIT_STATE = ULF_TRANS_STATE0;
            return 0;
            
        default:
            return 0;
    }
#endif
    return 0;
}

int ULF_Routine()
{   
    unsigned char i;
#if 0    
    if(ULF_CTRL.ULF_RECEIVE_NOTE){
        ULF_CTRL.ULF_RECEIVE_NOTE = 0;

        DEBUG_PRINTF("Info(%08x):ULF_RECEIVE_NOTE\n", Sys_counter);

        for(i = 0; i< ULF_CTRL.ULF_RECEIVE_PAGE; i++){
            DEBUG_PRINTF("Info(%08x):%08x\n", Sys_counter, ULF_Recv_Val.ULF_RecvValue[i]);
        }

        memset(&ULF_Recv_Val, 0, sizeof(ULF_Recv_Val));

        ULF_CTRL.ULF_RECEIVE_CNT = 0;
        ULF_CTRL.ULF_RECEIVE_PAGE = 0;

        ULF_SysInt_BasebandIn_start();
    }
#endif
#if 0
    if(ULF_Recv_Val.ULF_RecvLock){

        for(i = 0; i< ULF_BB_GetNum; i++){
            //DEBUG_PRINTF("Info(%08x):%03d\t-->%08x(%d)\n", Sys_counter, i, ULF_BB_Counter[i], ULF_BB_DCnt[i]);
            DEBUG_PRINTF("%d", ULF_BB_DCnt[i]);
        }
        DEBUG_PRINTF("\n");
        ULF_BB_GetNum = 0;
        ULF_Recv_Val.ULF_RecvLock = 0;
    }
#endif
    if(ULF_CTRL.ULF_RECEIVE_NOTE){
        ULF_CTRL.ULF_RECEIVE_NOTE = 0;

        ULF_Decode_4100();
#if 0
        //DEBUG_PRINTF("Info(%08x):ULF_RECEIVE_NOTE\n", Sys_counter);
        for(i = 0; i<= ULF_CTRL.ULF_RECEIVE_PAGE; i++){
            DEBUG_PRINTF("%08x ", ULF_Recv_Val.ULF_RecvValue[i]);
        }
        
        DEBUG_PRINTF("\n");
#endif
        memset(&ULF_Recv_Val,0,sizeof(ULF_Recv_Val));
        memset(&ULF_CTRL,0,sizeof(ULF_CTRL));
    }

    return 0;
}






