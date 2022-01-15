#!/usr/bin/bash

PROGRAM_NAME=$(echo $0 | tr '/' '\n' | tail -n1) 
has_message=$1
commit_message=$2
EXIT_SUCCESS=0
EXIT_FAILURE=1
FLAG=$1

quick-git-push(){
    case $FLAG in
        -h | --help)
            print_help_message
            exit $EXIT_SUCCESS
            ;;
        "") # Automated git message
            git add . && git commit	-m "Auto-commit on `date +"%A, %m-%d-%Y, at %I:%M %p"`" && git push
            exit $EXIT_SUCCESS
            ;;
        :)  # For a short git commit message
            git add . && git commit -m "${commit_message}" ; git push
            exit $EXIT_SUCCESS
            ;;
        -l | --long-message) # For a long git commit message
            git add . && git commit && git push
            exit $EXIT_SUCCESS
            ;;
        -*)
            print_help_message
            exit $EXIT_FAILURE
            ;;
    esac

}

print_help_message(){
            echo -e "USE    $PROGRAM_NAME [option/arg] [message]

DESCRIPTION
    A script that performs the following commands:
        1. git add .
        2. git commit -m \"your commit message\"
        3. git push
OPTIONS
    --help          -h      Displays this message.
    --long-message  -l      Will open up a text editor for you to 
                            type out your commit message.
ARGUMENTS
    :                       Used for writing short commit messages.
DEFAULT OPTION
    The default commit message is the current date.
EXAMPLES
    $PROGRAM_NAME
    $PROGRAM_NAME : \"This is my short message\"
    $PROGRAM_NAME -l"
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
