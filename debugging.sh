#!/bin/bash

qemu-system-x86_64 -kernel minikernel -s -S &
sleep 0.5
gdb
