#!/bin/bash

#usec
__usec=1
# rows, cols, half rows, half cols
__rows=`tput lines`
__cols=`tput cols`
__hr=`expr $__rows / 2`
__hc=`expr $__cols / 2`

# drow dot
# dot $row $col $char
dot()
{
	# row, coloum, char
	_r=$1
	_c=$2
	_char=$3
	tput cup $_r $_c
	echo -n $_char
}

dot_space()
{
	# row, coloum, char
	_r=$1
	_c=$2
	tput cup $_r $_c
	echo -n " "
}

# drow horizontal line
# hor_line $row $char
hor_line()
{
	# hide cursor
	tput civis

	# row
	_r=$1

	# character
	_char=$2

	# line
	tput cup $_r 0
	for((i=0;i<$__cols;++i))
	do
		echo -n $_char
		usleep $_usec
	done
	echo ""
}

# drow vertical line
# ver_line $col $char
ver_line()
{
	# col
	_c=$1

	# character
	_char=$2

	# line
	for((i=0;i<$__rows;++i))
	do
		tput cup $i $_c
		echo -n $_char
		usleep $_usec
	done
	echo ""
}
