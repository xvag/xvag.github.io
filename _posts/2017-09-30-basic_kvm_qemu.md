---
layout: post
title: Basic usage of KVM/Qemu
tags: [linux, virtualization, kvm, qemu]
---

#### check for virtualization support
`# lscpu`<br>
looking for VT-x for Intel processors and AMD-V for AMD processors<br>
or<br>
`# egrep --color=auto 'vmx|svm|0xc0f' /proc/cpuinfo`

#### check for kvm module availability
`# zgrep CONFIG_KVM /proc/config.gz`<br>
The module is only available if it is set to either y or m

#### install qemu
`# pacman -S qemu qemu-arch-extra`

#### create a hard disk image
`# qemu-img create -f raw disk_img 10G`

#### boot the vm to install the os
`# qemu-system-x86_64 --enable-kvm -m 4G -cdrom /path/to/iso -boot menu=on -drive file=disk_img,format=raw`

#### start the vm
`# qemu-system-x86_64 --enable-kvm -m 4G disk_img`
