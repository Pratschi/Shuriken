#include <stdint.h>
#include "bootinfo.h"
#include "font16x16.h"  // Custom Lato-Style Font 16x16

// VGA text buffer
char* vga = (char*)0xB8000;
int vga_pos = 0;

// Draw VGA Character
void vga_draw_char(char c) {
    vga[vga_pos++] = c;
    vga[vga_pos++] = 0x07;
}

// Draw VGA String
void vga_draw_string(const char* s) {
    while (*s) vga_draw_char(*s++);
}

// Draw pixel in framebuffer
void fb_putpixel(uint32_t* fb, int x, int y, uint32_t color, uint32_t pitch) {
    fb[y * (pitch / 4) + x] = color;
}

// Clean framebuffer
void fb_clear(struct BootInfo* boot) {
    uint32_t* fb = (uint32_t*)boot->fb_addr;
    for (int y = 0; y < boot->fb_height; y++)
        for (int x = 0; x < boot->fb_width; x++)
            fb_putpixel(fb, x, y, 0x202020, boot->fb_pitch);
}

// Draw Character using Custom Font
void fb_draw_char16(struct BootInfo* boot, char c, int x, int y, uint32_t color) {
    const uint16_t* glyph = font16x16[(int)c];  // Bitmap for character
    uint32_t* fb = (uint32_t*)boot->fb_addr;

    for (int row = 0; row < 16; row++) {
        for (int col = 0; col < 16; col++) {
            if (glyph[row] & (1 << (15 - col))) {
                fb_putpixel(fb, x + col, y + row, color, boot->fb_pitch);
            }
        }
    }
}

// Draw String using Custom Font
void fb_draw_string16(struct BootInfo* boot, const char* s, int x, int y, uint32_t color) {
    while (*s) {
        fb_draw_char16(boot, *s++, x, y, color);
        x += 16; // Character width
    }
}

// Kernel Entry
void kernel_entry(struct BootInfo* boot)
{
    if (boot->boot_type == 0) {
        // BIOS Mode Detected - VGA Text Mode
        vga_draw_string("ShurikenOS\n");
    } else {
        // UEFI Mode Detected - Framebuffer Graphics Mode
        fb_clear(boot);
        fb_draw_string16(boot, "ShurikenOS", 50, 50, 0xFFFFFF);
    }

    for (;;) {}
}
