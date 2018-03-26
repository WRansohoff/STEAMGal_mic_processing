#ifndef _VVC_UTIL_C_H
#define _VVC_UTIL_C_H

#include "global.h"

// C-languages utility method signatures.

// Methods for writing to the 1KB OLED framebuffer.
// These don't actually write through to the screen until
// the 'i2c_display_framebuffer' method is called (see util.S)
void oled_draw_h_line(int x, int y, int w, unsigned char color);
void oled_draw_v_line(int x, int y, int h, unsigned char color);
void oled_draw_rect(int x, int y, int w, int h,
                    int outline, unsigned char color);
void oled_write_pixel(int x, int y, unsigned char color);
void oled_draw_letter(int x, int y, unsigned int w0, unsigned int w1, unsigned char color, char size);
void oled_draw_letter_c(int x, int y, char c, unsigned char color, char size);
void oled_draw_letter_i(int x, int y, int ic, unsigned char color, char size);
void oled_draw_text(int x, int y, char* cc, unsigned char color, char size);

// Firmware support methods.
void draw_test_menu();
void draw_mic_readout();

#endif
