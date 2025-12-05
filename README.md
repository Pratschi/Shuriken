# Shuriken
An Operating System, with a focus on performance, developing and User-Friendly UI
# File System
We need an User and Developer Friendly filesystem, so instead of having multiple folders for related things, we're going to simplify everything.
```/
├── Users
|    ├── Shared
│    └── User1
│        ├── Programs
│        ├── Downloads
│        └── .data.json (Hidden)
│            ├── startup
│            ├── settings
│            ├── start
│            └── desktop
├── sys (All system files)
│    ├── bin
│    ├── boot
|    ├── config (All config files for system and programs)
│    └── utilities
│        └── pak (Package manager)
│            └── packages
├── mnt (Mounted disks)
└── tmp (Temporary files)
```
Working with the filesystem is really simple, Specifing;
* `/` at the start of a file path, it means it's on the **root folder**.
* `.` at the start of the file path, it means it's on the **current folder**.
* `..` in the file path, it means it's on the **parent folder**. This can be used multiple times to go up multiple levels.
* `~` at the start of the file path, it means it's on the **current user folder**.
* `*` at the end of a **directory** path, it includes all the **files and subfolders**. Only works with certain commands, like `ls` and `rm`.

# Commands
Commands list, usage and arguments.
<br> cd `folder` > Go to directory
## File Management
**File Listing** > `ls [path]`
* List files in specified folder. If not specified, in current folder.
* Also capable of showing sub-folders with their files with paths ending with `*`, **Example:** `ls /sys/*`
* **Arguments:**
<br>    -a  > Show file permissions
<br>    -r  > Reverse sorting
<br>    -d  > List only directories
<br>    -f  > Show only files
<br>    -D  > Show directories first
<br>    -s  > Sort by size
<br>    -t  > Sort by last modified
<br>    -T  > Sort by creation time
<br>    -X  > Sort by extension

<br>**Directory Change** > `cd [folder]`
<br>Change directory to specified folder. If not specified, goes to **current user (Home)** directory.

<br>**Make Directory** > `mkdir [folder]`
<br>Create a new folder in the current directory.

<br>**Remove File/Directory** > `rm [path]`
<br>Remove specified file or directory. Allows for multiple files/folders as source.
<br>If directory, removes folder and contents **Only if -f is specified**.

<br>**Copy File/Directory** > `cp [source] [destination]`
<br>Copy file from source to destination. Copies folders only copy if `-r` is specified.
<br>Allows multiple files/folders as source.

<br>**Move File/Directory** > `mv [source] [destination]`
<br>Move file or directory from source to destination. Allows multiple files/directories as source.

<br>**View File Contents** > `cat [file]`
<br>Display contents of specified file.

<br>**Create Empty File** > `touch [file]`
<br>Create an empty file with specified name.

<br>**File Information** > `stat [file]`
<br>Display detailed information about specified file.
<br>Display owner, permissions, size, creation and modification dates.

## User Management
**List Users** > `lsusers`
<br>List all users on the system.

<br>**Add User** > `adduser [username]`
<br>Add a new user with specified username.
<br>Requires admin privileges.

<br>**Remove User** > `deluser [username]`
<br>Remove user with specified username.
<br>Requires admin privileges.

## System Management
**System Info** > `sysinfo`
<br>Display system information, like **OS version, uptime, and Hardware info.**
<br>Requires admin privileges.

<br>**Reboot System** > `reboot`
<br>Reboot the operating system.

<br>**Shutdown System** > `shutdown`
<br>Shutdown the operating system.

## Package Management
**Uses pak, the integrated package manager.**

<br>**Install Package** > `pak install package_name`
<br>Install specified package.

<br>**Remove Package** > `pak remove package_name`
<br>Remove specified package.

<br>**List Installed Packages** > `pak list`
<br>List all installed packages.

<br>**Update Package List** > `pak update`
<br>Update the package list from repositories.

<br>**Upgrade Installed Packages** > `pak upgrade`
<br>Upgrade all installed packages to their latest versions.