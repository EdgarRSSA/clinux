#!/usr/bin/env bash
LOG="./../../logger.sh";
${LOG} "clear";

# Compilar y Ejecutar

outbuild="./out";
runfile="${outbuild}/run";
mainfile="./paths-manage.c";

if [[ ! -d ${outbuild} ]]; then
    mkdir ${outbuild}
fi

$LOG "log" "PWD:${PWD} MAIN:${mainfile} RUN:${runfile}";

#
# Compilacion:
#

$LOG "run" "gcc -D DEBUG -o ${runfile} ${mainfile}" || exit $?;

#
# RUN
#
$LOG "run" "${runfile} . .. ./out/";
