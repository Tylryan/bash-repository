#! /bin/bash

# This copies all of the directories in the main rice directory to the copy.

cd $(find ~/ -name Bootcamp) && cd 2-rice-bootcamp/;
git pull
cp -r $(find ~/ -name Bootcamp)/2-rice-bootcamp/* $(find ~/ -name Bootcamp)/1-rice-copy/ && echo "Copied" || echo "Something went wrong"

