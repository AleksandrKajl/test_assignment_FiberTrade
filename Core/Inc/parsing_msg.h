//
// Created by Aleksandr on 27.01.2025.
//

#ifndef TEST_ASSIGNMENT_FIBERTRADE_PARSING_MSG_H
#define TEST_ASSIGNMENT_FIBERTRADE_PARSING_MSG_H
#include "ring_buf.h"

typedef enum Receive_msg {
    LED1_ON = 0,
    LED2_ON,
    LED1_OFF,
    LED2_OFF,
    READ_I2C
}Receive_msg_t;

void get_msg(RING_buffer_t *rx_buf, RING_buffer_t *cmd_buff);

#endif //TEST_ASSIGNMENT_FIBERTRADE_PARSING_MSG_H
