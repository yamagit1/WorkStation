#include"LCD5110.h"

void LCDDelay(volatile __uint32 time){
	while(time!=0){
		time--;
	}
}
void InitPIN(GPIO_InitTypeDef *x,uint32_t PIN){
	(*x).GPIO_Pin		=PIN;
	(*x).GPIO_Mode		=GPIO_Mode_OUT;
	(*x).GPIO_OType		=GPIO_OType_PP;
	(*x).GPIO_PuPd		=GPIO_PuPd_NOPULL;
	(*x).GPIO_Speed		=GPIO_Speed_100MHz;
	GPIO_Init(LCD_COM,x);
}


void LCDSetPin(void){

	GPIO_InitTypeDef		LCDPin;
	RCC_AHB1PeriphClockCmd(LCD_RCC_D, ENABLE);

	InitPIN(&LCDPin,LCD_RST);
	InitPIN(&LCDPin,LCD_CE);
	InitPIN(&LCDPin,LCD_DC);
	InitPIN(&LCDPin,LCD_DIN);
	InitPIN(&LCDPin,LCD_CLK);
	InitPIN(&LCDPin,LCD_VCC);
	InitPIN(&LCDPin,LCD_LIG);
	InitPIN(&LCDPin,LCD_GND);

	GPIO_SetBits(LCD_COM,LCD_VCC);		//dien ap logic +5v cho LCD
	GPIO_ResetBits(LCD_COM,LCD_GND);	//pin mass
	GPIO_ResetBits(LCD_COM,LCD_LIG);	// bat den nen
//	GPIO_SetBits(LCD_COM,LCD_LIG);		//tat den nen
}

void LCDSendData(__uint8 data){
	__int32 i;

	LOW(LCD_CLK);
	HIGHT(LCD_DIN);
	for(i=8; i>0; i--){
		if((data & 0x80) == 0x80){	//write bit pin sdin
			HIGHT(LCD_DIN);
		}
		else{
			LOW(LCD_DIN);
		}
		HIGHT(LCD_CLK);				//clock hight end send
		data = data << 1;
		LOW(LCD_CLK);				//clock low,start send
	}
}

void LCDWrite(__int32 ew,__uint8 data){
	if(ew==EW_DATA){
		HIGHT(LCD_DC);
	}
	else{
		LOW(LCD_DC);
	}

	LOW(LCD_CE);
	LCDSendData(data);
	HIGHT(LCD_CE);
}

void LCDInit(void){
	LCDSetPin();

	HIGHT(LCD_RST);								//  set RST + CE + DC + SCK + DIN
	HIGHT(LCD_CE);
	HIGHT(LCD_DC);
	HIGHT(LCD_CLK);
	HIGHT(LCD_DIN);
	//1. reset LCD
   LOW(LCD_RST);  								//  Reset  LCD
   HIGHT(LCD_RST);    							//  set new state;
   //2.send command set (H=1)
   LCDWrite(EW_COMMAND, 0x21);                  //	set extended commands
   //3.send Command Set Voltage VOP
   LCDWrite(EW_COMMAND, 0xC0);         			//	Set LCD Vop =5v
   //4.set temp
   LCDWrite(EW_COMMAND, 0x07);       			//	Set Temp Vlcd=3
   //5.set bias
   LCDWrite(EW_COMMAND, 0x13);             		//	LCD bias (n=4, 1:48)
   //6. send command set (H=0)
   LCDWrite(EW_COMMAND, 0x20);                  	//	set use basic commands
   //7. set mode
   LCDWrite(EW_COMMAND, 0x0C);                    //	Set display control: normal mode(0C)
}

void LCDBitmap(__uint8 *my_array){
  __int32 index;
  for (index = 0 ; index < (LCD_X * LCD_Y / 8) ; index++)
    LCDWrite(EW_DATA, my_array[index]);
}
