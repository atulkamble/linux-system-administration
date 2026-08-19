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
