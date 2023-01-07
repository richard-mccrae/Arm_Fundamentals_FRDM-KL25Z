#include <MKL25Z4.h>
#include <stdbool.h>

#include "std_funcs.h"
#include "rgb.h"
#include "dac.h"

static void CMP0_IRQHandler(void)
{
	/* *** Consider setting break point here */
	if (CMP0->SCR & CMP_SCR_CFR_MASK) { 
		/* Rising edge, green light */
		rgb_led_on(GREEN);
		rgb_led_off(RED);
	} else if (CMP0->SCR & CMP_SCR_CFF_MASK) {
		/* Falling edge, red light */
		rgb_led_on(RED);
		rgb_led_off(GREEN);
	}
	
	/* Clear flags, keep both rising and falling edges enabled */
	CMP0->SCR = CMP_SCR_IEF_MASK | CMP_SCR_IER_MASK | CMP_SCR_CFR_MASK | CMP_SCR_CFF_MASK;
}

int main(void) {
	SystemCoreClockUpdate();
	rgb_init(true);
	dac_init();
	comparator_init();
	
	generate_triangle();
	
	return 0;
}
