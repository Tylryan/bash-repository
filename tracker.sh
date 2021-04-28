#!/usr/bin/bash

subject=$1
date=$2
hours=$3

# Print the last 10 entries of your list.

check_options=0
# If all fields are filled out
if [ ! -z ${subject} ] && [ ! -z ${date} ] && [ ! -z ${hours} ]
    then
        # Append entry to records.csv
        echo "${subject},${date},${hours}" >> $(find ~/Documents/Coding/Python/tracker -iname records.csv)

# If only the first field is filled out, check_options turned on
elif [ ! -z ${subject} ] && [ -z ${date} ] && [ -z ${hours} ]
    then 
        check_options=1
# Otherwise, I assume they have not entered in something correctly.
else 
    echo You need to have a Subject Date and Hours in that order.
fi

if [ ${check_options} == 1 ]
    then
        case ${subject} in 
            -t)
                tail $(find ~/Documents/Coding/Python/ -name records.csv)
            ;;
        esac
fi
