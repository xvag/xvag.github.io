```
sed 's/term/replacement/flag' file
sed 's/term/repl/flag;s/term/repl/flag' file

du -sch /path/ | sort -h

ls /path/ | sort -h

cat file | uniq -c -w 6

cat file | cut -d: -f1 | sort | uniq

grep [OPTIONS] PATTERN [FILE...]
grep -i username /etc/passwd
ls -l /etc | grep rc[0..9]

cat file | tr [:lower:] [:upper:]
ls -l | tr -s ' '

last | grep username | tr -s ' ' | cut -d' ' -f1,3 | sort -k2 | uniq

~/.vimrc
set number
syntax on
set tabstop=4
set autoindent

:%s/old/yound/gc 
# % = entire file 
# or: n,m from n to m lines
# c =  confirmation

:buffers


tar [OPTIONS] [PATHNAME...]
-z = .tar.gz
-j = .tar.bz2
-J = .tar.xz
tvf = list contents
--delete --file files.tar file4
--update --file files.tar file4
xjf backup.tar.bz2 --directory DIR --same-permissions

find [DIR_to_search] [expression]
find . -maxdepth 3-type f -size +2M
find /home/user -perm 777 -exec rm '{}' +
-iname "*.conf"
-mtime -180 = modified time
-atime +180 = accessed time
-print

chmod [new_mode] file
chown user:group file

# shred -zvu -n 5 filetodel
# wipe -rfi dirtodel/ (for magnetic memory)
# srm -vz dirtodel/ (install secure-delete)
# sfill -v /dirtodel/ (secure-delete)
# sswap /dev/sdXy (after swapoff)
# sdmem -f -v (remove data in RAM)

# foremost -t jpg -i /dev/sdXy -o /dirtostore  (to recover rm'd things)
```
