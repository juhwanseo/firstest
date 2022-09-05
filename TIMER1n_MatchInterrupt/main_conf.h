/***************************************************************************//**
* @file     main_conf.h
* @brief    Contains all macro definitions and function prototypes
*           support for Example Code on A31G12x
*
*
* @version  1.00
* @date     2020-05-29
* @author   ABOV Application Team
*
* Copyright(C) 2019, ABOV Semiconductor
* All rights reserved.
*
*//****************************************************************************/

#ifndef __A31G12x_CONF_H
#define __A31G12x_CONF_H

/* Includes ----------------------------------------------------------------- */
/* Uncomment the line below to enable peripheral header file inclusion */

#include "A31G12x.h"
#include "A31G12x_hal_aa_types.h"
#include "A31G12x_hal_debug_frmwrk.h"
#include "A31G12x_hal_libcfg.h"
#include "A31G12x_hal_wtidky.h"

#include "A31G12x_hal_adc.h"
#include "A31G12x_hal_crc.h"
#include "A31G12x_hal_fmc.h"
#include "A31G12x_hal_i2cn.h"
#include "A31G12x_hal_intc.h"
#include "A31G12x_hal_lcd.h"
#include "A31G12x_hal_pcu.h"
#include "A31G12x_hal_pwr.h"
#include "A31G12x_hal_scu.h"
#include "A31G12x_hal_sculv.h"
#include "A31G12x_hal_timer1n.h"
#include "A31G12x_hal_timer2n.h"
#include "A31G12x_hal_timer3n.h"
#include "A31G12x_hal_uartn.h"
#include "A31G12x_hal_usart1n.h"
#include "A31G12x_hal_wdt.h"
#include "A31G12x_hal_wt.h"

#include "A31G12x_it.h"
/*Private include-----------------------------------------------------------*/



#ifdef __cplusplus
extern "C"
{
#endif

/* Private typedef ---------------------------------------------------------- */
/* Private define ----------------------------------------------------------- */
/* Private macro ------------------------------------------------------------ */
/* Private variables -------------------------------------------------------- */
/* Private define ----------------------------------------------------------- */


/* Private function prototypes ---------------------------------------------- */

/* Initialize all port */
void Port_Init( void );

/* Configure the system clock to 40MHz */
void SystemClock_Config( void );

/* TIMER15_IRQHandler_IT */
void TIMER15_IRQHandler_IT( void );

/* SysTick_ExceptionHandler_IT */
void SysTick_ExceptionHandler_IT( void );

#ifdef __cplusplus
}
#endif

#endif   /* __A31G12x_CONF_H */

