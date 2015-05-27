#!/bin/bash

#usec
_usec=1
# rows, cols, half rows, half cols
_rows=`tput lines`
_cols=`tput cols`
_hr=`expr $_rows / 2`
_hc=`expr $_cols / 2`

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
	for((i=0;i<$_cols;++i))
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
	for((i=0;i<$_rows;++i))
	do
		tput cup $i $_c
		echo -n $_char
		usleep $_usec
	done
	echo ""
}
