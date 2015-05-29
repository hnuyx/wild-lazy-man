#!/bin/bash

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
#echo "tail: ${SnakeBody[1]}"
#echo "head: ${SnakeBody[$SnakeLen]}"

get_rc()
{
	value=$1
	_r=`expr $value / $__cols`
	_c=`expr $value % $__cols`
	echo $_r
	echo $_c
}

init()
{
	for pos in ${SnakeBody[*]}
	do
		_rc=`get_rc $pos`
		dot ${_rc[0]} ${_rc[1]} "#"
	done
}

get_tail_pos()
{
	echo `expr ($SnakeHead + 1) % $SnakeLen`
}

draw_next_pos()
{
}

# forever loop
run()
{
	while :
	do
		# read key event
		read -s -n 3 key_ctrl
		case $key_ctrl in
		$_UP_KEY)
			echo "up key"
		;;
		$_DOWN_KEY)
			echo "down key"
		;;
		$_LEFT_KEY)
			echo "left key"
		;;
		$_RIGHT_KEY)
			echo "right key"
		;;
		*)
			echo "unknow key $key_ctrl"
		;;
		esac
	done
}

# main
init

clear
