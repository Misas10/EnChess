# En-chess

## Table of Contents
* [Overview](#Overview)
* [Instalation](#Instalation)
  * [Debian/Ubuntu](#Debian-ubuntu)
  * [Arch Linux](#Arch-linux)
* [Credits](#Credits)

## Overview
A chess game made with SDL2 in C, and also has a sick engine (coming soon)

## Instalation*
_*Only for Linux and MacOS_

### Install SDL2

#### Debian/Ubuntu-based systems <a name="Debian-ubuntu"></a>
```bash
sudo apt update
sudo apt-get install libsdl2-dev
```
#### Arch Linux

```bash
sudo pacman -S sdl2
```
For more info you can check the SDL2 [Repo](https://github.com/libsdl-org/SDL).

### Install EnChess 
1. Clone the repo
```bash
git clone https://github.com/Misas10/EnChess
cd EnChess
```

2. Build the project
```bash
./EnChess -b
```

3. Now you just need to run it
```bash
./EnChess
```

You can also just **build and run** the file using the `-br` flag like:
```bash
./EnChess -br
```

It might be necessary to change the permissions to run the script file
if so just run:
```bash
chmod +x EnChess.sh
```

The `EnChess.sh` runs the engine. It also has some flags avaliable: `-r`, `-b`, `-h`. For more
information just run `./EnChess --help`.

## Credits: 
Assets/UI - [GeeekyBoy / royal-chess](https://github.com/GeeekyBoy/royal-chess/tree/main)


