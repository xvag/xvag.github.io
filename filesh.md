---
layout: page
permalink: /filesh/
---

awk<br>
```
# awk '/pattern/ { actions }' filename
# awk '//{print}'/etc/hosts
# awk '/localhost/{print}' /etc/hosts 
# awk '/l*c/{print}' /etc/hosts
# awk '/[al1]/{print}' /etc/hosts
# awk '/^ff/{print}' /etc/hosts
# awk '//{print $1, $2, $3; }' filename
# awk '//{printf "%-10s %s\n",$2, $3 }' filename
# awk '/ *\$[2-9]\.[0-9][0-9] */ { print $0 "*" ; } / *\$[0-1]\.[0-9][0-9] */ { print ; }' filename
# awk '$3 <= 20 { printf "%s\t%s\n", $0,"TRUE" ; } $3 > 20  { print $0 ;} ' filename
# awk '($3 ~ /^\$[2-9][0-9]*\.[0-9][0-9]$/) && ($4=="Tech") { printf "%s\t%s\n",$0,"*"; } ' filename
# awk '$4 <= 20 { printf "%s\t%s\n", $0,"*" ; next; } $4 > 20 { print $0 ;} ' filename
# dir -l | awk '{print $3, $4, $9;}'
# uname -a | awk '{hostname=$2 ; print hostname ; }'
# cat /etc/passwd | awk -v name="$username" ' $0 ~ name {print $0}'
 -v : Awk option to declare a variable

awk '
BEGIN { actions } 
/pattern/ { actions }
/pattern/ { actions }
...
END { actions } 
' filenames 

Built-in variables:
FILENAME : current input file name( do not change variable name)
FR : number of the current input line (that is input line 1, 2, 3# so on, do not change variable name)
NF : number of fields in current input line (do not change variable name)
OFS : output field separator
FS : input field separator
ORS : output record separator
RS : input record separator
NR : number of records (lines)
```

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
