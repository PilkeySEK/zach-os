#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/zachos.kernel isodir/boot/zachos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "zachos" {
	multiboot /boot/zachos.kernel
}
EOF
grub-mkrescue -o zachos.iso isodir
