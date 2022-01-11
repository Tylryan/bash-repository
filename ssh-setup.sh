#!/usr/bin/bash

# A script that automates the ssh key generation and copies the pub file to your clipboard

EXIT_SUCCESS=0
EXIT_FAILURE=1
SUCCESS=1
cont=true

ssh_setup() {
    get_user_info
    create_ssh_keys
    copy_ssh_pub_to_clipboard
    setup_git_config

    return $SUCCESS
}

get_user_info() {
    while [[ $cont == true ]]
    do
        read -r -p "Enter Your Email Address: " email
        read -r -p "Is this correct? y/[N] --> ${email}: " response
        is_correct_email=[Yy]
        if [[ $response = $is_correct_email ]];then 
            cont=false
        fi
    done
    return $SUCCESS
}

create_ssh_keys() {
    ssh-keygen -t ed25519 -C \"$email\" 
    eval "$(ssh-agent -s)"
    ssh-add ~/.ssh/id_ed25519
    return $SUCCESS
}

copy_ssh_pub_to_clipboard() {
    echo "******************************************************"
    read -r -p "Which distro do you have? ([a]rch or [d]ebian): " distro
    echo "******************************************************"
    case $distro in
        [aA] | [aA]rch)
            sudo pacman -S xclip
            xclip -selection clipboard < ~/.ssh/id_ed25519.pub
            ;;
        [dD] | [dD]ebian)
            sudo apt install xclip
            xclip -selection clipboard < ~/.ssh/id_ed25519.pub
            ;;
        *)
            echo "Please Select Either ARCH or DEBIAN Next Time"
            wait 2
            ;;
    esac
    return $SUCCESS
}

setup_git_config() {
    echo "**********************************"
    read -r -p "What is your First Name? " first_name
    read -r -p "What is your Last Name? " last_name
    echo "**********************************"
    echo "**********************************"
    echo "Public Key copied to clipboard..."
    echo "**********************************"
    echo "**********************************"
    echo -e "Go paste that key into Github, then copy the following to your terminal.\n"

    git config --global user.email $email
    git config --global user.name "$first_name $last_name"
    return $SUCCESS
}


ssh_setup
exit $EXIT_SUCCESS
