#!/bin/bash

if [[ $# -eq 0 || "$1" == "usage" || "$1" == "help" ]]; then
	echo "Usage: "
	echo "    ./compile.sh [Rx|Tx] [make|clean]"
	echo "    ./compile.sh [clean] [all]       "
	echo "    ./compile.sh [ |usage|help]      "
fi

ROOT_DIR="${PWD}"
MAKE_file="Makefile_linux.mak"


if [[ "$1" == "clean" ]]; then
	cd "$ROOT_DIR/Rx/Debug"
	echo "cd $(pwd)"
	make -f $MAKE_file clean
	cd "${ROOT_DIR}/Tx/Debug"
	echo "cd $(pwd)"
	make -f $MAKE_file clean
fi
if [[ "$1" == "all" || "$2" == "all" ]]; then
	echo '=============================RX=============================='
	cd "$ROOT_DIR/Rx/Debug"
	make -f $MAKE_file all
	echo '=============================TX=============================='
	cd "$ROOT_DIR/Tx/Debug"
	make -f $MAKE_file all
	echo '============================END=============================='
fi
if [[ "$1" == "Rx" ]]; then
	if [[ "$2" == "make" ]]; then
		cd "$ROOT_DIR/Rx/Debug"
		make -f $MAKE_file
	elif [[ "$2" == "clean" ]]; then
		cd "$ROOT_DIR/Rx/Debug"
		make -f $MAKE_file clean
	fi
fi
if [[ "$1" == "Tx" ]]; then
	if [[ "$2" == "make" ]]; then
		cd "$ROOT_DIR/Tx/Debug"
		make -f $MAKE_file
	elif [[ "$2" == "clean" ]]; then
		cd "$ROOT_DIR/Tx/Debug"
		make -f $MAKE_file clean
	fi
fi
if [[ "$1" == "burn" ]]; then
	if [[ -n 2 && "$2" == "rx" ]]; then
		# arduino UNO
		avrdude -p atmega328p -c arduino -P /dev/ttyACM0 -b 115200 -D -U flash:w:Rx/Debug/Rx.hex:i
	elif [[ -n 2 && "$2" == "tx" && false ]]; then
		avrdude -v -patmega328p -carduino -P/dev/ttyACM0 -b115200 -D -Uflash:w:Tx/Debug/Tx.hex:i
	fi
	
fi
