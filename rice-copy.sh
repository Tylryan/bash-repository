#! /bin/bash

# This copies all of the directories in the main rice directory to the copy.

cd ~/Bootcamp/2-rice-bootcamp/;
git pull
cp -r ~/Bootcamp/2-rice-bootcamp/* ~/Bootcamp/1-rice-copy/
echo copied

