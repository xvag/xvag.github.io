```
fdisk
gdisk
cfdisk
parted
gparted

# blkid /dev/sdX

# fsck [options] /dev/sdXy (after umount)

# ls /sbin/mk*
# mkfs -t [filesystem] -L [label] device

mkswap /dev/sdX1
swapon -v /dev/sdX1
swapoff /dev/sdX1
echo '/dev/sdX1 swap swap sw 0 0' >> /etc/fstab
cat /proc/swaps

mount -t type device dir -o options

# yum install samba-client samba-common cifs-utils
# smbclient -L 192.168.0.10
# mkdir /media/samba
# vi /media/samba/.smbcredentials
1	username=samba_username
2	password=samba_password
# chmod 600 /media/samba/.smbcredentials
# vi /etc/fstab
	//192.168.0.10/sharename /media/samba cifs credentials=/media/samba/.smbcredentilas,defaults 0 0
# mount -a

# yum install nfs-utils nfs-utils-lib
# mkdir /media/nfs
# vi /etc/fstab
	192.168.0.10/NFS-SHARE /media/nfs nfs defaults 0 0
# mount -a

/etc/fstab syntax:
<file system> <mount point> <type> <options> <dump> <pass>

*RAID*
# yum install mdadm
# cat /proc/mdstat
# mdadm --detail /dev/md0
# mkfs ... /dev/md0
# mdadm --detail --scan
# mdadm --assemble --scan
# systemctl start/enable mdmonitor
# mdadm /dev/md0 --add /dev/sdX1

# mdadm --stop /dev/md0
# mdadm --remove /dev/md0
# mdadm --zero-superblock /dev/sdX1

# echo 'MAILADDR root' >> /etc/mdadm.conf (mail alerts)

# mdadm --create --verbose /dev/md0 \
 --level=stripe --raid-devices=2 /dev/sdb1 /dev/sdc1 (real-time apps for performance)
 --level=1 --raid-devices=2 /dev/sdb1 /dev/sdc1 (OS, important dirs eg. home)
 --level=5 --raid-devices=3 /dev/sd[b-d]1 --spare-devices=1 /dev/sde1 (web/file servers)
 --level=6 --raid-devices=4 /dev/sd[b-e]1 --spare-devices=1 /dev/sdf1 (file/backup servers w/ large capacity & high availability)
 --level=10 --raid-devices=4 /dev/sd[b-e]1 --spare-devices=1 /dev/sdf1 (DB/App servers for fast I/O ops)


*BackUp*
with dd:
# dd if=/dev/sda of=/system_images/sda.img
# dd if=/dev/sda | gzip -c > /system_images/sda.img.gz

# dd if=/system_images/sda.img of=/dev/sda
# gzip -dc /system_images/sda.img.gz | dd of=/dev/sda

with tar:
see tar

with rsync:
# rsync -av --progress src_dir dest_dir
over ssh:
# rsync -avzhe ssh backups/ root@remote_host:/remote_dir/
# rsync -av --include '*.conf' --exclude '*' src_dir dest_dir
 --delete (del all files that are not in src_dir)
 --max-size='200k'
 --remove-source-files
 --dry-run (no changes - test)
 --bwlimit=100 (bandwidth limit)
 -W (sync whole file - not only changes)

*LVM*
# pvcreate /dev/sd[b-d]
# pvs (list created PVs)
# pvdisplay /dev/sdX
# vgcreate vg00 /dev/sdb /dev/sdc
# vgdisplay vg00
# lvcreate -n vol_projects -L 10G vg00
# lvcreate -n vol_backups -l 100%FREE vg00
# lvs
# lvdisplay vg00/vol_projects
# mkfs .. /dev/vg00/vol_projects

# lvreduce -L -2.5G -r /dev/vg00/vol_projects
# lvextend -l +100%FREE -r /dev/vg00/vol_backups

# vgextend vg00 /dev/sdd
```
