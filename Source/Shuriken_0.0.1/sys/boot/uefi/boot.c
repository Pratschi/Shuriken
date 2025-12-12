#include <efi.h>
#include <efilib.h>
#include "bootinfo.h"

// BootInfo shared with kernel
EFI_STATUS efi_main(EFI_HANDLE img, EFI_SYSTEM_TABLE *sys)
{
    InitializeLib(img, sys);
    Print(L"Shuriken UEFI Bootloader...\n");

    EFI_FILE_IO_INTERFACE *io;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *fsp;
    EFI_FILE *root, *file;

    sys->BootServices->HandleProtocol(
        img, &gEfiSimpleFileSystemProtocolGuid,
        (void**)&fsp);

    fsp->OpenVolume(fsp, &root);

    if (root->Open(root, &file, L"kernel.bin",
                   EFI_FILE_MODE_READ, 0) != EFI_SUCCESS) {
        Print(L"Error: kernel.bin not found\n");
        return EFI_LOAD_ERROR;
    }

    UINTN size = 1024*1024;
    UINT8 *kernel = AllocatePool(size);
    file->Read(file, &size, kernel);

    // Get framebuffer
    EFI_GRAPHICS_OUTPUT_PROTOCOL *gop;
    sys->BootServices->LocateProtocol(
        &gEfiGraphicsOutputProtocolGuid, NULL,
        (void**)&gop);

    struct BootInfo *b = AllocatePool(sizeof(struct BootInfo));
    b->fb_addr = gop->Mode->FrameBufferBase;
    b->fb_width = gop->Mode->Info->HorizontalResolution;
    b->fb_height = gop->Mode->Info->VerticalResolution;
    b->fb_pitch = gop->Mode->Info->PixelsPerScanLine * 4;
    b->boot_type = 1;

    // Kernel entry
    void (*kentry)(struct BootInfo*) =
        ((__attribute__((ms_abi)) void(*)(struct BootInfo*))kernel);

    kentry(b);

    return EFI_SUCCESS;
}
