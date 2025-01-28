//
// Created by Aleksandr on 27.01.2025.
//
#include "led_drv.h"
#include "main.h"
#include "tim.h"

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
#define DUTY_CYCLE 0xFFFF //Скважность
    int32_t crntBrightness = 0x00; //Текущая яркость подсветки
    const uint16_t  step = 0x1FF; //Шаг увелечения яркости подсветки(Влияет на плавность).

    while(crntBrightness != DUTY_CYCLE)
    {
        if((crntBrightness + step) <= DUTY_CYCLE)
            crntBrightness += step;
        else
            crntBrightness = DUTY_CYCLE;

        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, crntBrightness);
        HAL_Delay(50); // Задержка влияет на время включения полной яркости
    }
}

void led2_off()
{
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);
}