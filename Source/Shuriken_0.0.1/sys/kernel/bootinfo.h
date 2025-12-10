#pragma once
#include <stdint.h>

struct BootInfo {
    uint64_t fb_addr;
    uint32_t fb_width;
    uint32_t fb_height;
    uint32_t fb_pitch;
    uint8_t  boot_type; // 0=BIOS, 1=UEFI
};
