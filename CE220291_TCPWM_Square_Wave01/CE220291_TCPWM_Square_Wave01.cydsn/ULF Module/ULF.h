/**
 * @File    ULF.h
 * @Date    Friday, Mar. 1st 2019 at 09:41:12 PM BJT
 * @Author  Washington Ruan
 * @Email   ruanx@landicorp.com or washingtonxr@live.com
 *
 * This file contains the implementation of the gravity sensor device for motion detecting
 * module.
 *
 * @bug No known bugs.
 **/
#ifndef _ULF_H
#define _ULF_H

#define ULF_USER_PIOLT_LEN      9                               /* Piolt carrier length.   */
#define ULF_USER_ID_SIZE        1                               /* Size of user ID zone.   */
#define ULF_USER_DATA_SIZE      4                               /* Size of user data zone. */
#define ULF_USER_TRANS_TIMEOUT  3                               /* Million-second.         */

#define ULF_MANCHISTER_P1       32
#define ULF_MANCHISTER_P2       64

#define ULF_TRANS_GAP           3

#define ULF_RECV_BUF_DEPTH      8
#define ULF_RECV_D_OFFSET       (32 + 16)
#define ULF_RECV_LOW_TH0        (256 - 64)
#define ULF_RECV_LOW_TH1        (256 + 64)
#define ULF_RECV_HIGH_TH0       (512 - 64)
#define ULF_RECV_HIGH_TH1       (512 + 64)
#define ULF_RECV_PIOLT_CIR0     1
#define ULF_RECV_PIOLT_CIR1     16
#define ULF_RECV_PIOLT_CIR2     1
#define ULF_RECV_LATCH_PT       (64 - 16)

//#define ULF_USER_CHECKSUM_LEN   1

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
    CONT
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
    unsigned int ULF_RecvBitNum;
    unsigned char ULF_RecvLock;
    unsigned char ULF_RecvPiolt_Num;
    unsigned int ULF_RecvCurr_Data;
    unsigned int ULF_RecvPost_Data;
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
    unsigned int ULF_TRANSMIT_TIME;                             /* Transmit time.        */
    unsigned int ULF_TRANSMIT_CNT;                              /* Transmit Counter.     */
    unsigned char ULF_TRANSMIT_CMD;                             /* Transmit Command.     */
    unsigned char ULF_TRANSMIT_STATE;                           /* Transmit State.       */
    unsigned char ULF_TRANSMIT_BIT;                             /* Transmit Current bit. */
    unsigned int ULF_TRANSMIT_DLEN;                             /* Transmit Data Length. */
    /* Receiver Parameter. */
    unsigned char ULF_RECEIVE_START;                            /* Receive start sign.   */
    unsigned int ULF_RECEIVE_CNT;                               /* Receive Counter.      */
    unsigned char ULF_RECEIVE_NOTE;                             /* Receive Notice.       */
    unsigned char ULF_RECEIVE_PAGE;                             /* Baseband data page.   */
    unsigned char ULF_RECEIVE_STATE;                            /* Receive State.        */
}ulf_ctrl_t;

#define ULF_TRANS_STATE0        WARMUP
#define ULF_TRANS_STATE1        PIOLT
#define ULF_TRANS_STATE2        USERID
#define ULF_TRANS_STATE3        USERDATA
#define ULF_TRANS_STATE4        THEEND

void ULF_Init();
void ULF_Init2();

unsigned int ULF_Test();
int ULF_Routine();

extern ulf_ctrl_t ULF_CTRL;                                     /* ULF Transmit Control. */
extern ulf_user_db_t ULF_DB;                                    /* ULF Control Database. */
extern unsigned int Sys_counter;
#endif
 
