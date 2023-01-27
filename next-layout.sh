#!/usr/bin/bash

layout_file=~/.config/current-kbd-layout/layout.txt
current_layout=$(cat ${layout_file})

case ${current_layout} in 
    0)
        setxkbmap ru
        echo 1 > ${layout_file}
        ;;
    1)
        setxkbmap us
        echo 0 > ${layout_file}
        ;;
    *)
        echo "IDK"
        ;;
esac
