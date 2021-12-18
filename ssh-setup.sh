#!/usr/bin/bash
cont=true
while [ $cont = true ]
do
    echo "Enter Your Email Address: "
    read email
    echo "Is this correct? y/[N] --> ${email}"
    read response
    go=[Yy]
    if [[ $response =~ $go ]];then
        cont=false
    fi
done
ssh-keygen -t ed25519 -C \"$email\" 
wait 1
eval "$(ssh-agent -s)"
wait 1
ssh-add ~/.ssh/id_ed25519

echo "**********************************"
echo "Which distro do you have? ([a]rch or [d]ebian): "
read distro
echo "**********************************"
case $distro in
    [aA])
        sudo pacman -S xclip
        xclip -selection clipboard < ~/.ssh/id_ed25519.pub
        ;;
    [dD])
        sudo apt install xclip
        xclip -selection clipboard < ~/.ssh/id_ed25519.pub
        ;;
    *)
        echo "Please Select Either ARCH or DEBIAN Next Time"
        wait 2
        ;;
esac
echo "**********************************"
echo "What is your First Name? "
read first 
echo "What is your Last Name? "
read last
echo "**********************************"
echo "**********************************"
echo "Public Key copied to clipboard..."
echo "**********************************"
echo "**********************************"
echo "Go paste that key into Github, then copy the following to your terminal.\n"
git config --global user.email "$email"
git config --global user.name "$first $last"
