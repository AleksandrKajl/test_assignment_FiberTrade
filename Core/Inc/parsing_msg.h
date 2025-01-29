//
// Created by Aleksandr on 27.01.2025.
//

#ifndef TEST_ASSIGNMENT_FIBERTRADE_PARSING_MSG_H
#define TEST_ASSIGNMENT_FIBERTRADE_PARSING_MSG_H
#include "ring_buf.h"

/*!
* @brief Перечесления описывающии полученную команду
*/
typedef enum Receive_msg {
    LED1_ON = 0,
    LED2_ON,
    LED1_OFF,
    LED2_OFF,
    READ_I2C
}Receive_msg_t;

/*!
* @brief Парсинг кольцевого буфера и извлечение из него команд в кольцевой буфер команд
 * функция ожидает сивол возврата каретки '\r' в конце каждой команды для их парсинга
 * @param[in] rx_buf - Указател на кольцевой буфер с полученными данными
 * @param[Out] cmd_buff - Указатель на кольцевой буфер для полученных комманд
*/
void get_msg(RING_buffer_t *rx_buf, RING_buffer_t *cmd_buff);

#endif //TEST_ASSIGNMENT_FIBERTRADE_PARSING_MSG_H
