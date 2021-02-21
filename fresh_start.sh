#! /usr/bin/bash

options=$1
remove= cd .. ; rm -rf bash_repository/


# Make A bin directory
mkdir ~/bin

# Make the files executable
chmod 744 `ls`

# Move the files to bin
mv `ls` ~/bin

# Let bash know you want to read binaries from that location
PATH=$PATH:$HSME/bin

if [[ $options =~ "r" ]] && [[ $options =~ "R" ]];then
	$remove ; reboot
	
elif [[ $options == "-R" ]];then
        # Removing the original bash_repository
	$remove
elif [[ $options == "-r"]]
	# Reboot your computer
	reboot
fi
