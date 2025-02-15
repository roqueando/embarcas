# embarcas
![embarcas](images/embarcas.png)

> embarcas is a projecto for studiying embedded systems, and mark my progress, all in C/C++


### updates and improvements

the project still in development and the next updates will be coded in the following tasks:
- [x] led blinky
- [x] RGB led blinky
- [x] SimulIDE circuits
- [x] Seven Segments Display (SSD)
- [x] Shift Register (SR)
- [ ] LCD Display
- [ ] KiCAD eletronic schematics
- [ ] more...

## 💻 pre-requisites

before start, verify if you have the following things:

- you have installed avr-libc, avr-g++, avr-gcc and avrdude (in debian systems you can do a `sudo apt-get install avr-libc avr-g++ avr-gcc avrdude`)
- you have installed `make` tool in your machine (probably any unix system come with this tool)
- you have installed `gcc` and `g++` for C/C++ development purposes

## 🚀 installing embarcas

For install `embarcas` first you need:

- clone repository
```sh
$ git clone https://github.com/roqueando/embarcas.git
```

- build hex file
```sh
$ make build
```

- build test.c
```sh
$ make build-test
```

## ☕using embarcas

To use embarcas you need to flash this generated hex file in some AVR microchip, most specific atmega328p (or Arduino Nano), for learning I'm using SimulIDE for simulating all eletronics schematics with simulation by running my code.

>### opening and using schematics

You can use SimulIDE and open the desired circuit but always will be the main.hex that will be loading, so be sure that the code is correct with the circuit that you want to run.

1. Ctrl+O to select the circuit file
2. Select in the `circuits/<circuit_file_name>.sim1`
3. Right click on the board (probably mega328PB-XX) and select `Load firmware`
4. Choose your generated main.hex file.
5. Start simulation and enjoy!

>### flashing to a board
Usually I use the Arduino Nano board but if you have a AVR atmega328p, this will run perfectly.
1. build the hex file
```sh
$ make build
```
2. Make sure that you have plugged your board into your PC and have `/dev/ttyUSB0` port, if your board is in another serial port, change in Makefile (I'll make this more flexible later)
3. Run the flash command with avrdude
```sh
$ make flash
```
4. See your program running in your board!
