To edit your crontab specifically with **Nano**, use:

```bash
EDITOR=nano crontab -e
```

If you want Nano to be the default editor for future `crontab -e` commands:

```bash
export EDITOR=nano
export VISUAL=nano
```

Then simply run:

```bash
crontab -e
```

### Example

Open crontab with Nano:

```bash
EDITOR=nano crontab -e
```

Add:

```cron
* * * * * date >> /home/ec2-user/date.log 2>&1
```

Then save in Nano:

```text
Ctrl + O    → Save
Enter       → Confirm filename
Ctrl + X    → Exit
```

Verify the cron job:

```bash
crontab -l
```

For Amazon Linux, if Nano isn't installed:

```bash
sudo dnf install nano -y
```

A good permanent setup is:

```bash
echo 'export EDITOR=nano' >> ~/.bashrc
echo 'export VISUAL=nano' >> ~/.bashrc
source ~/.bashrc
```

After that, every time you run:

```bash
crontab -e
```

it should open in **Nano**.
