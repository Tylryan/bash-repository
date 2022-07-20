#!/usr/bin/bash

# A program that toggles the visibility 
# of a single window for BSPWM

# Current window location in memory
export win_id=$(xdo id)
TMP_FILE=/tmp/window-id.txt

hide_window()
{
    # Put that location in a temp file.
    echo $win_id > $TMP_FILE
    # hide the window
    xdo hide $win_id
}

show_window()
{
    # Find the id of the hidden window
    hidden_win_id=$(cat ${TMP_FILE})
    xdo show $hidden_win_id
    rm $TMP_FILE
}

toggle_window()
{
    if [[ -f $TMP_FILE ]];then
        show_window
    else
        hide_window
    fi
}

toggle_window
exit 0
