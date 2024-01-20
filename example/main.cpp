#include <cstdio>
#include <stdlib.h>
#include <pico/stdlib.h>

#include "debounce.pio.h"


int main() {
    stdio_init_all();
    sleep_ms(3*1000);
    printf("booted\n");

    uint debounce_offset = pio_add_program(pio1, &debounce_program);

    uint const debounce_gpio = 26;
    gpio_init(debounce_gpio);
    gpio_set_function(debounce_gpio, GPIO_FUNC_SIO);
    gpio_set_dir(debounce_gpio, false);  // input
    gpio_pull_up(debounce_gpio);   // In this example the button is NO and shorts to ground.

    debounce_init(pio1, debounce_offset, debounce_gpio);

    for (;;) {
        bool debounce_state;
        if (debounce_get_state(debounce_state)) {
            printf("got a debounce edge: %d\n", debounce_state);
        }
        sleep_ms(10);
    }
}
