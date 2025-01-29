//
// Created by Aleksandr on 27.01.2025.
//
#include "parsing_msg.h"
#include <string.h>

const uint8_t gk_led1_on[] = "led1 on";
const uint8_t gk_led1_off[] = "led1 off";
const uint8_t gk_led2_on[] = "led2 on";
const uint8_t gk_led2_off[] = "led2 off";
const uint8_t gk_read_i2c[] = "read i2c";

#define MAXCMD_SZ  20
uint8_t buf[MAXCMD_SZ];

void get_msg(RING_buffer_t *rx_buf, RING_buffer_t *cmd_buf)
{
    const uint16_t k_buff_sz = RING_get_count(rx_buf);
    if (!k_buff_sz) {
        return;
    }

    uint16_t cmdend_idx = 0;
    while (cmdend_idx < k_buff_sz) {
        buf[cmdend_idx] = RING_pop(rx_buf);
        if (buf[cmdend_idx] == '\r') {
            buf[cmdend_idx++] = 0;
            break;
        }
        cmdend_idx++;
    }

    if (!strcmp(buf, gk_led1_on)) {
        RING_put(LED1_ON, cmd_buf);
    } else if (!strcmp(buf, gk_led1_off)) {
        RING_put(LED1_OFF, cmd_buf);
    } else if (!strcmp(buf, gk_led2_on)) {
        RING_put(LED2_ON, cmd_buf);
    } else if (!strcmp(buf, gk_led2_off)) {
        RING_put(LED2_OFF, cmd_buf);
    }else if (!strcmp(buf, gk_led2_off)) {
        RING_put(READ_I2C, cmd_buf);
    }


    memset(buf, 0x00, MAXCMD_SZ);

    if (cmdend_idx < k_buff_sz) {
        get_msg(rx_buf, cmd_buf);
    }
}

