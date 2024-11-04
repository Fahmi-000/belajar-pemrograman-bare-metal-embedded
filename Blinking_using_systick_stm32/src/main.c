#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/vector.h>


#define RCCLEDPORT          (RCC_GPIOC)
#define LEDPORT             (GPIOC)
#define LEDPIN              (GPIO13)
#define GPIO_MODE_OUTPUT    GPIO_MODE_OUTPUT_2_MHZ
#define GPIO_PUPD_NONE      GPIO_CNF_OUTPUT_PUSHPULL
#define CPU_FREQ            (1000)
#define SYSTICK_FREQ        (2000000)

volatile uint64_t ticks = 0;
//static void rcc_setup(void) {
    //rcc_clock_setup_pll (&rcc_hsi_configs [RCC_CLOCK_HSI_64MHZ]);

//}
static void sys_tick_handler(void){
    ticks ++;
}

static void gpio_setup (void){
    rcc_periph_clock_enable(RCCLEDPORT);
    gpio_set_mode(LEDPORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LEDPIN);
}

static void systick_setup(void){
    systick_set_frequency(CPU_FREQ, SYSTICK_FREQ);
    systick_counter_enable();
    systick_interrupt_enable();
}

static void delay_cycle(uint32_t cycles){
    
    for (uint32_t i = 0; i < cycles; i++){
        __asm__("nop");
    }
}

int main (void) {
    gpio_setup();
    while (1)
    {
        gpio_clear(LEDPORT,LEDPIN);
        delay_cycle(750000);
        gpio_set(LEDPORT,LEDPIN);
        delay_cycle(250000);
    }
    
    return 0;
}