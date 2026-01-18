#pragma once
#include "stm32f1xx_hal.h"
#include <stdint.h>

#define SSD1306_WIDTH   128
#define SSD1306_HEIGHT  64
#define SSD1306_I2C_ADDR (0x3C << 1)   // prova 0x3D<<1 se il tuo modulo è diverso

typedef struct {
    I2C_HandleTypeDef *hi2c;
    uint8_t buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];
    uint8_t cursor_x;   // in pixel
    uint8_t cursor_y;   // in pixel
} ssd1306_t;

HAL_StatusTypeDef ssd1306_init(ssd1306_t *dev, I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef ssd1306_update(ssd1306_t *dev);

void ssd1306_clear(ssd1306_t *dev);
void ssd1306_set_cursor(ssd1306_t *dev, uint8_t x, uint8_t y);
void ssd1306_draw_pixel(ssd1306_t *dev, uint8_t x, uint8_t y, uint8_t color);

void ssd1306_write_char(ssd1306_t *dev, char c, uint8_t color);
void ssd1306_write_string(ssd1306_t *dev, const char *s, uint8_t color);
