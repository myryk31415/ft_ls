# ft_ls
This project is a partial rewrite of the `ls` command.

### Flags

The flags ft_ls is able to handle, entries marked with `!` are mandatory.

* !-a: do not ignore entries starting with .
* -d: list directories themselves, not their contents
* -f: do not sort, enable -aU, disable -ls --color
* -g: like -l, but do not list owner
* !-l: use a long listing format
* !-r: reverse order while sorting
* !-R: list subdirectories recursively
* !-t: sort by time, newest first
* -u: with -lt: sort by, and show, access time; with -l: show access time and sort by name; otherwise: sort by access time, newest first
