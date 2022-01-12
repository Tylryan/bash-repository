#!/usr/bin/bash



ARGS=($@)
LEN_ARGS=${#@}

if [[ ${ARGS[0]} =~ "-" ]];
then
    ARGS=${@:2}
fi

echo ${ARGS}

