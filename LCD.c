


#define LCD_DATA GPIO_PORTB_DATA_R
#define LCD_CONTROL GPIO_PORTE_DATA_R
#define LCD_DATA_DIR GPIO_PORTB_DIR_R
#define LCD_CONTROL_DIR GPIO_PORTE_DIR_R

#include "tm4c123gh6pm.h"
//#include "lcd.h"
#include "GLCD/glcd.h"

#include <stdio.h>

#include "pll/pll.h"
//#include "systick.c"
#include "uart/uart.h"
#include "adc/ADCSWTrigger.h"
#include "adc/ADCSWTrigger.c"

void mcu_init(void);
void SysTick_Init(void);
void SysTick_Wait1ms(unsigned long delay);

int main(void){
	
	unsigned char adcpin = 4;
	char buffer[64];
	
	unsigned char values[128];
	
	
		
	mcu_init();
	//lcd_init4();
	
	PLL_Init();
	SysTick_Init();
	UART_Init();
	glcd_init();
	ADC0_InitSWTriggerSeq3(0x04);
	glcd_clear();
	
	//hlavní smycka
	while(1){
		int i;
		//lcd_prints(0,12,"test");
		
		glcd_clear();
		
		ADC0_SSMUX3_R &= ~0x000F;       // 11) clear SS3 field
		ADC0_SSMUX3_R += adcpin;
		
		values[0] = ADC0_InSeq3()>>6;
		
		for(i = 1; i < 128; i++){
			values[i] = ADC0_InSeq3()>>6;
			
			glcd_line(i - 1, 64 - values[i - 1], i, 64-values[i]);
			sprintf(buffer, "Hodnota %d: %d\r\n", i, values[i]);
			UART_OutString(buffer);
			
			SysTick_Wait1ms(10);			
		}
		
		/*UART_OutString("Zadejte cislo pinu [4-7]: \r\n");
		//budeme z pc prijimat jeden byte tlacitka 1-4
		adcpin = UART_InChar() - '0';*/
		
		
		//vypisovat na display co merime
		//sprintf(buffer, "Pin: %d", adcpin);
		//lcd_prints(0,0,buffer);
		
		//vypisovat na display namerenou hodnotu
		//sprintf(buffer, "Hodnota: %04d", analogValue);
		//lcd_prints(1,0,buffer);
	}
}

void PortB_Init(void){
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB;	//1) enable clock: SYSCTL_RCGC2_R
	delay = SYSCTL_RCGC2_R;	//allow time for clock to stabilise
	
	GPIO_PORTB_AMSEL_R = 0x00;	//3) disable analog: GPIO_PORTx_AMSEL_R
	GPIO_PORTB_PCTL_R = 0x00000000;	//4) disable alternate: GPIO_PORTx_PCTL_R, GPIO_PORTx_AFSEL_R
	GPIO_PORTB_AFSEL_R = 0x00;	
	
	GPIO_PORTB_DEN_R = 0xFF;	//7) enable digital: GPIO_PORTx_DEN_R

}

void PortE_Init(void){
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE;	//1) enable clock: SYSCTL_RCGC2_R
	delay = SYSCTL_RCGC2_R;	//allow time for clock to stabilise
	
	GPIO_PORTE_AMSEL_R = 0x00;	//3) disable analog: GPIO_PORTx_AMSEL_R
	GPIO_PORTE_PCTL_R = 0x00000000;	//4) disable alternate: GPIO_PORTx_PCTL_R, GPIO_PORTx_AFSEL_R
	GPIO_PORTE_AFSEL_R = 0x00;	
	
	GPIO_PORTE_DEN_R = 0xff;	//7) enable digital: GPIO_PORTx_DEN_R

}

void mcu_init(void){
	
	volatile unsigned long delay;
	PortB_Init();
	PortE_Init();
	/*
	GLCD_PORT = 0x00;
	GLCD_CONTROL &= ~(1 << GLCD_EN | 1 << GLCD_RS | 1 << GLCD_RW | 1 << GLCD_CS1 | 1 << GLCD_CS2 | 1 << GLCD_RESETB);
	*/
	GPIO_PORTB_DIR_R = 0xff; //výstup
	GPIO_PORTE_DIR_R = 0xff;
	
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD;	//1) enable clock: SYSCTL_RCGC2_R
	delay = SYSCTL_RCGC2_R;
	
	SYSCTL_RCGCGPIO_R |= 0x0f;
  while((SYSCTL_PRGPIO_R&0x0f) != 0x0f){};
  GPIO_PORTD_DIR_R &= ~0x0f;      // 2) make PE4 input
  GPIO_PORTD_AFSEL_R |= 0x0f;     // 3) enable alternate function on PE4
  GPIO_PORTD_DEN_R &= ~0x0f;      // 4) disable digital I/O on PE4
  GPIO_PORTD_AMSEL_R |= 0x0f;     // 5) enable analog functionality on PE4
}

// Initialize SysTick with busy wait running at bus clock.
void SysTick_Init(void){
  NVIC_ST_CTRL_R = 0;                   // disable SysTick during setup
  NVIC_ST_RELOAD_R = NVIC_ST_RELOAD_M;  // maximum reload value
  NVIC_ST_CURRENT_R = 0;                // any write to current clears it
                                        // enable SysTick with core clock
  NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE+NVIC_ST_CTRL_CLK_SRC;
}
// Time delay using busy wait.
// The delay parameter is in units of the 6 MHz core clock. (167 nsec)
/*void SysTick_Wait(unsigned long delay){
  volatile unsigned long elapsedTime;
  unsigned long startTime = NVIC_ST_CURRENT_R;
  do{
    elapsedTime = (startTime-NVIC_ST_CURRENT_R)&0x00FFFFFF;
  }
  while(elapsedTime <= delay);
}*/

// Time delay using busy wait.
// 10000us equals 10ms
void SysTick_Wait1ms(unsigned long delay){
  unsigned long i;
  for(i=0; i<delay; i++){
    SysTick_Wait(50000);  // wait 10ms (assumes 50 MHz clock)
  }
}
