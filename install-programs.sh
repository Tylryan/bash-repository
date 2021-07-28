# Update
sudo pacman -Syu

# Putting all my files back
git clone https://github.com/Tylryan/bash_repository.git
cd bash_repository && ./install.sh && cd ~/bin/ && ./git-ssh-setup.sh
cd
rm -rf ~/.config/bspwm/ 
git clone git@github.com:Tylryan/bspwm-config.git bspwm && mv bspwm ~/.config
git clone git@github.com:Tylryan/zsh_config.git zsh ; mv zsh ~/.config

zsh
git clone git@github.com:Tylryan/task_warrior_backup.git task && mv task .config/
git clone git@github.com:Tylryan/nvim_backup.git

echo "\$TASKRC='~/.config/task'" >> .zshrc
echo "\$TASKDATA='~/.config/task'" >> .zshrc

git clone git@github.com:Tylryan/Notes.git
# Applications
sudo pacman -S firefox neovim taskwarrior-tui npm emacs ripgrep fd cmake

# Coding Stuff
sudo pacman -S lua jre-openjdk jre-openjdk-headless jdk-openjdk maven tomcat10 typescript 

# AUR

yay -S brave-bin eclipse-java-bin

# DOOM EMACS
git clone --depth 1 https://github.com/hlissner/doom-emacs ~/.emacs.d
~/.emacs.d/bin/doom instally

cd .emacs.d/ ; ./doom sync

reboot
