#!/usr/bin/env bash
LOG="./../../logger.sh";
${LOG} "clear";

#
# Rutas
#
outbuild="./out";
runfile="${outbuild}/run";
mainfile="./credentials.c";

if [[ ! -d ${outbuild} ]]; then
    mkdir ${outbuild}
fi

$LOG "log" "PWD:${PWD} MAIN:${mainfile} RUN:${runfile}";

#
# Compilacion:
#

$LOG "run" "gcc -o ${runfile} ${mainfile}" || exit $?;

#
# RUN
#
$LOG "run" "${runfile}";
