#!/bin/bash

# hide cursor
tput civis

# clear and include line.sh
clear
source line.sh

# up/down/left/right key
_UP_KEY='[A'
_DOWN_KEY='[B'
_LEFT_KEY='[D'
_RIGHT_KEY='[C'

# length
SnakeLen=10
# current direction
# 0 for up, 1 for down, 2 for left, 3 for right
_UP_DIR=0
_DOWN_DIR=1
_LEFT_DIR=2
_RIGHT_DIR=3
_CUR_DIR=$_RIGHT_DIR

# SnakeBody[$SnakeHead] is head, SnakeBody[($SnakeHead + 1)%SnakeLen] is tail
SnakeHead=`expr $SnakeLen - 1`
SnakeBody=( [0]=0 1 2 3 4 5 6 7 8 9 )

# next position, default is right direction
#echo "rows: $__rows cols $__cols"
_MAX_POS=`expr $__rows \* $__cols`
_NEXT_POS=`expr \( ${SnakeBody[$SnakeHead]} + 1 \) % $_MAX_POS`
#echo "max pos: $_MAX_POS next pos: $_NEXT_POS"

get_rc()
{
	# value = _r*__cols + _c
	value=$1
	_r=`expr $value / $__cols`
	_c=`expr $value % $__cols`
	echo $_r
	echo $_c
}

init()
{
	# draw begining position from tail to head
	for pos in ${SnakeBody[*]}
	do
		_rc=`get_rc $pos`
		dot ${_rc[0]} ${_rc[1]} "#"
	done
}

# get tail pos
get_tail_pos()
{
	echo `expr \( $SnakeHead + 1 \) % $SnakeLen`
}

draw_next_pos()
{
	# erase tail position
	SnakeHead=`get_tail_pos`
	_rc=`get_rc ${SnakeBody[$SnakeHead]}`
	dot_space ${_rc[0]} ${_rc[1]}

	# draw netx position
	_rc=`get_rc $_NEXT_POS`
	dot ${_rc[0]} ${_rc[1]} "#"
	SnakeBody[$SnakeHead]=$_NEXT_POS
}

# forever loop
run()
{
	while :
	do
		# read key event
		read -s -t 1 -n 3 key_ctrl
		case $key_ctrl in
		$_UP_KEY)
			#echo "up key"
			if [ "$_CUR_DIR" -ne "$_DOWN_DIR" ]; then
				_CUR_DIR=$_UP_DIR
			fi
		;;
		$_DOWN_KEY)
			#echo "down key"
			if [ "$_CUR_DIR" -ne "$_UP_DIR" ]; then
				_CUR_DIR=$_DOWN_DIR
			fi
		;;
		$_LEFT_KEY)
			#echo "left key"
			if [ "$_CUR_DIR" -ne "$_RIGHT_DIR" ]; then
				_CUR_DIR=$_LEFT_DIR
			fi
		;;
		$_RIGHT_KEY)
			#echo "right key"
			if [ "$_CUR_DIR" -ne "$_LEFT_DIR" ]; then
				_CUR_DIR=$_RIGHT_DIR
			fi
		;;
		*)
			#echo "unknow key $key_ctrl"
		;;
		esac

		case $_CUR_DIR in
		$_UP_DIR)
			_NEXT_POS=`expr \( ${SnakeBody[$SnakeHead]} + $_MAX_POS - $__cols \) % $_MAX_POS`
		;;
		$_DOWN_DIR)
			_NEXT_POS=`expr \( ${SnakeBody[$SnakeHead]} + $__cols \) % $_MAX_POS`
		;;
		$_LEFT_DIR)
			_NEXT_POS=`expr \( ${SnakeBody[$SnakeHead]} + $_MAX_POS - 1 \) % $_MAX_POS`
		;;
		$_RIGHT_DIR)
			_NEXT_POS=`expr \( ${SnakeBody[$SnakeHead]} + 1 \) % $_MAX_POS`
		;;
		esac

		draw_next_pos
		#usleep 200000
	done
}

# main
init
run

clear

# show cursor
tput cnorm
