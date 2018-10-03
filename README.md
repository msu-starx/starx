# STARX Software

## Introduction

## Installation

First, open a terminal window (Ctrl + Alt + T) and type the following code into the terminal to update the package list and upgrade the system.

```
sudo apt-get update && sudo apt-get upgrade
```

Then, make sure you have the most recent version of the GNU compiler collection, make utility, and git command.

```
sudo apt-get install build-essential git
```

Now, create a clone of this repository in your home directory.

```
cd ~
git clone https://github.com/msu-starx/starx.git
```

Inside the new directory, run the make command to compile and build the program.

```
cd starx
make
```

If you have the exosuit connected to the computer via USB, you can run the program with following command:

```
./starx
```

## Information

### Contact Info

thassyo@ieee.org
