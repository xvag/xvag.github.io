---
layout: post
title: VM networking with VDE
tags: [linux, virtualization, networking, vde]
---

Host: Arch Linux 4.12.13<br>
Hypervisor: KVM/Qemu<br>
```
# pacman -S vde2

# modprobe tun

# ip link add br0 type bridge
# ip link set br0 up`

# ip link set eth0 up
# ip link set eth0 master br0

# bridge link

# dhcpcd br0
and/or
# systemctl restart dhcpcd
(br0 should obtain an ip address)

# vde_tunctl -u <user> -t tap0
# ip link set tap0 up
# ip link set tap0 master br0
# brctl setfd br0 0

$ vde_switch -d -s /tmp/vde0 -M /tmp/vde0mgmt
$ vde_plug2tap -d -s /tmp/vde0 tap0
```

- start each vm with different MAC address
`$ qemu-system-x86_64 ... -net nic,macaddr=52:54:xx:xx:xx:xx -net vde,sock=/tmp/vde0`

```
 --------*{physical NIC}----------------------------------------
|        |							|
|	 |							|
|  ------|--------------------------------------		|
| |      |				        |		|
| |      |				        |		|
| |      *{br0}				        |		|
| |     / \				        |		|
| |    *   \				        |		|
| | {eth0}  * {tap0}         		        |		|
| |          \                                  |		|
| |           \                                 |		|
| |         ___\{tun0}_____                     |		|
| |         | O 0 O 0 0 O | {vde0}              |		|
| |         |______/___\__|                     |		|
| |               /     \                       |		|
| |              /       \                      |		|
| |          ___*{eth0}  *{eth0}_____           |		|
| |         |          |  |          |          |		|
| |         |qemuGuest1|  |qemuGuest2|          |		|
| |         |__________|  |__________|  Host OS |		|
|  ---------------------------------------------  Host Hardware |
 ---------------------------------------------------------------
```

sources:<br>
https://selamatpagicikgu.wordpress.com/2011/06/08/quickhowto-qemu-networking-using-vde-tuntap-and-bridge/<br>
https://werewblog.wordpress.com/2015/12/31/create-a-virtual-network-with-qemukvm/<br>
https://mohan43u.wordpress.com/2012/08/07/virtual-home-network/<br>
https://wiki.archlinux.org/index.php/QEMU#Networking_with_VDE2<br>
https://wiki.archlinux.org/index.php/Network_bridge<br>
http://wiki.virtualsquare.org/<br>

