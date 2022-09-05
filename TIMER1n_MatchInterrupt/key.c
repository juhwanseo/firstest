#include <main_conf.h>
#include <string.h> 

#define debCnt  4
#define Clear 0
#define Set 1

uint16_t old[4] = {0x000F, 0x000F, 0x000F, 0x000F}; // old init
uint16_t cnt[4] = {0, 0, 0, 0}; //cnt init
uint16_t Lcnt[4] = {0, 0, 0, 0}; //cnt init
uint8_t curser = 0;
Bool longkeyflag[4] = {0, 0, 0, 0};

//Key value
Bool key_SetTime = 0;
Bool key_Go = 0;
Bool key_Reset = 0;
Bool key_Curser = 0;
Bool key_Up = 0;
Bool key_Down = 0;
Bool key_Switch = 0;

struct key_flag1 { //rising edge
	Bool SetTime;
	Bool Go;
	Bool Reset;
}; 
struct	key_flag1 key1 = {0,};

struct key_flag2 { //rising edge
	Bool Curser;
	Bool Up;	
	Bool Down;
}; 
struct	key_flag2 key2 = {0,};

struct key_flag3 { //rising edge
	Bool Switch;	
}; 
struct	key_flag3 key3 = {0,};

Bool repeat_flag = 0;
uint16_t rCnt =0;
uint16_t value;

struct detect { //rising edge
	Bool cur;
	Bool swit;
	Bool up;
	Bool down;
}detct; 

//user extern variables
extern uint32_t TimCnt;
extern Bool switchmode;
extern Bool setTime_flag;

//******************************************************************************
// Function
//******************************************************************************

void key_make (void)
{
	switch(old[0]) {
		case 0xE : key1.SetTime = Set; break;
		case 0xD : key1.Go = Set; break;
		case 0xB : key1.Reset = Set; break;
		case 0x7 : break;
		default :  memset(&key1, 0, sizeof(struct key_flag1)); break;
	}
	
	switch(old[1]) {
		case 0xE : key2.Curser = Set; break;
		case 0xD : key2.Up = Set; break;
		case 0xB : key2.Down = Set; break;
		case 0x7 : break;
		default : memset(&key2, 0, sizeof(struct key_flag2)); break;
	}

	switch(old[3]) {
		case 0xE : key3.Switch = Set; break;
		case 0xD : break;
		case 0xB : break;
		case 0x7 : break;
		default : memset(&key3, 0, sizeof(struct key_flag3)); break;
	}
}

void scan()
{
	for(uint16_t i=0; i<4; i++){
	//	HAL_GPIO_WritePin( ( Pn_Type* )PA, arr[i] ); //scan sequence
		PA->OUTDR = (0xF^(1<<i)); //scan sequence
//		if(old[i] != (HAL_GPIO_ReadPin(( Pn_Type* )PF )&0x000F)) { //chatt code
		if(old[i] != ((PF->INDR)&0xF)) { //chatt code
			cnt[i]++;
			if(cnt[i] > debCnt){
//				old[i] = (HAL_GPIO_ReadPin(( Pn_Type* )PF )&0x000F); //key value
				old[i] = ((PF->INDR)&0xF); //key value
				cnt[i] = Clear;
				longkeyflag[i] = Set; //long key flag set when recorded old
			}
		}
		else {
			cnt[i] = Clear;
		}
	}
	key_make();
	if(repeat_flag) rCnt++;
	else rCnt = 0;
}

void key_func( void )
{ 
	//Set Time mode = Long key
	if(key1.SetTime){
		repeat_flag = 1;
		if(rCnt > 600) setTime_flag = TRUE;
	}
	//Set Time = Short key
	else if(key1.Go){
		setTime_flag = FALSE;
		curser = 0;
	}
	//Reset Timer = Short key
	else if(key1.Reset){
		TimCnt = 1234;
	}
	//Set Time Curser = rising Short key
	else if(key2.Curser){ 
		detct.cur = key2.Curser;
	}
	else if(detct.cur != key2.Curser)// key rising detect
	{
		curser++;
		if(curser >= 4) curser = 0;
			switch(curser){
				case 0:  value = 1; break;
				case 1:  value = 10; break;
				case 2:  value = 60; break;
				case 3:  value = 600; break;
				default : break;
		}
			detct.cur=0;
	}
	//Timer Up = rising Short key/Long key
	else if(key2.Up){
    detct.up = key2.Up;
		
		repeat_flag = 1;
		if(rCnt > 100) {
			TimCnt += value;
		}
	}
	else if(detct.up != key2.Up){
		TimCnt += value;
		detct.up = 0;
	}	
	//Timer Down = rising Short key/Long key
	else if(key2.Down){
    detct.down = key2.Down;
		
		repeat_flag = 1;
		if(rCnt > 100) {
			TimCnt -= value;
		}
	}
	else if(detct.down != key2.Down){
		TimCnt -= value;
		detct.down = 0;
	}	
	
	//Switch display = rising Short key
	else if(key3.Switch){
    detct.swit = key3.Switch;
	}
	else if(detct.swit != key3.Switch){
		switchmode = ~switchmode;
		detct.swit = 0;
	}
	
	else{ //Off Key
		repeat_flag = 0;
		rCnt = 0;
	}

}

