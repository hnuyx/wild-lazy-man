#!/bin/bash

# hide cursor
tput civis

source line.sh

clear

hor_line $__hr "-"
ver_line $__hc "|"

for((j=1;j<$__hr;++j))
do
	for((i=1;i<$__hc;++i))
	do
		# left/up
		_tr=`expr $__hr - $j - 1`
		_tc=`expr $__hc - $i`
		dot $_tr $_tc "\\"
		# right/up
		_tr=`expr $__hr - $j - 1`
		_tc=`expr $__hc + $i`
		dot $_tr $_tc "/"
		# right/down
		_tr=`expr $__hr + $j - 1`
		_tc=`expr $__hc + $i`
		dot $_tr $_tc "\\"
		# left/down
		_tr=`expr $__hr + $j - 1`
		_tc=`expr $__hc - $i`
		dot $_tr $_tc "/"
		usleep $_usec
	done

	for((i=1;i<$__hc;++i))
	do
		# left/up
		_tr=`expr $__hr - $j - 1`
		_tc=`expr $__hc - $i`
		dot_space $_tr $_tc
		# right/up
		_tr=`expr $__hr - $j - 1`
		_tc=`expr $__hc + $i`
		dot_space $_tr $_tc
		# right/down
		_tr=`expr $__hr + $j - 1`
		_tc=`expr $__hc + $i`
		dot_space $_tr $_tc
		# left/down
		_tr=`expr $__hr + $j - 1`
		_tc=`expr $__hc - $i`
		dot_space $_tr $_tc 
		usleep $_usec
	done
done

for((i=1;i<$__hc;++i))
do
	for((j=1;j<$__hr;++j))
	do
		# left/up
		_tr=`expr $__hr - $j - 1`
		_tc=`expr $__hc - $i`
		dot $_tr $_tc "\\"
		# right/up
		_tr=`expr $__hr - $j - 1`
		_tc=`expr $__hc + $i`
		dot $_tr $_tc "/"
		# right/down
		_tr=`expr $__hr + $j - 1`
		_tc=`expr $__hc + $i`
		dot $_tr $_tc "\\"
		# left/down
		_tr=`expr $__hr + $j - 1`
		_tc=`expr $__hc - $i`
		dot $_tr $_tc "/"
		usleep $_usec
	done

	for((j=1;j<$__hr;++j))
	do
		# left/up
		_tr=`expr $__hr - $j - 1`
		_tc=`expr $__hc - $i`
		dot_space $_tr $_tc
		# right/up
		_tr=`expr $__hr - $j - 1`
		_tc=`expr $__hc + $i`
		dot_space $_tr $_tc
		# right/down
		_tr=`expr $__hr + $j - 1`
		_tc=`expr $__hc + $i`
		dot_space $_tr $_tc
		# left/down
		_tr=`expr $__hr + $j - 1`
		_tc=`expr $__hc - $i`
		dot_space $_tr $_tc 
		usleep $_usec
	done
done

clear

# show cursor
tput cnorm
