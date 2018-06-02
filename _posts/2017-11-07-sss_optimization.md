---
layout: post
title: SSD optimization with TRIM
tags: [linux, ssd, trim]
---

A trim command (known as TRIM in the ATA command set, and UNMAP in the SCSI command set)<br>
allows an operating system to inform a solid-state drive (SSD) which blocks of data <br>
are no longer considered in use and can be wiped internally.

Trim was introduced soon after SSDs were introduced. Because low-level operation of SSDs differs significantly from hard drives, the typical way in which operating systems handle operations like deletes and formats resulted in unanticipated progressive performance degradation of write operations on SSDs. Trimming enables the SSD to more efficiently handle garbage collection, which would otherwise slow future write operations to the involved blocks.<br>
src: https://en.wikipedia.org/wiki/Trim_(computing)

- verify TRIM support<br>
`# lsblk -D `<br>
check the values of DISC-GRAN and DISC-MAX columns. Non-zero values indicate TRIM support<br>
or<br>
`# hdparm -I /dev/sda | grep TRIM`<br>
look for: Data Set Management TRIM supported (limit 1 block)

- enable periodic TRIM
```
# pacman -S util-linux 
!provides fstrim.service and fstrim.timer systemd unit files
# fstrim /mountpoint 
!manual activation
# systemctl enable fstrim.timer 
!activates the service weekly, on all mounted filesystems on devices that support the discard operation
```
The timer relies on the timestamp of /var/lib/systemd/timers/stamp-fstrim.timer (which it will create upon first invocation) to know whether a week has elapsed since it last ran.

sources:<br>
https://wiki.archlinux.org/index.php/Solid_State_Drives<br>
http://xfs.org/index.php/FITRIM/discard<br>
