#!/usr/bin/bash

PROGRAM_NAME=$(basename $0)
SERVER_ADDRESS=$(echo $SERVER_ADDRESS)
SERVER_HOST=$(echo $SERVER_HOST)
PORT=$(echo $SERVER_PORT)

WHAT=""
WHERE=""

case $1 in
    -h | --help)
        echo -e "USAGE      
$PROGRAM_NAME [file-to-copy] [server-location]

DESCRIPTION
    Copies a file/directory from your local directory to the server 
    specified in your environemnt variables.
Examples
    (Don't enter in anything)
    Copy your documents directory to your server. 
    \`$PROGRAM_NAME\`

    Copy a file/dir to your server's home dir, only enter the file 
    you want to copy.
    \`$PROGRAM_NAME file.txt\`

    Copy a file/dir to a specific location in your server, enter 
    the filename and the server directory 
    (Don't use /home/name or ~/)
    \`$PROGRAM_NAME file.txt documents/notes/computers\`"

    exit 0
esac

case $# in
    # Copies my documents to my server
    0)
        scp -r -P $PORT ~/documents $SERVER_ADDRESS:/home/$SERVER_HOST/external-drive/documents
        exit 0
        ;;
    # Copies a file/dir to my server's home dir
    1)
        WHAT=$1
        scp -r -P $PORT $WHAT $SERVER_ADDRESS:/home/$SERVER_HOST
        exit 0
        ;;
    # Copies a file/dir to a specific dir in my server
    2)
        WHAT=$1
        WHERE=$2
        scp -r -P $PORT $WHAT $SERVER_ADDRESS:/home/$SERVER_HOST/$WHERE
        exit 0
        ;;
esac

exit 0
