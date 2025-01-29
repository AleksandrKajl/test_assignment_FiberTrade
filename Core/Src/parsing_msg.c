//
// Created by Aleksandr on 27.01.2025.
//
#include "parsing_msg.h"
#include <string.h>
//Массивы команд сделаны глобальными для экономии памяти в рекурсивной функции get_msg
const uint8_t gk_led1_on[] = "led1 on";
const uint8_t gk_led1_off[] = "led1 off";
const uint8_t gk_led2_on[] = "led2 on";
const uint8_t gk_led2_off[] = "led2 off";
const uint8_t gk_read_i2c[] = "read i2c";

#define MAXCMD_SZ  20
uint8_t g_buf[MAXCMD_SZ];       //Буфер для хранения одной команды


void get_msg(RING_buffer_t *rx_buf, RING_buffer_t *cmd_buf)
{
    //Количество полученных байт в буфере
    const uint16_t k_buff_sz = RING_get_count(rx_buf);
    //Если нет данных
    if (!k_buff_sz) {
        return;
    }

    uint16_t cmdend_idx = 0;
    while (cmdend_idx < k_buff_sz) {            //Пока не конецц данных
        g_buf[cmdend_idx] = RING_pop(rx_buf);   //Извлекаем байт в буфер
        if (g_buf[cmdend_idx] == '\r') {        //Ищем символ возврата каретки как признак конца команды
            g_buf[cmdend_idx++] = 0;            //Заменяем его на символ конца строки '\0'
            break;                              //выходим из цикла
        }
        cmdend_idx++;
    }

    //Сравниваем строки для определения полученной команды
    if (!strcmp(g_buf, gk_led1_on)) {
        RING_put(LED1_ON, cmd_buf);
    } else if (!strcmp(g_buf, gk_led1_off)) {
        RING_put(LED1_OFF, cmd_buf);
    } else if (!strcmp(g_buf, gk_led2_on)) {
        RING_put(LED2_ON, cmd_buf);
    } else if (!strcmp(g_buf, gk_led2_off)) {
        RING_put(LED2_OFF, cmd_buf);
    }else if (!strcmp(g_buf, gk_read_i2c)) {
        RING_put(READ_I2C, cmd_buf);
    }

    //Обнудяем буфер команд
    memset(g_buf, 0x00, MAXCMD_SZ);

    //Если есть ещё команды входим в рекурсию
    if (cmdend_idx < k_buff_sz) {
        get_msg(rx_buf, cmd_buf);
    }
}

