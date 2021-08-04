#!/usr/bin/bash
gp=`~/bin/gp.sh`
cd ~/bin && ${gp} &
sleep 5
cd ~/Notes && sleep 2 && pwd && ${gp}&
sleep 5
echo "Done"
cp -r ~/.config/polybar/* ~/.config/bspwm/polybar.outer
echo "Done"
cp -r ~/.config/sxhkd/* ~/.config/bspwm/sxhkd1
echo "Done"
cd ~/.config/bspwm && ${gp} &
sleep 5
echo "Done"
cd ~/.config/nvim && ${gp}&
sleep 5
echo "Done"
cd ~/.config/task && ${gp} &
sleep 5
echo "Done"
# Don't need to cp. I have them linked
cd ~/.config/zsh/ && ${gp} &
sleep 5
echo "Done"
