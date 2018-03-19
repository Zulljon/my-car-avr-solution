#!/bin/bash

if [[ -n 1 || "$1" == "usage" || "$1" == "help" ]]; then
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
