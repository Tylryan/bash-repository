#               Update
cd
sudo pacman -Syu

#               Putting all my files back
./bin/git-ssh-setup.sh
rm -rf ~/.config/bspwm/ 
git clone git@github.com:Tylryan/bspwm-config.git bspwm && mv bspwm ~/.config

#               ZSH SETUP
git clone git@github.com:Tylryan/zsh_config.git zsh ; mv zsh ~/.config

cp .config/zsh/.p10k.zsh ~/
cp .config/zsh/.zshrc ~/

#               Syntax Highlighting
git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ~/.config/zsh/plugins/zsh-syntax-highlighting
#               Auto-Suggestions
git clone https://github.com/zsh-users/zsh-autosuggestions ~/.config/zsh/plugins/zsh-autosuggestions
#               Powerlevel10k: Customized PS1
git clone --depth=1 https://github.com/romkatv/powerlevel10k.git ~/.config/zsh/plugins/powerlevel10k


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
~/.emacs.d/bin/doom install

cd .emacs.d/ ; ./doom sync

reboot
