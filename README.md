# Linux Systems Programming

Programs I wrote while learning Linux systems programming in C.

## WEEK-1

# Task1.c:
### Process tree generator
Reads /proc/[pid]/status for every running process, takes Name, Pid and
PPid, and prints the parent-child tree starting from PID 1.

# Task2.c
### fork, PPID and waitpid
Parent creates 3 children with fork(). Each child prints its PID and PPID
(the parent's PID) and exits. The parent reaps all children with
waitpid() in a while loop, so no zombies are left.

# Task3.c
### execve without fork
Replaces the running process with /bin/ls using execve(). The PID stays
the same and the code after execve never runs unless it fails.


# Task4.c
### SIGCHLD handler with waitpid
A SIGCHLD handler calls
waitpid(-1, NULL, 0) , so every finished child is reaped and no zombies are left.

# Task5.c
### orphan process demo
The parent exits while the child is still running. The child is adopted
by init/systemd, so its PPid changes (checked with ps and /proc/[pid]/status).

# Task6.c
### raw syscall file copier
Copies a file using only open(), read(), write() and close().
Checks every return value and uses perror() for errors.
Compile and run:
./a.out src des bufsize

### How I verified the programs
- strace -f -e trace=process,open,read,write: checked the system calls
- valgrind --trace-children=yes: checked for memory leaks and errors
  
- cmp: confirmed the copied file is identical
- /proc/[pid]/status and cmdline: inspected running processes

---

# WEEK-2: Linux Process Memory Management

## TASK-03: Process Memory Layout

### Task 3a – Inspect Runtime Memory Map
- Program: `task3a.c`
- Inspect process memory mappings using `/proc/self/maps`.

### Task 3b – Memory Regions and Growth
- Program: `task3b.c`
- Print virtual addresses of Data, BSS, Heap and Stack.
- Observe heap and stack growth directions.

### Task 3c – Memory Mapping Verification
- Program: `task3c.c`
- Verify memory regions using:
  - `pmap -x`
  - `/proc/<pid>/smaps`
  - `readelf -S`

## TASK-04: Heap and malloc Internals

### Task 4a – Track Program Break
- Program: `task4a.c`
- Track the program break using `sbrk(0)` before and after malloc and free operations.

### Task 4b – glibc malloc Chunk Inspection
- Program: `task4b.c`
- Inspect malloc chunk headers, chunk sizes, usable sizes and memory reuse.

### Task 4c – Memory Leak Detection
- Program: `task4c.c`
- Demonstrate memory leaks.
- Verify using Valgrind:

```bash
valgrind --leak-check=full ./task4c
```

## Tools Used

- GCC
- Linux `/proc` filesystem
- pmap
- readelf
- Valgrind
- glibc malloc




