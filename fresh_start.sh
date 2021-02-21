#! /usr/bin/bash

remove_repository=$1

# Make A bin directory
mkdir ~/bin

# Make the files executable
chmod 744 `ls`

# Move the files to bin
mv `ls` ~/bin

# Let bash know you want to read binaries from that location
PATH=$PATH:$HSME/bin

# Removing the original repository since it is not technically needed anymore
# Removing the original repository since it is not technically needed anymore
if [ $1 == "-r" ];then
        # Going back a directory
        cd ..
        Removing bash_repository
        rm -rf bash_repository/
else
	# Reboot your computer
	reboot

