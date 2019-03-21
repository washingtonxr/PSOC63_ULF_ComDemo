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
static void ULF_BasebandIn_Isr(void);
static void ULF_FiledDetect_Disable(void);
static void ULF_FiledDetect_Enable(void);

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

static void ULF_Carrier_Stop(void)
{
#if 0
    Cy_TCPWM_TriggerStopOrKill(ULF_Carrier_HW, ULF_Carrier_CNT_MASK);
    Cy_TCPWM_Disable_Multiple(ULF_Carrier_HW, ULF_Carrier_CNT_MASK);
#endif
    Cy_TCPWM_PWM_Disable(ULF_Carrier_HW, ULF_Carrier_CNT_NUM);
    //Cy_TCPWM_PWM_DeInit(ULF_Carrier_HW, ULF_Carrier_CNT_NUM, &ULF_Carrier_config);
}

static void ULF_Capture_Stop(void)
{
#if 0
    Cy_TCPWM_TriggerStopOrKill(ULF_Capture_HW, ULF_Capture_CNT_NUM);
    Cy_TCPWM_Disable_Multiple(ULF_Capture_HW, ULF_Capture_CNT_NUM);
#else
    Cy_TCPWM_Counter_Disable(ULF_Capture_HW, ULF_Capture_CNT_NUM);
#endif
}

static void ULF_Counter_Stop(void)
{
#if 0
    Cy_TCPWM_TriggerStopOrKill(ULF_Capture_HW, ULF_Capture_CNT_NUM);
    Cy_TCPWM_Disable_Multiple(ULF_Capture_HW, ULF_Capture_CNT_NUM);
#else
    Cy_TCPWM_Counter_Disable(ULF_Counter_HW, ULF_Counter_CNT_NUM);
#endif
}

static void CarrierCnt_Isr_Disable(void)
{
    NVIC_ClearPendingIRQ(SysInt_ULFCarrierCnt_cfg.intrSrc);
    NVIC_DisableIRQ((IRQn_Type)SysInt_ULFCarrierCnt_cfg.intrSrc);
}

static void CarrierCnt_Isr_Enable(void)
{
    /* Configure CM4+ CPU interrupt vector for SysInt_ULFCnt_cfg Timmer. */
    Cy_SysInt_Init(&SysInt_ULFCarrierCnt_cfg, ULF_CarrierCnt_Isr);
    NVIC_ClearPendingIRQ(SysInt_ULFCarrierCnt_cfg.intrSrc);
    NVIC_EnableIRQ((IRQn_Type)SysInt_ULFCarrierCnt_cfg.intrSrc);
}

/**
 * Ultra Low Frequency ISR.
 */
static void ULF_CarrierCnt_Isr()
{
    int ret;

    ret = ULF_Carrier_GetInterruptStatus();

    if(ULF_CTRL.ULF_TRANSMIT_TIME++ >= ULF_T4100_PPDU_TXSIZE){
        ULF_CTRL.ULF_TRANSMIT_TIME = 0;

        if(ULF_CTRL.ULF_TRANSMIT_ROUND > 0){
            ULF_CTRL.ULF_TRANSMIT_ROUND--;
        }else{
            CarrierCnt_Isr_Disable();
            ULF_Carrier_Stop();
            ULF_FiledDetect_Enable();
        }    
    }
   
    ULF_Carrier_ClearInterrupt(ret);

    return;
}

static unsigned char ULF_BO_BIT;
static unsigned int ULF_BO_BYTE;
static unsigned int ULF_Recv_Num;
static void ULF_MainCnt_Isr()
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

                ULF_MainCnt_Isr_Disable();
                ULF_Counter_Stop();
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
    
    if(ULF_Recv_Num >= ULF_T4100_PAGE_LEN){
        ULF_Recv_Num = 0;
        ULF_CTRL.ULF_RECEIVE_PAGE++;
    }
    /* Reset ULF_RECEIVE_CNT. */
    ULF_CTRL.ULF_RECEIVE_CNT = 0;

    return;
}

static unsigned char ULF_Baseband_GetPeriod(unsigned int Curr_data, \
                                                    unsigned int Post_data)
{
    unsigned int temp;
    if(Curr_data < Post_data){
        temp = (ULF_RECV_CAPTURE_PERIOD - Post_data) + Curr_data;
    }else{
        temp = Curr_data - Post_data;
    }
    if((ULF_RECV_LOW_TH0 < temp) && (temp < ULF_RECV_LOW_TH1)){
        return 1;
    }else 
    if((ULF_RECV_HIGH_TH0 < temp) && (temp < ULF_RECV_HIGH_TH1)){
        return 2;
    }
    return 0;
}

static void ULF_BasebandCnt_Isr()
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

    ULF_Capture_ClearInterrupt(ret);
    return;
Piolt_err:
    /* Reset all things. */
    ULF_Recv_Num = 0;
    memset(&ULF_Recv_Val, 0, sizeof(ULF_Recv_Val));
    memset(&ULF_CTRL, 0, sizeof(ULF_CTRL));
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
}

static void ULF_BasebandCnt_Isr_Enable(void)
{
    /* Configure CM4+ CPU interrupt vector for SysInt_ULFBasebandCnt_cfg Capture. */
    Cy_SysInt_Init(&SysInt_ULFBasebandCnt_cfg, ULF_BasebandCnt_Isr);
    NVIC_ClearPendingIRQ(SysInt_ULFBasebandCnt_cfg.intrSrc);
    NVIC_EnableIRQ((IRQn_Type)SysInt_ULFBasebandCnt_cfg.intrSrc);

    return;
}

static void ULF_BasebandCnt_Isr_Disable(void)
{
    NVIC_ClearPendingIRQ(SysInt_ULFBasebandCnt_cfg.intrSrc);
    NVIC_DisableIRQ((IRQn_Type)SysInt_ULFBasebandCnt_cfg.intrSrc);
}

static void ULF_MainCnt_Isr_Enable(void)
{ 
    /* Configure CM4+ CPU interrupt vector for SysInt_ULFMainCnt_cfg PWM Generator. */
    Cy_SysInt_Init(&SysInt_ULFMainCnt_cfg, ULF_MainCnt_Isr);
    NVIC_ClearPendingIRQ(SysInt_ULFMainCnt_cfg.intrSrc);
    NVIC_EnableIRQ((IRQn_Type)SysInt_ULFMainCnt_cfg.intrSrc);

    return;
}

static void ULF_MainCnt_Isr_Disable(void)
{
    NVIC_ClearPendingIRQ(SysInt_ULFMainCnt_cfg.intrSrc);
    NVIC_DisableIRQ((IRQn_Type)SysInt_ULFMainCnt_cfg.intrSrc);
}

/**
 * Ultra Low Frequency ULF_init.
 */
void ULF_Init()
{
    memset(&ULF_CTRL, 0, sizeof(ULF_CTRL));
    memset(&ULF_DB, 0, sizeof(ULF_DB));
    memset(&ULF_Recv_Val, 0, sizeof(ULF_Recv_Val));
    memset(&ULF_Trans_Val, 0, sizeof(ULF_Trans_Val));
   
    /* Disable ULF Field Detecting. */
    ULF_CTRL.ULF_DETECT_CARRIER = 1;
    Cy_GPIO_Set(ULF_BB_PORT, ULF_BB_NUM);

    return;
}

static void ULF_FiledDetect_Disable(void)
{
    /* Disable ULF Field Detecting. */
    ULF_CTRL.ULF_DETECT_CARRIER = 0;
    Cy_GPIO_Clr(ULF_BB_PORT, ULF_BB_NUM);

    /* Disable transmit counter & ISR. */
    ULF_MainCnt_Isr_Disable();
#if 1
    /* Clear TXen pin. */
    Cy_GPIO_Clr(ULF_TXen_PORT, ULF_TXen_NUM);
#endif
    /* Clear ULF_BO pin. */
    Cy_GPIO_Clr(ULF_BO_PORT, ULF_BO_NUM);
   
    /* Reset Trans Carrier time. */
    ULF_CTRL.ULF_TRANSMIT_TIME = 0;
}

static void ULF_FiledDetect_Enable(void)
{
    //CyDelayUs(1000);

    /* Enable ULF Field Detecting. */
    ULF_CTRL.ULF_DETECT_CARRIER = 1;
    Cy_GPIO_Set(ULF_BB_PORT, ULF_BB_NUM);
    
    ULF_CTRL.ULF_TRANSMIT_NOTE = 1;
#if 1
    /* Enable TXen pin. */
    Cy_GPIO_Set(ULF_TXen_PORT, ULF_TXen_NUM);
#endif

}

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

    return 0;
}

unsigned int ULF_Transmit(ulf_userdb_t *userdb, unsigned short round)
{
    int i;

    if(0 != ULF_CTRL.ULF_DETECT_CARRIER){
#if 0
        Cy_GPIO_Set(ULF_BB_PORT, ULF_BB_NUM);
        CyDelayUs(10);
        Cy_GPIO_Clr(ULF_BB_PORT, ULF_BB_NUM);
#endif
        if((1 == userdb->option) && (round > 0)){
#if 0
            /* Set TXen pin. */
            Cy_GPIO_Set(ULF_TXen_PORT, ULF_TXen_NUM);
#endif
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
        
                DEBUG_PRINTF("Info(%08X):Transmit ID =>> ", Sys_counter);
                for(i = 0; i < 10; i++){
                    DEBUG_PRINTF("%1X", userdb->pure_data[i]);
                }
                DEBUG_PRINTF("\n");
                
            }else{
                DEBUG_PRINTF("Error(%08X):No vailid card ID.\n", Sys_counter);
            }
        }
    }
    return 0;
}

/**
 * Transmit Carrier and prepare to detect card.
 */
unsigned int ULF_Receive(ulf_userdb_t *userdb, unsigned char round)
{
    /* Start Carrier. */
    if((1 == userdb->option) && (round > 0)){    /* T4100:1 ... */     
        /* Set try round. */
        ULF_CTRL.ULF_TRANSMIT_ROUND = round;
            
        /* Disable transmit counter & ISR. */
        ULF_MainCnt_Isr_Disable();
    
        ULF_FiledDetect_Disable();
               
        CarrierCnt_Isr_Enable();
       
        /* ULF Carrier engine start. */
        ULF_Carrier_Start();

        /* Capture for ULF baseband. */
        ULF_Capture_Start();

        ULF_BasebandCnt_Isr_Enable();

    }

    return 0;
}

unsigned int ULF_Encode()
{


    return 0;
}

/**
 * Ultra Low Frequency Decode module.
 * Fit for 4100 tag mode.
 */
unsigned int ULF_Decode_L1_T4100()
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
    
    CARD_SDATA[6] = (ULF_Recv_Val.ULF_RecvValue[0] & 0x03
);
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
#if 0
    DEBUG_PRINTF("Info(%08X):Card ID:\n", Sys_counter);
    for(i = 0; i < 10; i++){
        DEBUG_PRINTF("%1X",CARD_DATA[i]);
    }
    DEBUG_PRINTF("\n");
#endif
#if 0
    for(i = 0; i < 20; i++){
        CyDelayUs(i);
        Cy_GPIO_Set(ULF_BB_PORT, ULF_BB_NUM);
        CyDelayUs(i);
        Cy_GPIO_Clr(ULF_BB_PORT, ULF_BB_NUM);
    }
    for(i = 20; i > 1; i--){
        CyDelayUs(i);
        Cy_GPIO_Set(ULF_BB_PORT, ULF_BB_NUM);
        CyDelayUs(i);
        Cy_GPIO_Clr(ULF_BB_PORT, ULF_BB_NUM);
    }
#endif

    memcpy(userdb->raw_data, CARD_RAW_DATA, sizeof(CARD_RAW_DATA));
    memcpy(userdb->pure_data, CARD_DATA, sizeof(CARD_DATA));
    
    return 0;
}
#if 0
unsigned int ULF_Test()
{

    if(ULF_CTRL.ULF_TRANSMIT_START == 1){
        
        ULF_Counter_Start();
        
        ULF_Carrier_Start();
        
        ULF_CTRL.ULF_TRANSMIT_BUSY = CONT;
        ULF_CTRL.ULF_TRANSMIT_START = 0;
    }

    DEBUG_PRINTF("Info(%08x):ULF_Test done.\n", Sys_counter);

    return 0;
}
#endif

int ULF_Routine(ulf_userdb_t *userdb)
{
    int i;
    
    if(ULF_CTRL.ULF_RECEIVE_NOTE){
        ULF_CTRL.ULF_RECEIVE_NOTE = 0;
        
        /* Latch L1 data flow. */
        ULF_Decode_L1_T4100();
    
        /* Decode 4100 RAW data. */
        ULF_Decode_L2_T4100(userdb);
        
        DEBUG_PRINTF("Info(%08X):Receive ID =>> ", Sys_counter);
        for(i = 0; i < 10; i++){
            DEBUG_PRINTF("%1X",userdb->pure_data[i]);
        }
        DEBUG_PRINTF("\n");
#if 0
        memset(&ULF_Recv_Val,0,sizeof(ULF_Recv_Val));
        memset(&ULF_CTRL,0,sizeof(ULF_CTRL));
#endif
        ULF_CTRL.ULF_RECEIVE_STATE = WARMUP;

        ULF_CTRL.ULF_RECEIVE_PAGE = 0;
        ULF_CTRL.ULF_RECEIVE_CNT = 0;
        
        /* Enable ULF Field Detecting. */
        //ULF_CTRL.ULF_DETECT_CARRIER = 1;
        //Cy_GPIO_Set(ULF_BB_PORT, ULF_BB_NUM);
        
        memset(&ULF_Recv_Val,0,sizeof(ULF_Recv_Val));

        return 1;
    }

    if(ULF_CTRL.ULF_TRANSMIT_NOTE){
        ULF_CTRL.ULF_TRANSMIT_NOTE = 0;
        return 2;
    }

    return 0;
}

/* The end of file. */

