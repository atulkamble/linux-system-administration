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

# ⏰ 6️⃣ Scheduling Tasks Using Cron Jobs

---

# 📌 What is Cron?

**Cron** is a time-based job scheduler in Linux used to **automatically execute commands and scripts at specified times or intervals**.

Cron is commonly used for repetitive system administration and automation tasks.

### Common Uses

* Backups
* Cleanup scripts
* Monitoring tasks
* Database jobs
* Log rotation
* Running maintenance scripts
* Generating reports
* Automated file synchronization

A scheduled task configured using Cron is called a **Cron Job**.

---

# 📌 Cron Components

Two important components are:

| Component        | Description                                     |
| ---------------- | ----------------------------------------------- |
| `cron` / `crond` | Background service that executes scheduled jobs |
| `crontab`        | Command used to create and manage Cron jobs     |

On **Ubuntu/Debian**, the service is generally called:

```bash
cron
```

On **RHEL / CentOS / Amazon Linux**, it is generally called:

```bash
crond
```

---

# 📌 Check Linux Operating System

Before installing or configuring Cron, check the Linux distribution:

```bash
cat /etc/os-release
```

Example:

```text
NAME="Amazon Linux"
VERSION="2023"
```

---

# 📌 Install Cron

## Amazon Linux 2023

Install the `cronie` package:

```bash
sudo dnf install cronie -y
```

## Amazon Linux 2 / RHEL-based Systems

```bash
sudo yum install cronie -y
```

## Ubuntu / Debian

```bash
sudo apt update
sudo apt install cron -y
```

---

# 📌 Verify Cron Installation

Check whether the `crontab` command is available:

```bash
crontab --version
```

You can also locate the command:

```bash
which crontab
```

---

# 📌 Start and Enable Cron Service

## Amazon Linux / RHEL

Start the service:

```bash
sudo systemctl start crond
```

Enable Cron automatically after system reboot:

```bash
sudo systemctl enable crond
```

Start and enable it using a single command:

```bash
sudo systemctl enable --now crond
```

Check status:

```bash
sudo systemctl status crond
```

Expected:

```text
Active: active (running)
```

## Ubuntu / Debian

```bash
sudo systemctl enable --now cron
sudo systemctl status cron
```

---

# 📌 Managing Cron Jobs

## Edit Cron Jobs

```bash
crontab -e
```

This opens the current user's crontab file.

---

## View Cron Jobs

```bash
crontab -l
```

Example:

```text
* * * * * date >> /home/ec2-user/date.log 2>&1
```

---

## Remove All Cron Jobs

```bash
crontab -r
```

> ⚠️ **Warning:** `crontab -r` removes all Cron jobs for the current user.

To confirm before removing:

```bash
crontab -i -r
```

---

# 📌 Cron Syntax

Basic syntax:

```text
* * * * * command
```

The five `*` characters represent different time fields.

```text
* * * * * command
│ │ │ │ │
│ │ │ │ └── Day of Week
│ │ │ └──── Month
│ │ └────── Day of Month
│ └──────── Hour
└────────── Minute
```

| Field | Meaning      | Common Values |
| ----- | ------------ | ------------- |
| 1     | Minute       | `0-59`        |
| 2     | Hour         | `0-23`        |
| 3     | Day of Month | `1-31`        |
| 4     | Month        | `1-12`        |
| 5     | Day of Week  | `0-7`         |

For the weekday field, `0` and `7` commonly represent **Sunday**.

---

# 📌 Cron Special Characters

Cron supports several useful special characters.

| Character | Meaning         | Example       |
| --------- | --------------- | ------------- |
| `*`       | Every value     | `* * * * *`   |
| `,`       | Multiple values | `0 8 * * 1,5` |
| `-`       | Range           | `0 8 * * 1-5` |
| `/`       | Interval/step   | `*/5 * * * *` |

Example:

```cron
*/5 * * * * command
```

Runs the command every **5 minutes**.

---

# 📌 Cron Examples

## Run Every Minute

```cron
* * * * * date
```

Meaning:

```text
Every minute
Every hour
Every day
Every month
Every weekday
```

---

## Run Every 5 Minutes

```cron
*/5 * * * * command
```

---

## Run Every Hour

```cron
0 * * * * command
```

Runs when the minute becomes `00`.

Example:

```text
01:00
02:00
03:00
04:00
```

---

## Run Daily at 2 AM

```cron
0 2 * * * /backup.sh
```

Explanation:

| Field   | Value |
| ------- | ----- |
| Minute  | `0`   |
| Hour    | `2`   |
| Day     | `*`   |
| Month   | `*`   |
| Weekday | `*`   |

Therefore:

```text
Every day at 02:00 AM
```

---

## Run Every Sunday at Midnight

```cron
0 0 * * 0 /path/script.sh
```

Meaning:

```text
00:00 every Sunday
```

---

## Run Monday to Friday at 8:30 AM

```cron
30 8 * * 1-5 command
```

---

# 📌 Redirect Cron Output to a Log File

Cron jobs should generally write their output to a log file so that execution can be verified and errors can be investigated.

Example:

```cron
0 2 * * * /backup.sh >> backup.log 2>&1
```

### Explanation

| Operator | Meaning                                              |
| -------- | ---------------------------------------------------- |
| `>`      | Write output and overwrite file                      |
| `>>`     | Append output to file                                |
| `2>`     | Redirect error output                                |
| `2>&1`   | Send errors to the same destination as normal output |

Recommended:

```cron
0 2 * * * /home/ec2-user/backup.sh >> /home/ec2-user/backup.log 2>&1
```

Both normal output and errors will be written to:

```text
/home/ec2-user/backup.log
```

---

# 📌 Basic Cron Practical Lab

Let's create a Cron job that writes the current date and time to a file **every minute**.

## Step 1 — Open Crontab

```bash
crontab -e
```

---

## Step 2 — Add the Cron Job

Inside the editor, add:

```cron
* * * * * date >> /home/ec2-user/date.log 2>&1
```

Save and exit.

---

## Step 3 — Verify the Cron Job

```bash
crontab -l
```

Expected:

```cron
* * * * * date >> /home/ec2-user/date.log 2>&1
```

---

## Step 4 — Wait 1–2 Minutes

Cron will execute the `date` command every minute.

Check the file:

```bash
cat /home/ec2-user/date.log
```

Example output:

```text
Thu Aug 20 07:10:01 IST 2026
Thu Aug 20 07:11:01 IST 2026
Thu Aug 20 07:12:01 IST 2026
```

This confirms that the Cron job is working.

---

# 📌 Backup Script Cron Job

Suppose you have a backup script:

```text
/home/ec2-user/backup.sh
```

Make it executable:

```bash
chmod +x /home/ec2-user/backup.sh
```

Edit the crontab:

```bash
crontab -e
```

Add:

```cron
0 2 * * * /home/ec2-user/backup.sh >> /home/ec2-user/backup.log 2>&1
```

The backup script will now execute every day at **2:00 AM**.

---

# 📌 Important: Cron Expressions Are Not Terminal Commands

Do **not** type a Cron expression directly into Bash.

Incorrect:

```bash
[ec2-user@server ~]$ 0 2 * * * /backup.sh
```

You may receive:

```text
-bash: 0: command not found
```

This happens because Bash tries to execute `0` as a Linux command.

Instead, run:

```bash
crontab -e
```

Then put the expression **inside the crontab editor**:

```cron
0 2 * * * /home/ec2-user/backup.sh
```

---

# 📌 Use Absolute Paths

Avoid:

```cron
0 2 * * * script.sh
```

Prefer:

```cron
0 2 * * * /home/ec2-user/script.sh
```

Cron runs with a more limited environment than your interactive shell. Using absolute paths makes jobs more reliable.

You can find a command's absolute path using:

```bash
which date
```

Example:

```text
/usr/bin/date
```

You could therefore use:

```cron
* * * * * /usr/bin/date >> /home/ec2-user/date.log 2>&1
```

---

# 📌 Cron Service Status

## Ubuntu / Debian

```bash
sudo systemctl status cron
```

Restart:

```bash
sudo systemctl restart cron
```

## RHEL / CentOS / Amazon Linux

```bash
sudo systemctl status crond
```

Restart:

```bash
sudo systemctl restart crond
```

---

# 📌 Troubleshooting

## Problem: `crontab: command not found`

Example:

```text
-bash: crontab: command not found
```

Install Cron on Amazon Linux:

```bash
sudo dnf install cronie -y
```

Then:

```bash
sudo systemctl enable --now crond
```

---

## Problem: `cron.service could not be found`

On Amazon Linux/RHEL, use:

```bash
sudo systemctl status crond
```

instead of:

```bash
sudo systemctl status cron
```

---

## Problem: Cron Job Is Not Running

Check the service:

```bash
sudo systemctl status crond
```

Check configured jobs:

```bash
crontab -l
```

Check your script permissions:

```bash
ls -l /home/ec2-user/backup.sh
```

Make the script executable if necessary:

```bash
chmod +x /home/ec2-user/backup.sh
```

Test the script manually:

```bash
/home/ec2-user/backup.sh
```

---

# 📌 Quick Command Reference

```bash
# Check Linux distribution
cat /etc/os-release

# Install Cron - Amazon Linux 2023
sudo dnf install cronie -y

# Install Cron - Amazon Linux 2
sudo yum install cronie -y

# Verify
crontab --version

# Start Cron
sudo systemctl start crond

# Enable Cron
sudo systemctl enable crond

# Start + Enable Cron
sudo systemctl enable --now crond

# Check service
sudo systemctl status crond

# Edit Cron jobs
crontab -e

# List Cron jobs
crontab -l

# Remove all current user's Cron jobs
crontab -r

# Check test output
cat /home/ec2-user/date.log
```

---

# 📌 Quick Cron Examples

```cron
# Every minute
* * * * * date

# Every 5 minutes
*/5 * * * * command

# Every hour
0 * * * * command

# Every day at 2 AM
0 2 * * * /home/ec2-user/backup.sh

# Every Sunday at midnight
0 0 * * 0 /home/ec2-user/script.sh

# Monday-Friday at 8:30 AM
30 8 * * 1-5 command

# Every minute with logging
* * * * * date >> /home/ec2-user/date.log 2>&1

# Daily backup with logging
0 2 * * * /home/ec2-user/backup.sh >> /home/ec2-user/backup.log 2>&1
```

---

# 🎯 Summary

**Cron workflow:**

```text
Install Cron
     ↓
Start crond
     ↓
Enable crond
     ↓
crontab -e
     ↓
Add schedule + command
     ↓
Save
     ↓
crontab -l
     ↓
Verify execution/logs
```

For **Amazon Linux 2023**, the essential setup is:

```bash
sudo dnf install cronie -y
sudo systemctl enable --now crond
sudo systemctl status crond
crontab -e
```

Then add your scheduled task inside `crontab -e`:

```cron
* * * * * date >> /home/ec2-user/date.log 2>&1
```

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
