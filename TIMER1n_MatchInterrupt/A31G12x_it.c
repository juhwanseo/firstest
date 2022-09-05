/***************************************************************************//**
* @file     A31G12x_it.c
* @brief    Contains all functions support for Exception & Interrupt Handler on A31G12x
*
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

#include "main_conf.h"

/* Private typedef ---------------------------------------------------------- */
/* Private define ----------------------------------------------------------- */
/* Private macro ------------------------------------------------------------ */
/* Private define ----------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
/* Private variables -------------------------------------------------------- */


/******************************************************************************/
/*            Cortex M0+ Processor Exceptions Handlers                        */
/******************************************************************************/

/*-------------------------------------------------------------------------*//**
 * @brief         This function handles NMI exception.
 * @param         None
 * @return        None
 *//*-------------------------------------------------------------------------*/
void NMI_Handler( void )
{
}

/*-------------------------------------------------------------------------*//**
 * @brief         This function handles Hard Fault exception.
 * @param         None
 * @return        None
 *//*-------------------------------------------------------------------------*/
void HardFault_Handler( void )
{
   /* Go to infinite loop when Hard Fault exception occurs */
   while( 1 )
   {
   }
}

/*-------------------------------------------------------------------------*//**
 * @brief         This function handles SVCall exception
 * @param         None
 * @return        None
 *//*-------------------------------------------------------------------------*/
void SVC_Handler( void )
{
}

/*-------------------------------------------------------------------------*//**
 * @brief         This function handles PendSVC exception
 * @param         None
 * @return        None
 *//*-------------------------------------------------------------------------*/
void PendSV_Handler( void )
{
}

/*-------------------------------------------------------------------------*//**
 * @brief         This function handles SysTick Handler.
 * @param         None
 * @return        None
 *//*-------------------------------------------------------------------------*/
void SysTick_Handler( void )
{
	 SysTick_ExceptionHandler_IT();
}

/******************************************************************************/
/*                 A31G12x Peripherals Interrupt Handlers                     */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_A31G12x.s).                                                 */
/******************************************************************************/

/*-------------------------------------------------------------------------*//**
 * @brief         This function handles TIMER15 Handler.
 * @param         None
 * @return        None
 *//*-------------------------------------------------------------------------*/
void TIMER15_Handler( void )
{
   TIMER15_IRQHandler_IT();
}

