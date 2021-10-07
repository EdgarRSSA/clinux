#!/usr/bin/env bash

# Archivos de compilacion

outbuild="./out";
mainfile="./ForkN.c";
files="";
runfile="${outbuild}/fork";

if [[ ! -d ${outbuild} ]]; then
    mkdir ${outbuild}
fi

echo -e "PWD:${PWD} MAIN:${mainfile} FILES:${files} RUN:${runfile}";

#
# Compilacion:
#

gcc -x c -Wall -o ${runfile} ${mainfile} ${files} || exit $?;

#
# Process info
#
echo -e "Compiled and Linked:  ${runfile}";
