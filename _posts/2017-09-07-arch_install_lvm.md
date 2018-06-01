---
layout: post
title: Installing Arch Linux on LVM
tags: [arch, linux, lvm]
---
<div>
Hardware: Intel i5-6500, 16G RAM, 1x60G SSD, 2x500G HDD<br/>
OS: Arch Linux 2017.07.01 – kernel: 4.11.7
sda = 60Gb ssd (/, /boot)
sdb,sdc = 500Gb hdd each (/home, /tmp)
</div>

edit:
(uefi tips)
if windows were previously installed on the disk, clean mbr with dd:
eg `# dd if=/dev/zero of=/dev/sda bs=512 count=1` !clean partition table too
or # dd if=/dev/zero of=/dev/sda bs=446 count=1 !keep partition table
!also boot the live usb/cd on uefi mode - it should be in boot menu!

/*network configuration*/
# ip link set dev wlan0 up
# wpa_supplicant -B -i wlan0 -c <(wpa_passphrase “SSID” “passphrase“)
# dhcpcd wlan0

/*gdisk-ing, lvm-ing, formatting and mounting*/
sda1 = 1G EFI System (ef)
sda2 = 54.9G Linux fs (83)
sdb1 = 465G Linux LVM (8e)
sdc1 = 465G Linux LVM (8e)

# mkfs.fat -F32 /dev/sda1
# mkfs.xfs /dev/sda2

# pvcreate /dev/sdb1
# pvcreate /dev/sdc1
# vgcreate VG01 /dev/sdb1 /dev/sdc1
# lvcreate -L 100G VG01 -n lvtmp
# lvcreate -l 100%FREE VG01 -n lvhome
# mkfs.xfs /dev/mapper/VG01-lvtmp
# mkfs.xfs /dev/mapper/VG01-lvhome

# mount /dev/sda2 /mnt
# mkdir /mnt/boot/
# mount /dev/sda1 /mnt/boot/
# mkdir /mnt/home/
# mount /dev/mapper/VG01-lvhome /mnt/home/
# mkdir /mnt/tmp/
# mount /dev/mapper/VG01-lvtmp /mnt/tmp/

/*installing the base system*/
# pacstrap /mnt base
# genfstab -U /mnt >> /mnt/etc/fstab
# arch-chroot /mnt

/*inside the new system*/
# ln -sf /usr/share/zoneinfo/Region/City /etc/localtime
# hwclock –systohc
# vi /etc/locale.gen
uncomment: en_US.UTF-8 and the rest
# locale-gen
# echo “LANG=en_US.UTF-8” > /etc/locale.conf
# echo “myhostname” > /etc/hostname
# vi /etc/hosts
append: 127.0.1.1 myhostname.localdomain myhostname

/*create a 8G swap file*/
# dd if=/dev/zero of=/swapfile bs=1M count=8192
# chmod 600 /swapfile
# mkswap /swapfile
# swapon /swapfile
# vi /etc/fstab
append: /swapfile none swap defaults 0 0
# mkinitcpio -p linux
# passwd

/*install grub*/
# pacman -S grub efibootmgr intel-ucode
# grub-install --target=x86_64-efi --efi-directory=/boot --bootloader-id=grub
# grub-mkconfig -o /boot/grub/grub.cfg

# exit /*from chroot*/
# umount -R /mnt
# reboot /*into the new system*/

/*some post-configuration*/

/*configure wireless network to start on boot*/
# vi /etc/netctl/profilename !examples can be found at /etc/netctl/examples/
edit:
Description='A simple WPA encrypted wireless connection using 256-bit PSK'
Interface=wlp2s2
Connection=wireless
Security=wpa
IP=dhcp
ESSID=your_essid
Key=your_key
# netctl start profilename !troubleshoot with #journalctl -xn or #netctl status profilename
# netctl enable profilename

/*create basic user*/
# useradd -m username
# passwd username
# pacman -S sudo
# visudo
append: username ALL=(ALL) ALL

/*login as user username*/

/*install basic gui*/
$ sudo pacman -S xorg xorg-xinit xterm i3
$ vi ~/.xinitrc
edit: exec i3
$ startx

/*install tools/software etc*/
$ sudo pacman -S iw wpa_supplicant dialog !for wifi
$ sudo pacman -S base-devel !to install from AUR
$ sudo pacman -S ntfs-3g !for r/w on ntfs
$ sudo pacman -S pulseaudio pavucontrol !for audio

$ sudo pacman -Syy && pacman -Syu !update
