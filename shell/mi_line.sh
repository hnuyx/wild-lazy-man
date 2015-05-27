#!/bin/bash

# hide cursor
tput civis

source line.sh

clear

hor_line $_hr "-"
ver_line $_hc "|"

for((k=1;k<$_hr;++k))
do
	for((i=1,j=k;i<$_hc && j<$_hr;++i, ++j))
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
	
	for((i=1,j=k;i<$_hc && j<$_hr;++i, ++j))
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

for((k=1;k<$_hc;++k))
do
	for((i=k,j=1;i<$_hc && j<$_hr;++i, ++j))
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
	
	for((i=k,j=1;i<$_hc && j<$_hr;++i, ++j))
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

# show cursor
tput cnorm
