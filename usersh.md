---
layout: page
permalink: /usersh/
---

```
--- User managment ---

# adduser [username]
# useradd [username]
(creates: 
- /home/username/{.bash_logout/.bash_profile/.bashrc}
- /var/spool/mail/username
- new entry in /etc/group:
  [Group name]:[Group password]:[GID]:[Group members]
- new entry in /etc/passwd:
  [username]:[x]:[UID]:[GID]:[Comment]:[Home directory]:[Default shell]

# usermod [options] [username]
eg.
# usermod --expiredate 2018-10-30 [username]
# usermod --append --groups (or -aG) [group],[group],.. [username]
# usermod --home (or -d) /dir/to/new/home [username]
# usermod --shell /bin/sh [username]
# usermod --lock/--unlock (or -L/-u) [username]

# groups [username]
# id [username]
# groupdel [groupname]
# userdel --remove [username]

- setuid -
When the setuid permission is applied to an executable file, 
a user running the program inherits the effective privileges of the program's owner.
# chmod u[+/-]s [file]
# chmod 4xxx [file] 

- setgid -
When the setgid bit is set, 
the effective GID of the real user becomes that of the group owner. 
# chmod g[+/-]s [file]
# chmod 2xxx [file]

- sticky bit -
When the "sticky bit" is set on files, Linux just ignores it, 
whereas for directories it has the effect of preventing users 
from deleting or even renaming the files it contains 
unless the user owns the directory, the file, or is root.
# chmod o[+/-]t [dir]
# chmod 1xxx [dir]

- special file attributes -
# chattr [options] [file]
# lsattr [file]

- root and sudo -
# su
# su -

# visudo (edits /etc/sudoers)
- directories that will be used for sudo:
Defaults    secure_path="/usr/sbin:/usr/bin:/sbin"
- 1st ALL=hosts, 2nd ALL=priviledges of any user, 3rd ALL=any command
root ALL=(ALL) ALL
- If no user is specified after the = sign, sudo assumes the root user. 
[username] ALL=/bin/yum update
- The NOPASSWD allows user to run [command] without entering his password.
[username]    ALL=NOPASSWD:/bin/updatedb
- The % sign indicates group.
%admin      ALL=(ALL) ALL


-- ACL --
filesystem should be mounted with acl option. 
xfs supports acl out of the box.
check compatibility:
# tune2fs -l /dev/sda1 | grep "Default mount options:"

two types of ACL:
- access ACL: applied to file or dir.
- default (optional) ACL: applied only to dir.
Inside a dir with default ACL, all files/dirs without ACL inherit 
the default ACL of the parent dir.

check ACL settings:
# getfacl [file/dir]

set ACL:
- access ACL:
# setfacl -m u:[username]:rw [file/dir] 
- default ACL:
# setfacl -m d:o:r [dir]
- to remove replace -m with -x.
# setfacl -x d:o [dir]
- to remove all ACL in one step:
# setfacl -b [file/dir]


-- Disk Quotas --
- enable quotas on a file system: 
mount it with the usrquota or grpquota (user or group quotas) options in /etc/fstab.
- initialize and enable quotas:
# quotacheck -avugc
# quotaon -vu [mountpoint-dir]
# quotaon -vg [mountpoint-dir]
- edit quotas:
# edquota -u [username]
# edquota -g [group]
# edquota -t (for grace period)
- check quotas:
# quota -u/-g [username/group]
# repquota -v [path/to/filesystem]



-- PAM --
Pluggable Authentication Modules (PAM) offer the flexibility of setting a specific 
authentication scheme on a per-application and/or per-service basis using modules.
Files inside /etc/pam.d indicate which applications are using PAM natively.
syntax:
type control module-path module-arguments
eg. # cat /etc/pam.d/passwd
 #%PAM-1.0
 auth   	include 	system-auth
 account	include 	system-auth
 password	substack	system-auth
 -password	optional	pam_gnome_keyring.so use_authtok
 password	substack	postlogin

1st col is the type of authentication to be used with module-path (3rd col).
When a hyphen appears before the type, 
PAM will not record to the system log if the module cannot be loaded 
because it could not be found in the system.
types available:
- account: this module type checks if the user or service 
has supplied valid credentials to authenticate.
- auth: this module type verifies that the user is 
who he / she claims to be and grants any needed privileges.
- password: this module type allows the user or service 
to update their password.
- session: this module type indicates what should be done 
before and/or after the authentication succeeds.

2nd col (control) indicates what should happen if the authentication fails:
- requisite: overall authentication will be denied immediately.
- required: similar to requisite, although all other listed modules for this service 
will be called before denying authentication.
- sufficient: PAM will still grant authentication even if a previous marked as required failed.
- optional: if the authentication via this module fails or succeeds, nothing happens 
unless this is the only module of its type defined for this service.
- include: means that the lines of the given type should be read from another file.
- substack: similar to includes but authentication failures or successes 
do not cause the exit of the complete module, but only of the substack.

4th col, if it exists, shows the arguments to be passed to the module.


-- SELinux --
two modes:
- Enforcing: SELinux denies access based on SELinux policy rules.
- Permissive: SELinux does not deny access, but denials are logged 
  for actions that would have been denied if running in enforcing mode.

config file: /etc/selinux/config
# getenforce
# setenforce [0/1]

install policycoreutils-python for:
# semanage
# restorecon
etc?
```
