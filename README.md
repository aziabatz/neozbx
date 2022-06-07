# NEOZBX
# A reimplementation of Zibix kernel on C++

## Requirements
> G++ 11.2.0

> Binutils 2.37

> CMake 3.10(3.18 recommended)

> Cross compiler made with G++ and Binutils

> Qemu or any other VM are recommended

> Grub

## How to build

Run `cmake .` from the project root directory to generate the Makefile
If you need to configure how the Makefile is generated, refer to CMakeLists.txt
Run `make` to build the kernel

## Booting the kernel

You can generate an iso with GRUB bootloader containing the kernel binary.
Just run: `grub-mkrescue iso/ -o kernel.iso`

The iso directory should show like this:
```
iso
└── boot
    ├── grub
    │   └── grub.cfg
    └── kernel.kim
```
The `grub.cfg` file will hold the entry to the "operating system". As we have a multiboot header in our kernel, GRUB shall recognize it. The grub.cfg content should be:
```
menuentry "ZIBIX OPERATING SYSTEM" {
  multiboot /boot/zibix.bin
  boot
}
```

### QEMU

With QEMU you can start the kernel two ways:

`qemu-system-i386 -kernel kernel.kim`
or
`qemu-system-i386 kernel.iso`

### VirtualBox

Just make the .iso and pass it to the VM.