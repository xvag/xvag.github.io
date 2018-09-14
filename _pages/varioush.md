---
permalink: /varioush/
---

```
/* create bootable usb w/ dd */
# dd if=/path/to/.iso of=/dev/sdX bs=4M status=progress oflag=sync
# dd if=/path/to/FBSD.img of=/dev/da0 bs=1M conv=sync 

/* configure metrics */
# ip route
# ip route del default .... metric X
# ip route add default .... metric Y

/* bridged vm problem
failed to parse default acl file '/usr/local/etc/qemu/bridge.conf' */
echo "allow br0" > /etc/qemu/bridge.conf

# ps -eo pid,ppid,cmd,%cpu,%mem --sort=%cpu | head

for i in ./*; do file $i | grep -iq png; if [ $? -eq 0 ]; then echo $i; fi; done;
```
