//
// Created by Aleksandr on 27.01.2025.
//
#include "led_drv.h"
#include "main.h"

// Включить светодиод
void led1_on()
{
    LL_GPIO_ResetOutputPin(LED_GPIO_Port, LED_Pin);
}

// Выключить светодиод
void led1_off()
{
    LL_GPIO_SetOutputPin(LED_GPIO_Port, LED_Pin);
}

void led2_on()
{

}

void led2_off()
{

}