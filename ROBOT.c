//knihovny / header files

#include "tm4c123gh6pm.h"	//vlastni knihovny
#include "pll\PLL.h"	//vlastni knihovny
#include <stdio.h>	//standartni knihovny
#include <string.h>






void mcu_init(void){
/*
1) enable clock: SYSCTL_RCGC2_R
2) unlock: GPIO_PORTx_LOCK_R (PC3-0, PD7, PF0)
3) disable analog: GPIO_PORTx_AMSEL_R
4) disable alternate: GPIO_PORTx_PCTL_R, GPIO_PORTx_AFSEL_R
5) set direction: GPIO_PORTx_DIR_R
6) pull-up/pull-down/open-drain: GPIO_PORTx_PUR_R
7) enable digital: GPIO_PORTx_DEN_R
*/
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB | SYSCTL_RCGC2_GPIOE | SYSCTL_RCGC2_GPIOD;
	
	GPIO_PORTB_AMSEL_R = 0x00;
	GPIO_PORTB_PCTL_R = 0x00000000;
	GPIO_PORTB_DIR_R = 0x00;
	GPIO_PORTB_AFSEL_R = 0x00;
	GPIO_PORTB_DEN_R = 0xFF;
	
	GPIO_PORTE_AMSEL_R = 0x00;
	GPIO_PORTE_PCTL_R = 0x00000000;
	GPIO_PORTE_DIR_R = 0xFF;
	GPIO_PORTE_AFSEL_R = 0x00;
	GPIO_PORTE_DEN_R = 0xFF;
	
	GPIO_PORTD_AMSEL_R = 0x00;
	GPIO_PORTD_PCTL_R = 0x00000000;
	GPIO_PORTD_DIR_R = 0xFF;
	GPIO_PORTD_AFSEL_R = 0x00;
	GPIO_PORTD_DEN_R = 0xFF;
	/*
	//LCD_DATA a LCD_CONTROL<LCD_RS,LCD_RW,LCD_EN> výstupní režim
	LCD_DATA = 0x00;
	LCD_CONTROL = LCD_CONTROL & ~(0x1<<LCD_RS | 0x1<<LCD_RW | 0x1<<LCD_EN);
	LCD_DATA_DIR = 0xFF;
	LCD_CONTROL_DIR = 0x1<<LCD_RS | 0x1<<LCD_RW | 0x1<<LCD_EN;
	*/
	
	
	/*
	SYSCTL_RCGC2_R |=SYSCTL_RCGC2_GPIOD;
	
  SYSCTL_RCGCADC_R |= 0x0001;   // 7) activate ADC0 
                                  // 1) activate clock for Port D
  SYSCTL_RCGCGPIO_R |= 0x10;
  while((SYSCTL_PRGPIO_R&0x10) != 0x10){};
		
  GPIO_PORTD_DIR_R &= ~0x0F;      // 2) make PE4 input
  GPIO_PORTD_AFSEL_R |= 0x0F;     // 3) enable alternate function on PD4
  GPIO_PORTD_DEN_R &= ~0x0F;      // 4) disable digital I/O on PD4
  GPIO_PORTD_AMSEL_R |= 0x0F;     // 5) enable analog functionality on PD4
	*/
}
/*
void ADC0_set_ch(unsigned char channel)
{
	
  ADC0_PC_R &= ~0xF;              // 7) clear max sample rate field
  ADC0_PC_R |= 0x1;               //    configure for 125K samples/sec
  ADC0_SSPRI_R = 0x0123;          // 8) Sequencer 3 is highest priority
  ADC0_ACTSS_R &= ~0x0008;        // 9) disable sample sequencer 3
  ADC0_EMUX_R &= ~0xF000;         // 10) seq3 is software trigger
  ADC0_SSMUX3_R &= ~0x000F;       // 11) clear SS3 field
  ADC0_SSMUX3_R += channel;             //    set channel
  ADC0_SSCTL3_R = 0x0006;         // 12) no TS0 D0, yes IE0 END0
  ADC0_IM_R &= ~0x0008;           // 13) disable SS3 interrupts
  ADC0_ACTSS_R |= 0x0008;         // 14) enable sample sequencer 3
	
	
}
*/

void SysTick_Init(void){
  NVIC_ST_CTRL_R = 0;                   // disable SysTick during setup
  NVIC_ST_RELOAD_R = NVIC_ST_RELOAD_M;  // maximum reload value
  NVIC_ST_CURRENT_R = 0;                // any write to current clears it
                                        // enable SysTick with core clock
  NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE+NVIC_ST_CTRL_CLK_SRC;
}
void SysTick_Wait(unsigned long delay){
  volatile unsigned long elapsedTime;
  unsigned long startTime = NVIC_ST_CURRENT_R;
  do{
    elapsedTime = (startTime-NVIC_ST_CURRENT_R)&0x00FFFFFF;
  }
  while(elapsedTime <= delay);
}
void SysTick_Wait1ms(unsigned long delay){
  unsigned long i;
  for(i=0; i<delay; i++){
    SysTick_Wait(50000);  // wait 1ms (assumes 6 MHz clock)
  }
}


	//unsigned char x= 0xAA;
int main(void){
	/*
	unsigned char x = 0, y = 0;
	char ret[17];*/
/*	char ret[17];
	//unsigned char hodiny = 0, minuty = 0, sekundy = 0;// cas = 0;
	char vstupC = '0'; // 0-teplota7; 1-photo6; 2-trim15; 3-trim24;
	char vstup = 0;
	char kanal = 0;
	char kanalC = 0;*/
	PLL_Init();
	mcu_init();
	//lcd_init4();
	SysTick_Init();
	/*
	UART_Init();
	
	glcd_init();
	glcd_clear();
	
	ADC0_set_ch(7);
	*/
	/*while(1){
		x=x >> 1;
		GPIO_PORTE_DATA_R = x;
		SysTick_Wait1ms(1000);
	}*/
		
	while(1){
		
		
			
		while(!(GPIO_PORTB_DATA_R & 0x01)){
			GPIO_PORTE_DATA_R = 0x04;
			GPIO_PORTE_DATA_R |= 0x02;
		SysTick_Wait1ms(1);
		GPIO_PORTE_DATA_R &= 0xFD;
		SysTick_Wait1ms(1);
		}
		while(!(GPIO_PORTB_DATA_R & 0x02)){
			GPIO_PORTE_DATA_R = 0x00;
			GPIO_PORTE_DATA_R |= 0x02;
		SysTick_Wait1ms(1);
		GPIO_PORTE_DATA_R &= 0xFD;
		SysTick_Wait1ms(1);
		}
		while(!(GPIO_PORTB_DATA_R & 0x04)){
			GPIO_PORTE_DATA_R = 0x00;
			GPIO_PORTE_DATA_R |= 0x10;
		SysTick_Wait1ms(1);
		GPIO_PORTE_DATA_R &= 0xEF;
		SysTick_Wait1ms(1);
		}
		while(!(GPIO_PORTB_DATA_R & 0x08)){
			GPIO_PORTE_DATA_R = 0x20;
			GPIO_PORTE_DATA_R |= 0x10;
		SysTick_Wait1ms(1);
		GPIO_PORTE_DATA_R &= 0xEF;
		SysTick_Wait1ms(1);
		}
		GPIO_PORTE_DATA_R = 0x00;
		
		while(!(GPIO_PORTB_DATA_R & 0x10)){
			GPIO_PORTD_DATA_R = 0x04;
			GPIO_PORTD_DATA_R |= 0x02;
		SysTick_Wait1ms(1);
		GPIO_PORTD_DATA_R &= 0xFD;
		SysTick_Wait1ms(1);
		}
		while(!(GPIO_PORTB_DATA_R & 0x20)){
			GPIO_PORTD_DATA_R = 0x00;
			GPIO_PORTD_DATA_R |= 0x02;
		SysTick_Wait1ms(1);
		GPIO_PORTD_DATA_R &= 0xFD;
		SysTick_Wait1ms(1);
		}
		while(!(GPIO_PORTB_DATA_R & 0x40)){
			GPIO_PORTD_DATA_R = 0x00;
			GPIO_PORTD_DATA_R |= 0x40;
		SysTick_Wait1ms(1);
		GPIO_PORTD_DATA_R &= 0xAF;
		SysTick_Wait1ms(1);
		}
		while(!(GPIO_PORTB_DATA_R & 0x80)){
			GPIO_PORTD_DATA_R = 0x80;
			GPIO_PORTD_DATA_R |= 0x40;
		SysTick_Wait1ms(1);
		GPIO_PORTD_DATA_R &= 0xF;
		SysTick_Wait1ms(1);
		}
		GPIO_PORTD_DATA_R = 0x00;
		
		
		
		
		
		
		
		
		
		
		
		/*
		if(!(GPIO_PORTB_DATA_R & 0x01)){
			GPIO_PORTE_DATA_R |= 0x01;
		}
		else{
		GPIO_PORTE_DATA_R &= 0xFE;
		}
		
		if(!(GPIO_PORTB_DATA_R & 0x02)){
			GPIO_PORTE_DATA_R |= 0x02;
		}
		else{
		GPIO_PORTE_DATA_R &= 0xFD;
		}
		
		if(!(GPIO_PORTB_DATA_R & 0x04)){
			GPIO_PORTE_DATA_R |= 0x04;
		}
		else{
		GPIO_PORTE_DATA_R &= 0xFA;
		}
		*/
		
		
		
		}
		
		/*
		vstupC = UART_InChar();
		vstup = vstupC - '0';
		if(vstup != kanal){
			kanal = vstup;
			kanalC = 7 - kanal;
			ADC0_set_ch(kanalC);
		}
		*/
		
		
		/*
		
		y= ADC0_InSeq3() >> 5;
		
		
		
		
		
		
		
		*/
		/*
		glcd_point(x,ADC0_InSeq3() >>6);
		sprintf(ret,"%u \r\n",x);
		UART_OutString(ret);
		
		x++;
		if(x>127){
			x=0;
			glcd_clear();
		}
		delay_ms(100);
		*/
												//zapisovat hodnoty jakobody na lcd
	
	/*while(1){
		
		vstupC = UART_InChar();
		vstup = vstupC - '0';
		if(vstup != kanal){
			kanal = vstup;
			kanalC = 7 - kanal;
			ADC0_set_ch(kanalC);
		}
		
		
		switch(kanal){
			
			case 0:sprintf(ret,"teplota : %02u",ADC0_InSeq3());
			break;
			case 1:sprintf(ret,"photo   : %02u",ADC0_InSeq3());
			break;
			case 2:sprintf(ret,"trim1   : %02u",ADC0_InSeq3());
			break;
			case 3:sprintf(ret,"trim2   : %02u",ADC0_InSeq3());
			break;
		}
		lcd_print(0,0,ret);
		UART_OutString(ret);
		UART_OutChar(9);
		UART_OutChar(13);
		
	}
	*/
	

	
	
	
	/*while(1){
		//sprintf(ret,"%02u:%02u:%02u",hodiny,minuty,sekundy);
		//lcd_print(0,0,ret);
		//delay_ms(100);
		//SysTick_Wait1ms(1000);
		if(sekundy >= 59){
			//lcd_cmd4(LCD_DISPLAY_CLEAR);
			sekundy = 0;
			if(minuty >= 59){
				//lcd_cmd4(LCD_DISPLAY_CLEAR);
				minuty = 0;
				hodiny++;
			}
			else{
			minuty++;
			}
		}
		else{
		sekundy++;
		}
		UART_OutString(ret);
		UART_OutChar(CR);
		UART_OutChar(LF);
		UART_InString(ret,16);
		lcd_print(0,0,ret);
		lcd_print(0,0,"0");
		lcd_data4(UART_InChar());
		
		
		
		
		
		
	}*/
	
	

}
