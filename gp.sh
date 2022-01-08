#!/usr/bin/bash
# git add . ; git commit ; git push


has_message=$1
commit_message=$2
EXIT_SUCCESS=0
EXIT_FAILURE=1
FLAG=$1
PROGRAM_NAME=$(echo $0 | tr '/' '\n' | tail -n1)

quick-git-push(){

    quick-git-push-help

    if [[ $has_message = ":" ]]; then
        git add . && git commit -m "${commit_message}" ; git push
        # Could add [[ $? -eq 0 ]] || exit EXIT_FAILURE
    else
        #Then push in the current directoryw ith the message being the current date and time
        git add . && git commit	-m "Auto-commit on `date +"%A, %m-%d-%Y, at %I:%M %p"`" && git push
        # Could add [[ $? -eq 0 ]] || exit EXIT_FAILURE
    fi
    exit EXIT_SUCCESS
}

quick-git-push-help(){
    case $FLAG in
        -h | --help)
            echo -e "USE\tgp : [optional message]

DESCRIPTION
\tA script that performs the following commands:
    \t\t1. git add .
    \t\t2. git commit -m \"your commit message\"
    \t\t3. git push
DEFAULT OPTION
\tThe default commit message is the current date"
            exit $EXIT_SUCCESS
    esac

}
quick-git-push




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
# fi
