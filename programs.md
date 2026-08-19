Yes. Before IPC, learn a **small amount of C** first. You do **not** need advanced C programming for basic Linux IPC.

# Basic C Required for Linux IPC

Recommended order:

**C basics → functions → arrays/strings → pointers → structures → file descriptors → processes → IPC**

|  # | C Topic          | Why needed for IPC                  |
| -: | ---------------- | ----------------------------------- |
|  1 | Basic program    | Understand C structure              |
|  2 | Variables        | Store PID, file descriptors, etc.   |
|  3 | `if/else`        | Separate parent/child logic         |
|  4 | Loops            | Keep processes/servers running      |
|  5 | Functions        | Signal handlers and reusable code   |
|  6 | Arrays           | Pipe file descriptors and buffers   |
|  7 | Strings          | Send/receive text                   |
|  8 | Pointers         | Shared memory and buffers           |
|  9 | Structures       | Message queues and sockets          |
| 10 | File descriptors | `read()`, `write()`, pipes, sockets |
| 11 | `fork()`         | Create processes                    |
| 12 | IPC              | Pipes, FIFO, signals, etc.          |

## 1. Hello World

**Purpose:** Understand the basic structure of a C program.

```c
#include <stdio.h>

int main() {
    printf("Hello Linux\n");
    return 0;
}
```

Compile and run:

```bash
gcc hello.c -o hello
./hello
```

Remember:

```text
hello.c
   ↓
  gcc
   ↓
Executable
   ↓
./hello
```

---

## 2. Variables

You will frequently store PIDs and file descriptors in integer variables.

```c
#include <stdio.h>

int main() {
    int a = 10;
    int b = 20;

    printf("a = %d\n", a);
    printf("b = %d\n", b);

    return 0;
}
```

Important basic types:

```c
int age = 30;
char grade = 'A';
float price = 10.5;
```

---

## 3. If / Else

Very important with `fork()` because you need to determine whether the current process is the **parent or child**.

```c
#include <stdio.h>

int main() {
    int a = 20;

    if (a > 10) {
        printf("Greater\n");
    }
    else {
        printf("Smaller\n");
    }

    return 0;
}
```

Later you'll use the same concept:

```c
if (pid == 0) {
    // child
}
else {
    // parent
}
```

---

## 4. Loops

Processes and servers often need to continue running.

```c
#include <stdio.h>

int main() {

    for (int i = 1; i <= 5; i++) {
        printf("%d\n", i);
    }

    return 0;
}
```

Also understand:

```c
while (1) {
    // keep running
}
```

You will see this in servers and signal examples.

---

## 5. Functions

**Definition:** A function groups reusable code.

```c
#include <stdio.h>

void hello() {
    printf("Hello Linux\n");
}

int main() {

    hello();

    return 0;
}
```

This becomes important for **signal handlers**:

```c
void handler(int signal) {
    // handle signal
}
```

---

## 6. Arrays

Arrays are especially important because `pipe()` uses an integer array.

```c
#include <stdio.h>

int main() {

    int numbers[2];

    numbers[0] = 10;
    numbers[1] = 20;

    printf("%d\n", numbers[0]);
    printf("%d\n", numbers[1]);

    return 0;
}
```

Later:

```c
int fd[2];

pipe(fd);
```

Where:

```text
fd[0] = Read end
fd[1] = Write end
```

This is why arrays should be understood before pipes.

---

## 7. Strings

IPC programs commonly send text between processes.

```c
#include <stdio.h>

int main() {

    char message[] = "Hello Linux";

    printf("%s\n", message);

    return 0;
}
```

You should also know:

```c
#include <string.h>

strlen(message);
strcpy(destination, source);
```

These become useful when sending messages:

```c
write(fd, message, strlen(message));
```

---

## 8. Pointers

Pointers become important when learning **shared memory**.

Basic example:

```c
#include <stdio.h>

int main() {

    int a = 10;

    int *ptr = &a;

    printf("Value: %d\n", *ptr);

    return 0;
}
```

Understand these three things:

```text
a       = actual value
&a      = address of a
*ptr    = value stored at address
```

For example:

```c
int a = 10;
int *ptr = &a;
```

Conceptually:

```text
ptr
 |
 v
Memory Address
 |
 v
a = 10
```

Later in shared memory you'll see something like:

```c
char *data;
```

---

## 9. Structures

Structures are especially useful for **message queues and socket programming**.

```c
#include <stdio.h>

struct Student {
    int id;
    char name[20];
};

int main() {

    struct Student s;

    s.id = 101;

    printf("ID: %d\n", s.id);

    return 0;
}
```

Later a message queue may use:

```c
struct message {
    long type;
    char text[100];
};
```

---

# Now Start Linux-Specific C

Once the previous basics are clear, move into system programming.

## 10. PID

Every running process has a **Process ID (PID)**.

```c
#include <stdio.h>
#include <unistd.h>

int main() {

    printf("PID: %d\n", getpid());

    return 0;
}
```

Run:

```bash
gcc pid.c -o pid
./pid
```

You'll get something like:

```text
PID: 3245
```

---

## 11. PID and PPID

**PPID = Parent Process ID**

```c
#include <stdio.h>
#include <unistd.h>

int main() {

    printf("PID  : %d\n", getpid());
    printf("PPID : %d\n", getppid());

    return 0;
}
```

This is important before learning `fork()`.

---

## 12. `fork()`

This should be your **first important Linux process program**.

```c
#include <stdio.h>
#include <unistd.h>

int main() {

    pid_t pid;

    pid = fork();

    if (pid == 0) {
        printf("I am Child\n");
    }
    else {
        printf("I am Parent\n");
    }

    return 0;
}
```

Compile:

```bash
gcc fork.c -o fork
./fork
```

Possible output:

```text
I am Parent
I am Child
```

`fork()` creates another process:

```text
Original Process
      |
    fork()
      |
  +---+---+
  |       |
Parent   Child
```

---

# Then Start IPC

Once you understand `fork()`, your learning sequence becomes:

```text
C Basics
   ↓
PID / PPID
   ↓
fork()
   ↓
wait()
   ↓
File Descriptors
   ↓
read() / write()
   ↓
pipe()
   ↓
Signals
   ↓
FIFO
   ↓
Shared Memory
   ↓
Message Queues
   ↓
Semaphores
   ↓
Sockets
```

For **Linux administration/DevOps learning**, you don't need to become a full C developer. Focus especially on `getpid()`, `getppid()`, `fork()`, `wait()`, `open()`, `close()`, `read()`, `write()`, `pipe()` and signals. These will make Linux process management and IPC much easier to understand.

# Linux Process Programming in C

**Process programming** means using C/Linux system calls to **create, execute, control, synchronize, and terminate processes**.

For Linux learning, follow this order:

**PID/PPID → `fork()` → Parent & Child → `wait()` → `exec()` → `exit()` → Zombie → Orphan → Signals → Pipes**

|  # | Topic                   | Basic definition                           | Main function        |
| -: | ----------------------- | ------------------------------------------ | -------------------- |
|  1 | PID                     | Unique ID of a process                     | `getpid()`           |
|  2 | PPID                    | ID of the parent process                   | `getppid()`          |
|  3 | Process creation        | Create a child process                     | `fork()`             |
|  4 | Process synchronization | Parent waits for child                     | `wait()`             |
|  5 | Program execution       | Replace process with another program       | `exec()`             |
|  6 | Process termination     | End a process                              | `exit()`             |
|  7 | Zombie process          | Finished child not yet collected by parent | `wait()`             |
|  8 | Orphan process          | Child whose parent has terminated          | `getppid()`          |
|  9 | Signals                 | Send events to processes                   | `kill()`, `signal()` |
| 10 | IPC                     | Communication between processes            | `pipe()`             |

## 1. PID and PPID

**PID (Process ID)** uniquely identifies a running process.

**PPID (Parent Process ID)** identifies the process that created it.

```c id="1np26q"
#include <stdio.h>
#include <unistd.h>

int main() {

    printf("PID  = %d\n", getpid());
    printf("PPID = %d\n", getppid());

    return 0;
}
```

Compile:

```bash id="3nhwjg"
gcc process.c -o process
./process
```

Example:

```text id="9u49v4"
PID  = 3250
PPID = 2100
```

Check from Linux:

```bash id="63ikjx"
ps -ef
```

or:

```bash id="a1g76i"
ps -o pid,ppid,cmd
```

---

# 2. `fork()` — Most Important

**Definition:** `fork()` creates a new process by duplicating the calling process.

```c id="5gg3hw"
#include <stdio.h>
#include <unistd.h>

int main() {

    fork();

    printf("Hello\n");

    return 0;
}
```

Compile:

```bash id="wjq73q"
gcc fork.c -o fork
./fork
```

Output:

```text id="sjqsm6"
Hello
Hello
```

Why twice?

Before:

```text id="gy0pt5"
Process
```

After `fork()`:

```text id="gzsw0b"
       fork()
         |
    +----+----+
    |         |
 Parent     Child
    |         |
 printf     printf
```

Both processes continue executing the code after `fork()`.

---

# 3. Identify Parent and Child

`fork()` returns different values:

| Return value | Meaning                                     |
| -----------: | ------------------------------------------- |
|        `< 0` | `fork()` failed                             |
|          `0` | Running inside child                        |
|        `> 0` | Running inside parent; value is child's PID |

Example:

```c id="fwmvgw"
#include <stdio.h>
#include <unistd.h>

int main() {

    pid_t pid = fork();

    if (pid == 0) {

        printf("I am Child\n");
        printf("Child PID: %d\n", getpid());

    } else {

        printf("I am Parent\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);

    }

    return 0;
}
```

Possible output:

```text id="4mrf73"
I am Parent
Parent PID: 4000
Child PID: 4001

I am Child
Child PID: 4001
```

---

# 4. `wait()` — Parent Waits for Child

**Definition:** `wait()` makes the parent process wait until one of its child processes terminates.

Without `wait()`, parent and child execute independently.

```c id="g5qv6v"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    pid_t pid = fork();

    if (pid == 0) {

        printf("Child started\n");
        sleep(3);
        printf("Child completed\n");

    } else {

        wait(NULL);

        printf("Parent completed\n");
    }

    return 0;
}
```

Output:

```text id="zqu1t6"
Child started

Child completed
Parent completed
```

Concept:

```text id="y2wukb"
Parent
  |
fork()
  |
  +---------- Child
  |             |
wait()        work
  |             |
  |          exit
  |<------------+
  |
continue
```

---

# 5. `exec()` — Execute Another Program

**Definition:** The `exec` family replaces the current process image with a new program.

Example:

```c id="imth98"
#include <stdio.h>
#include <unistd.h>

int main() {

    printf("Before exec\n");

    execl("/bin/ls", "ls", "-l", NULL);

    printf("After exec\n");

    return 0;
}
```

Compile:

```bash id="b06ejv"
gcc exec.c -o exec
./exec
```

You'll see the output of:

```bash id="tnu9wf"
ls -l
```

Normally:

```text id="o9m8pw"
Before exec
ls output...
```

You won't see:

```text id="83bj8s"
After exec
```

because successful `exec()` **replaces the current program**.

---

# 6. `fork()` + `exec()`

This is one of the most important Unix/Linux process patterns.

```c id="ck8gxu"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    pid_t pid = fork();

    if (pid == 0) {

        printf("Child executing ls\n");

        execl("/bin/ls", "ls", "-l", NULL);

    } else {

        wait(NULL);

        printf("Parent completed\n");
    }

    return 0;
}
```

Concept:

```text id="tjjm9u"
Shell
 |
fork()
 |
 +----------------+
 |                |
Parent           Child
 |                |
wait()          exec()
 |                |
 |               ls
 |                |
 +<---------------+
 |
continue
```

This concept is fundamental to understanding how **shells launch commands**.

---

# 7. `exit()`

**Definition:** `exit()` terminates the current process and provides an exit status.

```c id="3r5n7f"
#include <stdio.h>
#include <stdlib.h>

int main() {

    printf("Program started\n");

    exit(0);

    printf("This will not execute\n");
}
```

Compile and check the status:

```bash id="3mof6g"
gcc exit.c -o exit
./exit

echo $?
```

`0` normally means **success**.

---

# 8. Zombie Process

**Definition:** A zombie is a child process that has terminated but whose parent has **not yet collected its termination status** using `wait()`/`waitpid()`.

Basic demonstration:

```c id="jvq8dj"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

    pid_t pid = fork();

    if (pid == 0) {

        printf("Child exiting\n");
        exit(0);

    } else {

        printf("Parent sleeping\n");
        sleep(30);

    }

    return 0;
}
```

While the parent sleeps, use another terminal:

```bash id="b4b2j6"
ps -el
```

You may see:

```text id="f1qt7f"
Z
```

or:

```text id="oxm1w7"
<defunct>
```

Concept:

```text id="rt0o0c"
Child terminates
      ↓
Exit status remains
      ↓
Parent hasn't called wait()
      ↓
    ZOMBIE
```

---

# 9. Orphan Process

**Definition:** An orphan is a child process whose parent terminates while the child is still running. Linux reparents it to an appropriate subreaper, commonly `systemd`/PID 1 in a simple environment.

```c id="jrzdkm"
#include <stdio.h>
#include <unistd.h>

int main() {

    pid_t pid = fork();

    if (pid == 0) {

        sleep(5);

        printf("Child PID  : %d\n", getpid());
        printf("New PPID   : %d\n", getppid());

    } else {

        printf("Parent exiting\n");
    }

    return 0;
}
```

Concept:

```text id="6s94uq"
Parent
  |
fork()
  |
Child
  |
Parent terminates
  |
Child continues
  ↓
Orphan / reparented
```

---

# 10. Signals

**Definition:** Signals allow the OS or another process to notify/control a running process.

```c id="2ruc6n"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    printf("Signal received\n");
}

int main() {

    signal(SIGINT, handler);

    printf("PID: %d\n", getpid());

    while (1) {
        sleep(1);
    }

    return 0;
}
```

Run:

```bash id="55e5ax"
gcc signal.c -o signal
./signal
```

Press:

```text id="gj8lvp"
Ctrl+C
```

The program catches `SIGINT`.

---

# 11. Pipe Between Processes

After understanding `fork()`, start IPC.

```c id="mb31l6"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {

    int fd[2];
    char buffer[100];

    pipe(fd);

    pid_t pid = fork();

    if (pid == 0) {

        close(fd[1]);

        read(fd[0], buffer, sizeof(buffer));

        printf("Child received: %s\n", buffer);

        close(fd[0]);

    } else {

        close(fd[0]);

        char message[] = "Hello Child";

        write(fd[1], message, strlen(message) + 1);

        close(fd[1]);
    }

    return 0;
}
```

Concept:

```text id="p0dbri"
Parent Process
      |
    write()
      |
      ↓
   [ PIPE ]
      |
    read()
      |
      ↓
Child Process
```

## Commands Worth Practicing Alongside C

```bash id="xby6o1"
ps
ps -ef
ps aux
pstree
pgrep nginx
pidof nginx
top
htop

jobs
bg
fg

kill PID
kill -15 PID
kill -9 PID
kill -l
```

For your Linux learning, spend the most time on **`fork()` → PID/PPID → `wait()` → `exec()` → exit status → zombie/orphan → signals → pipes**. Once these are clear, IPC programming becomes much easier.


# Linux IPC — C Programs for Practice

For C programming, I recommend learning IPC in this order:

**Pipe → Signals → FIFO → Shared Memory → Message Queue → Semaphore → Socket**

> Redirection is primarily a shell/file-descriptor concept, so it doesn't need to be treated as a separate IPC C program initially.

## 1. Pipe — Parent to Child

**Definition:** A pipe transfers data from one process to another. Usually practiced with `fork()`.

Create:

```bash
nano pipe.c
```

```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    char message[] = "Hello from Parent";
    char buffer[100];

    pipe(fd);

    pid_t pid = fork();

    if (pid > 0) {
        close(fd[0]);

        write(fd[1], message, strlen(message) + 1);

        close(fd[1]);
    }
    else {
        close(fd[1]);

        read(fd[0], buffer, sizeof(buffer));

        printf("Child received: %s\n", buffer);

        close(fd[0]);
    }

    return 0;
}
```

Compile and run:

```bash
gcc pipe.c -o pipe
./pipe
```

Output:

```text
Child received: Hello from Parent
```

Concept:

```text
Parent
  |
write()
  ↓
 PIPE
  |
read()
  ↓
Child
```

---

## 2. Signal

**Definition:** A signal sends an event/notification to a process.

Create:

```bash
nano signal.c
```

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    printf("\nSignal received: %d\n", sig);
}

int main() {
    signal(SIGINT, handler);

    printf("PID: %d\n", getpid());
    printf("Press Ctrl+C\n");

    while (1) {
        sleep(1);
    }

    return 0;
}
```

Compile:

```bash
gcc signal.c -o signal
./signal
```

Press:

```text
Ctrl+C
```

You should see:

```text
Signal received: 2
```

Here `2` represents **SIGINT**.

---

## 3. Named Pipe — FIFO

**Definition:** FIFO allows separate/unrelated processes to communicate through a special file.

This is best practiced using **two C programs**.

### Writer

```bash
nano writer.c
```

```c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    mkfifo("mypipe", 0666);

    int fd = open("mypipe", O_WRONLY);

    char message[] = "Hello from Writer";

    write(fd, message, sizeof(message));

    close(fd);

    return 0;
}
```

### Reader

```bash
nano reader.c
```

```c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char buffer[100];

    int fd = open("mypipe", O_RDONLY);

    read(fd, buffer, sizeof(buffer));

    printf("Received: %s\n", buffer);

    close(fd);

    return 0;
}
```

Compile:

```bash
gcc writer.c -o writer
gcc reader.c -o reader
```

Terminal 1:

```bash
./reader
```

Terminal 2:

```bash
./writer
```

Output:

```text
Received: Hello from Writer
```

---

## 4. Shared Memory

**Definition:** Shared memory allows multiple processes to access the same memory region.

Create:

```bash
nano shared.c
```

```c
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {

    int shmid = shmget(1234, 1024, 0666 | IPC_CREAT);

    char *data = (char *)shmat(shmid, NULL, 0);

    strcpy(data, "Hello Shared Memory");

    printf("Data: %s\n", data);

    shmdt(data);

    return 0;
}
```

Compile:

```bash
gcc shared.c -o shared
./shared
```

Check shared memory:

```bash
ipcs -m
```

This introduces four important functions:

```text
shmget() → Create/get shared memory
shmat()  → Attach shared memory
shmdt()  → Detach shared memory
shmctl() → Control/delete shared memory
```

---

## 5. Message Queue

**Definition:** A message queue allows processes to exchange structured messages through a queue managed by the kernel.

Create:

```bash
nano message.c
```

```c
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct message {
    long type;
    char text[100];
};

int main() {

    int msgid = msgget(1234, 0666 | IPC_CREAT);

    struct message msg;

    msg.type = 1;

    strcpy(msg.text, "Hello Message Queue");

    msgsnd(msgid, &msg, sizeof(msg.text), 0);

    printf("Message sent\n");

    return 0;
}
```

Compile:

```bash
gcc message.c -o message
./message
```

Check:

```bash
ipcs -q
```

Important functions:

```text
msgget() → Create/get queue
msgsnd() → Send message
msgrcv() → Receive message
msgctl() → Control/delete queue
```

---

## 6. Semaphore

**Definition:** A semaphore controls access to a shared resource so that processes don't access a critical resource incorrectly at the same time.

For beginners, first understand:

```text
Process A ──┐
            ↓
        Semaphore
            ↓
     Shared Resource
            ↑
Process B ──┘
```

A simple POSIX semaphore example:

```bash
nano semaphore.c
```

```c
#include <stdio.h>
#include <semaphore.h>

int main() {

    sem_t sem;

    sem_init(&sem, 0, 1);

    printf("Waiting...\n");

    sem_wait(&sem);

    printf("Critical section\n");

    sem_post(&sem);

    printf("Released\n");

    sem_destroy(&sem);

    return 0;
}
```

Compile:

```bash
gcc semaphore.c -o semaphore -pthread
./semaphore
```

The important operations are:

```text
sem_wait() → Lock / wait
sem_post() → Unlock / signal
```

---

## 7. Socket — Client/Server

**Definition:** Sockets allow two processes to communicate locally or over a network.

This is extremely important for understanding Linux networking.

```text
Client Process
      |
      | TCP
      ↓
   Port 8080
      |
      ↓
Server Process
```

A socket lab normally requires two programs:

```text
server.c
client.c
```

and introduces:

```text
socket()
bind()
listen()
accept()
connect()
send()
recv()
```

I recommend doing this **after the first six programs**, because socket programming introduces networking concepts such as IP addresses and ports.

## Practice Order

|  # | Program           | Main functions to learn                      | Difficulty |
| -: | ----------------- | -------------------------------------------- | ---------- |
|  1 | **Pipe**          | `pipe()`, `fork()`, `read()`, `write()`      | Easy       |
|  2 | **Signal**        | `signal()`, `kill()`                         | Easy       |
|  3 | **FIFO**          | `mkfifo()`, `open()`, `read()`, `write()`    | Easy       |
|  4 | **Shared Memory** | `shmget()`, `shmat()`, `shmdt()`             | Medium     |
|  5 | **Message Queue** | `msgget()`, `msgsnd()`, `msgrcv()`           | Medium     |
|  6 | **Semaphore**     | `sem_init()`, `sem_wait()`, `sem_post()`     | Medium     |
|  7 | **Socket**        | `socket()`, `bind()`, `listen()`, `accept()` | Medium     |

For Linux learning, **Pipe + `fork()` should be your first C IPC lab**. It teaches processes, parent/child relationships, file descriptors, `read()`, `write()`, and IPC together.
