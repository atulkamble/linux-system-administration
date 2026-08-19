# Linux IPC — Learning Order with Basic Definitions

**IPC (Inter-Process Communication)** is a set of mechanisms that allow Linux processes to **communicate, exchange data, send notifications, and synchronize with each other**.

For Linux/DevOps learning, study IPC in this order:

| Order | IPC Topic              | Basic Definition                                              | Example / Command      | Priority |
| ----: | ---------------------- | ------------------------------------------------------------- | ---------------------- | -------- |
|     1 | **Pipes**              | Pass output of one process as input to another process        | `ps aux \| grep nginx` | ⭐⭐⭐⭐⭐    |
|     2 | **Redirection**        | Redirect input, output, or errors between commands/files      | `>`, `>>`, `<`, `2>`   | ⭐⭐⭐⭐⭐    |
|     3 | **Signals**            | Send notifications/instructions to running processes          | `kill`, `pkill`        | ⭐⭐⭐⭐⭐    |
|     4 | **Named Pipes (FIFO)** | Pipe that allows separate/unrelated processes to communicate  | `mkfifo`               | ⭐⭐⭐⭐     |
|     5 | **Sockets**            | Allow processes to communicate locally or over a network      | `ss`, `nc`             | ⭐⭐⭐⭐⭐    |
|     6 | **Shared Memory**      | Allows multiple processes to access the same memory area      | `ipcs -m`              | ⭐⭐⭐      |
|     7 | **Message Queues**     | Allows processes to exchange messages through a managed queue | `ipcs -q`              | ⭐⭐⭐      |
|     8 | **Semaphores**         | Synchronize processes and control access to shared resources  | `ipcs -s`              | ⭐⭐⭐      |

## 1. Pipes `|`

**Definition:** A pipe sends the **standard output (stdout)** of one process to the **standard input (stdin)** of another process.

```bash
ps aux | grep nginx
```

Another example:

```bash
df -h | grep /dev
```

Concept:

```text
Command 1                 Command 2
   |                         ^
   | stdout                  | stdin
   +---------- PIPE ---------+
```

This is one of the **most important Linux concepts**.

---

## 2. Redirection

**Definition:** Redirection changes where a command gets its input from or sends its output/errors.

### Output to file

```bash
echo "Hello Linux" > file.txt
```

### Append output

```bash
echo "Hello Again" >> file.txt
```

### Redirect errors

```bash
ls /wrongpath 2> error.log
```

Important file descriptors:

| Number | Name   | Meaning         |
| -----: | ------ | --------------- |
|    `0` | stdin  | Standard Input  |
|    `1` | stdout | Standard Output |
|    `2` | stderr | Standard Error  |

---

## 3. Signals

**Definition:** A signal is a notification sent to a process to tell it to perform an action such as **stop, terminate, continue, or reload**.

Create a process:

```bash
sleep 500 &
```

Find PID:

```bash
pgrep sleep
```

Terminate:

```bash
kill -15 <PID>
```

Force kill:

```bash
kill -9 <PID>
```

Important signals:

| Signal    | Number | Purpose                  |
| --------- | -----: | ------------------------ |
| `SIGHUP`  |      1 | Hangup / commonly reload |
| `SIGINT`  |      2 | Interrupt (`Ctrl+C`)     |
| `SIGKILL` |      9 | Force kill               |
| `SIGTERM` |     15 | Graceful termination     |
| `SIGSTOP` |     19 | Pause process            |
| `SIGCONT` |     18 | Continue process         |

Prefer `SIGTERM` before `SIGKILL` when stopping a process.

---

## 4. Named Pipes — FIFO

**Definition:** A named pipe is a special file that allows processes, including **unrelated processes**, to communicate.

Create:

```bash
mkfifo mypipe
```

Terminal 1:

```bash
cat mypipe
```

Terminal 2:

```bash
echo "Hello from Terminal 2" > mypipe
```

Terminal 1 receives:

```text
Hello from Terminal 2
```

---

## 5. Sockets

**Definition:** A socket is a communication endpoint that allows processes to communicate **on the same machine or across a network**.

Very important for Linux servers, cloud, containers, and DevOps.

Check listening sockets:

```bash
ss -tulpn
```

Check port `80`:

```bash
sudo ss -tulpn | grep :80
```

Example concept:

```text
Browser
   |
   | TCP :80
   ↓
Linux Server
   |
   ↓
Nginx Process
```

---

## 6. Shared Memory

**Definition:** Shared memory allows multiple processes to access the **same area of memory**.

It is one of the fastest IPC mechanisms because processes don't have to repeatedly copy data between themselves.

View shared memory:

```bash
ipcs -m
```

Concept:

```text
Process A ──┐
            ├──> Shared Memory
Process B ──┘
```

---

## 7. Message Queues

**Definition:** A message queue allows processes to communicate by **sending and receiving messages through a queue**.

```text
Process A
   |
   | Message
   ↓
+---------+
|  Queue  |
+---------+
   |
   ↓
Process B
```

View message queues:

```bash
ipcs -q
```

---

## 8. Semaphores

**Definition:** A semaphore is a synchronization mechanism used to **control access to a shared resource**.

For example:

```text
Process A ──┐
            │
            ↓
        Semaphore
            |
            ↓
       Shared File
            ↑
            │
Process B ──┘
```

It helps prevent multiple processes from incorrectly modifying the same resource simultaneously.

View semaphores:

```bash
ipcs -s
```

---

# IPC Commands to Remember

```bash
# Pipes
ps aux | grep nginx

# Redirection
command > output.txt
command 2> error.txt

# Signals
kill -15 PID
kill -9 PID
kill -l

# FIFO
mkfifo mypipe

# Network/Unix sockets
ss -tulpn

# All System V IPC
ipcs

# Shared Memory
ipcs -m

# Message Queues
ipcs -q

# Semaphores
ipcs -s

# Remove System V IPC resource
ipcrm
```

### Best learning path

**Pipes → Redirection → Signals → FIFO → Sockets → Shared Memory → Message Queues → Semaphores**

For a **Linux/Cloud/DevOps** path, master the first five first. Then learn Shared Memory, Message Queues, and Semaphores at a conceptual/basic-practical level.
