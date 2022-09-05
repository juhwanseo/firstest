/***************************************************************************//**
* @file     main.c
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
*/
/****************************************************************************/
//copy source
//******************************************************************************
// Include
//******************************************************************************

#include <main_conf.h>
#define Clear 0
#define Set 1
/* Private typedef ---------------------------------------------------------- */
/* Private define ----------------------------------------------------------- */
/* Private macro ------------------------------------------------------------ */
/* Private variables -------------------------------------------------------- */
/* Private define ----------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */

void SysTick_ExceptionHandler_IT( void );
void TIMER15_IRQHandler_IT( void );
void DEBUG_Init( void );
void DEBUG_MenuPrint( void );
void GPIO_Configure( void );
void TIMER15_Configure( void );
void TIMER1n_MatchInterruptRun( void );
void mainloop( void );
int main( void );
void Error_Handler( void );

//user function
void Delay(uint16_t Msec);
//user extern function
void LED_indi(void);
void Dis_value();
void FND_drive(uint16_t i);
void key_func();

/* Private variables -------------------------------------------------------- */
//******************************************************************************
// Variable
//******************************************************************************

const uint8_t menu[] =  "************************************************\n\r"
                        "TIMER1n_MatchInterrupt Example \n\r"
                        "  - MCU:        A31G123 \n\r"
                        "  - Core:       Cortex-M0+ \n\r"
                        "  - Monitoring: UART1 - 38400-8-N-1 \n\r"
                        "Target Peripheral: TIMER15 \n\r"
                        "Using Timer15 in interrupt mode \n\r"
                        "************************************************\n\r\n\r";

TIMER1n_PERIODICCFG_Type      TIMER1n_Config;
volatile uint32_t             count;
volatile uint32_t             flag;

//user variables
volatile uint32_t             cnt_10ms;
volatile uint32_t             cnt_100ms;
volatile uint32_t             sec = 0;
volatile uint32_t             TimCnt = 1234;
volatile uint32_t    					msec;

Bool switchmode = Clear;
Bool toggle = Clear;
Bool Ticktoggle = Clear;
Bool setTime_flag = Clear; 


//******************************************************************************
// Function
//******************************************************************************

/*-------------------------------------------------------------------------*//**
 * @brief         TIMER15_IRQHandler_IT
 * @param         None
 * @return        None
 *//*-------------------------------------------------------------------------*/
void TIMER15_IRQHandler_IT( void )
{
   uint32_t    status;

   status = T1nMaInt_GetFg( TIMER15 );
   if( status == 1 )
   {
      T1nMaInt_ClrFg( TIMER15 );
      count++;
		 
	 if(count == 10){ //10ms
		 cnt_10ms++;
		 if((cnt_10ms%5)==0) Ticktoggle = ~Ticktoggle; //setTime mode FND Flash Source
		 count = 0;
	 }
	 
	 if(cnt_10ms == 10){ //100ms
		 cnt_100ms++;
		 if((cnt_100ms%5)==0) toggle = ~toggle; //0.5s toggling source
//		 if(setTime_flag == FALSE) TimCnt++; //setTime_flag 
		 cnt_10ms = 0;
	 }	
  	if(cnt_100ms == 10){ //1s
		 sec++;
		 cnt_100ms = 0;
	 }
		
	 if(sec > 60){ //1min
		 sec = 0;
		 if(setTime_flag == FALSE) TimCnt++; //setTime_flag 
	 }
	
	 if(TimCnt >= 1440) // 1440min = 24h = 1d
		 TimCnt = 0;
   }
}
/*-------------------------------------------------------------------------*//**
 * @brief         SysTick_ExceptionHandler_IT
 * @param         None
 * @return        None
 *//*-------------------------------------------------------------------------*/
void SysTick_ExceptionHandler_IT( void )
{
   if( msec > 0 )
   {
      msec--;
   }
}

/*-------------------------------------------------------------------------*//**
 * @brief         DEBUG_Init
 * @param         None
 * @return        None
 *//*-------------------------------------------------------------------------*/
void DEBUG_Init( void )
{
#ifdef _DEBUG_MSG
   debug_frmwrk_init();
#endif
}

/*-------------------------------------------------------------------------*//**
 * @brief         DEBUG_MenuPrint
 * @param         None
 * @return        None
 *//*-------------------------------------------------------------------------*/
void DEBUG_MenuPrint( void )
{
#ifdef _DEBUG_MSG
   _DBG( menu );
#endif
}

/*-------------------------------------------------------------------------*//**
 * @brief         GPIO_Configure
 * @param         None
 * @return        None
 *//*-------------------------------------------------------------------------*/
void GPIO_Configure( void )
{
   // drive pin set
   HAL_GPIO_ConfigOutput( ( Pn_Type* )PD, 0, PUSH_PULL_OUTPUT );
   HAL_GPIO_ConfigPullup( ( Pn_Type* )PD, 0, PUPDx_Disable );
   HAL_GPIO_ClearPin( ( Pn_Type* )PD, _BIT( 0 ) );
	
	 HAL_GPIO_ConfigOutput( ( Pn_Type* )PD, 1, PUSH_PULL_OUTPUT );
   HAL_GPIO_ConfigPullup( ( Pn_Type* )PD, 1, PUPDx_Disable );
   HAL_GPIO_ClearPin( ( Pn_Type* )PD, _BIT( 1 ) );

	 HAL_GPIO_ConfigOutput( ( Pn_Type* )PD, 2, PUSH_PULL_OUTPUT );
   HAL_GPIO_ConfigPullup( ( Pn_Type* )PD, 2, PUPDx_Disable );
   HAL_GPIO_ClearPin( ( Pn_Type* )PD, _BIT( 2 ) );

	 HAL_GPIO_ConfigOutput( ( Pn_Type* )PD, 3, PUSH_PULL_OUTPUT );
   HAL_GPIO_ConfigPullup( ( Pn_Type* )PD, 3, PUPDx_Disable );
   HAL_GPIO_ClearPin( ( Pn_Type* )PD, _BIT( 3 ) );

   // data pin set
   HAL_GPIO_ConfigOutput( ( Pn_Type* )PC, 0, PUSH_PULL_OUTPUT );
   HAL_GPIO_ConfigPullup( ( Pn_Type* )PC, 0, PUPDx_Disable );
   HAL_GPIO_ClearPin( ( Pn_Type* )PC, _BIT( 0 ) );
	 
	 HAL_GPIO_ConfigOutput( ( Pn_Type* )PC, 1, PUSH_PULL_OUTPUT );
   HAL_GPIO_ConfigPullup( ( Pn_Type* )PC, 1, PUPDx_Disable );
   HAL_GPIO_ClearPin( ( Pn_Type* )PC, _BIT( 1 ) );
	 
	 HAL_GPIO_ConfigOutput( ( Pn_Type* )PC, 2, PUSH_PULL_OUTPUT );
   HAL_GPIO_ConfigPullup( ( Pn_Type* )PC, 2, PUPDx_Disable );
   HAL_GPIO_ClearPin( ( Pn_Type* )PC, _BIT( 2 ) );
	 
	 HAL_GPIO_ConfigOutput( ( Pn_Type* )PC, 3, PUSH_PULL_OUTPUT );
   HAL_GPIO_ConfigPullup( ( Pn_Type* )PC, 3, PUPDx_Disable );
   HAL_GPIO_ClearPin( ( Pn_Type* )PC, _BIT( 3 ) );
	 
	 HAL_GPIO_ConfigOutput( ( Pn_Type* )PC, 4, PUSH_PULL_OUTPUT );
   HAL_GPIO_ConfigPullup( ( Pn_Type* )PC, 4, PUPDx_Disable );
   HAL_GPIO_ClearPin( ( Pn_Type* )PC, _BIT( 4 ) );
	 
	 HAL_GPIO_ConfigOutput( ( Pn_Type* )PC, 5, PUSH_PULL_OUTPUT );
   HAL_GPIO_ConfigPullup( ( Pn_Type* )PC, 5, PUPDx_Disable );
   HAL_GPIO_ClearPin( ( Pn_Type* )PC, _BIT( 5 ) );
	 
	 HAL_GPIO_ConfigOutput( ( Pn_Type* )PC, 6, PUSH_PULL_OUTPUT );
   HAL_GPIO_ConfigPullup( ( Pn_Type* )PC, 6, PUPDx_Disable );
   HAL_GPIO_ClearPin( ( Pn_Type* )PC, _BIT( 6 ) );
	 
	 
	 //scan line 
	 HAL_GPIO_ConfigOutput( ( Pn_Type* )PA, 0, PUSH_PULL_OUTPUT );
   HAL_GPIO_ConfigPullup( ( Pn_Type* )PA, 0, PUPDx_Disable );
   HAL_GPIO_ClearPin( ( Pn_Type* )PA, _BIT( 0 ) );
	 
	 HAL_GPIO_ConfigOutput( ( Pn_Type* )PA, 1, PUSH_PULL_OUTPUT );
   HAL_GPIO_ConfigPullup( ( Pn_Type* )PA, 1, PUPDx_Disable );
   HAL_GPIO_ClearPin( ( Pn_Type* )PA, _BIT( 1 ) );
	 
	 HAL_GPIO_ConfigOutput( ( Pn_Type* )PA, 2, PUSH_PULL_OUTPUT );
   HAL_GPIO_ConfigPullup( ( Pn_Type* )PA, 2, PUPDx_Disable );
   HAL_GPIO_ClearPin( ( Pn_Type* )PA, _BIT( 2 ) );
	 
	 HAL_GPIO_ConfigOutput( ( Pn_Type* )PA, 3, PUSH_PULL_OUTPUT );
   HAL_GPIO_ConfigPullup( ( Pn_Type* )PA, 3, PUPDx_Disable );
   HAL_GPIO_ClearPin( ( Pn_Type* )PA, _BIT( 3 ) );
	 
	 //INDR line + debouncing set
	 HAL_GPIO_ConfigOutput( ( Pn_Type* )PF, 0, INPUT);
	 HAL_GPIO_ConfigPullup( ( Pn_Type* )PF, 0, PUPDx_EnablePU );
//	 HAL_GPIO_SetDebouncePin( ( Pn_Type* )PF, 0, DBCLK_HCLK1024);
	 
	 HAL_GPIO_ConfigOutput( ( Pn_Type* )PF, 1, INPUT);
	 HAL_GPIO_ConfigPullup( ( Pn_Type* )PF, 1, PUPDx_EnablePU );
//	 HAL_GPIO_SetDebouncePin( ( Pn_Type* )PF, 1, DBCLK_HCLK1024);
	 
	 HAL_GPIO_ConfigOutput( ( Pn_Type* )PF, 2, INPUT);
	 HAL_GPIO_ConfigPullup( ( Pn_Type* )PF, 2, PUPDx_EnablePU );
// HAL_GPIO_SetDebouncePin( ( Pn_Type* )PF, 2, DBCLK_HCLK1024);
	 
	 HAL_GPIO_ConfigOutput( ( Pn_Type* )PF, 3, INPUT);
	 HAL_GPIO_ConfigPullup( ( Pn_Type* )PF, 3, PUPDx_EnablePU );
//	 HAL_GPIO_SetDebouncePin( ( Pn_Type* )PF, 3, DBCLK_HCLK1024);
	 
	 
	 //using built in led set
	 {
		  // configure PE0 as a Output Mode
      HAL_GPIO_ConfigOutput( ( Pn_Type* )PE, 0, PUSH_PULL_OUTPUT );
      HAL_GPIO_ConfigPullup( ( Pn_Type* )PE, 0, PUPDx_EnablePU );			//LED 
      HAL_GPIO_ClearPin( ( Pn_Type* )PE, _BIT( 0 ) );								

      // configure PE1 as a Output Mode
      HAL_GPIO_ConfigOutput( ( Pn_Type* )PE, 1, PUSH_PULL_OUTPUT );
      HAL_GPIO_ConfigPullup( ( Pn_Type* )PE, 1, PUPDx_EnablePU );			//LED
      HAL_GPIO_ClearPin( ( Pn_Type* )PE, _BIT( 1 ) );

      // configure PE2 as a Output Mode
      HAL_GPIO_ConfigOutput( ( Pn_Type* )PE, 2, PUSH_PULL_OUTPUT );
      HAL_GPIO_ConfigPullup( ( Pn_Type* )PE, 2, PUPDx_Disable );
      HAL_GPIO_ClearPin( ( Pn_Type* )PE, _BIT( 2 ) );

      // configure PE3 as a Output Mode
      HAL_GPIO_ConfigOutput( ( Pn_Type* )PE, 3, PUSH_PULL_OUTPUT );
      HAL_GPIO_ConfigPullup( ( Pn_Type* )PE, 3, PUPDx_Disable );
      HAL_GPIO_ClearPin( ( Pn_Type* )PE, _BIT( 3 ) );
			
      // configure PE4 as a Output Mode
      HAL_GPIO_ConfigOutput( ( Pn_Type* )PE, 4, PUSH_PULL_OUTPUT );
      HAL_GPIO_ConfigPullup( ( Pn_Type* )PE, 4, PUPDx_Disable );
      HAL_GPIO_ClearPin( ( Pn_Type* )PE, _BIT( 4 ) );			
			
			// configure PE5 as a Output Mode
      HAL_GPIO_ConfigOutput( ( Pn_Type* )PE, 5, PUSH_PULL_OUTPUT );
      HAL_GPIO_ConfigPullup( ( Pn_Type* )PE, 5, PUPDx_Disable );
      HAL_GPIO_ClearPin( ( Pn_Type* )PE, _BIT( 5 ) );						//PE 2~5 Output port : KM 
			
						// configure PE5 as a Output Mode
      HAL_GPIO_ConfigOutput( ( Pn_Type* )PE, 6, PUSH_PULL_OUTPUT );
      HAL_GPIO_ConfigPullup( ( Pn_Type* )PE, 6, PUPDx_Disable );
      HAL_GPIO_ClearPin( ( Pn_Type* )PE, _BIT( 6 ) );						//PE 2~5 Output port : KM 
	 }
		 
}

/*-------------------------------------------------------------------------*//**
 * @brief         TIMER15_Configure
 * @param         None
 * @return        None
 *//*-------------------------------------------------------------------------*/
void TIMER15_Configure( void )
{
   count = 0;
   flag = 0;

   TIMER1n_Config.CkSel = TIMER1n_PCLK;               // PCLK = 40MHz
   TIMER1n_Config.Prescaler = 40;                     // fTIMER = PCLK / 40 = 1MHz
   TIMER1n_Config.ADR = ( 1000 );                     // Period  = ADR / fTIMER = 1000us
   TIMER1n_Config.StartLevel = TIMER1n_START_LOW;
   TIMER1n_Config.BDR = 0;                            // Duty(B) = BDR / fTIMER =    0us  // dummy parameter
   TIMER1n_Config.ECE = TIMER1n_FALLING_EGDE;         // dummy parameter

   HAL_TIMER1n_Init( ( TIMER1n_Type* )TIMER15, TIMER1n_PERIODIC_MODE, &TIMER1n_Config );
   HAL_TIMER1n_ConfigInterrupt( ( TIMER1n_Type* )TIMER15, TIMER1n_INTCFG_MIE, ENABLE );

   NVIC_SetPriority( TIMER15_IRQn, 3 );
   NVIC_EnableIRQ( TIMER15_IRQn );
   HAL_INT_EInt_MaskDisable( MSK_TIMER15 );

   HAL_TIMER1n_Cmd( ( TIMER1n_Type* )TIMER15, ENABLE );   // timer start & clear
}

/*-------------------------------------------------------------------------*//**
 * @brief         TIMER1n_MatchInterruptRun
 * @param         None
 * @return        None
 *//*-------------------------------------------------------------------------*/
void TIMER1n_MatchInterruptRun( void )
{
   /* Infinite loop */
   while( 1 )
   {
		 Dis_value();
		 
		 for(uint16_t i=0; i<4; i++){
			FND_drive(i);
			Delay(5); 
		 }

  	 LED_indi();
	//	 key_func(); //OLD
  //	 key_func2();	//NEW
   	 key_func();	//TEST
	 }//end of while
}// end of func

/*-------------------------------------------------------------------------*//**
 * @brief         LED_indi
 * @param         None
 * @return        None
 *//*-------------------------------------------------------------------------*/
void LED_indi(void)
{
	uint8_t indicator = 0;
			 
	if (TimCnt >= 720){ //led toggled //AM PM TimCnt >= 720 : PM
		indicator = 1; //PM 
		HAL_GPIO_SetPin( ( Pn_Type* )PE, _BIT( 0 ));
	}
	else{
		indicator = 0; //AM
		HAL_GPIO_SetPin( ( Pn_Type* )PE, _BIT( 1 ));
	}
		 
	if(toggle) //toggle indicator
		HAL_GPIO_SetPin( ( Pn_Type* )PE, _BIT( indicator ));
	else
		HAL_GPIO_ClearPin( ( Pn_Type* )PE, _BIT( indicator ));
}


/*-------------------------------------------------------------------------*//**
 * @brief         Delay loop
 * @param         get delay msec
 * @return        None
 *//*-------------------------------------------------------------------------*/
void Delay(uint16_t Msec)
{
		msec = Msec; 
    while( msec );
}

/*-------------------------------------------------------------------------*//**
 * @brief         Main loop
 * @param         None
 * @return        None
 *//*-------------------------------------------------------------------------*/
void mainloop( void )
{
   /* Configure menu prinf */
   DEBUG_MenuPrint();

   /* Configure port peripheral */
   GPIO_Configure();
	
	 // configure SysTick to 1ms interrupt
   SysTick_Config( SystemCoreClock / 1000 );

   /* TIMER15_Configure */
   TIMER15_Configure();

   /* Enable IRQ Interrupts */
   __enable_irq();

   /* TIMER1n_MatchInterruptRun */
   TIMER1n_MatchInterruptRun();
}

/*-------------------------------------------------------------------------*//**
 * @brief         Main program
 * @param         None
 * @return        None
 *//*-------------------------------------------------------------------------*/
int main( void )
{
   /* Initialize all port */
   Port_Init();

   /* Configure the system clock to HSI 40MHz */
   SystemClock_Config();

   /* Initialize Debug frame work through initializing USART port  */
   DEBUG_Init();

   /* Infinite loop */
   mainloop();

   return 0;
}

/*-------------------------------------------------------------------------*//**
 * @brief         Driver error handler
 * @param         None
 * @return        None
 *//*-------------------------------------------------------------------------*/
void Error_Handler( void )
{
   while( 1 )
   {
   }
}

#ifdef  USE_FULL_ASSERT
/*-------------------------------------------------------------------------*//**
 * @brief         Reports the name of the source file and the source line number
 *                where the assert_param error has occurred.
 * @param         file: pointer to the source file name
 * @param         line: assert_param error line source number
 * @return        None
 *//*-------------------------------------------------------------------------*/
void check_failed( uint8_t* file, uint32_t line )
{
   /* User can add his own implementation to report the file name and line number,
      ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

   /* Infinite loop */
   while( 1 )
   {
   }
}
#endif

