#!/usr/bin/bash

# Git won't let me do it. So here is a list of configs
~/bin && ${gp} ;
~/Notes && ${gp} ;
cp -r ~/.config/polybar/* ~/.config/bspwm/polybar.outer ;
cp -r ~/.config/sxhkd/* ~/.config/bspwm/sxhkd1 ;
~/.config/bspwm && ${gp} ;
~/.config/nvim && ${gp} ;
~/.config/task && ${gp} ;
# Don't need to cp. I have them linked
~/.config/zsh/ && ${gp} ;
