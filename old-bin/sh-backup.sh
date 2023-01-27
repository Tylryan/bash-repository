#! /usr/bin/bash

# If you used git clone git@Tylryan/bash_repository, then this should be redundant
update_readme=$1

if [ $update_readme == '-u' ];then
    # Pull before you send

	cd $(find ~/ -name bash_repository) 

    git pull &&
    
    # Update the readme 
    
    $EDITOR README.md ;

    # Copy files from ~/bin to ~/bash_repository

    cp ~/bin/* $(find ~/ -name bash_repository)

    # Git push

    git add . && git commit -m "Backing up my sh files on `date`" && git push
else
    # Pull before you send

    cd $(find ~/ -name bash_repository)

    git pull &&

    # Copy files from ~/bin to ~/bash_repository

    cp ~/bin/* $(find ~/ -name bash_repository) &&

    # Git push

    git add . && git commit -m "Backing up my sh files on `date`" && git push

fi




