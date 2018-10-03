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

### User

First, open a terminal window (Ctrl + Alt + T) and type the following code into the terminal to update the package list and upgrade the system.

```
sudo apt-get update && sudo apt-get upgrade
```

Also, make sure you have the most recent version of the GNU compiler collection, make utility, and git command.

```
sudo apt-get install build-essential git
```

Then, create a clone of this repository in your home directory.

```
cd ~
git clone https://github.com/msu-starx/starx.git
```

Inside the new directory, run the make command to compile and build the program.

```
cd starx
make
```

Since this software uses serial communication, you must verify if your user have the appropriate permissions before running the program. First, check your user membership.

```
groups
```

If your user is not part of the 'dialout' group, add your user to this group and restart your computer.

```
sudo usermod -a -G dialout <username>
```

Now, if you have the exosuit connected to the computer via USB, you can run the program with the following command:

```
./starx
```

### Developer

Under construction

## Information

Under construction

### Contact Info

thassyo@ieee.org
