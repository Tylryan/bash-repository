#! /bin/bash
# git add . ; git commit ; git push


has_message=$1
commit_message=$2

if [[ $has_message = ":" ]]; then
    git add . && git commit -m "${commit_message}" ; git push
else
    #Then push in the current directoryw ith the message being the current date and time
    git add . && git commit	-m "Auto-commit on `date +"%A, %m-%d-%Y, at %I:%M %p"`" && git push
fi




# I WILL LEAVE THIS HERE TO SHOW MYSELF THAT MORE COMPLICATED IS NOT ALWAYS BETTER.

## If there is neither a message nor location
#if [ -z $1 ] && [ -z $2 ]
#    then
#        #Then push in the current directoryw ith the message being the current date and time
#        git add . && git commit	-m "Auto-commit on `date +"%A, %m-%d-%Y, at %I:%M %p"`" && git push
## If there is a message but no location ...
#elif [ -n "$message" ] && [ -z "$location" ]
#    then
## 	Then do a git push in the current directory with the specified message 
#	git add . && git commit -m "${message}" && git push
## If there is a message and a location ...
#elif [ -n "$message" ] && [ -n "$location" ]
#    then
##         Then go to that location and do a git push with the specified message
#        cd "${location}" && git add . && git commit -m "${message}" && git push
#fi
