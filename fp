#!/usr/bin/bash

# ---------------------------------------------------
# Intended to help automate flatpak installs and uninstalls
# By default, to run a flatpak, you have to run `flatpak run x.y.package`.
# This is annoying and the package name is not always obvious.
#
# Not working at the moment
# ---------------------------------------------------

install_location=/usr/local/bin
case $1 in
    "")
        echo "Error: no argument entered"
        exit 1
        ;;

    "uninstall" | "rm")
        shift
        flatpak uninstall $1
        if [ -f ${install_location}/$1 ];then
            rm ${install_location}/$1
        else
            echo "install not found: ${install_location}/${1}"
        fi
        ;;

    "install" | "i")
        shift
        flatpak install $1
        read -p "Bin Name: " bin_name || exit 1
        echo "#!/usr/bin/bash" > ${install_location}/${bin_name}
        echo "flatpak install $1" >> ${install_location}/${bin_name}
        chmod 744 ${install_location}/${bin_name}
        ;;
    "search" | "s")
        shift
        flatpak search $1
        ;;
    "list" | "ls")
        shift
        flatpak list
        ;;
    *)
        echo "Error: `$1` is not a valid command."
        exit 1
        ;;

esac
