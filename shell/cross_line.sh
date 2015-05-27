#!/bin/bash

# hide cursor
tput civis

source line.sh

clear

hor_line $_hr "-"
ver_line $_hc "|"

for((j=1;j<$_hr;++j))
do
	for((i=1;i<$_hc;++i))
	do
		# left/up
		_tr=`expr $_hr - $j - 1`
		_tc=`expr $_hc - $i`
		dot $_tr $_tc "\\"
		# right/up
		_tr=`expr $_hr - $j - 1`
		_tc=`expr $_hc + $i`
		dot $_tr $_tc "/"
		# right/down
		_tr=`expr $_hr + $j - 1`
		_tc=`expr $_hc + $i`
		dot $_tr $_tc "\\"
		# left/down
		_tr=`expr $_hr + $j - 1`
		_tc=`expr $_hc - $i`
		dot $_tr $_tc "/"
		usleep $_usec
	done

	for((i=1;i<$_hc;++i))
	do
		# left/up
		_tr=`expr $_hr - $j - 1`
		_tc=`expr $_hc - $i`
		dot_space $_tr $_tc
		# right/up
		_tr=`expr $_hr - $j - 1`
		_tc=`expr $_hc + $i`
		dot_space $_tr $_tc
		# right/down
		_tr=`expr $_hr + $j - 1`
		_tc=`expr $_hc + $i`
		dot_space $_tr $_tc
		# left/down
		_tr=`expr $_hr + $j - 1`
		_tc=`expr $_hc - $i`
		dot_space $_tr $_tc 
		usleep $_usec
	done
done

for((i=1;i<$_hc;++i))
do
	for((j=1;j<$_hr;++j))
	do
		# left/up
		_tr=`expr $_hr - $j - 1`
		_tc=`expr $_hc - $i`
		dot $_tr $_tc "\\"
		# right/up
		_tr=`expr $_hr - $j - 1`
		_tc=`expr $_hc + $i`
		dot $_tr $_tc "/"
		# right/down
		_tr=`expr $_hr + $j - 1`
		_tc=`expr $_hc + $i`
		dot $_tr $_tc "\\"
		# left/down
		_tr=`expr $_hr + $j - 1`
		_tc=`expr $_hc - $i`
		dot $_tr $_tc "/"
		usleep $_usec
	done

	for((j=1;j<$_hr;++j))
	do
		# left/up
		_tr=`expr $_hr - $j - 1`
		_tc=`expr $_hc - $i`
		dot_space $_tr $_tc
		# right/up
		_tr=`expr $_hr - $j - 1`
		_tc=`expr $_hc + $i`
		dot_space $_tr $_tc
		# right/down
		_tr=`expr $_hr + $j - 1`
		_tc=`expr $_hc + $i`
		dot_space $_tr $_tc
		# left/down
		_tr=`expr $_hr + $j - 1`
		_tc=`expr $_hc - $i`
		dot_space $_tr $_tc 
		usleep $_usec
	done
done

clear

# show cursor
tput cnorm
