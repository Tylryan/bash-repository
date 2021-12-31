#!/usr/bin/python3.9

# Takes about 5 minutes
backup_configs(){
backup_dirs=(
    alacritty awesome bspwm nvim polybar task zsh
)

for dir in ${backup_dirs[@]}
do
    sudo cp -ru ~/.config/$dir ~/Ex-Drive/Dotfiles
done

}

backup_documents(){
    sudo cp -ru ~/Documents ~/Ex-Drive/Documents
    sudo cp -ru ~/Pictures ~/Ex-Drive/Pictures
    sudo cp -ru ~/Bin ~/Ex-Drive/Bin
}

backup_configs
backup_documents
