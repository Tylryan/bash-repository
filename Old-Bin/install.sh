#! /usr/bin/bash

# THIS INSTALL SCRIPT IS PRETTY REDUNDANT
# Checks to see if you have zsh
case $SHELL in 
	/usr/bin/zsh)
		# Let bash know you want to read binaries from that location
		echo "PATH=$PATH:$HOME/bin" >> ~/.zshrc
		;;
	*)
		echo "PATH=$PATH:$HOME/bin" >> ~/.bashrc
		;;
esac


# Remove the original bash_repository and reboot.
if [[ $options =~ "r" ]] && [[ $options =~ "R" ]];then # Works 02/21/21
    rm -rf ~/bash_repository/
    reboot
	
# Remove the original bash repository, but no reboot.
elif [[ $options == "-R" ]];then #This works 02/21/21
        # Removing the original bash_repository
    rm -rf ~/bash_repository/

# Reboot, but don't remove the origina bash repository.
elif [[ $options == "-r" ]];then # Works 02/21/21
	#Reboot your computer
	reboot
fi
