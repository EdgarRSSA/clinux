#!/usr/bin/env bash

# Archivos de compilacion

outbuild="./out";
mainfile="./ThreadsIO.c";
files="";
runfile="${outbuild}/run";

if [[ ! -d ${outbuild} ]]; then
    mkdir ${outbuild}
fi

echo -e "PWD:${PWD} \nMAIN:${mainfile} \nFILES:${files} \nRUN:${runfile}";

#
# Compilacion:
#

gcc -std=gnu17 -pthread -x c -Wall -o ${runfile} ${mainfile} ${files} || exit $?;
