# STARX Software

This is the main software for controlling the MSU STARX Team robotic exoskeleton which participates in the annual Applied Collegiate Exoskeleton (ACE) Competition. For more information please visit https://www.egr.msu.edu/starx/.

## Introduction

The MSU STARX Team exosuit uses soft pneumatic actuators and biosensors to augment the wearer strength in different applications. This software was developed to control the internal pressure of each artificial muscle based on biosensor responses using a PID algorithm (feedback control).

Required operating system:

* Debian 9 (Stretch) 64-bit

Required hardware:

* Arduino Micro (https://store.arduino.cc/usa/arduino-micro)
* USB A to Micro-USB B Cable

## Installation

### 1. User

1.1. First, open a terminal window (Ctrl + Alt + T) and type the following code into the terminal to update the package list and upgrade the system.

```
sudo apt-get update && sudo apt-get upgrade
```

1.2. Also, make sure you have the most recent version of the GNU compiler collection, make utility, and git command.

```
sudo apt-get install build-essential git
```

1.3. Then, create a clone of this repository in your home directory.

```
cd ~
git clone https://github.com/msu-starx/starx.git
```

1.4. Inside the new directory, run the make command to compile and build the program.

```
cd starx
make
```

1.5. Since this software uses serial communication, you must verify if your user have the appropriate permissions before running the program. First, check your user membership.

```
groups
```

1.6. If your user is not part of the 'dialout' group, add your user to this group and restart your computer (or virtual machine).

```
sudo usermod -a -G dialout <username>
```

1.7. Upload the firmware (.ino) to Arduino Micro using the Arduino IDE. (Note: You can follow this guide to install Arduino IDE on Linux: https://www.arduino.cc/en/Guide/Linux)

Go to _Arduino > Tools_

```
Board = Arduino/Genuino Micro
Port = < Port Number >
Programmer = AVRISP mkII
```


1.8. Now, if you have the exosuit connected to the computer via USB, you can run the program with the following command:

```
./starx
```

### 2. Developer

After completing the **User** instructions above, follow the steps bellow to setup your developer environment.

2.1. Use the official instructions to install Atom for Debian:


https://flight-manual.atom.io/getting-started/sections/installing-atom/#debian-and-ubuntu-debapt

2.2. Next, install the Beautify package for Atom:

```
apm install atom-beautify
```

2.3. Also, you need to install Uncrustify as the default beautifier for C/C++

```
sudo apt-get install uncrustify
```

2.4. Now, you can configure Atom beautification options.

Go to _Atom > Packages > Atom Beautify > Settings_

For both C and C++ settings, select the following options:

```
Default Beautifier = Uncrustify
Check "Beautify On Save"
Config Path = < your path >/starx/uncrustify/custom-starx.cfg
```

Go to _Atom > Preferences > Editor_

```
Tab Length = 4
```

2.5. If you already have a GitHub account, update your git settings to match your user account.

```
git config --global user.name "yourusername"
git config --global user.email "youremail@address.com"
```
2.6. Please refer to the Git Cheat Sheet to learn command line operations for managing a GitHub repository.

https://services.github.com/on-demand/downloads/github-git-cheat-sheet.pdf

## Information

### Contact Info

thassyo@ieee.org

---

MSU STARX, Strength Augmenting Robotic eXoskeleton  
(c) 2017-2018
