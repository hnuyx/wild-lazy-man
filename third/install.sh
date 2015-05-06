#!/bin/bash
# install third-party: log4cplus, protobuf, gtest

echo "We are going to install third party lib"

# suffix
TARGZ=".tar.gz"
TGZ=".tgz"

# glog4cplus
log4cplus_pkg="log4cplus-1.1.0"
# gprotobuf
protobuf_pkg="protobuf-2.4.1"
# gtest
# libevent
# boost
# memcached

# install directory
InstallDir=$HOME/usr
if [ ! -d $InstallDir ]; then
	mkdir -p $InstallDir
fi
echo "Install Dir: $InstallDir"

# environment file
EnvFile=$HOME"/.bash_profile"

# third part directory
ThirdPartDir=$PWD/third_part

# add environment variable
# needs 2 params, $1 for env name, $2 for env value
add_env_var()
{
	if [ 2 -ne $# ]; then
		return
	fi
	# env/value
	env=$1
	value=$2
	echo "ENV: $env=$value"

	# find env in env file
	exist=`grep $env $EnvFile | wc -l`

	if [ 0 -eq $exist ]; then
		# env not exist and add env into env file
		echo "add env var: $1 INTO FILE: $EnvFile"
	else
		# env has already been exist and update it
		echo "update env var: $1 IN FILE: $EnvFile"
		sed -i "/$env/d" $EnvFile
	fi
	echo "export $env=$value" >> $EnvFile
}

# extract package
# needs 3 params, $1 for directory, $2 for package name, $3 for package suffix
extract_pkg()
{
	if [ 3 -ne $# ]; then
		return
	fi
	# directory, pkg name, pkg suffix
	dir=$1
	pkg=$2
	suffix=$3

	case $suffix in
	$TARGZ)
		cd $dir && tar xzvf $pkg$suffix > $dir/log/$pkg.log 2>&1
		cd -
		;;
	$TGZ)
		cd $dir && tar xzvf $pkg$suffix > $dir/log/$pkg.log 2>&1
		cd -
		;;
	esac
}

# auto make install
# needs 2 params, $1 for dir, $2 for package name
automake_install()
{
	if [ 2 -ne $# ]; then
		return
	fi
	# directory, pkg name
	dir=$1
	pkg=$2

	cd $dir/$pkg
	./configure --prefix=$InstallDir >> $dir/log/$pkg.log 2>&1
	make >> $dir/log/$pkg.log 2>&1
	make install >> $dir/log/$pkg.log 2>&1
	cd -

	rm -rf $dir/$pkg
}

# install log4cplus
install_log4cplus()
{
	echo ""
	echo "install log4cplus"

	if [ ! -f $ThirdPartDir/$log4cplus_pkg$TARGZ ]; then
		echo "$ThirdPartDir/$log4cplus_pkg$TARGZ is not exist!!!"
		return
	fi

	# add env var
	add_env_var LOG4CPLUS_ROOT $InstallDir

	# extract pkg
	extract_pkg $ThirdPartDir $log4cplus_pkg $TARGZ

	# make and install
	automake_install $ThirdPartDir $log4cplus_pkg
}

#install protobuf
install_protobuf()
{
	echo ""
	echo "install protobuf"

	if [ ! -f $ThirdPartDir/$protobuf_pkg$TARGZ ]; then
		echo "$ThirdPartDir/$protobuf_pkg$TARGZ is not exist!!!"
		return
	fi

	# add env var
	add_env_var PROTOBUF_ROOT $InstallDir

	# extract pkg
	extract_pkg $ThirdPartDir $protobuf_pkg $TARGZ

	# make and install
	automake_install $ThirdPartDir $protobuf_pkg
}

# install google log4cplus
install_log4cplus

# install google protobuf
install_protobuf

# install google test

# install libevent

# install boost

# install memcached
