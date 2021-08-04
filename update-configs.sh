#!/usr/bin/bash
gp=`git add . ; git commit -m "Auto Commit" ; git push`
cd ~/bin && ${gp} ;
cd ~/Notes && ${gp} ;
cp -r ~/.config/polybar/* ~/.config/bspwm/polybar.outer ;
cp -r ~/.config/sxhkd/* ~/.config/bspwm/sxhkd1 ;
cd ~/.config/bspwm && ${gp} ;
cd ~/.config/nvim && ${gp} ;
cd ~/.config/task && ${gp} ;
# Don't need to cp. I have them linked
cd ~/.config/zsh/ && ${gp} ;
