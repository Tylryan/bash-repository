#!/usr/bin/bash

# Takes about 5-10 minutes

backup_dirs=(
    alacritty awesome bspwm nvim polybar task zsh xfce4/terminal
)
backup_configs(){
for dir in ${backup_dirs[@]};do
    sudo cp -ru ~/.config/$dir ~/Ex-Drive/Dotfiles
done
}

backup_documents(){
    sudo cp -ru ~/Documents ~/Ex-Drive/
    sudo cp -ru ~/Pictures ~/Ex-Drive/
    sudo cp -ru ~/Bin ~/Ex-Drive/
    sudo cp -ru ~/Notes ~/Ex-Drive/
    sudo cp -ru ~/Applications ~/Ex-Drive/

    sudo cp -ru ~/.elinks ~/Ex-Drive/Dotfiles/elinks 


}

backup_configs
backup_documents
