---
layout: post
title: Intro to libvirt
tags: [virtualization, libvirt]
---

Host: Arch Linux 4.15

install server<br>
`# pacman -S libvirt`

for the default NAT/DHCP networking<br>
`# pacman -S ebtables dnsmasq`

for bridged networking<br>
`# pacman -S bridge-utils`

for remote management over ssh<br>
`# pacman -S openbsd-netcat`

install client<br>
`# pacman -S virt-manager virt-viewer`

set up authentication - using polkit:<br>
The libvirt daemon provides two polkit actions in /usr/share/polkit-1/actions/org.libvirt.unix.policy:<br>
	org.libvirt.unix.manage for full management access (RW daemon socket), and<br>
	org.libvirt.unix.monitor for monitoring only access (read-only socket).<br>

The default policy for the RW daemon socket will require to authenticate as an admin.<br> 
This is akin to sudo auth, but does not require that the client application ultimately run as root.<br>
Default policy will still allow any application to connect to the RO socket.<br>

Arch defaults to consider anybody in the wheel group as an administrator:<br>
this is defined in /etc/polkit-1/rules.d/50-default.rules <br>
Therefore there is no need to create a new group and rule file if your user is a member of the wheel group:<br>
upon connection to the RW socket (e.g. via virt-manager) you will be prompted for your user's password.<br>

starting the daemons<br>
`# systemctl start libvirtd.service`<br>
`# systemctl start virtlogd.service`

Optionally enable libvirtd.service.<br>
There is no need to enable virtlogd.service, since libvirtd.service, when enabled, also enables the virtlogd.socket and virtlockd.socket units.

To test if libvirt is working properly on a system level:<br>
`$ virsh -c qemu:///system`

To test if libvirt is working properly for a user-session:<br>
`$ virsh -c qemu:///session`

### Management

#### print active and inactive storage pools
`$ virsh pool-list --all`

#### create a new pool using virsh

- define a directory<br>
`$ virsh pool-define-as poolname dir - - - - /home/username/.local/libvirt/images`

- define a LVM volume <br>
`$ virsh pool-define-as poolname fs - -  /dev/vg0/images - mntpoint`

Tip: For LVM storage pools:<br>
It is a good practice to dedicate a volume group to the storage pool only.
Choose a LVM volume group that differs from the pool name, 
otherwise when the storage pool is deleted the LVM group will be too.

The above command defines the information for the pool
- to build it
```
$ virsh pool-build     poolname
$ virsh pool-start     poolname
$ virsh pool-autostart poolname
```

- to remove it<br>
`$ virsh pool-undefine  poolname`


#### manage volumes
```
$ virsh vol-create-as      poolname volumename 10GiB --format aw|bochs|raw|qcow|qcow2|vmdk
$ virsh vol-upload  --pool poolname volumename volumepath
$ virsh vol-list           poolname
$ virsh vol-resize  --pool poolname volumename 12GiB
$ virsh vol-delete  --pool poolname volumename
$ virsh vol-dumpxml --pool poolname volumename  # for details.
```

#### manage domains
`# virsh list --all`

- create new domain - examples
```
Arch Linux install (two GiB, qcow2 format volume create; user-networking):
$ virt-install  \
  --name arch-linux_testing \
  --memory 1024             \ 
  --vcpus=2,maxvcpus=4      \
  --cpu host                \
  --cdrom $HOME/Downloads/arch-linux_install.iso \
  --disk size=2,format=qcow2  \
  --network user            \
  --virt-type kvm
```
```
Fedora testing (Xen hypervisor, non-default pool, do not originally view):
$ virt-install  \
  --connect xen:///     \
  --name fedora-testing \
  --memory 2048         \
  --vcpus=2             \
  --cpu=host            \
  --cdrom /tmp/fedora20_x84-64.iso      \
  --os-type=linux --os-variant=fedora20 \
  --disk pool=testing,size=4            \
  --network bridge=br0                  \
  --graphics=vnc                        \
  --noautoconsole
$ virt-viewer --connect xen:/// fedora-testing
```
```
Windows:
$ virt-install \
  --name=windows7           \
  --memory 2048             \
  --cdrom /dev/sr0          \
  --os-variant=win7         \
  --disk /mnt/storage/domains/windows7.qcow2,size=20GiB \
  --network network=vm-net  \
  --graphics spice
```

- import existing volume
```
$ virt-install  \
  --name demo  \
  --memory 512 \
  --disk /home/user/VMs/mydisk.img \
  --import
```

- delete/remove domain
`$ virsh undefine domain`

- start domain
```
$ virsh start domain
$ virt-viewer --connect qemu:///session domain
```

- shutdown/force off domain
```
$ virsh shutdown domain
$ virsh destroy  domain
```

- autostart domain on libvirtd start
```
$ virsh autostart domain
$ virsh autostart domain --disable
```

- shutdown domain on host shutdown<br>
Running domains can be automatically suspended/shutdown at host shutdown 
using the libvirt-guests.service systemd service. 
This same service will resume/startup the suspended/shutdown domain 
automatically at host startup. 
Read /etc/conf.d/libvirt-guests for service options.

- edit a domain's XML configuration<br>
`$ virsh edit domain`

