---
layout: page
permalink: /shystem/
---

`# top -hv|-bcEHiOSs1 -d secs -n max -u|U user -p pid -o fld -w [cols]`<br>
`# free`<br>
`# ps`<br>
`/var/log`<br>

- report file system disk space usage:<br>
`# df [OPTION]... [FILE]...`

- estimate file space usage:<br>
`# du [OPTION]... [FILE]...`

--- GRUB ---
```
GRUB config file (Centos):
/etc/default/grub
/etc/grub.d/
# grub2-mkconfig -o /boot/grub2/grub.cfg (after editing config files)

list entries:
# awk -F\' '$1=="menuentry " {print $2}' /boot/grub2/grub.cfg
```

--- kernel runtime parameters ---
```
# sysctl
# sysctl -a (list)
the name of a parameter matches the directory structure inside /proc/sys where it can be found.
eg. 
dev.cdrom.autoclose -> /proc/sys/dev/cdrom/autoclose
net.ipv4.ip_forward -> /proc/sys/net/ipv4/ip_forward
so:
# sysctl dev.cdrom.autoclose
 dev.cdrom.autoclose = 1
# cat /proc/sys/dev/cdrom/autoclose
 1
# sysctl net.ipv4.ip_forward
 net.ipv4.ip_forward = 1
# cat /proc/sys/net/ipv4/ip_forward
 1

to modify for current session:
# echo 0 > /proc/sys/net/ipv4/ip_forward
or:
# sysctl -w net.ipv4.ip_forward=0

to modify permanently:
edit /etc/sysctl.conf with
net.ipv4.ip_forward=0
-or-
set .conf files inside /etc/sysctl.d:
edit /etc/sysctl.d/net.conf with
net.ipv4.ip_forward=0
net.ipv4.icmp_echo_ignore_all=1

and then:
# sysctl -p
```

--- Services ---
```
# systemctl {status/start/stop/restart/enable/disable/is-enabled} [service]
# systemctl {reboot/shutdown}
```

--- Resources ---
```
# mpstat -P ALL -u 2 3 (processor monitoring tool from sysstat package)
# ps -eo pid,ppid,cmd,%cpu,%mem --sort=-%cpu (monitor processes)
/proc/PID/ = info about the process

# vim /etc/security/limits.conf (set resource limits)
 * hard nproc 10 (max limit for everyone to 10 processes)
(* could be <user> or <group>)

# renice [-n] <new_priority> <UID, GID, PGID, or empty> identifier
(low value = high priority)
(range = -20 to 19)

# kill [options] PID (kill a process)

# pkill [options] identifier (kill many processes)
eg.
 # pkill -G 1000 (kill all with GID=1000)
 # pkill -P 4993 (kill all with PPID=4993)

# pgrep -l -u <username> (test before pkill)
```

--- Package Management ---
```
# rpm -i package.rmp (install from compiled file)
# rpm -U file.rpm (upgrade)
# rpm -qa (list installed packages)
# rpm -q package_name
# rpm -qf file_name (find which package installed a file)

# yum search package_name
# yum search all package_name
# yum whatprovides "*/package_name"
# yum update && yum install package_name
# yum erase package_name
# yum info package_name
```

