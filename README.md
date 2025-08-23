# Zach OS
The directory and file structure as well as the linker and .sh files are mostly based on the [Meaty Skeleton](https://wiki.osdev.org/Meaty_Skeleton) in the OSDev Wiki.

## Developing
1. Install a [Cross-Compiler](https://wiki.osdev.org/GCC_Cross-Compiler) (this project uses i686-elf-gcc).
2. Clone the repo into some directory.
3. You may need to install GNU Make and/or QEMU, if you haven't already.

Scripts:
```sh
qemu.sh     # build everything and emulate the resulting .iso in QEMU
build.sh    # create a .iso
clean.sh    # delete all build files created by build.sh
format.sh   # run clang-format for all .h and .c files
```
...and more (don't ask what exactly they do because i'm too lazy to check)

## Features
None yet (contribute!)

## Roadmap
- lets see where it goes