#include "stm32f411xe.h"
#include "spi.h"

void spi_pin_init()
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    GPIOA->MODER |= 2 << GPIO_MODER_MODE5_Pos | 2 << GPIO_MODER_MODE6_Pos | 2 << GPIO_MODER_MODE7_Pos | 1 << GPIO_MODER_MODER3_Pos;

    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5 | GPIO_OSPEEDER_OSPEEDR6 | GPIO_OSPEEDER_OSPEEDR7;

    GPIOA->AFR[0] |= 5 << (4 * 5) | 5 << (4 * 6) | 5 << (4 * 7);

    GPIOA->BSRR |= 1 << 3;
}

Spi spi;

int main()
{
    uint8_t buffer[] = "Asraful Islam Taj";
    spi_pin_init();
    spi.init();

    GPIOA->BSRR |= 1 << 3 << 16;

    spi.send(buffer, sizeof(buffer));

    GPIOA->BSRR |= 1 << 3;

    while (true)
    {
    }
}