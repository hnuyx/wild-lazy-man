#!/bin/bash
# author henuyx

# hide cursor
tput civis

# clear and include line.sh
source line.sh

# snake pid
snake_pid=$$

# snake speed
snake_speed=100000
# food count
food_count_init=10
food_count=0

# up/down/left/right key
_UP_KEY='[A'
_DOWN_KEY='[B'
_LEFT_KEY='[D'
_RIGHT_KEY='[C'

# length
SnakeLen=10
# current direction
# 0 for up, 1 for down, 2 for left, 3 for right
_UP_DIR=20
_DOWN_DIR=21
_LEFT_DIR=22
_RIGHT_DIR=23
_CUR_DIR=$_RIGHT_DIR

# SnakeBody[$SnakeHead] is head, SnakeBody[($SnakeHead + 1)%SnakeLen] is tail
SnakeHead=`expr $SnakeLen - 1`
SnakeBody=( [0]=0 1 2 3 4 5 6 7 8 9 )
# mark map, 0  for nothing, 1 for Snake body, 2 for food
_Mark_Nothing=0
_Mark_SnakeBody=1
_Mark_Food=2
#_MarkMap=( [0]=1 1 1 1 1 1 1 1 1 1 )
_MarkMap=( [0]=$_Mark_SnakeBody $_Mark_SnakeBody $_Mark_SnakeBody $_Mark_SnakeBody $_Mark_SnakeBody $_Mark_SnakeBody $_Mark_SnakeBody $_Mark_SnakeBody $_Mark_SnakeBody $_Mark_SnakeBody )

# next position, default is right direction
#echo "rows: $__rows cols $__cols"
_MAX_POS=`expr $__rows \* $__cols`
_NEXT_POS=`expr \( ${SnakeBody[$SnakeHead]} + 1 \) % $_MAX_POS`
_SUCCESS_LEN=`expr $_MAX_POS - 100`
#echo "max pos: $_MAX_POS next pos: $_NEXT_POS"

# save stty attr
_STTY_G=`stty -g`

game_exit()
{
	kill -9 $snake_pid
	stty $_STTY_G
	# show cursor
	tput cnorm
	exit 0
}

trap "game_exit" INT TERM

game_over()
{
	echo ""
	echo "What The Fuck Operation"
	echo "Game Over"
	kill $PPID

	game_exit
}

success()
{
	echo ""
	echo "Well Done"
	echo "Congratulations"
	kill $PPID

	game_exit
}

#trap 'tput cnorm; exit 0' INT

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

eat_food()
{
	# move left body
	for((i=$SnakeLen;i>$SnakeHead;--i))
	do
		SnakeBody[i]=${SnakeBody[i - 1]}
	done

	# insert a new position
	SnakeLen=`expr $SnakeLen + 1`
	#SnakeBody[$SnakeLen - 1]=${SnakeBody[$SnakeHead]}
	SnakeHead=`get_tail_pos`
	SnakeBody[$SnakeHead]=$_NEXT_POS

	# adjust speed
	if [ "$snake_speed" -gt "100" ]; then
		snake_speed=`expr $snake_speed - 100`
	fi

	if [ "$SnakeLen" -eq "$_SUCCESS_LEN" ]; then
		success
	fi
}

rand_food()
{
	# get no-body position
	_rp=`expr $RANDOM % $_MAX_POS`
	#try_food=0
	food_flag=0
	while :
	do
		#if [ "$try_food" -gt "10" ]; then
		#	break
		#fi
		case ${_MarkMap[$_rp]} in
		$_Mark_SnakeBody)
			_rp=`expr $RANDOM % $_MAX_POS`
		;;
		$_Mark_Food)
			_rp=`expr $RANDOM % $_MAX_POS`
		;;
		*)
			food_flag=1
			break
		;;
		esac

		#try_food=`expr $try_food + 1`
	done

	if [ "$food_flag" -eq "1" ]; then
		# draw food
		_rc=`get_rc $_rp`
		dot ${_rc[0]} ${_rc[1]} "#"
		_MarkMap[$_rp]=$_Mark_Food

		# record food count
		food_count=`expr $food_count + 1`
	fi
}

draw_next_pos()
{
	# judge head hit itself
	case ${_MarkMap[$_NEXT_POS]} in
	$_Mark_SnakeBody)
		game_over
	;;
	$_Mark_Food)
		# eat food
		eat_food
		# record food count
		food_count=`expr $food_count - 1`
	;;
	*)
		# erase tail position
		SnakeHead=`get_tail_pos`
		_rc=`get_rc ${SnakeBody[$SnakeHead]}`
		dot_space ${_rc[0]} ${_rc[1]}
		_MarkMap[${SnakeBody[$SnakeHead]}]=$_Mark_Nothing

		# draw netx position
		_rc=`get_rc $_NEXT_POS`
		dot ${_rc[0]} ${_rc[1]} "#"
		SnakeBody[$SnakeHead]=$_NEXT_POS
		_MarkMap[${SnakeBody[$SnakeHead]}]=$_Mark_SnakeBody
	;;
	esac
}

live_snake()
{
	clear
	init
	for((i=0;i<$food_count_init;++i))
	do
		rand_food
	done

	trap "_CUR_DIR=$_UP_DIR" $_UP_DIR
	trap "_CUR_DIR=$_DOWN_DIR" $_DOWN_DIR
	trap "_CUR_DIR=$_LEFT_DIR" $_LEFT_DIR
	trap "_CUR_DIR=$_RIGHT_DIR" $_RIGHT_DIR

	while :
	do
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

		# add food
		if [ "$food_count" -lt "$food_count_init" ]; then
			# rand food
			rand_food
		fi
		#echo "$food_count" >> log

		usleep $snake_speed
	done
}

control_dir()
{
	snake_pid=$1

	while :
	do
		# read key event
		read -s -n 3 key_ctrl
		case $key_ctrl in
		$_UP_KEY)
			#echo "up key"
			if [ "$_CUR_DIR" -ne "$_DOWN_DIR" ]; then
				_CUR_DIR=$_UP_DIR
				kill -$_CUR_DIR $snake_pid
			fi
		;;
		$_DOWN_KEY)
			#echo "down key"
			if [ "$_CUR_DIR" -ne "$_UP_DIR" ]; then
				_CUR_DIR=$_DOWN_DIR
				kill -$_CUR_DIR $snake_pid
			fi
		;;
		$_LEFT_KEY)
			#echo "left key"
			if [ "$_CUR_DIR" -ne "$_RIGHT_DIR" ]; then
				_CUR_DIR=$_LEFT_DIR
				kill -$_CUR_DIR $snake_pid
			fi
		;;
		$_RIGHT_KEY)
			#echo "right key"
			if [ "$_CUR_DIR" -ne "$_LEFT_DIR" ]; then
				_CUR_DIR=$_RIGHT_DIR
				kill -$_CUR_DIR $snake_pid
			fi
		;;
		*)
			#echo "unknow key $key_ctrl"
		;;
		esac
	done
}

# main

if [ "$1" == "moving" ]; then
	live_snake
else
	bash $0 moving &
	control_dir $! 2>/dev/null
fi

clear
