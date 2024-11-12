#define RCC_BASE  0x40021000
#define PORTC_BASE  0x40011000
#define TIM2  0x40000000


#define RCC_APB2ENR   (*(volatile unsigned int *)(RCC_BASE + 0x18))
#define RCC_APB1ENR   (*(volatile unsigned int *)(RCC_BASE + 0x1C))

#define GPIOC_CRH     (*(volatile unsigned int *)(PORTC_BASE + 0x04))
#define GPIOC_BSRR    (*(volatile unsigned int *)(PORTC_BASE + 0x10))

#define PSC    (*(volatile unsigned int *)(TIM2 + 0x28))
#define ARR    (*(volatile unsigned int *)(TIM2 + 0x2C))
#define SR     (*(volatile unsigned int *)(TIM2 + 0x10))
#define TIM2_CR1    (*(volatile unsigned int *)(TIM2 + 0x00))

#define frequency 72000000


void delay(int count) {
	PSC = (frequency /1000) - 1;
	ARR = count - 1;
	SR &= ~(1);

	TIM2_CR1 |= 1;

	while (!(SR & 1));

	TIM2_CR1 &= ~(1);
}

int main() {
	// clock enable
	RCC_APB2ENR |= (1 << 4);
	RCC_APB1ENR |= 1;

	// mode and configuration setup
	GPIOC_CRH &= ~(0xF << 20);
	GPIOC_CRH |= (1 << 20);

	while (1) {
		GPIOC_BSRR |= (1 << 13);
		delay(1000);

		GPIOC_BSRR |= (1 << (13 + 16));
		delay(1000);
	}

	return 0;
}



