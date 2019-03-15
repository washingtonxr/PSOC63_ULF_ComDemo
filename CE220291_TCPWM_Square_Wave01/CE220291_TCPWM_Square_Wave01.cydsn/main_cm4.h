/**
 * @File    main_cm4.h
 * @Date    Friday, Mar. 4th 2019 at 10:30:52 AM BJT
 * @Author  Washington Ruan
 * @Email   ruanx@landicorp.com or washingtonxr@live.com
 *
 * This file contains the implementation of the gravity sensor device for motion detecting
 * module.
 *
 * @bug No known bugs.
 **/
#ifndef MAIN_CM4_H
#define MAIN_CM4_H

#define LED_TO              3       /* LTE Timeout counter. */
#define SYS_HEARTBEAT_TO    100     /* Beat in 1 second.    */

typedef struct{
    unsigned char sw;
    unsigned char counter;
}sys_LEDtimer_t;

#endif

/* [] END OF FILE */
