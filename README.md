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

# Week 3: Concurrency and Mutexes

POSIX threads, race conditions and `pthread_mutex_t` on Linux.

**Reading:** TLPI Ch. 29, 30, 31 (threads, synchronization, thread safety); LKD Ch. 9, 10 (kernel synchronization).

## Tasks

| Task | Program | What it does |
|---|---|---|
| TASK-05 Concurrency & Races | `task5a.c` | `NTHREADS` threads each do `counter++` `NITER` times with **no lock** and expose lost updates |
| TASK-06 Mutex Synchronization | `task6a.c` | Same counter protected with `pthread_mutex_lock` / `unlock`; result is exact |
| TASK-06 Error checking | `task6b.c` | Mutex created with `PTHREAD_MUTEX_ERRORCHECK`; deliberate misuse (double lock, bad unlock) returns error codes |

## Build and run

```
gcc -O0 -pthread -o task5a task5a.c
gcc -O0 -pthread -o task6a task6a.c
gcc -O0 -pthread -o task6b task6b.c
./task5a
time ./task6a
```

`-O0` keeps the compiler from changing the loop; `-pthread` links the thread library.

## 1. Race condition (TASK-05)

`counter++` is three steps (load, add, store). When two threads interleave between the load and the store, one increment is lost.

- Expected result: `NTHREADS * NITER`
- Observed: a lower value that changes on every run
- With a very small `NITER` the threads do not overlap and the race stays hidden, so the load must be high

## 2. Mutex (TASK-06)

Locking only the critical region (`counter++`) makes the result exact on every run.

Example run (5 threads x 100000, mutex): counter = 500000, real = 0.039 s, `perf stat`: 14,810 context-switches, 0 cpu-migrations.

## 3. Error-checking mutex

With `PTHREAD_MUTEX_ERRORCHECK`:

| Misuse | Return value |
|---|---|
| Lock twice in the same thread | `EDEADLK` (35) |
| Unlock a mutex that is not locked | `EPERM` (1) |
| Unlock from a thread that does not own it | `EPERM` (1) |

With the default type, locking twice would hang forever (self-deadlock).

## 4. Benchmark: throughput under contention

Throughput = `(NTHREADS * NITER) / real` (`NITER` the same in every row).

| Threads | Mutex real (s) | Mutex ops/s | No-lock real (s) | No-lock ops/s |
|---|---|---|---|---|
| 1 | | | | |
| 2 | | | | |
| 4 | | | | |
| 8 | | | | |

Machine: `nproc` = ____ cores.

Observations to confirm with your numbers:
- No-lock is faster but gives a wrong counter
- Mutex throughput stays flat or drops as threads are added (one thread at a time in the critical region)
- Mutex run shows large `sys` time and many context switches: contended `pthread_mutex_lock` takes the slow path (`futex` WAIT/WAKE), which costs far more than `counter++`

## 5. Tools used

| Tool | Command | Result |
|---|---|---|
| `time` | `time ./task6a` | `real` / `user` / `sys` |
| `perf stat` | `sudo perf stat -e context-switches,cpu-migrations,page-faults ./task6a` | context switches show lock contention |
| Helgrind | `valgrind --tool=helgrind ./task5a` | reports a data race on `counter`; 0 errors for the mutex version |
| ThreadSanitizer | `gcc -g -fsanitize=thread -pthread ...` | reports the exact line of the race |

## What I learned

- A thread is a `task_struct` that shares the process's `mm_struct` (`clone` with `CLONE_VM` etc.); `pthread_create` allocates a stack with `mmap` and calls `clone3`
- A mutex fixes the race but costs time under contention
- A single run is not a benchmark: repeat, and keep the work per thread the same in every version compared


