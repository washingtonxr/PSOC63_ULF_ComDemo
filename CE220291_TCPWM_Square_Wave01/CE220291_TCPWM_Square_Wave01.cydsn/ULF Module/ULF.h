/**
 * @File    ULF.h
 * @Date    Friday, Mar. 1st 2019 at 09:41:12 PM BJT
 * @Author  Washington Ruan
 * @Email   washingtonxr@live.com
 *
 * This file contains the implementation of the gravity sensor device for motion detecting
 * module.
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
 * @bug No known bugs.
 **/
/**
 * Function: Ultra Low Frequency module. 
 * Author: Xi Ruan
 * Date: Mar.1st,2019
 * E-mail: washingtonxr@live.com
 **/
#ifndef _ULF_H
#define _ULF_H

#include "main_cm4.h"

#define ULF_Debug                   0
#define ULF_USER_PIOLT_LEN          9                           /* Piolt carrier length.   */
#define ULF_USER_ID_SIZE            1                           /* Size of user ID zone.   */
#define ULF_USER_DATA_SIZE          4                           /* Size of user data zone. */
#define ULF_USER_TRANS_TIMEOUT      3                           /* Million-second.         */

#define ULF_MANCHISTER_P1           32
#define ULF_MANCHISTER_P2           (ULF_MANCHISTER_P1*2)

#define ULF_TRANS_GAP               3

#define ULF_RECV_BUF_DEPTH          4
#define ULF_RECV_D_OFFSET           (32 + 16)
#define ULF_RECV_LOW_TH0            (256 - ULF_MANCHISTER_P2)
#define ULF_RECV_LOW_TH1            (256 + ULF_MANCHISTER_P2)
#define ULF_RECV_HIGH_TH0           (512 - ULF_MANCHISTER_P2)
#define ULF_RECV_HIGH_TH1           (512 + ULF_MANCHISTER_P2)
#define ULF_RECV_PIOLT_CIR0         1
#define ULF_RECV_PIOLT_CIR1         16
#define ULF_RECV_PIOLT_CIR2         1
#define ULF_RECV_LATCH_PT           (ULF_MANCHISTER_P2 - 16)

#define ULF_T4100_PILT_LEN          9
#define ULF_T4100_PPDU_LEN          ULF_MANCHISTER_P2
#define ULF_T4100_PAGE_LEN          (ULF_T4100_PPDU_LEN/2)
#define ULF_T4100_MPDU_LEN          (ULF_T4100_PPDU_LEN - ULF_T4100_PILT_LEN)
#define ULF_T4100_PPDU_TXSIZE       (ULF_MANCHISTER_P2*ULF_T4100_PPDU_LEN)
#define ULF_RECV_CAPTURE_PERIOD     0xFFFF

/* L1 link modulation type. */
typedef enum{
    ULF_ASK = 1,
    ULF_FSK,
    ULF_PSK
}ulf_link_t;

/* ULF Protocol type. */
typedef enum{
    ULF_PRO_4100 = 1,
    ULF_PRO_4200,
    ULF_PRO_55xx
}ulf_pro_t;
    
/* ULF Transmit State. */
typedef enum{
    WARMUP = 0,
    PIOLT,
    USERID,
    USERDATA,
    THEEND,
    /* Transmit sign. */
    IDLE,
    BUSY,
    CONT,
    SYNC,
    TIMEOUT,
    CARRIER_TO,
    BASEBAND_TO,
    GETCARD_INFO
}ulf_txstate_t;

/* Database for ULF. */
typedef struct{
    /* For type EM4100, EM4200. */
    unsigned char ULF_PRO_TYPE;                                 /* Protocol Type.        */
    unsigned char ULF_USER_PIOLT[ULF_USER_PIOLT_LEN];           /* Piolt carrier length. */
    unsigned char ULF_USER_ID[ULF_USER_ID_SIZE];                /* USER ID zone.         */
    unsigned char ULF_USER_DATA[ULF_USER_DATA_SIZE];            /* USER DATA zone.       */
    //unsigned char ULF_USER_CHECKSUM[ULF_USER_CHECKSUM_LEN];   /* Checksum zone.        */
}ulf_user_db_t; 

typedef struct{
    unsigned char ULF_RecvVal_CNT;
    unsigned int ULF_RecvTick;
    unsigned int ULF_RecvValue[ULF_RECV_BUF_DEPTH];
    unsigned char ULF_RecvLock;
    unsigned char ULF_RecvPiolt_Num;
    unsigned int ULF_RecvCurr_Data;
    unsigned int ULF_RecvPost_Data;
    unsigned short ULF_RecvBitNum;
    unsigned short ULF_RecvPeri_Num;
    unsigned char ULF_RecvPost_Phase;
    unsigned char ULF_Recv_PeriodBuf[256];
    unsigned short ULF_Recv_PeriHNum;
}ulf_recv_value_t;

typedef struct{
    unsigned char ULF_TransVal_CNT;
    unsigned int ULF_TransTick;
    unsigned int ULF_TransValue[ULF_RECV_BUF_DEPTH];
    unsigned int ULF_TransBitNum;
    unsigned char ULF_TransLock;
}ulf_trans_value_t;

/* User control part. */
typedef struct{
    /* Transmiter Parameter. */
    unsigned char ULF_TRANSMIT_START;                           /* Transmit start sign.  */
    unsigned char ULF_TRANSMIT_BUSY;                            /* Transmit busy.        */
    unsigned int ULF_TRANSMIT_TIME;                             /* Transmit times.       */
    unsigned short ULF_TRANSMIT_ROUND;
    unsigned short ULF_TRANSMIT_CNT;                            /* Transmit Counter.     */
    unsigned char ULF_TRANSMIT_CMD;                             /* Transmit Command.     */
    unsigned char ULF_TRANSMIT_STATE;                           /* Transmit State.       */
    unsigned char ULF_TRANSMIT_BIT;                             /* Transmit Current bit. */
    unsigned short ULF_TRANSMIT_DLEN;                           /* Transmit Data Length. */
    unsigned char ULF_TRANSMIT_NOTE;
    /* Receiver Parameter. */
    unsigned char ULF_RECEIVE_START;                            /* Receive start sign.   */
    unsigned char ULF_RECEIVE_BITEN;
    unsigned short ULF_RECEIVE_CNT;                             /* Receive Counter.      */
    unsigned char ULF_RECEIVE_NOTE;                             /* Receive Notice.       */
    unsigned char ULF_RECEIVE_PAGE;                             /* Baseband data page.   */
    unsigned char ULF_RECEIVE_STATE;                            /* Receive State.        */
    /* Baseband Transmit Parameter. */
    unsigned short ULF_BBTRANS_ROUND;
    unsigned char ULF_DETECT_CARRIER;
    unsigned char ULF_BBTRANS_NOTE;
    /* Runtine Parameter. */
    //unsigned char ULF_ROUTINE_STATE;
}ulf_ctrl_t;

typedef struct{
    unsigned char option;       /* Default value:1. */
    unsigned int raw_data[2];   /* Default depth:2. */
    unsigned char pure_data[10];   
    unsigned char priority;     /* Default value:0. */
}ulf_userdb_t;

#define ULF_TRANS_STATE0            WARMUP
#define ULF_TRANS_STATE1            PIOLT
#define ULF_TRANS_STATE2            USERID
#define ULF_TRANS_STATE3            USERDATA
#define ULF_TRANS_STATE4            THEEND

void ULF_Init(void);
unsigned int ULF_Test(void);
int ULF_Routine(ulf_userdb_t *userdb);
unsigned int ULF_Receive(ulf_userdb_t *userdb, unsigned char round);
unsigned int ULF_Transmit(ulf_userdb_t *userdb, unsigned short round);
unsigned int ULF_Transmit_Exit(void);

extern unsigned int Sys_counter;

#endif
/* The end of file. */

