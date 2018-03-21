
# My R/C car 
Code writen in C for avr mcu family. Also include PCB design files for manufacturing and assembly.
## Functions
Main functionality: 
- Servo with PWM control to turn forward wheels.
- DC engine with PWM control thru the H-bridge.
- Background light, under the car, green and blue leds controled with PWM.
- White headlamps with brightness change (PWM).
- Red back lights.
- Parking lights.
## Usage
1. Clone repo.
2. Make shure you have avr-gcc, compile all.
3. Burn your mcu.
```bash
$ git clone https://github.com/Zulljon/my-car-avr-solution.git
$ cd my-car-avr-solution
$ ./compile.sh clean all
$ ./compile.sh burn rx
```

## How it works
I was wanted to build such car in pair with android smartphone to control via bluetooth. But all massages receiving throw UART, so now the device can work with any uart radio modules (bluetooth or simple RF395)( for now in one direction). All data packing in 1 byte in transmitter and parsing in receiver, so this byte can care any kind of information about only one part of functions described in [fucntions](#functions). So massage are asynchronous, states of all parts save in RAM while device power on and just need/wait to be changed.
```
xxxyyyyy
```
- `xxx` - 3 major bits is assignation of blocks
-  `yyyyy` -  5 minor bits value of some parameter (for example brightness of headlamps 0..32), or it can be `qwert` - state of 1 of 5 leds `LEDq`,`LEDw`,`LEDe`,`LEDr`,`LEDt`.

So I notice that I am create a my own protocol. This byte call uart receive interrupt in MCU, massage is parsed and sends to value in RAM. from value in RAM thru main cycle setting up all periphery.


## Used programs
At the begining code was writen in Atmel Studio, after i start to use linux and made little fix to studio Makefile to compile under linux.
- /bin/bash
- GNU AVR Toolchain
- Atom
- Atmel Studio
- make
- avrdude

 P.S. I will add links later.