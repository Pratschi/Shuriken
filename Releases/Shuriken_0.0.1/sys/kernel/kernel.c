#include <stdint.h>
#include "bootinfo.h"

// VGA text buffer (BIOS)
char* vga = (char*)0xB8000;
int vga_pos = 0;

void vga_print(const char* s) {
    while (*s) {
        vga[vga_pos++] = *s++;
        vga[vga_pos++] = 0x07;
    }
}

void fb_putpixel(uint32_t* fb, int x, int y, uint32_t color, uint32_t pitch) {
    fb[y * (pitch/4) + x] = color;
}

void fb_clear(struct BootInfo* boot) {
    uint32_t* fb = (uint32_t*)boot->fb_addr;
    for (int y = 0; y < boot->fb_height; y++)
        for (int x = 0; x < boot->fb_width; x++)
            fb_putpixel(fb, x, y, 0x202020, boot->fb_pitch);
}

void fb_print(struct BootInfo* boot, const char* s) {
    uint32_t* fb = (uint32_t*)boot->fb_addr;
    int x = 10, y = 10;

    while (*s) {
        char c = *s++;
        for (int dy = 0; dy < 8; dy++)
            for (int dx = 0; dx < 8; dx++)
                fb_putpixel(fb, x+dx, y+dy, 0xffffff, boot->fb_pitch);
        x += 10;
    }
}

void kernel_entry(struct BootInfo* boot)
{
    if (boot->boot_type == 0) {
        vga_print("Shuriken Kernel (BIOS)\n> ");
    } else {
        fb_clear(boot);
        fb_print(boot, "Shuriken Kernel (UEFI)");
    }

    for (;;) {}
}
