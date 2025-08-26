#!/bin/sh
set -e
. ./clean.sh
set -e
. ./iso.sh

qemu-system-$(./target-triplet-to-arch.sh $HOST) -cdrom zachos.iso -m 1024M
