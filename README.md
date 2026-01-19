# MLFQ Scheduler for xv6-riscv

This project implements a **Multi-Level Feedback Queue (MLFQ)** scheduler for the xv6-riscv operating system. It replaces the default Round-Robin scheduler with a priority-based system featuring aging mechanisms to prevent starvation and custom logic to ensure fair CPU distribution.

## Key Features

* **Multi-Level Feedback Queue (MLFQ):** Implements prioritized scheduling where processes move between queues based on CPU usage and wait time.
* **Anti-Starvation Mechanism:** Processes waiting too long in lower-priority queues are promoted to higher priorities.
* **Custom Round-Robin Fairness:** Improved intra-queue scheduling using a state-tracking array to prevent lower-index processes from monopolizing the CPU.
* **System Monitoring:** Implementation of a new syscall and a user-level `ps` command to inspect process states and priority metrics.

## Implementation Details

### 1. Process Structure Modifications (`struct proc`)
The process control block was extended to support MLFQ metrics:
* `priority`: Current priority queue index.
* `cticks`: Ticks consumed in the current queue (time slice tracking).
* `wticks`: Ticks spent waiting (used for aging/starvation prevention).
* `mticks`: Maximum allowed ticks for the current priority level.

### 2. System Calls & Utilities
* **`sys_getpinfo`**: A new system call that iterates over active processes and exports their internal state (priority, accumulated ticks) to user space.
* **`ps` Command**: A user-level program that utilizes `sys_getpinfo` to display a snapshot of all running processes and their scheduling attributes.

### 3. Trap & Interrupt Handling
modifications in `trap.c` (`usertrap` / `kerneltrap`) ensure accurate time tracking:
* **Time Slices:** On timer interrupts, the running process's `cticks` are incremented. If the max quantum is reached, the process yields the CPU.
* **Aging:** `wticks` are incremented for all `RUNNABLE` processes. If a threshold is crossed, the process is promoted to a higher priority queue to prevent starvation.

### 4. Scheduler Logic (`proc.c`)
The `scheduler()` function utilizes nested loops to iterate through priority queues and processes:
* **Fair Round-Robin:** To address standard RR limitations where processes at lower array indices might dominate CPU time after priority resets, a tracking array was implemented. This array remembers the last executed index for each priority level, ensuring the scheduler picks up where it left off (True Round-Robin).
* **Priority Reset:** When a process yields or completes its quantum, the scheduler re-evaluates priorities starting from the highest level.

## Usage

### Compiling and Running
To build the kernel with the MLFQ scheduler:

```bash
sudo apt-get update
sudo apt-get install git build-essential gdb-multiarch qemu-system-misc gcc-riscv64-linux-gnu binutils-riscv64-linux-gnu
make qemu