# Linux Systems Programming

Programs I wrote while learning Linux systems programming in C.

## WEEK-1

# Task1.c:
Process tree generator
Reads /proc/[pid]/status for every running process, takes Name, Pid and
PPid, and prints the parent-child tree starting from PID 1.

# Task2_b.c
fork, PPID and waitpid
Parent creates 3 children with fork(). Each child prints its PID and PPID
(the parent's PID) and exits. The parent reaps all children with
waitpid() in a while loop, so no zombies are left.

# Task2_c.c
execve without fork
Replaces the running process with /bin/ls using execve(). The PID stays
the same and the code after execve never runs unless it fails.


# Task3_d.c
SIGCHLD handler with waitpid
A SIGCHLD handler calls
waitpid(-1, NULL, 0) , so every finished child is reaped and no zombies are left.

# Task4_d.c
orphan process demo
The parent exits while the child is still running. The child is adopted
by init/systemd, so its PPid changes (checked with ps and /proc/[pid]/status).

# Task5.c
raw syscall file copier
Copies a file using only open(), read(), write() and close().
Checks every return value and uses perror() for errors.
Compile and run:
./a.out src des bufsize

### How I verified the programs
- strace -f -e trace=process,open,read,write: checked the system calls
- valgrind --trace-children=yes: checked for memory leaks and errors
- cmp: confirmed the copied file is identical
- /proc/[pid]/status and cmdline: inspected running processes


