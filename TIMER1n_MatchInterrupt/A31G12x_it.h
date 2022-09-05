/***************************************************************************//**
* @file     A31G12x_it.h
* @brief    Contains all macro definitions and function prototypes
*           support for Exception & Interrupt Handler on A31G12x
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

/* Define to prevent recursive inclusion ------------------------------------ */
#ifndef __A31G12x_IT_H
#define __A31G12x_IT_H

/* Includes ----------------------------------------------------------------- */

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ----------------------------------------------------------- */
/* Exported constants ------------------------------------------------------- */
/* Exported macro ----------------------------------------------------------- */


/* Exported functions ------------------------------------------------------- */

void NMI_Handler( void );
void HardFault_Handler( void );
void MemManage_Handler( void );
void BusFault_Handler( void );
void UsageFault_Handler( void );
void SVC_Handler( void );
void DebugMon_Handler( void );
void PendSV_Handler( void );
void SysTick_Handler( void );

void TIMER15_Handler( void );

#ifdef __cplusplus
}
#endif

#endif   /* __A31G12x_IT_H */

