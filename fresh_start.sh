#! /usr/bin/bash

options=$1

# Make A bin directory
mkdir ~/bin || :

# Make the files executable
chmod 744 `ls`

# Move the files to bin
cp -r `ls` ~/bin &&

# Let bash know you want to read binaries from that location
PATH=$PATH:$HSME/bin

if [[ $options =~ "r" ]] && [[ $options =~ "R" ]];then # Works 02/21/21
    cd .. ; rm -rf bash_repository/
    reboot
	
elif [[ $options == "-R" ]];then #This works 02/21/21
        # Removing the original bash_repository
    cd .. ; rm -rf bash_repository/
elif [[ $options == "-r" ]];then # Works 02/21/21
	#Reboot your computer
	reboot
fi
