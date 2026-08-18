# 📖 Linux System Administration Essentials

---

# 📑 Table of Contents

1. Process Management Essentials
2. System Initialization and Services
3. Software Installation in Linux
4. Backup and Archival
5. Log Management and Analysis
6. Scheduling Tasks using Cron Jobs

---

# 🛠️ 1️⃣ Process Management Essentials

---

# 📌 What is a Process?

A **process** is a running instance of a program in Linux.

Examples:

* Apache Web Server
* SSH Service
* Bash Shell
* Python Script

Every process has:

* PID (Process ID)
* Parent Process
* Priority
* Memory Usage
* CPU Usage

---

# 📌 View Running Processes

| Command | Description                | Example         |
| :------ | :------------------------- | :-------------- |
| `ps`    | View running processes     | `ps aux`        |
| `top`   | Real-time monitoring       | `top`           |
| `htop`  | Interactive process viewer | `htop`          |
| `pidof` | Get PID of process         | `pidof nginx`   |
| `pgrep` | Find process by name       | `pgrep apache2` |

---

## 🔹 View All Running Processes

```bash
ps aux
```

Example Output:

```bash
USER       PID %CPU %MEM COMMAND
root         1  0.0  0.1 /sbin/init
ec2-user  2456  1.2  0.5 nginx
```

---

## 🔹 Real-Time Process Monitoring

```bash
top
```

Quit:

```bash
q
```

---

## 🔹 Install htop

Ubuntu/Debian:

```bash
sudo apt install htop -y
```

RHEL/CentOS:

```bash
sudo yum install htop -y
```

Check Version:

```bash
htop --version
```

Run:

```bash
htop
```

---

## 🔹 Find Process IDs

```bash
pidof httpd
```

```bash
pgrep nginx
```

---

# 📌 Install Apache for Practice

Ubuntu:

```bash
sudo apt install apache2 -y
```

RHEL/CentOS:

```bash
sudo yum install httpd -y
```

Start Service:

```bash
sudo systemctl start httpd
```

Enable at Boot:

```bash
sudo systemctl enable httpd
```

Check PID:

```bash
pidof httpd
```

---

# 📌 Start / Stop Services

| Command             | Description         |
| :------------------ | :------------------ |
| `systemctl start`   | Start service       |
| `systemctl stop`    | Stop service        |
| `systemctl restart` | Restart service     |
| `systemctl status`  | Check status        |
| `systemctl enable`  | Enable during boot  |
| `systemctl disable` | Disable during boot |

---

## 🔹 Examples

```bash
sudo systemctl start httpd
```

```bash
sudo systemctl stop httpd
```

```bash
sudo systemctl restart httpd
```

```bash
sudo systemctl status httpd
```

---

# 📌 Kill Processes

| Command       | Description          |
| :------------ | :------------------- |
| `kill PID`    | Stop process         |
| `kill -9 PID` | Force kill           |
| `killall`     | Kill by process name |
| `pkill`       | Kill using pattern   |

---

## 🔹 Examples

```bash
kill 1234
```

```bash
kill -9 1234
```

```bash
killall nginx
```

```bash
pkill apache2
```

---

# 📌 Background & Foreground Jobs

Run in Background:

```bash
sleep 100 &
```

Check Jobs:

```bash
jobs
```

Foreground:

```bash
fg %1
```

Background:

```bash
bg %1
```

---

# 📌 Process Priority

Start with Priority:

```bash
nice -n 10 sleep 100
```

Change Priority:

```bash
renice 5 1234
```

---

# 📌 Resource Monitoring

Check Memory:

```bash
free -m
```

VM Statistics:

```bash
vmstat 5
```

Install sysstat:

```bash
sudo yum install sysstat -y
```

Disk IO:

```bash
iostat
```

---

# 📌 Process Tree

```bash
pstree
```

Example:

```bash
systemd─┬─sshd───bash
        ├─httpd
        └─nginx
```

---

# 📌 Important Signals

| Signal       | Meaning        |
| :----------- | :------------- |
| SIGTERM (15) | Graceful stop  |
| SIGKILL (9)  | Force kill     |
| SIGSTOP      | Pause process  |
| SIGCONT      | Resume process |

---

# 📌 Important Points to Remember

- ✅ Every process has a unique PID
- ✅ PID 1 is usually `systemd`
- ✅ Use `top` or `htop` for monitoring
- ✅ Use `kill -9` only if required
- ✅ Monitor CPU and memory regularly
- ✅ Use `systemctl` for service management

---

# ⚙️ 2️⃣ System Initialization and Services

---

# 📌 What is System Initialization?

The process Linux follows during startup to initialize the operating system and services.

Modern Linux distributions use:

```bash
systemd
```

---

# 📌 Boot Process Flow

```text
BIOS/UEFI
   ↓
Bootloader (GRUB)
   ↓
Kernel
   ↓
systemd
   ↓
Services & User Space
```

---

# 📌 Manage Services

Start Service:

```bash
sudo systemctl start nginx
```

Stop Service:

```bash
sudo systemctl stop nginx
```

Restart:

```bash
sudo systemctl restart nginx
```

Status:

```bash
sudo systemctl status nginx
```

Enable at Boot:

```bash
sudo systemctl enable nginx
```

Disable:

```bash
sudo systemctl disable nginx
```

---

# 📌 View System Logs

```bash
journalctl
```

Service Logs:

```bash
journalctl -u nginx
```

Live Logs:

```bash
journalctl -f
```

Boot Logs:

```bash
journalctl -b
```

---

# 📌 Targets / Runlevels

| Target            | Purpose       |
| :---------------- | :------------ |
| multi-user.target | CLI mode      |
| graphical.target  | GUI mode      |
| rescue.target     | Recovery mode |

Check Default Target:

```bash
systemctl get-default
```

---

# 📌 Important Points to Remember

- ✅ `systemd` controls services
- ✅ Services can auto-start during boot
- ✅ Use `journalctl` for troubleshooting
- ✅ Failed services can impact applications

---

# 📦 3️⃣ Software Installation in Linux

---

# 📌 Package Managers

| Distribution  | Package Manager |
| :------------ | :-------------- |
| Ubuntu/Debian | apt             |
| RHEL/CentOS   | yum / dnf       |
| SUSE          | zypper          |

---

# 📌 Update Packages

Ubuntu:

```bash
sudo apt update -y
```

RHEL:

```bash
sudo yum update -y
```

---

# 📌 Install Packages

Ubuntu:

```bash
sudo apt install nginx -y
```

RHEL:

```bash
sudo yum install nginx -y
```

---

# 📌 Remove Packages

Ubuntu:

```bash
sudo apt remove nginx -y
```

RHEL:

```bash
sudo yum remove nginx -y
```

---

# 📌 Search Packages

```bash
apt search docker
```

```bash
yum search docker
```

---

# 📌 Check Installed Packages

Ubuntu:

```bash
dpkg -l
```

RHEL:

```bash
rpm -qa
```

---

# 📌 Important Points to Remember

- ✅ Update repositories before installation
- ✅ Use trusted repositories only
- ✅ Package managers resolve dependencies automatically

---

# 💾 4️⃣ Backup and Archival

---

# 📌 Backup Tools

| Tool  | Purpose         |
| :---- | :-------------- |
| tar   | Archive         |
| gzip  | Compression     |
| zip   | Compress files  |
| rsync | Synchronization |

---

# 📌 Create Archive

```bash
tar -cvf backup.tar myfolder/
```

---

# 📌 Extract Archive

```bash
tar -xvf backup.tar
```

---

# 📌 Compress Archive

```bash
tar -czvf backup.tar.gz myfolder/
```

---

# 📌 Extract Compressed Archive

```bash
tar -xzvf backup.tar.gz
```

---

# 📌 Rsync Backup

```bash
rsync -av source/ destination/
```

---

# 📌 Important Backup Locations

* `/etc`
* `/home`
* `/var/www`
* Databases
* Application Configurations

---

# 📌 Important Points to Remember

- ✅ Verify backups regularly
- ✅ Keep backup copies remotely
- ✅ Automate backups with cron jobs
- ✅ Test restore process regularly

---

# 📜 5️⃣ Log Management and Analysis

---

# 📌 Importance of Logs

Logs help in:

* Troubleshooting
* Security Analysis
* Monitoring
* Auditing

---

# 📌 Common Log Locations

| Directory           | Purpose             |
| :------------------ | :------------------ |
| `/var/log/messages` | System logs         |
| `/var/log/syslog`   | General logs        |
| `/var/log/auth.log` | Authentication logs |
| `/var/log/secure`   | Security logs       |
| `/var/log/nginx/`   | Nginx logs          |

---

# 📌 View Logs

```bash
cat /var/log/syslog
```

```bash
less /var/log/syslog
```

---

# 📌 Monitor Logs Live

```bash
tail -f /var/log/syslog
```

---

# 📌 Search Logs

```bash
grep error /var/log/syslog
```

---

# 📌 Log Rotation

Configuration:

```bash
/etc/logrotate.conf
```

---

# 📌 Journal Logs

```bash
journalctl
```

Boot Logs:

```bash
journalctl -b
```

---

# 📌 Important Points to Remember

- ✅ Logs consume disk space
- ✅ Use `tail -f` for real-time monitoring
- ✅ Monitor auth logs for security
- ✅ Configure log rotation properly

---

# ⏰ 6️⃣ Scheduling Tasks using Cron Jobs

---

# 📌 What is Cron?

Cron is used to automate repetitive tasks.

Examples:

* Backups
* Cleanup Scripts
* Monitoring Tasks
* Database Jobs

---

# 📌 Edit Cron Jobs

```bash
crontab -e
```

View Cron Jobs:

```bash
crontab -l
```

Remove Cron Jobs:

```bash
crontab -r
```

---

# 📌 Cron Syntax

```bash
* * * * * command
```

| Field | Meaning |
| :---- | :------ |
| 1     | Minute  |
| 2     | Hour    |
| 3     | Day     |
| 4     | Month   |
| 5     | Weekday |

---

# 📌 Examples

Run Every Minute:

```bash
* * * * * date
```

Run Daily at 2 AM:

```bash
0 2 * * * /backup.sh
```

Run Every Sunday:

```bash
0 0 * * 0 script.sh
```

---

# 📌 Redirect Output to Log File

```bash
0 2 * * * /backup.sh >> backup.log 2>&1
```

---

# 📌 Cron Service Status

Ubuntu:

```bash
sudo systemctl status cron
```

RHEL:

```bash
sudo systemctl status crond
```

---

# 📌 Important Points to Remember

- ✅ Use full file paths in cron jobs
- ✅ Test scripts manually before scheduling
- ✅ Redirect output to log files
- ✅ Ensure cron service is running

---

# 🚀 Final Important Linux System Administration Tips

- ✅ Monitor processes regularly
- ✅ Keep systems updated
- ✅ Secure services and logs
- ✅ Automate repetitive tasks
- ✅ Maintain proper backups
- ✅ Analyze logs regularly
- ✅ Learn troubleshooting commands daily
- ✅ Practice service management commands
- ✅ Monitor CPU, memory, and disk usage
- ✅ Understand Linux boot and service flow

---

# 👨‍💻 Author

**Atul Kamble**

* [LinkedIn](https://www.linkedin.com/in/atuljkamble/?utm_source=chatgpt.com)
* [GitHub](https://github.com/atulkamble?utm_source=chatgpt.com)
* [X (Twitter)](https://x.com/Atul_Kamble?utm_source=chatgpt.com)
* [Instagram](https://www.instagram.com/atuljkamble?utm_source=chatgpt.com)
* [Website](https://www.atulkamble.in?utm_source=chatgpt.com)
