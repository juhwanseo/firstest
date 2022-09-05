/***************************************************************************//**
* @file     A31G12x_SystemClock.c
* @brief    Contains all functions support for Example Code on A31G12x
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
/*******************************************************************************
 *                          A31G12x Device
 *------------------------------------------------------------------------
 *    System Clock source       | High Speend Internal oscillator
 *------------------------------------------------------------------------
 *    SYSCLK(MHz)               | 40MHz
 *------------------------------------------------------------------------
 *    HCLK(MHz) - Core Clock    | 40MHz
 *------------------------------------------------------------------------
 *    PCLK(MHz) - Peri Clock    | 40MHz
 *------------------------------------------------------------------------
 ******************************************************************************/

#include "main_conf.h"

/* Private typedef ---------------------------------------------------------- */
/* Private define ----------------------------------------------------------- */
/* Private macro ------------------------------------------------------------ */
/* Private variables -------------------------------------------------------- */


/* Private define ----------------------------------------------------------- */

// Main Clock Selection: Select only one of the following.
#define USED_HIRC       /*  HIRC  :  40000000uL */
//#define USED_WDTRC      /*  WDTRC :  40000uL */
//#define USED_XMOSC      /*  XMOSC :  16000000uL */
//#define USED_XSOSC      /*  XSOSC :  32768uL */

/* Clock Out Selection ( Monitoring ) */
/*#define USED_CLKO*/


/* Private function prototypes ---------------------------------------------- */

void SystemClock_Config( void );


/* Private variables -------------------------------------------------------- */


/*-------------------------------------------------------------------------*//**
 * @brief         Initialize default clock for A31G12x Board
 * @param         None
 * @return        None
 *//*-------------------------------------------------------------------------*/
void SystemClock_Config( void )
{
   uint32_t    i;

   // enable clock source
   HAL_SCU_ClockSource_Enable( CLKSRCR_HIRCEN | CLKSRCR_XMOSCEN | CLKSRCR_XSOSCEN | CLKSRCR_WDTRCEN, HIRCSEL_HIRC1 );
   for( i = 0; i < 1000; i++ );  // Clock Stable Time

   // select system clock
#ifdef USED_WDTRC
   HAL_SCU_SystemClockDivider( WLDIV_MCLK64 | HDIV_MCLK1, SYSTDIV_HCLK1 | PDIV_HCLK1 );  // WT/LCD | HCLK, SysTick | PCLK
   HAL_SCU_SystemClockChange( MCLKSEL_WDTRC );

   SystemCoreClock = 40000uL;    // HCLK
   SystemPeriClock = 40000uL;    // PCLK
#endif

#ifdef USED_XSOSC
   HAL_SCU_SystemClockDivider( WLDIV_MCLK64 | HDIV_MCLK1, SYSTDIV_HCLK1 | PDIV_HCLK1 );  // WT/LCD | HCLK, SysTick | PCLK
   HAL_SCU_SystemClockChange( MCLKSEL_XSOSC );

   SystemCoreClock = 32768uL;    // HCLK
   SystemPeriClock = 32768uL;    // PCLK
#endif

#ifdef USED_XMOSC
   HAL_SCU_SystemClockChange( MCLKSEL_XMOSC );
   HAL_SCU_SystemClockDivider( WLDIV_MCLK64 | HDIV_MCLK1, SYSTDIV_HCLK1 | PDIV_HCLK1 );  // WT/LCD | HCLK, SysTick | PCLK

   SystemCoreClock = 16000000uL;    // HCLK
   SystemPeriClock = 16000000uL;    // PCLK
#endif

#ifdef USED_HIRC
   HAL_SCU_SystemClockChange( MCLKSEL_HIRC );
   HAL_SCU_SystemClockDivider( WLDIV_MCLK64 | HDIV_MCLK1, SYSTDIV_HCLK1 | PDIV_HCLK1 );  // WT/LCD | HCLK, SysTick | PCLK

   SystemCoreClock = 40000000uL;    // HCLK
   SystemPeriClock = 40000000uL;    // PCLK
#endif

   // disable unused clock source
   //HAL_SCU_ClockSource_Disable( CLKSRCR_XMOSCEN | CLKSRCR_XSOSCEN );

   // enable clock monitoring
   HAL_SCU_ClockMonitoring( MACTS_SysClkChg, MONCS_MCLK );

   // enable clock output
#ifdef USED_CLKO
   HAL_SCU_CLKO_PinConfig();
   HAL_SCU_ClockOutput( CLKOS_MCLK, POLSEL_Low, CLKODIV_SelectedClock1 );
#endif
}

