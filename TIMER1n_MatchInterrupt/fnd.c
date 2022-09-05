#include <main_conf.h>

#define PinClear 0b00001111
#define OFFLAMP 0b11111111

 
uint16_t m_1 = 0;
uint16_t m_10 = 0;
uint16_t h_1 = 0;
uint16_t h_10 = 0;

uint16_t table[10] = // table[0] = fnd data '0'
{   0b11000000, //0
    0b11111001, //1
    0b10100100, //2
    0b10110000, //3
    0b10011001, //4
    0b10010010, //5
    0b10000010, //6
    0b11111000, //7
    0b10000000, //8
    0b10010000  //9
};

//user extern variables
extern uint32_t TimCnt;
extern uint8_t curser;
extern Bool switchmode;
extern Bool Ticktoggle;
extern Bool setTime_flag;

//user extern function
void scan( void );

//******************************************************************************
// Function
//******************************************************************************
void Dis_value(void)
{
		 //make watch value
		 uint16_t hour = TimCnt/60; 	// scope : 0~23
     uint16_t min = TimCnt%60;	// scope : 0~59
	   uint16_t h = 0;
		 if(switchmode){
				if( (hour==12)||(hour==0) ) h = 12;
				else	h = hour%12;
			 
				h_1 = h%10;
				h_10 = h/10;
		 }
		 else{
			  h_1 = hour % 10;
				h_10 = hour / 10;
		 }
		 m_1 = min % 10;
		 m_10 = min / 10;
}


uint16_t FND_driveOutput(uint16_t i)
{
	switch(i){
		case 0 : return table[m_1]; break; //data pin input m_1 data
		case 1 : return table[m_10]; break; //data pin input m_10 data
		case 2 : return table[h_1]; break; //data pin input h_1 data
		case 3 : return table[h_10]; break; //data pin input h_10 data
		default : return 0; break;
	}
}


void FND_data(uint16_t i)
{
	uint16_t data = FND_driveOutput(i); //fnd data
	if((setTime_flag == TRUE)&&(curser == i)){ //watch stopped & curser here
		if(Ticktoggle)//setTime mode -> flash FND 
			PC->OUTDR = data;
		else
			PC->OUTDR = OFFLAMP;
	}
	else 
		PC->OUTDR = data;
}


void FND_drive(uint16_t i)
{
	PD->OUTDR = PinClear;
	scan(); //isolating
	FND_data(i);
	PD->OUTDR = (0xF^(1<<i));
}

