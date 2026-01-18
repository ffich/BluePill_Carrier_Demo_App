#include "ssd1306.h"
#include <string.h>
#include "ssd1306_font5x7.h"


/* ---------------- I2C low-level ---------------- */

static HAL_StatusTypeDef ssd1306_write_cmd(ssd1306_t *dev, uint8_t cmd)
{
    uint8_t data[2] = {0x00, cmd}; // control=0x00 -> command
    return HAL_I2C_Master_Transmit(dev->hi2c, SSD1306_I2C_ADDR, data, 2, HAL_MAX_DELAY);
}

static HAL_StatusTypeDef ssd1306_write_data(ssd1306_t *dev, const uint8_t *p, uint16_t len)
{
    // control=0x40 -> data
    // chunk small to be safe with I2C drivers
    uint8_t chunk[1 + 16];
    chunk[0] = 0x40;

    while (len) {
        uint16_t n = (len > 16) ? 16 : len;
        memcpy(&chunk[1], p, n);
        HAL_StatusTypeDef st = HAL_I2C_Master_Transmit(dev->hi2c, SSD1306_I2C_ADDR, chunk, n + 1, HAL_MAX_DELAY);
        if (st != HAL_OK) return st;
        p   += n;
        len -= n;
    }
    return HAL_OK;
}

/* ---------------- minimal 5x7 font ----------------
   Each char is 5 bytes, each byte = vertical column (LSB at top).
   Only chars needed for "HELLO WORLD!" + space.
*/

static const uint8_t FONT_SPACE[5] = {0x00,0x00,0x00,0x00,0x00};
static const uint8_t FONT_EXCL [5] = {0x00,0x00,0x5F,0x00,0x00};

static const uint8_t FONT_D[5] = {0x7F,0x41,0x41,0x22,0x1C};
static const uint8_t FONT_E[5] = {0x7F,0x49,0x49,0x49,0x41};
static const uint8_t FONT_H[5] = {0x7F,0x08,0x08,0x08,0x7F};
static const uint8_t FONT_L[5] = {0x7F,0x40,0x40,0x40,0x40};
static const uint8_t FONT_O[5] = {0x3E,0x41,0x41,0x41,0x3E};
static const uint8_t FONT_R[5] = {0x7F,0x09,0x19,0x29,0x46};
static const uint8_t FONT_W[5] = {0x7F,0x20,0x18,0x20,0x7F};

static const uint8_t* font_get(char c)
{
    if (c < 0x20 || c > 0x7F) return font5x7[0]; // spazio
    return font5x7[c - 0x20];
}

/* ---------------- framebuffer drawing ---------------- */

void ssd1306_clear(ssd1306_t *dev)
{
    memset(dev->buffer, 0x00, sizeof(dev->buffer));
    dev->cursor_x = 0;
    dev->cursor_y = 0;
}

void ssd1306_set_cursor(ssd1306_t *dev, uint8_t x, uint8_t y)
{
    dev->cursor_x = x;
    dev->cursor_y = y;
}

void ssd1306_draw_pixel(ssd1306_t *dev, uint8_t x, uint8_t y, uint8_t color)
{
    if (x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT) return;
    uint16_t i = x + (y / 8) * SSD1306_WIDTH;
    uint8_t  m = 1u << (y & 7);
    if (color) dev->buffer[i] |=  m;
    else       dev->buffer[i] &= ~m;
}

void ssd1306_write_char(ssd1306_t *dev, char c, uint8_t color)
{
    const uint8_t *glyph = font_get(c);

    // 5 columns + 1 empty column spacing
    for (int col = 0; col < 5; col++) {
        uint8_t bits = glyph[col];
        for (int row = 0; row < 8; row++) {
            uint8_t on = (bits >> row) & 0x01;
            ssd1306_draw_pixel(dev, dev->cursor_x + col, dev->cursor_y + row, on ? color : 0);
        }
    }
    // spacing column
    for (int row = 0; row < 8; row++) {
        ssd1306_draw_pixel(dev, dev->cursor_x + 5, dev->cursor_y + row, 0);
    }

    dev->cursor_x += 6; // advance
    if (dev->cursor_x + 6 >= SSD1306_WIDTH) {
        dev->cursor_x = 0;
        dev->cursor_y += 8;
    }
}

void ssd1306_write_string(ssd1306_t *dev, const char *s, uint8_t color)
{
    while (*s) {
        ssd1306_write_char(dev, *s++, color);
    }
}

/* ---------------- init + update ---------------- */

HAL_StatusTypeDef ssd1306_init(ssd1306_t *dev, I2C_HandleTypeDef *hi2c)
{
    dev->hi2c = hi2c;
    ssd1306_clear(dev);

    HAL_StatusTypeDef st;

    st = ssd1306_write_cmd(dev, 0xAE); if (st) return st; // display off
    st = ssd1306_write_cmd(dev, 0xD5); if (st) return st; // clock
    st = ssd1306_write_cmd(dev, 0x80); if (st) return st;

    st = ssd1306_write_cmd(dev, 0xA8); if (st) return st; // multiplex
    st = ssd1306_write_cmd(dev, 0x3F); if (st) return st; // 64-1

    st = ssd1306_write_cmd(dev, 0xD3); if (st) return st; // offset
    st = ssd1306_write_cmd(dev, 0x00); if (st) return st;

    st = ssd1306_write_cmd(dev, 0x40); if (st) return st; // start line 0

    st = ssd1306_write_cmd(dev, 0x8D); if (st) return st; // charge pump
    st = ssd1306_write_cmd(dev, 0x14); if (st) return st;

    st = ssd1306_write_cmd(dev, 0x20); if (st) return st; // memory mode
    st = ssd1306_write_cmd(dev, 0x00); if (st) return st; // horizontal

    // Se vedi roba "specchiata" o spostata, prova a invertire queste due:
    st = ssd1306_write_cmd(dev, 0xA1); if (st) return st; // segment remap
    st = ssd1306_write_cmd(dev, 0xC8); if (st) return st; // com scan dec

    st = ssd1306_write_cmd(dev, 0xDA); if (st) return st; // com pins
    st = ssd1306_write_cmd(dev, 0x12); if (st) return st;

    st = ssd1306_write_cmd(dev, 0x81); if (st) return st; // contrast
    st = ssd1306_write_cmd(dev, 0x7F); if (st) return st;

    st = ssd1306_write_cmd(dev, 0xD9); if (st) return st; // pre-charge
    st = ssd1306_write_cmd(dev, 0xF1); if (st) return st;

    st = ssd1306_write_cmd(dev, 0xDB); if (st) return st; // vcom detect
    st = ssd1306_write_cmd(dev, 0x40); if (st) return st;

    st = ssd1306_write_cmd(dev, 0xA4); if (st) return st; // resume
    st = ssd1306_write_cmd(dev, 0xA6); if (st) return st; // normal
    st = ssd1306_write_cmd(dev, 0xAF); if (st) return st; // display on

    return ssd1306_update(dev);
}

HAL_StatusTypeDef ssd1306_update(ssd1306_t *dev)
{
    HAL_StatusTypeDef st;

    // set column address
    st = ssd1306_write_cmd(dev, 0x21); if (st) return st;
    st = ssd1306_write_cmd(dev, 0x00); if (st) return st;
    st = ssd1306_write_cmd(dev, 0x7F); if (st) return st;

    // set page address
    st = ssd1306_write_cmd(dev, 0x22); if (st) return st;
    st = ssd1306_write_cmd(dev, 0x00); if (st) return st;
    st = ssd1306_write_cmd(dev, 0x07); if (st) return st;

    return ssd1306_write_data(dev, dev->buffer, sizeof(dev->buffer));
}
